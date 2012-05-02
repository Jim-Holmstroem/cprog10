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
};
