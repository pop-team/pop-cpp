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

#ifndef POPC_PARSER_POPCC_IN_H
#define POPC_PARSER_POPCC_IN_H

#define POPC_CXX_COMPILER "/usr/bin/clang++"
#define POPC_MPI_CXX_COMPILER ""
#define POPC_INSTALL_PREFIX  "/usr/local"

#endif //POPC_PARSER_POPCC_IN_H
