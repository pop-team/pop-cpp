#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "const.ph"
#ifndef _POPC_
#include "nopopc.h"
#endif


// =====================================================================
// Empty constructor
// =====================================================================

TestConst::TestConst()
{
	printf("--- Build  ---\n");
	aVar = 33; // init global Privat vor Return tests
}

// =====================================================================
// Methodes with const in their signature as parameter
// =====================================================================

void TestConst::TestParam_Int(int constInt) // by copy
{
	 printf("--> Test Param Int: %d\n", constInt);
}

void TestConst::TestParam_ConstInt(const int constInt) // by copy
{
	 printf("--> Test Param Const Int: %d\n", constInt);
}


// Parser error
void TestConst::TestParam_IntConst(int const constInt) // by copy
{
	 printf("--> Test Param Int Const: %d\n", constInt);
}


void TestConst::TestParam_ConstIntRef(const int & constInt) // by ref
{
	 printf("--> Test Param Const Int &: %d\n", constInt);
}

// Parser error
void TestConst::TestParam_IntConstRef(int const & constInt) // by ref
{
	 printf("--> Test Param Int Const & out: %d\n", constInt);
}


// Parser error
void TestConst::TestParam_IntConstPtr(int const * ptrToConst)
{
	 printf("--> Test Param Int Const *: %d\n", (*ptrToConst));
}

// Parser error
void TestConst::TestParam_ConstIntPtr(const int * ptrToConst)
{
	 printf("--> Test Param Const Int *: %d\n", *ptrToConst);
}

// Parser error
void TestConst::TestParam_IntPtrConst(int * const constPtr)
{
	 printf("--> Test Param Int * Const: %d\n", *constPtr);
}

void TestConst::TestParam_IntPtrConstPtrConst(int * const * const constPtrConstPtr)
{
	 printf("--> Test Param Int * Const * Const: %d\n", **constPtrConstPtr);
}

void TestConst::TestParam_IntPtrConstPtrConstPtrPtrPtrConst(int *const *const * * *const var)
{
	 printf("--> Test Param Int * Const * Const * * * Const: %d\n", *****var);
}

// Parser error
void TestConst::TestParam_IntConstPtrConst(int const * const constPtrToConst)
{
	 printf("--> Test Param Int Const * Const: %d\n", *constPtrToConst);
}

// =====================================================================
// Methodes with const as return value
// =====================================================================

// Parser error
int const TestConst::TestReturn_IntConst()
{
	 return 30;
}

// Parser error
const int TestConst::TestReturn_ConstInt()
{
	 return 30;
}
/*
// Parser error
int const & TestConst::TestReturn_IntConstRef()
{
	 return aVar;
}

// Parser error
const int & TestConst::TestReturn_ConstIntRef()
{
	 return aVar;
}
*/

// Parser error
int const * TestConst::TestReturn_IntConstPtr()
{
	return &aVar;
}

// Parser error
const int * TestConst::TestReturn_ConstIntPtr()
{
	return &aVar;
}

// Parser error
int * const TestConst::TestReturn_IntPtrConst()
{
	return &aVar;
}

// Parser error
int const * const TestConst::TestReturn_IntConstPtrConst()
{
	return &aVar;
}

int const TestConst::TestReturn_normal_IntConst()
{
	 return 3;
}
const int TestConst::TestReturn_normal_ConstInt()
{
	return 4;
}
const int TestConst::TestReturn_ConstIntMarshal()
{
	 return 4;
}

// =====================================================================
// Methode with content is not modivied
// =====================================================================

// Parser error
void TestConst::TestGlobalConst() const
{
	printf("--> Global const\n");
}

// =====================================================================
// Methode which contains different const Variables
// =====================================================================
void TestConst::TestConstVars()
{
	// a Int who is constant
	const int Constant1=96;
	int const Constant1_b = 22;
	
	// variable pointer to a constant integer
	const int * Constant2_1 = &Constant1;
	int const * Constant2_2 = &Constant1;
	
	// constant pointer to a variable integer
	int value_Const3 = 32;
	int * const Constant3  = &value_Const3;
	
	// constant pointer to a constant integer
	int value_Const4 = 4;
	int const * const Constant4 = &value_Const4;
	
	// a constant Referenc
	const int & Constant5 = 39;
	int const & Constant5_b = 92;
	
	// TODO maybe use the vars in some extend.... print out ??
}


void MethodCall()
{
	TestConst t;
	
	printf("Test dif. possible const position\n");

	// ==== Methode param ====
	// init + dev input param
	int tmp_int = 39;
	const int tmp_const_int = 59;
	int const tmp_int_const = 69;
	int * const tmp_int_ptr_const = &tmp_int;
	int * const * const tmp_int_ptr_const_ptr_const = &tmp_int_ptr_const;
	
	// mehtodes call
	t.TestParam_ConstInt(tmp_int);
	t.TestParam_IntConst(tmp_const_int);
	t.TestParam_ConstIntRef(tmp_int_const);
	t.TestParam_IntConstRef(tmp_int_const);
	t.TestParam_IntConstPtr(&tmp_int_const);
	t.TestParam_ConstIntPtr(&tmp_const_int);
	t.TestParam_IntPtrConst(tmp_int_ptr_const);
	t.TestParam_IntPtrConstPtrConst(tmp_int_ptr_const_ptr_const);
	t.TestParam_IntConstPtrConst(&tmp_int_const);
	
	
	// ==== Methode return ====
	printf("--> Test Return Int Const: %d\n", t.TestReturn_IntConst());
	printf("--> Test Return Const Int: %d\n", t.TestReturn_ConstInt());
	//printf("--> Test Return Int Const &: %d\n", t.TestReturn_IntConstRef());
	//printf("--> Test Return Const Int &: %d\n", t.TestReturn_ConstIntRef());
	printf("--> Test Return Int Const *: %d\n", *t.TestReturn_IntConstPtr());
	printf("--> Test Return Const Int *: %d\n", *t.TestReturn_ConstIntPtr());
	printf("--> Test Return Int * Const: %d\n", *t.TestReturn_IntPtrConst());
	printf("--> Test Return Int Const * Const: %d\n", *t.TestReturn_IntConstPtrConst());
	
	// ==== Global const ====
	//t.TestGlobalConst();
	
	// ==== Const variables ====
	t.TestConstVars();
	
	printf("Wait results...\n");
}


int main (int argc, char **argv)
{
	try 
	{
		printf("Method: Starting test..\n");
	
		MethodCall();
	
		printf("Method: test succeeded, destroying objects..\n");
	}
	catch (paroc_exception *e){
		printf("ERROR on using const !!!!");
		return -1;
	}
	
	return 0;
}

#ifdef _POPC_
	@pack(TestConst);
#endif
