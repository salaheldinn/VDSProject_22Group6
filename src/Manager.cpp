#include "Manager.h"
#include <vector>
#include <unordered_map>

using namespace ClassProject;

Manager::Manager(){
    //Initialize False and True in the unique table and hash unique table
    unique_table_entry temp_entry = {.id=0, .high=0, .low=0, .topvar=0, .label="False"};
    unique_table.push_back(temp_entry);
    hash_unique_table.insert({{0, 0, 0}, 0});
    temp_entry = {.id=1, .high=1, .low=1, .topvar=1, .label="True"};
    unique_table.push_back(temp_entry);
    hash_unique_table.insert({{1, 1, 1}, 1});
}

BDD_ID Manager::createVar(const std::string &label){
    unique_table_entry temp_entry = {.id=unique_table.size(), .high=1, .low=0, .topvar=unique_table.size(), .label=label};
    unique_table.push_back(temp_entry);
    hash_unique_table.insert({{1, 0, unique_table.size()-1}, unique_table.size()-1});
    return temp_entry.id;
}

const BDD_ID &Manager::True(){
    return unique_table[1].id;
}

const BDD_ID &Manager::False(){
    return unique_table[0].id;
}

bool Manager::isConstant(BDD_ID f){
    return (f == 0 || f == 1);
}

bool Manager::isVariable(BDD_ID f){
    return (unique_table[f].high == 1 && unique_table[f].low == 0);
}

BDD_ID Manager::topVar(BDD_ID f){
    return unique_table[f].topvar;
}

BDD_ID Manager::find_or_add_unique_table(BDD_ID tv, BDD_ID h, BDD_ID l){
    auto indx = hash_unique_table.find({h, l, tv});
    //add entry
    if (indx==hash_unique_table.end()) {
        unique_table_entry temp_entry = {.id=uniqueTableSize(), .high=h, .low=l, .topvar=tv, .label=""};
        unique_table.push_back(temp_entry);
        hash_unique_table.insert({{h, l, tv}, unique_table[uniqueTableSize()-1].id});
        return unique_table[uniqueTableSize()-1].id;
    }
    //entry found
    else return indx->second;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    //check for terminal cases
    if (i==0)
        return e;
    if ((i==1) || (t==e))
        return t;
    //not a terminal case
    //top variable added first has higher priority
    BDD_ID topvar_x;
    if (isConstant(t) && isConstant(e))
        topvar_x = topVar(i);
    else if (isConstant(t))
        topvar_x = std::min(topVar(i), topVar(e));
    else if (isConstant(e))
        topvar_x = std::min(topVar(i), topVar(t));
    else
        topvar_x = std::min(std::min(topVar(i), topVar(t)), topVar(e));
    //calculate positive and negative cofactors
    BDD_ID i_pos_cofactor = coFactorTrue(i, topvar_x);
    BDD_ID i_neg_cofactor = coFactorFalse(i, topvar_x);
    BDD_ID t_pos_cofactor = coFactorTrue(t, topvar_x);
    BDD_ID t_neg_cofactor = coFactorFalse(t, topvar_x);
    BDD_ID e_pos_cofactor = coFactorTrue(e, topvar_x);
    BDD_ID e_neg_cofactor = coFactorFalse(e, topvar_x);
    //calculate HIGH and LOW
    BDD_ID r_high = ite(i_pos_cofactor, t_pos_cofactor, e_pos_cofactor);
    BDD_ID r_low = ite(i_neg_cofactor, t_neg_cofactor, e_neg_cofactor);
    //reduce if possible
    if (r_high==r_low)
        return r_high;
    //add to unique table if it does not exist already
    BDD_ID r = find_or_add_unique_table(topvar_x, r_high, r_low);
    return r;
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    //check for terminal case
    if (isConstant(f) || isConstant(x) || topVar(f)>x)
        return f;
    //not a terminal case
    if (topVar(f) == x)
        return coFactorTrue(f);
    //recursion
    BDD_ID t_temp = coFactorTrue(coFactorTrue(f), x);
    BDD_ID f_temp = coFactorTrue(coFactorFalse(f), x);
    return ite(topVar(f), t_temp, f_temp);
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    //check for terminal case
    if (isConstant(f) || isConstant(x) || topVar(f)>x)
        return f;
    //not a terminal case
    if (topVar(f) == x)
        return coFactorFalse(f);
    //recursion
    BDD_ID t_temp = coFactorFalse(coFactorTrue(f), x);
    BDD_ID f_temp = coFactorFalse(coFactorFalse(f), x);
    return ite(topVar(f), t_temp, f_temp);
}

BDD_ID Manager::coFactorTrue(BDD_ID f){
    return unique_table[f].high;
}

BDD_ID Manager::coFactorFalse(BDD_ID f){
    return unique_table[f].low;
}

BDD_ID Manager::neg(BDD_ID a){
    return ite(a, 0, 1);
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    return ite(a, b, 0);
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    return ite(a, 1, b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    return ite(a, neg(b), b);
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){};

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){};

std::string Manager::getTopVarName(const BDD_ID &root){
    BDD_ID topvar_of_root = topVar(root);
    return unique_table[topvar_of_root].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    //if node has already been added do nothing
    if (nodes_of_root.find(root) == nodes_of_root.end()){
        nodes_of_root.insert(root);
        //if node is not a constant find reachable nodes of high and low
        if (!isConstant(root)) {
            findNodes(coFactorTrue(root), nodes_of_root);
            findNodes(coFactorFalse(root), nodes_of_root);
        }
    }
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    //if top variable has already been added don't add again
    if (vars_of_root.find(topVar(root)) == vars_of_root.end())
        vars_of_root.insert(topVar(root));
    //if node is not a constant find top variables of reachable nodes of high and low
    if (!isConstant(root)) {
        findNodes(coFactorTrue(root), vars_of_root);
        findNodes(coFactorFalse(root), vars_of_root);
    }
}

size_t Manager::uniqueTableSize(){
    return unique_table.size();
}