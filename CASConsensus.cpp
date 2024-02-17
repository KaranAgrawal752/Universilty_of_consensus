#include "CASConsensus.h"
#include "Node.h"
template class CASConsensus<Node*>;

using namespace std;
template<typename T>
void CASConsensus<T>::propose(T value,int id) {
    // Implement the proposal logic here
    this->proposed[id] = value;
}

template<typename T>
T CASConsensus<T>::decide(T value,int id) {
    propose(value,id);
    if (compare_exchange(&r,FIRST, id)) // I won
        return this->proposed[id];
    else // I lost
        return this->proposed[r];
}

template<typename T>
bool CASConsensus<T>:: compare_exchange(int* addr, int expected, int desired) {
    bool result;
    asm volatile(
        "lock cmpxchg %3, %1\n\t"
        "sete %0"
        : "=q" (result), "+m" (*addr)
        : "a" (expected), "r" (desired)
        : "memory"
    );
    return result;
}