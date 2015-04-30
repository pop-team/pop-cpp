#include "type.h"
#include <stdio.h>

char TypeTemplate::stlType[MAXSTLTYPES][32] = {"std::vector", "vector", "std::list", "list",
                                               "std::deque",  "deque",  "std::map",  "map"};

#define STL_START_TWO_ELEMENT 7

TypeTemplate::TypeTemplate(char* name) : DataType(name) {
}
TypeTemplate::~TypeTemplate() {
}

void TypeTemplate::AddTemplate(DataType* eltype, bool isRef) {
    elements.push_back(eltype);
    refStatus.push_back(isRef);
}

bool TypeTemplate::GetDeclaration(const char* varname, char* output) {
    if (!DataType::GetDeclaration(nullptr, output)) {
        return false;
    }
    output += strlen(output);
    strcat(output, " < ");
    output += 3;
    int n = elements.size();
    for (int i = 0; i < n; i++) {
        if (!elements[i]->GetDeclaration(nullptr, output)) {
            return false;
        }
        if (refStatus[i]) {
            strcat(output, "&");
        }
        if (i < n - 1) {
            strcat(output, ",");
        }
        output += strlen(output);
    }
    strcat(output, " > ");
    if (varname != nullptr) {
        strcat(output, varname);
    }
    return true;
}

