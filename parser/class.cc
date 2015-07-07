/** File : class.cc
 * Author : Tuan Anh Nguyen
 * Description : POP-C++ parser/compiler Class object
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval   March 2012  Add Enum support
 * clementval   April 2012  Add namespace support to the parser
 * clementval   August 2012 Add asynchronous parallel object allocation (APOA) support
 */

#include <algorithm>

#include "pop_intface.h"

#include "parser.h"
#include "pop_utils.h"

#define MIN_CLASSID 1000

using namespace std;

char Class::interface_base[] = "pop_interface";
char Class::broker_base[] = "pop_broker";
char Class::object_base[] = "pop_object";

/**
 * Constant declaration for code generation of POG
 */
const char* Class::POG_BASE_INTERFACE_NAME = "POPC_GroupInterface";
const char* Class::POG_BASE_OBJECT_NAME = "POPC_Object";
const char* Class::POG_OBJECT_POSTFIX = "_popcobject";
const char* Class::POG_BROKER_POSTFIX = "_popcobject_Broker";
const char* Class::POG_BASE_BROKER_NAME = "POPC_GroupBroker";

Class::Class(char* clname, CodeFile* file) : CodeData(file), DataType(clname), constructor(this, PUBLIC) {
    *classid = 0;
    initDone = false;
    endid = 11;
    myFile = nullptr;
    constrcutor_id = 0;

    startline = endline = 0;
    strcpy(constructor.name, clname);
    constructor.id = 10;

    noConstructor = true;
    pureVirtual = false;
    basePureVirtual = false;
    hasWarningEnable = false;
    _is_collective = false;

    isCoreCompilation = false;
    asyncAllocationEnabled = false;

    my_interface_base = popc_strdup(interface_base);
    my_object_base = popc_strdup(object_base);
    my_broker_base = popc_strdup(broker_base);
}

Class::~Class() {
    int i, n;
    n = baseClass.size();
    for (i = 0; i < n; i++)
        if (baseClass[i] != nullptr) {
            delete baseClass[i];
        }

    n = memberList.size();
    for (i = 0; i < n; i++)
        if (memberList[i] != nullptr) {
            delete memberList[i];
        }

    if (myFile != nullptr) {
        free(myFile);
    }
    if (my_interface_base != nullptr) {
        free(my_interface_base);
    }
    if (my_object_base != nullptr) {
        free(my_object_base);
    }
    if (my_broker_base != nullptr) {
        free(my_broker_base);
    }
}

/*
parclass is also a data type
 */

bool Class::IsParClass() {
    return true;
}

int Class::CanMarshal() {
    return 1;
}

void Class::Marshal(char* varname, char* bufname, char* /*sizehelper*/, std::string& output) {
    char tmpstr[1024];
    char paramname[256];

    if (!FindVarName(varname, paramname)) {
        strcpy(paramname, "unkown");
    }
    snprintf(tmpstr, sizeof(tmpstr), "%s.Push(\"%s\",\"pop_interface\",1);\n", bufname, paramname);
    output += tmpstr;

    // If uncommented, the 4 following lines will check at runtime if polymorphism is used (and exit)
    // snprintf(tmpstr, sizeof(tmpstr), "if(!pop_utils::MatchWildcard(typeid(%s).name(),\"*%s\"))\n",varname,GetName());
    // output += tmpstr;
    // snprintf(tmpstr, sizeof(tmpstr), "{printf(\"POPC Error at method call: dynamic type of %s must correspond with static type
    // %s\\n\");exit(-1);}\n",varname,GetName());
    // output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "((%s &)(%s)).Serialize(%s, true);", GetName(), varname, bufname);
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "%s.Pop();\n", bufname);
    output += tmpstr;
}

void Class::DeMarshal(char* varname, char* bufname, char* /*sizehelper*/, std::string& output) {
    char tmpstr[1024];
    char paramname[256];

    if (!FindVarName(varname, paramname)) {
        strcpy(paramname, "unkown");
    }
    snprintf(tmpstr, sizeof(tmpstr), "%s.Push(\"%s\",\"pop_interface\",1);\n", bufname, paramname);
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "((%s &)(%s)).Serialize(%s, false);", GetName(), varname, bufname);
    output += tmpstr;

    snprintf(tmpstr, sizeof(tmpstr), "%s.Pop();\n", bufname);
    output += tmpstr;
}

/*
Other methods...
*/

void Class::SetFileInfo(char* file) {
    if (myFile != nullptr) {
        free(myFile);
    }
    myFile = popc_strdup(file);
}

char* Class::GetFileInfo() {
    return myFile;
}

void Class::SetStartLine(int num) {
    startline = num;
}

void Class::SetEndLine(int num) {
    endline = num;
}

