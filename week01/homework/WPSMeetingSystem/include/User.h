#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string id;
    std::string username;
    std::string name;
    std::string password;
    std::string role; // "研发人员", "行政人员", "管理员"

public:
    User();
    User(const std::string& id, const std::string& username, 
         const std::string& name, const std::string& password, 
         const std::string& role);
    
    // Getters
    std::string getId() const;
    std::string getUsername() const;
    std::string getName() const;
    std::string getPassword() const;
    std::string getRole() const;
    
    // Setters
    void setId(const std::string& id);
    void setUsername(const std::string& username);
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    void setRole(const std::string& role);
    
    std::string toString() const;
    static User fromString(const std::string& data);
};

#endif