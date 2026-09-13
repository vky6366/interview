#include <iostream>
#include <stdexcept>

// Template class for a reusable Linked List
template <typename T>
class LinkedList {
private:
    // Nested private Node structure to protect internal layout
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head; // Pointer to the first node
    Node* tail; // Pointer to the last node for O(1) appending

public:
    // 1. Constructor
    LinkedList() : head(nullptr), tail(nullptr) {}

    // 2. Destructor (Prevents memory leaks)
    ~LinkedList() {
        clear();
    }

    // 3. Insert at the front (Head) - O(1)
    void insertFront(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head; // If list was empty, head is also tail
        }
    }

    // 4. Insert at the back (Tail) - O(1)
    void insertBack(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    // 5. Delete from the front - O(1)
    void deleteFront() {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr; // If list became empty
        }
    }

    // 6. Clear entire list - O(N)
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    // 7. Display the list contents - O(N)
    void display() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    void reverse(){
        Node* next = nullptr;
        Node* curr = head;
        Node* prev = nullptr;
        while(curr!=nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
    void mergelist(LinkedList<T>& head1, LinkedList<T>& head2){
        if(head1.data == NULL || head2.data == NULL){
            return head1.data = NULL ? head2 : head1;;
        }

        if(head1.data < head2.data){
            head1->next = mergelist(head1->next, head2);
            return head1;
        }
        else{
            head2->next = mergelist(head1, head2->next);
            return head2;
        }
    }
};

// Example usage
int main() {
    LinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertFront(5);
    
    std::cout << "Current List: ";
    list.display(); // Expected: 5 -> 10 -> 20 -> nullptr

    list.deleteFront();
    std::cout << "After Deleting Front: ";
    list.display(); // Expected: 10 -> 20 -> nullptr

    return 0;
}
