#include "type.h"
#include <stdio.h>
#include <strings.h>

TypeSeqClass::TypeSeqClass(char* name) : DataType(name) {
}

TypeSeqClass::~TypeSeqClass() {
}

/**
 * Add a base class to the current sequential class
 */
void TypeSeqClass::AddBase(DataType* t) {
    bases.push_back(t);
}

/**
 * Check if the current class can be marshalled
 */
int TypeSeqClass::CanMarshal() {
    if (IsMarked()) {
        Mark(false);
        return 0;
    }
    char* str = GetName();
    if (str == nullptr) {
        return 0;
    }
    if (strcmp(str, "pop_base") == 0) {
        return 1;
    }

    Mark(true);
    for (auto t : bases) {
        if (t->CanMarshal()) {
            Mark(false);
            return 1;
        }
    }
    Mark(false);
    return 0;
}

void TypeSeqClass::Marshal(char* varname, char* bufname, char* /*sizehelper*/, std::string& output) {
    char tmpstr[1024];
    char paramname[256];

    if (!FindVarName(varname, paramname)) {
        strcpy(paramname, "unkown");
    }
    snprintf(tmpstr, sizeof(tmpstr), "%s.Push(\"%s\",\"%s\",1);\n", bufname, paramname, GetName());
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "((%s &)(%s)).Serialize(%s, true);\n", GetName(), varname, bufname);
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "%s.Pop();\n", bufname);
    output += tmpstr;
}

void TypeSeqClass::DeMarshal(char* varname, char* bufname, char* /*sizehelper*/, std::string& output) {
    char tmpstr[1024];
    char paramname[256];

    if (!FindVarName(varname, paramname)) {
        strcpy(paramname, "unkown");
    }
    snprintf(tmpstr, sizeof(tmpstr), "%s.Push(\"%s\",\"%s\",1);\n", bufname, paramname, GetName());
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "((%s &)(%s)).Serialize(%s, false);\n", GetName(), varname, bufname);
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "%s.Pop();\n", bufname);
    output += tmpstr;
}
