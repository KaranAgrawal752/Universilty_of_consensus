#include "Universal.h"
#include <iostream>
#include <vector>
#include <pthread.h> // Include pthread header
#include <unistd.h>  // for sleep

using namespace std;


struct ThreadArgs {
    Universal* univ_obj;
    Invoc* invoc_obj;
    int id;
};

void* threadFunction(void * args_ptr) {
    ThreadArgs* args = static_cast<ThreadArgs*>(args_ptr);

    // Accessing univ_obj and invoc_obj from args
    Universal* univ_obj = args->univ_obj;
    Invoc* invoc_obj = args->invoc_obj;
    int id=args->id;
    Response resp=univ_obj->apply(*invoc_obj);
    vector<int> res=resp.getArguments();
    cout<<"Thread id: "<<res[0]<<"  Seq in Consensus: "<<res[1]<<endl;
    return nullptr;
}

int main() {
    cout<<"main started\n";
    int N= 10;
    Universal* univ_obj=new Universal(N);
    pthread_t myThread;
    vector<Invoc*> invoc_obj(N);

    // cout<<"Inoc is creation started";
    // Create Invoc objects and populate the vector
    for (int i = 0; i < N; i++) {
        vector<int> v = {i};
        string function_name = "enqueue";
        invoc_obj[i] = new Invoc(function_name, v); // Creating Invoc objects directly
    }
    cout<<"Invoc is created\n";
    // Create threads
    for (int i = 0; i < N; i++) {
        ThreadArgs* args = new ThreadArgs{univ_obj, invoc_obj[i],i};
        if (pthread_create(&myThread, nullptr, threadFunction, args)) {
            cerr << "Error creating thread." << endl;
            return 1;
        }
        // cout<<i<<" ";
    }

    // // Wait for all threads to finish execution
    // for (int i = 0; i < N; i++) {
    //     if (pthread_join(myThread, nullptr)) {
    //         cerr << "Error joining thread." << endl;
    //         return 1;
    //     }
    // }

    return 0;
}
