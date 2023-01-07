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
    EXPECT_EQ(0,Test_ROBDD.False());
    EXPECT_EQ(0,Test_ROBDD.coFactorTrue(0));
    EXPECT_EQ(0,Test_ROBDD.coFactorTrue(0));
    EXPECT_EQ(0,Test_ROBDD.topVar(0));

    EXPECT_EQ(1,Test_ROBDD.True());
    EXPECT_EQ(1,Test_ROBDD.coFactorTrue(1));
    EXPECT_EQ(1,Test_ROBDD.coFactorTrue(1));
    EXPECT_EQ(1,Test_ROBDD.topVar(1));

    EXPECT_EQ(2,Test_ROBDD.uniqueTableSize());

}

/*Test Function "BDD_ID Manager::createVar(const std::string &label){};"*/
TEST(ManagerFuncsTest, TestCreateVar) {

    ClassProject:: Manager Test_ROBDD   ;
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    EXPECT_EQ(a,Test_ROBDD.topVar(a));
    EXPECT_EQ(1,Test_ROBDD.coFactorTrue(a));
    EXPECT_EQ(0,Test_ROBDD.coFactorFalse(a));
    EXPECT_EQ("a",Test_ROBDD.getTopVarName(a));
    EXPECT_EQ(3,Test_ROBDD.uniqueTableSize());
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
    ClassProject::Manager Test_ROBDD;
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    EXPECT_FALSE(Test_ROBDD.isConstant(a));
    EXPECT_TRUE(Test_ROBDD.isConstant(Test_ROBDD.True()));
    EXPECT_TRUE(Test_ROBDD.isConstant(Test_ROBDD.False()));
}

/*Test Function "bool Manager::isVariable(BDD_ID x){};"*/
TEST(ManagerFuncsTest, Test_isVarFunc) {
    ClassProject::Manager Test_ROBDD;
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    EXPECT_TRUE(Test_ROBDD.isVariable(a));
    EXPECT_FALSE(Test_ROBDD.isVariable(Test_ROBDD.True()));
    EXPECT_FALSE(Test_ROBDD.isVariable(Test_ROBDD.False()));
}

/*Test Function "BDD_ID Manager::topVar(BDD_ID f){};"*/
TEST(ManagerFuncsTest, Test_topVarFunc) {
    ClassProject::Manager Test_ROBDD;
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    EXPECT_EQ(a, Test_ROBDD.topVar(a));
    EXPECT_EQ(0, Test_ROBDD.topVar(Test_ROBDD.False()));
    EXPECT_EQ(1, Test_ROBDD.topVar(Test_ROBDD.True()));
}

/*Test Function "size_t Manager::uniqueTableSize(){};"*/
TEST(ManagerFuncsTest, Test_uniqueTableSize) {
    ClassProject::Manager Test_ROBDD;
    EXPECT_EQ(2, Test_ROBDD.uniqueTableSize());
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject:: BDD_ID b = Test_ROBDD.createVar("b");
    EXPECT_EQ(4, Test_ROBDD.uniqueTableSize());
    Test_ROBDD.and2(a, b);
    EXPECT_EQ(5, Test_ROBDD.uniqueTableSize());
}

/*Test Function "BDD_ID Manager::coFactorTrue(BDD_ID f){};"*/
TEST(ManagerFuncsTest, Test_coFactorTrue1) {
    ClassProject::Manager Test_ROBDD;
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject:: BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject:: BDD_ID a_and_b = Test_ROBDD.and2(a, b);
    EXPECT_EQ(1, Test_ROBDD.coFactorTrue(a));
    EXPECT_EQ(b, Test_ROBDD.coFactorTrue(a_and_b));
}

/*Test Function "BDD_ID Manager::coFactorFalse(BDD_ID f){};"*/
TEST(ManagerFuncsTest, Test_coFactorFalse1) {
    ClassProject::Manager Test_ROBDD;
    ClassProject:: BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject:: BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject:: BDD_ID a_or_b = Test_ROBDD.or2(a, b);
    EXPECT_EQ(0, Test_ROBDD.coFactorFalse(a));
    EXPECT_EQ(b, Test_ROBDD.coFactorFalse(a_or_b));
}

TEST(ManagerFuncsTest, Test_find_or_add_unique_table) {
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    //find ID of a and b
    EXPECT_EQ(Test_ROBDD.find_or_add_unique_table(a, 1, 0), a);
    EXPECT_EQ(Test_ROBDD.find_or_add_unique_table(b, 1, 0), b);
    //add new entry
    EXPECT_EQ(Test_ROBDD.find_or_add_unique_table(a, b, 0), 4);
}

