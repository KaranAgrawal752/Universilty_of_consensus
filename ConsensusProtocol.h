#ifndef CONSENSUSPROTOCOL_H
#define CONSENSUSPROTOCOL_H
#include<iostream>
#include<vector>
#include <pthread.h> // Include for pthreads
using namespace std;

template<typename T>
class Consensus {
public:
    virtual T decide(T value) =0; // Pure virtual function
};

template<typename T>
class ConsensusProtocol : public Consensus<T> {
public:
    int n;
protected:
    vector<T> proposed;

public:
    ConsensusProtocol<T>(int _n) {
        this->n=_n;
        this->proposed.resize(this->n);
    }
    virtual void propose(T value) {
        // Implement the proposal logic here
        pthread_t tid = pthread_self();
        // Convert the thread ID to an index in the proposed array
        size_t index = (size_t)tid % this->n;
        proposed[index] = value;
    }

    virtual T decide(T value)=0; // Pure virtual function
};
#endif // CONSENSUSPROTOCOL_H
