/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test_must_follow_a.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test_must_follow_a.cpp", 5, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_a_is_second_to_last : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 8, "test_a_is_second_to_last" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last(); }
} testDescription_MyTestSuite_test_a_is_second_to_last;

static class TestDescription_MyTestSuite_test_min_fail : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_min_fail() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 17, "test_min_fail" ) {}
 void runTest() { suite_MyTestSuite.test_min_fail(); }
} testDescription_MyTestSuite_test_min_fail;

static class TestDescription_MyTestSuite_test_min2_fail : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_min2_fail() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 24, "test_min2_fail" ) {}
 void runTest() { suite_MyTestSuite.test_min2_fail(); }
} testDescription_MyTestSuite_test_min2_fail;

static class TestDescription_MyTestSuite_test_fast_nofail : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_fast_nofail() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 31, "test_fast_nofail" ) {}
 void runTest() { suite_MyTestSuite.test_fast_nofail(); }
} testDescription_MyTestSuite_test_fast_nofail;

#include <cxxtest/Root.cpp>
