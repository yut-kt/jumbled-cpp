#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MAXRE = 3; // 返信の最大数
const int MAXSIZE = 20; // コメント最大数

// 投稿されたコメントのクラス
class Post {
private:
    int id; // コメントID
    int pid; // コメントの親ID
    string comment; // コメント
    Post *re[MAXRE]; // 返信コメントの配列
public:
    Post(int = -1, int = -1, string = ""); // コンストラクタ
    ~Post() { //デストラクタ
        for (int i = 0; i < MAXRE; i++) {
            if (re[i] == NULL) {
                continue;
            }
            delete re[i]; //デストラクタの再帰呼び出し
            re[i] = NULL;
        }
        cout << "Deleted id : " << id << endl;
    }
    int getId() {return id;}
    int getPid() {return pid;}
    Post* getre(int d) const {return re[d];} //試作用　受け取った数値の返信コメントのポインタを返す
    void dump() {cout << id << ": " << comment << endl;}
    void setRe(Post *);
    void print(int);
    void del(int);
};

// Postのコンストラクタ
Post::Post(int i, int p, string c) {
    id = i;
    pid = p;
    comment = c;
    for (int i = 0; i < MAXRE; i++) {
        re[i] = 0;
    }
}

void Post::setRe(Post *p) {
    for (int i = 0; i < MAXRE; i++) {
        if (re[i] == 0) {
            re[i] = p;
            break;
        }
    }
}

void Post::print(int num) {
    dump();
    for (int i = 0; i < MAXRE; i++) {
        if(re[i] == 0) {
            continue;
        }
        for (int j = 0; j < num; j++) {
            cout << " ";
        }
        cout << "-";
        re[i]->print(num + 1);
    }
}

void Post::del(int de) {
    for (int i = 0; i < MAXRE; i++) {
        if (re[i] == NULL) { //この後の判定(消したいidとre[i]のidが一致するか)でre[i]にNULLが入ってた場合なぜかエラーが生じるので繰り返しに戻す
            continue;
        }
        if (de == re[i]->id) { //消したいidが見つかったらデストラクタで削除
            delete re[i];
            re[i] = NULL;
            break;
        }
    }
}

class Board {
private:
    int index; // 次に入れるpostのindexを保存
    Post *posts[MAXSIZE]; // 全コメントの配列
public:
    Board(); // コンストラクタ
    void setPost(int, int, string); // 渡されたデータを用いてpostオブジェクトを生成し、*posts配列にひもづける
    void print(); // 掲示板に投稿されたコメントを表示
    void del(int d);
    void posts_delete(int);
};

Board::Board() {
    index = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        posts[i] = 0;
    }
}

void Board::setPost(int id, int pid, string comment) {
    posts[index++] = new Post(id, pid, comment);
    if (id == 0) {
        return;
    }
    for (int i = 0; i < index; i++) {
        if (posts[i]->getId() == pid) {
            posts[i]->setRe(posts[index - 1]);
        }
    }
}

void Board::print() {
    posts[0]->print(0);
}

void Board::del(int de) {
    if (posts[de] == NULL) { //空のidが入力されたときの処理
        cerr << "Empty id : " << de << endl;
        return;
    }
    if (de == 0) { //消したいidが0だった場合強制終了
        cerr << "No Data" << endl;
        exit(1);
    }
    Post *posts_temp = posts[posts[de]->getPid()]; //posts_deleteでpostsが削除されてしまうので保存しておく
    posts_delete(de);
    posts_temp->del(de);
    posts[de] = NULL;
}

void Board::posts_delete(int d) {
    for (int i = 0; i < MAXRE; i++) {
        if (posts[d]->getre(i) == NULL) { //postsのreがNULLかどうか判定し、再帰を抜ける
            continue;
        }
        posts_delete(posts[d]->getre(i)->getId()); //再帰呼び出し
    }
    posts[d] = NULL;
}

int input(Board& b, string fname) {
    ifstream fin(fname.c_str());
    if (!fin) {
        return 1;
    }
    int id, pid;
    string comment;
    while (fin >> id >> pid) {
        fin >> ws;
        getline(fin, comment);
        b.setPost(id, pid, comment);
    }
    return 0;
}

int main() {
    Board b;
    if (input(b, "ファイル名") == 1) {
        cerr << "can not open!" << endl;
        return 1;
    }
    b.print();
    int de; //削除したいid
    cout << endl << "Delete id -> ";
    while (cin >> de) { //削除したいidの入力
        if (de < 0 || de > 19) {
            cerr << "No array" << endl;
            continue;
        }
        b.del(de);
        b.print();
        cout << endl << "Delete id -> ";
    }
    return 0;
}

