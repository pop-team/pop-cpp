#ifndef PARSER_H
#define PARSER_H

#include "parser_common.h"
#include "type.h"

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef long YYSTYPE; // We force the declaration as long to avoid compilation problems in 64bits
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#define PARAM_IN 1
#define PARAM_OUT 2
#define SYNC    4
#define ASYNC   8
#define CONC    16
#define USERPROC 32
#define PARAMSIZE  64
#define OBJ_POSTFIX "__parocobj"
#define TMP_CODE_PREFIX "_paroc_"

//Invocation semantics codes...
#define INVOKE_SYNC 1
//#define INVOKE_ASYNC 2
#define INVOKE_CONSTRUCTOR 4
#define INVOKE_CONC 8
#define INVOKE_MUTEX 16

//bit FLAGS values customized marshalling/demarshalling procedure....should be the same as defined in marshal.h
#define FLAG_MARSHAL  2
#define FLAG_INPUT  1

#define TYPE_OTHERCODE 1
#define TYPE_PACKOBJECT 2
#define TYPE_CLASS 3

#define TYPE_ATTRIBUTE 4
#define TYPE_METHOD 5
#define TYPE_DIRECTIVE 6

#define METHOD_NORMAL 0
#define METHOD_CONSTRUCTOR 1
#define METHOD_DESTRUCTOR 2

enum InvokeType { autoselect=0 , invokesync=1, invokeasync=2 };
enum AccessType {PUBLIC=0,PROTECTED=1,PRIVATE=2};

class Param;
class Method;
class Class;
class BaseClass;
class ClassMember;
class CodeData;
class CodeFile;
class PackObject;

typedef paroc_array<Param *> CArrayParam;
typedef paroc_array<Method *> CArrayMethod;
typedef paroc_array<Class *> CArrayClass;
typedef paroc_array<BaseClass *> CArrayBaseClass;
typedef paroc_array<ClassMember *> CArrayClassMember;
typedef paroc_array<CodeData *> CArrayCodeData;
typedef paroc_array<CodeFile *> CArrayCodeFile;

typedef paroc_array<DataType *> CArrayDataType;


/**
 * @class CodeData
 * @brief A C++ class representing code to generate, used by the parser.
 *
 *
 */
class CodeData
{
public:
	CodeData(CodeFile *file);
	virtual ~CodeData();

	virtual int Type() { return -1;};

	virtual void GenerateCode(CArrayChar &output);
	CodeFile *GetCodeFile() { return codeFile;}
protected:
	CodeFile *codeFile;
};

/**
 * @class OtherCode
 * @brief A C++ class representing other code lines, used by the parser.
 *
 *
 */
class OtherCode: public CodeData
{
public:
	OtherCode(CodeFile *file);
	virtual int Type() { return TYPE_OTHERCODE;};

	virtual void GenerateCode(CArrayChar &output);


	void AddCode(char *newcode);
	void AddCode(char *, int n);
	void AddCode(CArrayChar &newcode);
protected:
	CArrayChar code;
};

/**
 * @class PackObject
 * @brief A C++ class representing code for the object packing, used by the parser.
 *
 *
 */
class PackObject: public CodeData
{
public:
	PackObject(CodeFile *file);
	virtual int Type() { return TYPE_PACKOBJECT;};
	virtual void GenerateCode(CArrayChar &output);
	void AddObject(string64 objname);
	int GetNumObject();

	void SetStartLine(int l);
	void SetEndLine(int l);

protected:
	CArrayString objects;
	int startline, endline;
};


/**
 * @class CodeFile
 * @brief A C++ class representing a code file, used by the parser.
 *
 *
 */
class CodeFile
{
public:
	CodeFile(char *fname);
	~CodeFile();
	void AddCodeData(CodeData *code);
	void EmptyCodeData();
	void GenerateCode(CArrayChar &output, bool client=true, bool broker=true);
	CArrayCodeData *GetCodes();
	bool HasClass();
	char *GetFileName();
	void SetFileName(char *name);

