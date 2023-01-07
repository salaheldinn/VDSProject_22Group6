#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"

namespace ClassProject {

    class Reachability : public ReachabilityInterface {
    private:
        std::vector<BDD_ID> state_variables;

        std::vector<BDD_ID> next_state_variables;

        std::vector<BDD_ID> transition_functions;

        std::vector<bool> init_state; //initial state
    public:
        BDD_ID existential_quantification(BDD_ID f, BDD_ID x);

        BDD_ID img(BDD_ID f); //img(s0, s1)

        BDD_ID img_nxt(BDD_ID f); //img(s0', s1')

        BDD_ID translation_relation(); //Tau

        BDD_ID bool_to_BDD_ID(const std::vector<bool> &stateVector); //adds state to ROBDD

        explicit Reachability(unsigned int stateSize);

        const std::vector<BDD_ID> &getStates() const override;

        bool isReachable(const std::vector<bool> &stateVector) override;

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) override;

        void setInitState(const std::vector<bool> &stateVector) override;
    };

}
#endif
