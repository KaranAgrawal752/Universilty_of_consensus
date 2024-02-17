#ifndef NODE_H
#define NODE_H
#include "CASConsensus.h" // Include header file for Consensus class
#include "SeqObject.h"
#include<string.h>
using namespace std;

class Node {
public:
    int n;
    Invoc invoc; // method name and args
    CASConsensus<Node*> decideNext; // decide next Node in list
    Node* next; // the next node
    int seq; // sequence number

    Node(Invoc invoc,int n); // Constructor declaration
    Node(int n); // Constructor declaration
    static Node* max(vector<Node*>& array); // Static member function declaration
};

#endif // NODE_H
