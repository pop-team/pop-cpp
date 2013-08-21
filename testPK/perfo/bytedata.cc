#include <stdlib.h>
#include "bytedata.h"

ByteData::ByteData() {theData=NULL; n=0;}
ByteData::~ByteData()
{ 
/*if (theData!=NULL) free(theData);*/ theData=NULL; n=0;
}

void ByteData::Serialize(paroc_buffer &buf, bool pack)
{
  if (pack)
  { 
    buf.Pack(&n,1);
    buf.Pack(theData,n);
  }
  else /* Unpack */
  {
    buf.UnPack(&n,1);
    if (theData != NULL) free(theData);
    theData=(char*)malloc(n);
    if (theData==NULL) {printf("\nMEMORY OVERFLOW !!!!\n"); exit(0);}
    buf.UnPack(theData, n);
  }
}

