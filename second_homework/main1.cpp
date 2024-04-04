#include <iostream>
#include <thread>

using namespace std;

void addSumNonSync(int& sum, int count_iter){
    for (int i = 0; i < count_iter; ++i) {
        sum += 2;
    }
}

void testsNonSync(){
    int sum = 0, count_iter = 10000;
    thread th1(addSumNonSync, ref(sum), count_iter);
    thread th2(addSumNonSync, ref(sum), count_iter);
    thread th3(addSumNonSync, ref(sum), count_iter);
    thread th4(addSumNonSync, ref(sum), count_iter);
    thread th5(addSumNonSync, ref(sum), count_iter);
    thread th6(addSumNonSync, ref(sum), count_iter);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    cout << sum << endl;
}

int main() {
    testsNonSync();
    return 0;
}
