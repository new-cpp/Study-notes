/*for binary search tree( BST) : left sub tree always less than right sub tree*/

#include <string>
struct BST
{
  std::string data;
  BST* right{nullptr};
  BST* left{nullptr};
};


void insert_recursive(BST* t_bst, std::string t_value)
  {
    if(t_bst == nullptr)
      {
        t_bst = new BST();
        t_bst->data = t_value;
      }
    else
      {
        if(t_value >= t_bst-> data)
          {
            return insert_recursive(t_bst->right, t_value);
          }
        else
          {
            return insert_recursive(t_bst->left , t_value);
          }
      }
  }

// Todo
//
// delete node : pseudo code
// case 1 : if it's leaf just delete
// case 2 : have one child : just copy the chile value to node and delete the child
// case 3 : have 2 child then the min of the right side copy to root and deleted
void delete_node_recursive(BST* t_bst, std::string t_value);


// lowest common ancestor : pseudo code
// case 1 : if the root is one of them return the root.
//case 2 : if the root is between the two value return root
//case 3 : if root > max(node1 ,node2) -> lowest_common( root->left,node1,node2 )(else right)
void lowest_common_ancestor(BST* root, BST* node1 , BST* node2);

// isBST : Pseudo code ->
//
// if empty or left sub tree is a bst and max left sub tree is less then root value (analogic for right side)

bool isBST(BST* root);
void in_order_print(BST* t_bst)
  {
    if(t_bst == nullptr) return;

    in_order_print(t_bst->left);
    printf("%s ",t_bst->data.c_str());
    in_order_print(t_bst-> right);
  }

int main()
  {
    return 0;
  }
