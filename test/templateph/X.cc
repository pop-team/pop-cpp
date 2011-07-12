#include "X.h"
#include <stdio.h>

X::X() {ident=0;printf("Template: Contructing X object-%d\n", ident);}

X::~X() {printf("Template: Destroying X object-%d\n", ident);}

void X::SetIdent(int i) {printf("Template: SetIdent on X object-%d\n", i); ident = i;}

int X::GetIdent() {printf("Template: GetIdent on X object-%d\n", ident); return ident;}

//virtual X::void Serialize(POPBuffer &buf, bool pack) {;}
