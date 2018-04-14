#include <iostream>
#include <string>
using namespace std;

class opStack {
    string sdata;
    opStack *next;
public:
    opStack(string s = NULL, opStack *np = 0) {
        sdata = s; next = np;
    }
    string getData() {
        return sdata; 
    }
    void print() {
        cout << sdata <<" ";
    }
    void setNext(opStack *p){ 
        next = p;
    }
    opStack *getNext(){ 
        return next;
    }
};

class Stack{
    opStack *top;    // スタックトップ
    int length;       // スタック内のデータ数（スタックの長さ）
public:
    Stack() { //コンストラクタ
        top = 0;
        length = 0;
    }
    void push(string d);   // スタックにデータをpushする
    string back();         // スタックトップのデータを返す
    void pop();         // スタックトップのデータを取り出す（取り除く）
    bool empty(){ return length == 0; } // スタックが空かの判定
    int size(){ return length; }      // スタックの長さを返す
};

void Stack::push(string d) {
    length++;
    if (top == NULL) {
        top = new opStack(d);
    } else {
        opStack *head = new opStack(d, top);
        top = head;
    }
}

string Stack::back() {
    if (top == NULL) {
        return "Empty";
    }
    return top->getData();
}

void Stack::pop() {
    length--;
    opStack *temp = top;
    top = temp->getNext();
    delete temp;
}

int main(){
    Stack st1;  // 空のスタックを作る
    string term, form = "!"; //式の保存用
    bool ope = true, parenthesis = false, braces = false, first = true;
    
    cout << "数式ー＞ ";
    while(cin >> term && term != "$") {

        if (term[0] >= '0' && term[0] <= '9' || term.size() > 1 && term[0] == '-') { //数字の判定
            for (unsigned int i = 1; i < term.size(); i++) { //数字に他の文字が混ざった場合のエラー処理
                if (term[i] < '0' || term[i] > '9') {
                    cerr << "\nERROR : Wrong form !" << endl;
                    return 1;
                }
            }
            if (form.back() == ')' || form.back() == '}') {
                st1.push("*");
                ope = true;
            }
            if (!ope) { //数字が並んで入力された時のエラー処理
                cerr << "\nERROR : Wrong form !" << endl; 
                return 1;
            }
            cout << term << " ";
            ope = false;
            first = false;
        } else if (term.size() > 1) { //括弧や演算子が複数ある場合のエラー処理
            cerr << "\nERROR : Wrong form !" << endl;
            return 1;
        } else if (term == "(") { //左括弧の判定
            if (parenthesis) {
                cerr << "\nERROR : No closed parentesis !" << endl;
                return 1;
            }
            if (!ope && !first) { //左括弧の直前が演算子ではなく数字だった場合の処理
                st1.push("*");
                ope = true;
            } else {
                first = false;
            }
            st1.push(term);
            parenthesis = true;
        } else if (term == "{") {
            if (parenthesis) { //小括弧が閉じられていない場合のエラー処理
                cerr << "\nERROR : Parenthesis is not closed !" << endl;
                return 1;
            }
            if (braces) { //中括弧が閉じられていない場合のエラー処理
                cerr << "\nERROR : No closed praces !" << endl;
                return 1;
            }
            if (!ope && !first) { //括弧の直前が演算子ではなく数字だった場合の処理
                st1.push("*");
                ope = true;
            } else {
                first = false;
            }
            st1.push(term);
            braces = true;
        } else if (term == "+" || term == "-") { //演算子の判定
            if (ope) { //演算子が連続で入力された場合のエラー処理
                cerr << "\nERROR : Wrong form !" << endl;
                return 1;
            }
            while(st1.size() > 0 && st1.back() != "(" && st1.back() != "{") { //左括弧まで出力
                cout << st1.back() << " ";
                st1.pop();
            }
            st1.push(term);
            ope = true;
        } else if (term == "*" || term == "/") { //演算子の判定
            if (ope) { //演算子が連続で入力された時のエラー
                cerr << "\nERROR : Wrong form !" << endl;
                return 1;
            }
            if (st1.back() == "+" || st1.back() == "-") { //優先順位の判定
                st1.push(term);
            } else {
                while (st1.size() > 0 && st1.back() != "(" && st1.back() != "{") { //左括弧まで出力
                    cout << st1.back() << " ";
                    st1.pop();
                }
                st1.push(term);
            }
            ope = true;
        } else if (term == ")") {
            if (!parenthesis) { //左の小括弧が入力されていない場合のエラー処理
                cerr << "\nERROR : No left parenthesis !" << endl;
                return 1;
            }
            while (st1.back() != "(") {
                cout << st1.back() << " ";
                st1.pop();
            }
            parenthesis = false;
            st1.pop();
        } else if (term == "}") {
            if (parenthesis) { //小括弧が閉じらていない場合のエラー処理
                cerr << "\nERROR : Parenthesis is not closed !" << endl;
                return 1;
            }
            if (!braces) { //左の中括弧が入力されていない場合のエラー処理
                cerr << "\nERROR : No left braces !" << endl;
                return 1;
            }
            while (st1.back() != "{") {
                cout << st1.back() << " ";
                st1.pop();
            }
            braces = false;
            st1.pop();
        } else { //不明な文字が入力された場合のエラー処理
            cerr << "\nERROR : Wrong character !" << endl;
            return 1;
        }
        form += term; //式の保存
    }

    if (parenthesis) { //小括弧が閉じられていない状態で終わろうとした場合のエラー処理
        cerr << "\nERROR : No closed parentesis !" << endl;
        return 1;
    }
    if (braces) { //中括弧が閉じられていない状態で終わろうとした場合のエラー処理
        cerr << "\nERROR : No closed praces !" << endl;
        return 1;
    }

    while(st1.size() > 0) { //$が入力されたらスタックの中身をすべて出力
        cout << st1.back() << " ";
        st1.pop();
    }
    cout << endl;

    for (unsigned int i = 1; i < form.size() - 1; i++) { //0で割った場合のエラー処理
        if (form[i] == '/' && form[i + 1] == '0') {
            cerr << "ERROR : This form cannot calculate !" << endl;
            return 1;
        }
    }
    return 0;
}

