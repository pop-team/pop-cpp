#include "pop_intface.h"

//#include <string.h>
//#include <stdio.h>
#include "type.h"

TypeArray::TypeArray(char* name, char* cardstr, DataType* base) : DataType(name) {
    cardinal = popc_strdup(cardstr);
    typebase = base;
}

TypeArray::~TypeArray() {
    if (cardinal != nullptr) {
        free(cardinal);
    }
}

void TypeArray::GetCardinalSize(char* size) {
    char* tmpindex = cardinal;
    char* tmpindex1 = size;
    int openbracket = 0;
    int ignore = 0;
    bool firstdim = true;

    while (*tmpindex != 0) {
        *tmpindex1 = *tmpindex;

        if (ignore && *tmpindex1 == '\\') {
            tmpindex1++;
            tmpindex++;
            *tmpindex1 = *tmpindex;
        } else if (*tmpindex1 == '"') {
            ignore = !ignore;
        } else if (!ignore) {
            if (*tmpindex1 == '[') {
                if (openbracket == 0) {
                    if (!firstdim) {
                        *tmpindex1 = '*';
                        tmpindex1++;
                    } else {
                        firstdim = false;
                    }
                    *tmpindex1 = '(';
                }
                openbracket++;
            } else if (*tmpindex1 == ']') {
                openbracket--;
                if (openbracket == 0) {
                    *tmpindex1 = ')';
                }
            }
        }

        tmpindex1++;
        tmpindex++;
    }
    *tmpindex1 = 0;
}

int TypeArray::CanMarshal() {
    if (IsMarked()) {
        Mark(false);
        return 0;
    }
    Mark(true);
    int ret = typebase->CanMarshal();
    Mark(false);
    return ret;
}

void TypeArray::Marshal(char* varname, char* bufname, char* sizehelper, std::string& output) {
    char tmpvar[1024];
    char size[1024];
    char* tmpsize;

    if (sizehelper == nullptr) {
        GetCardinalSize(size);
        tmpsize = size;
    } else {
        tmpsize = sizehelper;
    }

    if (typebase->IsStandardType() || tmpsize == nullptr || strcmp(tmpsize, "1") == 0) {
        snprintf(tmpvar, sizeof(tmpvar), "(*((%s *)%s))", typebase->GetName(), varname);
        typebase->Marshal(tmpvar, bufname, tmpsize, output);
    } else {
        char tmpcode[1024];

        snprintf(tmpcode, sizeof(tmpcode), "{ int _paroc_count%d=%s;\n", counter, tmpsize);
        output += tmpcode;

        char paramname[256];
        if (!FindVarName(varname, paramname)) {
            strcpy(paramname, "unknown");
        }
        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",_paroc_count%d);\n", bufname, paramname, typebase->GetName(), counter);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "for (%s *_pop_elem%d =(%s *)(%s); _paroc_count%d>0; _paroc_count%d--, _pop_elem%d++)\n{\n",
                typebase->GetName(), counter, typebase->GetName(), varname, counter, counter, counter);
        output += tmpcode;

        snprintf(tmpvar, sizeof(tmpvar), "(*_pop_elem%d)", counter);
        typebase->Marshal(tmpvar, bufname, nullptr, output);
        strcpy(tmpcode, "}\n}\n");
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Pop();\n", bufname);
        output += tmpcode;

        counter++;
    }
}

void TypeArray::DeMarshal(char* varname, char* bufname, char* sizehelper, std::string& output) {
    char tmpvar[1024];
    char size[1024];
    char* tmpsize;

    if (sizehelper == nullptr) {
        GetCardinalSize(size);
        tmpsize = size;
    } else {
        tmpsize = sizehelper;
    }

    if (typebase->IsStandardType() || tmpsize == nullptr || strcmp(tmpsize, "1") == 0) {
        snprintf(tmpvar, sizeof(tmpvar), "(*((%s *)%s))", typebase->GetName(), varname);
        typebase->DeMarshal(tmpvar, bufname, tmpsize, output);
    } else {
        char tmpcode[1024];

        snprintf(tmpcode, sizeof(tmpcode), "{ int _paroc_count%d=%s;\n", counter, tmpsize);
        output += tmpcode;

        char paramname[256];
        if (!FindVarName(varname, paramname)) {
            strcpy(paramname, "unknown");
        }
        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",_paroc_count%d);\n", bufname, paramname, typebase->GetName(), counter);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "for (%s *_pop_elem%d =(%s *)(%s); _paroc_count%d>0; _paroc_count%d--, _pop_elem%d++)\n{\n",
                typebase->GetName(), counter, typebase->GetName(), varname, counter, counter, counter);
        output += tmpcode;

        snprintf(tmpvar, sizeof(tmpvar), "(*_pop_elem%d)", counter);
        typebase->DeMarshal(tmpvar, bufname, nullptr, output);
        strcpy(tmpcode, "}\n}\n");
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Pop();\n", bufname);
        output += tmpcode;

        counter++;
    }
}

bool TypeArray::GetDeclaration(const char* varname, char* output) {
    if (DataType::GetDeclaration(varname, output)) {
        return true;
    }

    if (typebase->GetDeclaration(varname, output)) {
        strcat(output, cardinal);
        return true;
    }

    return false;
}

bool TypeArray::GetCastType(char* output) {
    char* str = cardinal;
    while (*str != 0 && *str != '[') {
        str++;
    }

    if (*str == '[') {
        int count = 0;
        do {
            if (*str == '[') {
                count++;
            } else if (*str == ']') {
                count--;
            }
            str++;
        } while (count > 0 && *str != 0);
    }

    if (!typebase->GetCastType(output)) {
        return false;
    }
    strcat(output, "(*)");
    strcat(output, str);
    return true;
}

void TypeArray::GetExpandType(char* output) {
    typebase->GetExpandType(output);
    strcat(output, cardinal);
}

bool TypeArray::IsArray() {
    return true;
}
