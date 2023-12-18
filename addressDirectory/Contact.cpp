//
//  Contact.cpp
//  addressDirectory
//
//  Created by Avinash Sai Sriramoju on 16/12/23.
//

#include "Contact.h"
#include <sstream>

Contact::Contact(const std::string& firstName, const std::string& lastName,
                 const std::string& address, const std::string& phoneNumber)
    : firstName(firstName), lastName(lastName), address(address), phoneNumber(phoneNumber) {}

std::string Contact::toString() const {
    std::string s = std::string("Contact{") +
        "firstName='" + firstName + '\'' +
        ", lastName='" + lastName + '\'' +
        ", address='" + address + '\'' +
        ", phoneNumber='" + phoneNumber + '\'' +
        '}';
    return s;
}

std::istream& operator>>(std::istream& is, Contact& contact) {
    std::getline(is >> std::ws, contact.firstName, ',');
    std::getline(is >> std::ws, contact.lastName, ',');
    std::getline(is >> std::ws, contact.address, ',');
    std::getline(is >> std::ws, contact.phoneNumber);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Contact& contact) {
    os << contact.firstName << "," << contact.lastName << "," << contact.address << "," << contact.phoneNumber;
    return os;
}
