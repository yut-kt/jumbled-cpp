#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Data {
private:
    string speechfilename;  //音声データを格納した元の音声ファイル名
    vector<short> speechdata;   //音声データの配列(100サンプル目の音声データはspeechdata[99]に格納される)
public:
    Data() {}  //コンストラクタ
    
    int readrawfile(string filename){   //音声データをファイルから読みspeechdataに格納
        speechfilename=filename;
        ifstream fin(filename.c_str(), ios::binary);
        if(!fin){
            cerr << "ERROR:cannot open:" << filename << endl;
            exit(101);
        }
        fin.seekg(0,ios_base::end);
        if(speechdata.size() > 100000){
            cerr << "ERROR:need more speechdata:" << filename << endl;
            exit(103);
        }
        //これまでの処理で音声ファイルに含まれるデータ数を計算した
        //以下で音声ファイルからデータを読みspeechdataに格納する
        //データ数はsamplesuuに格納される
        fin.seekg(0,ios_base::beg);
        //fin.read((char*) speechdata,sizeof(short)*samplesuu);
        auto x = ' ';
        while (fin >> x) {
            speechdata.push_back(x);
        }
        fin.close();
        return 0;
    }
    int getmaxraw(int *,int *,string&);
};

//tmpmaxvalue:speechdata配列の中で絶対値が最大となる値を格納する変数を指すポインタ
//tmpmaxtime:最大値をとるときのデータが最初から何番目かを格納する変数を指すポインタ
//           一番初めのデータを0番目とする
//tmpmaxfilename:現在の音声データの元音声ファイルの名前を格納する文字型参照変数
//関数の中では、
//speechdataの配列0からsamplesuu-1までの中で絶対値が最大となるデータを探し、
//*tmpmaxvalue、*tmpmaxtime、tmpmaxfilenameに値を代入する。
int Data::getmaxraw(int *tmpmaxvalue,int *tmpmaxtime,string &tmpmaxfilename){
    vector<short>::iterator tmpspeechdata = speechdata.begin();
    *tmpmaxvalue = 0;
    for (unsigned int i = 0; i < speechdata.size() - 1; i++) {
        if (tmpspeechdata[i] < 0) {
            tmpspeechdata[i] *= -1;
        }
        if (*tmpmaxvalue < tmpspeechdata[i]) {
            *tmpmaxvalue = tmpspeechdata[i];
            *tmpmaxtime = i;
        }
    }
    tmpmaxfilename =  speechfilename;



    return 0;
}

int main(int argc, char *argv[])
{

    int samplingrate;
    int speechnumber;
    int tmpmaxvalue,maxvalue,nextmaxvalue,tmpmaxtime,maxtime,nextmaxtime;
    char *listfilename;
    string speechfilename;
    string tmpmaxfilename;
    string maxfilename;
    string nextmaxfilename;

    vector<Data> sldata;

    //「prac06 -S 16000 -L rawlist.txt」で実行可能なように、argc=5の場合のみ動作し、
    //それ以外の時はエラーを出力するようにする。
    //また、argvから、この後のプログラムで必要となるsamplingrateおよびlistfilenameの
    //値の取得を行いなさい。
    //さらに、「prac06 -L rawlist.txt -S 16000」のように、順番を変えても同じ動作になるようにしなさい。

    if (argc != 5) {
        cerr << "erro : Not five name" << endl;
        exit(1);
    }
    if (argv[1][1] == 'S') {
        samplingrate = atoi(argv[2]);
        listfilename = argv[4];
    } else {
        samplingrate = atoi(argv[4]);
        listfilename = argv[2];
    }




    //リストファイルを読み込み音声ファイル名を取得する
    speechnumber=0;   
    ifstream listfin(listfilename);
    if(!listfin){
        cerr << "ERROR:ファイル:" << listfilename << "を開けません。" <<endl;
        exit(4);
    }
    while(listfin >> speechfilename){
        //speechfilename(音声ファイル)のデータをsldata[speechnumber]に格納
        if(sldata[speechnumber].readrawfile(speechfilename) > 0){
            cerr << "ERROR:cannot read " << speechfilename << endl;
            exit(5);        
        }
        speechnumber++;
    }


    maxvalue = 0;
    nextmaxvalue = 0;
    for(int i=0; i < speechnumber; i++){
        //各ファイルの最大値とそれに付随するデータを計算
        if(sldata[i].getmaxraw(&tmpmaxvalue,&tmpmaxtime,tmpmaxfilename) > 0){
            cerr << "ERROR:" << i << endl;
            exit(6);
        }
        //最大値・二番目に大きい値の更新
        //最大値よりも大きければ、二番目に大きい値に最大値を代入し、次に現在の値を最大値に代入する
        //二番目に大きい値よりも大きければ、現在の値を二番目に大きい値に代入する。
        if (tmpmaxvalue > maxvalue) {
            nextmaxvalue = maxvalue;
            nextmaxtime = maxtime;
            nextmaxfilename = maxfilename;
            maxvalue = tmpmaxvalue;
            maxtime = tmpmaxtime;
            maxfilename = tmpmaxfilename;
        } else if(tmpmaxvalue > nextmaxvalue){
            nextmaxvalue = tmpmaxvalue;
            nextmaxtime = tmpmaxtime;
            maxfilename = nextmaxfilename;
        }
    }

    //最大値・二番目に大きい値の出力
    cout << "samplingrate=" << samplingrate << endl;
    cout << "max=" << maxvalue << endl;
    cout << "time=" << maxtime << endl;
    cout << "filename=" << maxfilename << endl;
    cout << "nextmax=" << nextmaxvalue << endl;
    cout << "time=" << nextmaxtime << endl;
    cout << "filename=" << nextmaxfilename << endl;
    return 0;
}

