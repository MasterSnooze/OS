#ifndef FILE_SYSTEM_ALLCOMMANDS_H
#define FILE_SYSTEM_ALLCOMMANDS_H

#include <vector>
#include <string>

class Directory;

namespace commands{
    //*&
    //cd
    Directory* changeDirectory(const std::vector<std::string>& params, Directory* curr_dir);

    //cat
    Directory* printFileData(const std::vector<std::string>& params, Directory* curr_dir);

    //mkdir
    Directory* createDir(const std::vector<std::string>& params, Directory* curr_dir);

    //help
    Directory* printAllCommands(const std::vector<std::string>& params, Directory* curr_dir);

    //touch
    Directory* createNewFile(const std::vector<std::string>& params, Directory* curr_dir);

    //write
    Directory* changeFile(const std::vector<std::string>& params, Directory* curr_dir);

    //rm
    Directory* deleteFile(const std::vector<std::string>& params, Directory* curr_dir);

    //find_by_name
    Directory* FindDataByName(const std::vector<std::string>& params, Directory* curr_dir);

    //ls
    Directory* printDirInformation(const std::vector<std::string>& params, Directory* curr_dir);

    std::vector<std::string> readCommand();
}
#endif //FILE_SYSTEM_ALLCOMMANDS_H
