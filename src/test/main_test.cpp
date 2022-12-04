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


/*Test Function "BDD_ID Manager::coFactorTrue(BDD_ID f){};"*/
/*this test will be improved after implementing and2, or2...functions*/
TEST(ManagerFuncsTest, Test_coFactorTrue1) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;

    /**/
    Test_ROBDD.createVar("a");

    for (ClassProject::BDD_ID i = 0 ; i < 3 ; i++)
    {
        EXPECT_EQ(Test_ROBDD.unique_table[i].high, Test_ROBDD.coFactorTrue(i));
    }
}

/*Test Function "BDD_ID Manager::coFactorFalse(BDD_ID f){};"*/
/*this test will be improved after implementing and2, or2...functions*/
TEST(ManagerFuncsTest, Test_coFactorFalse1) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;

    /**/
    Test_ROBDD.createVar("a");

    for (ClassProject::BDD_ID i = 0 ; i < 3 ; i++)
    {
        EXPECT_EQ(Test_ROBDD.unique_table[i].low, Test_ROBDD.coFactorFalse(i));
    }
}

TEST(ManagerFuncsTest, Test_find_or_add_unique_table) {
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID id_of_a = Test_ROBDD.createVar("a");
    //find ID of a
    EXPECT_EQ(Test_ROBDD.find_or_add_unique_table(2, 1, 0), id_of_a);
    //add new entry
    EXPECT_EQ(Test_ROBDD.find_or_add_unique_table(3, 1, 0), 3);
}


/*Test Function "BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){}"*/
/*this test will be improved after implementing and2, or2...functions*/
TEST(ManagerFuncsTest, Test_ite) {

    /*Declare used variables*/
    ClassProject::Manager Test_ROBDD;

    /**/
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");


    /*All terminal cases*/
    ClassProject::BDD_ID  exp_a= Test_ROBDD.ite(1,a,b);
    ClassProject::BDD_ID  exp_b= Test_ROBDD.ite(0,a,b);
    ClassProject::BDD_ID  exp_a2= Test_ROBDD.ite(a,1,0);
    ClassProject::BDD_ID  exp_b2= Test_ROBDD.ite(a,b,b);
    ClassProject::BDD_ID  exp_notA= Test_ROBDD.ite(a,0,1);
    ClassProject::BDD_ID  exp_a3 = Test_ROBDD.ite(exp_notA,0,1); //to test computed table, "a" should not be repeated in unique table


    /*Terminal Cases test*/
    EXPECT_EQ(2, exp_a);
    EXPECT_EQ(2, exp_a2);
    EXPECT_EQ(2, exp_a3);

    EXPECT_EQ(3, exp_b);
    EXPECT_EQ(3, exp_b2);

    EXPECT_EQ(4, exp_notA);
    EXPECT_EQ(2, Test_ROBDD.unique_table[exp_notA].topvar);
    EXPECT_EQ(0, Test_ROBDD.unique_table[exp_notA].high);
    EXPECT_EQ(1, Test_ROBDD.unique_table[exp_notA].low);

}

TEST(ManagerFuncsTest, Test_getTopVarName) {
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID id_of_a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID id_of_b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID id_of_a_and_b = Test_ROBDD.ite(id_of_a, id_of_b, 0);
    EXPECT_EQ(Test_ROBDD.getTopVarName(id_of_a_and_b), "a");
    EXPECT_EQ(Test_ROBDD.getTopVarName(id_of_b), "b");
}

TEST(ManagerFuncsTest, Test_findNodes) {
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID id_of_a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID id_of_b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID id_of_a_and_b = Test_ROBDD.ite(id_of_a, id_of_b, 0);
    std::set<ClassProject::BDD_ID> found_nodes;
    Test_ROBDD.findNodes(id_of_a_and_b, found_nodes);
    EXPECT_EQ(found_nodes.size(), 4);
    EXPECT_NE(found_nodes.find(0), found_nodes.end());
    EXPECT_NE(found_nodes.find(1), found_nodes.end());
    EXPECT_NE(found_nodes.find(id_of_b), found_nodes.end());
    EXPECT_NE(found_nodes.find(id_of_a_and_b), found_nodes.end());
}

TEST(ManagerFuncsTest, Test_findVars) {
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID id_of_a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID id_of_b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID id_of_a_and_b = Test_ROBDD.ite(id_of_a, id_of_b, 0);
    std::set<ClassProject::BDD_ID> found_vars;
    Test_ROBDD.findVars(id_of_a_and_b, found_vars);
    EXPECT_EQ(found_vars.size(), 4);
    EXPECT_NE(found_vars.find(0), found_vars.end());
    EXPECT_NE(found_vars.find(1), found_vars.end());
    EXPECT_NE(found_vars.find(id_of_b), found_vars.end());
    EXPECT_NE(found_vars.find(id_of_a), found_vars.end());
}


TEST(ManagerFuncsTest, Test_neg) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID not_a = Test_ROBDD.neg(a);
    EXPECT_EQ(Test_ROBDD.topVar(not_a), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(not_a), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.coFactorFalse(not_a), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.neg(0), Test_ROBDD.True());
}

TEST(ManagerFuncsTest, Test_and2) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aANDb = Test_ROBDD.and2(a,b);

    EXPECT_EQ(Test_ROBDD.topVar(aANDb), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(aANDb), b);
    EXPECT_EQ(Test_ROBDD.coFactorFalse(aANDb), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.and2(0,1), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.and2(1,0), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.and2(1,1), Test_ROBDD.True());
}


TEST(ManagerFuncsTest, Test_or2) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aORb = Test_ROBDD.or2(a,b);

    EXPECT_EQ(Test_ROBDD.topVar(aORb), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(aORb), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.coFactorFalse(aORb), b);
    EXPECT_EQ(Test_ROBDD.or2(0,0), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.or2(1,0), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.or2(0,1), Test_ROBDD.True());
}