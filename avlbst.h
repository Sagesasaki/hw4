
#ifndef RBBST_H
#define RBBST_H



#include <cstdint>
#include <iostream>
#include <algorithm>
#include <exception>
#include <cstdlib>
#include "bst.h"

struct KeyError { };
/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	virtual void insert(const std::pair<const Key, Value> &new_item); // TODO
	virtual void remove(const Key& key);  // TODO
protected:
	virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
	// Add helper functions here

	void removeFix(AVLNode<Key,Value>* n, int diff);
	void rotateRight(AVLNode<Key,Value>* n);
	void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
	void rotateLeft(AVLNode<Key,Value>* n);
	AVLNode<Key,Value>* predecessor(AVLNode<Key, Value>* current);

	void functionOne(AVLNode<Key,Value>* p, AVLNode<Key,Value>* t);
	void functionTwo(AVLNode<Key,Value>* p, AVLNode<Key,Value>* t);
	
protected:   
	AVLNode<Key,Value>* root_ = nullptr;
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* k, AVLNode<Key,Value>* n)
{
	if(k == nullptr) return;
	else if(k -> getParent() == nullptr)
	{
			return;
	}
	AVLNode<Key,Value>* g = k->getParent();

    //if p is the left child
    if(k->getKey() < g->getKey())
    {
			int new_Balance = g->getBalance();

			if(new_Balance == 1){
				g->setBalance(0); return; // in this case, balance is 1
			}
			// if(new_Balance == 1){ g->setBalance(0); return; // in this case, balance is 1
			// }
			if(new_Balance == 0){
				g->setBalance(-1); insertFix(g,k); // in this case, balance is 0
			}
        if(new_Balance != 0 && new_Balance != 1) //balance of g is -1
        {
            
					if(k->getBalance() == 1) // cases of zig-zag
					{
						rotateLeft(k); rotateRight(g);
						// std::cout << n->getBalance();
						// if(n->getBalance() == 11){
						if(n -> getBalance() == -1){
							k -> setBalance(0); g -> setBalance(1); n -> setBalance(0);}
						else if(n -> getBalance() == 0) 
						{
							// std::cout << n->getBalance();
							k -> setBalance(0); g -> setBalance(0); n -> setBalance(0);
							// k -> setBalance(0); g -> setBalance(0); n -> setBalance(0);

						}
						//n = 1
						else
						{
							k->setBalance(-1); g->setBalance(0); n->setBalance(0);
							// k -> setBalance(-1); g -> setBalance(0); n -> setBalance(0);
						}
					}
            //zig zig and p balance is -1
					else
					{
						rotateRight(g); k -> setBalance(0); g -> setBalance(0);
							//if(p -> getParent() == nullptr) root_ = p;
					}
        }
    }
    
    //must be right child since know the child exists
    else
    {
        int new_Balance = g -> getBalance();
        //balance = -1
        if(new_Balance == -1) 
        {
					g -> setBalance(0);
					return;
        }
        //balance = 0
        else if(new_Balance == 0) 
        {
					g -> setBalance(1); insertFix(g,k);
        }
        //balance of g = 1
        else
        {
            if(k -> getBalance() == -1) //zig zag cases
            {
							rotateRight(k);
							rotateLeft(g);
							// rotateLeft(key);
							if(n -> getBalance() == 1){ k -> setBalance(0); g -> setBalance(-1); n -> setBalance(0); }
							else if(n -> getBalance() == 0)
							{
								k->setBalance(0); g->setBalance(0); n->setBalance(0);
							}
							//n = -1
							else
							{
								k->setBalance(1); n->setBalance(0); g->setBalance(0);
							}
            }
            //zig zig and p balance is -1 in this case
            else
            {
							rotateLeft(g); k -> setBalance(0); g -> setBalance(0);
							// k -> setBalance(1); n -> setBalance(0); g -> setBalance(0);
            }
            
        }
    }
    
    if(k -> getParent() == nullptr){ root_ = k;}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
	// let us cout the first item 
	std::cout<<new_item.first<<std::endl;

	// TODO
	// make t, (temp) here
	AVLNode<Key,Value>* t = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);

	t -> setBalance(0);

	//check to see if the tree is empty
	if(root_ == nullptr){ root_ = t;}
	// if not empty, go through this thing 
	else{
		//find leaf node
		AVLNode<Key,Value>* current = root_;
		AVLNode<Key,Value>* p = current;
		
		while(current != nullptr)
		{
			p = current;
			if(current->getKey() == new_item.first)
			{
				current->setValue(new_item.second); // setValue
				break; // break out of this while loop
			}
			if(new_item.first > current->getKey()){ current = current->getRight();} // go to the right 
			else{ current = current->getLeft();} //go to the left
		}
		if(current!=nullptr)
		{
			return;
		}
		if(new_item.first > p->getKey()){ functionOne(p,t); } // set the right one 
		else if(new_item.first < p->getKey()){ functionTwo(p,t); } // set the left one 
		if(p->getBalance()!=false){ insertFix(p,t); } // check to see if p->get balance is not 0
	}
	//
	BinarySearchTree<Key,Value>::root_ = root_;
}








// functionOne
template<class Key, class Value>
void AVLTree<Key,Value>::functionOne(AVLNode<Key,Value>* p, AVLNode<Key,Value>* t){
	p->setRight(t); t->setParent(p); p->updateBalance(1);
}

// functionTwo
template<class Key, class Value>
void AVLTree<Key,Value>::functionTwo(AVLNode<Key,Value>* p, AVLNode<Key,Value>* t){
	p->setLeft(t); t->setParent(p); p->updateBalance(-1);
}

	



// predecessor function
// helper function 
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* curr)
{
	if(curr->getLeft() != nullptr){
		// make a t = temp
		AVLNode<Key,Value>* t = curr->getLeft(); //go to the left child

		while(t->getRight() != nullptr){ t = t->getRight(); } //find the child on the most right
		return t; // then return t
	}
	// has a parent
	else if(curr->getParent() != nullptr){
		if(!(curr->getKey() > curr->getParent()->getKey())) // case of right child
		{
			return (curr->getParent());
		}
		else return ((curr->getParent())->getParent()); // case of left child
	}
	// doesn't have a parent i.e. root node without left child
	else 
		return nullptr; // the node on the very right 
	
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* Left_tempp = n -> getLeft();
    //make left's parent the current parent
    Left_tempp -> setParent(n -> getParent());
    if(n -> getParent() != nullptr)
    {
        
      //make the child of the parent the left node
			if (n -> getKey() > n -> getParent() -> getKey())
			{
					//true if right child
					Left_tempp -> getParent() -> setRight(Left_tempp);
			}
			else
			{
					//true if left child
					Left_tempp -> getParent() -> setLeft(Left_tempp);
			}
    }
    
    //make the left of current the right of the left
    n -> setLeft(Left_tempp -> getRight());
    //make the right the current
    Left_tempp -> setRight(n);
    //set the parent to the left
    n -> setParent(Left_tempp);
}

template<typename Key, typename Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* Right_temp = n -> getRight();
    //make right parent the current parent
    Right_temp -> setParent(n -> getParent());
    if(n -> getParent() != nullptr)
    {
        
			//make the child of the parent the right node
			if (n -> getKey() > n -> getParent() -> getKey())
			{
				//true if right child
				Right_temp -> getParent()->setRight(Right_temp);
			}
			else
			{
				//true if left child
				Right_temp -> getParent()->setLeft(Right_temp);
			}
    }
    
    //make the right of current the left of the right
    n -> setRight(Right_temp -> getLeft());
    //make left the current
    Right_temp -> setLeft(n);
    //set the parent to the left
    n->setParent(Right_temp);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	// TODO
	AVLNode<Key,Value>* curr = root_;
	while(curr != nullptr)
	{
		if(curr -> getKey() == key){break;}
	// else curr = curr -> getLeft();
		if(key > curr -> getKey()) curr=curr->getRight();
		else curr = curr -> getLeft();
	}

    //2 children
    if(curr -> getLeft() != nullptr && curr -> getRight() != nullptr)
    {
        nodeSwap(curr, predecessor(curr));
    }

    AVLNode<Key,Value>* p = curr -> getParent();

 		int d;
    //setting d value for fix
    if(p != nullptr)
    {
        if(curr == p -> getLeft()) d = 1; else d = -1;
    }
    
    //up to this point current can have at most one child 
    
    //current has a child means current must be a right child of its parent
    if(curr->getLeft() != nullptr)
    {
			AVLNode<Key,Value>* c = curr -> getLeft();
			// c -> setParent(p); p->setRight(c);
			c -> setParent(p); p->setRight(c);

    }
    //has no child 
    else
    {
        //if it has a parent
        if(p != nullptr)
        {
					//if right child
					if(p -> getRight() == curr){p -> setRight(nullptr);}
					//if left child
					else{p -> setLeft(nullptr);}
        }
        root_ = nullptr; // no parent means it is root node
    }
		// delete curr;
    delete curr;

    removeFix(p,d);
    BinarySearchTree<Key,Value>::root_ = root_;
		//  BinarySearchTree<Key,Value>::root_ = root_;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int diff)
{
    if(n == nullptr) return;

    AVLNode<Key,Value>* p = n -> getParent();
    int pdn = 0;
    if(p != nullptr)
    {
        //left child
        if(n -> getKey() < p -> getKey()) pdn = 1;
        //right child
        else pdn = -1;
    }

    //diff = -1 means removed a right child
    if(diff == -1)
    {
        if(n->getBalance() == 0)
        {
          n->setBalance(-1);
          return;
        }
        else if(n -> getBalance() == 1){n -> setBalance(0); removeFix(p, pdn);}
        //-1
        else
        {
            AVLNode<Key,Value>* c;
            
            c = n->getLeft();//left will be taller than the right. This is because we removed from the right. 


            int c_balance = c -> getBalance();

            //zig-zig

            if(c_balance == -1)
            {
							rotateRight(n); n -> setBalance(0); c -> setBalance(0); removeFix(p,pdn);
            }
            //zig-zig
            else if(c_balance == 0)
            {
							rotateRight(n); n -> setBalance(-1); c -> setBalance(1); return;
            }
            //zig-zag
            else
            {
                AVLNode<Key,Value>* g = c -> getRight();
                rotateLeft(c);
                rotateRight(n);
								// rotateRight(n);
								// rotateRight(c);

                if(g -> getBalance() == 1)
                {
                  n -> setBalance(0); c -> setBalance(-1); g -> setBalance(0);
                }
                else if(g -> getBalance() == 0)
                {
                  n -> setBalance(0); c -> setBalance(0); g -> setBalance(0);
                }
                else
                {
                   n -> setBalance(1); c -> setBalance(0); g -> setBalance(0);
                }
                removeFix(p,pdn);
            }
        }
    }
    //diff = 1 since removed from the left
    else
    {
			if(n -> getBalance() == 0)
			{
					n -> setBalance(1);
					return;
			}
			else if(n->getBalance() == -1){
				n->setBalance(0); removeFix(p, pdn); 
			}
			else
			{
				AVLNode<Key,Value>* c;
				//left will be taller since we removed from the left
				c = n -> getRight();
				int c_balance = c -> getBalance();
				
				if(c_balance == 1) //first zig zig 
				{
					rotateLeft(n); n -> setBalance(0); c -> setBalance(0);
					removeFix(p,pdn);
				}
				// if(c_balance == 1)
				
				//zig-zig
				else if(c_balance == 0) //second zig zig 
				{
					rotateLeft(n); n -> setBalance(1); c -> setBalance(-1);
					return;
				}
				else //else zig zig 
				{
					AVLNode<Key,Value>* g = c -> getLeft();
					rotateRight(c);
					rotateLeft(n);
					if(g -> getBalance() == -1){ n -> setBalance(0); c -> setBalance(1); g -> setBalance(0); }
					else if(g -> getBalance() == 0){
						n -> setBalance(0); c -> setBalance(0); g -> setBalance(0);
					}
					else n -> setBalance(-1); c -> setBalance(0); g -> setBalance(0);
					removeFix(p,pdn);
				}
			}
    }

}





template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif


