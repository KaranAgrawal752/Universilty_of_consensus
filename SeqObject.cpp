#include "SeqObject.h"

Response SeqObject::apply(Invoc invoc) {
    Response rp;

    if (invoc.getFunctionName() == "enqueue") {
        std::vector<int> args = invoc.getArguments();
        for (int arg : args) {
            que.push(arg);
        }
    } else if (invoc.getFunctionName() == "dequeue") {
        if (!que.empty()) {
            rp.addArgument(que.front());
            que.pop();
        }
    }
    else if (invoc.getFunctionName() == "push") {
        std::vector<int> args = invoc.getArguments();
        for (int arg : args) {
            st.push(arg);
        }
    } else if (invoc.getFunctionName() == "pop") {
        if (!st.empty()) {
            rp.addArgument(st.top());
            st.pop();
        }
    }

    return rp;
}
