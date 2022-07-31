/* https://leetcode.com/explore/learn/card/hash-table/182/practical-applications/1139/

PROBLEM: Design a HashSet without using any built-in hash table libraries.

Implement MyHashSet class:

void add(key) Inserts the value key into the HashSet.
bool contains(key) Returns whether the value key exists in the HashSet or not.
void remove(key) Removes the value key in the HashSet. If key does not exist in the HashSet, do nothing.

EXAMPLE 1:
Input
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
Output
[null, null, null, true, false, null, true, null, false]

Explanation
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // return True
myHashSet.contains(3); // return False, (not found)
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // return True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // return False, (already removed)

CONSTRAINTS:
- 0 <= key <= 10^6
- At most 10^4 calls will be made to add, remove, and contains
*/

#include <iostream>
#include <list>

const int SIZE = 1000;

class MyHashSet {
public:
    MyHashSet();
    ~MyHashSet();
    void add(int key); //inserts the value "key" into the HashSet
    bool contains(int key); //returns whether the value "key" exists in the HashSet or not.
    void remove(int key); //removes the value "key" in the HashSet. If "key" does not exist in the HashSet, do nothing.
private:
    int hash(int key);
    std::list<int> bucket[SIZE];
};

MyHashSet::MyHashSet() {}

MyHashSet::~MyHashSet() {}

void MyHashSet::add(int key) {
    if (!contains(key)) {
        bucket[hash(key)].push_back(key);
    }
}

bool MyHashSet::contains(int key) {
    int index = hash(key);
    if (bucket[index].size() > 0) {
        for (std::list<int>::iterator it = bucket[index].begin(); it != bucket[index].end(); it++) {
            if (*it == key) return true;
        }
    }

    return false;
}

void MyHashSet::remove(int key) {
    if (contains(key)) {
        bucket[hash(key)].remove(key);
    }
}

int MyHashSet::hash(int key) {
    return key % SIZE;
}

int main()
{
    //we are mainly using the LeetCode window and relying on it's tests here...
    MyHashSet* obj = new MyHashSet();
    obj->add(3);
    obj->contains(3);
}