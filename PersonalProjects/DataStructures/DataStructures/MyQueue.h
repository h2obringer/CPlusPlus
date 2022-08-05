#ifndef _MYQUEUE_
#define _MYQUEUE_

class MyQueue {
public:
	MyQueue();
	~MyQueue();
	bool isEmpty();
	int peek();
	void enqueue(int value);
	int dequeue();
private:
	struct Node {
		Node(int value);
		int value;
		Node* next;
	};
	Node* head;
	Node* tail;
};

MyQueue::Node::Node(int value) {
	this->value = value;
	next = NULL;
}

MyQueue::MyQueue(){
	head = tail = NULL;
}

MyQueue::~MyQueue() {
	while (!isEmpty()) {
		dequeue();
	}
}

bool MyQueue::isEmpty() {
	return head == NULL;
}

int MyQueue::peek() {
	if (head == NULL) throw std::exception("Cannot peek. The queue is empty.");
	return head->value; //will throw an exception if head == NULL
}

void MyQueue::enqueue(int value) {
	Node* node = new Node(value);

	if (tail != NULL) tail->next = node;
	tail = node;
	if (head == NULL) head = tail;
}

int MyQueue::dequeue() {
	if (head == NULL) throw std::exception("Cannot dequeue. The queue is empty.");
	int result = head->value; //will throw an exception if head == NULL
	Node* toDelete = head;
	
	head = head->next;
	if (head == NULL) tail = NULL;

	delete toDelete; //clean up the memory of the head node.

	return result;
}

#endif