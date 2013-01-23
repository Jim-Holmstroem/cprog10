/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "matrix_test.h"

static MatrixTestSuite suite_MatrixTestSuite;

static CxxTest::List Tests_MatrixTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MatrixTestSuite( "matrix_test.h", 66, "MatrixTestSuite", suite_MatrixTestSuite, Tests_MatrixTestSuite );

static class TestDescription_MatrixTestSuite_test_default_constructor : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_default_constructor() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 119, "test_default_constructor" ) {}
 void runTest() { suite_MatrixTestSuite.test_default_constructor(); }
} testDescription_MatrixTestSuite_test_default_constructor;

static class TestDescription_MatrixTestSuite_test_size_constructor : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_size_constructor() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 127, "test_size_constructor" ) {}
 void runTest() { suite_MatrixTestSuite.test_size_constructor(); }
} testDescription_MatrixTestSuite_test_size_constructor;

static class TestDescription_MatrixTestSuite_test_copy_constructor : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_copy_constructor() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 146, "test_copy_constructor" ) {}
 void runTest() { suite_MatrixTestSuite.test_copy_constructor(); }
} testDescription_MatrixTestSuite_test_copy_constructor;

static class TestDescription_MatrixTestSuite_test_size_constructor_quad : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_size_constructor_quad() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 186, "test_size_constructor_quad" ) {}
 void runTest() { suite_MatrixTestSuite.test_size_constructor_quad(); }
} testDescription_MatrixTestSuite_test_size_constructor_quad;

static class TestDescription_MatrixTestSuite_test_zero_size_multiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_zero_size_multiplication() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 288, "test_zero_size_multiplication" ) {}
 void runTest() { suite_MatrixTestSuite.test_zero_size_multiplication(); }
} testDescription_MatrixTestSuite_test_zero_size_multiplication;

static class TestDescription_MatrixTestSuite_test_zero_size_addition : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_zero_size_addition() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 303, "test_zero_size_addition" ) {}
 void runTest() { suite_MatrixTestSuite.test_zero_size_addition(); }
} testDescription_MatrixTestSuite_test_zero_size_addition;

static class TestDescription_MatrixTestSuite_test_zero_size_subtraction : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_zero_size_subtraction() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 316, "test_zero_size_subtraction" ) {}
 void runTest() { suite_MatrixTestSuite.test_zero_size_subtraction(); }
} testDescription_MatrixTestSuite_test_zero_size_subtraction;

static class TestDescription_MatrixTestSuite_test_one_size_multiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_one_size_multiplication() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 331, "test_one_size_multiplication" ) {}
 void runTest() { suite_MatrixTestSuite.test_one_size_multiplication(); }
} testDescription_MatrixTestSuite_test_one_size_multiplication;

static class TestDescription_MatrixTestSuite_test_one_size_addition : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_one_size_addition() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 351, "test_one_size_addition" ) {}
 void runTest() { suite_MatrixTestSuite.test_one_size_addition(); }
} testDescription_MatrixTestSuite_test_one_size_addition;

static class TestDescription_MatrixTestSuite_test_one_size_subtraction : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test_one_size_subtraction() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 372, "test_one_size_subtraction" ) {}
 void runTest() { suite_MatrixTestSuite.test_one_size_subtraction(); }
} testDescription_MatrixTestSuite_test_one_size_subtraction;

#include <cxxtest/Root.cpp>
