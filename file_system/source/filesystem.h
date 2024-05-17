#ifndef FILE_SYSTEM_FILESYSTEM_H
#define FILE_SYSTEM_FILESYSTEM_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <unordered_set>
#include <optional>

#include "../commands/allcommands.h"


class FileSystem{
public:
    void waitCommand(Directory* curr_dir);
    void addStrategy(std::string curr_command,
                     std::function<Directory*(const std::vector<std::string>&, Directory*)> func_pointer);
private:
    std::unordered_map<std::string, std::function<Directory*(const std::vector<std::string>&, Directory*)>> our_commands;
};

class Directory{
public:
    Directory();
    Directory(Directory* _father_);

    void addNewFile(const std::string& file_name);

    void addDirectory(const std::string& directory_name);

    std::optional<std::string> getFileDataByName(const std::string& file_name);

    std::optional<Directory*> getChildByName(const std::string& dir_name);

    //возвращает количество занимаемого места файлами в байтах
    void printDirectoryInformation() const;

    void removeFile(const std::string& file_name);

    void setFileData(const std::string& file_name, const std::string& data);

private:
    std::map<std::string, std::string> file_to_data;
    std::map<std::string, Directory*> children;
    Directory* father;
};

#endif //FILE_SYSTEM_FILESYSTEM_H