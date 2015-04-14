/**
 * File : classmember.cc
 * Author : Tuan Anh Nguyen
 * Description : Generate source code for the broker of parallel objects
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * P.Kuonen     June 2011   Modify to print all exceptions raised in methods
 * clementval   March 2012  Add Enum, Struct support
 * clementval   August 2012 Add asynchronous parallel object allocation (APOA) support
 * vanhieu      July 2013       Modify line #925
 */

#include <deque>

#include "popc_intface.h"

#include "parser.h"
#include "pop_utils.h"

#define MIN_CLASSID 1000

//Begin Param implementation

Param::Param(DataType *ptype) {
    name[0]=0;
    mytype=ptype;

    paramSize=marshalProc=defaultVal=nullptr;
    isVoid=isArray=isRef=isConst=isInput=isOutput=false;
}

Param::Param() {
    name[0]=0;
    mytype=nullptr;

    paramSize=marshalProc=defaultVal=nullptr;
    isVoid=isArray=isRef=isConst=isInput=isOutput=false;
}

Param::~Param() {
    if(paramSize!=nullptr) {
        free(paramSize);
    }
    if(marshalProc!=nullptr) {
        free(marshalProc);
    }
    if(defaultVal!=nullptr) {
        free(defaultVal);
    }
}

bool Param::Match(Param *p) {
    return (pop_utils::isEqual(name,p->GetName()));
}

bool Param::InParam() {
    if(isInput || isConst) {
        return true;
    }
    if(isOutput) {
        return false;
    }
    return true;
}

bool Param::OutParam() {
    if(isConst) {
        return false;
    }
    if(isOutput) {
        return true;
    }
    if(isInput) {
        return false;
    }
    return (isRef || IsPointer() || mytype->IsArray());
}

bool Param::IsPointer() {
    return (mytype->IsPointer()>0);
}

bool Param::IsRef() {
    return isRef;
}

bool Param::IsConst() {
    return isConst;
}

bool Param::IsArray() {
    return isArray;
}

bool Param::IsVoid() {
    return isVoid;
}

void Param::SetType(DataType *type) {
    mytype=type;
}

DataType *Param::GetType() {
    return mytype;
}

char *Param::GetName() {
    return name;
}

char *Param::GetDefaultValue() {
    return defaultVal;
}

int  Param::GetAttr() {
    return attr;
}

bool Param::CanMarshal() {
    if(mytype==nullptr) {
        return false;
    }
    int stat=mytype->CanMarshal();
    if(marshalProc!=nullptr || stat==1 || (stat==2 && paramSize!=nullptr)) {
        return true;
    }
    return false;

}

bool Param::DeclareParam(char *output, bool header) {
    if(mytype == nullptr) {
        return false;
    }
    if(isConst) {
        strcpy(output,"const ");
        output+=strlen(output);
    }
    char tmpvar[1024];

    if(isRef) {
        snprintf(tmpvar,sizeof(tmpvar),"&%s", name);
    } else if(isArray) {
        snprintf(tmpvar,sizeof(tmpvar),"%s", name);
    } else {
        strcpy(tmpvar,name);
    }

    if(!mytype->GetDeclaration(tmpvar, output)) {
        return false;
    }
    if(defaultVal!=nullptr && header) {
        strcat(output,"=");
        strcat(output,defaultVal);
    }
    return true;
}

bool Param::DeclareVariable(char *output, bool &reformat, bool allocmem) {
    if(mytype==nullptr) {
        return false;
    }
    if(isVoid) {
        return false;
    }

    int nptr=mytype->IsPointer();
    if(nptr==1 && paramSize==nullptr) {
        DataType *base=mytype->GetBaseType();
        assert(base!=nullptr);
        if(!base->GetDeclaration(name, output)) {
            return false;
        }
        if(base->IsParClass()) {
            strcat(output,"(pop_interface::_pop_nobind)");
        }
        strcat(output,";\n");
        reformat=true;
    } else {
        if(!mytype->GetDeclaration(name, output)) {
            return false;
        }
        if(mytype->IsParClass()) {
            strcat(output,"(pop_interface::_pop_nobind)");
        }
        reformat=false;
        strcat(output,";\n");

        //Check and allocate memory....
        if(allocmem && paramSize!=nullptr && nptr) {
            char decl[1024];
            DataType *base=mytype->GetBaseType();
            assert(base!=nullptr);
            char basetype[1024];
            base->GetDeclaration(nullptr,basetype);

            if(nptr==1 && base->IsParClass()) {
                snprintf(decl, sizeof(decl), "pop_interface_container<%s> __pop_container_%s(%s);\n%s =__pop_container_%s;\n", basetype,name,paramSize,name,name);
            } else {
                char tmpstr[1024];
                strcpy(tmpstr,base->GetName());
                for(int i=1; i<nptr; i++) {
                    strcat(tmpstr,"*");
                }
                snprintf(decl, sizeof(decl), "pop_container<%s> __pop_container_%s(%s);\n%s=__pop_container_%s;\n", tmpstr,name ,paramSize,   name, name);

            }
            strcat(output,decl);
        }
    }
    return true;
}

bool Param::DeclareVariable(char *output) {
    if(mytype==nullptr) {
        return false;
    }

    char tmpvar[1024];
    if(isRef&&!GetType()->IsParClass()) {
        sprintf(tmpvar,"&%s", name);
    } else {
        strcpy(tmpvar,name);
    }

    if(mytype->GetDeclaration(tmpvar, output)) {
        strcat(output,";\n");
        return true;
    }
    return false;
}

bool Param::Marshal(char *bufname, bool reformat,bool inf_side, std::string &output) {
    if(mytype==nullptr) {
        return false;
    }

    char tmpvar[1024];
    if(isConst) {
        *tmpvar=0;
//             *tmpvar='(';
//       mytype->GetCastType(tmpvar+1);
//       if (isRef) strcat(tmpvar,"&");
//       strcat(tmpvar,")");
    } else {
        *tmpvar=0;
    }

    if(reformat) {
        strcat(tmpvar,"&");
    }

    strcat(tmpvar,name);

    int flags=(inf_side)? FLAG_INPUT : 0;
    flags|=FLAG_MARSHAL;

    char sizeinfo[1024];
    *sizeinfo=0;

    if(paramSize!=nullptr && !reformat) {
        char decl[1024];
        sprintf(decl, "int __pop_size1_%s=%s;\n%s.Push(\"%sSize\",\"int\",1);\n%s.Pack(& __pop_size1_%s,1);\n%s.Pop();\n",name,paramSize,bufname, name, bufname,name, bufname);
        sprintf(sizeinfo,"__pop_size1_%s",name);

        output += decl;
    }

    if(marshalProc!=nullptr) {
        char tmpcode[1024];
        sprintf(tmpcode,"%s(%s,%s, %s, %d, 0);\n",marshalProc,bufname,tmpvar, (*sizeinfo==0)? "0" : sizeinfo,flags);
        output += tmpcode;
    } else {
        mytype->Marshal(tmpvar,bufname,(*sizeinfo==0)? nullptr : sizeinfo,output);
    }
    return true;
}

