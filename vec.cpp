#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int main() {
    unsigned int i;
    int tmpimax;
    string listfilename = "namelist.txt";
    vector<string> name;
    vector<int> count;
    vector<int> imax;

    ifstream listfin(listfilename.c_str());
    if (!listfin) {
        cerr << "ERROR:ファイル:" << listfilename << "を開けません。" << endl;
        exit(1);
    }
    string tmp;
    listfin >> tmp;
    name.push_back(tmp);
    count.push_back(1);
    while (listfin >> tmp) {
        cout << tmp << endl;
        int comp = name.size();
        for (unsigned int i = 0; i < comp; i++) {
            if (name[i] == tmp) {
                count[i]++;
                break;
            }
            if (i == name.size() - 1) {
                name.push_back(tmp);
                count.push_back(1);
            }
        }
    }
    int max = 0;
    for (unsigned int i = 0; i < name.size(); i++) {
        if (max < count[i]) {
            max = count[i];
        }
    }
    for (unsigned int i = 0; i < name.size(); i++) {
        if (max ==count[i]) {
            imax.push_back(i);
        }
    }

    for (i = 0; i < imax.size(); i++) {
        tmpimax = imax[i];
        cout << "最大得票数は" << count[tmpimax] << "になります(name = " << name[tmpimax] << ")" << endl;
    }
    return 0;
}
