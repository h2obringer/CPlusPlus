#include <iostream>
using namespace std;

/* https://leetcode.com/explore/learn/card/queue-stack/230/usage-stack/1360/
https://leetcode.com/problems/min-stack

PROBLEM: Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

    MinStack() initializes the stack object.
    void push(int val) pushes the element val onto the stack.
    void pop() removes the element on the top of the stack.
    int top() gets the top element of the stack.
    int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

CONSTRAINTS:

    -2^31 <= val <= 2^31 - 1
    Methods pop, top and getMin operations will always be called on non-empty stacks.
    At most 3 * 104 calls will be made to push, pop, top, and getMin.

*/

class MinStack {
public:
    MinStack();
    ~MinStack();
    void push(int val);
    void pop();
    int top();
    int getMin();
private:
    struct Node {
        Node(int value);
        int value;
        int currMinVal; //what is the minimum up to this node in the stack?
        Node* next;
    };
    Node* head;
};

MinStack::MinStack(){
    head = NULL;
}

MinStack::~MinStack() {
    while (head != NULL) {
        pop();
    }
}

void MinStack::push(int val) {
    Node* temp = new Node(val);
    temp->next = head;
    if (head != NULL && head->currMinVal < val) temp->currMinVal = head->currMinVal; //temp is already assigned currMinVal to val, if the previous element had a lower value, make the new head's min that value
    head = temp; //update the head
}

void MinStack::pop() {
    Node* temp = head;
    head = head->next;
    delete temp; //clean up memory
}

int MinStack::top() {
    return head->value;
}

int MinStack::getMin() {
    return head->currMinVal;
}

MinStack::Node::Node(int value) {
    this->value = value;
    currMinVal = value;
    next = NULL;
}

int main()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << endl; // return -3
    minStack.pop();
    cout << minStack.top() << endl;    // return 0
    cout << minStack.getMin() << endl; // return -2
}