bool Param::UnMarshal(char *bufname, bool reformat, bool alloc_mem, bool inf_side, std::string &output) {
    if(mytype==nullptr) {
        return false;
    }

    int flags=(inf_side)? 0: FLAG_INPUT;

    char tmpvar[1024];

    *tmpvar=0;
    if(reformat) {
        strcat(tmpvar,"&");
    }
    strcat(tmpvar,name);

    char sizeinfo[1024];
    *sizeinfo=0;

    if(paramSize!=nullptr && !reformat) {
        char decl[1024];
        sprintf(decl, "int __pop_size2_%s;\n%s.Push(\"%sSize\",\"int\",1);\n \n%s.UnPack(& __pop_size2_%s,1);\n%s.Pop();\n",name,bufname, name, bufname,name, bufname);

        sprintf(sizeinfo,"__pop_size2_%s",name);

        output += decl;

        //check to alloc the memory
        int nptr=mytype->IsPointer();
        if(alloc_mem && nptr) {
            char alloccode[1024];
            DataType *base=mytype->GetBaseType();
            assert(base!=nullptr);
            char basetype[1024];
            base->GetDeclaration(nullptr,basetype);

            if(nptr==1 && base->IsParClass()) {
                sprintf(alloccode, "pop_interface_container<%s> __pop_container_%s(__pop_size2_%s);\n %s=__pop_container_%s;\n", basetype,name,name,name, name);
            } else {
                //        sprintf(alloccode, "pop_container<typeof(*%s)> __pop_container_%s(%s,__pop_size2_%s);\n", name,name,name,name);
                char tmpstr[1024];
                strcpy(tmpstr,base->GetName());
                for(int i=1; i<nptr; i++) {
                    strcat(tmpstr,"*");
                }
                sprintf(alloccode, "pop_container<%s> __pop_container_%s(__pop_size2_%s);\n%s=__pop_container_%s;\n", tmpstr,name,name,name,name);
            }
            output += alloccode;
        }
    }
    if(marshalProc!=nullptr) {
        char tmpcode[1024];

        sprintf(tmpcode,"%s(%s,%s,%s,%d,%s);",marshalProc,bufname,tmpvar, (*sizeinfo==0)?  "0" : sizeinfo,flags,(inf_side ? "0" : "&_internal_mem"));
        output += tmpcode;
    } else {
        mytype->DeMarshal(tmpvar,bufname,(*sizeinfo==0)? nullptr : sizeinfo,output);
    }

    return true;
}

bool Param::UserProc(char *output) {
    if(mytype==nullptr) {
        return false;
    }

    *output=0;

    if(marshalProc==nullptr) {
        return false;
    }

    char decl[1024];

    mytype->GetDeclaration("param",decl);
    sprintf(output,"void %s(pop_buffer &buf, %s, int hint,  bool marshal);" , marshalProc, decl);
    return true;
}
//END Param implementation



//BEGIN OD - object description class
ObjDesc::ObjDesc() {
    odstr=nullptr;
}
ObjDesc::~ObjDesc() {
    if(odstr!=nullptr) {
        free(odstr);
    }
}

void ObjDesc::Generate(char *code) {
    code[0]=0;
    if(odstr == nullptr) {
        return;
    }
    strcpy(code, "\n  ");
    strcat(code, odstr);
}

void ObjDesc::SetCode(char *code) {
    if(odstr!=nullptr) {
        free(odstr);
    }
    odstr=(code==nullptr)? nullptr : popc_strdup(code);
}

//END ObjectDesc - object description class

// BEGIN ClassMember class implementation....
ClassMember::ClassMember(Class *cl, AccessType myaccess) {
    accessType=myaccess;
    myclass=cl;
    line=-1;
}

ClassMember::~ClassMember() {
}


AccessType ClassMember::GetMyAccess() {
    return accessType;
}

Class * ClassMember::GetClass() {
    return myclass;
}

void ClassMember::SetLineInfo(int linenum) {
    line=linenum;
}

void ClassMember::GenerateClient(std::string& /*output*/) {
}

void ClassMember::generate_header_pog(std::string &output, bool interface) {
    GenerateHeader(output, interface);
}

void ClassMember::GenerateHeader(std::string& output, bool /*interface*/) {
    char *fname;
    if(line>0 && (fname=myclass->GetFileInfo())!=nullptr) {
        char str[1024];
        sprintf(str,"\n# %d \"%s\"\n", line, fname);
        output += str;
    }

}

// END of ClassMember implementation

// Implement Attribute class
Attribute::Attribute(Class *cl, AccessType myaccess): ClassMember(cl, myaccess) {
}

void Attribute::GenerateHeader(std::string &output, bool interface) {
    if(interface) {
        return;
    }
    ClassMember::GenerateHeader(output, interface);

    char tmp[1024];
    for(auto& attribute : attributes){
        Param &p=*attribute;
        p.DeclareVariable(tmp);
        output += tmp;
    }
}

Param *Attribute::NewAttribute() {
    auto  t=new Param;
    attributes.push_back(t);
    return t;
}

/**
 * Implementation of Enumeration class
 */

// enum type constrcutor
Enumeration::Enumeration(Class *cl, AccessType myaccess): ClassMember(cl, myaccess) {

}

// enum type destructor
Enumeration::~Enumeration() {

}

// Save the name of the enum type
void Enumeration::setName(std::string value) {
    name = value;
}

// Save the arguments of the enum type
void Enumeration::setArgs(std::string value) {
    args = value;
}

// Generation of the appropriate code for the enum type
void Enumeration::GenerateHeader(std::string &output, bool interface) {
    ClassMember::GenerateHeader(output, interface);
    output += "enum ";
    output += name;
    output += "{";
    output += args;
    output += "};";
}

/**
 * Implementation of Structure class
 */

// struct type constrcutor
Structure::Structure(Class *cl, AccessType myaccess): ClassMember(cl, myaccess) {

}

// struct type destructor
Structure::~Structure() {

}

// Save the name of the struct type
void Structure::setName(std::string value) {
    name = value;
}

// Save the objects of the struct type
void Structure::setObjects(std::string value) {
    objects = value;
}

void Structure::setInnerDecl(std::string value) {
    if(innerdecl.length()==0) {
        innerdecl = value;
    } else {
        innerdecl.append("\n");
        innerdecl.append(value);
    }
}

