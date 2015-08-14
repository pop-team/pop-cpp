#include "pop_intface.h"

#include "type.h"

// Pointer of a type....

TypePtr::TypePtr(char* name, int level, DataType* base, std::vector<bool> constPositions) : DataType(name) {
    typebase = base;
    assert(base != nullptr);
    // nptr=(level<=0)? 1: level;
    size = nullptr;

    if (level <= 0) {
        nptr = 1;
        constPos.clear();
        constPos.push_back(false);
    } else {
        nptr = level;
        constPos.assign(constPositions.rbegin(),
                        constPositions.rend());  // Copy, without using copy constructor in reverse order !
    }
}

TypePtr::~TypePtr() {
    if (size != nullptr) {
        free(size);
    }
}

int TypePtr::CanMarshal() {
    if (IsMarked()) {
        Mark(false);
        return 0;
    }
    Mark(true);
    int ret = 0;
    if (nptr == 1 && typebase->CanMarshal()) {
        ret = 2;
    }
    Mark(false);
    return ret;
}

void TypePtr::Marshal(char* varname, char* bufname, char* sizehelper, std::string& output) {
    char tmpvar[1024];
    char* tmpsize = (sizehelper != nullptr) ? sizehelper : size;

    if (typebase->IsStandardType() || tmpsize == nullptr || strcmp(tmpsize, "1") == 0) {
        snprintf(tmpvar, sizeof(tmpvar), "(*(%s))", varname);
        typebase->Marshal(tmpvar, bufname, tmpsize, output);
    } else {
        char tmpcode[1024];

        char paramname[256];
        if (!FindVarName(varname, paramname, sizeof(paramname))) {
            snprintf(paramname, sizeof(paramname), "unknown");
        }
        snprintf(tmpcode, sizeof(tmpcode), "\n%s.Push(\"%s\",\"%s\", %s);\n", bufname, paramname, typebase->GetName(),
                 tmpsize);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "\n{for (int _pop_item=0; _pop_item < %s; _pop_item++) { \n", tmpsize);
        output += tmpcode;
        snprintf(tmpvar, sizeof(tmpvar), "(%s[_pop_item])", varname);
        typebase->Marshal(tmpvar, bufname, nullptr, output);

        snprintf(tmpcode, sizeof(tmpcode), "}\n}\n");
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Pop();\n", bufname);
        output += tmpcode;
    }
}

void TypePtr::DeMarshal(char* varname, char* bufname, char* sizehelper, std::string& output) {
    char tmpvar[1024];
    char* tmpsize = (sizehelper != nullptr) ? sizehelper : size;

    if (typebase->IsStandardType() || tmpsize == nullptr || strcmp(tmpsize, "1") == 0) {
        snprintf(tmpvar, sizeof(tmpvar), "(*(%s))", varname);
        typebase->DeMarshal(tmpvar, bufname, tmpsize, output);
    } else {
        char tmpcode[1024];

        char paramname[256];
        if (!FindVarName(varname, paramname, sizeof(paramname))) {
            snprintf(paramname, sizeof(paramname), "unknown");
        }
        snprintf(tmpcode, sizeof(tmpcode), "\n%s.Push(\"%s\",\"%s\", %s);\n", bufname, paramname, typebase->GetName(),
                 tmpsize);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), " {\nfor (int _pop_item=0; _pop_item < %s; _pop_item++) { \n", tmpsize);
        output += tmpcode;
        snprintf(tmpvar, sizeof(tmpvar), "(%s[_pop_item])", varname);
        typebase->DeMarshal(tmpvar, bufname, nullptr, output);

        snprintf(tmpcode, sizeof(tmpcode), "}\n}\n");
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Pop();\n", bufname);
        output += tmpcode;
    }
}

bool TypePtr::GetDeclaration(const char* varname, char* output) {
    if (name != nullptr) {
        return DataType::GetDeclaration(varname, output);
    }

    if (!typebase->GetDeclaration(nullptr, output)) {
        return false;
    }
    strcat(output, " ");

    for (int i = 0; i < nptr; i++) {
        strcat(output, "*");
        if (i < static_cast<int>(constPos.size())) {
            if (constPos[i]) {
                strcat(output, "const ");
            }
        }
    }
    if (varname != nullptr) {
        strcat(output, varname);
    }
    return true;
}

void TypePtr::GetExpandType(char* output, size_t buffer_length) {
    typebase->GetExpandType(output, buffer_length);
    for (int i = 0; i < nptr; i++) {
        strcat(output, "*");
    }
}

void TypePtr::resize(char* sizestr) {
    if (size != nullptr) {
        free(size);
    }
    size = (sizestr == nullptr) ? nullptr : popc_strdup(sizestr);
}

int TypePtr::IsPointer() {
    return nptr + typebase->IsPointer();
}

DataType* TypePtr::GetBaseType() {
    DataType* t = typebase->GetBaseType();
    if (t != nullptr) {
        return t;
    }
    return typebase;
}
