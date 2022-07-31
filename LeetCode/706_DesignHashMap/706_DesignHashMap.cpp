/* https://leetcode.com/explore/learn/card/hash-table/182/practical-applications/1140/

PROBLEM: Implement the MyHashMap class:

MyHashMap() initializes the object with an empty map.
void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
int get(int key) returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
void remove(key) removes the key and its corresponding value if the map contains the mapping for the key.

Examples 1:
Input
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
Output
[null, null, null, 1, -1, null, 1, null, -1]

Explanation
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // The map is now [[1,1]]
myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

CONSTRAINTS:
- 0 <= key <= 10^6
- At most 10^4 calls will be made to put, get, and remove.
*/

#include <iostream>
#include <list>

const int SIZE = 1000;

class MyHashMap {
public:
    MyHashMap();
    ~MyHashMap();
    void put(int key, int value); //inserts a "(key, value)" pair into the HashMap. If the "key" already exists in the map, update the corresponding value.
    int get(int key); //returns the "value" to which the specified "key" is mapped, or -1 if this map contains no mapping for the "key".
    void remove(int key); //removes the "key" and it's corresponding "value" if the map contains the mapping for the "key".
private:
    int hash(int key);
    std::list<std::pair<int, int>> bucket[SIZE];
};

MyHashMap::MyHashMap() {}

MyHashMap::~MyHashMap() {}

void MyHashMap::put(int key, int value) {
    std::pair<int, int> new_value(key, value);

    int index = hash(key);
    if (bucket[index].size() > 0) {
        for (std::list<std::pair<int, int>>::iterator it = bucket[index].begin(); it != bucket[index].end(); it++) {
            if (it->first == key) {
                *it = new_value;
                return;
            }
        }
    }

    bucket[hash(key)].push_back(new_value);
    return;
}

int MyHashMap::get(int key) {
    int index = hash(key);
    if (bucket[index].size() > 0) {
        for (std::list<std::pair<int, int>>::iterator it = bucket[index].begin(); it != bucket[index].end(); it++) {
            if (it->first == key) {
                return it->second;
            }
        }
    }

    return -1;
}

void MyHashMap::remove(int key) {
    int index = hash(key);
    if (bucket[index].size() > 0) {
        for (std::list<std::pair<int, int>>::iterator it = bucket[index].begin(); it != bucket[index].end(); it++) {
            if (it->first == key) {
                bucket[index].erase(it--);
                return;
            }
        }
    }
}

int MyHashMap::hash(int key) {
    return key % SIZE;
}

int main()
{
    //we are mainly using the LeetCode window and relying on it's tests here...
    MyHashMap* obj = new MyHashMap();
    obj->put(3, 4);
    std::cout << obj->get(3) << std::endl;
}