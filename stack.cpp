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
    top = new DataList(d,top);
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
    string term; 
    cout << "数式ー＞ ";
    while(cin >> term && term != "$") {
        if (term == "+" || term == "-" || term == "*" || term == "/") {
            int num2 = st1.back();
            st1.pop();
            int num1 = st1.back();
            st1.pop();
            if (term == "+") {
                st1.push(num1 + num2);
            } else if (term == "-") {
                st1.push(num1 - num2);
            } else if (term == "*") {
                st1.push(num1 * num2);
            } else if (term == "/") {
                st1.push(num1 / num2);
            } 
        } else {
            st1.push(atoi(term.c_str()));
        }
    }
    cout << "=" << st1.back() << endl;
    return 0;
}

