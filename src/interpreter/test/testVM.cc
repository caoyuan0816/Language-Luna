#include "gtest/gtest.h"

class TestVM : public ::testing::Test {
protected:
	TestVM(){}
};

TEST_F (TestVM, LoadInstructions1){
	EXPECT_EQ(1, 1);
}