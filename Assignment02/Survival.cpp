#include <iostream> // Include the standard input/output stream library.
#include <fstream>  // Include the file stream library for file operations.
using namespace std; // Use the standard namespace to simplify code.

// Node structure for the linked list
struct Node {
    int data;      // Data stored in the node.
    Node* next;    // Pointer to the next node in the linked list.
};

// Function to insert a new element into the linked list
void insert(Node*& head, int data) {
    // Create a new node and allocate memory for it
    Node* newNode = (Node*)malloc(sizeof(Node));
    // Set the data of the new node
    newNode->data = data;
    // Initialize the next pointer of the new node to nullptr
    newNode->next = nullptr;

    // Check if the linked list is empty or if the new data is smaller or equal to the head's data
    if (head == nullptr || data <= head->data) {
        // Update the new node's next pointer to point to the current head
        newNode->next = head;
        // Update the head to point to the new node
        head = newNode;
    }
    else {
        // Initialize a current pointer to traverse the list
        Node* current = head;
        // Traverse the list to find the correct position to insert the new node
        while (current->next != nullptr && current->next->data < data) {
            current = current->next;
        }
        // Update the new node's next pointer to point to the next node
        newNode->next = current->next;
        // Update the current node's next pointer to point to the new node
        current->next = newNode;
    }
}

// Function to calculate the median of the linked list
double calculateMedian(Node* head, int count) {
    // Initialize two pointers, curr (current) and pre (previous), to traverse the list
    Node* curr = head;
    Node* pre = nullptr;

    // Move curr pointer to the middle and pre pointer to the previous node of the middle
    while (curr != nullptr && curr->next != nullptr) {
        curr = curr->next->next;
        pre = pre ? pre->next : head;
    }

    // Check if the count of elements in the list is even
    if (count % 2 == 0) {
        // Calculate and return the average of the middle two elements
        return (pre->data + curr->data) / 2;
    } else {
        // Return the data of the middle element
        return curr->data;
    }
}

int main() {
    // Initialize the head of the linked list to nullptr
    Node* head = nullptr;
    // Initialize a counter for the number of elements in the list
    int count = 0;
    int num;
    string filePath;

    // Prompt the user to enter the filepath
    cout << "Enter the filepath: ";
    // Read the file path from the user
    getline(cin, filePath);

    // Open the input file
    ifstream inputFile(filePath.c_str());
    // Check if the file is successfully opened
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open input file!" << endl;
        return 1; // Return 1 to indicate an error
    }

    // Read numbers from the file and insert them into the linked list
    while (inputFile >> num) {
        // Check if the input number is within the valid range
        if (num < 0 || num > 100) {
            cout << "Invalid Numbers between 0 and 100." << endl;
            break;
        }

        // Insert the number into the linked list
        insert(head, num);
        // Increment the count of elements in the list
        count++;
        // Calculate the median and display it
        double median = calculateMedian(head, count);
        cout << num << " Median : " << median << endl;
    }

    // Close the input file
    inputFile.close();

    return 0;
}
