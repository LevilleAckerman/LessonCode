#include "User.h"
#include <sstream>

User::User() : id(""), username(""), name(""), password(""), role("") {}

User::User(const std::string& id, const std::string& username, 
           const std::string& name, const std::string& password, 
           const std::string& role) 
    : id(id), username(username), name(name), password(password), role(role) {}

// Getters
std::string User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getName() const { return name; }
std::string User::getPassword() const { return password; }
std::string User::getRole() const { return role; }

// Setters
void User::setId(const std::string& id) { this->id = id; }
void User::setUsername(const std::string& username) { this->username = username; }
void User::setName(const std::string& name) { this->name = name; }
void User::setPassword(const std::string& password) { this->password = password; }
void User::setRole(const std::string& role) { this->role = role; }

std::string User::toString() const {
    return id + "," + username + "," + name + "," + password + "," + role;
}

User User::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string id, username, name, password, role;
    
    std::getline(ss, id, ',');
    std::getline(ss, username, ',');
    std::getline(ss, name, ',');
    std::getline(ss, password, ',');
    std::getline(ss, role, ',');
    
    return User(id, username, name, password, role);
}