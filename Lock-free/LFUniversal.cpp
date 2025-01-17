#include "LFUniversal.h"
#include <iostream>
#include <pthread.h> // Include for pthreads
#include <mutex>


LFUniversal::LFUniversal(int n) {
    cout<<"LFUniversal Constructor called\n";
    this->n=n;
    tail = new Node(this->n);
    // tail.decideNext.n=this->n;
    tail->seq = 1;
    for (int j = 0; j <n; j++) {
        head.push_back(tail);
    }
    // cout<<head.size()<<"\n"<<announce.size()<<"\n";
}

Response LFUniversal::apply(Invoc invoc,int id) {
    Response rsp;
    Node* prefer;
    std::lock_guard<std::mutex> lock(mutex);
    [&](){
    prefer= new Node(invoc, this->n);
    Node* tmp = Node::max(head);
    rsp.addArgument(tmp->seq);
    }();
    while (prefer->seq == 0) {
        Node* before = Node::max(head);
        Node* after = before->decideNext.decide(prefer,id);
        before->next = after;
        after->seq = before->seq + 1;
        head[id] = after;
    }
    SeqObject MyObject=SeqObject();
    Node* current = tail->next;
    while (current != prefer) {
        MyObject.apply(current->invoc);
        current = current->next;
    }
    MyObject.apply(current->invoc);
    rsp.addArgument(id);
    rsp.addArgument(head[id]->seq);
    return rsp;
}

