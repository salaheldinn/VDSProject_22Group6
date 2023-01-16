#include "Reachability.h"

using namespace ClassProject;

BDD_ID Reachability::existential_quantification(BDD_ID f, BDD_ID x) {
    BDD_ID temp, temp2;
    temp = coFactorTrue(f, x);
    temp2 = coFactorFalse(f, x);
    return or2(temp, temp2);
}

BDD_ID Reachability::translation_relation() {
    BDD_ID temp, temp2;
    temp = xnor2(next_state_variables[0], transition_functions[0]);
    for(int i=1; i<state_variables.size(); i++){
        temp2 = xnor2(next_state_variables[i], transition_functions[i]);
        temp = and2(temp, temp2);
    }
    return temp;
}

BDD_ID Reachability::img(BDD_ID f) {
    BDD_ID temp, temp2;
    temp = f;
    for(int i=0; i<state_variables.size(); i++){
        temp2 = xnor2(state_variables[i], next_state_variables[i]);
        temp = and2(temp, temp2);
    }
    for(int i=0; i<state_variables.size(); i++)
        temp = existential_quantification(temp, next_state_variables[state_variables.size()-1-i]);
    return temp;
}

BDD_ID Reachability::img_nxt(BDD_ID f) {
    BDD_ID temp = f;
    for(int i=0; i<state_variables.size(); i++)
        temp = existential_quantification(temp, state_variables[state_variables.size()-1-i]);
    return temp;
}

BDD_ID Reachability::bool_to_BDD_ID(const std::vector<bool> &stateVector) {
    BDD_ID temp, temp2;
    temp = (stateVector[0]) ? state_variables[0] : neg(state_variables[0]);
    for(int i=1; i<stateVector.size(); i++){
        temp2 = (stateVector[i]) ? state_variables[i] : neg(state_variables[i]);
        temp = and2(temp, temp2);
    }
    return temp;
}

Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize){
    //stateSize can't be zero
    if(stateSize==0)
        throw std::runtime_error("number of state variables is zero");
    //create state variables and initialize transition functions with ID
    BDD_ID temp, temp2;
    for(int i=0; i<stateSize; i++){
        temp = createVar("");
        state_variables.push_back(temp);
        transition_functions.push_back(temp);
    }
    //create next state variables
    for(int i=0; i<stateSize; i++){
        temp = createVar("");
        next_state_variables.push_back(temp);
    }
    //initial state
    for(int i=0; i<stateSize; i++)
        init_state.push_back(false);
}

const std::vector<BDD_ID> &Reachability::getStates() const {
    return state_variables;
}

bool Reachability::isReachable(const std::vector<bool> &stateVector){
    if (stateVector.size() != state_variables.size())
        throw std::runtime_error ("number of state values to be reached does not match number of state variables");
    BDD_ID tau = translation_relation();
    BDD_ID C_R_it = bool_to_BDD_ID(init_state); //C_S
    BDD_ID C_R;
    do{
        C_R = C_R_it;
        BDD_ID C_R_and_tau = and2(C_R, tau);
        BDD_ID img_1 = img_nxt(C_R_and_tau);
        BDD_ID img_2 = img(img_1);
        C_R_it = or2(C_R, img_2);
    } while(C_R != C_R_it);
    BDD_ID temp = bool_to_BDD_ID(stateVector);
    return (temp == and2(temp, C_R));
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){
    //check number of transition functions
    if(transitionFunctions.size() != state_variables.size())
        throw std::runtime_error("number of transition functions does not match number of state variables");
    //check the IDs of transition functions
    for(int i=0; i<transitionFunctions.size(); i++)
        if (transitionFunctions[i]>uniqueTableSize()) throw std::runtime_error("ID of transition function does not exist");
    //assign transition functions
    for (int i=0; i<transitionFunctions.size(); i++)
        transition_functions[i] = transitionFunctions[i];
}

void Reachability::setInitState(const std::vector<bool> &stateVector){
    if (stateVector.size() != state_variables.size())
        throw std::runtime_error ("number of initial state variables does not match number of state variables");
    for(int i=0; i<stateVector.size(); i++)
        init_state[i] = stateVector[i];
}