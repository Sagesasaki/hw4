#include "equal-paths.h"
using namespace std;


// // max helper function
// int max(int a, int b){
//   return (a<b)?b:a;
// }


// // we use this helper function for the equalPaths function
// int calculateHeightIfBalanced(Node* root) {
//     // Base case: an empty tree is always balanced and has a height of 0
//     if (root == nullptr) return 0;

//     // Think about cases to handle:
//     // - What if at least one subtree is NOT balanced?
//     // - What if BOTH are balanced?

//     // TODO: handle the cases here

//     // check left subtree
//     int leftSubtreeHeight = calculateHeightIfBalanced(root->left);
//     if (leftSubtreeHeight == -1) return -1;
//     // if left subtree is not balanced then the entire tree is also not balanced

//     // check right subtree
//     int rightSubtreeHeight = calculateHeightIfBalanced(root->right);
//     if (rightSubtreeHeight == -1) return -1;
//     // if right subtree is not balanced then the entire tree is also not balanced
    
//     //checking the difference of left and right subtree for current node
//     // we want all paths from leaf to root to be of same length
//     if (abs(leftSubtreeHeight - rightSubtreeHeight) > 0)
//     {
//         return -1;
//     }
//     return (max(leftSubtreeHeight, rightSubtreeHeight) + 1);
// }



// bool equalPaths(Node * root)
// {
// 	// this is a recursive function because 
// 	// the helper function is recursive 
//   if (calculateHeightIfBalanced(root) != -1){
// 		return true;
//   }
// 	return false;

// }



bool checkthelevelo(Node *node, int currLevel, int& leafLevel);

bool checkthelevelo(Node *n, int clevel, int& leafLevel)
{
  // base case
  if (n == nullptr){return true;}

  // work when you hit the first leaf node
  if (n->left == nullptr && n->right == nullptr)
  {
    // first leaf node found
    if (n->left == nullptr && leafLevel == 0)
    {
      leafLevel = clevel; // first found ever leaf node to level
      return true;
    }
    // compare the level of current with first leaf's level
    return (clevel == leafLevel);
  }




  bool left = checkthelevelo(n->left, clevel+1, leafLevel); // check left sub tree

  bool right = checkthelevelo(n->right, clevel+1, leafLevel); // and the right as well
          // bool right = checkthelevelo(node->right, currLevel + 1, leafLevel);
  return (right && left);

  // TA helped with recusive idea
  // return checkLevel(node->left, currLevel + 1, leafLevel) &&
  //         checkLevel(node->right, currLevel + 1, leafLevel);

}
bool equalPaths(Node * r)
{
  // Add your code below

  int level;
  int i = 0;

  level = 0;
  int leaflvl;
  leaflvl = 0;

  return checkthelevelo(r, level, leaflvl);
    // return checklevel(root, level, leaflvl);


}