	char *GetOutputName();
	void SetOutputName(char *name);

	Class *FindClass(char *clname);
	/**
	     * @brief Returns the class list
	     * @param classlist Output
	 */
	void FindAllClass(CArrayClass &classlist);
	/**
	 * @brief Finds out if a class is in bases and adds it if not found.
	 * @param t Class to search
	 * @param bases Base
	 * @param virtualBaseOnly
	 */
	void FindAllBaseClass(Class &t, CArrayClass & bases, bool virtualBaseOnly);

	DataType *FindDataType(const char *name);
	void AddDataType(DataType *type);
	void RemoveDataType(DataType *type);

	static bool SameFile(char *file1, char *file2);
protected:
	char *filename;
	char *outfile;
	CArrayCodeData codes;
	CArrayClass classlist;

	CArrayDataType datatypes;
	CArrayDataType temptypes;

};




/**
 * @class Param
 * @brief A C++ class representing a parameter, used by the parser.
 *
 * It seems that this class is also used to represent a class attribute.
 */
class Param
{
public:
	Param(DataType *ptype);
	Param();
	~Param();
	char *Parse(char *str);
	bool Match(Param *p);

	bool IsPointer();
	bool IsRef();
	bool IsConst();
	bool InParam();
	bool OutParam();

	void SetType(DataType *type);

	DataType *GetType();

	char *GetName();
	char *GetDefaultValue();

	int  GetAttr();

	bool CanMarshal();

	bool DeclareParam(char *output, bool header);
	bool DeclareVariable(char *output, bool &reformat, bool allocmem);
	bool DeclareVariable(char *output);

	virtual bool Marshal(char *bufname, bool reformat,bool inf_side, CArrayChar &output);
	virtual bool UnMarshal(char *bufname, bool reformat, bool alloc_mem, bool inf_side, CArrayChar &output);
	virtual bool UserProc(char *code);

	bool isConst;
	bool isRef;
	char name[64];
	DataType *mytype;
	//  char *cardinal;
	char *paramSize;
	char *marshalProc;
	char *defaultVal;

	bool isInput;
	bool isOutput;

	int attr;
};

/**
 * @class ObjDesc
 * @brief (to be written)
 *
 *
 */
class ObjDesc
{
public:
	ObjDesc();
	~ObjDesc();

	void Generate(char *code);
	void SetCode(char *code);
protected:
	char *odstr;
};


/**
 * @class ClassMember
 * @brief A C++ class representing a member of a class, used by the parser.
 *
 *
 */
class ClassMember
{
public:
	ClassMember(Class *cl, AccessType myaccess);
	virtual ~ClassMember();

	virtual int Type() { return -1; };

	virtual void GenerateClient(CArrayChar &output);
	virtual void GenerateHeader(CArrayChar &output, bool interface);

	void SetLineInfo(int linenum);

	AccessType GetMyAccess();
	Class *GetClass();
protected:
	AccessType accessType;
	Class *myclass;
	int line;
};

/**
 * @class Attribute
 * @brief  A C++ class representing a class attribute, used by the parser.
 *
 *
 */
class Attribute: public ClassMember
{
public:
	Attribute(Class *cl,AccessType myaccess);
	virtual int Type() { return TYPE_ATTRIBUTE; };

	virtual void GenerateHeader(CArrayChar &output, bool interface);

	Param *NewAttribute();

protected:
	CArrayParam attributes;
};
/**
 * @class Directive
 * @brief (to be written)
 *
 */
class Directive: public ClassMember
{
public:
	Directive(Class *cl, char *directive);
	~Directive();

	virtual int Type() { return TYPE_DIRECTIVE; };
	virtual void GenerateHeader(CArrayChar &output, bool interface);
private:
	char *code;
};

/**
 * @class Method
 * @brief  A C++ class representing a method, used by the parser.
 *
 */
class Method: public ClassMember
{
public:
	Method(Class *cl, AccessType myaccess);
	~Method();
	virtual int Type() { return TYPE_METHOD; };

	int CheckMarshal();

