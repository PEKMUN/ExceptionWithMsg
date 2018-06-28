#include <stdio.h>
#include "CException.h"
#include "unity.h"
#include "Exception.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//name is array 3 of pointer to char
char *names[] = {
	"Ali",
	"David",
	"Ah Beng",
	"Sally"
};

char *getName(int index)
{
	if(index >= 4 || index <0)
		Throw("Error: Out of bound of the array. Please try again");
	return names[index];
}

void test_getName_given_1_expect_David(void)
{
	CEXCEPTION_T e;
    char *name;
	
	Try{
		name = getName(1);
		TEST_ASSERT_EQUAL_STRING("David", name);
	}Catch(e){
		printf("error code:%d\n", e);
	}
}

void test_getName_given_minus_1_expect_ERR_OUT_OF_BOUND(void)
{
	CEXCEPTION_T e;
    char *name;
	
	Try{
		name = getName(-1);
		TEST_FAIL_MESSAGE("Expected ERR_OUT_OF_BOUND to be thrown, but none.");
	}Catch(e){
		printf("Under test_getName_given_minus_1_expect_ERR_OUT_OF_BOUND:\n");
		printf("\t%s", e);
	}
	
//	TEST_ASSERT_EQUAL_STRING("David", name);
}

void test_getName_given_4_expect_ERR_OUT_OF_BOUND(void)
{
	CEXCEPTION_T e;
    char *name;
	
	Try{
		name = getName(4);
		TEST_FAIL_MESSAGE("Expected ERR_OUT_OF_BOUND to be thrown, but none.");
	}Catch(e){
		printf("Under test_getName_given_4_expect_ERR_OUT_OF_BOUND:\n");
		printf("\t%s", e);
	}
	
//	TEST_ASSERT_EQUAL_STRING("David", name);
}
