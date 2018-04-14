#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class SortedLinkedList {
private:
    class Node {
    public:
        int data, priority;
        Node* next;
        Node(int d = 0, int p = 0, Node* n = NULL) {data = d;priority = p;next = n;}
    }*head;
    int total;
    Node* insertNode(int d, int p, Node* pos);
    void printNode(Node* pos);
    int count(Node* pos);

public:
    SortedLinkedList();
    void insert(int d, int p);
    void print();
    int size();
    int getTotal();
};

SortedLinkedList::Node* SortedLinkedList::insertNode(int d, int p, Node* pos) {
    if (!pos) {
        return new Node(d, p);
    } else if (p > pos->priority) {
        return new Node(d, p, pos);
    } else {
        pos->next = insertNode(d, p, pos->next);
        return pos;
    }
}

void SortedLinkedList::printNode(Node *pos) {
    if (pos) {cout << pos->data << "(" << pos->priority << ")->";
    printNode(pos->next);
    }
    else {return;}
}

int SortedLinkedList::count(Node* pos) {
    if(pos) {return count(pos->next) + 1;}
    else {return 0;}
}

SortedLinkedList::SortedLinkedList() {head = NULL;total = 0;}

void SortedLinkedList::insert(int d, int p) {head = insertNode(d, p, head);total += d;}

void SortedLinkedList::print() {printNode(head);}

int SortedLinkedList::size() {return count(head);}

int SortedLinkedList::getTotal() {return total;}

int main(int argc, char const* argv[]) {

    SortedLinkedList *lista = new SortedLinkedList();
    SortedLinkedList *listb = new SortedLinkedList();
    for (int i = 0; i < 20; i++) {
        int d = rand() % 10;
        int p = rand() % 100;
        if (lista->getTotal() >= listb->getTotal()) {
            listb->insert(d, p);
        } else{
            lista->insert(d, p);
        }
    }
    cout << lista->getTotal() << "(" << lista->size() << ")";
    lista->print();cout << endl;
    cout << listb->getTotal() << "(" << listb->size() << ")";
    listb->print();cout << endl;
}
