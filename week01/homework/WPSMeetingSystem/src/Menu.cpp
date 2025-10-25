#include "Menu.h"
#include "FileUtil.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>

Menu::Menu() {
    loadData();
}

void Menu::loadData() {
    // 创建数据目录
    FileUtil::createDirectory("data");
    
    // 加载用户数据
    if (FileUtil::fileExists("data/users.txt")) {
        auto userLines = FileUtil::readLines("data/users.txt");
        for (const auto& line : userLines) {
            users.push_back(User::fromString(line));
        }
    } else {
        initializeDefaultData();
    }
    
    // 加载会议室数据
    if (FileUtil::fileExists("data/meeting_rooms.txt")) {
        auto roomLines = FileUtil::readLines("data/meeting_rooms.txt");
        for (const auto& line : roomLines) {
            meetingRooms.push_back(MeetingRoom::fromString(line));
        }
    } else {
        // 初始化默认会议室
        meetingRooms = {
            MeetingRoom(1, "紫阳湖会议室", 14, true),
            MeetingRoom(2, "后官湖会议室", 8, false),
            MeetingRoom(3, "清潭湖会议室", 10, false),
            MeetingRoom(4, "黄家湖会议室", 6, false),
            MeetingRoom(5, "杨春湖会议室", 18, true),
            MeetingRoom(6, "中山湖会议室", 150, true)
        };
        std::vector<std::string> roomLines;
        for (const auto& room : meetingRooms) {
            roomLines.push_back(room.toString());
        }
        FileUtil::writeLines("data/meeting_rooms.txt", roomLines);
    }
    
    // 加载预约数据
    if (FileUtil::fileExists("data/reservations.txt")) {
        auto reservationLines = FileUtil::readLines("data/reservations.txt");
        for (const auto& line : reservationLines) {
            reservations.push_back(Reservation::fromString(line));
        }
    }
}

void Menu::saveData() {
    // 保存用户数据
    std::vector<std::string> userLines;
    for (const auto& user : users) {
        userLines.push_back(user.toString());
    }
    FileUtil::writeLines("data/users.txt", userLines);
    
    // 保存预约数据
    std::vector<std::string> reservationLines;
    for (const auto& reservation : reservations) {
        reservationLines.push_back(reservation.toString());
    }
    FileUtil::writeLines("data/reservations.txt", reservationLines);
}

void Menu::initializeDefaultData() {
    // 添加默认管理员账户
    users.push_back(User("admin001", "admin", "系统管理员", "admin123", "管理员"));
    
    // 添加默认研发人员账户
    users.push_back(User("dev001", "zhangsan", "张三", "dev123", "研发人员"));
    users.push_back(User("dev002", "lisi", "李四", "dev123", "研发人员"));
    
    // 添加默认行政人员账户
    users.push_back(User("adminstaff001", "wangwu", "王五", "admin123", "行政人员"));
    
    saveData();
}

bool Menu::authenticateUser(const std::string& role) {
    std::string username, password;
    
    std::cout << "\n=== " << role << "登录 ===" << std::endl;
    std::cout << "用户名: ";
    std::cin >> username;
    std::cout << "密码: ";
    std::cin >> password;
    
    for (const auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == password && user.getRole() == role) {
            currentUser = user;
            std::cout << "登录成功！欢迎 " << user.getName() << std::endl;
            return true;
        }
    }
    
    std::cout << "登录失败！用户名或密码错误，或身份不匹配。" << std::endl;
    return false;
}

void Menu::run() {
    while (true) {
        showMainMenu();
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: // 研发人员
                if (authenticateUser("研发人员")) {
                    showResearcherMenu();
                }
                break;
            case 2: // 行政人员
                if (authenticateUser("行政人员")) {
                    showAdminStaffMenu();
                }
                break;
            case 3: // 系统管理员
                if (authenticateUser("管理员")) {
                    showSystemAdminMenu();
                }
                break;
            case 4: // 退出
                std::cout << "感谢使用金山办公会议室预约系统！" << std::endl;
                return;
            default:
                std::cout << "无效选择，请重新输入！" << std::endl;
        }
    }
}

void Menu::showMainMenu() {
    std::cout << "\n=== 金山办公会议室预约系统 ===" << std::endl;
    std::cout << "1. 研发人员" << std::endl;
    std::cout << "2. 行政人员" << std::endl;
    std::cout << "3. 系统管理员" << std::endl;
    std::cout << "4. 退出" << std::endl;
    std::cout << "请选择您的身份: ";
}

// showResearcherMenu(), applyReservation(), viewMyReservations(), cancelReservation()
// showAdminStaffMenu(), viewAllReservations(), approveReservation()
// showSystemAdminMenu(), addAccount(), viewAccounts(), viewMeetingRooms(), clearReservations(), deleteAccount()
// 以及相关的工具函数

