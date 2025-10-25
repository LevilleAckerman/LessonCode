#ifndef MENU_H
#define MENU_H

#include "User.h"
#include "MeetingRoom.h"
#include "Reservation.h"
#include <vector>

class Menu {
private:
    User currentUser;
    std::vector<User> users;
    std::vector<MeetingRoom> meetingRooms;
    std::vector<Reservation> reservations;
    
    void loadData();
    void saveData();
    void initializeDefaultData();
    
    // 通用功能
    bool authenticateUser(const std::string& role);
    void showMainMenu();
    
    // 研发人员功能
    void showResearcherMenu();
    void applyReservation();
    void viewMyReservations();
    void cancelReservation();
    
    // 行政人员功能
    void showAdminStaffMenu();
    void viewAllReservations();
    void approveReservation();
    
    // 系统管理员功能
    void showSystemAdminMenu();
    void addAccount();
    void viewAccounts();
    void viewMeetingRooms();
    void clearReservations();
    void deleteAccount();
    
    // 工具函数
    std::string generateReservationId();
    std::string getNextMonday();
    bool isRoomAvailable(int roomId, const std::string& date, const std::string& timeSlot);
    void displayAllRoomsStatus();

public:
    Menu();
    void run();
};

#endif