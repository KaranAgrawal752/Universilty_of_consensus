#ifndef SEQOBJECT_H
#define SEQOBJECT_H

#include <string>
#include <vector>
#include <queue>
#include<stack>

class Invoc {
public:
    Invoc( std::string& functionName,  std::vector<int>& arguments) 
        : function_name(functionName), arguments(arguments) {}
    Invoc() {}
    std::string getFunctionName()  { return function_name; }
    std::vector<int> getArguments()  { return arguments; }

private:
    std::string function_name;
    std::vector<int> arguments;
};

class Response {
public:
    void addArgument(int arg) { arguments.push_back(arg); }
    std::vector<int> getArguments()  { return arguments; }

private:
    std::vector<int> arguments;
};

class SeqObject {
public:
    Response apply( Invoc invoc);

private:
    std::queue<int> que;
    std::stack<int> st;
};

#endif // SEQOBJECT_H
