#include "commands/allcommands.h"
#include "source/filesystem.h"


int main(){
    FileSystem fileSystem;

    fileSystem.addStrategy("cd", commands::changeDirectory);
    fileSystem.addStrategy("cat", commands::printFileData);
    fileSystem.addStrategy("mkdir",commands::createDir);
    fileSystem.addStrategy("help", commands::printAllCommands);
    fileSystem.addStrategy("touch", commands::createNewFile);
    fileSystem.addStrategy("write", commands::changeFile);
    fileSystem.addStrategy("rm", commands::deleteFile);
    fileSystem.addStrategy("find_by_name",  commands::FindDataByName);
    fileSystem.addStrategy("ls",  commands::printDirInformation);

    Directory root_dir;
    fileSystem.waitCommand(&root_dir);
    return 0;
}