void Class::GenerateCode(std::string& output /*, bool isPOPCPPCompilation*/) {
    char str[1024];

    // Generate the class uid in fonction of the defined one or generate one from the name of the parclass
    if (*classid == 0) {
        snprintf(str, sizeof(str), "\nconst unsigned CLASSUID_%s = unsigned(%u);\n", name, IDFromString(name));
        fprintf(stderr, "POP-C++ Warning: class unique identifier (classuid) for %s is not specified.\n", name);
    } else {
        snprintf(str, sizeof(str), "\nconst unsigned CLASSUID_%s = unsigned(%s);\n", name, classid);
    }

    if (!pureVirtual) {
        CArrayMethod puremethods;
        bool flag = findPureVirtual(puremethods);
        // printf("%s class is pureVirtual: %d methods are virtual\n", GetName(), (int)puremethods.size());
        if (puremethods.size() > 0) {
            SetPureVirtual(true);
            SetBasePureVirtual(flag);
        }
    }

    output += str;

    // If the parclass is a POG, generate differently
    if (is_collective()) {
        // Generate special code for a POG
        generate_header_pog(output, true);
        generate_header_pog(output, false);
        generate_broker_header_pog(output);
    } else {
        // Generate standard parclass code
        GenerateHeader(output, true);
        GenerateHeader(output, false);
        GenerateBrokerHeader(output);
    }
}
void Class::AddMember(ClassMember* t) {
    if (t->Type() == TYPE_METHOD) {
        Method* met = (Method*)t;
        int type = met->MethodType();
        if (type == METHOD_CONSTRUCTOR) {
            noConstructor = false;
        }

        if (type == METHOD_CONSTRUCTOR && ((Constructor*)met)->isDefault()) {
            met->id = 10;
        } else {
            met->id = endid++;
        }
    }
    memberList.push_back(t);
}

void Class::SetClassID(char* id) {
    if (id == nullptr) {
        snprintf(classid, sizeof(classid), "%u", IDFromString(name));
    } else {
        strncpy(classid, id, 63);
        classid[63] = 0;
    }
}

void Class::SetPureVirtual(bool val) {
    pureVirtual = val;
}

/**
 * Tell if the class is pure virtual
 * @return TRUE if the class is pure virtual. FALSE otherwise.
 */
bool Class::IsPureVirtual() {
    return pureVirtual;
}

/**
 * Tell is the class is pure virtual because it's a base class and has a pure virtual method or because it inherits a
 * pure
 * virtual class.
 * @return TRUE if the class is a base class and pure virtual. FALSE otherwise.
 */
bool Class::IsBasePureVirtual() {
    return basePureVirtual;
}

/**
 * Set the base pure virtual flag to the given value.
 * @param val   A boolean value. TRUE if base pure virtual.
 * @return void
 */
void Class::SetBasePureVirtual(bool val) {
    basePureVirtual = val;
}

bool Class::hasMethod(Method& x) {
    int n = memberList.size();
    for (int i = 0; i < n; i++)
        if (memberList[i]->Type() == TYPE_METHOD) {
            Method& t = *((Method*)memberList[i]);
            if (t == x) {
                return true;
            }
        }
    return false;
}

bool Class::methodInBaseClass(Method& x) {
    int n = baseClass.size();
    for (int i = 0; i < n; i++) {
        BaseClass& t = *(baseClass[i]);
        if (t.type != PUBLIC) {
            continue;
        }
        if (t.base->hasMethod(x)) {
            return true;
        }
        if (t.base->methodInBaseClass(x)) {
            return true;
        }
    }
    return false;
}

bool Class::findPureVirtual(CArrayMethod& lst) {
    bool returnFlag = true;

    // Find pure virtual classes in parents
    for (auto& bc : baseClass) {
        if (bc->type != PUBLIC) {
            continue;
        }

        bc->base->findPureVirtual(lst);
        returnFlag = false;
    }

    for (auto& member : memberList) {
        if (member->Type() == TYPE_METHOD) {
            auto t = (Method*)member;

            if (t->isPureVirtual) {
                lst.push_back(t);
            } else {
                // Remove pure virtual methods if implemented in current class
                lst.erase(std::remove_if(lst.begin(), lst.end(), [t](Method* v) { return *v == *t; }), lst.end());
            }
        }
    }

    return returnFlag;
}

