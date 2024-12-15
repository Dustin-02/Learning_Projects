#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;    
};

Node* makeNode(int a) {
    Node* temp = new Node();
    temp->data = a;
    temp->next = nullptr;
    return temp;
}

bool isEmpty(Node* a){
    return a == nullptr;
}

int size(Node* a) {
    int count = 0;
    while (a != nullptr){
        count++;
        a = a->next;
    }
    return count;
}

void insertFirst(int x, Node* &a){
    Node* temp = makeNode(x);
    if (!a) a = temp;
    else {
        temp->next = a;
        a = temp;
    }    
} 
void deleteFirst(Node* &a){
    if (!a) return;
    a = a->next;
}

void insertLast(int x, Node* &a){
    Node* temp = makeNode(x);
    if (!a) a = temp;
    else {
        Node* b = a;
        while (b->next) {
            b = b->next;
        }
        b->next = temp;
    }
}
void deleteLast(Node* &a){
    if (!a) return;
    Node* end = a, *befEnd = nullptr;
    while(end->next){
        befEnd = end;
        end = end->next;
    }
    if (!befEnd) a = nullptr;
    else befEnd->next = nullptr;
}

void insertMiddle(int x, Node* &a, int pos){
    int n = size(a);
    if (pos <= 0 || pos > n + 1){
        cout << "Not valid!\n";
    }
    else if (pos == 1) insertFirst(x, a);
    else if (pos == n + 1) insertLast(x, a);
    else {
        int index = 1;
        Node* b = a;
        Node* temp = makeNode(x);        
        while (b && index != pos - 1) {
            index++;
            b = b->next;
        }
        temp->next = b->next;
        b->next = temp;
    }
}

void deleteMiddle(Node* &a, int pos){
    int n = size(a);
    if (pos <= 0 || pos > n + 1) return;
    Node* befPos = nullptr, *pos_node = a;
    for (int i = 1; i < pos; i++){
        befPos = pos_node;
        pos_node = pos_node->next;
    }
    if (!befPos) a = a->next;
    else {    
        befPos->next = pos_node->next;
    }
}

void printNode(Node* a){
    cout << "_____________________\n";
    while (a) {
        cout << a->data << "  ";
        a = a->next;
    }
}

void arrange(Node* a){    
    for (Node* p = a; p != nullptr; p = p->next){
        Node* minNode = p;
        for (Node* q = p->next; q != nullptr; q = q->next){
            if (q->data < minNode->data){
                min = q;
            }
        }
        int temp = minNode->data;
        minNode->data = p->data;
        p->data = temp;    
    }
}


int main(){
    /* Node* head = nullptr;
    string request;
    cout << "Enter your inquiries: 1. Insert F, L or M (with position), 2. Delete F, L or M (with position), 3. Print linked list\n";
    cin >> request;
    enum ReqList{MN, IF, IL, IM, DF, DL, DM, P};
    ReqList reqList1 = (ReqList) request;
    switch(reqList1){
        case(MN):
            int x;
            cout << "Please enter your data\n";
            cin >> x;
            Node* a = makeNode(x);
            cout << "New Node" << a->data;
            break;
        case(IF):
            int x;
            cout << "Input input value:\n";
            insertFirst(x, head);
            break;
        case(IM):
            int x, pos;
            cout << "Input value & position (1 -> N+1):\n";
            cin >> x >> pos;
            insertMiddle(x, head, pos);
            break;
        case(IL):
            int x;
            cout << "Input value at last:\n";
            cin >> x;
            insertLast(x, head);
            break;
        case(IL):
            int x;
            cout << "Input value at last:\n";
            cin >> x;
            insertLast(x, head);
            break;
    } */
    return 0;
}