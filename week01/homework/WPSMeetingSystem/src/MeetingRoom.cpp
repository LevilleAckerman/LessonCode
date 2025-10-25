#include "MeetingRoom.h"
#include <sstream>

MeetingRoom::MeetingRoom() : id(0), name(""), capacity(0), needApproval(false) {}

MeetingRoom::MeetingRoom(int id, const std::string& name, int capacity, bool needApproval)
    : id(id), name(name), capacity(capacity), needApproval(needApproval) {}

// Getters
int MeetingRoom::getId() const { return id; }
std::string MeetingRoom::getName() const { return name; }
int MeetingRoom::getCapacity() const { return capacity; }
bool MeetingRoom::getNeedApproval() const { return needApproval; }

// Setters
void MeetingRoom::setId(int id) { this->id = id; }
void MeetingRoom::setName(const std::string& name) { this->name = name; }
void MeetingRoom::setCapacity(int capacity) { this->capacity = capacity; }
void MeetingRoom::setNeedApproval(bool needApproval) { this->needApproval = needApproval; }

std::string MeetingRoom::toString() const {
    return std::to_string(id) + "," + name + "," + std::to_string(capacity) + "," + 
           (needApproval ? "true" : "false");
}

MeetingRoom MeetingRoom::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string idStr, name, capacityStr, approvalStr;
    
    std::getline(ss, idStr, ',');
    std::getline(ss, name, ',');
    std::getline(ss, capacityStr, ',');
    std::getline(ss, approvalStr, ',');
    
    int id = std::stoi(idStr);
    int capacity = std::stoi(capacityStr);
    bool needApproval = (approvalStr == "true");
    
    return MeetingRoom(id, name, capacity, needApproval);
}