// Generation of the appropriate code for the enum type
void Structure::GenerateHeader(std::string &output, bool interface) {
    ClassMember::GenerateHeader(output, interface);
    output += "struct ";
    output += name;
    output += "{\n";
    output += innerdecl;
    output += "\n}";
    output += objects;
    output += ";";
}

/**
 * Implementation of TypeDefinition class
 */

// TypeDefinition constructor
TypeDefinition::TypeDefinition(Class *cl, AccessType myaccess): ClassMember(cl, myaccess) {
    ptr = false;
}

// TypeDefinition type destructor
TypeDefinition::~TypeDefinition() {

}

// Save the name of the typedef
void TypeDefinition::setName(std::string value) {
    name = value;
}

// Save the basetype of the typedef
void TypeDefinition::setBaseType(std::string value) {
    basetype = value;
}

void TypeDefinition::setAsPtr() {
    ptr = true;
}

bool TypeDefinition::isPtr() {
    return ptr;
}

void TypeDefinition::setAsArray() {
    array = true;
}

bool TypeDefinition::isArray() {
    return array;
}


// Generation of the appropriate code for the enum type
void TypeDefinition::GenerateHeader(std::string &output, bool interface) {
    ClassMember::GenerateHeader(output, interface);
    output += "typedef ";
    output += name;
    if(isPtr()) {
        output += " * ";
    } else {
        output += " ";
    }
    output += basetype;
    if(isArray()) {
        output += "[]";
    }
    output += ";";
}

//Directives inside a parallel class
Directive::Directive(Class *cl, char *directive): ClassMember(cl, PUBLIC) {
    code=popc_strdup(directive);
}

Directive::~Directive() {
    if(code!=nullptr) {
        free(code);
    }
}

void Directive::GenerateHeader(std::string &output, bool /*interface*/) {
    if(code!=nullptr) {
        output += "\n";
        output += code;
        output += "\n";
    }
}



// BEGIN Method class implementation....

const int Method::POPC_METHOD_NON_COLLECTIVE_SIGNAL_ID = 9;
const int Method::POPC_METHOD_NON_COLLECTIVE_SIGNAL_INVOKE_MODE = 0;
const char* Method::POPC_METHOD_NON_COLLECTIVE_SIGNAL_NAME = "set_non_collective_rank";

Method::Method(Class *cl, AccessType myaccess): ClassMember(cl, myaccess), returnparam(nullptr) {
    name[0]=0;
    id=0;
    invoketype = invokesync;
    isConcurrent = false;
    isMutex = false;
    isHidden = false;
    isVirtual = false;
    isPureVirtual = false;
    isGlobalConst = false;

    _is_collective = false;
    _is_broadcast = false;
    _is_scatter = false;
    _is_gather = false;
    _is_reduce = false;
}

Method::~Method() {
    for(auto param : params){
        if(param){
            delete param;
        }
    }
}

/**
 * Set a method as collective method
 * @param type  Type of the collective method (Broadcast, Gather, Scatter, Reduce).
 */
void Method::set_collective(CollectiveType type) {
    _is_collective = true;
    switch(type) {
    case POPC_COLLECTIVE_BROADCAST:
        _is_broadcast = true;
        break;
    case POPC_COLLECTIVE_SCATTER:
        _is_scatter = true;
        break;
    case POPC_COLLECTIVE_GATHER:
        _is_gather = true;
        break;
    case POPC_COLLECTIVE_REDUCE:
        _is_reduce = true;
        break;
    default:
        _is_collective = false;
    }
}

/**
 * Check if the method is a collective method
 * @return TRUE if the method is collective. FALSE if it is non-collective.
 */
bool Method::is_collective() {
    if(_is_collective) {
        return true;
    }
    return false;
}

/**
 * Check if the parameter of a specific method can be marshalled
 * @return 0 in case of succes, -1 is the return argument cannot be marshalled, the number of the parameter that cannot be marshalled
 */
int Method::CheckMarshal() {
    // Avoid if access modifier is not public or if the method is hidden
    if(GetMyAccess()!=PUBLIC || isHidden) {
        return 0;
    }

    if(MethodType()==METHOD_NORMAL && !returnparam.CanMarshal()) {
        return -1;
    }

    // Get the number of parameter for this method
    int n=params.size();
    Class *cl=GetClass();

    // Check all the parameters of the method
    for(int i=0; i<n; i++) {
        if(params[i]->GetType()->IsParClass() && !params[i]->IsRef()) {
            fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s : parallel object '%s' must be passed as reference to the remote object.\n",  cl->GetFileInfo(), line, cl->GetName(), name,params[i]->GetName());
            return(i+1);
        }
        // Check if the parameter can be marshalled
        if(!params[i]->CanMarshal()) {
            return (i+1);
        }
    }
    return 0;

}

void Method::GenerateReturn(std::string &output, bool header) {
    GenerateReturn(output,header, false);
}

void Method::GenerateReturn(std::string &output, bool header, bool interface) {
    DataType *type=returnparam.GetType();
    if(type==nullptr) {
        return;
    }
    if(header && isVirtual) {
        output += "virtual ";
    } else if(!header) {
        output += "\n";
    }

    if(returnparam.GetType()->IsParClass() && !returnparam.IsRef()) {
        /* changed by David : no more warning, error ! */
        //fprintf(stderr,"%s:%d: WARNING in %s::%s : the return argument '%s' is treated as a reference to a parallel object.\n", GetClass()->GetFileInfo(), line, GetClass()->GetName(), (const char*)name, returnparam.GetType()->GetName());

        fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s : the return argument '%s' should by a reference to a parallel object !\n", GetClass()->GetFileInfo(), line, GetClass()->GetName(), (const char*)name, returnparam.GetType()->GetName());
        exit(1);
    }
    if(returnparam.IsRef() && !returnparam.GetType()->IsParClass()) {
        fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s : methods of parallel objects can not technically return a reference.\n", GetClass()->GetFileInfo(), line, GetClass()->GetName(), (const char*)name);
        exit(1);
    }

    // add by david
    if(returnparam.IsConst()) {
        output += "const ";
    }

    char tmp[1024];

    type->GetDeclaration(nullptr,tmp);
    //if (returnparam.IsConst())sprintf(tmp, "const %s", tmp);
    output += tmp;

    // add by david
    if(returnparam.IsRef() && !interface) {
//      if(!returnparam.GetType()->IsParClass())
//      {
        output += "& ";
//      }
    }

    output += " ";
}

void Method::GeneratePostfix(std::string &output, bool header) {
    // add const at the end of methode - david
    if(isGlobalConst) {
        output += " const ";
    }

    if(header) {
        output += ";";
    }
}

void Method::GenerateName(std::string &output, bool header) {
    if(header) {
        output += name;
    } else {
        char str[256];
        sprintf(str,"%s::%s",GetClass()->GetName(),name);
        output += str;
    }
}