bool Class::GenerateClient(string& code /*, bool isPOPCPPCompilation*/) {
    char tmpcode[10240];

    if (is_collective()) {
        snprintf(tmpcode, sizeof(tmpcode), "\n// Generate code for client side of POG\n");
        code += tmpcode;
    }

    const string& outfile = GetCodeFile()->GetOutputName();
    if (!outfile.empty()) {
        int lines = CountCodeLines(code);
        snprintf(tmpcode, sizeof(tmpcode), "\n# %d \"%s\"\n", lines + 3, outfile.c_str());
        code += tmpcode;

        if (strcmp(strnamespace.c_str(), "") != 0) {
            snprintf(tmpcode, sizeof(tmpcode), "using namespace %s;\n", strnamespace.c_str());
            code += tmpcode;
        }
    }

    if (!IsCoreCompilation() && IsAsyncAllocationEnabled()) {
        snprintf(tmpcode, sizeof(tmpcode),
                "// This code is generated for Asynchronous Parallel Object Allocation support for the object %s\n",
                name);
        code += tmpcode;

        int nb_of_methods = memberList.size();
        for (int i = 0; i < nb_of_methods; i++) {
            if (memberList[i]->Type() != TYPE_METHOD || memberList[i]->GetMyAccess() != PUBLIC) {
                continue;
            }

            Method* met = (Method*)memberList[i];
            if (met->MethodType() == METHOD_CONSTRUCTOR) {
                Constructor* cons = dynamic_cast<Constructor*>(met);
                cons->set_id(constrcutor_id++);

                snprintf(tmpcode, sizeof(tmpcode), "extern \"C\"\n{\n  void* %s_AllocatingThread%d(void* arg);\n}\n\n", name,
                        cons->get_id());
                code += tmpcode;

                snprintf(tmpcode, sizeof(tmpcode), "struct pthread_args_t_%d\n{\n  %s* ptr_interface;\n", cons->get_id(), name);
                code += tmpcode;

                //Generate all the members
                auto nb = (*met).params.size();
                for (std::size_t j = 0; j < nb; j++) {
                    snprintf(tmpcode, sizeof(tmpcode), "  ");
                    Param& p = *((*met).params[j]);
                    p.DeclareParam(tmpcode, false);
                    strcat(tmpcode, ";\n");
                    code += tmpcode;
                }

                snprintf(tmpcode, sizeof(tmpcode), "pthread_args_t_%d(", cons->get_id());
                code += tmpcode;

                snprintf(tmpcode, sizeof(tmpcode), "%s* ptr_interface", name);
                code += tmpcode;

                for (std::size_t j = 0; j < nb; j++) {
                    code += ", ";
                    snprintf(tmpcode, sizeof(tmpcode), " ");
                    Param& p = *((*met).params[j]);
                    p.DeclareParam(tmpcode, false);
                    code += tmpcode;
                }

                code += ") : ptr_interface(ptr_interface)";

                for (std::size_t j = 0; j < nb; j++) {
                    Param& p = *((*met).params[j]);
                    code += ", ";
                    code += p.GetName();
                    code += "(";
                    code += p.GetName();
                    code += ")";
                }

                code += "{}\n";

                snprintf(tmpcode, sizeof(tmpcode), "};\n\n");
                code += tmpcode;
            }
        }
    }

    int n = memberList.size();
    for (int i = 0; i < n; i++) {
        if (memberList[i]->Type() != TYPE_METHOD || memberList[i]->GetMyAccess() != PUBLIC) {
            continue;
        }

        Method* met = (Method*)memberList[i];
        if (pureVirtual && met->MethodType() == METHOD_CONSTRUCTOR &&
            IsCoreCompilation()) {  // TODO LW: Why do we generate virtual clients if not core ! Why do we generate
                                    // clients at all for virtual classes ?
            continue;
        }

        met->GenerateClient(code);
    }

    if (noConstructor && !pureVirtual) {
        constructor.GenerateClient(code);
    }

    if (is_collective()) {
        snprintf(tmpcode, sizeof(tmpcode), "\nvoid %s::construct_remote_object() {\n  switch(_popc_selected_constructor_id) {",
                GetName());
        code += tmpcode;
        int n = memberList.size();
        for (int i = 0; i < n; i++) {
            if (memberList[i]->Type() == TYPE_METHOD) {
                Method* m = dynamic_cast<Method*>(memberList[i]);
                if (m->MethodType() == METHOD_CONSTRUCTOR) {
                    Constructor* c = dynamic_cast<Constructor*>(memberList[i]);
                    snprintf(tmpcode, sizeof(tmpcode), "\n  case %d:", (*c).id);
                    code += tmpcode;
                    strcpy(tmpcode, "\n    _popc_constructor(");
                    code += tmpcode;
                    auto nb = (*c).params.size();
                    for (std::size_t j = 0; j < nb; j++) {
                        Param& p = *((*c).params[j]);
                        snprintf(tmpcode, sizeof(tmpcode), "_popc_constructor_%d_%s", (*c).id, p.GetName());
                        if (j < nb - 1) {
                            strcat(tmpcode, ", ");
                        }
                        code += tmpcode;
                    }
                    strcpy(tmpcode, ");\n    break;");
                    code += tmpcode;
                }
            }
        }
        strcpy(tmpcode, "\n  }\n}");
        code += tmpcode;

        snprintf(tmpcode, sizeof(tmpcode), "\%s& %s::operator[] (const int index) {\n  set_default_rank(index);\n  return (*this);\n}\n",
                GetName(), GetName());
        code += tmpcode;
    }

    const string& fname = GetCodeFile()->GetFileName();
    if (endline > 0 && !fname.empty()) {
        snprintf(tmpcode, sizeof(tmpcode), "\n# %d \"%s\"\n", endline, fname.c_str());
        code += tmpcode;
    }
    return true;
}

unsigned Class::IDFromString(char* str) {
    char tmp[256];
    int n = 0;
    int len = strlen(str);
    int starta = ('Z' - 'A') + 1;
    for (int i = 0; i < len && i < 256; i++, str++) {
        if (*str >= 'A' && *str >= 'Z') {
            tmp[n++] = (*str) - 'A';
        } else if (*str >= 'a' && *str >= 'z') {
            tmp[n++] = (*str) - 'a' + starta;
        } else if (*str == '_') {
            tmp[n++] = 2 * starta;
        } else if (*str >= '0' && *str <= '9') {
            tmp[n++] = (*str) - '0' + 2 * starta + 1;
        }
    }

    unsigned sz = 2 * starta + 11;
    n--;
    if (n < 0)
        return 999 + MIN_CLASSID;  // note LW: added this to quiet the compilation errors of g++
    unsigned id = tmp[n];
    for (int i = 0; i < n; i++) {
        id = id * sz + tmp[i];
    }
    return id + MIN_CLASSID;
}