	virtual void GenerateClient(CArrayChar &output);
	virtual void GenerateHeader(CArrayChar &output, bool interface);
	virtual void GenerateBrokerHeader(CArrayChar &output);
	virtual void GenerateBroker(CArrayChar &output);

	virtual int MethodType() { return METHOD_NORMAL; };

	bool operator == (Method &other);


	char *Parse(char *str);

	Param *AddNewParam();

	bool hasInput();
	bool hasOutput();

	bool isVirtual;
	bool isPureVirtual;

	bool isConcurrent;
	bool isMutex;
	bool isHidden;

	CArrayString mutex;

	InvokeType invoketype;

	char name[64];
	int id;
	CArrayParam params;
	Param returnparam;

protected:
	virtual void GenerateReturn(CArrayChar &output, bool header);
	virtual void GeneratePostfix(CArrayChar &output, bool header);
	virtual void GenerateName(CArrayChar &output, bool header);
	virtual void GenerateArguments(CArrayChar &output, bool header);

	virtual void GenerateClientPrefixBody(CArrayChar &output);
};
/**
 * @class Constructor
 * @brief  A C++ class representing constructor method, used by the parser.
 *
 *
 */
class Constructor: public Method
{
public:
	Constructor(Class *cl, AccessType myaccess);
	virtual int MethodType() { return METHOD_CONSTRUCTOR; };

	virtual void GenerateHeader(CArrayChar &output, bool interface);
	bool isDefault();

	ObjDesc &GetOD();

protected:
	virtual void GenerateReturn(CArrayChar &output, bool header);
	virtual void GeneratePostfix(CArrayChar &output, bool header);
	virtual void GenerateClientPrefixBody(CArrayChar &output);

	ObjDesc od; //Only used for constructor method
};
/**
 * @class Destructor
 * @brief  A C++ class representing destructor method, used by the parser.
 *
 */
class Destructor: public Method
{
public:
	Destructor(Class *cl, AccessType myaccess);

	virtual int MethodType() { return METHOD_DESTRUCTOR; };

	virtual void GenerateClient(CArrayChar &output);
protected:
	virtual void GenerateReturn(CArrayChar &output, bool header);
};

/**
 * @class BaseClass
 * @brief A C++ class representing a parent class, used by the parser
 *
 *
 */
class BaseClass
{
public:
	BaseClass(Class *name, AccessType basemode, bool onlyVirtual);
	bool baseVirtual;
	AccessType type;
	Class *base;
};


/**
 * @class Class
 * @brief A C++ class representing a parallel class, used by the parser.
 *
 *
 */
class Class: public CodeData, public DataType
{
public:
	Class(char *clname, CodeFile *file);
	~Class();

	virtual bool IsParClass();
	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

	virtual int Type() { return TYPE_CLASS;};
	virtual void GenerateCode(CArrayChar &output);

	void SetFileInfo(char *file);
	char *GetFileInfo();
	void SetStartLine(int num);
	void SetEndLine(int  num);

	char *Parse(char *str);
	void AddMember(ClassMember *t);

	void SetClassID(char *id);
	void SetPureVirtual(bool val);


	static unsigned IDFromString(char *str);

	bool hasMethod(Method &x);
	bool methodInBaseClass(Method &x);
	void findPureVirtual(CArrayMethod &lst);


	bool GenerateClient(CArrayChar &code);
	bool GenerateHeader(CArrayChar &code, bool interface);
	bool GenerateBrokerHeader(CArrayChar & code);
	bool GenerateBroker(CArrayChar & code);

	char classid[64];

	CArrayBaseClass baseClass;
	CArrayClassMember memberList;

public:
	static char interface_base[1024];
	static char broker_base[1024];
	static char object_base[1024];

protected:
	char *myFile;
	bool initDone;
	int endid;
	int startline, endline;

	bool noConstructor;
	bool pureVirtual;
	Constructor constructor;

	char *my_interface_base;
	char *my_object_base;
	char *my_broker_base;
};




//Implementation of template

#endif
