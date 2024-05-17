#include "allcommands.h"

#include <iostream>
#include "../source/filesystem.h"

namespace{
    void errorPrint(){
        std::cout << "Неверно введена команда. Ожидается два параметра"<< std::endl;
    }
}

namespace commands {

    Directory* changeDirectory(const std::vector<std::string> &params, Directory* curr_dir) {
        if(params.size() == 2){
            auto dir = curr_dir->getChildByName(params.back());
            if(dir) {
                curr_dir = *dir;
            }else{
                std::cout << "Папка с именем <<"<< params.back() <<">> не найдена" <<std::endl;
            }
        }else{
            errorPrint();
        }
        return curr_dir;
    }

    Directory* printFileData(const std::vector<std::string> &params, Directory* curr_dir) {
        if(params.size() == 2){
            auto data = curr_dir->getFileDataByName(params.back());
            if(data.has_value()){
                std::cout << *data << std::endl;
            }else{
                std::cout << "Такого файла нет"<< std::endl;
            }
        }else {
            errorPrint();
        }
        return curr_dir;
    }

    Directory* createDir(const std::vector<std::string> &params, Directory* curr_dir) {
        if(params.size() == 2) {
            curr_dir->addDirectory(params.back());
        }else {
            errorPrint();
        }
        return curr_dir;
    }

    Directory* printAllCommands(const std::vector<std::string> &params, Directory* curr_dir) {
        std::cout << "--------------------------------------\n"
        << "cd file_name : перейти в папку file_name\n"
        << "mkdir dir_name : создать папку dir_name в текущем каталоге\n"
        << "touch file_name : создать файл file_name в текущем каталоге\n"
        << "cat file_name : вывести содержимое файла\n"
        << "write file_name : изменить содержимое файла\n"
        << "rm file_name : удалить файл file_name\n"
        << "find_by_name file_name: находит файл по имени в текущей директории\n"
        << "ls: вывести файл текущего каталога, их размер, количество свободного пространства в папке\n"
        << "--------------------------------------" << std::endl;
        return curr_dir;
    }

    Directory* createNewFile(const std::vector<std::string> &params, Directory* curr_dir) {
        if(params.size() == 2) {
            curr_dir->addNewFile(params.back());
        }else {
            errorPrint();
        }
        return curr_dir;
    }

    Directory* changeFile(const std::vector<std::string> &params, Directory* curr_dir) {
        if(params.size() == 2){
            auto data = curr_dir->getFileDataByName(params.back());
            if(data.has_value()){
                std::string new_data;
                std::cout << *data << "\nВведите новое содержимое файла: ";
                std::getline(std::cin, new_data);
                curr_dir->setFileData(params.back(), new_data);
            }else{
                std::cout << "Такого файла нет"<< std::endl;
            }
        }else{
            errorPrint();
        }
        return curr_dir;
    }

    Directory* deleteFile(const std::vector<std::string> &params, Directory* curr_dir) {
        if(params.size() == 2) {
            curr_dir->removeFile(params.back());
        }else {
             errorPrint();
        }
        return curr_dir;
    }

    Directory* FindDataByName(const std::vector<std::string> &params, Directory* curr_dir) {
        printFileData(params, curr_dir);
        return curr_dir;
    }

    Directory* printDirInformation(const std::vector<std::string> &params, Directory* curr_dir) {
        curr_dir->printDirectoryInformation();
        return curr_dir;
    }

    std::vector<std::string> readCommand() {
        std::vector<std::string> words;
        std::string word, curr_word;
        std::getline(std::cin, word);
        for(char symb: word){
            if (symb == ' ') {
                if (!curr_word.empty()) {
                    words.push_back(move(curr_word));
                }
            } else {
                curr_word.push_back(symb);
            }
        }
        if (!curr_word.empty()) {
            words.push_back(move(curr_word));
        }
        return words;
    }
}
