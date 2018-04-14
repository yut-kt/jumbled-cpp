#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class QueueInt {
private:
    int ns;
    int length;
    int arraySize;
    int *data;
public:
    QueueInt(const int = 10);
    void push(const int);
    int pop();
    int size() const;
};

QueueInt::QueueInt(const int aSize) {
    ns = 0;
    length = 0;
    arraySize = aSize;
    data = new int[arraySize];
}

void QueueInt::push(const int num) {
    if (length >= arraySize) {
        cerr << "ERROR:データを追加できません" << endl;
        exit(EXIT_FAILURE);
    }
    data[(ns + length) % arraySize] = num;
    length++;
}


int QueueInt::pop() {
    if (length <= 0) {
        cerr << "ERROR:データが１つもありません" << endl;
        exit(EXIT_FAILURE);
    }
    length--;
    ns = (ns + 1) % arraySize;
    return data[ns - 1];
}

int QueueInt::size() const {
    return length;
}

int main() {
    QueueInt q(5);
    int num = 5;

    for (int i = num - 1; i >= 0; i--) {
        q.push(i * 10);
    }
    for (int i = 0; i < num / 2; i++) {
        cout << "q.pop() = " << q.pop() << endl;
    }
    cout << "q.size() = " << q.size() << endl;
    q.push(99);
    cout << "q.size() = " << q.size() << endl;

    while (q.size() > 0) {
        cout << setw(4) << q.pop();
    }
    cout << endl;
    return 0;
}