bool Class::generate_broker_header_pog(std::string& code) {
    int i;
    char str[1024];
    char tmpcode[10240];
    char brokername[256];
    const string& outfile = GetCodeFile()->GetOutputName();

    // Print a comment in the generated code
    snprintf(tmpcode, sizeof(tmpcode), "\n// Generate broker-side code for a POG\n");
    code += tmpcode;

    if (!outfile.empty()) {
        int lines = CountCodeLines(code);
        snprintf(tmpcode, sizeof(tmpcode), "\n# %d \"%s\"\n", lines + 3, outfile.c_str());
        code += tmpcode;
    }

    // Prepare broker name
    snprintf(brokername, sizeof(brokername), "%s%s", name, Class::POG_BROKER_POSTFIX);

    int n = baseClass.size();
    if (n == 0) {
        snprintf(tmpcode, sizeof(tmpcode), "\n\nclass %s: virtual public %s", brokername, Class::POG_BASE_BROKER_NAME);
    } else {
        snprintf(tmpcode, sizeof(tmpcode), "\n\nclass %s: ", brokername);
        for (i = 0; i < n; i++) {
            if (baseClass[i]->baseVirtual) {
                strcat(tmpcode, "virtual ");
            }
            strcat(tmpcode, "public ");
            strcat(tmpcode, baseClass[i]->base->GetName());
            strcat(tmpcode, POG_BASE_BROKER_NAME);
            if (i < n - 1) {
                strcat(tmpcode, ", ");
            }
        }
    }
    snprintf(str, sizeof(str),
            "\n{\npublic:\n  %s();\n  virtual bool invoke(unsigned method[3],  pop_buffer &_popc_buffer, "
            "pop_connection *_popc_connection);",
            brokername);
    strcat(tmpcode, str);

    strcat(tmpcode, "\nprotected:");
    code += tmpcode;

    n = memberList.size();
    for (i = 0; i < n; i++) {
        if (memberList[i]->GetMyAccess() != PUBLIC || memberList[i]->Type() != TYPE_METHOD) {
            continue;
        }
        Method& met = *((Method*)memberList[i]);
        if (pureVirtual && met.MethodType() == METHOD_CONSTRUCTOR && IsCoreCompilation()) {
            continue;
        }
        met.generate_broker_header_pog(code);
    }

    /* In the current version a constructor is mandatory so no need for this.
      if (noConstructor && !pureVirtual) {
        constructor.GenerateBrokerHeader(code);
    }*/

    snprintf(tmpcode, sizeof(tmpcode),
            "\npublic:\n  static POPC_GroupBroker *_init();\n  static POPC_GroupBrokerFactory _popc_factory;\n");
    code += tmpcode;
    strcpy(str, "\n}\n;");
    code += str;

    const string& fname = GetCodeFile()->GetFileName();
    if (endline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", endline, fname.c_str());
        code += str;
    }
    return true;
}

