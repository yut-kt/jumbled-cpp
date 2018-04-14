#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {

    int time[100000] = {};
    for (int i = 0; i < 100000; i++) {
        time[i] = 100000 - i;
    }
    clock_t start = clock();
    for (int i = 0; i < 100000; i++) {
        int min = i;
        for (int j = i + 1; j < 100000 - 1; j++) {
            if (time[min] > time[j]) {
                min = j;
            }
        }
        swap(time[min], time[i]);
    }
    int num;
    cout << "input a number" << endl;
    cin >> num;
    for (int i = 0; i < 100000; i++) {
        if (time[i] <= num) {
            cout << time[i] << endl;
        }
    }
    clock_t end = clock();
    cout << "TIME is " << end - start << endl;
}
