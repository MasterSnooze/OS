#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void addSumNonSync(int& sum, int count_iter){
    for (int i = 0; i < count_iter; ++i) {
        sum += 1;
    }
}

void testsNonSync(){
    int sum = 0, count_iter = 10000, count_thread = 6 ;

    vector<thread> threads;
    threads.reserve(count_thread);
    for(size_t i = 0; i < count_thread; ++i){
        threads.emplace_back(addSumNonSync, ref(sum), count_iter);
    }
    for (size_t i = 0; i < count_thread; ++i) {
        threads[i].join();
    }
    cout << sum << endl;
}

int main() {
    testsNonSync();
    return 0;
}
