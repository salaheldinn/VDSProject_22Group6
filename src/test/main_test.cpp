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



/*Test Function "const BDD_ID &Manager::True(){}"*/
TEST(ManagerFuncsTest, TestTrueFunc) {

    ClassProject:: Manager Test_ROBDD   ;
    EXPECT_EQ(1,Test_ROBDD.True());
}

/*Test Function "const BDD_ID &Manager::False(){}"*/
TEST(ManagerFuncsTest, TestFalseFunc) {

    ClassProject:: Manager Test_ROBDD   ;
    EXPECT_EQ(0,Test_ROBDD.False());
}



/*Test Function "bool Manager::isConstant(BDD_ID f){};*/
TEST(ManagerFuncsTest, Test_isConstantFunc) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;
    bool Loc_isLeafNode;

    /**/
    Test_ROBDD.createVar("a");

    for (ClassProject::BDD_ID i = 0 ; i < 3 ; i++)
    {

        Loc_isLeafNode = Test_ROBDD.isConstant(i);
        if (i > 1)
        {
            EXPECT_FALSE(Loc_isLeafNode);
        }
        else
        {
            EXPECT_TRUE(Loc_isLeafNode);
        } //end if

    } //end for
} //end func

/*Test Function "bool Manager::isVariable(BDD_ID x){};"*/
TEST(ManagerFuncsTest, Test_isVarFunc) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;
    bool Loc_isVarNode;

    /**/
    Test_ROBDD.createVar("a");

    for (ClassProject::BDD_ID i = 0 ; i < 3 ; i++)
    {

        Loc_isVarNode = Test_ROBDD.isVariable(i);
        /*this if statement need to be updated after implementing and2, or2, ... */
        if (i <= 1)
        {
            EXPECT_FALSE(Loc_isVarNode);
        }
        else
        {
            EXPECT_TRUE(Loc_isVarNode);
        } //end if

    } //end for
} //end func



/*Test Function "BDD_ID Manager::topVar(BDD_ID f){};"*/
TEST(ManagerFuncsTest, Test_topVarFunc) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;

    /**/
    Test_ROBDD.createVar("a");

    for (ClassProject::BDD_ID i = 0 ; i < 3 ; i++)
    {
        EXPECT_EQ(Test_ROBDD.unique_table[i].topvar, Test_ROBDD.topVar(i));
    }


}

TEST(ManagerFuncsTest, Test_hash_unique_table) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID id_of_a = Test_ROBDD.createVar("a");
    //find entry of True
    auto indx = Test_ROBDD.hash_unique_table.find({1, 1, 1});
    EXPECT_EQ(indx->second, 1);
    //find entry of a
    indx = Test_ROBDD.hash_unique_table.find({1, 0, 2});
    EXPECT_EQ(indx->second, id_of_a);
    //find non-existent entry
    indx = Test_ROBDD.hash_unique_table.find({1, 0, 3});
    EXPECT_EQ(indx, Test_ROBDD.hash_unique_table.end());
}



/*Test Function "size_t Manager::uniqueTableSize(){};"*/
/*this test will be improved after implementing and2, or2...functions*/
TEST(ManagerFuncsTest, Test_uniqueTableSize) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;

    Test_ROBDD.createVar("a");
    Test_ROBDD.createVar("b");
    EXPECT_EQ(4, Test_ROBDD.uniqueTableSize());
}
