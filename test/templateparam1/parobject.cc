#include <stdio.h>
#include "parobject.ph"

ParObject::ParObject()
{
	printf("TemplateParam1: Object ParObject created on localhost\n");
	theData.GetData()->SetIdent(0);
}

ParObject::ParObject(POPString machine)
{
	printf("TemplateParam1: Object ParObject created on %s\n"/*,(const char *)POPSystem::GetHost()*/);
	theData.GetData()->SetIdent(1);
}

ParObject::~ParObject()
{
	printf("TemplateParam1: Destroying the object ParObject...%d\n", theData.GetData()->GetIdent());
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


