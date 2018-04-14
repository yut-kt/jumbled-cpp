#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DataList {
    int idata;
    DataList *next;
public:
    DataList(int a = 0,DataList *np = 0) {
        idata = a; next = np;
    }
    int getData() {
        return idata; 
    }
    void print() {
        cout << idata <<" ";
    }
    void setNext(DataList *p){ 
        next = p;
    }
    DataList *getNext(){ 
        return next;
    }
};

class Stack{
    DataList *top;    // スタックトップ
    int length;       // スタック内のデータ数（スタックの長さ）
public:
    Stack() { //コンストラクタ
        top=0; length=0;
    }
    void push(int d);   // スタックにデータをpushする
    int back();         // スタックトップのデータを返す
    void pop();         // スタックトップのデータを取り出す（取り除く）
    bool empty(){ return length == 0; } // スタックが空かの判定
    int size(){ return length; }      // スタックの長さを返す
};

void Stack::push(int d) {
    length++;
    if (top == NULL) {
        top = new DataList;
        *top = DataList(d);
    } else {
        DataList *head = new DataList(d,top);
        //*head = DataList(d, top);
        top = head;
    }
}

int Stack::back() {
    return top->getData();
}
void Stack::pop() {
    length--;
    DataList *temp = top;
    top = temp->getNext();
    delete temp;
}


int main(){
    Stack st1;  // 空のスタックを作る
    int x, y = 0;
    cout << "num : ";
    cin >> x;
    while (x > 0) {
        st1.push(x % 2);
        x /= 2;
    }
    while (!st1.empty()) {
        cout << st1.back();
        y *= 2;
        y += st1.back();
        st1.pop();
    }
    cout << endl;
    cout << "10進数 : " << y << endl;

    return 0;
}