std::string Menu::generateReservationId() {
    static int counter = 1;
    return "RES" + std::to_string(counter++);
}

void Menu::displayAllRoomsStatus() {
    std::cout << "\n=== 所有会议室状态 ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "会议室名称" 
              << std::setw(10) << "容量" 
              << std::setw(15) << "是否需要审批" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    for (const auto& room : meetingRooms) {
        std::cout << std::left << std::setw(5) << room.getId()
                  << std::setw(20) << room.getName()
                  << std::setw(10) << room.getCapacity()
                  << std::setw(15) << (room.getNeedApproval() ? "是" : "否") << std::endl;
    }
}

// 在 Menu.cpp 文件末尾添加以下代码

void Menu::showResearcherMenu() {
    while (true) {
        std::cout << "\n=== 研发人员菜单 ===" << std::endl;
        std::cout << "1. 申请预约会议室" << std::endl;
        std::cout << "2. 查看我的预约" << std::endl;
        std::cout << "3. 取消预约" << std::endl;
        std::cout << "4. 退出登录" << std::endl;
        std::cout << "请选择操作: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                applyReservation();
                break;
            case 2:
                viewMyReservations();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                std::cout << "退出登录成功！" << std::endl;
                return;
            default:
                std::cout << "无效选择，请重新输入！" << std::endl;
        }
    }
}

void Menu::showAdminStaffMenu() {
    while (true) {
        std::cout << "\n=== 行政人员菜单 ===" << std::endl;
        std::cout << "1. 查看所有会议室预约信息" << std::endl;
        std::cout << "2. 审批预约" << std::endl;
        std::cout << "3. 退出登录" << std::endl;
        std::cout << "请选择操作: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                viewAllReservations();
                break;
            case 2:
                approveReservation();
                break;
            case 3:
                std::cout << "退出登录成功！" << std::endl;
                return;
            default:
                std::cout << "无效选择，请重新输入！" << std::endl;
        }
    }
}

void Menu::showSystemAdminMenu() {
    while (true) {
        std::cout << "\n=== 系统管理员菜单 ===" << std::endl;
        std::cout << "1. 添加账户" << std::endl;
        std::cout << "2. 查看账户" << std::endl;
        std::cout << "3. 查看会议室信息" << std::endl;
        std::cout << "4. 清空预约" << std::endl;
        std::cout << "5. 删除账户" << std::endl;
        std::cout << "6. 退出登录" << std::endl;
        std::cout << "请选择操作: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                viewAccounts();
                break;
            case 3:
                viewMeetingRooms();
                break;
            case 4:
                clearReservations();
                break;
            case 5:
                deleteAccount();
                break;
            case 6:
                std::cout << "退出登录成功！" << std::endl;
                return;
            default:
                std::cout << "无效选择，请重新输入！" << std::endl;
        }
    }
}

// 实现其他必要的函数
void Menu::applyReservation() {
    std::cout << "\n=== 申请预约会议室 ===" << std::endl;
    displayAllRoomsStatus();
    
    // 这里需要实现具体的预约逻辑
    std::cout << "预约功能开发中..." << std::endl;
}

