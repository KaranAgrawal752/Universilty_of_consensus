#include "Node.h"

Node::Node(Invoc invoc,int n)
{
    this->invoc=Invoc(invoc);
    this->decideNext=CASConsensus<Node*>(n); 
    this->next=nullptr; 
    this->seq=0;
}

Node::Node(int n)
{
    this->decideNext=CASConsensus<Node*>(n); 
    this->next=nullptr; 
    this->seq=0;
}

Node* Node::max(vector<Node*> &array) {
    int length=array.size();
    Node* max = array[0];
    for (int i = 1; i < length; i++) {
        if (max->seq < array[i]->seq) {
            max = array[i];
        }
    }
    return max;
}