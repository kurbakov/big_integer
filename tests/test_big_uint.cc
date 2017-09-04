#include "../dependencies/googletest/include/gtest/gtest.h"
#include "../scr/big_uint.h"

// info:
// https://github.com/google/googletest/blob/master/googletest/docs/Primer.md

TEST(BigUInt, Constructor) {
	// call the class
	BigNumber::BigUInt x;
	BigNumber::BigUInt y(x);

	int* v = new int[10];
	BigNumber::BigUInt z(v, 10);

	// memory leak
	long long rep = 999999;
	for(int i=0; i<rep; i++){ BigNumber::BigUInt num; }
	for(int i=0; i<rep; i++){ BigNumber::BigUInt num(x); }
}

TEST(BigUInt, OperatorAccessElement){
	BigNumber::BigUInt x;
	ASSERT_EQ(x[0], 0);
	
	x[0] = 10;
	ASSERT_EQ(x[0], 10);
	ASSERT_NE(x[0], 1);
	for(int i=0; i<999; i++){
		x[1] = i;
		ASSERT_EQ(x[1], i);
	}

	BigNumber::BigUInt y, z;
	// 10 is the length of the BigUInt (variable SIZE)
	for(int k=0; k<10; k++){ 
		ASSERT_EQ(y[k], z[k]);
	}
}

TEST(BigUInt, OperatorAssignInt){
	BigNumber::BigUInt x;
	x=1;
	ASSERT_EQ(x[0], 1);
	ASSERT_EQ(x[1], 0);
	ASSERT_STREQ(x.to_string().c_str(), "1");

	x=12345;
	BigNumber::BigUInt y;
	y=12345;
	ASSERT_STREQ(x.to_string().c_str(), y.to_string().c_str());
}


TEST(BigUInt, OperatorAssignBigUInt){
	BigNumber::BigUInt x,y ;
	ASSERT_STREQ(x.to_string().c_str(), y.to_string().c_str());
	
	x=12345;
	y=x;
	ASSERT_STREQ(x.to_string().c_str(), y.to_string().c_str());
	x=1234;
	ASSERT_STRNE(x.to_string().c_str(), y.to_string().c_str());
}


TEST(BigUInt, OperatorEqual){}


TEST(BigUInt, OperatorNotEqual){}


TEST(BigUInt, OperatorGreater){}


TEST(BigUInt, OperatorGreaterEqual){}


TEST(BigUInt, OperatorLower){}


TEST(BigUInt, OperatorLowerequal){}


TEST(BigUInt, OperatorAddInt){}


TEST(BigUInt, OperatorAddBigUInt){}


TEST(BigUInt, OperatorSubstractInt){}


TEST(BigUInt, OperatorSubstractBigUInt){}


TEST(BigUInt, OperatorMultiplyInt){}


TEST(BigUInt, OperatorMultiplyBigUInt){}


TEST(BigUInt, OperatorDivideInt){}


TEST(BigUInt, OperatorDivideBigUInt){}


TEST(BigUInt, OperatorModuloInt){}


TEST(BigUInt, OperatorModuloBigUInt){}

