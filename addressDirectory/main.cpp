//
//  main.cpp
//  addressDirectory
//
//  Created by Avinash Sai Sriramoju on 16/12/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
#include <limits>
#include "AddressBook.h"


int getChoice() {
    std::string input;
    int choice;

    while (true) {
        std::cout << "Choose an option: ";
        std::getline(std::cin, input);

        // Validate if the input is an integer
        if (std::all_of(input.begin(), input.end(), ::isdigit)) {
            choice = std::stoi(input);
            break;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
        }
    }

    return choice;
}

int main() {
    try {
        AddressBook addressBook("address_book.dat");

        // Mock data
        addressBook.addContact(Contact("Avinash", "test", "HSR Layout", "9676806379"));
        addressBook.addContact(Contact("first", "last", "test address ", "1234567890"));

        // CLI
        while (true) {
            std::cout << "\n1. Add Contact\n"
                      << "2. Search by Phone Number\n"
                      << "3. Search by Name\n"
                      << "4. Exit\n";

            int choice = getChoice();

            switch (choice) {
                case 1: {
                    std::string firstName, lastName, address, phoneNumber;
                    std::cout << "Enter First Name: ";
                    std::getline(std::cin, firstName);

                    std::cout << "Enter Last Name: ";
                    std::getline(std::cin, lastName);

                    std::cout << "Enter Address: ";
                    std::getline(std::cin, address);

                    std::cout << "Enter Phone Number: ";
                    std::getline(std::cin, phoneNumber);

                    addressBook.addContact(Contact(firstName, lastName, address, phoneNumber));
                    std::cout << "Contact added successfully!\n";
                    break;
                }

                case 2: {
                    std::string searchPhoneNumber;
                    std::cout << "Enter Phone Number to Search: ";
                    std::getline(std::cin, searchPhoneNumber);

                    long startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                    Contact resultByPhoneNumber = addressBook.searchByPhoneNumber(searchPhoneNumber);
                    long endTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

                    if (resultByPhoneNumber.firstName != "") {
                        std::cout << "Search Result: " << resultByPhoneNumber << "\n";
                    } else {
                        std::cout << "Contact not found.\n";
                    }

                    std::cout << "Search time: " << (endTime - startTime) / 1e6 << " milliseconds\n";
                    break;
                }

                case 3: {
                    std::string searchName;
                    std::cout << "Enter Name to Search: ";
                    std::getline(std::cin, searchName);

                    long nameStartTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                    Contact resultByName = addressBook.searchByName(searchName);
                    long nameEndTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

                    if (resultByName.firstName != "") {
                        std::cout << "Search Result: " << resultByName << "\n";
                    } else {
                        std::cout << "Contact not found.\n";
                    }

                    std::cout << "Search time: " << (nameEndTime - nameStartTime) / 1e6 << " milliseconds\n";
                    break;
                }

                case 4:
                    addressBook.close();
                    std::cout << "Exiting Address Book. Goodbye!\n";
                    std::exit(0);
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
