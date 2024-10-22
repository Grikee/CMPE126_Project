#ifndef BinaryTree_h
#define BinaryTree_h

#include <vector>
using namespace std;

template <class T>
struct TreeNode{
    T data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(T value): data(value), left(nullptr), right(nullptr){}
};

template <class T>
class BinaryTree{
private:


    TreeNode<T>* insert(TreeNode<T>* current, T value){
        if(current == nullptr){
            return new TreeNode<T>(value);
        }

        if (value < current->data){
            current->left = insert(current->left, value);
        }else{
            current->right = insert(current->right, value);
        }

        return current;
    }

    
    void inOrderTraversalHelper(TreeNode<T>* current, vector<T>& result) const{
        if (current != nullptr) {
            inOrderTraversalHelper(current->left, result);
            result.push_back(current->data);
            inOrderTraversalHelper(current->right, result);
        }
    }

    void deleteTree(TreeNode<T>* current) {
        if (current != nullptr) {
            deleteTree(current->left);
            deleteTree(current->right);
            delete current;
        }
    }


public:
    TreeNode<T>* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        deleteTree(root);
    }

    TreeNode<T>* getRoot() const{
        return *root;
    }

    void insert(T value) {
        root = insert(root, value);
    }

    vector<T> inOrderTraversal() const{
        vector<T> result;
        inOrderTraversalHelper(root, result);
        cout << endl;
        return result;
    }

    
    TreeNode<T>* search(TreeNode<T>* root, T input) {
        if(root == nullptr || root->data == input){
          return root;
        }
        else if(root->data < input){
          return search(root->right, input);
        }
        return search(root->left, input);
    }
    
};

#endif /* BinaryTree_h */