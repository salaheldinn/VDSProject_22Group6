// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <boost/functional/hash.hpp>


namespace ClassProject {

    struct unique_table_entry {
        BDD_ID id;
        BDD_ID high;
        BDD_ID low;
        BDD_ID topvar;
        std::string label;
    };

    struct Key
    {
        BDD_ID first;
        BDD_ID second;
        BDD_ID third;
        bool operator==(const Key &other) const
        { return (first==other.first && second==other.second && third==other.third);
        }
    };

    struct KeyHasher
    {
        std::size_t operator()(const Key& k) const
        {
            using boost::hash_value;
            using boost::hash_combine;
            std::size_t seed = 0;
            hash_combine(seed,hash_value(k.first));
            hash_combine(seed,hash_value(k.second));
            hash_combine(seed,hash_value(k.third));
            return seed;
        }
    };

    class Manager : public ManagerInterface {
    public:
        std::vector<unique_table_entry> unique_table;

        std::unordered_map<Key,BDD_ID,KeyHasher> hash_unique_table;

        std::unordered_map<Key,BDD_ID,KeyHasher> computed_table;

        Manager();

        BDD_ID createVar(const std::string &label) override;

        const BDD_ID &True() override;

        const BDD_ID &False() override;

        bool isConstant(BDD_ID f) override;

        bool isVariable(BDD_ID x) override;

        BDD_ID topVar(BDD_ID f) override;

        BDD_ID find_or_add_unique_table(BDD_ID tv, BDD_ID h, BDD_ID l);

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorTrue(BDD_ID f) override;

        BDD_ID coFactorFalse(BDD_ID f) override;

        BDD_ID neg(BDD_ID a) override;

        BDD_ID and2(BDD_ID a, BDD_ID b) override;

        BDD_ID or2(BDD_ID a, BDD_ID b) override;

        BDD_ID xor2(BDD_ID a, BDD_ID b) override;

        BDD_ID nand2(BDD_ID a, BDD_ID b) override;

        BDD_ID nor2(BDD_ID a, BDD_ID b) override;

        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

        std::string getTopVarName(const BDD_ID &root) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

        size_t uniqueTableSize() override;

    };
}

#endif