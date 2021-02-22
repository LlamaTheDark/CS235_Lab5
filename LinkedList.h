#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include <typeinfo>
#include "LinkedListInterface.h"


template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    struct Node {
        T item;
        Node *next = NULL;

        Node(T item){
            this->item = item;
        }
        Node(T item, Node *next){
            this->item = item;
            this->next = next;
        }
        ~Node(){
            // I'm thinking this'll recursively delete all the nodes in the list...
            delete next;
        }
    };

    Node *head = NULL;
    int length = 0;

public:

	LinkedList() {};
	~LinkedList() {

    };

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertHead(T value) {
        if(isEmpty()){
            head = new Node(value);
        }else if(!contains(value)){
            head = new Node(value, head);
        }
        length++;
    }

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertTail(T value){
        if(isEmpty()){
            head = new Node(value);
        }else if(!contains(value)){
            Node *tmp;
            for(tmp = head; tmp != NULL; tmp = tmp->next); // will take us all the way to the tail
            tmp->next = new Node(value);
            length++;
        }
    }

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	virtual void insertAfter(T value, T afterValue){
        Node *tmp = find(afterValue);
        if(tmp != NULL){
            Node *newNode = new Node(value, tmp->next);
            tmp->next = newNode;
            length++;
        }
    }

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	virtual void remove(T value){
        if(!isEmpty()){
            Node *tmp = find(value, true);
            if(tmp != NULL){
                Node *tmpDel;
                if(tmp == head){
                    tmpDel = head;
                    head = head->next;
                } else {
                    tmpDel = tmp->next;
                    tmp->next = tmp->next->next;
                }
                tmpDel->next = NULL;
                delete tmpDel;
            }
            length--;
        }
    }

	/*
	clear

	Remove all nodes from the list.
	*/
	virtual void clear(){
        delete head;

        head = NULL;
        length = 0;
    };

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	virtual T at(int index){ 
        return *(new T()); 
    };

	/*
	size

	Returns the number of nodes in the list.
	*/
	virtual int size() { return length; }

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	virtual std::string toString(){
        std::stringstream ss;
        ss.exceptions(std::ios_base::failbit);
        
        try {
            Node *tmp;
            for(tmp = head; tmp != NULL; tmp = tmp->next){
                ss << tmp->item << " ";
            }
        } catch(std::ios_base::failure &ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return "";
        }

        return ss.str();
    }


    bool isEmpty() { return head == NULL; }


    /*
    Node *find(T, bool)

    @param value: the value to be found within the array
    @param returnPrevious: whether to return the Node that contains the array or that before it
                           *has no effect if the value is at the head*

    returns a pointer to either the Node that contains the provided value, the Node before the 
    one that contains the provided value, or NULL if the value is not found.

    */
    Node *find(T value, bool returnPrevious = false){
        if(isEmpty()) return NULL;
        if(compare(head->item, value) == 0){
            return head;
        }
        for(Node *tmp = head; tmp->next != NULL; tmp = tmp->next){
            if(compare(tmp->next->item, value) == 0){
                return (returnPrevious)?tmp:tmp->next;
            }
        }
        return NULL;
    }
    bool contains(T value) {
        return find(value) != NULL;
    }

    /*
    @param a, b: two values to compare

    returns 0 if equal, 1 otherwise

    */
    bool compare(T a, T b){
        // if(typeid(T) == typeid(std::string)) return compareString(a, b);
        if(a == b){
            return 0;
        }
        return 1;
    }
    // bool compareString(std::string a, std::string b){
    //     if(a.compare(b) == 0){
    //         return 0;
    //     }
    //     return 1;
    // } // this will not work with strings
    

};

#endif /* LINKEDLIST_H_ */