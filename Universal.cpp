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

Response Universal::apply(Invoc invoc) {
    // Get the thread ID
    // cout<<"a";
    pthread_t self = pthread_self();
    
    // Loop through the array of threads to find the index of the current thread
    int i=(int)self%this->n;
    // for (i = 0; i < n; i++) {
    //     if (pthread_equal(threads[i], self)) {
    //         break;
    //     }
    // }
    // cout<<i<<"Hello";
    announce[i] =new Node(invoc, this->n);
    // announce[i].decideNext.n=this->n;
    head[i] = Node::max(head);
    while (announce[i]->seq == 0) {
        Node* before = head[i];
        Node* help = announce[(before->seq + 1) %this->n];
        Node* prefer;
        if (help->seq == 0)
            prefer = help;
        else
            prefer = announce[i];
        Node* after = before->decideNext.decide(prefer);
        before->next = after;
        after->seq = before->seq + 1;
        head[i] = after;
    }
    SeqObject MyObject=SeqObject();
    Node* current = tail->next;
    while (current != announce[i]) {
        MyObject.apply(current->invoc);
        current = current->next;
    }
    head[i] = announce[i];
    MyObject.apply(current->invoc);
    Response rsp;
    rsp.addArgument((int)self%this->n);
    rsp.addArgument(head[i]->seq);
    return rsp;
    // vector<int> tmp={self%this->n,head[i]->seq};
    // return tmp;

}

