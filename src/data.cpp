#include <iostream>
#include <stdio.h>
#include <string>

#include "./lib/pair.h"
#include "./lib/polynominal.h"

#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

int main()
{
    freopen("DATA1", "r", stdin);
    freopen("DATA2", "w", stdout);

    int n, m;
    cin >> n;
    cin >> m;
    cin.ignore(); cin.ignore();
    Polynomial P(n + 1), Q(m + 1);

    cin >> P >> Q;

    Polynomial sum = P + Q;
    Polynomial subtract = P - Q;
    Polynomial product = P * Q;

    double c;
    cin >> c;
    Pair<Polynomial, double> divide = P / c;

    cout << "Tong hai da thuc: " << sum << endl;
    cout << "Hieu hai da thuc: " << subtract << endl;
    cout << "Tich hai da thuc: " << product << endl;
    cout << "Thuong cua da thuc chia cho (x - " << c << "): " << divide.first() << endl;
    cout << "Du cua da thuc chia cho (x - " << c << "): " << divide.second() << endl;
    return 0;
}