bool Class::generate_header_pog(std::string& code, bool interface) {
    char tmpcode[10240];
    char str[1024];
    const string& fname = GetCodeFile()->GetFileName();
    if (startline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", startline, fname.c_str());
        code += str;
    }

    if (interface) {
        snprintf(tmpcode, sizeof(tmpcode), "\n// Generated code for the interface-side of a POG\n");
        code += tmpcode;
    } else {
        snprintf(tmpcode, sizeof(tmpcode), "\n// Generated code for the object-side of a POG\n");
        code += tmpcode;
    }

    strcpy(str, name);

    if (!interface) {
        strcat(str, POG_OBJECT_POSTFIX);
    }

    snprintf(tmpcode, sizeof(tmpcode), "class %s ", str);
    int n = baseClass.size();
    strcat(tmpcode, " :");

    int i;

    for (i = 0; i < n; i++) {
        BaseClass& base = *(baseClass[i]);
        if (base.baseVirtual) {
            strcat(tmpcode, "virtual ");
        }
        if (base.type == PUBLIC) {
            strcat(tmpcode, "public ");
        } else if (base.type == PROTECTED) {
            strcat(tmpcode, "protected ");
        } else {
            strcat(tmpcode, "private ");
        }
        strcat(tmpcode, base.base->GetName());
        if (!interface) {
            strcat(tmpcode, POG_OBJECT_POSTFIX);
        }
        if (i < n - 1) {
            strcat(tmpcode, ", ");
        }
    }
    if (n) {
        strcat(tmpcode, "\n{\npublic:");
    } else if (interface) {
        snprintf(str, sizeof(str), " virtual public %s\n{\npublic: ", Class::POG_BASE_INTERFACE_NAME);
        strcat(tmpcode, str);
    } else {
        snprintf(str, sizeof(str), " virtual public %s\n{\npublic:", POG_BASE_OBJECT_NAME);
        strcat(tmpcode, str);
    }

    code += tmpcode;
    *tmpcode = 0;

    // Generate members
    const char* accessstr[3] = {"\npublic:", "\nprotected:", "\nprivate:"};
    AccessType currentaccess = PUBLIC;
    n = memberList.size();

    for (i = 0; i < n; i++) {
        if (interface && memberList[i]->GetMyAccess() != PUBLIC) {
            continue;
        }

        if (memberList[i]->GetMyAccess() != currentaccess) {
            currentaccess = memberList[i]->GetMyAccess();
            code += accessstr[currentaccess];
        }

        memberList[i]->generate_header_pog(code, interface);
    }

    if (interface) {
        snprintf(str, sizeof(str), "\npublic:\n  virtual void construct_remote_object();");
        code += str;

        // snprintf(str, sizeof(str),"\n  void _popc_constructor();", name);
        // code += str;

        snprintf(str, sizeof(str), "\n  virtual char* get_class_name() { return (char*)\"%s\"; };\n", name);
        code += str;

        snprintf(str, sizeof(str), "\n  %s& operator[] (const int index);\n", name);
        code += str;

        /*int n=baseClass.size();
        if (n)
        {
            CArrayClass bases;
            bases.resize(n);
            for (int i=0;i<n;i++)  bases[i]=baseClass[i]->base;
            CodeFile *prog=GetCodeFile();
            prog->FindAllBaseClass(*this, bases,true);

            n=bases.size();
            strcpy(tmpcode," : ");
            for (int j=0;j<n;j++)
            {
                strcat(tmpcode,bases[j]->GetName());
                if (j<n-1) strcat(tmpcode,"(_pop_nobind) ,");
                else  strcat(tmpcode,"(_pop_nobind)");
            }
            code += tmpcode;
        }

        strcpy(str," { Bind(p); };\n");
        code += str;


        if (noConstructor && !pureVirtual)
        { constructor.GenerateHeader(code, interface); }

        //Generate constructor from the interface binding
        snprintf(str, sizeof(str),"\n%s(const %s &inf)",name, my_interface_base);
        code += str;
        code += tmpcode;
        strcpy(str," { SetOD(inf.GetOD()); Bind(inf.GetAccessPoint()); };\n");
        code += str;

        //Generate constructor from the object side binding
        snprintf(str, sizeof(str),"\n%s(const pop_object *obj)",name);
        code += str;
        code += tmpcode;
        strcpy(str," { Bind(obj->GetAccessPoint());};\n");
        code += str;*/

        snprintf(str, sizeof(str), "\n  ~%s() {};", name);
        code += str;

        n = memberList.size();
        for (i = 0; i < n; i++) {
            if (memberList[i]->Type() == TYPE_METHOD) {
                Method* m = dynamic_cast<Method*>(memberList[i]);
                if (m->MethodType() == METHOD_CONSTRUCTOR) {
                    Constructor* t = dynamic_cast<Constructor*>(memberList[i]);
                    for (auto& param : t->params) {
                        Param& p = *param;
                        snprintf(str, sizeof(str), "\n  %s _popc_constructor_%d_%s;\n", p.GetType()->GetName(), (*t).id, p.GetName());
                        code += str;
                    }
                }
            }
        }
    }

    // Add the declaration of the __POPThis variable for support of the "this" keyword
    snprintf(str, sizeof(str), "\npublic:\n  %s* __POPThis_%s; \n", name, name);
    code += str;
    strcpy(str, "\n};\n");
    code += str;

    if (endline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", endline, fname.c_str());
        code += str;
    }

    return true;
}

