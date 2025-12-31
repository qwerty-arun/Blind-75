#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(NULL) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(NULL) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    // Create a cycle for testing
    void createCycle(int pos) {
        if (!head) return;
        Node* temp = head;
        Node* cycleNode = NULL;
        int count = 1;
        while (temp->next) {
            if (count == pos) cycleNode = temp;
            temp = temp->next;
            count++;
        }
        if (cycleNode) temp->next = cycleNode;
    }

    bool detectCycle() {
        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next) {
            slow = slow->next;          // move 1 step
            fast = fast->next->next;    // move 2 steps

            if (slow == fast) {
                cout << "Cycle detected!" << endl;
                return true;
            }
        }
        cout << "No cycle found." << endl;
        return false;
    }
};

int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);
    list.insert(50);

    // Uncomment to create cycle
    list.createCycle(2); // creates a cycle at node with value 20

    if (list.detectCycle())
        cout << "Loop exists in Linked List." << endl;
    else
        cout << "No loop in Linked List." << endl;

    return 0;
}