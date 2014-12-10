/**
 * File : class.cc
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

#include "popc_intface.h"

#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"

#define MIN_CLASSID 1000
char Class::interface_base[]="paroc_interface";
char Class::broker_base[]="paroc_broker";
char Class::object_base[]="paroc_object";

/**
 * Constant declaration for code generation of POG
 */
const char* Class::POG_BASE_INTERFACE_NAME = "POPC_GroupInterface";
const char* Class::POG_BASE_OBJECT_NAME = "POPC_Object";
const char* Class::POG_OBJECT_POSTFIX = "_popcobject";
const char* Class::POG_BROKER_POSTFIX = "_popcobject_Broker";
const char* Class::POG_BASE_BROKER_NAME = "POPC_GroupBroker";

Class::Class(char *clname, CodeFile *file): CodeData(file), DataType(clname), constructor(this, PUBLIC) {
    *classid = 0;
    initDone = false;
    endid = 11;
    myFile = NULL;
    constrcutor_id = 0;

    startline = endline = 0;
    strcpy(constructor.name, clname);
    constructor.id = 10;

    noConstructor=true;
    pureVirtual=false;
    basePureVirtual=false;
    hasWarningEnable=false;
    _is_collective = false;

    my_interface_base=popc_strdup(interface_base);
    my_object_base=popc_strdup(object_base);
    my_broker_base=popc_strdup(broker_base);

}

