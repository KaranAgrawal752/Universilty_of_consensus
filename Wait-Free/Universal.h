#ifndef UNIVERSAL_H
#define UNIVERSAL_H
#include<map>
#include <vector>
#include "../Node.h"
#include<mutex>

class Universal {
private:
    std::vector<Node*> announce;
    std::vector<Node*> head;
    int n;
    Node* tail;

public:
    Universal(int n);
    Response apply(Invoc invoc,int id);
};


#endif // UNIVERSAL_H
