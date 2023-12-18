//
//  AddressBook.cpp
//  addressDirectory
//
//  Created by Avinash Sai Sriramoju on 16/12/23.
//

#include "AddressBook.h"
#include <iostream>
#include <sstream>
#include <algorithm>

AddressBook::AddressBook(const std::string& filename) {
    storage.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!storage.is_open()) {
        storage.open(filename, std::ios::out | std::ios::binary);
    }

    storage.seekg(0, storage.end);
    nextOffset = storage.tellg();
    storage.seekg(0, storage.beg);
}

long AddressBook::writeContact(const Contact& contact) {
//    long offset = nextOffset;
//    storage.seekp(offset, storage.beg);
//
//    std::ostringstream oss;
//    oss << contact;
//
//    std::string data = oss.str();
//    int length = static_cast<int>(data.length());
//
//    storage.write(reinterpret_cast<const char*>(&length), sizeof(length));
//    storage.write(data.c_str(), length);
//
//    nextOffset = storage.tellp();
//
//    return offset;
    
    std::streampos offset = nextOffset;
    storage.seekp(offset);

    // Write the contact directly to the file in binary format
    storage.write(reinterpret_cast<const char*>(&contact), sizeof(contact));

    nextOffset = storage.tellp();

    return offset;
}

Contact AddressBook::readContact(long offset) {
//    storage.seekg(offset);
//    int length;
//    storage.read(reinterpret_cast<char*>(&length), sizeof(length));
//
//    char* data = new char[length + 1];
//    data[length] = '\0'; // Null-terminate the string
//    storage.read(data, length);
//
//    std::string dataString(data);
//
//    std::istringstream iss(dataString);
//    Contact contact("", "", "", "");
//    iss >> contact;
//
//    delete[] data;
//
//    return contact;
    
    storage.seekg(offset);

    // Read the contact directly from the file in binary format
    Contact contact("", "", "", "");
    storage.read(reinterpret_cast<char*>(&contact), sizeof(contact));

    return contact;
}

std::string AddressBook::toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void AddressBook::addContact(const Contact& contact) {
//    long offset = writeContact(contact);
//    phoneIndex[contact.phoneNumber] = offset;
//    nameIndex[contact.firstName + " " + contact.lastName] = offset;
    std::streampos offset = writeContact(contact);
    phoneIndex[contact.phoneNumber] = offset;
    nameIndex[contact.firstName + " " + contact.lastName] = offset;
}

Contact AddressBook::searchByPhoneNumber(const std::string& phoneNumber) {
    if (phoneIndex.find(phoneNumber) != phoneIndex.end()) {
        long offset = phoneIndex[phoneNumber];
        return readContact(offset);
    }
    return Contact("", "", "", "");
}

Contact AddressBook::searchByName(const std::string& name) {
    std::string lowercaseName = toLowerCase(name);
    if (nameIndex.find(lowercaseName) != nameIndex.end()) {
        long offset = nameIndex[lowercaseName];
        return readContact(offset);
    }
    return Contact("", "", "", "");
}

void AddressBook::close() {
    storage.close();
}
