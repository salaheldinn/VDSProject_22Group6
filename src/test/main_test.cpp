//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(HelloTest, BasicAssertions) {
    EXPECT_EQ(7 * 6, 42);
}

TEST(ManagerFuncsTest, TestUniqueTableInit) {

    ClassProject:: Manager Test_ROBDD   ;

    EXPECT_EQ(0,Test_ROBDD.unique_table[0].id);
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].high);
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].low);
    EXPECT_EQ(0,Test_ROBDD.unique_table[0].topvar);
    EXPECT_EQ("False",Test_ROBDD.unique_table[0].label);

    EXPECT_EQ(1,Test_ROBDD.unique_table[1].id);
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].high);
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].low);
    EXPECT_EQ(1,Test_ROBDD.unique_table[1].topvar);
    EXPECT_EQ("True",Test_ROBDD.unique_table[1].label);
}