Class::~Class() {
    int i,n;
    n=baseClass.GetSize();
    for(i=0; i<n; i++) if(baseClass[i]!=NULL) {
            delete baseClass[i];
        }

    n=memberList.GetSize();
    for(i=0; i<n; i++) if(memberList[i]!=NULL) {
            delete memberList[i];
        }

    if(myFile!=NULL) {
        free(myFile);
    }
    if(my_interface_base!=NULL) {
        free(my_interface_base);
    }
    if(my_object_base!=NULL) {
        free(my_object_base);
    }
    if(my_broker_base!=NULL) {
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

void Class::Marshal(char *varname, char *bufname, char* /*sizehelper*/, CArrayChar &output) {
    char tmpstr[1024];
    char paramname[256];

    if(!FindVarName(varname,paramname)) {
        strcpy(paramname,"unkown");
    }
    sprintf(tmpstr,"%s.Push(\"%s\",\"paroc_interface\",1);\n",bufname,paramname);
    output.InsertAt(-1,tmpstr,strlen(tmpstr));

    // If uncommented, the 4 following lines will check at runtime if polymorphism is used (and exit)
    //sprintf(tmpstr, "if(!paroc_utils::MatchWildcard(typeid(%s).name(),\"*%s\"))\n",varname,GetName());
    //output.InsertAt(-1,tmpstr,strlen(tmpstr));
    //sprintf(tmpstr, "{printf(\"POPC Error at method call: dynamic type of %s must correspond with static type %s\\n\");exit(-1);}\n",varname,GetName());
    //output.InsertAt(-1,tmpstr,strlen(tmpstr));

    sprintf(tmpstr, "((%s &)(%s)).Serialize(%s, true);",GetName(),varname,bufname);
    output.InsertAt(-1,tmpstr,strlen(tmpstr));

    sprintf(tmpstr,"%s.Pop();\n",bufname);
    output.InsertAt(-1,tmpstr,strlen(tmpstr));
}

void Class::DeMarshal(char *varname, char *bufname, char* /*sizehelper*/, CArrayChar &output) {
    char tmpstr[1024];
    char paramname[256];

    if(!FindVarName(varname,paramname)) {
        strcpy(paramname,"unkown");
    }
    sprintf(tmpstr,"%s.Push(\"%s\",\"paroc_interface\",1);\n",bufname,paramname);
    output.InsertAt(-1,tmpstr,strlen(tmpstr));

    sprintf(tmpstr, "((%s &)(%s)).Serialize(%s, false);",GetName(),varname,bufname);
    output.InsertAt(-1,tmpstr,strlen(tmpstr));

    sprintf(tmpstr,"%s.Pop();\n",bufname);
    output.InsertAt(-1,tmpstr,strlen(tmpstr));
}


/*
Other methods...
*/

void Class::SetFileInfo(char *file) {
    if(myFile != NULL) {
        free(myFile);
    }
    myFile = popc_strdup(file);
}

char * Class::GetFileInfo() {
    return myFile;
}

void Class::SetStartLine(int num) {
    startline=num;
}


void Class::SetEndLine(int num) {
    endline=num;
}


void Class::GenerateCode(CArrayChar &output/*, bool isPOPCPPCompilation*/) {
    char str[1024];

    // Generate the class uid in fonction of the defined one or generate one from the name of the parclass
    if(*classid == 0) {
        sprintf(str, "\nconst unsigned CLASSUID_%s = unsigned(%u);\n", name, IDFromString(name));
        fprintf(stderr, "POP-C++ Warning: class unique identifier (classuid) for %s is not specified.\n", name);
    } else {
        sprintf(str,"\nconst unsigned CLASSUID_%s = unsigned(%s);\n",name,classid);
    }

    if(!pureVirtual) {
        CArrayMethod puremethods;
        bool flag = findPureVirtual(puremethods);
        if(puremethods.GetSize()>0) {
            SetPureVirtual(true);
            SetBasePureVirtual(flag);
        }
    }

    output.InsertAt(-1,str,strlen(str));

    // If the parclass is a POG, generate differently
    if(is_collective()) {
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
void Class::AddMember(ClassMember *t) {
    if(t->Type()==TYPE_METHOD) {
        Method *met=(Method *)t;
        int type=met->MethodType();
        if(type==METHOD_CONSTRUCTOR) {
            noConstructor=false;
        }

        if(type==METHOD_CONSTRUCTOR && ((Constructor *)met)->isDefault()) {
            met->id=10;
        } else {
            met->id=endid++;
        }
    }
    memberList.InsertAt(-1,t);
}


void Class::SetClassID(char *id) {
    if(id==NULL) {
        sprintf(classid,"%u",IDFromString(name));
    } else {
        strncpy(classid,id,63);
        classid[63]=0;
    }
}

void Class::SetPureVirtual(bool val) {
    pureVirtual=val;
}

/**
 * Tell if the class is pure virtual
 * @return TRUE if the class is pure virtual. FALSE otherwise.
 */
bool Class::IsPureVirtual() {
    return pureVirtual;
}

/**
 * Tell is the class is pure virtual because it's a base class and has a pure virtual method or because it inherits a pure
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
    basePureVirtual=val;
}

bool Class::hasMethod(Method &x) {
    int n=memberList.GetSize();
    for(int i=0; i<n; i++) if(memberList[i]->Type()==TYPE_METHOD) {
            Method &t=*((Method *)memberList[i]);
            if(t==x) {
                return true;
            }
        }
    return false;
}

bool Class::methodInBaseClass(Method &x) {
    int n=baseClass.GetSize();
    for(int i=0; i<n; i++) {
        BaseClass &t=*(baseClass[i]);
        if(t.type!=PUBLIC) {
            continue;
        }
        if(t.base->hasMethod(x)) {
            return true;
        }
        if(t.base->methodInBaseClass(x)) {
            return true;
        }
    }
    return false;
}


bool Class::findPureVirtual(CArrayMethod &lst) {
    bool returnFlag = true;

    int n=baseClass.GetSize();
    for(int i=0; i<n; i++) {
        BaseClass &t=*(baseClass[i]);
        if(t.type!=PUBLIC) {
            continue;
        }
        t.base->findPureVirtual(lst);
        returnFlag = false;
    }

    n=memberList.GetSize();
    int m=lst.GetSize();
    for(int i=0; i<n; i++) if(memberList[i]->Type()==TYPE_METHOD) {
            Method *t=(Method *)(memberList[i]);
            if(t->isPureVirtual) {
                lst.InsertAt(-1,t);
            } else if(m) {
                for(int j=m-1; j>=0; j--) {
                    if(*(lst[j]) == (*t)) {
                        lst.RemoveAt(j);
                    }
                }
            }
        }
    return returnFlag;
}

bool Class::GenerateClient(CArrayChar &code/*, bool isPOPCPPCompilation*/) {
    char tmpcode[10240];

    if(is_collective()) {
        sprintf(tmpcode,"\n// Generate code for client side of POG\n");
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
    }

    char *outfile=GetCodeFile()->GetOutputName();
    if(outfile != NULL) {
        int lines=CountCodeLines(code);
        sprintf(tmpcode,"\n# %d \"%s\"\n",lines+3, outfile);
        code.InsertAt(-1,tmpcode,strlen(tmpcode));

        if(strcmp(strnamespace.c_str(), "") != 0) {
            sprintf(tmpcode,"using namespace %s;\n", strnamespace.c_str());
            code.InsertAt(-1,tmpcode,strlen(tmpcode));
        }
    }

    if(!IsCoreCompilation() && IsAsyncAllocationDisable()) {
        sprintf(tmpcode,"// This code is generated for Asynchronous Parallel Object Allocation support for the object %s\n", name);
        code.InsertAt(-1,tmpcode,strlen(tmpcode));

        int nb_of_methods = memberList.GetSize();
        for(int i = 0; i < nb_of_methods; i++) {


            if(memberList[i]->Type() != TYPE_METHOD || memberList[i]->GetMyAccess() != PUBLIC) {
                continue;
            }

            Method *met = (Method *)memberList[i];
            if(met->MethodType() == METHOD_CONSTRUCTOR) {

                Constructor *cons = dynamic_cast<Constructor*>(met);
                cons->set_id(constrcutor_id++);


                sprintf(tmpcode,"extern \"C\"\n{\n  void* %s_AllocatingThread%d(void* arg);\n}\n\n", name, cons->get_id());
                code.InsertAt(-1,tmpcode,strlen(tmpcode));

                sprintf(tmpcode, "typedef struct pthread_args%d\n{\n  %s* ptr_interface;\n", cons->get_id(), name);
                code.InsertAt(-1, tmpcode, strlen(tmpcode));

                int nb = (*met).params.GetSize();
                for(int j=0; j<nb; j++)  {
                    sprintf(tmpcode, "  ");
                    Param &p=*((*met).params[j]);
                    p.DeclareParam(tmpcode, false);
                    strcat(tmpcode, ";\n");
                    code.InsertAt(-1,tmpcode,strlen(tmpcode));
                }

                sprintf(tmpcode, "} pthread_args_t_%d;\n\n", cons->get_id());
                code.InsertAt(-1, tmpcode, strlen(tmpcode));
            }
        }
    }

    int n = memberList.GetSize();
    for(int i=0; i<n; i++) {
        if(memberList[i]->Type() != TYPE_METHOD || memberList[i]->GetMyAccess() != PUBLIC) {
            continue;
        }

        Method *met = (Method *)memberList[i];
        if(pureVirtual && met->MethodType() == METHOD_CONSTRUCTOR && IsCoreCompilation()) {
            continue;
        }

        met->GenerateClient(code);
    }

    if(noConstructor && !pureVirtual) {
        constructor.GenerateClient(code);
    }


    if(is_collective()) {
        sprintf(tmpcode, "\nvoid %s::construct_remote_object() {\n  switch(_popc_selected_constructor_id) {", GetName());
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
        int n = memberList.GetSize();
        for(int i=0; i<n; i++) {
            if(memberList[i]->Type() == TYPE_METHOD) {
                Method* m = dynamic_cast<Method*>(memberList[i]);
                if(m->MethodType() == METHOD_CONSTRUCTOR) {
                    Constructor* c = dynamic_cast<Constructor*>(memberList[i]);
                    sprintf(tmpcode, "\n  case %d:", (*c).id);
                    code.InsertAt(-1, tmpcode, strlen(tmpcode));
                    strcpy(tmpcode, "\n    _popc_constructor(");
                    code.InsertAt(-1, tmpcode, strlen(tmpcode));
                    int nb = (*c).params.GetSize();
                    for(int j=0; j<nb; j++)  {
                        Param &p = *((*c).params[j]);
                        sprintf(tmpcode, "_popc_constructor_%d_%s", (*c).id, p.GetName());
                        if(j < nb-1) {
                            strcat(tmpcode, ", ");
                        }
                        code.InsertAt(-1, tmpcode, strlen(tmpcode));
                    }
                    strcpy(tmpcode, ");\n    break;");
                    code.InsertAt(-1, tmpcode, strlen(tmpcode));
                }
            }
        }
        strcpy(tmpcode, "\n  }\n}");
        code.InsertAt(-1, tmpcode, strlen(tmpcode));

        sprintf(tmpcode, "\%s& %s::operator[] (const int index) {\n  set_default_rank(index);\n  return (*this);\n}\n", GetName(), GetName());
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
    }

    char *fname = GetCodeFile()->GetFileName();
    if(endline > 0 && fname != NULL) {
        sprintf(tmpcode,"\n# %d \"%s\"\n", endline, fname);
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
    }
    return true;
}

unsigned Class::IDFromString(char *str) {
    char tmp[256];
    int n=0;
    int len=strlen(str);
    int starta=('Z'-'A')+1;
    for(int i=0; i<len && i<256; i++,str++) {
        if(*str>='A' && *str>='Z') {
            tmp[n++]=(*str)-'A';
        } else if(*str>='a' && *str>='z') {
            tmp[n++]=(*str)-'a'+starta;
        } else if(*str=='_') {
            tmp[n++]=2*starta;
        } else if(*str>='0' && *str<='9') {
            tmp[n++]=(*str)-'0'+2*starta+1;
        }
    }

    unsigned sz=2*starta+11;
    n--;
    unsigned id=tmp[n];
    for(int i=0; i<n; i++) {
        id=id*sz+tmp[i];
    }
    return id+MIN_CLASSID;

}

bool Class::generate_broker_header_pog(CArrayChar &code) {
    int i;
    char str[1024];
    char tmpcode[10240];
    char brokername[256];
    char *outfile = GetCodeFile()->GetOutputName();

    // Print a comment in the generated code
    sprintf(tmpcode, "\n// Generate broker-side code for a POG\n");
    code.InsertAt(-1, tmpcode, strlen(tmpcode));

    if(outfile != NULL) {
        int lines = CountCodeLines(code);
        sprintf(tmpcode, "\n# %d \"%s\"\n", lines+3, outfile);
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
    }

    // Prepare broker name
    sprintf(brokername, "%s%s", name, Class::POG_BROKER_POSTFIX);

    int n = baseClass.GetSize();
    if(n == 0) {
        sprintf(tmpcode,"\n\nclass %s: virtual public %s", brokername, Class::POG_BASE_BROKER_NAME);
    } else {
        sprintf(tmpcode,"\n\nclass %s: ", brokername);
        for(i = 0; i < n; i++) {
            if(baseClass[i]->baseVirtual) {
                strcat(tmpcode, "virtual ");
            }
            strcat(tmpcode, "public ");
            strcat(tmpcode, baseClass[i]->base->GetName());
            strcat(tmpcode, POG_BASE_BROKER_NAME);
            if(i < n-1) {
                strcat(tmpcode,", ");
            }
        }
    }
    sprintf(str,"\n{\npublic:\n  %s();\n  virtual bool invoke(unsigned method[3],  paroc_buffer &_popc_buffer, paroc_connection *_popc_connection);", brokername);
    strcat(tmpcode,str);

    strcat(tmpcode,"\nprotected:");
    code.InsertAt(-1,tmpcode,strlen(tmpcode));

    n=memberList.GetSize();
    for(i = 0; i < n; i++) {
        if(memberList[i]->GetMyAccess() != PUBLIC || memberList[i]->Type() != TYPE_METHOD) {
            continue;
        }
        Method &met=*((Method *)memberList[i]);
        if(pureVirtual && met.MethodType() == METHOD_CONSTRUCTOR && IsCoreCompilation()) {
            continue;
        }
        met.generate_broker_header_pog(code);
    }

    /* In the current version a constructor is mandatory so no need for this.
      if (noConstructor && !pureVirtual) {
        constructor.GenerateBrokerHeader(code);
    }*/

    sprintf(tmpcode,"\npublic:\n  static POPC_GroupBroker *_init();\n  static POPC_GroupBrokerFactory _popc_factory;\n");
    code.InsertAt(-1, tmpcode, strlen(tmpcode));
    strcpy(str,"\n}\n;");
    code.InsertAt(-1,str,strlen(str));

    char *fname = GetCodeFile()->GetFileName();
    if(endline > 0 && fname != NULL) {
        sprintf(str, "\n# %d \"%s\"\n", endline, fname);
        code.InsertAt(-1, str, strlen(str));
    }
    return true;
}

bool Class::generate_header_pog(CArrayChar &code, bool interface) {
    char tmpcode[10240];
    char str[1024];
    char *fname = GetCodeFile()->GetFileName();
    if(startline > 0 && fname != NULL) {
        sprintf(str, "\n# %d \"%s\"\n", startline, fname);
        code.InsertAt(-1, str, strlen(str));
    }

    if(interface) {
        sprintf(tmpcode, "\n// Generated code for the interface-side of a POG\n");
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
    } else {
        sprintf(tmpcode, "\n// Generated code for the object-side of a POG\n");
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
    }

    strcpy(str, name);

    if(!interface) {
        strcat(str, POG_OBJECT_POSTFIX);
    }

    sprintf(tmpcode, "class %s ", str);
    int n = baseClass.GetSize();
    strcat(tmpcode, " :");

    int i;

    for(i = 0; i < n; i++) {
        BaseClass &base = *(baseClass[i]);
        if(base.baseVirtual) {
            strcat(tmpcode,"virtual ");
        }
        if(base.type == PUBLIC) {
            strcat(tmpcode, "public ");
        } else if(base.type == PROTECTED) {
            strcat(tmpcode, "protected ");
        } else {
            strcat(tmpcode, "private ");
        }
        strcat(tmpcode, base.base->GetName());
        if(!interface) {
            strcat(tmpcode, POG_OBJECT_POSTFIX);
        }
        if(i<n-1) {
            strcat(tmpcode, ", ");
        }
    }
    if(n) {
        strcat(tmpcode,"\n{\npublic:");
    } else if(interface) {
        sprintf(str," virtual public %s\n{\npublic: ", Class::POG_BASE_INTERFACE_NAME);
        strcat(tmpcode, str);
    } else {
        sprintf(str," virtual public %s\n{\npublic:", POG_BASE_OBJECT_NAME);
        strcat(tmpcode, str);
    }

    code.InsertAt(-1,tmpcode,strlen(tmpcode));
    *tmpcode=0;

    //Generate members
    const char *accessstr[3] = {"\npublic:", "\nprotected:", "\nprivate:"};
    AccessType currentaccess = PUBLIC;
    n = memberList.GetSize();

    for(i = 0; i < n; i++) {
        if(interface && memberList[i]->GetMyAccess() != PUBLIC) {
            continue;
        }

        if(memberList[i]->GetMyAccess() != currentaccess) {
            currentaccess = memberList[i]->GetMyAccess();
            code.InsertAt(-1, accessstr[currentaccess], strlen(accessstr[currentaccess]));
        }

        memberList[i]->generate_header_pog(code, interface);
    }

    if(interface) {
        sprintf(str,"\npublic:\n  virtual void construct_remote_object();");
        code.InsertAt(-1, str, strlen(str));

        //sprintf(str,"\n  void _popc_constructor();", name);
        //code.InsertAt(-1, str, strlen(str));

        sprintf(str, "\n  virtual char* get_class_name() { return (char*)\"%s\"; };\n", name);
        code.InsertAt(-1, str, strlen(str));

        sprintf(str, "\n  %s& operator[] (const int index);\n", name);
        code.InsertAt(-1, str, strlen(str));

        /*int n=baseClass.GetSize();
        if (n)
        {
            CArrayClass bases;
            bases.SetSize(n);
            for (int i=0;i<n;i++)  bases[i]=baseClass[i]->base;
            CodeFile *prog=GetCodeFile();
            prog->FindAllBaseClass(*this, bases,true);

            n=bases.GetSize();
            strcpy(tmpcode," : ");
            for (int j=0;j<n;j++)
            {
                strcat(tmpcode,bases[j]->GetName());
                if (j<n-1) strcat(tmpcode,"(_paroc_nobind) ,");
                else  strcat(tmpcode,"(_paroc_nobind)");
            }
            code.InsertAt(-1,tmpcode,strlen(tmpcode));
        }

        strcpy(str," { Bind(p); };\n");
        code.InsertAt(-1,str,strlen(str));


        if (noConstructor && !pureVirtual)
        { constructor.GenerateHeader(code, interface); }

        //Generate constructor from the interface binding
        sprintf(str,"\n%s(const %s &inf)",name, my_interface_base);
        code.InsertAt(-1,str,strlen(str));
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
        strcpy(str," { SetOD(inf.GetOD()); Bind(inf.GetAccessPoint()); };\n");
        code.InsertAt(-1,str,strlen(str));

        //Generate constructor from the object side binding
        sprintf(str,"\n%s(const paroc_object *obj)",name);
        code.InsertAt(-1,str,strlen(str));
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
        strcpy(str," { Bind(obj->GetAccessPoint());};\n");
        code.InsertAt(-1,str,strlen(str));*/

        sprintf(str,"\n  ~%s() {};",name);
        code.InsertAt(-1, str, strlen(str));

        n = memberList.GetSize();
        for(i = 0; i < n; i++) {
            if(memberList[i]->Type() == TYPE_METHOD) {
                Method* m = dynamic_cast<Method*>(memberList[i]);
                if(m->MethodType() == METHOD_CONSTRUCTOR) {
                    Constructor* t = dynamic_cast<Constructor*>(memberList[i]);
                    int nb = (*t).params.GetSize();
                    for(int j = 0; j < nb; j++) {
                        Param &p = *((*t).params[j]);
                        sprintf(str, "\n  %s _popc_constructor_%d_%s;\n", p.GetType()->GetName(), (*t).id, p.GetName());
                        code.InsertAt(-1, str, strlen(str));
                    }
                }
            }
        }
    }

    strcpy(str,"\n};\n");
    code.InsertAt(-1,str, strlen(str));

    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        code.InsertAt(-1,str,strlen(str));
    }

    return true;
}

bool Class::GenerateHeader(CArrayChar &code, bool interface/*, bool isPOPCPPCompilation*/) {
    char tmpcode[10240];
    char str[1024];

    char *fname=GetCodeFile()->GetFileName();
    if(startline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",startline,fname);
        code.InsertAt(-1,str,strlen(str));
    }

    strcpy(str,name);

    if(!interface) {
        strcat(str, OBJ_POSTFIX);
    }

    sprintf(tmpcode,"class %s ",str);
    int n=baseClass.GetSize();
    strcat(tmpcode," :");

    int i;

    for(i=0; i<n; i++) {
        BaseClass &base=*(baseClass[i]);
        if(base.baseVirtual) {
            strcat(tmpcode,"virtual ");
        }
        if(base.type==PUBLIC) {
            strcat(tmpcode,"public ");
        } else if(base.type==PROTECTED) {
            strcat(tmpcode,"protected ");
        } else {
            strcat(tmpcode,"private ");
        }

        strcat(tmpcode,base.base->GetName());
        if(!interface) {
            strcat(tmpcode, OBJ_POSTFIX);
        }
        if(i<n-1) {
            strcat(tmpcode,", ");
        }
    }
    if(n) {
        strcat(tmpcode,"\n{\npublic:");
    } else if(interface) {
        sprintf(str," virtual public %s\n{\npublic:", my_interface_base);
        strcat(tmpcode, str);
    } else {
        sprintf(str," virtual public %s\n{\npublic:", my_object_base);
        strcat(tmpcode, str);
    }

    code.InsertAt(-1,tmpcode,strlen(tmpcode));
    *tmpcode=0;

    //Generate members
    const char *accessstr[3]= {"\npublic:","\nprotected:","\nprivate:"};
    AccessType currentaccess=PUBLIC;
    n=memberList.GetSize();

    for(i=0; i<n; i++) {
        if(interface && memberList[i]->GetMyAccess()!=PUBLIC) {
            continue;
        }

        if(memberList[i]->GetMyAccess()!=currentaccess) {
            currentaccess=memberList[i]->GetMyAccess();
            code.InsertAt(-1,accessstr[currentaccess],strlen(accessstr[currentaccess]));
        }

        if(memberList[i]->Type()==TYPE_METHOD) {
            Method *t=(Method *)memberList[i];
            if(t->MethodType()==METHOD_CONSTRUCTOR) {
                //if ( ((Constructor *)t)->isDefault()) defaultconstructor=true;
                /*PEKA Removed */ //if (interface && pureVirtual) continue;
            }
        }

        memberList[i]->GenerateHeader(code,interface);
    }

    //Add the declaration of the __POPThis variable for support of the "this" keyword
    sprintf(str,"\n%s* __POPThis_%s; \n", name, name);
    code.InsertAt(-1,str,strlen(str));

    sprintf(str,"void AllocateObject();\n");
    code.InsertAt(-1,str,strlen(str));

    if(interface) {

        sprintf(str,"\npublic:\nvirtual const char *ClassName() { return \"%s\"; };",name);
        code.InsertAt(-1,str,strlen(str));




        //Generate constructor from paroc_accesspoint...
        sprintf(str,"\npublic:\n%s(const paroc_accesspoint &p)",name);
        code.InsertAt(-1,str,strlen(str));

        int n=baseClass.GetSize();
        if(n) {
            CArrayClass bases;
            bases.SetSize(n);
            for(int i=0; i<n; i++) {
                bases[i]=baseClass[i]->base;
            }
            CodeFile *prog=GetCodeFile();
            prog->FindAllBaseClass(*this, bases,true);

            n=bases.GetSize();
            strcpy(tmpcode," : ");
            for(int j=0; j<n; j++) {
                strcat(tmpcode,bases[j]->GetName());
                if(j<n-1) {
                    strcat(tmpcode,"(_paroc_nobind) ,");
                } else {
                    strcat(tmpcode,"(_paroc_nobind)");
                }
            }
            code.InsertAt(-1,tmpcode,strlen(tmpcode));
        }

        strcpy(str," { Bind(p); };\n");
        code.InsertAt(-1,str,strlen(str));

        //If no constructor, generate default for interface...
        if(noConstructor /*PEKA Removed */ && !pureVirtual) {
            constructor.GenerateHeader(code, interface);
        }

        //Generate constructor from the interface binding
        sprintf(str,"\n%s(const %s &inf)",name, my_interface_base);
        code.InsertAt(-1,str,strlen(str));
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
        strcpy(str," { SetOD(inf.GetOD()); Bind(inf.GetAccessPoint()); };\n");
        code.InsertAt(-1,str,strlen(str));

        //Generate constructor from the object side binding
        sprintf(str,"\n%s(const paroc_object *obj)",name);
        code.InsertAt(-1,str,strlen(str));
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
        strcpy(str," { Bind(obj->GetAccessPoint());};\n");
        code.InsertAt(-1,str,strlen(str));

        sprintf(str,"\n~%s() {};",name);
        code.InsertAt(-1,str,strlen(str));

        /*  if(!IsCoreCompilation()){
                // Generate method declaration for asynchronous object creation
                sprintf(str,"void %s_AsynchronousAllocation();\n", name);
                code.InsertAt(-1,str,strlen(str));
            }*/


//       if (!defaultconstructor && interface)
//  {
//    sprintf(str,"\n\t%s ()",name);
//    code.InsertAt(-1,str,strlen(str));
//    if (n)
//      {
//        code.InsertAt(-1,tmpcode,strlen(tmpcode));
//      }
//    code.InsertAt(-1," {};\n",5);
//  }
    }
    strcpy(str,"\n};\n");
    code.InsertAt(-1,str, strlen(str));



    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        code.InsertAt(-1,str,strlen(str));
    }



    return true;
}

bool Class::GenerateBrokerHeader(CArrayChar &code/*, bool isPOPCPPCompilation*/) {
    int i;
    char str[1024];
    char tmpcode[10240];
    char brokername[256];

    if(is_collective()) {
        sprintf(tmpcode, "\n//Generating broker-side of a POG\n");
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
    }

    char *outfile = GetCodeFile()->GetOutputName();
    if(outfile != NULL) {
        int lines = CountCodeLines(code);
        sprintf(tmpcode, "\n# %d \"%s\"\n", lines+3, outfile);
        code.InsertAt(-1, tmpcode, strlen(tmpcode));
    }
    sprintf(brokername,"%s%s",name, Class::POG_BROKER_POSTFIX);

    int n=baseClass.GetSize();
    if(n==0) {
        sprintf(tmpcode,"\n\nclass %s: virtual public %s",brokername, my_broker_base);
    } else {
        sprintf(tmpcode,"\n\nclass %s: ",brokername);
        for(i=0; i<n; i++) {
            if(baseClass[i]->baseVirtual) {
                strcat(tmpcode,"virtual ");
            }
            strcat(tmpcode,"public ");
            strcat(tmpcode, baseClass[i]->base->GetName());
            strcat(tmpcode, Class::POG_BROKER_POSTFIX);
//          strcat(tmpcode, "Broker");
            if(i<n-1) {
                strcat(tmpcode,", ");
            }
        }
    }
    sprintf(str,"\n{\npublic:\n%s();\nvirtual bool Invoke(unsigned method[3],  paroc_buffer &__brokerbuf, paroc_connection *peer);", brokername);
    strcat(tmpcode,str);

    strcat(tmpcode,"\nprotected:");
    code.InsertAt(-1,tmpcode,strlen(tmpcode));

    n=memberList.GetSize();
    for(i=0; i<n; i++) {
        if(memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) {
            continue;
        }
        Method &met=*((Method *)memberList[i]);
        if(pureVirtual && met.MethodType()==METHOD_CONSTRUCTOR /* LAST MODIFICATION */ && IsCoreCompilation()) {
            continue;
        }
        met.GenerateBrokerHeader(code);
    }

    if(noConstructor && !pureVirtual) {
        constructor.GenerateBrokerHeader(code);
    }

    sprintf(tmpcode,"\npublic:\nstatic paroc_broker *_init();\nstatic paroc_broker_factory _popc_factory;\n");
    code.InsertAt(-1,tmpcode,strlen(tmpcode));


    strcpy(str,"\n}\n;");

    code.InsertAt(-1,str,strlen(str));

    char *fname=GetCodeFile()->GetFileName();
    if(endline>0 && fname!=NULL) {
        sprintf(str,"\n# %d \"%s\"\n",endline,fname);
        code.InsertAt(-1,str,strlen(str));
    }
    return true;
}

bool Class::GenerateBroker(CArrayChar &code/*, bool isPOPCPPCompilation*/) {
    // Generate Broker-derived class for creation objects and the re-implementation of

    int i;
    char str[10240];
    char tmpcode[10240];
    char brokername[256];


    if(is_collective()) {
        sprintf(tmpcode, "\n// Generating code implementing the broker of a POG\n");
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
    }


    CodeFile *codefile=GetCodeFile();

    char *outfile = codefile->GetOutputName();
    if(outfile != NULL) {
        int lines = CountCodeLines(code);
        sprintf(tmpcode, "\n# %d \"%s\"\n", lines+3, outfile);
        code.InsertAt(-1,tmpcode,strlen(tmpcode));
    }


    sprintf(brokername,"%s%s", name, Class::POG_BROKER_POSTFIX);

    //now...the implementation....

    // Generate broker::Invoke virtual method
    if(is_collective()) {
        sprintf(str,"\nbool %s::invoke(unsigned method[3], paroc_buffer &_popc_buffer, paroc_connection *_popc_connection) {\n if (*method == CLASSUID_%s) {\n    switch(method[1]) {",brokername,name);
    } else {
        sprintf(str,"\nbool %s::Invoke(unsigned method[3], paroc_buffer &__brokerbuf, paroc_connection *peer)\n{\n if (*method==CLASSUID_%s) {\n    switch(method[1])\n{",brokername,name);
    }
    code.InsertAt(-1,str,strlen(str));

    char methodinfo[10240];
    char methodcount = 0;
    char *methodinfoptr = methodinfo;
    *methodinfoptr = 0;

    int n = memberList.GetSize();
    for(i = 0; i < n; i++) {
        if(memberList[i]->GetMyAccess()!=PUBLIC || memberList[i]->Type()!=TYPE_METHOD) {
            continue;
        }
        Method &met=*((Method *)memberList[i]);

        int t=met.MethodType();
        if(t==METHOD_DESTRUCTOR  || met.isHidden /* LAST MODIFICATION */|| (pureVirtual && t==METHOD_CONSTRUCTOR && IsCoreCompilation()) || (met.isVirtual && methodInBaseClass(met))) {
            continue;
        }
        if(is_collective()) {
            sprintf(str,"\n      case %d: Invoke_%s_%d(_popc_buffer, _popc_connection);\n        return true;", met.id, met.name, met.id);
        } else {
            sprintf(str,"\n    case %d: Invoke_%s_%d(__brokerbuf, peer); return true;", met.id, met.name, met.id);
        }
        code.InsertAt(-1,str,strlen(str));

//Collect method id, name
        if(methodcount) {
            sprintf(methodinfoptr,",{%d,(char*)\"%s\"}",met.id,met.name);
        } else {
            sprintf(methodinfoptr,"{%d,(char*)\"%s\"}",met.id,met.name);
        }
        methodcount++;
        methodinfoptr+=strlen(methodinfoptr);
    }
    if(noConstructor && !pureVirtual) {
        sprintf(str,"\ncase %d: Invoke_%s_%d(__brokerbuf, peer); return true;",constructor.id, constructor.name,constructor.id);
        code.InsertAt(-1,str,strlen(str));

        if(methodcount) {
            sprintf(methodinfoptr,",{%d,(char*)\"%s\"}",constructor.id,constructor.name);
        } else {
            sprintf(methodinfoptr,"{%d,(char*)\"%s\"}",constructor.id,constructor.name);
        }
        methodcount++;
    }

    strcpy(str,"\n    default:\n      return false;\n    }\n  }");
    code.InsertAt(-1,str,strlen(str));

    n=baseClass.GetSize();
    for(i=0; i<n; i++) {
        sprintf(str,"\nelse if (%s%s::Invoke(method,__brokerbuf,peer)) return true;", baseClass[i]->base->GetName(), Class::POG_BROKER_POSTFIX);
        code.InsertAt(-1,str,strlen(str));
    }
    if(n) {
        strcpy(str,"\nreturn false;\n}");
    } else {
        if(is_collective()) {
            strcpy(str,"\n  return POPC_GroupBroker::invoke(method, _popc_buffer, _popc_connection);\n}\n");
        } else {
            strcpy(str,"\nreturn paroc_broker::Invoke(method,__brokerbuf,peer);\n}\n");
        }
    }

    code.InsertAt(-1,str,strlen(str));




    // Generate default constructor
    if(is_collective()) {
        sprintf(str,"\n%s::%s()\n{\n  static popc_method_info _popc_minfo[%d] = { %s };\n  add_method_info(CLASSUID_%s, _popc_minfo, %d);\n}\n", brokername, brokername, methodcount, methodinfo, name, methodcount);
    } else {
        sprintf(str,"\n%s::%s()\n{\nstatic paroc_method_info _paroc_minfo[%d]={%s};\nAddMethodInfo(CLASSUID_%s, _paroc_minfo, %d);\n}", brokername, brokername, methodcount, methodinfo, name, methodcount);
    }
    code.InsertAt(-1,str,strlen(str));

    // Generate code for Invoke_xxx(...) to invoke object's method
    n = memberList.GetSize();
    for(i = 0; i < n; i++) {
        if(memberList[i]->GetMyAccess() != PUBLIC || memberList[i]->Type() != TYPE_METHOD) {
            continue;
        }

        Method &met = *((Method *)memberList[i]);
        int t = met.MethodType();
        if(t == METHOD_DESTRUCTOR || met.isHidden || (pureVirtual && t == METHOD_CONSTRUCTOR && IsCoreCompilation()) || (met.isVirtual && methodInBaseClass(met))) {
            continue;
        }
        met.GenerateBroker(code);
    }

    // Generate default constructor stubs
    if(noConstructor) {
        constructor.GenerateBroker(code);
    }

    if(is_collective()) {
        sprintf(tmpcode,"\nPOPC_GroupBroker* %s::_init() { return new %s; }\nPOPC_GroupBrokerFactory %s::_popc_factory(_init, \"%s\");\n",brokername, brokername, brokername, name);
    } else {
        sprintf(tmpcode,"\nparoc_broker *%s::_init() { return new %s; }\nparoc_broker_factory %s::_popc_factory(_init, \"%s\");\n",brokername, brokername, brokername, name);
    }
    code.InsertAt(-1,tmpcode,strlen(tmpcode));

    char *fname = GetCodeFile()->GetFileName();
    if(endline > 0 && fname != NULL) {
        sprintf(str, "\n# %d \"%s\"\n", endline, fname);
        code.InsertAt(-1,str,strlen(str));
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
 * Disable the asynchronous parallel object allocation mechanism.
 * @return void
 */
void Class::DisableAsyncAllocation() {
    isAsyncAllocationDisable = true;
}

/**
 * Check if asynchronous parallel object allocation is disable
 * @return TRUE if asynchronous allocation is disable. FALSE otherwise.
 */
bool Class::IsAsyncAllocationDisable() {
    return isAsyncAllocationDisable;
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

