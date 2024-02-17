#ifndef CASCONSENSUS_H
#define CASCONSENSUS_H

#include "ConsensusProtocol.h"

template<typename T>
class CASConsensus : public ConsensusProtocol<T> {
private:
    int FIRST=-1;
    int r;

public:
    CASConsensus<T>() : ConsensusProtocol<T>(0) { // Default constructor
        r = FIRST;
    }
    CASConsensus<T>(int _n) : ConsensusProtocol<T>(_n) { 
        // this->n=_n;
        // this->proposed(this->n);
        r=FIRST;
    }

    void propose(T value,int id) override;
    T decide(T value,int id) override;
    bool compare_exchange(int* addr, int expected, int desired);
};


#endif // CASCONSENSUS_H
