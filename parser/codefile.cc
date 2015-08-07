/**
 * File : codefile.cc
 * Author : Tuan Anh Nguyen
 * Description : POP-C++ parser/compiler CodeFile object
 * Creation date : -
 *
 * Modifications :
 * Authors      Date                Comment
 * clementval   Jul/Aug 2012    Add information for compilation process (core compilation & asynchronous parallel object
 *allocation)
 */

#include "pop_intface.h"

#include "parser.h"
#include "pop_utils.h"

CodeFile::CodeFile(const std::string& fname)
    : filename(fname), isCoreCompilation(false), asyncAllocationEnabled(false) {
    for (auto& elem : DataType::stdType) {
        AddDataType(new DataType(elem));
    }
}

CodeFile::~CodeFile() {
    EmptyCodeData();
}

void CodeFile::AddCodeData(CodeData* code) {
    codes.push_back(code);
    if (code->Type() == TYPE_CLASS) {
        classlist.push_back(static_cast<Class*>(code));
    }
}

void CodeFile::EmptyCodeData() {
    for (auto& code : codes) {
        if (code) {
            delete code;
        }
    }
    codes.clear();
}

void CodeFile::GenerateCode(std::string& output, bool client, bool broker) {
    int m = codes.size();
    for (int j = 0; j < m; j++) {
        if (broker || codes[j]->Type() != TYPE_PACKOBJECT) {
            codes[j]->GenerateCode(output);
        }
    }

    for (int j = 0; j < m; j++) {
        if (codes[j]->Type() == TYPE_CLASS) {
            Class& cl = *static_cast<Class*>(codes[j]);
            char* clfname = cl.GetFileInfo();
            if (filename.empty() || clfname == nullptr || SameFile(clfname, filename.c_str())) {
                if (client) {
                    cl.GenerateClient(output);
                }
                if (broker) {
                    cl.GenerateBroker(output);
                }
            }
        }
    }
}

CArrayCodeData* CodeFile::GetCodes() {
    return &codes;
}
bool CodeFile::HasClass() {
    return (classlist.size() > 0);
}

Class* CodeFile::FindClass(char* clname) {
    char tmp[256];
    while (isspace(*clname)) {
        clname++;
    }
    snprintf(tmp, sizeof(tmp), "%s", clname);
    char* tmp1 = tmp + strlen(tmp) - 1;
    while (isspace(*tmp1) && tmp1 > tmp) {
        *tmp1 = 0;
        tmp1--;
    }

    int n = classlist.size();
    for (int i = 0; i < n; i++)
        if (pop_utils::isEqual(classlist[i]->GetName(), tmp)) {
            return classlist[i];
        }
    return nullptr;
}

void CodeFile::FindAllClass(CArrayClass& list) {
    list = classlist;
}

void CodeFile::FindAllBaseClass(Class& t, CArrayClass& bases, bool virtualBaseOnly) {
    int index = bases.size();
    CArrayClass tmp;
    if (virtualBaseOnly) {
        tmp = bases;
    }

    CArrayClass& allbases = (virtualBaseOnly) ? tmp : bases;

    Class* cl = &t;
    int sz1, actual_n1 = 0;

    index = 0;
    while (1) {
        int sz = allbases.size();
        int n = cl->baseClass.size();
        allbases.resize(sz + n);
        int actual_n = sz;

        if (virtualBaseOnly) {
            sz1 = bases.size();
            actual_n1 = sz1;
            bases.resize(sz1 + n);
        }

        for (int i = 0; i < n; i++) {
            bool existed = false;
            BaseClass& b = *(cl->baseClass[i]);
            for (int j = 0; j < sz; j++)
                if (allbases[j] == b.base) {
                    existed = true;
                    break;
                }
            if (!existed) {
                allbases[actual_n] = b.base;
                actual_n++;

                if (virtualBaseOnly && b.baseVirtual) {
                    bases[actual_n1] = b.base;
                    actual_n1++;
                }
            }
        }
        allbases.resize(actual_n);
        if (virtualBaseOnly) {
            bases.resize(actual_n1);
        }
        if (index < actual_n) {
            cl = allbases[index];
            index++;
        } else {
            break;
        }
    }
}

DataType* CodeFile::FindDataType(const char* name) {
    for (auto& datatype : datatypes) {
        if (strcmp(name, datatype->GetName()) == 0) {
            return datatype;
        }
    }

    return nullptr;
}

void CodeFile::AddDataType(DataType* type) {
    type->SetOwnerFile(this);
    if (type->GetName() == nullptr) {
        temptypes.push_back(type);
    } else {
        datatypes.push_back(type);
    }
}

bool CodeFile::SameFile(const char* file1, const char* file2) {
    if (pop_utils::isEqual(file1, file2)) {
        return true;
    }
    const char* fn1 = strrchr(file1, '/');
    const char* fn2 = strrchr(file2, '/');
    char dir1[256], dir2[256];

    if (fn1 == nullptr && fn2 == nullptr) {
        return false;
    }
    if (fn1 == nullptr) {
        fn1 = file1;
        popc_getcwd(dir1, 255);
    } else {
        int n = fn1 - file1;
        strncpy(dir1, file1, n);
        dir1[n] = 0;
        fn1++;
        if (*dir1 != '/') {
            char tmp[256];
            popc_getcwd(tmp, 255);
            popc_chdir(dir1);
            popc_getcwd(dir1, 255);
            popc_chdir(tmp);
        }
    }

    if (fn2 == nullptr) {
        fn2 = file2;
        popc_getcwd(dir2, 255);
    } else {
        int n = fn2 - file2;
        strncpy(dir2, file2, n);
        dir2[n] = 0;
        fn2++;
        if (*dir2 != '/') {
            char tmp[256];
            popc_getcwd(tmp, 255);
            popc_chdir(dir2);
            popc_getcwd(dir2, 255);
            popc_chdir(tmp);
        }
    }

    return (pop_utils::isEqual(fn1, fn2) && pop_utils::isEqual(dir1, dir2));
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
 * Enable the asynchronous parallel object allocation mechanism.
 * @return void
 */
void CodeFile::EnableAsyncAllocation() {
    asyncAllocationEnabled = true;
}

/**
 * Check if asynchronous parallel object allocation is enabled
 * @return true if asynchronous allocation is enabled. false otherwise.
 */
bool CodeFile::IsAsyncAllocationEnabled() {
    return asyncAllocationEnabled;
}