bool Class::GenerateHeader(std::string& code, bool interface /*, bool isPOPCPPCompilation*/) {
    char tmpcode[10240];
    char str[1024];

    const string& fname = GetCodeFile()->GetFileName();
    if (startline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", startline, fname.c_str());
        code += str;
    }

    strcpy(str, name);

    if (!interface) {
        strcat(str, OBJ_POSTFIX);
    }

    snprintf(tmpcode, sizeof(tmpcode), "class %s ", str);
    int n = baseClass.size();
    strcat(tmpcode, " :");

    int i;

    for (i = 0; i < n; i++) {
        BaseClass& base = *(baseClass[i]);
        if (base.baseVirtual) {
            strcat(tmpcode, "virtual ");
        }
        if (base.type == PUBLIC) {
            strcat(tmpcode, "public ");
        } else if (base.type == PROTECTED) {
            strcat(tmpcode, "protected ");
        } else {
            strcat(tmpcode, "private ");
        }

        strcat(tmpcode, base.base->GetName());
        if (!interface) {
            strcat(tmpcode, OBJ_POSTFIX);
        }
        if (i < n - 1) {
            strcat(tmpcode, ", ");
        }
    }
    if (n) {
        strcat(tmpcode, "\n{\npublic:");
    } else if (interface) {
        snprintf(str, sizeof(str), " virtual public %s\n{\npublic:", my_interface_base);
        strcat(tmpcode, str);
    } else {
        snprintf(str, sizeof(str), " virtual public %s\n{\npublic:", my_object_base);
        strcat(tmpcode, str);
    }

    code += tmpcode;
    *tmpcode = 0;

    // Generate members
    const char* accessstr[3] = {"\npublic:", "\nprotected:", "\nprivate:"};
    AccessType currentaccess = PUBLIC;
    n = memberList.size();

    for (i = 0; i < n; i++) {
        if (interface && memberList[i]->GetMyAccess() != PUBLIC) {
            continue;
        }

        if (memberList[i]->GetMyAccess() != currentaccess) {
            currentaccess = memberList[i]->GetMyAccess();
            code += accessstr[currentaccess];
        }

        if (memberList[i]->Type() == TYPE_METHOD) {
            Method* t = (Method*)memberList[i];
            if (t->MethodType() == METHOD_CONSTRUCTOR) {
                // if ( ((Constructor *)t)->isDefault()) defaultconstructor=true;
                /*PEKA Removed */  // if (interface && pureVirtual) continue;
            }
        }

        memberList[i]->GenerateHeader(code, interface);
    }

    // Add the declaration of the __POPThis variable for support of the "this" keyword
    snprintf(str, sizeof(str), "\n%s* __POPThis_%s; \n", name, name);
    code += str;

    snprintf(str, sizeof(str), "void AllocateObject();\n");
    code += str;

    bool declared_constructor = false;
    for(auto& member : memberList){
        if (member->Type() == TYPE_METHOD) {
            Method* t = (Method*) member;
            if (t->MethodType() == METHOD_DESTRUCTOR) {
                declared_constructor = true;
                break;
            }
        }
    }

    if (interface) {
        snprintf(str, sizeof(str), "\npublic:\nvirtual const char *ClassName() { return \"%s\"; };", name);
        code += str;

        // Generate constructor from pop_accesspoint...
        snprintf(str, sizeof(str), "\npublic:\n%s(const pop_accesspoint &p)", name);
        code += str;

        int n = baseClass.size();
        if (n) {
            CArrayClass bases;
            bases.resize(n);
            for (int i = 0; i < n; i++) {
                bases[i] = baseClass[i]->base;
            }
            CodeFile* prog = GetCodeFile();
            prog->FindAllBaseClass(*this, bases, true);

            n = bases.size();
            strcpy(tmpcode, " : ");
            for (int j = 0; j < n; j++) {
                strcat(tmpcode, bases[j]->GetName());
                if (j < n - 1) {
                    strcat(tmpcode, "(_pop_nobind) ,");
                } else {
                    strcat(tmpcode, "(_pop_nobind)");
                }
            }
            code += tmpcode;
        }

        strcpy(str, " { Bind(p); };\n");
        code += str;

        // If no constructor, generate default for interface...
        if (noConstructor /*PEKA Removed */ && !pureVirtual) {
            constructor.GenerateHeader(code, interface);
        }

        // Generate constructor from the interface binding
        snprintf(str, sizeof(str), "\n%s(const %s &inf)", name, my_interface_base);
        code += str;
        code += tmpcode;
        strcpy(str, " { SetOD(inf.GetOD()); Bind(inf.GetAccessPoint()); };\n");
        code += str;

        // Generate constructor from the object side binding
        snprintf(str, sizeof(str), "\n%s(const pop_object *obj)", name);
        code += str;
        code += tmpcode;
        strcpy(str, " { Bind(obj->GetAccessPoint());};\n");
        code += str;

        snprintf(str, sizeof(str), "\n~%s()", name);
        code += str;

        // In case of async allocation, we need a body for synchronization purpose
        if (!IsCoreCompilation() && IsAsyncAllocationEnabled()) {
            if(declared_constructor){
                code += ";";
            } else {
                code += "{\n";
                code += "  if(_popc_async){\n";
                code += "    pthread_mutex_lock(&_popc_async_mutex);\n";
                code += "    if(!_popc_async_joined){\n";
                code += "      void* status;\n  pthread_join(_popc_async_construction_thread, &status);\n";
                code += "      _popc_async_joined = true;\n";
                code += "    }\n";
                code += "    pthread_mutex_unlock(&_popc_async_mutex);\n";
                code += "  }\n";
                code += "  if(!isBinded()) {\n";
                code += "     printf(\"POP-C++ Error: [APOA] Object not allocated but allocation process done !\");\n";
                code += "  }\n";
                code += "}";
            }
        } else {
            code += "{}\n";
        }
    }

    strcpy(str, "\n};\n");
    code += str;

    if (endline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", endline, fname.c_str());
        code += str;
    }

    return true;
}

