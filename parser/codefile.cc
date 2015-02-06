/**
 * File : codefile.cc
 * Author : Tuan Anh Nguyen
 * Description : POP-C++ parser/compiler CodeFile object
 * Creation date : -
 *
 * Modifications :
 * Authors      Date                Comment
 * clementval   Jul/Aug 2012    Add information for compilation process (core compilation & asynchronous parallel object allocation)
 */

#include "popc_intface.h"

#include "parser.h"
#include "paroc_utils.h"

CodeFile::CodeFile(char *fname) {
    isCoreCompilation = false;              // Core compilation is disable by default.
    isAsyncAllocationDisable = false;   // Asynchronous allocation is enable by default.
    filename = (fname == NULL) ? NULL : popc_strdup(fname);
    codes.SetGrowby(1024);
    outfile=NULL;
    DataType *std;
    for(int i=0; i<MAXSTDTYPES; i++) {
        std=new DataType(DataType::stdType[i]);
        AddDataType(std);
    }

}

CodeFile::~CodeFile() {
    if(filename != NULL) {
        free(filename);
    }

    if(outfile != NULL) {
        free(outfile);
    }

    EmptyCodeData();
}

void CodeFile::AddCodeData(CodeData *code) {
    codes.InsertAt(-1,code);
    if(code->Type()==TYPE_CLASS) {
        classlist.InsertAt(-1,(Class *)code);
    }
}

void CodeFile::EmptyCodeData() {
    int n=codes.size();
    for(int i=0; i<n; i++) if(codes[i]!=NULL) {
            delete codes[i];
        }
    codes.SetSize(0);
}

void CodeFile::GenerateCode(CArrayChar &output, bool client, bool broker) {
    int m = codes.size();
    for(int j = 0; j < m; j++) {
        if(broker || codes[j]->Type() != TYPE_PACKOBJECT) {
            codes[j]->GenerateCode(output);
        }
    }

    for(int j = 0; j < m; j++) {
        if(codes[j]->Type() == TYPE_CLASS) {
            Class &cl = *(Class *)(codes[j]);
            char *clfname = cl.GetFileInfo();
            if(filename == NULL || clfname == NULL || SameFile(clfname, filename)) {
                if(client) {
                    cl.GenerateClient(output);
                }
                if(broker) {
                    cl.GenerateBroker(output);
                }
            }
        }
    }
}

CArrayCodeData *CodeFile::GetCodes() {
    return &codes;
}
bool CodeFile::HasClass() {
    return (classlist.size()>0);
}

char *CodeFile::GetFileName() {
    return filename;
}

void CodeFile::SetFileName(char *name) {
    if(filename != NULL) {
        free(filename);
    }
    filename = (name == NULL) ? NULL : popc_strdup(name);
}

char *CodeFile::GetOutputName() {
    return outfile;
}

void CodeFile::SetOutputName(char *name) {
    if(outfile != NULL) {
        free(outfile);
    }
    outfile = (name == NULL) ? NULL : popc_strdup(name);
}

Class *CodeFile::FindClass(char *clname) {
    char tmp[256];
    while(isspace(*clname)) {
        clname++;
    }
    strcpy(tmp,clname);
    char *tmp1=tmp+strlen(tmp)-1;
    while(isspace(*tmp1) && tmp1>tmp) {
        *tmp1=0;
        tmp1--;
    }

    int n=classlist.size();
    for(int i=0; i<n; i++) if(paroc_utils::isEqual(classlist[i]->GetName(),tmp)) {
            return classlist[i];
        }
    return 0;
}

void CodeFile::FindAllClass(CArrayClass &list) {
    list=classlist;
}

