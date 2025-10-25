#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <vector>
#include <string>

class FileUtil {
public:
    static std::vector<std::string> readLines(const std::string& filename);
    static bool writeLines(const std::string& filename, const std::vector<std::string>& lines);
    static bool appendLine(const std::string& filename, const std::string& line);
    static bool fileExists(const std::string& filename);
    static void createDirectory(const std::string& dirname);
};

#endif