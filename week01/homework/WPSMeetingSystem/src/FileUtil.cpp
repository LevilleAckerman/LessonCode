#include "FileUtil.h"
#include <fstream>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

vector<string> FileUtil::readLines(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    string line;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        file.close();
    }
    
    return lines;
}

bool FileUtil::writeLines(const string& filename, const vector<string>& lines) {
    ofstream file(filename);
    
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << endl;
        }
        file.close();
        return true;
    }
    
    return false;
}

bool FileUtil::appendLine(const string& filename, const string& line) {
    ofstream file(filename, ios_base::app);
    
    if (file.is_open()) {
        file << line << endl;
        file.close();
        return true;
    }
    
    return false;
}

bool FileUtil::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void FileUtil::createDirectory(const string& dirname) {
#ifdef _WIN32
    // Windows创建目录
    CreateDirectoryA(dirname.c_str(), NULL);
#else
    // Linux/Mac创建目录
    mkdir(dirname.c_str(), 0755);
#endif
}