#ifndef MEETINGROOM_H
#define MEETINGROOM_H

#include <string>

class MeetingRoom {
private:
    int id;
    std::string name;
    int capacity;
    bool needApproval;

public:
    MeetingRoom();
    MeetingRoom(int id, const std::string& name, int capacity, bool needApproval);
    
    // Getters
    int getId() const;
    std::string getName() const;
    int getCapacity() const;
    bool getNeedApproval() const;
    
    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setCapacity(int capacity);
    void setNeedApproval(bool needApproval);
    
    std::string toString() const;
    static MeetingRoom fromString(const std::string& data);
};

#endif