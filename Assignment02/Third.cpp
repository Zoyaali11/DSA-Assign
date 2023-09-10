#include <iostream>    // Include the necessary header for input and output
#include <fstream>     // Include the header for file input/output
#include <cstdlib>     // Include the header for functions like malloc

using namespace std;   // Use the standard namespace

// Define the structure for a linked list node
struct Node {
    int data;          // Integer data stored in the node
    Node* next;        // Pointer to the next node in the linked list
};

// Function to find the third last element of a linked list
int thirdlast(Node* head) {
    if (head == nullptr) {
        // If the linked list is empty, return -1
        return -1;
    }

    Node* first = head;
    Node* second = head;
    Node* third = head;

    // Advance the first pointer by three positions
    for (int i = 0; i < 3; i++) {
        if (first->next != nullptr) {
            first = first->next;
        } else {
            // If the list is not long enough, return -1
            return -1;
        }
    }

    // Move all pointers together until the first pointer reaches the end
    while (first->next != nullptr) {
        first = first->next;
        second = second->next;
        third = third->next;
    }

    // The third pointer now points to the third last element
    return third->data;
}

int main() {
    // Create a linked list with sample data
    Node* head = nullptr;  // Initialize the head of the linked list to nullptr
    int num;              // Variable to store integer input from the file

    // Open the input file
    string filePath;       // Variable to store the file path
    ifstream inputFile;   // Create an input file stream object

    cout << "Enter the filepath: ";
    getline(cin, filePath);  // Read the file path from the user

    inputFile.open(filePath.c_str());  // Attempt to open the specified file

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open input file!" << endl;
        return 1;  // Return 1 to indicate an error
    }

    cout << "File content:" << endl;

    // Read integers from the file and build the linked list
    while (inputFile >> num) {
        if (num <= 0) {
            cout << "Error: All numbers must be greater than 0." << endl;
            return 1;  // Exit the program with an error code
        }

        cout << num << " ";  // Print the read integer

        Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for a new node
        newNode->data = num;  // Set the data of the new node to the read integer
        newNode->next = head;  // Point the new node's next to the current head of the list
        head = newNode;  // Update the head to the new node, effectively adding it to the list
    }

    inputFile.close();  // Close the input file stream

    cout << endl;  // Print a newline to separate the file content from the result

    // Find the third last element
    int result = thirdlast(head);

    if (result != -1) {
        cout << "The third last element is: " << result << endl;  // Print the third last element
    } else {
        cout << "The linked list has less than three elements." << endl;  // Print -1 if the linked list has less than three elements
    }

    // Free memory (cleanup)
    while (head != nullptr) {
        Node* temp = head;  // Create a temporary pointer to the current head
        head = head->next;  // Move the head to the next node
        free(temp);  // Free the memory of the previous head
    }

    return 0;  // Return 0 to indicate successful execution
}