void Method::GenerateArguments(std::string &output, bool header) {
    char tmpcode[10240];

    output += "(";
    int nb=params.size();
    for(int j=0; j<nb; j++) {
        Param &p=*(params[j]);
        p.DeclareParam(tmpcode, header);
        if(j<nb-1) {
            strcat(tmpcode,", ");
        }
        output += tmpcode;
    }
    output += ")";
}


void Method::GenerateClientPrefixBody(std::string& /*output*/) {

}

void Method::GenerateClient(std::string &output) {
    if((isVirtual && GetClass()->methodInBaseClass(*this)) || isHidden) {
        return;
    }

    // Check if we can generate marshalling stubs
    int t = CheckMarshal();
    if(t != 0) {
        Class *cl = GetClass();
        if(t == -1) {
            if(returnparam.IsPointer()) {
                fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s: The return argument is a Illegal Pointer.\n", cl->GetFileInfo(),line, cl->GetName(), name);
            } else {
                fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s: unable to marshal the return argument.\n", cl->GetFileInfo(),line, cl->GetName(), name);
            }
        } else {
            if(params[t-1]->IsPointer()) {
                fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s: Illegal Pointer Parameter at argument %d.\n",  cl->GetFileInfo(), line, cl->GetName(), name,t);
            } else {
                fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s: unable to marshal argument %d.\n",  cl->GetFileInfo(), line, cl->GetName(), name,t);
            }
        }
        exit(1);
    }

    char tmpcode[10240];

    char *clname = GetClass()->GetName();
    int j, nb = params.size();

    GenerateReturn(output, false, true);
    GenerateName(output, false);
    GenerateArguments(output, false);
    GeneratePostfix(output, false);

    output += "\n{";

    GenerateClientPrefixBody(output);


    // Generate method body
    int invoke_code = 0;
    bool waitreturn = false;
    if(MethodType() == METHOD_CONSTRUCTOR) {
        invoke_code |= INVOKE_CONSTRUCTOR | INVOKE_SYNC | INVOKE_MUTEX;
        waitreturn = true;
    } else {
        if(invoketype == invokesync || (invoketype == autoselect && hasOutput())) {
            invoke_code |= INVOKE_SYNC;
            waitreturn = true;
        }

        if(isMutex) {
            invoke_code |= INVOKE_MUTEX;
        } else if(isConcurrent) {
            invoke_code |= INVOKE_CONC;
        }
    }

    /**
     * Asynchronous Parallel Object Allocation (APOA)
     * The code below is generated to support the APOA in POP-C++ application.
     * Generated at the beginning of each remote method invocation (not for constructor method).
     */
    if(!GetClass()->IsCoreCompilation() && MethodType() != METHOD_CONSTRUCTOR && GetClass()->IsAsyncAllocationEnabled()) {
        output += "\n  // Waiting for APOA to be done before executing any method\n";

        output += "  if(!_popc_async_joined){\n";
        output += "    void* status;\n  pthread_join(_popc_async_construction_thread, &status);\n";
        output += "    _popc_async_joined = true;\n";
        output += "  }\n";

        char* nameOfRetType = returnparam.GetType()->GetName();
        if(MethodType()==METHOD_NORMAL &&!returnparam.GetType()->Same((char*)"void")) {
            sprintf(tmpcode, "  if(!isBinded()) {\n    printf(\"POP-C++ Error: [APOA] Object not allocated but allocation process done !\");\n    %s *tempObject = 0;\n    return (*tempObject);\n  }\n", nameOfRetType);
        } else  if(MethodType()==METHOD_NORMAL && returnparam.GetType()->Same((char*)"void")) {
            sprintf(tmpcode, "  if(!isBinded()) {\n    printf(\"POP-C++ Error: [APOA] Object not allocated but allocation process done !\");\n    return;\n  }\n");
        }

        output += tmpcode;
    } // End of APOA Support

    if(!GetClass()->is_collective()) {
        sprintf(tmpcode, "\n  pop_mutex_locker __pop_lock(_pop_imutex);");
        output += tmpcode;
        sprintf(tmpcode, "\n  if(!__pop_combox)pop_exception::pop_throw(\"combox was not initialized\");");
        output += tmpcode;
        sprintf(tmpcode, "\n  pop_connection* _popc_connection = __pop_combox->get_connection();\n  __pop_buf->Reset();\n  pop_message_header __pop_buf_header(CLASSUID_%s,%d,%d, \"%s\");\n  __pop_buf->SetHeader(__pop_buf_header);\n", clname, id, invoke_code, name);
        output += tmpcode;
    } else {
        // Additional code if the method is not collective
        if(!is_collective() && MethodType() != METHOD_CONSTRUCTOR) {
            sprintf(tmpcode, "\n  // Generate additional information for a non collective call");
            output += tmpcode;

            sprintf(tmpcode, "\n  pop_connection* _popc_connection = _popc_combox->get_connection();\n  _popc_buffer->Reset();\n  pop_message_header _popc_message_header(CLASSUID_%s, %d, %d, \"%s\");\n  _popc_buffer->SetHeader(_popc_message_header);\n",
                    clname, POPC_METHOD_NON_COLLECTIVE_SIGNAL_ID, POPC_METHOD_NON_COLLECTIVE_SIGNAL_INVOKE_MODE, POPC_METHOD_NON_COLLECTIVE_SIGNAL_NAME);
            output += tmpcode;

            sprintf(tmpcode, "\n   _popc_buffer->Push(\"rank\", \"int\", 1);\n  _popc_buffer->Pack(&_popc_default_rank_for_single_call, 1);\n  _popc_buffer->Pop();\n");
            output += tmpcode;

            sprintf(tmpcode, "\n  popc_send_request(_popc_buffer, _popc_connection);\n  _popc_buffer->Reset();\n  pop_message_header _popc_message_header_call(CLASSUID_%s, %d, %d, \"%s\");", clname, id, invoke_code, name);
            output += tmpcode;

            sprintf(tmpcode, "\n  _popc_buffer->SetHeader(_popc_message_header_call);");
            output += tmpcode;
        } else {
            sprintf(tmpcode, "\n  pop_connection* _popc_connection = _popc_combox->get_connection();\n  _popc_buffer->Reset();\n  pop_message_header _popc_message_header(CLASSUID_%s, %d, %d, \"%s\");\n  _popc_buffer->SetHeader(_popc_message_header);\n", clname, id, invoke_code, name);
            output += tmpcode;
        }
    }

    // Generate marshalling stub
    for(j=0; j<nb; j++) {
        Param &p=*(params[j]);
        if(p.InParam())  {
            if(!GetClass()->is_collective()) {
                p.Marshal((char*)"(*__pop_buf)", false, true, output);
            } else {
                p.Marshal((char*)"  (*_popc_buffer)", false, true, output);
            }
        }
    }

    // Marshalling code generation is done. Transmit buffer

    if(!GetClass()->is_collective()) {
        strcpy(tmpcode,"\n  popc_send_request(__pop_buf, _popc_connection);");
    } else {
        strcpy(tmpcode,"\n  popc_send_request(_popc_buffer, _popc_connection);");
    }
    output += tmpcode;

    if(waitreturn) {
#ifdef OD_DISCONNECT
        strcpy(tmpcode,"\n\tif(od.getCheckConnection()){\n\t\tif(!RecvCtrl())pop_exception::pop_throw(\"od.getCheckConnection()\");\n\t}");
        output += tmpcode;
        strcpy(tmpcode,"\n\telse\n");
        output += tmpcode;
#endif

        if(!GetClass()->is_collective()) {
            strcpy(tmpcode,"\t{\n\t\tif (!__pop_buf->Recv((*__pop_combox), _popc_connection)) pop_exception::pop_throw(\"Buffer receive\");\n\t}\n\t\n\tpop_buffer::CheckAndThrow(*__pop_buf);\n");
        } else {
            strcpy(tmpcode,"\n  popc_recv_response(_popc_buffer, _popc_connection);");
        }
        output += tmpcode;
        for(j=0; j<nb; j++) {
            Param &p=*(params[j]);
            if(p.OutParam()) {
                if(!GetClass()->is_collective()) {
                    p.UnMarshal((char*)"(*__pop_buf)",false,false, true, output);
                } else {
                    p.UnMarshal((char*)"  (*_popc_buffer)",false,false, true, output);
                }
            }
        }

        if(MethodType() == METHOD_NORMAL && !returnparam.GetType()->Same((char*)"void")) {
            bool reformat;
            returnparam.DeclareVariable(tmpcode,reformat,false);
            output += tmpcode;



            if(!GetClass()->is_collective()) {
                returnparam.UnMarshal((char*)"(*__pop_buf)", reformat, true, true, output);
                strcpy(tmpcode,"\n  __pop_buf->Reset();");
            } else {
                returnparam.UnMarshal((char*)"(*_popc_buffer)", reformat, true, true, output);
                strcpy(tmpcode,"\n  _popc_buffer->Reset();");
            }
            output += tmpcode;


            // Added for new communication support
            strcpy(tmpcode,"\n_popc_connection->reset();\nreturn ");

            if(reformat) {
                strcat(tmpcode,"&");
            }
            strcat(tmpcode,returnparam.name);
            strcat(tmpcode,";\n}\n");
            output += tmpcode;

        } else {
            if(!GetClass()->is_collective()) {
                strcpy(tmpcode,"\n  __pop_buf->Reset();\n");
            } else {
                strcpy(tmpcode,"\n  _popc_buffer->Reset();\n");
            }
            output += tmpcode;
            // Added for new communication support
            strcpy(tmpcode,"\n  _popc_connection->reset();}\n");
            output += tmpcode;
        }
    } else {
        // Check that we are not waiting for a returning param
        for(j=0; j<nb; j++) {
            if(params[j]->OutParam() && !params[j]->GetType()->IsParClass()) {
                Class *cl=GetClass();
                fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s: Asynchronous method cannot have an output (parameter %s must be declared with [in])\n",cl->GetFileInfo(),line, cl->GetName(), name, params[j]->name);
                exit(1);
            }
        }
        if(MethodType()==METHOD_NORMAL &&!returnparam.GetType()->Same((char*)"void")) {
            Class *cl=GetClass();
            fprintf(stderr,"%s:%d: POP-C++ Error in %s::%s: Asynchronous method must return void\n",cl->GetFileInfo(),line, cl->GetName(), name);
            exit(1);
        }
#ifdef OD_DISCONNECT
        strcpy(tmpcode,"\n\tint time_alive, time_control, oldTime;\nod.getCheckConnection(time_alive, time_control);\n\t");
        output += tmpcode;
        strcpy(tmpcode,"\n\tif(time_alive > 0 && time_control > 0 ){\n\t\toldTime=__pop_combox->GetTimeout();\n\t\t__pop_combox->SetTimeout(time_alive);\n\t\t__pop_combox->RecvAck();\n\t\t__pop_combox->SetTimeout(oldTime);\n\t}");
        output += tmpcode;
#else
        if(!GetClass()->is_collective()) {
            strcpy(tmpcode,"\n  __pop_buf->Reset();");
        } else {
            strcpy(tmpcode,"\n  _popc_buffer->Reset();");
        }
        output += tmpcode;

        // Added for new communication support
        strcpy(tmpcode,"_popc_connection->reset();\n}\n");
        output += tmpcode;
#endif
    }
}

