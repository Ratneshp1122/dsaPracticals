/*
Title: Implement a Threaded Binary Search Tree.
Problem Statement: Convert given binary tree into threaded binary tree. Analyze time and space
complexity of the algorithm.

*/


#include<iostream>
using namespace std;

struct Node{
  int data;
  Node* left;
  Node* right;
  bool lthread;
  bool rthread;
};

class TBT{
    Node* root = new Node;
    void insert(Node* temp,Node*& par){
      if(par == NULL){
        par = temp;
        cout << par->data << ": Inserted. " << endl;
        return;
      }
      else if(par->data > temp->data){
      cout << temp->data << ": going left of " << par->data << "." << endl;
        insert(temp,par->left);
        
      }
      else{
        cout << temp->data << ": going right of " << par->data << "." << endl;
        insert(temp,par->right);
      }
    }

    void createThread(Node* root,Node*& prev){
        if(root == NULL) return;
        createThread(root->left,prev);
        if(root->left == NULL){
            root->left = prev;
            root->lthread = true;
        }
        if(prev != NULL && prev->right == NULL){
            prev->right = root;
            prev->rthread = true;
        }
        prev = root;


        createThread(root->right,prev);
        
    }

    public:
    TBT(){
    root = NULL;
  }

    void add(int d){
        Node* temp = new Node{d,NULL,NULL,false,false};
        insert(temp, root);

}
    void makeThreaded(){
        Node* prev = NULL;
        createThread(root,prev);
    }
    void inorderThreadedTraversal() {
        Node* curr = root;
    
        while (curr && !curr->lthread) {
            curr = curr->left;
        }
    
        while (curr) {
            cout << curr->data << " ";
    
            if (curr->rthread) {
                curr = curr->right;
            } 
            else {
                curr = curr->right;
                while (curr && !curr->lthread) {
                    curr = curr->left;
                }
            }
        }
    }
    

};


int main(){
  TBT t;
  t.add(5);
  t.add(3);
  t.add(4);
  t.add(2);
  t.add(6);
  t.makeThreaded();
  t.inorderThreadedTraversal();
  return 0;
}

