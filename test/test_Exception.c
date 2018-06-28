#include <stdio.h>
#include "CException.h"
#include "unity.h"
#include "Exception.h"
#include <stdarg.h>
#include <malloc.h>

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

void throwError2(int errorCode, char *msg)
{
  Exception *ex = (Exception *)malloc(sizeof(Exception));
  ex->errorCode = errorCode;
  ex->errorMsg = msg;
  Throw(ex);
}

char *getName(int index)
{
	if(index >= 4 || index <0)
  {
    throwError(3, "Error: Out of bound of the array. Index given was %d", index);
  }
	return names[index];
}

int add(int num, ...)
{
  va_list valist;
  int i, sum=0;
  
  va_start(valist, num);
  for(i=0;i<num;i++)
  {
    sum += va_arg(valist, int);
  }
  va_end(valist);
  return sum;
}

void printAllNumber(char *format, ...)
{
  va_list valist;
  char *buffer;
  int neededSize;
  
  va_start(valist, format);
  neededSize = vsnprintf(NULL, 0, format, valist) + 1;
  buffer = malloc(neededSize);
  vsnprintf(buffer, 1024, format, valist);
  va_end(valist);
  
  printf(buffer);
}

void test_printAllNumber(void)
{
  printAllNumber("%f, %d, %x, %s", 1234.56789, 654217, 255, "Ooil");
}

void test_add_given_1_2_3_4_5_expect_15(void)
{
  int result = add(5,1,2,3,4,5);
  TEST_ASSERT_EQUAL(15, result);
}

void test_add_given_9_8_7_expect_24(void)
{
  int result = add(3,9,8,7);
  TEST_ASSERT_EQUAL(24, result);
}

void test_add_given_6_28_2_0_10_1_expect_47(void)
{
  int result = add(6, 6,28,2,0,10,1);
  TEST_ASSERT_EQUAL(47, result);
}

void test_getName_given_1_expect_David(void)
{
	CEXCEPTION_T e;
    char *name;
	
	Try{
		name = getName(1);
		TEST_ASSERT_EQUAL_STRING("David", name);
	}Catch(e){
		TEST_FAIL_MESSAGE(e->errorMsg);
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
		printf("\t%s (error code: %d)", e->errorMsg, e->errorCode);
    freeError(e);
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
		printf("\t%s", e->errorMsg);
    freeError(e);
	}
	
//	TEST_ASSERT_EQUAL_STRING("David", name);
}
