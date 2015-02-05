/**
 * POPCC (POP-C++ Compiler)
 * @file popcc.in
 * @brief This program handle the compilation of POP-C++ source files. It prepare the files by parsing them with the POP-C++ parser
 * and then compile them with a standard C++ compiler. Finally, object file are linked with the POP-C++ library.
 *
 * Modifications:
 * Date           Author      Description
 * 2012/07/12   clementval  Finalize automatic pack when @pack is not specified. This is handled at the end of parsing only if no
 *                                        @pack directive has been found.
 * 2012/11/09
 */

#include "popcc.h"          //Contains macros defined by CMake
#include "popc_intface.h"
#include "config.h"
#include "paroc_utils.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

char arch[256];

struct popc_options {
    bool verbose = false;
    bool noclean = false;
    bool nowarning = false;
    bool popcppcompilation = false;
    bool noimplicitpack = false;
    bool asyncallocation = false;
    bool xmp = false;
    bool mpi = false;
    bool usepipe = false;
    bool advanced = false;
    bool kcomputer = false;
    bool nobroker = false;
    bool nointerface = false;
    bool psdyn = false;
    bool cpp11 = false;
};

void Usage() {
    fprintf(stderr,"\nPOP-C++ version %s on %s\n", VERSION, arch);
    fprintf(stderr,"\npopcc [-cxxmain] [-object[=type]] [-cpp=<C++ preprocessor>] [-cxx=<compiler>] ] [-popcld=linker] [-popcdir=<path>] [-popcpp=<POP-C++ parser>] [-verbose] [-noclean] [-no-warning] [-no-implicit-pack] [other C++ options] sources...\n");

    fprintf(stderr,"   -cxxmain:            Use standard C++ main (ignore POP-C++ initialization)\n");
    fprintf(stderr,"   -popc-static:        Link with standard POP-C++ libraries statically\n");
    fprintf(stderr,"   -popc-nolib:         Avoid standard POP-C++ libraries from linking\n");
    fprintf(stderr,"   -parclass-nointerface:   Do not generate POP-C++ interface codes for parallel objects\n");
    fprintf(stderr,"   -parclass-nobroker:      Do not generate POP-C++ broker codes for parallel objects\n");

    fprintf(stderr,"\n");

    fprintf(stderr,"   -object[=type]:          Generate parallel object executable (linking only) (type: std (default) or mpi)\n");
    fprintf(stderr,"   -popcpp:                 POP-C++ parser\n");
    fprintf(stderr,"   -cpp=<preprocessor>:     C++ preprocessor command\n");
    fprintf(stderr,"   -cxx=<compiler>:         C++ compiler\n");
    fprintf(stderr,"   -popcld=<linker>:        C++ linker (default: same as C++ compiler)\n");
    fprintf(stderr,"   -popcdir:                POP-C++ installed directory\n");
    fprintf(stderr,"   -noclean:                Do not clean temporary files\n");
    fprintf(stderr,"   -no-warning:             Do not print warning on stdout\n");
    fprintf(stderr,"   -no-implicit-pack:       Do not pack parclass implicitly if no @pack directive is present\n");
    fprintf(stderr,"   -cpp11:                  Compile in c++11 mode\n");

    fprintf(stderr,"   -async-allocation:       Use asynchronous mechanism to allocate a parallel object\n");
    fprintf(stderr,"   -verbose:                Print out additional information\n");
    fprintf(stderr,"   -nopipe:                 Do not use pipe during compilation phases ( create _paroc2_ files )\n");
    fprintf(stderr,"   -version:            Display the installed version of POP-C++\n");

    fprintf(stderr,"\n");

    fprintf(stderr,"   -mpi:            Enable MPI compilation in collective parallel class\n");
    fprintf(stderr,"   -xmp:            Enable XMP compilation in collective parallel class\n");
    fprintf(stderr,"   -advanced:       Link with the POP-C++ Advanced Library\n");
    fprintf(stderr,"   -pseudo-dynamic:       Use the pseudo-dynamic communication model of POP-C++\n");

    fprintf(stderr,"\n");

    fprintf(stderr,"Environment variables change the default values used by POP-C++:\n");
    fprintf(stderr,"   POPC_LOCATION:  Directory where POP-C++ has been installed\n");
    fprintf(stderr,"   POPC_CXX:       The C++ compiler used to generate object code\n");
    fprintf(stderr,"   POPC_CPP:       The C++ preprocessor\n");
    fprintf(stderr,"   POPC_LD:        The C++ linker used to generate binary code\n");
    fprintf(stderr,"   POPC_PP:        The POP-C++  parser\n");

    exit(1);
}

