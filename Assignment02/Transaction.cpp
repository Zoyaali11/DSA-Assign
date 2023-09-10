#include <iostream>
#include <fstream>
#include <cstdlib> // Include the C standard library for malloc and free functions
using namespace std;

struct Trans { // Define a struct to represent a transaction
    int id;         // Integer field for transaction ID
    int amount;     // Integer field for transaction amount
    Trans* next; // Pointer to the next transaction in the linked list
};

// Function to delete a transaction with a specific ID
void remove(Trans*& head, int id) {
    Trans* prev = nullptr; // Initialize a pointer to the previous transaction
    Trans* current = head; // Initialize a pointer to the current transaction

    while (current != nullptr) { // Loop through the linked list until the end is reached
        if (current->id == id) { // Check if the current transaction has the specified ID
            if (prev != nullptr) { // If there is a previous transaction
                prev->next = current->next; // Update the previous transaction's next pointer
                free(current); // Free memory for the current transaction
                current = prev->next; // Move to the next transaction
            } else { // If the current transaction is the head of the linked list
                Trans* temp = current; // Create a temporary pointer to the current transaction
                current = current->next; // Move to the next transaction
                free(temp); // Free memory for the current transaction
                head = current; // Update the head pointer
            }
        } else { // If the current transaction is not the one to remove
            prev = current; // Update the previous pointer
            current = current->next; // Move to the next transaction
        }
    }
}

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

    int numofTrans, numofFradTrans;
    inputFile >> numofTrans >> numofFradTrans; // Read input for the number of transactions

    Trans* head = nullptr; // Initialize a pointer to the head of the linked list
    Trans* tail = nullptr; // Initialize a pointer to the tail of the linked list

    // Read and store transactions
    for (int i = 0; i < numofTrans; ++i) {
        int id, amount;
        char comma;
        inputFile >> id >> comma >> amount; // Read input for transaction ID and amount

        Trans* newNode = (Trans*)malloc(sizeof(Trans)); // Allocate memory for a new transaction
        newNode->id = id; // Assign the ID to the new transaction
        newNode->amount = amount; // Assign the amount to the new transaction
        newNode->next = nullptr; // Initialize the next pointer of the new transaction as nullptr

        if (!head) { // If the linked list is empty
            head = newNode; // Set the head to the new transaction
            tail = newNode; // Set the tail to the new transaction
        } else { // If the linked list is not empty
            tail->next = newNode; // Set the next pointer of the tail to the new transaction
            tail = newNode; // Update the tail to the new transaction
        }
    }

    // Read and store fraudulent transaction IDs
    int* fraudIds = (int*)malloc(sizeof(int) * numofFradTrans); // Allocate memory for an array of fraudulent IDs
    for (int i = 0; i < numofFradTrans; ++i) {
        inputFile >> fraudIds[i]; // Read and store fraudulent transaction IDs
    }

    // Remove fraudulent transactions using delete()
    for (int i = 0; i < numofFradTrans; ++i) {
        remove(head, fraudIds[i]); // Call the remove function to delete fraudulent transactions
    }

    // Print the remaining transactions
    Trans* current = head; // Initialize a pointer to the current transaction
    while (current != nullptr) { // Loop through the linked list of remaining transactions
        cout << current->id << "," << current->amount << endl; // Print the ID and amount of the current transaction
        current = current->next; // Move to the next transaction
    }

    // Clean up memory by freeing allocated memory
    while (head != nullptr) { // Loop through the linked list
        Trans* temp = head; // Create a temporary pointer to the head
        head = head->next; // Move the head to the next transaction
        free(temp); // Free memory for the current transaction
    }

    free(fraudIds); // Free memory for the array of fraudulent IDs

    // Close the input file since you've finished reading from it
    inputFile.close();

    return 0; // Return 0 to indicate successful execution
}
