//
//  Contact.h
//  addressDirectory
//
//  Created by Avinash Sai Sriramoju on 16/12/23.
//
//
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>

class Contact {
public:
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string phoneNumber;

    Contact(const std::string& firstName, const std::string& lastName,
            const std::string& address, const std::string& phoneNumber);

    std::string toString() const;

    friend std::istream& operator>>(std::istream& is, Contact& contact);
    friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
};

#endif // CONTACT_H