void Menu::viewMyReservations() {
    std::cout << "\n=== 我的预约信息 ===" << std::endl;
    
    bool found = false;
    for (const auto& reservation : reservations) {
        if (reservation.getUserId() == currentUser.getId()) {
            std::cout << "预约ID: " << reservation.getId() 
                      << ", 会议室: " << reservation.getRoomName()
                      << ", 日期: " << reservation.getDate()
                      << ", 时间段: " << reservation.getTimeSlot()
                      << ", 状态: " << reservation.getStatus() << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "您还没有任何预约记录。" << std::endl;
    }
}

void Menu::cancelReservation() {
    std::cout << "\n=== 取消预约 ===" << std::endl;
    viewMyReservations();
    
    std::string reservationId;
    std::cout << "请输入要取消的预约ID: ";
    std::cin >> reservationId;
    
    for (auto& reservation : reservations) {
        if (reservation.getId() == reservationId && reservation.getUserId() == currentUser.getId()) {
            reservation.setStatus("已取消");
            saveData();
            std::cout << "取消预约成功！" << std::endl;
            return;
        }
    }
    
    std::cout << "未找到该预约记录或您没有权限取消此预约。" << std::endl;
}

void Menu::viewAllReservations() {
    std::cout << "\n=== 所有预约信息 ===" << std::endl;
    
    if (reservations.empty()) {
        std::cout << "暂无预约记录。" << std::endl;
        return;
    }
    
    for (const auto& reservation : reservations) {
        std::cout << "预约ID: " << reservation.getId() 
                  << ", 用户: " << reservation.getUsername()
                  << ", 会议室: " << reservation.getRoomName()
                  << ", 日期: " << reservation.getDate()
                  << ", 时间段: " << reservation.getTimeSlot()
                  << ", 状态: " << reservation.getStatus() << std::endl;
    }
}

void Menu::approveReservation() {
    std::cout << "\n=== 审批预约 ===" << std::endl;
    
    // 显示待审批的预约
    bool foundPending = false;
    for (const auto& reservation : reservations) {
        if (reservation.getStatus() == "待审批") {
            std::cout << "预约ID: " << reservation.getId() 
                      << ", 用户: " << reservation.getUsername()
                      << ", 会议室: " << reservation.getRoomName()
                      << ", 日期: " << reservation.getDate()
                      << ", 时间段: " << reservation.getTimeSlot() << std::endl;
            foundPending = true;
        }
    }
    
    if (!foundPending) {
        std::cout << "暂无待审批的预约。" << std::endl;
        return;
    }
    
    std::string reservationId;
    std::cout << "请输入要审批的预约ID: ";
    std::cin >> reservationId;
    
    std::string decision;
    std::cout << "请输入审批结果(通过/不通过): ";
    std::cin >> decision;
    
    for (auto& reservation : reservations) {
        if (reservation.getId() == reservationId && reservation.getStatus() == "待审批") {
            if (decision == "通过") {
                reservation.setStatus("预约成功");
                std::cout << "审批通过！" << std::endl;
            } else {
                reservation.setStatus("预约失败");
                std::cout << "审批不通过！" << std::endl;
            }
            saveData();
            return;
        }
    }
    
    std::cout << "未找到该预约记录或该预约无需审批。" << std::endl;
}

void Menu::addAccount() {
    std::cout << "\n=== 添加账户 ===" << std::endl;
    
    std::string id, username, name, password, role;
    std::cout << "请输入工号: ";
    std::cin >> id;
    std::cout << "请输入用户名: ";
    std::cin >> username;
    std::cout << "请输入姓名: ";
    std::cin >> name;
    std::cout << "请输入密码: ";
    std::cin >> password;
    
    std::cout << "请选择角色 (1-研发人员, 2-行政人员): ";
    int roleChoice;
    std::cin >> roleChoice;
    
    if (roleChoice == 1) {
        role = "研发人员";
    } else if (roleChoice == 2) {
        role = "行政人员";
    } else {
        std::cout << "无效的角色选择！" << std::endl;
        return;
    }
    
    // 检查用户名是否已存在
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            std::cout << "用户名已存在！" << std::endl;
            return;
        }
    }
    
    users.push_back(User(id, username, name, password, role));
    saveData();
    std::cout << "添加账户成功！" << std::endl;
}

void Menu::viewAccounts() {
    std::cout << "\n=== 查看账户 ===" << std::endl;
    std::cout << "1. 查看研发人员账户" << std::endl;
    std::cout << "2. 查看行政人员账户" << std::endl;
    std::cout << "请选择: ";
    
    int choice;
    std::cin >> choice;
    
    std::string targetRole;
    if (choice == 1) {
        targetRole = "研发人员";
    } else if (choice == 2) {
        targetRole = "行政人员";
    } else {
        std::cout << "无效选择！" << std::endl;
        return;
    }
    
    bool found = false;
    for (const auto& user : users) {
        if (user.getRole() == targetRole) {
            std::cout << "工号: " << user.getId() 
                      << ", 用户名: " << user.getUsername()
                      << ", 姓名: " << user.getName()
                      << ", 角色: " << user.getRole() << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "暂无" << targetRole << "账户。" << std::endl;
    }
}

void Menu::viewMeetingRooms() {
    displayAllRoomsStatus();
}

void Menu::clearReservations() {
    std::cout << "\n=== 清空预约 ===" << std::endl;
    std::cout << "确定要清空所有预约记录吗？(y/n): ";
    
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        reservations.clear();
        saveData();
        std::cout << "已清空所有预约记录！" << std::endl;
    } else {
        std::cout << "操作已取消。" << std::endl;
    }
}

void Menu::deleteAccount() {
    std::cout << "\n=== 删除账户 ===" << std::endl;
    viewAccounts();
    
    std::string userId;
    std::cout << "请输入要删除的账户工号: ";
    std::cin >> userId;
    
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getId() == userId && it->getRole() != "管理员") {
            users.erase(it);
            saveData();
            std::cout << "删除账户成功！" << std::endl;
            return;
        }
    }
    
    std::cout << "未找到该账户或不能删除管理员账户。" << std::endl;
}

// 工具函数实现
std::string Menu::getNextMonday() {
    // 简化实现，返回固定日期
    return "2024-01-01";
}

bool Menu::isRoomAvailable(int roomId, const std::string& date, const std::string& timeSlot) {
    for (const auto& reservation : reservations) {
        if (reservation.getRoomId() == roomId && 
            reservation.getDate() == date && 
            reservation.getTimeSlot() == timeSlot &&
            reservation.getStatus() != "已取消") {
            return false;
        }
    }
    return true;
}