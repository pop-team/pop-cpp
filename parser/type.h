#ifndef _POPC_TYPE_H
#define _POPC_TYPE_H

#define MAXSTDTYPES 24
#define MAXSTLTYPES 8

#include "parser_common.h"

#define TYPE_BASE 0
#define TYPE_STRUCT 1
#define TYPE_EQUAL 2
#define TYPE_PTR 3
#define TYPE_ARRAY 4
#define TYPE_PARCLASS 5

class CodeFile;

/**
 * @class DataType
 * @brief A C++ class representing a data type, used by the parser.
 *
 *
 */

class DataType
{
public:
	/**
	* @brief A constructor for the DataType class
	*
	* @param tname Name of the type (without * &)
	*/
	DataType(char *tname);
	/**
	 * @brief A destructor for the DataType class
	 *
	 */
	virtual ~DataType();

	/**
	 * @brief  Can the data type be marshalled
	 *
	 *    A data type can be marshalled either if it is a standard type (int, float, paroc_string, ...) or if a marshalling/Serialize function is defined.
	 *
	 * @returns true/false
	 */
	virtual int CanMarshal();
	/**
	 * @brief  Print the marshalling code ot the output
	 *
	 *
	 * @param varname Name of the variable
	 * @param bufname Communication buffer
	 * @param sizehelper (not used)
	 * @param output output
	 */
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

	/**
	 * @brief  Prints the declaration line to output
	 * @param varname Name of the variable
	 * @param output output
	 * @returns true if executed correctly
	 *
	 */
	virtual bool GetDeclaration(const char *varname, char *output);
	/**
	 * @brief  Prints the cast type line to output
	 * @param output output
	 * @returns true if executed correctly
	 * (=declaration line without the variable name)
	 */
	virtual bool GetCastType(char *output);
	/**
	 * @brief  Prints the expanded type line to output
	 * @param output output
	 * @returns true if executed correctly
	 *
	 */
	virtual void GetExpandType(char *output);

	char *GetName();
	void SetName(const char *tname);

	virtual int IsPointer();
	virtual bool IsArray();
	virtual bool IsPrototype();

	virtual bool IsStandardType();
	virtual bool IsParClass();

	/**
	 * @brief  Compares this data type to an other.
	 * @param other Other data type
	 * @returns true/false
	 */
	virtual bool Same(DataType *other);
	/**
	 * @brief  Compares this data type to an other.
	 * @param tname Other data type
	 * @returns true/false
	 */
	virtual bool Same(char *tname);
	/**
	 * @brief  Retreives the base type of the current type.
	 * @returns data type or NULL
	 *
	 * recurrent, if a standard type, returns NULL
	 */
	virtual DataType *GetBaseType();

	void Mark(bool ismarked);
	bool IsMarked();

	void SetOwnerFile(CodeFile *owner);
	CodeFile * GetOwnerFile();

	static char stdType[MAXSTDTYPES][32];
	static int counter;
	static bool FindVarName(const char *var, char name[256]);

protected:
	char *name;
	bool isStandard;
	bool isparclass;
	bool mark;
	CodeFile *codefile;
};

/**
 * @class TypeArray
 * @brief A C++ class representing an array data type, used by the parser.
 *
 *
 */
class TypeArray: public DataType
{
public:
	/**
	* @brief  Constructor
	* @param name
	* @param cardstr
	* @param base
	 */
	TypeArray(char *name, char *cardstr, DataType *base);
	/**
	  * @brief  Destructor
	 */
	~TypeArray();
	void GetCardinalSize(char *size);

	//  virtual bool Same(DataType *other);

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

	virtual bool GetDeclaration(const char *varname, char *output);
	virtual bool GetCastType(char *output);
	virtual void GetExpandType(char *output);

	virtual bool IsArray();

protected:
	char *cardinal;
	DataType *typebase;

};

/**
 * @brief  A C++ class representing a pointer data type, used by the parser.
 */
class TypePtr: public DataType
{
public:
	TypePtr(char *name, int level, DataType *base);
	~TypePtr();

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

	virtual bool GetDeclaration(const char *varname, char *output);
	virtual void GetExpandType(char *output);

	virtual void SetSize(char *sizestr);

	virtual int IsPointer();
	virtual DataType *GetBaseType();

protected:
	DataType *typebase;
	int nptr;
	char *size;

};

/**
 * @brief  A C++ class representing a standard data type, used by the parser.
 */
class TypeEqual: public DataType
{
public:
	TypeEqual(char *name, DataType *atype);

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

	//  virtual bool Same(DataType *other);
	//  virtual bool Same(char *tname);

	virtual bool GetCastType(char *output);
	virtual void GetExpandType(char *output);

	virtual int IsPointer();
	virtual bool IsArray();
	virtual bool IsParClass();

	virtual DataType *GetBaseType();
protected:
	DataType *type;

};

/**
 * @brief  A C++ class representing a structure, used by the parser.
 */
class TypeStruct: public virtual DataType
{
public:
	TypeStruct(char *name);
	~TypeStruct();

	void Add(DataType *elem, char *ename);

	virtual bool IsPrototype();

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
protected:
	paroc_list<DataType *> attr_types;
	paroc_list<char *> attr_names;
};

/**
 * @brief  A C++ class representing sequential class, used by the parser.
 */
class TypeSeqClass: public virtual DataType
{
public:
	TypeSeqClass(char *name);
	~TypeSeqClass();
	void AddBase(DataType *t);

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	paroc_list<DataType *> bases;
};

/**
 * @brief  A C++ class representing a class, used by the parser.
 */
class TypeClassStruct: virtual public TypeSeqClass, virtual public TypeStruct
{
public:
	TypeClassStruct(char *name, bool classtype);
	~TypeClassStruct();

	bool SetTypeClass(bool classtype);

	virtual bool IsPrototype();

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

protected:
	bool isClass;
};


class TypeTemplate: public virtual DataType
{
public:
	TypeTemplate(char *name);
	~TypeTemplate();
	void AddTemplate(DataType *eltype, bool isRef);

	virtual bool GetDeclaration(const char *varname, char *output);

	virtual int CanMarshal();
	virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
	virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

private:
	paroc_array<DataType *> elements;
	paroc_array<bool> refStatus;
	static char stlType[MAXSTLTYPES][32];


};

#endif