void Method::generate_header_pog(std::string &output, bool interface) {
    int type = MethodType();
    if(interface) {
        if(type == METHOD_DESTRUCTOR || GetMyAccess() != PUBLIC || isHidden) {
            return;
        }
        if(isVirtual && GetClass()->methodInBaseClass(*this)) {
            return;
        }
    }

    ClassMember::GenerateHeader(output, interface);

    if(type == METHOD_NORMAL) {
        GenerateReturn(output, true, interface);
    } else {
        GenerateReturn(output, true);
    }

    if(!interface && type != METHOD_NORMAL) {
        char str[256];
        sprintf(str, "%s%s", name, Class::POG_OBJECT_POSTFIX);
        output += str;
    } else {
        GenerateName(output, true);
    }

    GenerateArguments(output, true);

    if(isPureVirtual && !interface) {
        output += "=0";
    }

    GeneratePostfix(output, true);
}

void Method::GenerateHeader(std::string &output, bool interface) {
    int type=MethodType();
    if(interface) {
        if(type==METHOD_DESTRUCTOR || GetMyAccess()!=PUBLIC || isHidden) {
            return;
        }
        if(isVirtual && GetClass()->methodInBaseClass(*this)) {
            return;
        }
    }
    ClassMember::GenerateHeader(output, interface);

    if(type==METHOD_NORMAL) {
        GenerateReturn(output, true, interface);
    } else {
        GenerateReturn(output, true);
    }

    if(!interface && type != METHOD_NORMAL) {
        char str[256];
        sprintf(str, "%s%s", name, OBJ_POSTFIX);
        output += str;
    } else {
        GenerateName(output, true);
    }
    GenerateArguments(output, true);

    if(isPureVirtual && !interface) {
        output += "=0";
    }

    GeneratePostfix(output,true);
}

void Method::GenerateBrokerHeader(std::string &output) {
    int type=MethodType();
    if(type==METHOD_DESTRUCTOR || GetMyAccess()!=PUBLIC || isHidden) {
        return;
    }
    if(isVirtual && GetClass()->methodInBaseClass(*this)) {
        return;
    }

    char str[1024];
    sprintf(str,"\nvoid Invoke_%s_%d(pop_buffer &__pop_buf, pop_connection *__interface_output);",name , id);
    output += str;
}

