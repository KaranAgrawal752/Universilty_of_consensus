#include "Universal.h"
#include <iostream>
#include <vector>
#include <pthread.h> // Include pthread header
#include <unistd.h>  // for sleep
#include <mutex>

using namespace std;

std::mutex mtx;

void printAtomically(int start,int threadId, int sequence) {
    // Lock the mutex to ensure atomicity
    std::lock_guard<std::mutex> lock(mtx);
    
    // Print the line atomically
    std::cout << "Thread id: " << threadId << "  Seq in Consensus: " << sequence <<" Invoking time "<<start<< std::endl;
    // Mutex is automatically released when lock_guard goes out of scope
}
struct ThreadArgs {
    Universal* univ_obj;
    int id;
};

void* threadFunction(void * args_ptr) {
    ThreadArgs* args = static_cast<ThreadArgs*>(args_ptr);

    // Accessing univ_obj and invoc_obj from args
    Universal* univ_obj = args->univ_obj;
    int id=args->id;
    for(int i=0;i<3;i++)
    {
        vector<int> v = {id};
        string function_name = "enqueue";
        Invoc* invoc_obj= new Invoc(function_name, v);
        Response resp=univ_obj->apply(*invoc_obj,id);
        vector<int> res=resp.getArguments();
        printAtomically(res[0], res[1],res[2]);
        // sleep(0.01);
    }
    return nullptr;
}

int main() {
    cout<<"main started\n";
    int N= 10;
    Universal* univ_obj=new Universal(N);
    vector<pthread_t> myThread(N);
    // for(int i=0;i<3;i++)
    // {
    // Create threads
    for (int i = 0; i < N; i++) {
        ThreadArgs* args = new ThreadArgs{univ_obj,i};
        if (pthread_create(&myThread[i], nullptr, threadFunction, args)) {
            cerr << "Error creating thread." << endl;
            return 1;
        }
        // cout<<i<<" ";
    }

    // // Wait for all threads to finish execution
    for (int i = 0; i < N; i++) {
        if (pthread_join(myThread[i], NULL)) {
            cerr << "Error joining thread." << endl;
            return 1;
        }
    }
    // }
    return 0;
}