bool Class::GenerateBrokerHeader(std::string& code /*, bool isPOPCPPCompilation*/) {
    int i;
    char str[1024];
    char tmpcode[10240];
    char brokername[256];

    if (is_collective()) {
        snprintf(tmpcode, sizeof(tmpcode), "\n//Generating broker-side of a POG\n");
        code += tmpcode;
    }

    const string& outfile = GetCodeFile()->GetOutputName();
    if (!outfile.empty()) {
        int lines = CountCodeLines(code);
        snprintf(tmpcode, sizeof(tmpcode), "\n# %d \"%s\"\n", lines + 3, outfile.c_str());
        code += tmpcode;
    }
    snprintf(brokername, sizeof(brokername), "%s%s", name, Class::POG_BROKER_POSTFIX);

    int n = baseClass.size();
    if (n == 0) {
        snprintf(tmpcode, sizeof(tmpcode), "\n\nclass %s: virtual public %s", brokername, my_broker_base);
    } else {
        snprintf(tmpcode, sizeof(tmpcode), "\n\nclass %s: ", brokername);
        for (i = 0; i < n; i++) {
            if (baseClass[i]->baseVirtual) {
                strcat(tmpcode, "virtual ");
            }
            strcat(tmpcode, "public ");
            strcat(tmpcode, baseClass[i]->base->GetName());
            strcat(tmpcode, Class::POG_BROKER_POSTFIX);
            //          strcat(tmpcode, "Broker");
            if (i < n - 1) {
                strcat(tmpcode, ", ");
            }
        }
    }
    snprintf(
        str, sizeof(str),
        "\n{\npublic:\n%s();\nvirtual bool Invoke(unsigned method[3],  pop_buffer &__brokerbuf, pop_connection *peer);",
        brokername);
    strcat(tmpcode, str);

    strcat(tmpcode, "\nprotected:");
    code += tmpcode;

    n = memberList.size();
    for (i = 0; i < n; i++) {
        if (memberList[i]->GetMyAccess() != PUBLIC || memberList[i]->Type() != TYPE_METHOD) {
            continue;
        }
        Method& met = *((Method*)memberList[i]);
        if (pureVirtual && met.MethodType() == METHOD_CONSTRUCTOR /* LAST MODIFICATION */ && IsCoreCompilation()) {
            continue;
        }
        met.GenerateBrokerHeader(code);
    }

    if (noConstructor && !pureVirtual) {
        constructor.GenerateBrokerHeader(code);
    }

    snprintf(tmpcode, sizeof(tmpcode), "\npublic:\nstatic pop_broker *_init();\nstatic pop_broker_factory _popc_factory;\n");
    code += tmpcode;

    strcpy(str, "\n}\n;");

    code += str;

    const string& fname = GetCodeFile()->GetFileName();
    if (endline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", endline, fname.c_str());
        code += str;
    }
    return true;
}

