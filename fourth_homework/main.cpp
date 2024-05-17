#include <iostream>
#include <sys/mman.h>
#include <fstream>
#include <thread>
#include <semaphore.h>
#include <fcntl.h>
#include <chrono>
#include  <cstring>
#include <sys/stat.h>
#include <algorithm>
#include <unistd.h>

using namespace std;

const int BSIZE = 1024;

bool just_read = false;
sem_t* semaphore;

void writeThreadF(void* mapped_address){
    string message;
    while(true) {
        getline(cin, message);
        memset(mapped_address, 0, BSIZE); //небольшая неэффективность. Приходится полностью
                                                 //очищать буфер перед добавлением туда элемента
        memcpy(static_cast<char *>(mapped_address), message.c_str(), message.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        just_read = true;
        sem_post(semaphore);
        sem_post(semaphore);
    }
}

void readThreadF(void* mapped_address){
    while(true) {
        sem_wait(semaphore);
        char* text = static_cast<char*>(mapped_address);
        if (!just_read) {
            cout << "Также я: " + string{text} << endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        just_read = false;
    }
}

int main() {

    const char *semaphore_name = "/my_named_semaphore";
    semaphore = sem_open(semaphore_name, O_CREAT, 0644, 0);

    int fd = shm_open("shared_memory", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    ftruncate(fd, BSIZE); // задаем размер файла

    //получаем указатель на начало отображенного участка памяти размером BSIZE
    void *mapped_address = mmap(NULL, BSIZE,
                                PROT_READ | PROT_WRITE, MAP_SHARED, fd,0 );

    thread write(writeThreadF, ref(mapped_address));
    thread read(readThreadF, ref(mapped_address));

    write.join();
    read.join();

    sem_destroy(semaphore);
    return 0;
}