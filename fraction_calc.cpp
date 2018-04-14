#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int gcd (int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

class Fraction {
private:
    int numerator, denominator;
public:
    Fraction (int num = 0, int den = 1) {
        if (den == 0) {
            cerr << "Cannot divide!" << endl;
            exit(1);
        }
        numerator = num;
        denominator = den;
    }

    void reduce() {
        int a = numerator, b = denominator;
        if(a < 0){
            a*=-1;
        }
        if(b < 0){
            b*=-1;
        }
        numerator /= gcd(a, b);
        denominator /= gcd(a, b);
    }
    friend ostream& operator<<(ostream& , Fraction);
    friend istream& operator>>(istream&, Fraction&);
    friend Fraction operator+(Fraction, Fraction);
    Fraction operator-(Fraction a) {
        Fraction temp(numerator * a.denominator - denominator * a.numerator, denominator * a.denominator);
        temp.reduce();
        return temp;
    }
    friend Fraction operator*(Fraction, Fraction);
    Fraction operator/(Fraction a) {
        Fraction temp(numerator * a.denominator, denominator * a.numerator);
        temp.reduce();
        return temp;
    }
    bool operator>(Fraction a) {
        if (numerator * a.denominator > a.numerator * denominator) {
            return true;
        } else {
            return false;
        }
    }
    bool operator==(Fraction a) {
        if (numerator*a.denominator==a.numerator*denominator) {
            return true;
        } else {
            return false;
        }
    }
};

ostream& operator<<(ostream &oust, Fraction a) {
    if (a.numerator == 0) {
        oust << 0;
    } else {
        if (a.numerator == a.denominator) {
            oust << 1;
        } else {
            if (a.denominator < 0) {
                a.numerator *= -1;
                a.denominator *= -1;
            }
            if (a.denominator == 1) {
                oust << a.numerator;
            } else {
                oust << '(' << a.numerator <<'/' << a.denominator << ')';
            }
        }
    }
    return oust;
}
istream& operator>>(istream &ist, Fraction &a) {
    ist >> a.numerator >> a.denominator;
    return ist;
}
Fraction operator+(Fraction a, Fraction b) {
    Fraction temp(a.numerator * b.denominator + a.denominator * b.numerator, a.denominator * b.denominator);
    temp.reduce();
    return temp;
}
Fraction operator*(Fraction a, Fraction b) {
    Fraction temp(a.numerator * b.numerator, a.denominator * b.denominator);
    temp.reduce();
    return temp;
}
int main() {
    Fraction f1(1, 2), f2(2, 3), f3(2), f4(2, 4), f5(-3, 5), f6(0), ans, g1, g2;

    ans = f1 + f2;
    cout << f1 << '+' << f2 << '=' << ans << endl;
    ans = f1 - f2;
    cout << f1 << '-' << f2 << '=' << ans << endl;
    ans = f1 * f3;
    cout << f1 << '*' << f3 << '=' << ans << endl;
    ans = f1 - f4;
    cout << f1 << '-' << f4 << '=' << ans << endl;
    ans = f2 / f4;
    cout << f2 << '/' << f4 << '=' << ans << endl;
    ans = f2 / f5;
    cout << f2 << '/' << f5 << '=' << ans << endl;
    ans = f6 * f2;
    cout << f6 << '*' << f2 << '=' << ans << endl;
    ans = 1 + f5;
    cout << 1 << '+' << f5 << '=' << ans << endl;

    cout << "分数を入力―>";
    cin >> g1;
    cout << "分数を入力―>";
    cin >> g2;
    if (g1 > g2) {
        cout << g1 << '>' << g2 << endl;
    } else if (g1 == g2) {
        cout << g1 << "==" << g2 << endl;
    } else {
        cout << g1 << '<' << g2 << endl;
    }
    ans = g1 * g2;
    cout << g1 << '*' << g2 << '=' << ans << endl;
    int n = 20;
    cout << g1 << '*' << n << '=' << g1 * n << "  " << n << '*' << g1 << '=' << n * g1 << endl;
    return 0;
}
