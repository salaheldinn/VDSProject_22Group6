#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

struct ReachabilityTest : testing::Test {

    std::unique_ptr<ClassProject::ReachabilityInterface> fsm2 = std::make_unique<ClassProject::Reachability>(2);

    std::vector<BDD_ID> stateVars2 = fsm2->getStates();
    std::vector<BDD_ID> transitionFunctions;

};

TEST(ReachabilityTest, HowTo_Example) {
    ClassProject::Reachability Test_Reachability(2);
    std::vector<BDD_ID> stateVars2 = Test_Reachability.getStates();
    std::vector<BDD_ID> transitionFunctions;
    BDD_ID s0 = stateVars2.at(0);
    BDD_ID s1 = stateVars2.at(1);
    transitionFunctions.push_back(Test_Reachability.neg(s0)); // s0' = not(s0)
    transitionFunctions.push_back(Test_Reachability.neg(s1)); // s1' = not(s1)
    Test_Reachability.setTransitionFunctions(transitionFunctions);

    Test_Reachability.setInitState({false,false});

    EXPECT_TRUE(Test_Reachability.isReachable({false, false}));
    EXPECT_FALSE(Test_Reachability.isReachable({false, true}));
    EXPECT_FALSE(Test_Reachability.isReachable({true, false}));
    EXPECT_TRUE(Test_Reachability.isReachable({true, true}));
}

/*TEST_F(ReachabilityTest, HowTo_Example) { *//* NOLINT *//*

    BDD_ID s0 = stateVars2.at(0);
    BDD_ID s1 = stateVars2.at(1);

    transitionFunctions.push_back(fsm2->neg(s0)); // s0' = not(s0)
    transitionFunctions.push_back(fsm2->neg(s1)); // s1' = not(s1)
    fsm2->setTransitionFunctions(transitionFunctions);

    fsm2->setInitState({false,false});

    ASSERT_TRUE(fsm2->isReachable({false, false}));
    ASSERT_FALSE(fsm2->isReachable({false, true}));
    ASSERT_FALSE(fsm2->isReachable({true, false}));
    ASSERT_TRUE(fsm2->isReachable({true, true}));
}*/

#endif