/**
 * Print the POP-C++ version information on stderr
 */
void DisplayVersion() {
    fprintf(stderr,"POP-C++ version %s on %s\n", VERSION, arch);
}

/**
 * Prepare POP-C++ source file. Generate _popc1_ files.
 */
void prepare_source(const char *src, const char *dest, const popc_options& options) {
    FILE *sf = fopen(src, "r+t");
    if(!sf) {
        perror(src);
        exit(1);
    }
    FILE *df = fopen(dest, "w+t");
    if(!df) {
        perror("Temporary file:");
        exit(1);
    }

    if(options.advanced) {
        fprintf(df, "\n# 1 \"<paroc system>\"\n#define _POPC_\n#include \"paroc_sys.h\"\n#include \"popc_advanced_header.h\"\n@parocfile \"%s\"\n# 1 \"%s\"\n", src, src);
    } else {
        fprintf(df, "\n# 1 \"<paroc system>\"\n#define _POPC_\n#include \"paroc_sys.h\"\n@parocfile \"%s\"\n# 1 \"%s\"\n", src, src);
    }

    char buf[1024];
    buf[1023] = 0;
    while(fgets(buf, 1023, sf)) {
        if(fputs(buf,df) == EOF) {
            perror("Writing temporary file");
            exit(1);
        }
    }
    fputs("\n", df);
    fclose(df);
    fclose(sf);
}

/**
 * Run the C++ preprocessor
 */
std::size_t cxx_preprocessor(const char *preprocessor, const char** pre_opt, const char* tmpfile1, const char* tmpfile2, const char** cmd, const popc_options& options){
    std::size_t count = 0;
    cmd[count++] = preprocessor;

    if(options.cpp11){
        cmd[count++] = "-std=cpp11";
    }

    for(auto t2 = pre_opt; *t2; t2++) {
        cmd[count++] = *t2;
    }
    cmd[count++] = tmpfile1;

    // Preprocessor output
    if(!options.usepipe) {
        cmd[count++] = "-o";
        cmd[count++] = tmpfile2;

        if(options.verbose) {
            printf("C++ preprocessing: ");
            for(std::size_t i = 0; i < count; i++) {
                printf("%s ", cmd[i]);
            }
            printf("\n");
        }

        RunCmd(count, cmd);
    }

    return count;
}

