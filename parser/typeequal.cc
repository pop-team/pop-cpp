#include "type.h"

TypeEqual::TypeEqual(char* name, DataType* atype) : DataType(name) {
    type = atype;
    if (atype->GetName() == nullptr && name != nullptr) {
        atype->SetName(name);
    }
}

int TypeEqual::CanMarshal() {
    if (IsMarked()) {
        Mark(false);
        return 0;
    }
    Mark(true);
    int ret = type->CanMarshal();
    Mark(false);
    return ret;
}

void TypeEqual::Marshal(char* varname, char* bufname, char* sizehelper, std::string& output) {
    type->Marshal(varname, bufname, sizehelper, output);
}

void TypeEqual::DeMarshal(char* varname, char* bufname, char* sizehelper, std::string& output) {
    type->DeMarshal(varname, bufname, sizehelper, output);
}

int TypeEqual::IsPointer() {
    return type->IsPointer();
}

bool TypeEqual::IsArray() {
    return type->IsArray();
}

bool TypeEqual::IsParClass() {
    return type->IsParClass();
}

DataType* TypeEqual::GetBaseType() {
    DataType* t = type->GetBaseType();
    if (t != nullptr) {
        return t;
    }
    return type;
}

bool TypeEqual::GetCastType(char* output) {
    if (!IsArray()) {
        return GetDeclaration(nullptr, output);
    } else {
        return type->GetDeclaration(nullptr, output);
    }
}

void TypeEqual::GetExpandType(char* output, size_t buffer_length) {
    type->GetExpandType(output, buffer_length);
}
