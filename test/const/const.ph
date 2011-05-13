#ifndef _TESTMETHOD_PH
#define _TESTMETHOD_PH

#ifndef _POPC_
#include "nopopc.h"
#endif


parclass TestConst
{
public:

	TestConst();
	
	// Methodes with const in their signature as parameter
	sync conc void TestParam_Int(int);
	sync conc void TestParam_ConstInt(const int); // const Int by copy
	sync conc void TestParam_IntConst(int const); // const Int by copy 
	sync conc void TestParam_ConstIntRef(const int&); // const Int by ref
	sync conc void TestParam_IntConstRef(int const &); // const Int by ref 
	sync conc void TestParam_IntConstPtr(int const * ); // ptr to const 
	sync conc void TestParam_ConstIntPtr(const int * ); // ptr to const 
	sync conc void TestParam_IntPtrConst(int * const ); // const Ptr 
	sync conc void TestParam_IntPtrConstPtrConst(int * const * const ); // const Ptr const Ptr  
	sync conc void TestParam_IntPtrConstPtrConstPtrPtrPtrConst(int * const * const * * * const); // to test * const generationg order
	sync conc void TestParam_IntConstPtrConst(int const * const); //constPtrToConst 

	// Methodes with const as return value	--> Attantion, more possible wit & compination
	sync conc int const TestReturn_IntConst(); // const Int by copy 
	sync conc const int TestReturn_ConstInt(); // const Int by copy  
	//sync conc int const & TestReturn_IntConstRef(); // const Int by ref 
	//sync conc const int & TestReturn_ConstIntRef(); // const Int by ref  
	sync conc int const * TestReturn_IntConstPtr();// ptr to const 
	sync conc const int * TestReturn_ConstIntPtr();// ptr to const  
	sync conc int * const TestReturn_IntPtrConst(); // const Ptr 
	sync conc int const * const TestReturn_IntConstPtrConst();
	
	// some methodes with special POP-C++ Syntax
	int const TestReturn_normal_IntConst();
	const int TestReturn_normal_ConstInt();
	[out] const int TestReturn_ConstIntMarshal(); // const Int by copy       
	
	// Methode with content is not modivied
	sync conc void TestGlobalConst() const;
	
	// Methode which contains different const Variables
	sync conc void TestConstVars(); // compiles and runs
	
private:

	// TODO del
	//static const int A_CONST = 42;
	int aVar; // variable used to return test
	
	#ifdef _POPC_
		classuid(1001);
	#endif

};

#endif
