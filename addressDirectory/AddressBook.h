//
//  AddressBook.h
//  addressDirectory
//
//  Created by Avinash Sai Sriramoju on 16/12/23.
//

#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "Contact.h"
#include <unordered_map>
#include <fstream>

class AddressBook {
private:
    std::unordered_map<std::string, long> phoneIndex;
    std::unordered_map<std::string, long> nameIndex;
    std::fstream storage;
    long nextOffset;

    long writeContact(const Contact& contact);
    Contact readContact(long offset);

public:
    AddressBook(const std::string& filename);

    void addContact(const Contact& contact);
    Contact searchByPhoneNumber(const std::string& phoneNumber);
    Contact searchByName(const std::string& name);
    std::string toLowerCase(const std::string& str);
    void close();
};

#endif // ADDRESSBOOK_H
