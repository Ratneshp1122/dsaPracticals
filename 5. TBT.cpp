#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool lthread;
    bool rthread;
};

class TBT {
    Node* root;

    void insert(Node* temp, Node*& par) {
        if (par == NULL) {
            par = temp;
            cout << par->data << ": Inserted.\n";
            return;
        }
        else if (par->data > temp->data) {
            cout << temp->data << ": going left of " << par->data << ".\n";
            insert(temp, par->left);
        }
        else {
            cout << temp->data << ": going right of " << par->data << ".\n";
            insert(temp, par->right);
        }
    }

    void createThread(Node* root, Node*& prev) {
        if (root == NULL) return;

        createThread(root->left, prev);
        if (root->left == NULL) {
            root->left = prev;
            root->lthread = true;
        }
        if (prev != NULL && prev->right == NULL) {
            prev->right = root;
            prev->rthread = true;
        }
        prev = root;
        createThread(root->right, prev);
    }

public:
    TBT() {
        root = NULL;
    }

    void add(int d) {
        Node* temp = new Node{ d, NULL, NULL, false, false };
        insert(temp, root);
    }

    void makeThreaded() {
        Node* prev = NULL;
        createThread(root, prev);
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

    // 🚨 Function to delete a node with 0 or 1 child only
    void deleteNode(int key) {
        Node* parent = NULL;
        Node* curr = root;
        bool found = false;

        // Search for the node
        while (curr != NULL) {
            if (key == curr->data) {
                found = true;
                break;
            }

            parent = curr;

            if (key < curr->data) {
                if (curr->lthread) break;
                curr = curr->left;
            } else {
                if (curr->rthread) break;
                curr = curr->right;
            }
        }

        if (!found) {
            cout << "Node not found.\n";
            return;
        }

        // Case 1: Leaf node
        if (curr->lthread && curr->rthread) {
            if (parent == NULL) {
                root = NULL;
            } else if (parent->left == curr) {
                parent->lthread = true;
                parent->left = curr->left;
            } else {
                parent->rthread = true;
                parent->right = curr->right;
            }
            delete curr;
        }

        // Case 2: One child
        else if (curr->lthread == false && curr->rthread == true) {
            // Left child only
            Node* child = curr->left;
            if (parent == NULL) root = child;
            else if (parent->left == curr) parent->left = child;
            else parent->right = child;
            delete curr;
        }
        else if (curr->lthread == true && curr->rthread == false) {
            // Right child only
            Node* child = curr->right;
            if (parent == NULL) root = child;
            else if (parent->left == curr) parent->left = child;
            else parent->right = child;
            delete curr;
        }

        else {
            cout << "Deletion for nodes with 2 children not supported.\n";
        }
    }
};
int main() {
    TBT t;
    t.add(5);
    t.add(3);
    t.add(4);
    t.add(2);
    t.add(6);

    t.makeThreaded();
    cout << "\nInorder before deletion:\n";
    t.inorderThreadedTraversal();

    cout << "\n\nDeleting node 2 (leaf)...\n";
    t.deleteNode(2);

    cout << "\nInorder after deletion:\n";
    t.inorderThreadedTraversal();

    cout << "\n\nDeleting node 3 (has one child)...\n";
    t.deleteNode(3);

    cout << "\nInorder after deletion:\n";
    t.inorderThreadedTraversal();

    return 0;
}

