#include <iostream>
#include <fstream>
#include <thread>
#include <semaphore.h>
#include <fcntl.h>
#include <chrono>

using namespace std;

bool just_read = false;
sem_t* semaphore;

void writeThreadF(){
    string message;
    std::ofstream file;
    while(true){
        file.open("text.txt", ios::app);
        if(file.is_open()) {
            getline(cin, message);
            file << message << '\n';
            file.close();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            just_read = true;
            sem_post(semaphore);
            sem_post(semaphore);
        }
    }
}

void readThreadF(){
    string text;
    std::ifstream file;
    file.open("text.txt");
    while(true) {
        sem_wait(semaphore);
        if (file.is_open()) {
            getline(file, text);
            if(!just_read) {
                cout <<"Также я: " +  text << endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            just_read = false;
        }
    }
}

int main() {
    const char* semaphore_name = "/my_named_semaphore";
    semaphore = sem_open(semaphore_name, O_CREAT, 0644, 0);

    thread write(writeThreadF);
    thread read(readThreadF);

    write.join();
    read.join();

    sem_destroy(semaphore);
    return 0;
}

