#ifndef _PAROC_TYPE_H
#define _PAROC_TYPE_H

#define MAXSTDTYPES 15

#include "parser_common.h"

#define TYPE_BASE 0
#define TYPE_STRUCT 1
#define TYPE_EQUAL 2
#define TYPE_PTR 3
#define TYPE_ARRAY 4
#define TYPE_PARCLASS 5


class DataType
{
 public:
  DataType(char *tname);
 virtual ~DataType();

  virtual int CanMarshal();
  virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
  virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

  virtual bool GetDeclaration(char *varname, char *output);
  virtual bool GetCastType(char *output);
  virtual void GetExpandType(char *output);

  char *GetName();
  void SetName(const char *tname);

  virtual int IsPointer();

  virtual bool IsArray();
  virtual bool IsPrototype();

  virtual bool IsStandardType();
  virtual bool IsParClass();

  virtual bool Same(DataType *other);
  virtual bool Same(char *tname);

  virtual DataType *GetBaseType();

  void Mark(bool ismarked);
  bool IsMarked();

  static char stdType[MAXSTDTYPES][32];
  static int counter;
  static bool FindVarName(const char *var, char name[256]);

 protected:
  char *name;
  bool isStandard;
  bool isparclass;
  bool mark;
};

class TypeArray: public DataType
{
 public:
  TypeArray(char *name, char *cardstr, DataType *base);
  ~TypeArray();
  void GetCardinalSize(char *size);

  //  virtual bool Same(DataType *other);

  virtual int CanMarshal();
  virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
  virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

  virtual bool GetDeclaration(char *varname, char *output);
  virtual bool GetCastType(char *output);
  virtual void GetExpandType(char *output);

  virtual bool IsArray();
 
 protected:
  char *cardinal;
  DataType *typebase;

};

class TypePtr: public DataType
{
 public:
  TypePtr(char *name, int level, DataType *base);
  ~TypePtr();

  virtual int CanMarshal();
  virtual void Marshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);
  virtual void DeMarshal(char *varname, char *bufname, char *sizehelper, CArrayChar &output);

  virtual bool GetDeclaration(char *varname, char *output);
  virtual void GetExpandType(char *output);

  virtual void SetSize(char *sizestr);

  virtual int IsPointer();
  virtual DataType *GetBaseType();

 protected:
  DataType *typebase;
  int nptr;
  char *size;

};

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

class TypeStruct: public DataType
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

class TypeSeqClass: public DataType
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
#endif
