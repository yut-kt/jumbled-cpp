#include <iostream>
using namespace std;

int main() {

    int a, b, c = 1, num = 0, ans = 0, temp;
    cin >> a;
    temp = a;
    if (a < 0) {
        a *= -1;
    }
    b = a;
    while (a % 10 != 0) {
        a /= 10;
        num++;
        c *= 10;
    }

    for (int i = num; i > 0; i--) {
        c /= 10;
        ans += b % 10 * c;
        b /= 10;
    }
    /*for (int i = 0; i < num; i++) {
        if (i != 0 && i % 3 == 0) {
            cout << ',';
        }
        cout << ans % 10;

        cout << ans << endl;
        ans /=10;
    }*/
    cout << "num = " << num << endl;
    cout << "ans = " << ans << endl;
    if (temp < 0) {
        cout << '-';
    }
    for (int i = num; i > 0; i--) {
        if (i != num && i % 3 == 0) {
            cout << ',';
        }
        cout << ans % 10;
        ans /= 10;
    }
    cout << endl;
    return 0;

}
