#ifndef LFUNIVERSAL_H
#define LFUNIVERSAL_H
#include<map>
#include <vector>
#include "../Node.h"

class LFUniversal {
private:
    std::vector<Node*> head;
    int n;
    Node* tail;

public:
    LFUniversal(int n);
    Response apply(Invoc invoc,int id);
};


#endif // LFUNIVERSAL_H
