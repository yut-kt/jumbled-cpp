#include <iostream>
#include <string>
using namespace std;

class DataList {
  int idata;
  DataList *next;
public:
  DataList(int a=0,DataList *np=0){ idata=a; next=np; }
  int getData() { return idata; }
  void print(){ cout << idata; }
  void setNext(DataList *p){ next=p; }
  DataList *getNext(){ return next; }
};

class Stack{
  DataList *top;
  int length;       // スタック内のデータ数
public:
  Stack(){ top=0; length=0; }
  void push(int d);
  int back();
  void pop();
  bool empty(){ return length==0; }
  int size(){ return length; }
  void print(int = 0);       // スタックの内容をすべて表示する
};

void Stack::push(int d) {
    length++;
    top = new DataList(d,top);
}

int Stack::back() {
    if (top == NULL) {
        return 10;
    } else {
        return top->getData();
    }
}

void Stack::pop() {
    length--;
    DataList *temp = top;
    top = temp->getNext();
    delete temp;
}

void Stack::print(int len) {
    DataList *temp = top;
    for (int i = 0; i < len - length; i++) {
        cout << "-";
    }
    for (int i = 0; i < length; i++) {
        if (top == NULL) {
            cout << "-";
        } else {
        top->print();
        top = top->getNext();
        }
    } 
    top = temp;
}

int main(){
  Stack s, b, g;  // ３本の杭、s:スタート、b:バッファ、g:ゴール
  int n;        // 円盤の数
  string from, to; // 始点と終点の入力
  Stack *fp, *tp;  // 始点と終点の杭を指すポインタ

  cout << "円盤の数--> "; 
  cin >> n;

  // n枚の円盤を杭sに載せる
  for (int i = n; i > 0; i--) {
      s.push(i);
  }

  // 実行例の通りに3本の杭を表示する。
  s.print(n);
  cout << "-S" << endl;
  b.print(n);
  cout << "-B" << endl;
  g.print(n);
  cout << "-G" << endl;

  while(cout << "移動指示(from to):" && cin >> from >> to) {
    if(from == "S" || from == "s") fp = &s;
    else if(from == "B" || from == "b") fp = &b;
    else if(from == "G" || from == "g") fp = &g;
    else{
      cout << "杭はS、B、Gの中から選んでください" << endl;
      continue;
    }
    if(to=="S"||to=="s") tp=&s;
    else if(to=="B"||to=="b") tp=&b;
    else if(to=="G"||to=="g") tp=&g;
    else {
      cout << "杭はS、B、Gの中から選んでください" << endl;
      continue;
    }

    // 杭の名前が正しく選ばれ、指定された移動が可能か判断する
    // 移動できないときは、メッセージを表示し、新しい移動指示入力に進む
    if (fp->back() > tp->back()) {
        cerr << "そこには動かせません" << endl;
        continue;
    }

    // 円盤を移動する
    tp->push(fp->back());
    fp->pop();

    // 移動後の3本の杭の状態を表示する
    s.print(n);
    cout << "-S" << endl;
    b.print(n);
    cout << "-B" << endl;
    g.print(n);
    cout << "-G" << endl;

    // 次のif文で、移動完了か判定する
    if(s.empty() && b.empty()) {
      cout<<"おめでとう！ 移動完了です！"<<endl;  break;
    }
  }
  return 0;
}