/*Test Function "BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){}"*/
TEST(ManagerFuncsTest, Test_ite) {
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    /*Terminal Cases test*/
    EXPECT_EQ(a, Test_ROBDD.ite(1,a,b));
    EXPECT_EQ(a, Test_ROBDD.ite(a,1,0));
    EXPECT_EQ(b, Test_ROBDD.ite(0,a,b));
    EXPECT_EQ(b, Test_ROBDD.ite(a,b,b));

    ClassProject::BDD_ID a_and_b = Test_ROBDD.and2(a, b);
    EXPECT_EQ(a_and_b, Test_ROBDD.ite(a,b,0));
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
    EXPECT_EQ(found_vars.size(), 2);
    EXPECT_EQ(found_vars.find(0), found_vars.end());
    EXPECT_EQ(found_vars.find(1), found_vars.end());
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


TEST(ManagerFuncsTest, Test_xor2) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aXORb = Test_ROBDD.xor2(a,b);

    EXPECT_EQ(Test_ROBDD.topVar(aXORb), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(aXORb), Test_ROBDD.neg(b));
    EXPECT_EQ(Test_ROBDD.coFactorFalse(aXORb), b);
    EXPECT_EQ(Test_ROBDD.xor2(0,0), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.xor2(1,0), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.xor2(0,1), Test_ROBDD.True());
}

TEST(ManagerFuncsTest, Test_nand2) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aNANDb = Test_ROBDD.nand2(a,b);

    EXPECT_EQ(Test_ROBDD.topVar(aNANDb), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(aNANDb), Test_ROBDD.neg(b));
    EXPECT_EQ(Test_ROBDD.coFactorFalse(aNANDb), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.nand2(1,1), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.nand2(1,0), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.nand2(0,1), Test_ROBDD.True());
}


TEST(ManagerFuncsTest, Test_nor2) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aNORb = Test_ROBDD.nor2(a,b);

    EXPECT_EQ(Test_ROBDD.topVar(aNORb), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(aNORb), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.coFactorFalse(aNORb), Test_ROBDD.neg(b));
    EXPECT_EQ(Test_ROBDD.nor2(0,0), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.nor2(1,0), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.nor2(0,1), Test_ROBDD.False());
}

TEST(ManagerFuncsTest, Test_xnor2) {

    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID aXNORb = Test_ROBDD.xnor2(a,b);

    EXPECT_EQ(Test_ROBDD.topVar(aXNORb), a);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(aXNORb), b);
    EXPECT_EQ(Test_ROBDD.coFactorFalse(aXNORb), Test_ROBDD.neg(b));
    EXPECT_EQ(Test_ROBDD.xnor2(0,0), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.xnor2(1,0), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.xnor2(0,1), Test_ROBDD.False());
}

TEST(ManagerFuncsTest, Test_example) {
    // f = (a + b) * c * d function from Document part 1
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c = Test_ROBDD.createVar("c");
    ClassProject::BDD_ID d = Test_ROBDD.createVar("d");
    ClassProject::BDD_ID a_or_b = Test_ROBDD.or2(a, b);
    ClassProject::BDD_ID c_and_d = Test_ROBDD.and2(c, d);
    ClassProject::BDD_ID f = Test_ROBDD.and2(a_or_b, c_and_d);
    //check size of unique table
    EXPECT_EQ(Test_ROBDD.uniqueTableSize(), 10);
    //check top variables
    EXPECT_EQ(Test_ROBDD.topVar(a_or_b), a);
    EXPECT_EQ(Test_ROBDD.topVar(c_and_d), c);
    EXPECT_EQ(Test_ROBDD.topVar(8), 3);
    EXPECT_EQ(Test_ROBDD.topVar(f), a);
    //check pos cofactors
    EXPECT_EQ(Test_ROBDD.coFactorTrue(a_or_b), Test_ROBDD.True());
    EXPECT_EQ(Test_ROBDD.coFactorTrue(c_and_d), d);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(8), c_and_d);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(f), c_and_d);
    //check neg cofactors
    EXPECT_EQ(Test_ROBDD.coFactorFalse(a_or_b), b);
    EXPECT_EQ(Test_ROBDD.coFactorFalse(c_and_d), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.coFactorFalse(8), Test_ROBDD.False());
    EXPECT_EQ(Test_ROBDD.coFactorFalse(f), 8);
}

TEST(ManagerFuncsTest, Test_example2) {
    // f = (b * c)((b * c) + a) this function tests whether a node with equal positive and negative cofactors is reduced
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID c = Test_ROBDD.createVar("c");
    ClassProject::BDD_ID b_and_c = Test_ROBDD.and2(b, c);
    ClassProject::BDD_ID a_b_c = Test_ROBDD.or2(a, b_and_c);
    ClassProject::BDD_ID f = Test_ROBDD.and2(a_b_c, b_and_c);
    EXPECT_EQ(f, b_and_c);
}

TEST(ManagerFuncsTest, Test_coFactorTrue2) {
    //test recursion in coFactorTrue not covered by ite
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID a_and_b = Test_ROBDD.and2(a, b);
    EXPECT_EQ(Test_ROBDD.coFactorTrue(a_and_b, b), a);
}

TEST(ManagerFuncsTest, Test_coFactorFalse2) {
    //test recursion in coFactorFalse not covered by ite
    ClassProject::Manager Test_ROBDD;
    ClassProject::BDD_ID a = Test_ROBDD.createVar("a");
    ClassProject::BDD_ID b = Test_ROBDD.createVar("b");
    ClassProject::BDD_ID a_and_b = Test_ROBDD.and2(a, b);
    EXPECT_EQ(Test_ROBDD.coFactorFalse(a_and_b, b), Test_ROBDD.False());
}


