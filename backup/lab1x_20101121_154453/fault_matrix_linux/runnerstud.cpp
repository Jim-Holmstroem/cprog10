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
#include "matrix_student_test.h"

static MatrixTestSuite suite_MatrixTestSuite;

static CxxTest::List Tests_MatrixTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MatrixTestSuite( "matrix_student_test.h", 9, "MatrixTestSuite", suite_MatrixTestSuite, Tests_MatrixTestSuite );

static class TestDescription_MatrixTestSuite_testIndexOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testIndexOperator() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 19, "testIndexOperator" ) {}
 void runTest() { suite_MatrixTestSuite.testIndexOperator(); }
} testDescription_MatrixTestSuite_testIndexOperator;

#include <cxxtest/Root.cpp>
