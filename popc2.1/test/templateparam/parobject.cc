#include <stdio.h>
#include "parobject.ph"

ParObject::ParObject()
{
  printf("TemplateParam: Object ParObject created on localhost\n");
  theData.GetData()->SetIdent(0);
}

ParObject::ParObject(paroc_string machine)
{
  printf("TemplateParam: Object ParObject created on %s\n"/*,POPGetHost()*/);
  theData.GetData()->SetIdent(1);
}

ParObject::~ParObject()
{
  printf("TemplateParam: Destroying the object ParObject...%d\n", theData.GetData()->GetIdent());
}

void ParObject::SetTheData(X d)
{
  theData.SetData(d);
}

X ParObject::GetTheData()
{
  return *(theData.GetData());
}

@pack(ParObject);