void Method::generate_broker_header_pog(std::string &output) {
    int type=MethodType();
    if(type==METHOD_DESTRUCTOR || GetMyAccess()!=PUBLIC || isHidden) {
        return;
    }
    if(isVirtual && GetClass()->methodInBaseClass(*this)) {
        return;
    }

    char str[1024];
    sprintf(str,"\n  void Invoke_%s_%d(pop_buffer &_popc_buffer, pop_connection *_popc_connection);",name , id);
    output += str;
}

void Method::GenerateBroker(std::string &output) {
    int type = MethodType();

    if(type == METHOD_DESTRUCTOR || GetMyAccess() != PUBLIC || isHidden) {
        return;
    }

    if(isVirtual && GetClass()->methodInBaseClass(*this)) {
        return;
    }

    Class *cl = GetClass();
    char *clname = cl->GetName();

    int nb=params.size();

    char brokername[256];
    sprintf(brokername, "%s%s", cl->GetName(), Class::POG_BROKER_POSTFIX);

    std::deque<bool> reformat(nb);

    // Now generate method wrappers
    char str[1024];

    if(GetClass()->is_collective()) {
        sprintf(str,"\nvoid %s::Invoke_%s_%d(pop_buffer &_popc_buffer, pop_connection *_popc_connection)\n{",brokername,name, id);
    } else {
        sprintf(str,"\nvoid %s::Invoke_%s_%d(pop_buffer &__pop_buf, pop_connection *__interface_output)\n{",brokername,name, id);
    }
    output += str;

    char methodcall[1024];
    bool haveReturn=false;

    if(cl->IsCoreCompilation() || !cl->IsBasePureVirtual()) {  // ADDED FOR 2.0.3 Create constructor and stuff only if the parclass is not abstract
        if(type==METHOD_CONSTRUCTOR) {
            //Constructor...create object now...
            if(GetClass()->is_collective()) {
                sprintf(methodcall,"\n  try {\n    _popc_internal_object = new %s%s(", clname, Class::POG_OBJECT_POSTFIX);
            } else {
                sprintf(methodcall,"\n  try {\n    obj = new %s%s(", clname, OBJ_POSTFIX);
            }
        } else if(type != METHOD_NORMAL || returnparam.GetType()->Same((char*)"void")) {
            if(GetClass()->is_collective()) {
                sprintf(methodcall,"\n  %s%s* _popc_object = dynamic_cast<%s%s*>(_popc_internal_object);\n  try {\n    _popc_object->%s(",clname,Class::POG_OBJECT_POSTFIX,clname,Class::POG_OBJECT_POSTFIX, name);
                // TODO security: a good improvement would be to dynamic cast to references to handle exceptions: dynamic_cast<Type&>(*obj).method()
            } else {
                sprintf(methodcall,"\n%s%s * _pop_obj = dynamic_cast<%s%s *>(obj);\ntry {\n_pop_obj->%s(", clname, OBJ_POSTFIX, clname, OBJ_POSTFIX, name);
            }
        } else {
            char retdecl[1024];
            char tmpvar[1024];
            strcpy(tmpvar,returnparam.GetName());
            returnparam.GetType()->GetDeclaration(tmpvar,retdecl);

            if(returnparam.GetType()->IsParClass()) {
                if(GetClass()->is_collective()) {
                    sprintf(methodcall,"\n%s(pop_interface::_pop_nobind);\n    %s%s * _popc_object = dynamic_cast<%s%s*>(_popc_internal_object);\n  try {\n    %s=_popc_object->%s(",retdecl, clname, Class::POG_OBJECT_POSTFIX, clname, Class::POG_OBJECT_POSTFIX, tmpvar, name);
                } else {
                    sprintf(methodcall,"\n%s(pop_interface::_pop_nobind);\n%s%s * _pop_obj=dynamic_cast<%s%s *>(obj);\ntry {\n%s=_pop_obj->%s(", retdecl, clname, OBJ_POSTFIX, clname, OBJ_POSTFIX, tmpvar, name);
                }
            } else {
                if(GetClass()->is_collective()) {
                    sprintf(methodcall,"\n%s;\n%s%s * _popc_object = dynamic_cast<%s%s*>(_popc_internal_object);\n  try {\n    %s=_popc_object->%s(",retdecl, clname, Class::POG_OBJECT_POSTFIX, clname, Class::POG_OBJECT_POSTFIX, tmpvar, name);
                } else {
                    sprintf(methodcall,"\n%s;\n%s%s * _pop_obj=dynamic_cast<%s%s *>(obj);\ntry {\n%s=_pop_obj->%s(",retdecl, clname, OBJ_POSTFIX, clname, OBJ_POSTFIX, tmpvar, name);
                }
            }
            haveReturn = true;
        }

        bool have_memspool = false;

        // unmarhall and allocate memory for input arguments first
        strcpy(str,"\n  ");
        output += str;

        for(int j = 0; j < nb; j++) {
            Param &p = *(params[j]);
            if(!p.InParam()) {
                continue;
            }
            char decl[1024];
            if(p.DeclareVariable(decl,reformat[j],false)) {
                output += decl;
            }

            if(GetClass()->is_collective()) {
                strcpy(str,"_popc_buffer");
            } else {
                strcpy(str,"__pop_buf");
            }
            if(p.marshalProc!=nullptr && !have_memspool) {
                strcpy(str,"\npop_memspool _internal_mem;");
                output += str;
                have_memspool=true;
            }
            if(GetClass()->is_collective()) {
                p.UnMarshal((char*)"  _popc_buffer", reformat[j], true, false, output);
            } else {
                p.UnMarshal((char*)"__pop_buf",reformat[j],true,false,output);
            }
        }

        // Then, declare and alloc mem  for output-only arguments

        for(int j = 0; j < nb; j++) {

            Param &p=*(params[j]);
            if(!p.InParam()  /*&& strcmp(p.GetType()->GetName(), "void") != 0 */) {
                char decl[1024];
                p.DeclareVariable(decl,reformat[j],true);
                output += decl;
            }

            if(reformat[j] && !p.IsVoid()) {
                strcat(methodcall," &");
            }
            strcat(methodcall,p.GetName());
            if(j<nb-1) {
                strcat(methodcall,", ");
            }
        }

        strcat(methodcall,");");
        // Add 'catch' to catch and print all std exceptions raised in the method
        char tempcatch[256];
        for(auto & elem : tempcatch) {
            elem='\0';
        }

        sprintf(tempcatch,"\n  } catch(std::exception& e) {\n    popc_logger_t(__DEBUG__,\"(classmember.cc)\", 0, \"\", 0, \"Exception '%%s' raised in method '%s' of class '%s'\\n\",e.what());\n    throw;\n  }\n", name, clname);
        strcat(methodcall,tempcatch);



        //now....generate the call...
        output += methodcall;

        /*

          } */

        if(GetClass()->is_collective()) {
            sprintf(str,"\n  if (_popc_connection != 0) {\n    _popc_buffer.Reset();\n    pop_message_header _popc_message_header(\"%s\");\n    _popc_buffer.SetHeader(_popc_message_header);\n", name);
        } else {
            sprintf(str,"\nif (__interface_output!=0) \n{\n__pop_buf.Reset();\npop_message_header __pop_buf_header(\"%s\");\n__pop_buf.SetHeader(__pop_buf_header);\n", name);
        }

        output += str;

        for(int j=0; j<nb; j++) {
            Param &p=*(params[j]);
            if(p.OutParam()) {
                if(GetClass()->is_collective()) {
                    p.Marshal((char*)"    _popc_buffer", reformat[j], false, output);
                } else {
                    p.Marshal((char*)"__pop_buf", reformat[j], false, output);
                }
            }
        }

        if(haveReturn) {
            if(GetClass()->is_collective()) {
                returnparam.Marshal((char*)"    _popc_buffer",false,false, output);
            } else {
                returnparam.Marshal((char*)"__pop_buf",false,false, output);
            }

        }




        if(GetClass()->is_collective()) {
            // TODO change true by false if non-collective
            if(type == METHOD_CONSTRUCTOR) {
                sprintf(str, "\n    popc_send_response(_popc_buffer, _popc_connection, true);");
            } else {
                sprintf(str, "\n    popc_send_response(_popc_buffer, _popc_connection, %s);", (is_collective()) ? "true" : "false");
            }
            output += str;
            strcpy(str, "\n    _popc_connection->reset();\n  }\n}\n");
            output += str;
        } else {
            strcpy(str,"\nif (!__pop_buf.Send(__interface_output)) pop_exception::pop_throw(\"buffer send\");\n}\n");
            output += str;
            strcpy(str,"\nif(__interface_output != 0)\n__interface_output->reset();\n}\n");
            output += str;
        }
        // End of mod
    } else {
        if(cl->IsWarningEnable()) {
            printf("POP-C++ Warning: %s is an abstract parclass. Be aware that only the final class (parallel object) will keep this semantic.\n", clname);
        }
        strcpy(str,"}\n");  // Close the method braces
        output += str;
    }

}

