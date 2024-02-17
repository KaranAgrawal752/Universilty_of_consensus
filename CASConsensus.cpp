#include "CASConsensus.h"
#include "Node.h"
template class CASConsensus<Node*>;

using namespace std;
template<typename T>
void CASConsensus<T>::propose(T value) {
    // Implement the proposal logic here
    this->proposed[(int)pthread_self()%this->n] = value;
}

template<typename T>
T CASConsensus<T>::decide(T value) {
    propose(value);
    int i =(int)pthread_self()%this->n;
    if (compare_exchange(&r,FIRST, i)) // I won
        return this->proposed[i];
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