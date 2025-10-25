#include "Reservation.h"
#include <sstream>

Reservation::Reservation() 
    : id(""), userId(""), username(""), roomId(0), roomName(""), 
      date(""), timeSlot(""), participants(0), status(""), notes("") {}

Reservation::Reservation(const std::string& id, const std::string& userId, 
                       const std::string& username, int roomId, const std::string& roomName,
                       const std::string& date, const std::string& timeSlot,
                       int participants, const std::string& status, const std::string& notes)
    : id(id), userId(userId), username(username), roomId(roomId), roomName(roomName),
      date(date), timeSlot(timeSlot), participants(participants), status(status), notes(notes) {}

// Getters
std::string Reservation::getId() const { return id; }
std::string Reservation::getUserId() const { return userId; }
std::string Reservation::getUsername() const { return username; }
int Reservation::getRoomId() const { return roomId; }
std::string Reservation::getRoomName() const { return roomName; }
std::string Reservation::getDate() const { return date; }
std::string Reservation::getTimeSlot() const { return timeSlot; }
int Reservation::getParticipants() const { return participants; }
std::string Reservation::getStatus() const { return status; }
std::string Reservation::getNotes() const { return notes; }

// Setters
void Reservation::setId(const std::string& id) { this->id = id; }
void Reservation::setUserId(const std::string& userId) { this->userId = userId; }
void Reservation::setUsername(const std::string& username) { this->username = username; }
void Reservation::setRoomId(int roomId) { this->roomId = roomId; }
void Reservation::setRoomName(const std::string& roomName) { this->roomName = roomName; }
void Reservation::setDate(const std::string& date) { this->date = date; }
void Reservation::setTimeSlot(const std::string& timeSlot) { this->timeSlot = timeSlot; }
void Reservation::setParticipants(int participants) { this->participants = participants; }
void Reservation::setStatus(const std::string& status) { this->status = status; }
void Reservation::setNotes(const std::string& notes) { this->notes = notes; }

std::string Reservation::toString() const {
    return id + "," + userId + "," + username + "," + std::to_string(roomId) + "," + 
           roomName + "," + date + "," + timeSlot + "," + std::to_string(participants) + "," + 
           status + "," + notes;
}

Reservation Reservation::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string id, userId, username, roomIdStr, roomName, date, timeSlot, participantsStr, status, notes;
    
    std::getline(ss, id, ',');
    std::getline(ss, userId, ',');
    std::getline(ss, username, ',');
    std::getline(ss, roomIdStr, ',');
    std::getline(ss, roomName, ',');
    std::getline(ss, date, ',');
    std::getline(ss, timeSlot, ',');
    std::getline(ss, participantsStr, ',');
    std::getline(ss, status, ',');
    std::getline(ss, notes, ',');
    
    int roomId = std::stoi(roomIdStr);
    int participants = std::stoi(participantsStr);
    
    return Reservation(id, userId, username, roomId, roomName, date, timeSlot, participants, status, notes);
}