int popc_preprocessor(const char* popcpp, const char* tmpfile1, const char* tmpfile2, const char* tmpfile3, const char** cmd, std::size_t count, const popc_options& options){
    // Run POP-C++ preprocessor (popcpp)
    const char *popc_preprocessor_command[1000];
    std::size_t countparoc=0;

    popc_preprocessor_command[countparoc++] = popcpp;
    popc_preprocessor_command[countparoc++] = tmpfile2;
    popc_preprocessor_command[countparoc++] = tmpfile3;

    if(options.nointerface) {
        popc_preprocessor_command[countparoc++] = "-parclass-nointerface";
    }
    if(options.nobroker) {
        popc_preprocessor_command[countparoc++] = "-parclass-nobroker";
    }
    if(options.nowarning) {
        popc_preprocessor_command[countparoc++] = "-no-warning";
    }
    if(options.popcppcompilation) {
        popc_preprocessor_command[countparoc++] = "-popcpp-compilation";
    }
    if(options.asyncallocation) {
        popc_preprocessor_command[countparoc++] = "-async-allocation";
    }
    if(options.noimplicitpack) {
        popc_preprocessor_command[countparoc++] = "-no-implicit-pack";
    }
    if(options.xmp) {
        popc_preprocessor_command[countparoc++] = "-xmp";
    }
    if(options.advanced) {
        popc_preprocessor_command[countparoc++] = "-advanced";
    }

    int ret = 0;
    if(!options.usepipe) {
        if(options.verbose) {
            printf("POP-C++ parsing: ");
            for(std::size_t i = 0; i < countparoc; i++) {
                printf("%s ", popc_preprocessor_command[i]);
            }
            printf("\n");
        }
        ret = RunCmd(countparoc, popc_preprocessor_command);
        if(!options.noclean) {
            popc_unlink(tmpfile2);
        }
    } else {
        if(options.verbose) {
            printf("C++ preprocessing: ");
            for(std::size_t i = 0; i < count; i++) {
                printf("%s ", cmd[i]);
            }
            printf("\n");
            printf("POP-C++ parsing (from pipe %s): ", tmpfile1);
            for(std::size_t i = 0; i < countparoc; i++) {
                printf("%s ", popc_preprocessor_command[i]);
            }
            printf("\n");
        }
        ret = RunPipe(count, cmd, countparoc, popc_preprocessor_command);
    }

    return ret;
}

// Run C++ compiler
int cxx_compiler(char* cpp, const char** cpp_opt, const char* source, char** dest, const char* tmpfile3, char* str, bool paroc, int ret, const popc_options& options){
    static char output[1024];

    const char *cmd[1000];
    std::size_t count = 0;

    cmd[count++] = cpp;

    if(options.cpp11){
        cmd[count++] = "-std=cpp11";
    }

    for(auto t2 = cpp_opt; *t2; t2++) {
        cmd[count++] = *t2;
    }

    cmd[count++] = "-c";
    cmd[count++] = (paroc) ? tmpfile3 : source;
    cmd[count++] = "-o";

    if(!*dest) {
        strcpy(output, source);
        str = strrchr(output, '.');
        if(strcmp(str, ".ph") == 0) {
            strcpy(str, ".stub.o");
        } else {
            strcpy(str, ".o");
        }
        *dest = output;
        cmd[count++] = output;
    } else {
        cmd[count++] = *dest;
    }

    if(!ret) {
        if(options.verbose) {
            printf("C++ compilation: ");
            for(std::size_t i = 0; i < count; i++) {
                printf("%s ", cmd[i]);
            }
            printf("\n");
        }

        ret = RunCmd(count, cmd);
    }

    return ret;
}

char *Compile(const char *preprocessor, char *popcpp, char *cpp, const char** pre_opt, const char** cpp_opt, char *source, char *dest, const popc_options& options) {
    const char *cmd[1000];

    char sdir[1024];
    char tmpfile1[1024];
    char tmpfile2[1024];
    char tmpfile3[1024];

    bool paroc = false;
    int ret = 0;

    auto fname = strrchr(source, '/');
    if(fname) {
        fname++;
        int n = fname - source;
        strncpy(sdir, source, n);
        sdir[n+1] = 0;
    } else {
        fname = source;
        *sdir=0;
    }

    // Get the extension
    auto str = strrchr(fname, '.');
    if(!str) {
        return nullptr;
    }

    // Check the extension of the header file. .ph or .pc are accepted as POP-C++ header file extensions.
    bool paroc_extension = (strcmp(str, ".ph") == 0 || strcmp(str,".pc") == 0);
    if(options.verbose) {
        printf("-- Compilation of source file %s\n", fname);
    }

    if(paroc_extension || strcmp(str, ".cc") == 0 ||  strcmp(str, ".C") == 0 || strcmp(str, ".cpp") == 0) {
        //TODO Generation of the various file names should be reviewed
        sprintf(tmpfile1, "%s_popc1_%s", sdir, fname);

        if(options.usepipe) {
            sprintf(tmpfile2, "-");
        } else {
            sprintf(tmpfile2, "%s_popc2_%s", sdir, fname);
        }
        sprintf(tmpfile3, "%s_popc3_%s", sdir, fname);
        if(paroc_extension) {
            strcat(tmpfile1 ,".cc");
            strcat(tmpfile2 ,".cc");
            strcat(tmpfile3 ,".cc");
        }

        // Prepare the source and generate _popc1_ files
        prepare_source(source, tmpfile1, options);

        //Run the C++ preprocessor
        auto count = cxx_preprocessor(preprocessor, pre_opt, tmpfile1, tmpfile2, cmd, options);

        //Run the POPC++ preprocessor
        ret = popc_preprocessor(popcpp, tmpfile1, tmpfile2, tmpfile3, cmd, count, options);

        paroc = true;
    }

    if(!options.noclean) {
        popc_unlink(tmpfile1);
    }

    ret = cxx_compiler(cpp, cpp_opt, source, &dest, tmpfile3, str, paroc, ret, options);

    if(!options.noclean && paroc) {
        popc_unlink(tmpfile3);
    }

    if(ret != 0) {
        popc__exit(ret);
    }

    return dest;
}