void CodeFile::FindAllBaseClass(Class &t, CArrayClass & bases, bool virtualBaseOnly) {
    int index=bases.size();
    CArrayClass tmp;
    if(virtualBaseOnly) {
        tmp=bases;
    }

    CArrayClass &allbases=(virtualBaseOnly)? tmp : bases;

    Class *cl=&t;
    int sz1, actual_n1=0;

    index=0;
    while(1) {
        int sz=allbases.size();
        int n=cl->baseClass.size();
        allbases.SetSize(sz+n);
        int actual_n=sz;

        if(virtualBaseOnly) {
            sz1=bases.size();
            actual_n1=sz1;
            bases.SetSize(sz1+n);
        }

        for(int i=0; i<n; i++) {
            bool existed=false;
            BaseClass &b=*(cl->baseClass[i]);
            for(int j=0; j<sz; j++) if(allbases[j]==b.base) {
                    existed=true;
                    break;
                }
            if(!existed) {
                allbases[actual_n]=b.base;
                actual_n++;

                if(virtualBaseOnly && b.baseVirtual) {
                    bases[actual_n1]=b.base;
                    actual_n1++;
                }
            }
        }
        allbases.SetSize(actual_n);
        if(virtualBaseOnly) {
            bases.SetSize(actual_n1);
        }
        if(index<actual_n) {
            cl=allbases[index];
            index++;
        } else {
            break;
        }
    }
}

DataType *CodeFile::FindDataType(const char *name) {
    for(int i = 0; i < datatypes.size(); ++i){
        if(strcmp(name, datatypes[i]->GetName())==0) {
            return datatypes[i];
        }
    }

    return nullptr;
}

void CodeFile::AddDataType(DataType *type) {
    type->SetOwnerFile(this);
    if(type->GetName()==NULL) {
        temptypes.InsertAt(-1,type);
    } else {
        datatypes.InsertAt(-1,type);
    }

}

void CodeFile::RemoveDataType(DataType *type) {
    for(int i = 0; i < datatypes.size(); ++i){
        if(datatypes[i] == type){
            temptypes.RemoveAt(i);
        }
    }
}

bool CodeFile::SameFile(char *file1, char *file2) {
    if(paroc_utils::isEqual(file1,file2)) {
        return true;
    }
    char *fn1=strrchr(file1,'/');
    char *fn2=strrchr(file2,'/');
    char dir1[256], dir2[256];

    if(fn1==NULL && fn2==NULL) {
        return false;
    }
    if(fn1==NULL) {
        fn1=file1;
        popc_getcwd(dir1,255);
    } else {
        char tmp[256];
        int n=fn1-file1;
        strncpy(dir1, file1,n);
        dir1[n]=0;
        fn1++;
        if(*dir1!='/') {
            popc_getcwd(tmp,255);
            popc_chdir(dir1);
            popc_getcwd(dir1,255);
            popc_chdir(tmp);
        }
    }

    if(fn2==NULL) {
        fn2=file2;
        popc_getcwd(dir2,255);
    } else {
        char tmp[256];
        int n=fn2-file2;
        strncpy(dir2, file2,n);
        dir2[n]=0;
        fn2++;
        if(*dir2!='/') {
            popc_getcwd(tmp,255);
            popc_chdir(dir2);
            popc_getcwd(dir2,255);
            popc_chdir(tmp);
        }
    }

    return (paroc_utils::isEqual(fn1,fn2) && paroc_utils::isEqual(dir1,dir2));

}

/**
 * Set the current code file as compilation of the POP-C++ core.
 * @return void
 */
void CodeFile::SetAsCoreCompilation() {
    isCoreCompilation = true;
}

/**
 * Check if the current compilation is the POP-C++ core compilation
 * @return TRUE if it is the core compilation. FALSE otherwise.
 */
bool CodeFile::IsCoreCompilation() {
    return isCoreCompilation;
}

/**
 * Disable the asynchronous parallel object allocation mechanism.
 * @return void
 */
void CodeFile::DisableAsyncAllocation() {
    isAsyncAllocationDisable = true;
}

/**
 * Check if asynchronous parallel object allocation is disable
 * @return TRUE if asynchronous allocation is disable. FALSE otherwise.
 */
bool CodeFile::IsAsyncAllocationDisable() {
    return isAsyncAllocationDisable;
}