Param *Method::AddNewParam() {
    auto  t=new Param;
    params.push_back(t);
    return t;
}

bool Method::hasInput() {
    for(auto& param : params){
        if(param->InParam()){
            return true;
        }
    }
    return false;
}

bool Method::hasOutput() {
    if(MethodType()==METHOD_NORMAL) {
        if(!returnparam.GetType()->Same((char*)"void")) {
            return true;
        }
    }

    for(auto& param : params){
        if(param->OutParam()){
            return true;
        }
    }
    return false;
}

bool Method::operator ==(Method &other) {
    if(isVirtual!=other.isVirtual) {
        return false;
    }
    if(GetMyAccess()!=other.GetMyAccess()) {
        return false;
    }
    if(MethodType()!=other.MethodType()) {
        return false;
    }
    if(!pop_utils::isEqual(name,other.name)) {
        return false;
    }


    DataType *type1=returnparam.GetType();
    DataType *type2=other.returnparam.GetType();

    if((type1==nullptr || type2==nullptr) && type1!=type2) {
        return false;
    }

    if(!type1->Same(type2)) {
        return false;
    }

    auto n=params.size();
    if(n!=other.params.size()) {
        return false;
    }
    for(std::size_t i=0; i<n; i++) {
        Param &t1=*params[i];
        Param &t2=*other.params[i];
        if(!t1.GetType()->Same(t2.GetType())) {
            return false;
        }
    }
    return true;
}

// END Method class implementation....

//Implement Constructor class

Constructor::Constructor(Class *cl, AccessType myaccess):Method(cl, myaccess) {
    strcpy(name, cl->GetName());
}

void Constructor::set_id(int value) {
    identifier = value;
}
int Constructor::get_id() {
    return identifier;
}

bool Constructor::isDefault() {
    return params.empty();
}


ObjDesc & Constructor::GetOD() {
    return od;
}

void Constructor::generate_header_pog(std::string &output, bool interface) {
    Method::generate_header_pog(output, interface);



    if(interface) {
        char str[1024];
        strcpy(str,"\nvoid _popc_constructor");
        output += str;
        GenerateArguments(output, true);
        GeneratePostfix(output,true);
    }
}

void Constructor::GenerateHeader(std::string &output, bool interface) {
    Method::GenerateHeader(output, interface);

    if(interface) {
        char str[1024];
        strcpy(str,"\nvoid _pop_construct");
        output += str;
        GenerateArguments(output, true);
        GeneratePostfix(output,true);
    }
}

void Constructor::GenerateReturn(std::string& /*output*/, bool /*header*/) {
}

void Constructor::GeneratePostfix(std::string &output, bool header) {
    if(header) {
        output += ";";
        return;
    }

    CArrayBaseClass &baseClass=GetClass()->baseClass;
    int n=baseClass.size();
    if(n) {
        CArrayClass bases;
        bases.resize(n);
        for(int i=0; i<n; i++) {
            bases[i]=baseClass[i]->base;
        }
        Class *cl=GetClass();
        CodeFile *prog=cl->GetCodeFile();
        prog->FindAllBaseClass(*cl, bases,true);

        n=bases.size();
        char tmpcode[10240];
        strcpy(tmpcode," : ");
        for(int j=0; j<n; j++) {
            strcat(tmpcode,bases[j]->GetName());
            if(j<n-1) {
                strcat(tmpcode,"(_pop_nobind) ,");
            } else {
                strcat(tmpcode,"(_pop_nobind)");
            }
        }
        output += tmpcode;
    }
}

