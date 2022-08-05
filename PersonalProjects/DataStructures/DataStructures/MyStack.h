#ifndef _MYSTACK_
#define _MYSTACK_

class MyStack {
public:
	MyStack();
	~MyStack();
	bool isEmpty();
	int peek();
	void push(int value);
	int pop();

private:
	struct Node {
		Node(int value);
		int value;
		Node* next;
	};
	Node* top;
};

MyStack::Node::Node(int value) {
	this->value = value;
	next = NULL;
}

MyStack::MyStack(){
	top = NULL;
}

MyStack::~MyStack() {
	while (!isEmpty()) {
		pop();
	}
}

bool MyStack::isEmpty() {
	return top == NULL;
}

void MyStack::push(int value) {
	Node* node = new Node(value);
	node->next = top;
	top = node;
}

int MyStack::peek() {
	if (top == NULL) throw std::exception("Cannot peek. The stack is empty.");
	return top->value;
}

int MyStack::pop() {
	if (top == NULL) throw std::exception("Cannot pop. The stack is empty.");
	int result = top->value;
	Node* toDelete = top;
	top = top->next;
	delete toDelete; //clean up memory

	return result;
}

#endif