int TypeTemplate::CanMarshal() {
    if (elements.empty()) {
        return false;
    }

    for (auto& elem : stlType) {
        if (strcmp(name, elem) == 0) {
            for (auto& element : elements) {
                if (!element->CanMarshal()) {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

void TypeTemplate::Marshal(char* varname, char* bufname, char* /*sizehelper*/, std::string& output) {
    assert(!elements.empty());

    char tmpcode[10240];
    char iterator[256];
    char value[256];
    char decl[1024];
    snprintf(iterator, sizeof(iterator), "_elem%d", counter++);

    // In case we have a vector template, it is much faster to Pack the memory as one block (since it is contiguous !)
    if ((strcmp(name, "vector") == 0 || strcmp(name, "std::vector") == 0) && elements[0]->IsStandardType()) {
        char paramname[256];

        if (!FindVarName(elements[0]->GetName(), paramname)) {
            strcpy(paramname, "unkown");
        }

        snprintf(tmpcode, sizeof(tmpcode), "int %s_size=%s.size();\n", iterator, varname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"@size\",\"int\",1);\n%s.Pack(&%s_size, 1);\n%s.Pop();\n", bufname,
                 bufname, iterator, bufname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",%s_size);\n", bufname, varname, name, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Pack((%s*)&(%s)[0], %s_size);\n%s.Pop();\n", bufname,
                 elements[0]->GetName(), varname, iterator, bufname);
        output += tmpcode;

    } else if ((strcmp(name, "map") == 0 || strcmp(name, "std::map") == 0)) {
        snprintf(tmpcode, sizeof(tmpcode), "int %s_size=%s.size();\n", iterator, varname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"@size\",\"int\",1);\n%s.Pack(&%s_size,1);\n%s.Pop();\n", bufname,
                 bufname, iterator, bufname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",%s_size);\n", bufname, varname, name, iterator);
        output += tmpcode;

        GetDeclaration(nullptr, decl);
        snprintf(tmpcode, sizeof(tmpcode), "for (%s::const_iterator it_%s=%s.begin();it_%s!=%s.end();it_%s++) {\n",
                 decl, iterator, varname, iterator, varname, iterator);
        output += tmpcode;

        elements[0]->GetDeclaration(nullptr, decl);
        snprintf(value, sizeof(value), "((%s &)(it_%s->first))", decl, iterator);
        elements[0]->Marshal(value, bufname, nullptr, output);

        elements[1]->GetDeclaration(nullptr, decl);
        snprintf(value, sizeof(value), "((%s &)(it_%s->second))", decl, iterator);
        elements[1]->Marshal(value, bufname, nullptr, output);

        snprintf(tmpcode, sizeof(tmpcode), "}\n%s.Pop();\n", bufname);
        output += tmpcode;
    } else {
        elements[0]->GetDeclaration(nullptr, decl);
        snprintf(value, sizeof(value), "((%s &)(*%s))", decl, iterator);

        GetDeclaration(nullptr, decl);

        snprintf(tmpcode, sizeof(tmpcode), "int %s_size=%s.size();\n", iterator, varname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"@size\",\"int\",1);\n%s.Pack(&%s_size,1);\n%s.Pop();\n", bufname,
                 bufname, iterator, bufname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",%s_size);\n", bufname, varname, name, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "for (%s::iterator %s=%s.begin();%s!=%s.end();%s++) {\n", decl, iterator,
                 varname, iterator, varname, iterator);
        output += tmpcode;
        elements[0]->Marshal(value, bufname, nullptr, output);

        snprintf(tmpcode, sizeof(tmpcode), "}\n%s.Pop();\n", bufname);
        output += tmpcode;
    }
}

void TypeTemplate::DeMarshal(char* varname, char* bufname, char* /*sizehelper*/, std::string& output) {
    assert(!elements.empty());

    char tmpcode[10240];
    char iterator[32];
    char value[256];
    char decl[1024];
    snprintf(iterator, sizeof(iterator), "_elem%d", counter++);

    // In case we have a vector template, it is much faster to Pack the memory as one block (since it is contiguous !)
    if ((strcmp(name, "vector") == 0 || strcmp(name, "std::vector") == 0) && elements[0]->IsStandardType()) {
        char paramname[256];

        if (!FindVarName(varname, paramname)) {
            strcpy(paramname, "unkown");
        }

        snprintf(tmpcode, sizeof(tmpcode),
                 "int %s_size=0;\n%s.Push(\"@size\",\"int\", 1);\n%s.UnPack(&%s_size,1);\n%s.Pop();\n", iterator,
                 bufname, bufname, iterator, bufname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.resize(%s_size);\n", varname, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",%s_size);\n", bufname, varname, name, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.UnPack((%s*)&%s[0],%s_size);\n%s.Pop();\n", bufname,
                 elements[0]->GetName(), varname, iterator, bufname);
        output += tmpcode;
    } else if ((strcmp(name, "map") == 0 || strcmp(name, "std::map") == 0)) {
        snprintf(tmpcode, sizeof(tmpcode), "int %s_size=0;\n", iterator);
        output += tmpcode;

        elements[0]->GetDeclaration(nullptr, decl);
        snprintf(tmpcode, sizeof(tmpcode), "%s %s_key;\n", decl, iterator);
        output += tmpcode;
        elements[1]->GetDeclaration(nullptr, decl);
        snprintf(tmpcode, sizeof(tmpcode), "%s %s_value;\n", decl, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"@size\",\"int\",1);\n%s.UnPack(&%s_size,1);\n%s.Pop();\n",
                 bufname, bufname, iterator, bufname);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",%s_size);\n", bufname, varname, name, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.clear();\nfor(int i=0;i<%s_size;i++){\n", varname, iterator);
        output += tmpcode;

        elements[0]->GetDeclaration(nullptr, decl);
        snprintf(value, sizeof(value), "((%s &)(%s_key))", decl, iterator);
        elements[0]->DeMarshal(value, bufname, nullptr, output);
        elements[1]->GetDeclaration(nullptr, decl);
        snprintf(value, sizeof(value), "((%s &)(%s_value))", decl, iterator);
        elements[1]->DeMarshal(value, bufname, nullptr, output);

        snprintf(tmpcode, sizeof(tmpcode), "%s[%s_key]=%s_value;\n", varname, iterator, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "}\n%s.Pop();\n", bufname);
        output += tmpcode;

    } else {
        elements[0]->GetDeclaration(nullptr, decl);
        snprintf(value, sizeof(value), "((%s &)(*%s))", decl, iterator);

        GetDeclaration(nullptr, decl);

        snprintf(
            tmpcode, sizeof(tmpcode),
            "int %s_size;\n%s.Push(\"@size\",\"int\", 1);\n%s.UnPack(&%s_size,1);\n%s.Pop();\n%s.resize(%s_size);\n",
            iterator, bufname, bufname, iterator, bufname, varname, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "%s.Push(\"%s\",\"%s\",%s_size);\n", bufname, varname, name, iterator);
        output += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "for (%s::iterator %s=%s.begin();%s!=%s.end();%s++) {\n", decl, iterator,
                 varname, iterator, varname, iterator);
        output += tmpcode;
        elements[0]->DeMarshal(value, bufname, nullptr, output);

        snprintf(tmpcode, sizeof(tmpcode), "}\n%s.Pop();\n", bufname);
        output += tmpcode;
    }
}
