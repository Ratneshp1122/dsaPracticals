#include<iostream>
using namespace std;

struct Node{
  int data;
  Node* left;
  Node* right;
};

class BST{
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
  int height(Node* temp){
    if(temp == NULL){
      return 0;
    }
    return max(height(temp->left),height(temp->right)) + 1;
  }

  void mirror(Node* temp){
      if(temp == NULL){
        return;
      }
      mirror(temp->left);
      mirror(temp->right);
      Node* temp2 = temp->left;
      temp->left = temp->right;
      temp->right = temp2;
  }
  public:
  BST(){
    root = NULL;
  }
void add(int d){
    Node* temp = new Node{d,NULL,NULL};
    insert(temp, root);
}
void minVal(){
    Node* temp = root; 
    while(temp->left != NULL){
      temp = temp->left;
    }
    cout << temp->data << endl;
}

void maxVal(){
    Node* temp = root; 
    while(temp->right != NULL){
      temp = temp->right;
    }
    cout << temp->data << endl;
}

bool search(int x){
    Node* temp = root;
    while(temp != NULL){
      if(temp->data == x){
        return true;
      }
      if(temp->data > x){
        temp = temp->left;
      }
      else{
        temp = temp->right;
      }
    }
    return false;
  }
  void inorder(Node* temp){
    if(temp == NULL) return;
    inorder(temp->left);
    cout << temp->data << " ";
    inorder(temp->right);
  }
  
  void displayInOrder(){
    inorder(root);
    cout << endl;
  }
    

int numberOfNodesInLongestPath(){
    return height(root);
}

void mirrorTree(){
    mirror(root);
}
  
};
int main(){
  BST a;
  a.add(50);
  a.add(20);
  a.add(30);
  a.add(40);
  a.add(10);
  a.add(60);
  a.add(70);
  a.add(80);
  a.add(90);
  a.add(100);
  a.minVal();
  a.maxVal();
a.displayInOrder();
  cout << a.search(20);
  cout << a.search(150);
  cout << a.numberOfNodesInLongestPath();
  a.mirrorTree();
  a.maxVal();
  a.minVal();
  a.displayInOrder();


  return 0;
}
