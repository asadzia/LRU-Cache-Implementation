#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};


class LRUCache : public Cache
{
    private:
        int size;
    
    public:
        LRUCache (int cap)
        {
            cp = cap;
            size = 0;
            tail = head = NULL;
        }
        
        void set (int key, int value)
        {            
                if (mp.find(key) != mp.end())
                {   //place it in the front
                
                    mp[key]->value = value;
                    Node* temp = mp[key];
                    
                    if (temp == tail && head != tail)
                    {
                        // if the node is at the end of the list
                        temp->prev->next = NULL;
                        tail = temp->prev;
                        temp->prev = NULL;
                        head->prev = temp;
                        temp->next = head;
                        head = temp;
                    }
                    else if (temp != head && temp != tail)
                    {
                        // if the node is in between the tail and the head
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        temp->prev = NULL;
                        head->prev = temp;
                        temp->next = head;
                        head = temp;
                    }
                }
                else
                {
                     if (size < cp)
                     {
                       Node* myNode = new Node(key, value);
                       
                       if (tail == NULL && head == NULL)
                       {
                           head = myNode;
                           tail = myNode;
                           mp[key] = myNode;
                           size++;
                       }
                       else
                       {
                           myNode->prev = NULL;
                           head->prev = myNode;
                           myNode->next = head;
                           head = myNode;
                           mp[key] = myNode;
                           size++;
                       }
                    }
                    else if (size == cp)
                    {
                         // replacing old pages
                         Node* x;
                         x = tail->prev;
                         mp.erase(tail->key);
                         delete (tail);
                         x->next = NULL;
                         tail = x;
                         
                         Node* temp = new Node(key, value);
                         temp->prev = NULL;
                         temp->next = head;
                         head->prev = temp;
                         head = temp;
                         mp[key] = temp;
                    }
               }
        }
        
        int get (int key)
        {
            if (size == 0 || mp.find(key) == mp.end())
            {
               return -1;
            }
            else
            {
                    Node* temp = mp[key];
                    
                    if (temp == tail && head != tail)
                    {
                        // if the node is at the end of the list
                        temp->prev->next = NULL;
                        tail = temp->prev;
                        temp->prev = NULL;
                        head->prev = temp;
                        temp->next = head;
                        head = temp;
                    }
                    else if (temp != head && temp != tail)
                    {
                        // if the node is in between the tail and the head
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        temp->prev = NULL;
                        head->prev = temp;
                        temp->next = head;
                        head = temp;
                    }

               return temp->value;
            }
        }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

/*

Abstract base classes in C++ can only be used as base classes. Thus, they are allowed to have virtual member functions without definitions.

A cache is a component that stores data so future requests for that data can be served faster. The data stored in a cache might be the results of an earlier computation, or the duplicates of data stored elsewhere. A cache hit occurs when the requested data can be found in a cache, while a cache miss occurs when it cannot. Cache hits are served by reading data from the cache which is faster than recomputing a result or reading from a slower data store. Thus, the more requests that can be served from the cache, the faster the system performs.

One of the popular cache replacement policies is: "least recently used" (LRU). It discards the least recently used items first.

For example, if a cache with a capacity to store 5 keys has the following state(arranged from most recently used key to least recently used key) -

5 3 2 1 4
Now, If the next key comes as 1(which is a cache hit), then the cache state in the same order will be -

1 5 3 2 4
Now, If the next key comes as 6(which is a cache miss), then the cache state in the same order will be -

6 1 5 3 2
You can observe that 4 has been discarded because it was the least recently used key and since the capacity of cache is 5, it could not be retained in the cache any longer.

Given an abstract base class Cache with member variables and functions: 

mp - Map the key to the node in the linked list
cp - Capacity
tail - Double linked list tail pointer
head - Double linked list head pointer
set() - Set/insert the value of the key, if present, otherwise add the key as the most recently used key. If the cache has reached its capacity, it should replace the least recently used key with a new key.
get() - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

You have to write a class LRUCache which extends the class Cache and uses the member functions and variables to implement an LRU cache.

Input Format

First line of input will contain the  number of lines containing  or  commands followed by the capacity of the cache.
The following  lines can either contain  or  commands.
An input line starting with  will be followed by a  to be found in the cache. An input line starting with  will be followed by the  and  respectively to be inserted/replaced in the cache.

Constraints 
 
 
 

Output Format

The code provided in the editor will use your derived class LRUCache to output the value whenever a get command is encountered.

Sample Input

3 1
set 1 2
get 1
get 2
Sample Output

2
-1
Explanation

Since, the capacity of the cache is 1, the first set results in setting up the key 1 with it's value 2. The first get results in a cache hit of key 1, so 2 is printed as the value for the first get. The second get is a cache miss, so -1 is printed.
*/
