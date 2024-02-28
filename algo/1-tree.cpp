#include <cstdio>
#include <cstdint>
#include <string>

/* c style implmentation */
/* defintion */
struct Tree
{
  std::string data;
  Tree* left;
  Tree* right;
};



static void print_tree_recursive( Tree* t_tree,  uint32_t depth)
  {
   if(t_tree == nullptr)
     {
       return;
     }

   printf("node value : %s, node depth : depth\n", t_tree->data.c_str());

   print_tree_recursive(t_tree->left, depth + 1);
   print_tree_recursive(t_tree->right, depth + 1);

  }

static void print_tree(Tree* t_node)
  {
    print_tree_recursive(t_node , 0);
  }

static bool same_tree(Tree* a ,Tree* b)
  {
    if(a == nullptr)
      {
        return b==nullptr;
      }

    if(a->data!= b->data)
      {
        return false;
      }

    return same_tree(a->left,b->left) && same_tree(a->right,b-> right);
  }



int main()
  {
    return 0;
  }
