#include "pop_intface.h"
#include "parser.h"
#include "pop_utils.h"
#include <assert.h>

using namespace std;

// PackObject implementation

PackObject::PackObject(CodeFile* file) : CodeData(file), startline(-1), endline(-1) {
}

void PackObject::GenerateCode(std::string& output) {
    char str[1024];
    const string& fname = GetCodeFile()->GetFileName();
    if (startline > 0 && !fname.empty()) {
        sprintf(str, "\n# %d \"%s\"\n", startline, fname.c_str());
        output += str;
    }

    sprintf(str, "\n// Generate code for pack directive\n");
    output += str;

    // New code: BEGIN===================
    strcpy(str, "void paroc_registerbroker() {\n");
    output += str;
    int n = objects.size();
    for (int i = 0; i < n; i++) {
        sprintf(str, "  %s%s::_popc_factory.test(\"%s\");\n", objects[i].c_str(), Class::POG_BROKER_POSTFIX,
                objects[i].c_str());
        output += str;
    }
    strcpy(str, "}\n");
    output += str;

    // Check if the object broker is packed
    strcpy(str, "bool CheckIfPacked(const char *objname)\n{\n\tif (objname==0) return false;\n");
    output += str;
    int sz = objects.size();
    for (int j = 0; j < sz; j++) {
        sprintf(str, "\n\tif (pop_utils::isEqual(objname, \"%s\")) return true;", objects[j].c_str());
        output += str;
    }
    strcpy(str, "\n\treturn false;\n}\n");
    output += str;
    if (endline > 0 && !fname.empty()) {
        sprintf(str, "\n# %d \"%s\"\n", endline, fname.c_str());
        output += str;
    }

    if (endline > 0 && !fname.empty()) {
        sprintf(str, "\n# %d \"%s\"\n", endline, fname.c_str());
        output += str;
    }
    return;
}

void PackObject::AddObject(const std::string& objname) {
    for (auto& object : objects) {
        if (object == objname) {
            return;
        }
    }

    objects.push_back(objname);
}

int PackObject::GetNumObject() {
    return objects.size();
}

void PackObject::SetStartLine(int l) {
    startline = l;
}

void PackObject::SetEndLine(int l) {
    endline = l;
}
