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
CxxTest::StaticSuiteDescription suiteDescription_MatrixTestSuite( "matrix_test.h", 77, "MatrixTestSuite", suite_MatrixTestSuite, Tests_MatrixTestSuite );

static class TestDescription_MatrixTestSuite_testSquareConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testSquareConstructor() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 110, "testSquareConstructor" ) {}
 void runTest() { suite_MatrixTestSuite.testSquareConstructor(); }
} testDescription_MatrixTestSuite_testSquareConstructor;

static class TestDescription_MatrixTestSuite_testNormalConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testNormalConstructor() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 127, "testNormalConstructor" ) {}
 void runTest() { suite_MatrixTestSuite.testNormalConstructor(); }
} testDescription_MatrixTestSuite_testNormalConstructor;

static class TestDescription_MatrixTestSuite_testElementwiseOperations : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testElementwiseOperations() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 154, "testElementwiseOperations" ) {}
 void runTest() { suite_MatrixTestSuite.testElementwiseOperations(); }
} testDescription_MatrixTestSuite_testElementwiseOperations;

static class TestDescription_MatrixTestSuite_testMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testMultiplication() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 210, "testMultiplication" ) {}
 void runTest() { suite_MatrixTestSuite.testMultiplication(); }
} testDescription_MatrixTestSuite_testMultiplication;

static class TestDescription_MatrixTestSuite_testTranspose : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testTranspose() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 280, "testTranspose" ) {}
 void runTest() { suite_MatrixTestSuite.testTranspose(); }
} testDescription_MatrixTestSuite_testTranspose;

static class TestDescription_MatrixTestSuite_testOutput : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testOutput() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 317, "testOutput" ) {}
 void runTest() { suite_MatrixTestSuite.testOutput(); }
} testDescription_MatrixTestSuite_testOutput;

#include <cxxtest/Root.cpp>
