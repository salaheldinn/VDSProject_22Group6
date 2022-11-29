#include "Manager.h"
#include <vector>
#include <unordered_map>

using namespace ClassProject;

Manager::Manager(){
    //Initialize False and True in the unique table
    unique_table_entry temp_entry = {.id=0, .high=0, .low=0, .topvar=0, .label="False"};
    unique_table.push_back(temp_entry);
    temp_entry = {.id=1, .high=1, .low=1, .topvar=1, .label="True"};
    unique_table.push_back(temp_entry);
}

BDD_ID Manager::createVar(const std::string &label){
    unique_table_entry temp_entry = {.id=unique_table.size(), .high=1, .low=0, .topvar=unique_table.size(), .label=label};
    unique_table.push_back(temp_entry);
    return temp_entry.id;
}

const BDD_ID &Manager::True(){
    return unique_table[1].id;
}

const BDD_ID &Manager::False(){
    return unique_table[0].id;
}

bool Manager::isConstant(BDD_ID f){
    return (f==0||f==1) ? true : false;
}

bool Manager::isVariable(BDD_ID x){};

BDD_ID Manager::topVar(BDD_ID f){};

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){};

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){};

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){};

BDD_ID Manager::coFactorTrue(BDD_ID f){};

BDD_ID Manager::coFactorFalse(BDD_ID f){};

BDD_ID Manager::neg(BDD_ID a){};

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){};

std::string Manager::getTopVarName(const BDD_ID &root){};

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){};

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){};

size_t Manager::uniqueTableSize(){};