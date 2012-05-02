#include <cxxtest/TestSuite.h>

#include "must_follow_a.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:
    void test_a_is_second_to_last( void )
    {
        char vek[] = {'x', 'x', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 1);
    }

	//Our own test functions

    void test_min_fail( void )
    {
        char vek[] = {'a', 'b'};
        int result = must_follow_a(vek, 2, 'a', 'b');
        TS_ASSERT_EQUALS( result, 1);
    }

    void test_min2_fail( void )
    {
        char vek[] = {'a', 'b','a','b'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 2);
    }

	void test_fast_nofail( void )
    {
        char vek[] = {'s','n','a', 'b','b'};
        int result = must_follow_a(vek, 5, 'a', 's');
        TS_ASSERT_EQUALS( result, 0);
    }

};
