// Include the necessary C++ standard input/output library.
#include <iostream>
// Include the C standard library header for memory allocation functions.
#include <cstdlib>
// Include the C++ standard library for file input/output operations.
#include <fstream>
// Include the C++ standard library for string handling.
#include <string>

// Using the standard namespace for C++.
using namespace std;

// Define a structure for a node in the linked list.
struct Node {
    int data;      // Data stored in the node.
    Node* next;    // Pointer to the next node in the list.
};

// Declare a global pointer to the head (first node) of the list.
Node* head = nullptr;
// Declare a global variable to store the size of the linked list.
int linkSize = 0;

// Function to add an element to the linked list.
void AddToList(int num) {
    // Check for duplicates before adding.
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == num) {
            cout << "Error: Duplicate entry not allowed!" << endl;
            return;
        }
        curr = curr->next;
    }

    // Create a new node and allocate memory for it using malloc.
    Node* newNode = (Node*)malloc(sizeof(Node));
    // Set the data of the new node.
    newNode->data = num;
    // Initialize the next pointer to nullptr.
    newNode->next = nullptr;

    // Check if the linked list is empty.
    if (head == nullptr) {
        // If the list is empty, the new node becomes the head.
        head = newNode;
    } else {
        // Traverse the list to find the last node.
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        // Insert the new node at the end of the list.
        curr->next = newNode;
    }
    // Update the size of the linked list.
    linkSize++;
}

// Function to delete the last customer from the list.
void DELETE() {
    // Check if the linked list is empty.
    if (head == nullptr) {
        return; // If the list is empty, nothing to delete.
    }

    // Check if there's only one node in the list.
    if (head->next == nullptr) {
        free(head); // Free the single node.
        head = nullptr;
        // Update the size of the linked list.
        linkSize--;
        return; // Early return to avoid accessing head->next.
    }

    // Traverse the list to find the last and second-to-last nodes.
    Node* curr = head;
    Node* per = nullptr;

    while (curr->next != nullptr) {
        per = curr;
        curr = curr->next;
    }

    // Free the last node.
    free(curr);

    // Check if the second-to-last node exists.
    if (per != nullptr) {
        // Set the next pointer of the new last node to nullptr.
        per->next = nullptr;
    } else {
        head = nullptr; // If there's no previous node, set head to nullptr.
    }

    // Update the size of the linked list.
    linkSize--;
}

// Function to get the middle number(s) without traversing the whole list.
void GetTrump() {
    // Check if the linked list is empty.
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* curr = head;
    Node* per = head;
    Node* prev = nullptr;

    // Use two pointers to find the middle element(s).
    while (curr != nullptr && curr->next != nullptr) {
        curr = curr->next->next;
        prev = per;
        per = per->next;
    }

    // Determine and print the middle number(s).
    if (prev == nullptr) {
        // Only one element in the list.
        cout << per->data << endl;
    } else if (curr == nullptr) {
        // Even number of elements, print two middle numbers.
        cout << prev->data << " " << per->data << endl;
    } else {
        // Odd number of elements, print the middle number.
        cout << per->data << endl;
    }
}

// Function to print the linked list.
void PrintLink() {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " -> ";
        } else {
            cout << " -> null";
        }
        curr = curr->next;
    }
    cout << endl;
}

// The main function where program execution begins.
int main() {
    string filePath; // String to store the file path
    ifstream inputFile;

    // Prompt the user to enter the filepath.
    cout << "Enter the filepath: ";
    // Read the file path from the user.
    getline(cin, filePath);

    // Open the input file.
    inputFile.open(filePath.c_str());
    // Check if the file is successfully opened.
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open input file!" << endl;
        return 1; // Return 1 to indicate an error.
    }

    string command;
    int num;

    // Start of input processing loop.
    while (inputFile >> command) {
    // Check the value of the 'command' variable to determine the action.
    if (command == "ADD") {
        inputFile >> num;  // Read an integer from the input file.
        AddToList(num);    // Call the 'AddToList' function to add the number to the linked list.
    } else if (command == "DELETE") {
        DELETE();          // Call the 'DELETE' function to delete the last element from the linked list.
    } else if (command == "TRUMP") {
        GetTrump();        // Call the 'GetTrump' function to get and print the middle number(s).
    } else if (command == "END") {
        break;             // Exit the loop when the "END" command is encountered.
    }
}

    // End of input processing loop.

    // Close the input file.
    inputFile.close();

    // Print the linked list.
    PrintLink();

    // Return 0 to indicate successful execution.
    return 0;
}