void Constructor::GenerateClientPrefixBody(std::string &output) {
    char tmpcode[10240];


    /**
     * Asynchronous Parallel Object Creation (APOA)
     * The code below is generated to support the APOA in POP-C++ application.
     */

    if(!GetClass()->IsCoreCompilation() && GetClass()->IsAsyncAllocationEnabled()) {
        strcpy(tmpcode, "\n");
        output += tmpcode;
        od.Generate(tmpcode);   // Generates the object description
        output += tmpcode;
#ifdef __APPLE__
        strcpy(tmpcode,"\n  pthread_attr_t attr;\n  pthread_attr_init(&attr);\n  pthread_attr_setdetachstate(&attr, 1);");
#else
        strcpy(tmpcode,"\n  pthread_attr_t attr;\n  pthread_attr_init(&attr);\n  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);");
#endif
        output += tmpcode;

        sprintf(tmpcode,"\n  pthread_args_t_%d *arguments = (pthread_args_t_%d *) malloc(sizeof(pthread_args_t_%d));\n  %s* ptr = static_cast<%s*>(this);\n  arguments->ptr_interface = ptr;\n", get_id(), get_id(), get_id(), GetClass()->GetName(), GetClass()->GetName());
        output += tmpcode;

        for(auto& param : params){
            Param &p = *param;
            sprintf(tmpcode, "  arguments->");
            strcat(tmpcode, p.GetName());
            strcat(tmpcode, " = ");
            strcat(tmpcode, p.GetName());
            strcat(tmpcode, ";\n");
            output += tmpcode;
        }

        sprintf(tmpcode, "  int ret;\n   _popc_async_joined = false;\n  ret = pthread_create(&_popc_async_construction_thread, &attr, %s_AllocatingThread%d, arguments);\n", GetClass()->GetName(), get_id());
        output += tmpcode;
        strcpy(tmpcode, "  if(ret != 0) {\n    printf(\"Thread creation failed\\n\");\n    perror(\"pthread_create\");\n    pthread_attr_destroy(&attr);\n    return;\n  }\n  pthread_attr_destroy(&attr);\n");
        output += tmpcode;
    } else if(!GetClass()->is_collective()) { // End of APOA Support
        /**
         * Standard parallel object allocation
         */
        strcpy(tmpcode, "");
        od.Generate(tmpcode);   // Generates the object description
        strcat(tmpcode,"\nAllocate();");    // Generates call to the Allocate method of pop_interface
        output += tmpcode;

        // Generates invocation to the constructor of the remote object
        strcpy(tmpcode,"\n_pop_construct(");
        auto nb = params.size();
        for(std::size_t j=0; j<nb; j++) {
            Param &p=*(params[j]);
            strcat(tmpcode,p.GetName());
            if(j<nb-1) {
                strcat(tmpcode,", ");
            }
        }
        strcat(tmpcode,");\n");
        output += tmpcode;
        // End of constructor invocation
    } else {
        // Generate the object description in the interface constructor
        sprintf(tmpcode, "\n  _popc_selected_constructor_id = %d;", id);
        output += tmpcode;

        strcpy(tmpcode, "\n  ");
        od.Generate(tmpcode);
        strcat(tmpcode, "\n");
        output += tmpcode;

        // Save constructor parameters for group initialization
        for(auto& param : params){
            Param &p = *param;
            sprintf(tmpcode, "  _popc_constructor_%d_%s = %s;\n", id, p.GetName(), p.GetName());
            output += tmpcode;
        }
    }


    strcpy(tmpcode,"}\n");
    output += tmpcode;


    // APOA Code generation
    if(!GetClass()->IsCoreCompilation() && GetClass()->IsAsyncAllocationEnabled()) {
        sprintf(tmpcode,"\n// This code is generated for Asynchronous Parallel Object Allocation support for the object %s\n", GetClass()->GetName());
        output += tmpcode;
        sprintf(tmpcode,"extern \"C\"\n{\n  void* %s_AllocatingThread%d(void* arg)\n  {\n", GetClass()->GetName(), get_id());
        output += tmpcode;

        sprintf(tmpcode,"    pthread_args_t_%d *arguments = (pthread_args_t_%d*)arg;\n", get_id(), get_id());
        output += tmpcode;

        sprintf(tmpcode,"    %s* _this_interface = static_cast<%s*>(arguments->ptr_interface);\n",GetClass()->GetName(), GetClass()->GetName());
        output += tmpcode;

        for(auto& param : params){
            Param &p = *param;
            sprintf(tmpcode, "%s %s = arguments->%s;\n", p.GetType()->GetName(), p.GetName(), p.GetName());
            output += tmpcode;
        }

        output += "    try{\n      _this_interface->Allocate();\n      _this_interface->_pop_construct(";

        auto nb = params.size();
        for(std::size_t j=0; j<nb; j++) {
            Param &p = *(params[j]);
            output += p.GetName();
            if(j<nb-1) {
                output += ", ";
            }
        }

        output += ");\n";

        sprintf(tmpcode, "    } catch(pop_exception* ex) {\n      printf(\"Async allocation: %%s\", ex->what()); \n    }\n   free(arg);\n  return 0;\n  }\n}\n");
        output += tmpcode;
    }



    if(!GetClass()->is_collective()) {
        sprintf(tmpcode, "\nvoid %s::_pop_construct", GetClass()->GetName());
        output += tmpcode;
    } else {
        //sprintf(tmpcode, "\nvoid %s::construct_remote_object() {\n  _popc_constructor(", GetClass()->GetName());
        //output += tmpcode;



        // Place saved constructor arguments
        /*      int nb = params.size();
                for (int j = 0; j < nb; j++) {
                    Param &p = *(params[j]);
                    sprintf(tmpcode, "_popc_constructor_%d_%s", get_id(), p.GetName());
                    output += tmpcode;
                    if (j < nb-1) {
                    strcpy(tmpcode, ", ");
                    output += tmpcode;
                }
                }


              strcpy(tmpcode, ");\n}\n");
              output += tmpcode;     */

        sprintf(tmpcode,"\nvoid %s::_popc_constructor",GetClass()->GetName());
        output += tmpcode;
    }

    GenerateArguments(output,false);



    strcpy(tmpcode,"\n{");
    output += tmpcode;
}

//Implement Destructor class

Destructor::Destructor(Class *cl, AccessType myaccess): Method(cl, myaccess) {
}

void Destructor::GenerateClient(std::string& output) {
    /**
     * Asynchronous Parallel Object Allocation (APOA)
     * The code below is generated to support the APOA in POP-C++ application.
     * Generated at the beginning of each remote method invocation (not for constructor method).
     */
    if(!GetClass()->IsCoreCompilation() && MethodType() != METHOD_CONSTRUCTOR && GetClass()->IsAsyncAllocationEnabled()) {
        auto class_name = GetClass()->GetName();

        output += class_name;
        output += "::~";
        output += class_name;

        output += "(){\n";
        output += "  if(!_popc_async_joined){\n";
        output += "    void* status;\n  pthread_join(_popc_async_construction_thread, &status);\n";
        output += "    _popc_async_joined = true;\n";
        output += "  }\n";
        output += "  if(!isBinded()) {\n";
        output += "     printf(\"POP-C++ Error: [APOA] Object not allocated but allocation process done !\");\n";
        output += "  }\n";
        output += "}";
    }
}

void Destructor::GenerateReturn(std::string &output, bool header) {
    if(header) {
        output += "~";
    } else {
        output += "\n~";
    }
}

// BEGIN  BaseClass implementation....

BaseClass::BaseClass(Class *name, AccessType basemode, bool onlyVirtual) {
    base=name;
    type=basemode;
    baseVirtual=onlyVirtual;
}
// END  BaseClass implementation....

