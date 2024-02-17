#include "Universal.h"
#include <iostream>
#include <pthread.h> // Include for pthreads


Universal::Universal(int n) {
    cout<<"Universal Constructor called\n";
    this->n=n;
    tail = new Node(this->n);
    // tail.decideNext.n=this->n;
    tail->seq = 1;
    for (int j = 0; j <n; j++) {
        head.push_back(tail);
        announce.push_back(tail);
    }
    // cout<<head.size()<<"\n"<<announce.size()<<"\n";
}

Response Universal::apply(Invoc invoc,int id) {
    // Get the thread ID
    // cout<<"a";
    
    // Loop through the array of threads to find the index of the current thread
    // for (i = 0; i < n; i++) {
    //     if (pthread_equal(threads[i], self)) {
    //         break;
    //     }
    // }
    // cout<<i<<"Hello";
    announce[id] =new Node(invoc, this->n);
    head[id] = Node::max(head);
    while (announce[id]->seq == 0) {
        Node* before = head[id];
        Node* help = announce[(before->seq + 1) %this->n];
        Node* prefer;
        if (help->seq == 0)
            prefer = help;
        else
            prefer = announce[id];
        Node* after = before->decideNext.decide(prefer,id);
        before->next = after;
        after->seq = before->seq + 1;
        head[id] = after;
    }
    SeqObject MyObject=SeqObject();
    Node* current = tail->next;
    while (current != announce[id]) {
        MyObject.apply(current->invoc);
        current = current->next;
    }
    head[id] = announce[id];
    MyObject.apply(current->invoc);
    Response rsp;
    rsp.addArgument(id);
    rsp.addArgument(head[id]->seq);
    return rsp;
    // vector<int> tmp={self%this->n,head[i]->seq};
    // return tmp;

}

