class MyQueue {
public:
    stack<int> ip , op;
    int peekEl = -1;
    MyQueue() {
        
    }
    
    void push(int x) {
        if (ip.empty()) peekEl = x;
        ip.push(x);
    }
    
    int pop() {
        if (op.empty()) {
            while(!ip.empty()) {
                op.push(ip.top());
                ip.pop();
            }
        }
        
        int val = op.top();
        op.pop();

        return val;
    }
    
    int peek() {
        if (op.empty()) return peekEl;
        return op.top();
    }
    
    bool empty() {
        if (ip.empty() && op.empty()) return true;
        return false;
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */