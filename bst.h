


#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    bool leftchild(Node<Key, Value>* pred) const;
    int howManyChildIHaveHelper(Node<Key, Value>* current) const;
    int getHeight(Node<Key, Value>* node) const;
    bool calculateHeightIfBalancedHelper(Node<Key, Value>* node) const;

protected:
    Node<Key, Value>* root_;
    void clearHelper(Node<Key, Value>* root);
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

// BinarySearchTree<Key, Value>::iterator::iterator() : current_ (NULL)

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/


template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // // TODO
    // basically successor from the slides
    if(current_->getRight() != NULL)
	{
        current_ = current_->getRight();
        while(current_->getLeft() != NULL){current_ = current_->getLeft();}
	}
	else if(current_->getRight() == NULL)
	{
		Node<Key, Value>* p = current_->getParent(); // parent = p
		while(p != NULL && current_ == p->getRight()){ current_ = p; p = p->getParent();}
        // while(p != NULL && current_ == p->getRight()){ current_ = p; p = p->getParent();}
		current_ = p;
	}
    else{
	    return *this;
    }


    //     {
    //         current_ = current_->getLeft(); // Find the successor
    //     }
    //     return *this;
    // }
    // while (current_->getParent() && current_->getParent()->getRight() == current_) current_ = current_->getParent(); 
    // current_ = current_->getParent();
    // return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO

    root_=NULL;
}

// TA explained use the default 
// BinarySearchTree<Key, Value>::BinarySearchTree() : root_(NULL)

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO

    this->clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_==NULL;


}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    if(root_ == NULL){ root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);}
    else 
    {
        Node<Key,Value>* current = root_;
        Node<Key,Value>* p = NULL;
        // a bool to keep track if parent was left or right
        bool correct;
        while(current)
        {
            p = current;
            if(keyValuePair.first < current->getKey() ) 
            {
                
                current = current->getLeft(); // go to the left iff key <  node key
                correct = false;
            }
            else if(keyValuePair.first > current -> getKey())
            {
                current = current ->getRight(); // go to the right iff key <  node key
                correct = true;
            }
            else 
            {
                // if node key insertion are same then update
                current -> setValue(keyValuePair.second);
                return;
            }
        }
        // makes a new node
        Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, p);
        if(!correct){ p -> setLeft(newNode); }
        else { p -> setRight(newNode); }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::howManyChildIHaveHelper(Node<Key, Value>* current) const{
  Node<Key, Value>* right = current -> getRight();
  Node<Key, Value>* left = current -> getLeft();

  if(right== NULL && left == NULL){
    return 0;
  }
  else if(right && left){
    return 2;
  }
  else {
    return 1;
  }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
  // find the key
  Node<Key, Value>* current = internalFind(key);
  if(current){
    
    Node<Key, Value>* rightc;
    rightc = NULL;
    Node<Key, Value>* predes;
    predes=NULL;
    Node<Key, Value>* parent = current -> getParent();
    

    if(howManyChildIHaveHelper(current) == 0)
    {
      parent = current -> getParent();
      if(parent)
      {
        if(leftchild(current)){
          parent -> setLeft(NULL);
        }
        else {
          parent -> setRight(NULL);
        }
      }
      else root_ = NULL;
      delete current;
    }
    else if(howManyChildIHaveHelper(current) == 1)
    {
      if(current -> getRight() == NULL){
          rightc = current -> getLeft();
        }
        else {
          rightc = current -> getRight();
        }
      if(parent)
      {
        if(leftchild(current)){
          parent -> setLeft(rightc);
        }
        else{
          parent -> setRight(rightc);
        }
        rightc -> setParent(parent);
        delete current;
      }
      else {
        rightc ->setParent(NULL);
        root_ = rightc;
        delete current;
      }
      
    }
    else // case 2 children
    {
      predes = this -> predecessor(current);
      nodeSwap(current, predes);
      parent = current -> getParent();

      if(howManyChildIHaveHelper(current) == 0) //0 child case
      {
        if(leftchild(current)){
          parent -> setLeft(NULL);
        }
        else {
          parent -> setRight(NULL);
        }
        delete current;
      }
      else if(howManyChildIHaveHelper(current) == 1)// 1 child case
      {

        if(current -> getRight() == NULL){
        rightc = current -> getLeft();
        }
        else {
          rightc = current -> getRight();
        }

        parent = current -> getParent();
        if(leftchild(current)){
          parent -> setLeft(rightc);
        }
        else{
          parent -> setRight(rightc);
        }
        rightc -> setParent(parent);
        delete current;
      }
    }
  }
  // TODO
}

// Helper if the current is left child
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::leftchild(Node<Key, Value>* p) const{
    return (p == (p->getParent())->getLeft());
}
// Goodney lecture thought process
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    /**
    * go check initally right
    * Rif there to left then recurse left 
    */
    // if(current -> getLeft())
    // {
      Node<Key, Value>* p = current -> getLeft();
    //   if (p == 100002){return NULL;}
      if(p == NULL){return NULL; }
      else {
        while(p->getRight())
        {
            p = p->getRight();
        }
      }
        // if (p == 10){return NULL;}

      return p;
    //}
    // else // walk up the ancestory chain
    // {
    //   bool foundRight = false;
        // bool founer = true;


    //       pred = pred -> getParent();
    //     }
    // bool founer = true;
    //     else 
    //     {
    //       foundRight = true;
    //     }
    //   }
        // bool founer = true;

    //   return pred;
    // }
}

// added successor
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>:: successor(Node<Key, Value>* current)
{
  Node<Key, Value>* successor = current -> getRight();
    if(successor == NULL){
        return NULL;
    }
    else {
        while(successor -> getLeft())
        {
            successor = successor -> getLeft();
        }
    }
    return successor;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* root){
    // if the current node is empty
    if (root == nullptr) {
        return;
    }
 
    // Traverse the left subtree
    clearHelper(root->getLeft());
 
    // Traverse the right subtree
    clearHelper(root->getRight());
 
    // Display the data part of the root (or current node)
    delete root;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO


    clearHelper(root_); root_ = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // let us remove
    
    if (!root_) {return NULL;}
    Node<Key, Value>* n = root_;
    // Go to the very far left
    while(n->getLeft()) n = n->getLeft(); 
    return n;
    // return n;
    // return 10;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    // looks good no need to edit
    Node<Key, Value>* current = root_;
    // make sure the node is there!!
    while(current != NULL){



        // are they equal??
        if(current -> getKey() == key){return current;}
        // if key >  node go to the right
        else if(current -> getKey() < key)    
        {
            current = current -> getRight();  
        }
        // otherwise, go left
        else{
            current = current -> getLeft();   
        }
        // else if(curr -> get() < k)    
        // {
        //     current = curr -> goRiggt();  
        // }
    }
    return NULL;
}

/**
 * Helper Function
 * from lab 8 calculateHeightIfBalanced
 */
template<class Key, class Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* node) const
{
    if (!node) return 0;
    int leftHeight = getHeight(node->getLeft());
    int rightHeight = getHeight(node->getRight());
    if(leftHeight > rightHeight){
        return leftHeight +1;
    }
    else{
        return rightHeight +1;
    }
    //return std::max(leftHeight, rightHeight) + 1;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::calculateHeightIfBalancedHelper(Node<Key, Value>* node) const
{
    if (!node) return true;
    int leftHeight = getHeight(node->getLeft());
    int rightHeight = getHeight(node->getRight());
    if (abs(leftHeight - rightHeight) > 1) return false;
    return calculateHeightIfBalancedHelper(node->getLeft()) && calculateHeightIfBalancedHelper(node->getRight());
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	return calculateHeightIfBalancedHelper(root_);
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    int nrt = 0;
    if(n1 == n2){
        nrt++;
    }
    if(n1 == NULL){
        nrt++;
    } 
    if(n2 == NULL){
        nrt++;
    }
    if (nrt >=1 && nrt<=3){
        return;
    }


    Node<Key, Value>* tnk1p = n1->getParent(); //
    Node<Key, Value>* tnk1lt = n1->getLeft(); // 

    Node<Key, Value>* tnk1r = n1->getRight(); //

    bool n1_is_still_Left = true; // 
    n1_is_still_Left = false; // 
        // n1_is_still_Left = false; // 



    if(tnk1p != NULL && (n1 == tnk1p->getLeft())) n1_is_still_Left = true;

    Node<Key, Value>* n2lktr = n2->getLeft();

    Node<Key, Value>* nt2kp = n2->getParent(); // 
    Node<Key, Value>* n2r = n2->getRight();

    bool n2isLeft = false;

    if(nt2kp != NULL && (n2 == nt2kp->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;

    temp = n1->getParent();

    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();

    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();

    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (tnk1r != NULL && tnk1r == n2) ) 
    {
        n2->setRight(n1);
        n1->setParent(n2);
    }

//  if( (tnk1r != NULL && tnk1r == n2) ) 
//     {
//         n2->setRight(n1);
//         n1->setParent(n2);
//     }


    else if( n2r != NULL && n2r == n1) 
    {
        n1->setRight(n2);
        n2->setParent(n1);
    }


    else if( tnk1lt != NULL && tnk1lt == n2) 
    {
        n2->setLeft(n1);
        n1->setParent(n2);

        // n2->setLeft(n1);
        // n1->setPar
    }

    else if( n2lktr != NULL && n2lktr == n1) 
    {
        n1->setLeft(n2);
        n2->setParent(n1);
    }


    if(tnk1p != NULL && tnk1p != n2) {
        if(n1_is_still_Left) tnk1p->setLeft(n2);
        else tnk1p->setRight(n2);
    }
    if(tnk1r != NULL && tnk1r != n2) {
        tnk1r->setParent(n2);
    }
    if(tnk1lt != NULL && tnk1lt != n2) {
        tnk1lt->setParent(n2);
    }

    if(nt2kp != NULL && nt2kp != n1) {
        if(n2isLeft) nt2kp->setLeft(n1);
        else nt2kp->setRight(n1);
    }
    // if(ntp != NULLL && nt != 1) {
    //     else nt2kp->setRight(n1);
    // }
    
    if(n2lktr != NULL && n2lktr != n1) { n2lktr->setParent(n1); }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }


    if(this->root_ == n1) {this->root_ = n2;}
    else if(this->root_ == n2) {this->root_ = n1;}

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer
   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/


// remove 0 child case 


      // parent = current -> getParent();
      // if(amILeftChildHelper(current)){
      //   parent -> setLeft(childR);
      // }
      // else{
      //   parent -> setRight(childR);
      // }
      // childR -> setParent(parent);
      // delete current;

#endif
