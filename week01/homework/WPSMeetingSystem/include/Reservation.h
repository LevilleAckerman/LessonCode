#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
private:
    std::string id;
    std::string userId;
    std::string username;
    int roomId;
    std::string roomName;
    std::string date; // 格式: YYYY-MM-DD
    std::string timeSlot; // "上午" or "下午"
    int participants;
    std::string status; // "待审批", "预约成功", "预约失败", "已取消"
    std::string notes;

public:
    Reservation();
    Reservation(const std::string& id, const std::string& userId, 
                const std::string& username, int roomId, const std::string& roomName,
                const std::string& date, const std::string& timeSlot,
                int participants, const std::string& status, const std::string& notes);
    
    // Getters
    std::string getId() const;
    std::string getUserId() const;
    std::string getUsername() const;
    int getRoomId() const;
    std::string getRoomName() const;
    std::string getDate() const;
    std::string getTimeSlot() const;
    int getParticipants() const;
    std::string getStatus() const;
    std::string getNotes() const;
    
    // Setters
    void setId(const std::string& id);
    void setUserId(const std::string& userId);
    void setUsername(const std::string& username);
    void setRoomId(int roomId);
    void setRoomName(const std::string& roomName);
    void setDate(const std::string& date);
    void setTimeSlot(const std::string& timeSlot);
    void setParticipants(int participants);
    void setStatus(const std::string& status);
    void setNotes(const std::string& notes);
    
    std::string toString() const;
    static Reservation fromString(const std::string& data);
};

#endif