bool Class::GenerateBroker(std::string& code /*, bool isPOPCPPCompilation*/) {
    // Generate Broker-derived class for creation objects and the re-implementation of

    int i;
    char str[10240];
    char tmpcode[10240];
    char brokername[256];

    if (is_collective()) {
        snprintf(tmpcode, sizeof(tmpcode), "\n// Generating code implementing the broker of a POG\n");
        code += tmpcode;
    }

    CodeFile* codefile = GetCodeFile();

    const string& outfile = codefile->GetOutputName();
    if (!outfile.empty()) {
        int lines = CountCodeLines(code);
        snprintf(tmpcode, sizeof(tmpcode), "\n# %d \"%s\"\n", lines + 3, outfile.c_str());
        code += tmpcode;
    }

    snprintf(brokername, sizeof(brokername), "%s%s", name, Class::POG_BROKER_POSTFIX);

    // now...the implementation....

    // Generate broker::Invoke virtual method
    if (is_collective()) {
        snprintf(str, sizeof(str),
                "\nbool %s::invoke(unsigned method[3], pop_buffer &_popc_buffer, pop_connection *_popc_connection) {\n "
                "if (*method == CLASSUID_%s) {\n    switch(method[1]) {",
                brokername, name);
    } else {
        snprintf(str, sizeof(str),
                "\nbool %s::Invoke(unsigned method[3], pop_buffer &__brokerbuf, pop_connection *peer)\n{\n if "
                "(*method==CLASSUID_%s) {\n    switch(method[1])\n{",
                brokername, name);
    }
    code += str;

    char methodinfo[10240];
    char methodcount = 0;
    char* methodinfoptr = methodinfo;
    *methodinfoptr = 0;

    int n = memberList.size();
    for (i = 0; i < n; i++) {
        if (memberList[i]->GetMyAccess() != PUBLIC || memberList[i]->Type() != TYPE_METHOD) {
            continue;
        }
        Method& met = *((Method*)memberList[i]);

        int t = met.MethodType();
        if (t == METHOD_DESTRUCTOR || met.isHidden /* LAST MODIFICATION */ ||
            (pureVirtual && t == METHOD_CONSTRUCTOR && IsCoreCompilation()) ||
            (met.isVirtual && methodInBaseClass(met))) {
            continue;
        }
        if (is_collective()) {
            snprintf(str, sizeof(str), "\n      case %d: Invoke_%s_%d(_popc_buffer, _popc_connection);\n        return true;", met.id,
                    met.name, met.id);
        } else {
            snprintf(str, sizeof(str), "\n    case %d: Invoke_%s_%d(__brokerbuf, peer); return true;", met.id, met.name, met.id);
        }
        code += str;

        // Collect method id, name
        if (methodcount) {
            snprintf(methodinfoptr, methodinfo - methodinfoptr + sizeof(methodinfo), ",{%d,(char*)\"%s\"}", met.id, met.name);
        } else {
            snprintf(methodinfoptr, methodinfo - methodinfoptr + sizeof(methodinfo), "{%d,(char*)\"%s\"}", met.id, met.name);
        }
        methodcount++;
        methodinfoptr += strlen(methodinfoptr);
    }
    if (noConstructor && !pureVirtual) {
        snprintf(str, sizeof(str), "\ncase %d: Invoke_%s_%d(__brokerbuf, peer); return true;", constructor.id, constructor.name,
                constructor.id);
        code += str;

        if (methodcount) {
            snprintf(methodinfoptr, methodinfo - methodinfoptr + sizeof(methodinfo), ",{%d,(char*)\"%s\"}", constructor.id, constructor.name);
        } else {
            snprintf(methodinfoptr, methodinfo - methodinfoptr + sizeof(methodinfo), "{%d,(char*)\"%s\"}", constructor.id, constructor.name);
        }
        methodcount++;
    }

    strcpy(str, "\n    default:\n      return false;\n    }\n  }");
    code += str;

    n = baseClass.size();
    for (i = 0; i < n; i++) {
        snprintf(str, sizeof(str), "\nelse if (%s%s::Invoke(method,__brokerbuf,peer)) return true;", baseClass[i]->base->GetName(),
                Class::POG_BROKER_POSTFIX);
        code += str;
    }
    if (n) {
        strcpy(str, "\nreturn false;\n}");
    } else {
        if (is_collective()) {
            strcpy(str, "\n  return POPC_GroupBroker::invoke(method, _popc_buffer, _popc_connection);\n}\n");
        } else {
            strcpy(str, "\nreturn pop_broker::Invoke(method,__brokerbuf,peer);\n}\n");
        }
    }

    code += str;

    // Generate default constructor
    if (is_collective()) {
        snprintf(str, sizeof(str),
                "\n%s::%s()\n{\n  static popc_method_info _popc_minfo[%d] = { %s };\n  add_method_info(CLASSUID_%s, "
                "_popc_minfo, %d);\n}\n",
                brokername, brokername, methodcount, methodinfo, name, methodcount);
    } else {
        snprintf(str, sizeof(str),
                "\n%s::%s()\n{\nstatic pop_method_info _paroc_minfo[%d]={%s};\nAddMethodInfo(CLASSUID_%s, "
                "_paroc_minfo, %d);\n}",
                brokername, brokername, methodcount, methodinfo, name, methodcount);
    }
    code += str;

    // Generate code for Invoke_xxx(...) to invoke object's method
    n = memberList.size();
    for (i = 0; i < n; i++) {
        if (memberList[i]->GetMyAccess() != PUBLIC || memberList[i]->Type() != TYPE_METHOD) {
            continue;
        }

        Method& met = *((Method*)memberList[i]);
        int t = met.MethodType();
        if (t == METHOD_DESTRUCTOR || met.isHidden || (pureVirtual && t == METHOD_CONSTRUCTOR && IsCoreCompilation()) ||
            (met.isVirtual && methodInBaseClass(met))) {
            continue;
        }
        met.GenerateBroker(code);
    }

    // Generate default constructor stubs
    if (noConstructor) {
        constructor.GenerateBroker(code);
    }

    if (is_collective()) {
        snprintf(tmpcode, sizeof(tmpcode),
                "\nPOPC_GroupBroker* %s::_init() { return new %s; }\nPOPC_GroupBrokerFactory %s::_popc_factory(_init, "
                "\"%s\");\n",
                brokername, brokername, brokername, name);
    } else {
        snprintf(tmpcode, sizeof(tmpcode),
                "\npop_broker *%s::_init() { return new %s; }\npop_broker_factory %s::_popc_factory(_init, \"%s\");\n",
                brokername, brokername, brokername, name);
    }
    code += tmpcode;

    const string& fname = GetCodeFile()->GetFileName();
    if (endline > 0 && !fname.empty()) {
        snprintf(str, sizeof(str), "\n# %d \"%s\"\n", endline, fname.c_str());
        code += str;
    }

    return true;
}

/**
 * Set the namespace associated with this class.
 * @param value Name of the namespace
 * @return void
 */
void Class::SetNamespace(char* value) {
    strnamespace.assign(value);
}

/**
 * Get the namespace associated with this class.
 * @return A string value representing the name of the namespace.
 */
std::string Class::GetNamespace() {
    return strnamespace;
}

/**
 * Set the current code file as compilation of the POP-C++ core.
 * @return void
 */
void Class::SetAsCoreCompilation() {
    isCoreCompilation = true;
}

/**
 * Check if the current compilation is the POP-C++ core compilation.
 * @return TRUE if it is the core compilation. FALSE otherwise.
 */
bool Class::IsCoreCompilation() {
    return isCoreCompilation;
}

/**
 * Enable warnings for the compilation
 * @return void
 */
void Class::EnableWarning() {
    hasWarningEnable = true;
}

/**
 *  Check if warning are enable.
 * @return TRUE if warnings are enable. FALSE otherwise.
 */
bool Class::IsWarningEnable() {
    return hasWarningEnable;
}

/**
 * Enable the asynchronous parallel object allocation mechanism.
 * @return void
 */
void Class::EnableAsyncAllocation() {
    asyncAllocationEnabled = true;
}

/**
 * Check if asynchronous parallel object allocation is enabled
 * @return TRUE if asynchronous allocation is disable. FALSE otherwise.
 */
bool Class::IsAsyncAllocationEnabled() {
    return asyncAllocationEnabled;
}

/**
 * Set the class as a collective (group) class
 */
void Class::set_as_collective() {
    _is_collective = true;
}

/**
 * Check if the class is a collective class (group)=
 * @return TRUE if it is a collective class.
 */
bool Class::is_collective() {
    return _is_collective;
}
