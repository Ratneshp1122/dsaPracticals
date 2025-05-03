#include<iostream>
#include<string>
using namespace std;

struct Node {
    string data;
    Node* nextChapter;
    Node* firstSection;
    Node* firstSubSection;
};

class Book {
    Node* root;

public:
    Book(string name) {
        root = new Node;
        root->data = name;
        root->nextChapter = NULL;
        root->firstSection = NULL;
        root->firstSubSection = NULL;
    }

    void addChapter(string chap) {
        Node* newChapter = new Node;
        newChapter->data = chap;
        newChapter->nextChapter = NULL;
        newChapter->firstSection = NULL;
        newChapter->firstSubSection = NULL;

        if (!root->nextChapter) {
            root->nextChapter = newChapter;
        } else {
            Node* temp = root->nextChapter;
            while (temp->nextChapter)
                temp = temp->nextChapter;
            temp->nextChapter = newChapter;
        }
    }

    void addSection(string sec, string chap) {
        Node* temp = root->nextChapter;
        while (temp) {
            if (temp->data == chap)
                break;
            temp = temp->nextChapter;
        }

        if (!temp) return;

        Node* newSection = new Node;
        newSection->data = sec;
        newSection->nextChapter = NULL;
        newSection->firstSection = NULL;
        newSection->firstSubSection = NULL;

        if (!temp->firstSection)
            temp->firstSection = newSection;
        else {
            Node* ptr = temp->firstSection;
            while (ptr->nextChapter)
                ptr = ptr->nextChapter;
            ptr->nextChapter = newSection;
        }
    }

    void addSubSection(string subs, string sec, string chap) {
        Node* temp = root->nextChapter;
        while (temp) {
            if (temp->data == chap)
                break;
            temp = temp->nextChapter;
        }

        if (!temp) return;

        Node* section = temp->firstSection;
        while (section) {
            if (section->data == sec)
                break;
            section = section->nextChapter;
        }

        if (!section) return;

        Node* newSub = new Node;
        newSub->data = subs;
        newSub->nextChapter = NULL;
        newSub->firstSection = NULL;
        newSub->firstSubSection = NULL;

        if (!section->firstSubSection)
            section->firstSubSection = newSub;
        else {
            Node* ptr = section->firstSubSection;
            while (ptr->nextChapter)
                ptr = ptr->nextChapter;
            ptr->nextChapter = newSub;
        }
    }

    void display() {
        cout << "Book Title: " << root->data << endl;

        Node* chapter = root->nextChapter;
        while (chapter) {
            cout << "  Chapter: " << chapter->data << endl;

            Node* section = chapter->firstSection;
            while (section) {
                cout << "    Section: " << section->data << endl;

                Node* subsec = section->firstSubSection;
                while (subsec) {
                    cout << "      Subsection: " << subsec->data << endl;
                    subsec = subsec->nextChapter;
                }

                section = section->nextChapter;
            }

            chapter = chapter->nextChapter;
        }
    }
};

int main() {
    Book book("The Alchemist");
    book.addChapter("Chapter 1");
    book.addChapter("Chapter 2");
    book.addSection("Section 1", "Chapter 1");
    book.addSection("Section 2", "Chapter 2");
    book.addSubSection("Subsection 1", "Section 1", "Chapter 1");
    book.addSubSection("Subsection 2", "Section 2", "Chapter 2");
    book.display();
    return 0;
}
