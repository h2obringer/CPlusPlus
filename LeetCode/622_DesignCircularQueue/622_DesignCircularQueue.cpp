#include <iostream>
#include <vector>

/* https://leetcode.com/explore/learn/card/queue-stack/228/first-in-first-out-data-structure/1337/
https://leetcode.com/problems/design-circular-queue/

PROBLEM: Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a normal queue, once the queue becomes full, we cannot insert the next element even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.

Implementation the MyCircularQueue class:

MyCircularQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return -1.
int Rear() Gets the last item from the queue. If the queue is empty, return -1.
boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
boolean isEmpty() Checks whether the circular queue is empty or not.
boolean isFull() Checks whether the circular queue is full or not.
You must solve the problem without using the built-in queue data structure in your programming language. 

Example 1:

Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]

Explanation
MyCircularQueue myCircularQueue = new MyCircularQueue(3);
myCircularQueue.enQueue(1); // return True
myCircularQueue.enQueue(2); // return True
myCircularQueue.enQueue(3); // return True
myCircularQueue.enQueue(4); // return False
myCircularQueue.Rear();     // return 3
myCircularQueue.isFull();   // return True
myCircularQueue.deQueue();  // return True
myCircularQueue.enQueue(4); // return True
myCircularQueue.Rear();     // return 4

CONSTRAINTS:
    1 <= k <= 1000
    0 <= value <= 1000
    At most 3000 calls will be made to enQueue, deQueue, Front, Rear, isEmpty, and isFull.
*/

class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        head = -1;
        tail = -1;
        cq.resize(k);
        max_index = k - 1;
    }

    bool enQueue(int value) {
        if (isFull()) return false;

        tail++;
        if (tail > max_index) tail = 0;
        if (head == -1) head = tail;
        cq[tail] = value;

        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;

        if (head == tail) 
        {
            head = -1;
            tail = -1;
        }
        else
        {
            head++;
            if (head > max_index) head = 0;
        }

        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return cq[head];
    }

    int Rear() {
        if (isEmpty()) return -1;
        return cq[tail];
    }

    bool isEmpty() {
        if (head < 0 || tail < 0) return true;
        return false;
    }

    bool isFull() {
        int new_tail = tail + 1;
        if (new_tail > max_index) new_tail = 0;
        if (head != -1 && head == new_tail) return true;
        return false;
    }
private:
    std::vector<int> cq; //circular queue
    int head;
    int tail;
    int max_index;
};

int main()
{
    MyCircularQueue* obj = new MyCircularQueue(6);
    bool param_1 = obj->enQueue(6);
    int param_2 = obj->Rear();
    int param_3 = obj->Rear();
    bool param_4 = obj->deQueue();
    bool param_5 = obj->enQueue(5);
    int param_6 = obj->Rear();
    bool param_7 = obj->deQueue();
    bool param_8 = obj->Front();
    bool param_9 = obj->deQueue();
    bool param_10 = obj->deQueue();
    bool param_11 = obj->deQueue();
    std::cout << "Hello World!\n";
}