#ifndef _PAROC_STRING_H
#define _PAROC_STRING_H

class paroc_string
{
 public:
  paroc_string();
  paroc_string(const char *x);
  paroc_string(const char *x, int n);
  paroc_string(const paroc_string &x);

  ~paroc_string();
  operator const char *() const;

  const char *operator =(const char *x);
  const paroc_string & operator =(const paroc_string &x);
  void operator +=(const char *x);
  paroc_string operator +  (const paroc_string &x);

  void substring(int start, int end, paroc_string &sub);
 
  int Length() const;
  char *GetString();

 protected:
  char *data;
};

typedef paroc_string POPString;

#endif