bool FindLib(const char *libpaths[1024], int count, const char *libname, char libfile[1024]) {
    for(int i = 0; i < count; i++) {
        sprintf(libfile, "%s/lib%s.a", libpaths[i], libname);
        if(popc_access(libfile, F_OK) == 0) {
            return true;
        }
    }
    return false;
}

//This function parses all the arguments
//and dispatch them to all the programs that forms the toolchain

int main(int argc, char *argv[]) {
    popc_options options;

#ifndef HOST_CPU
    sprintf(arch, "%s", "unknown");
#else
    sprintf(arch, "%s-%s", HOST_CPU, HOST_KERNEL);
#endif

    // If no arguments specified prints usage
    if(argc <= 1) {
        Usage();
    }

    // POP-C++ preprocessor command
    char popcpp[1024];

#ifndef POPC_CXX
    char parocxx[1024] = POPC_CXX_COMPILER;
    char parocld[1024] = POPC_CXX_COMPILER;
#else
    char parocxx[1024] = POPC_CXX;
    char parocld[1024] = POPC_CXX;
#endif

    // For MPI and XMP support
    char mpicxx[1024] = POPC_MPI_CXX_COMPILER;
    char mpicpp[1024] = POPC_MPI_CXX_COMPILER " -E";

#ifndef POPC_CPP
    char cpp[1024] = POPC_CXX_COMPILER " -E";
#else
    char cpp[1024] = POPC_CPP;
#endif

    // POP-C++ installation directory
    char parocdir[1024] = POPC_INSTALL_PREFIX;



    char buf[256];

    char outputfile[1024] = "";

    bool useparocmain = true;
    bool compile = false;
    bool object = false;
    bool staticlib = false;

    char objmain[256] = "std";

    // Display version if option "-version" is found on the command
    if(paroc_utils::check_remove(&argc, &argv, "-version")) {
        DisplayVersion();
        return 0;
    }

    // Check for POP-C++ options
    options.noclean = paroc_utils::check_remove(&argc, &argv, "-noclean");
    options.nowarning = paroc_utils::check_remove(&argc, &argv, "-no-warning");
    options.popcppcompilation = paroc_utils::check_remove(&argc, &argv, "-popcpp-compilation");
    options.noimplicitpack = paroc_utils::check_remove(&argc, &argv, "-no-implicit-pack");
    options.asyncallocation = paroc_utils::check_remove(&argc, &argv, "-async-allocation");
    options.nobroker = paroc_utils::check_remove(&argc, &argv, "-parclass-nobroker");
    options.nointerface = paroc_utils::check_remove(&argc, &argv, "-parclass-nointerface");
    options.kcomputer = paroc_utils::check_remove(&argc, &argv, "-kcomputer");
    options.xmp = paroc_utils::check_remove(&argc, &argv, "-xmp");
    options.mpi = paroc_utils::check_remove(&argc, &argv, "-mpi");
    options.advanced = paroc_utils::check_remove(&argc, &argv, "-advanced");
    options.psdyn = paroc_utils::check_remove(&argc, &argv, "-pseudo-dynamic");
    options.cpp11 = paroc_utils::check_remove(&argc, &argv, "-cpp11");

#ifndef __WIN32__
    options.usepipe = !paroc_utils::check_remove(&argc, &argv, "-nopipe");
#endif

    //Compute options depending on other options

    if(options.psdyn){
        options.mpi = true;
    }

    if((options.xmp || options.mpi) && !options.psdyn) {
        options.advanced = true;
    }

    // Check for POP-C++ installation directory
    char *tmp;
    if((tmp = paroc_utils::checkremove(&argc, &argv, "-popcdir="))) {
        strcpy(parocdir, tmp);
    } else if((tmp = getenv("POPC_LOCATION"))) {
        strcpy(parocdir, tmp);
    }

    //Detect the POPC preprocessor

    if((tmp = paroc_utils::checkremove(&argc, &argv, "-popcpp="))) {
        strcpy(popcpp, tmp);
    } else if((tmp = getenv("POPC_PP"))) {
        strcpy(popcpp, tmp);
    } else {
#ifdef __WIN32__
        sprintf(popcpp, "%s/bin/popcpp.exe", parocdir);
#else
        sprintf(popcpp, "%s/bin/popcpp", parocdir);
#endif
    }

    // Check execution rights the POP-C++ preprocessor
#ifndef __WIN32__
    if(popc_access(popcpp, X_OK) != 0) {
#else
    if(popc_access(popcpp, R_OK) != 0) {
#endif
        perror(popcpp);
        Usage();
    }

    // Detect C++ preprocessor
    if((tmp = paroc_utils::checkremove(&argc, &argv, "-cpp="))) {
        strcpy(cpp, tmp);
    } else if(options.xmp || options.mpi) {
        strcpy(cpp, mpicpp);
    } else if((tmp = getenv("POPC_CPP"))) {
        strcpy(cpp, tmp);
    }

    // Detect C++ compiler
    if((tmp = paroc_utils::checkremove(&argc, &argv, "-cxx="))) {
        strcpy(parocxx, tmp);
    } else if(options.xmp || options.mpi) {
        strcpy(parocxx, mpicxx);
    } else if((tmp = getenv("POPC_CXX"))) {
        strcpy(parocxx, tmp);
    }

    // Detect C++ linker
    if((tmp = paroc_utils::checkremove(&argc, &argv, "-popcld="))) {
        strcpy(parocld,tmp);
    } else if(options.xmp || options.mpi) {
        strcpy(parocld, mpicxx);
    } else if((tmp = getenv("POPC_LD"))) {
        strcpy(parocld, tmp);
    } else {
        strcpy(parocld, parocxx);
    }

    const char *cpp_opts[1000];
    int cpp_count = 0;

    const char *cxx_opts[1000];
    int cxx_count = 0;

    auto tok = strtok(cpp, " \t");
    while((tok = strtok(nullptr, " \t"))) {
        cpp_opts[cpp_count++] = tok;
    }

    tok = strtok(parocxx, " \t");
    while((tok = strtok(nullptr, " \t"))) {
        cxx_opts[cxx_count++] = tok;
    }

    const char *link_cmd[1024];
    int link_count = 0;

    link_cmd[link_count++] = parocld;
    tok = strtok(parocld, " \t");
    while((tok = strtok(nullptr," \t"))) {
        link_cmd[link_count++] = tok;
    }

    // Add the library path for compilation
    if(options.psdyn) {
        sprintf(buf, "-L%s/lib/pseudodynamic", parocdir);
    } else {
        sprintf(buf, "-L%s/lib/dynamic", parocdir);
    }

    link_cmd[link_count++] = popc_strdup(buf);

    const char *libpaths[1024];
    int libpaths_count = 0;

    // Add POP-C++ library path to the lib path
    char paroclibdir[1024];
    sprintf(paroclibdir, "%s/lib", parocdir);
    libpaths[libpaths_count++] = paroclibdir;


#ifdef POPC_EXTRA_LINK
    link_cmd[link_count++] = popc_strdup(POPC_EXTRA_LINK);
#endif

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0) {
            argv[i][0] = 0;
            compile = true;
        } else if(strcmp(argv[i], "-o") == 0) {
            if(i == argc - 1) {
                fprintf(stderr, "POP-C++ Error: option -o is used but no output file is specified\n");
                exit(1);
            }
            if(*outputfile != 0) {
                fprintf(stderr, "POP-C++ Error: multiple output files specified\n");
                exit(1);
            }
            argv[i][0] = 0;
            strcpy(outputfile, argv[i+1]);
            i++;
            argv[i][0] = 0;
        } else if(strcmp(argv[i], "-object") == 0) {
            argv[i][0]=0;
            object=true;
        } else if(strncmp(argv[i], "-object=", 8) == 0) {
            if(argv[i][8] != 0) {
                strcpy(objmain, argv[i] + 8);
            }
            argv[i][0] = 0;
            object = true;
        } else if(strcmp(argv[i], "-cxxmain") == 0) {
            argv[i][0]=0;
            useparocmain=false;
        } else if(strcmp(argv[i], "-verbose") == 0) {
            argv[i][0] = 0;
            options.verbose = true;
        } else if(strncmp(argv[i], "-I" , 2) == 0) {
            cpp_opts[cpp_count++]=argv[i];
        } else if(strcmp(argv[i], "-shared") == 0) {
            staticlib = false;
        } else if(strncmp(argv[i], "-L", 2) == 0) {
            libpaths[libpaths_count++] = argv[i] + 2;
        } else if(strncmp(argv[i], "-D", 2) == 0 || strncmp(argv[i], "-U", 2) == 0) {
            cpp_opts[cpp_count++] = argv[i];
            cxx_opts[cxx_count++] = argv[i];
        } else if(argv[i][0] == '-' && argv[i][1] != 'L' && argv[i][1] != 'l') {
            cxx_opts[cxx_count++] = argv[i];
        }
    }

    libpaths[libpaths_count++] = "/usr/lib";
    libpaths[libpaths_count++] = "/lib";

    sprintf(buf, "-DPOPC_ARCH=\"%s\"", arch);
    cpp_opts[cpp_count++] = popc_strdup(buf);

    if(useparocmain) {
        cpp_opts[cpp_count++] = popc_strdup("-Dmain=parocmain");
    }

    if(options.psdyn) {
        sprintf(buf, "-I%s/include/pseudodynamic", parocdir);
    } else {
        sprintf(buf, "-I%s/include/dynamic", parocdir);
    }

    cpp_opts[cpp_count++] = popc_strdup(buf);

    if(*outputfile != 0) {
        link_cmd[link_count++] = popc_strdup("-o");
        link_cmd[link_count++] = outputfile;
    }

    cxx_opts[cxx_count++] = popc_strdup("-Dparclass=class");

    cpp_opts[cpp_count] = nullptr;
    cxx_opts[cxx_count] = nullptr;

    if(options.verbose) {
        printf("POP-C++ Compiler - version %s on %s\n", VERSION, arch);
    }
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] != 0) {
            if(argv[i][0] != '-') {
                char *str = strrchr(argv[i], '.');
                if(str) {
                    bool paroc_extension = (strcmp(str, ".ph") == 0 || strcmp(str, ".pc") == 0);
                    if(paroc_extension || strcmp(str, ".cc") == 0 ||  strcmp(str, ".C") == 0 || strcmp(str, ".cpp")==0) {
                        if(options.verbose) {
                            printf("\n");
                        }

                        auto outf = Compile(cpp, popcpp, parocxx, cpp_opts, cxx_opts, argv[i], ((*outputfile==0 || (!compile)) ? nullptr :  outputfile), options);
                        link_cmd[link_count++] = !outf ? argv[i] : popc_strdup(outf);
                        continue;
                    }
                }
            }

            if(staticlib && strncmp(argv[i], "-l", 2) == 0) {
                char libfile[1024];
                if(FindLib(libpaths, libpaths_count, argv[i] + 2, libfile)) {
                    link_cmd[link_count++] = popc_strdup(libfile);
                    continue;
                }

            }
            link_cmd[link_count++] = argv[i];
        }
    }

    bool paroc_static = paroc_utils::checkremove(&argc, &argv, "-popc-static");
    bool paroc_nolib = paroc_utils::checkremove(&argc, &argv, "-popc-nolib");

    if(!compile) {
        if(useparocmain) {
            if(options.psdyn && object) {
                sprintf(buf, "%s/lib/pseudodynamic/popc_objmain.%s.o", parocdir, "psdyn");
            } else if(options.psdyn) {
                sprintf(buf, "%s/lib/pseudodynamic/paroc_infmain.%s.o", parocdir, "psdyn");
            } else if((options.xmp || options.mpi) && object) {
                sprintf(buf, "%s/lib/dynamic/popc_objmain.%s.o", parocdir, "xmp");
            } else if(object) {
                sprintf(buf, "%s/lib/dynamic/paroc_objmain.%s.o", parocdir, objmain);
            } else {
                sprintf(buf, "%s/lib/dynamic/paroc_infmain.std.o", parocdir);
            }
            link_cmd[link_count++] = popc_strdup(buf);
        }
        if(!paroc_nolib) {
            if(options.psdyn && (paroc_static || staticlib)) {
                sprintf(buf, "%s/lib/pseudodynamic/libpopc_common_psdyn.a", parocdir);
            } else if(options.psdyn) {
                strcpy(buf, "-lpopc_common_psdyn");
            } else if(paroc_static || staticlib) {
                sprintf(buf, "%s/lib/dynamic/libpopc_common.a", parocdir);
            } else {
#ifndef __WIN32__
                strcpy(buf, "-lpopc_common");
#else
                strcpy(buf, "-lpopc_common -lws2_32 -lxdr");
#endif
            }
            link_cmd[link_count++] = popc_strdup(buf);

            char tmplibfile[1024];

#ifdef HAVE_LIBNSL
            link_cmd[link_count++] = (staticlib && FindLib(libpaths, libpaths_count, "nsl", tmplibfile)) ? popc_strdup(tmplibfile) : popc_strdup("-lnsl");
#endif

#ifdef HAVE_LIBSOCKET
            link_cmd[link_count++] = (staticlib && FindLib(libpaths, libpaths_count, "socket", tmplibfile)) ? popc_strdup(tmplibfile) : popc_strdup("-lsocket");
#endif

#ifndef HAVE_LIBPTHREAD
            link_cmd[link_count++] = (staticlib && FindLib(libpaths, libpaths_count, "pthread", tmplibfile)) ? popc_strdup(tmplibfile) : popc_strdup("-lpthreadGC2");
#else
            link_cmd[link_count++] = (staticlib && FindLib(libpaths, libpaths_count, "pthread", tmplibfile)) ? popc_strdup(tmplibfile) : popc_strdup("-lpthread");
#endif

#ifdef HAVE_LIBDL
            link_cmd[link_count++] = (staticlib && FindLib(libpaths, libpaths_count, "dl", tmplibfile)) ? popc_strdup(tmplibfile) : popc_strdup("-ldl");
#endif

            // Link with advanced POP-C++ library
            if((options.xmp || options.advanced || options.mpi) && !options.psdyn) {
                if(paroc_static || staticlib) {
                    sprintf(buf, "%s/lib/dynamic/libpopc_advanced.a", parocdir);
                } else {
                    strcpy(buf, "-lpopc_advanced");
                }
                link_cmd[link_count++] = popc_strdup(buf);
            }
        }
        link_cmd[link_count] = nullptr;
        if(options.verbose) {
            printf("\nC++ linking: ");
            for(int i = 0; i < link_count; i++) {
                printf("%s ", link_cmd[i]);
            }
            printf("\n");
        }
        RunCmd(link_count, link_cmd);
    }

    if(options.verbose) {
        printf("POP-C++ compilation done ...\n\n\n");
    }
    return 0;
}
