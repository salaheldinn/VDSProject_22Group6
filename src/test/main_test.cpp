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
/*Test the Constructor Manager*/
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

/*Test Function "BDD_ID Manager::createVar(const std::string &label){};"*/
TEST(ManagerFuncsTest, TestCreateVar) {

    ClassProject:: Manager Test_ROBDD   ;
    ClassProject:: BDD_ID Test_ID;

    for (int i = 2 ; i < 10 ; i++)
    {

        Test_ID = Test_ROBDD.createVar("Test");

        EXPECT_EQ(Test_ID,Test_ROBDD.unique_table[i].id);
        EXPECT_EQ("Test",Test_ROBDD.unique_table[i].label);
        EXPECT_EQ(1,Test_ROBDD.unique_table[i].high);
        EXPECT_EQ(0,Test_ROBDD.unique_table[i].low);
        EXPECT_EQ(i,Test_ROBDD.unique_table[i].topvar);

    }

}