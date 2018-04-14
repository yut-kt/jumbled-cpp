// 線形探索（配列の動的確保）
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

double get_sec(void) { //時間の測定関数
  struct timeval time_v;
  timerclear(&time_v);
  gettimeofday(&time_v, NULL);
  return time_v.tv_sec + (double)time_v.tv_usec * 1e-6;
}


// セルを表わす構造体の定義 
struct cell{
  int key;           // キー
  char data[256];    // キーに対応する値（文字列）
  struct cell *next;    // 次のデータへのポインタ
};

//リストの要素生成
//int key:キー, char *data:対応するデータとなる文字列 
struct cell *make_cell(int key, const char *data){
  struct cell *mk_cell;
  
  // cellの領域を確保 
  mk_cell = new struct cell;
  
  // 文字列 data を cell->data へコピーする
  strcpy(mk_cell->data, data);
  
  // 整数へ変換
  mk_cell->key = key;
  
  // nextを初期化
  mk_cell->next = NULL;
  
  return mk_cell; //ポインタを返す
}

//リストを検索
// root:ツリーのルートのポインタ  key:検索したいキー
// 戻値：キーが存在したノードへのポインタ．ない場合は NULL
struct cell *search_cell(struct cell *head, int key){
  struct cell *buf;
  buf = head;
  
  while(buf != NULL){
    if(buf->key == key){
      return buf; //見つかったらポインタを返す
    }
    
    buf = buf->next; //bufを更新
  }

  return NULL;
}


int main(int argc, char *argv[])
{  
  if(argc == 1){  // 引数がない場合
    cout << "input file name\n";
    return -1;
  }
  
  // ファイルオープン
  ifstream fp(argv[1]); 

  // リストのヘッドを定義し初期化
  struct cell *head;
  head = NULL; 
  
  // データのリストへの格納
   cout << "Loading " << argv[1] << endl;
   string line;
   
   double s_start = get_sec(); //構築時間測定開始
   
   while(fp >> line){
     // ファイルからキーと対応する値（ファイル名）を取得
     int index = line.find(",");    // 区切り文字までの文字数
     string key_str = line.substr(0,index); 
     string value = line.substr(index+1);
     
     // キーを整数変換 （本当は危険）
     int key = atoi(key_str.data());
     
     if(value.length() > 255){
       cout << "length of value is too long\n";
       return -1;
     }
     
     // リスト要素の生成
     struct cell *e_cell;
     e_cell = make_cell(key, value.data());
     
     // 生成した要素をリストの先頭に追加
     e_cell->next = head;
     
     // 先頭アドレスを更新
     head = e_cell;
   }
   cout << endl;
   
   double s_end = get_sec(); //構築時間測定終了
   cout << "構築時間：" << s_end-s_start << endl;



   // 配列 data から値がkyである要素番号を探索
   int ky;  
   struct cell *s_cell;
   s_cell = search_cell(head, ky); 

   s_start = get_sec(); //探索時間測定開始
   for(int i=0; i<1000; i++){
     search_cell(head,i);
   }
   s_end = get_sec(); //探索時間測定終了
   cout << "探索時間：" << s_end-s_start << endl;

   fp.close();

   return 0;
}

