#include "filesystem.h"

Directory::Directory(){}

Directory::Directory(Directory* _father__): father(_father__){}

void FileSystem::addStrategy(std::string curr_command,
std::function<Directory*(const std::vector<std::string>&, Directory*)> func_pointer) {
    our_commands[curr_command] = func_pointer;
}

void FileSystem::waitCommand(Directory* curr_dir){
    while(true){
        std::cout << ">> ";
        std::vector<std::string> curr_action = commands::readCommand();
        if(curr_action.empty() || our_commands.find(*curr_action.begin()) == our_commands.end()){
            std::cout << "Введите команду из списка доступных!" << std::endl;
            continue;
        }
        curr_dir = our_commands[*curr_action.begin()](curr_action, curr_dir);
    }
}

void Directory::addNewFile(const std::string& file_name){
    if(file_to_data.find(file_name) == file_to_data.end()) {
        file_to_data[file_name];
    }
}

void Directory::addDirectory(const std::string& directory_name){
    if(children.find(directory_name) == children.end()){
        children[directory_name] =  new Directory(this);
    }
}

std::optional<std::string> Directory::getFileDataByName(const std::string& file_name){
    return ((file_to_data.find(file_name) == file_to_data.end())
            ? (std::nullopt): std::optional{file_to_data[file_name]});
}

std::optional<Directory*> Directory::getChildByName(const std::string& dir_name){
    if(children.find(dir_name) != children.end()){
        return children[dir_name];
    }
    else if(dir_name == ".."){
        if(father){
            return father;
        }
    }
    return std::nullopt;
}

void Directory::printDirectoryInformation() const {
    size_t curr_size = 0;
    for(const auto& [file_name, data]: file_to_data){
        curr_size += data.size();
        std::cout << "file name: " << file_name << " ; size: " << data.size() << std::endl;
    }
    for(const auto [dir_name, _]: children){
        std::cout << "directory name: " << dir_name << std::endl;
    }
    std::cout << "Free_space: " << 100 * 1024 * 1024 - curr_size << " bytes" << std::endl;
}

void Directory::removeFile(const std::string& file_name){
    file_to_data.erase(file_name);
}

void Directory::setFileData(const std::string& file_name, const std::string& data){
    file_to_data[file_name] = data;
}
