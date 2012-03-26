#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/types.h>
#include <time.h>

#define MIN_CLASSID 1000


CodeData::CodeData(CodeFile *file)
{
	codeFile=file;
}

CodeData::~CodeData()
{
}

void CodeData::GenerateCode(CArrayChar &output)
{
}

//End CodeData implementation







