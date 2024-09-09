# Bank Management System

This project is a simple **Bank Management System** built in C++ as part of the "Algorithms and Problem Solving Level 3" course from [ProgrammingAdvices.com](https://programmingadvices.com). The system manages bank clients' information such as account numbers, pin codes, names, phone numbers, and account balances.

## Features

- **Show Client List**: Displays a list of all clients in the system.
- **Add New Client**: Allows you to add a new bank client by providing account number, pin code, name, phone, and initial balance.
- **Delete Client**: Deletes a client’s account from the system.
- **Update Client Information**: Allows updating the client’s account information.
- **Find Client**: Searches for a client by account number and displays their details.

## How It Works

1. **Data Storage**: Client information is stored in a text file (`clients.txt`). Each client's data is saved in a specific format.
2. **File Operations**: The program reads and writes data to the `clients.txt` file, keeping track of client information persistently.
3. **Data Validation**: When adding a new client, the program checks if the account number already exists to prevent duplicates.
4. **Mark for Deletion**: Clients marked for deletion will be excluded when saving data back to the file.

## Project Structure

- **Main Menu**: The main interface where users can select options to interact with the system.
- **File Handling**: Functions to load client data from the file, save new clients, update information, and handle deletions.
- **Client Management**: Functions to add, update, delete, and find clients.

## How to Run

1. Compile the C++ code using any compiler that supports C++11 or higher.
2. The `clients.txt` file must be in the same directory as the executable to store and retrieve client data.

## Sample Commands

- To add a new client, the system will prompt you to input:
  - Account Number
  - Pin Code
  - Name
  - Phone
  - Balance

- You can also update or delete client information by entering the respective client’s account number.

## Credits

This project was developed as part of a course provided by [ProgrammingAdvices.com](https://programmingadvices.com).
