#include "base_iostream.h"

export module base_list1;



template <class T>
class slist_node
{
public:
    T data;
    slist_node* next;
};

template <class T>
class slist
{
    slist_node<T> *front_ptr;  	// points to first node of list

public:

    slist()
	{
		front_ptr = nullptr;
	}

    slist_node<T>* allocate()
    {
        slist_node<T>* temp_ptr = new slist_node<T>();
        return temp_ptr;
    }

    void push_back(T val)
    {       
        // Allocate new node.
        slist_node<T>* temp_ptr = allocate();
        temp_ptr->data = val;
        temp_ptr->next = nullptr;

        if (front_ptr == nullptr)
        {
            front_ptr = temp_ptr;            

            front_ptr->next = temp_ptr->next;

            //print("{}\n", front_ptr->data);
        }
        else
        {
            slist_node<T>* prev_node_ptr = nullptr;
            slist_node<T>* iter_ptr;
	        iter_ptr = front_ptr;
            // Go to last node
	        while (iter_ptr != nullptr)
	        {
                // Store previous node.
                prev_node_ptr = iter_ptr;
		        iter_ptr = iter_ptr->next;
	        }

            iter_ptr = temp_ptr;
            iter_ptr->next = temp_ptr->next;
            // Link previous node next ptr to last node.
            prev_node_ptr->next = iter_ptr;
            //print("{}\n", iter_ptr->data);
        }
    }

    void display()
    {
        slist_node<T> *iter_ptr;
	    iter_ptr = front_ptr;
        while (iter_ptr != nullptr)
	    {
			print("{}\n", iter_ptr->data);
		    iter_ptr = iter_ptr->next;
	    }
    }

};


//======================================================================================

template <class T>
struct Node
{
	T data;     	// Data
	Node *prev;  	// A reference to the previous node
	Node *next; 	// A reference to the next node
};

template <class T>
class dlist
{
	Node<T> *front;  	// points to first node of list
	Node<T> *end;   	// points to last node of list

public:
	dlist()
	{
		front = nullptr;
		end = nullptr;
	}

    Node<T> * get_front()
    {
        return front;
    }

    Node<T> * get_end()
    {
        return end;
    }

    Node<T> * get_node_by_value(T val)
    {
        Node<T> *trav;
	    trav = front;
	    while(trav != nullptr)
	    {
		    if (trav->data == val)
            {
                return trav;
            }
		    trav = trav->next;
	    }

        return end;
    }


    // add_after, add_before does not handle front and end correctly: crash
	void add_after(Node<T> *n, T d)
    {
	    Node<T> *temp;
	    temp = new Node<T>();
	    temp->data = d;

	    temp->prev = n;
	    temp->next = n->next;
	    n->next = temp;
        temp->next->prev = temp;

	    //if node is to be inserted after last node
	    if(n->next == nullptr)
        {
		    end = temp;
        }
    }

	void add_before(Node<T> *n, T d)
    {
	    Node<T> *temp;
	    temp = new Node<T>();
	    temp->data = d;

	    temp->next = n;
	    temp->prev = n->prev;
	    n->prev = temp;
        temp->prev->next = temp;

	    //if node is to be inserted before first node
	    if(n->prev == nullptr)
        {
		    front = temp;
        }
    } 


    
	void add_front(T d)
    {
	    // Creating new node
	    Node<T> *temp;
	    temp = new Node<T>();
	    temp->data = d;
	    temp->prev = nullptr;
	    temp->next = front;

	    // List is empty
	    if(front == nullptr)
		    end = temp;
		
	    else
		    front->prev = temp;
		
	    front = temp;
    }

	void add_end(T d)
    {
	    // create new node
	    Node<T> *temp;
	    temp = new Node<T>();
	    temp->data = d;
	    temp->prev = end;
	    temp->next = nullptr;

	    // if list is empty
	    if(end == nullptr)
		    front = temp;
	    else
		    end->next = temp;	
	    end = temp;
    }

	void delete_node(Node<T> *n)
    {	
	    // if node to be deleted is first node of list
	    if(n->prev == nullptr)
	    {
		    front = n->next; //the next node will be front of list
		    front->prev = nullptr;
	    }
	    // if node to be deleted is last node of list
	    else if(n->next == nullptr)
	    {
		    end = n->prev;   // the previous node will be last of list
		    end->next = nullptr;
	    }
	    else
	    {
		    //previous node's next will point to current node's next
		    n->prev->next = n->next;
		    //next node's prev will point to current node's prev
		    n->next->prev = n->prev;
	    }
	    //delete node
	    delete(n);			
    }


	void forward_traverse()
    {
	    Node<T> *trav;
	    trav = front;
	    while(trav != nullptr)
	    {
		    print("{}\n", trav->data);
		    trav = trav->next;
	    }
    }

	void backward_traverse()
    {
	    Node<T> *trav;
	    trav = end;
	    while(trav != nullptr)
	    {
		    print("{}\n", trav->data);
		    trav = trav->prev;
	    }
    }

};