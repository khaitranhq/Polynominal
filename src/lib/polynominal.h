#pragma once

#include <iostream>
#include "pair.h"
using namespace std;

class Polynomial{
    private:
        Pair<int, float> *arr;
        int sizeArr, maxDeg;
    public:
        Polynomial() {}
        Polynomial(int);
        ~Polynomial();

        void fixed();

        friend istream& operator >> (istream& in, Polynomial& P);
        friend ostream& operator << (ostream& out, const Polynomial& P);

        Pair<Polynomial, float> operator + (const Polynomial& P);
        Pair<Polynomial, float> operator - (const Polynomial& P);
        Pair<Polynomial, float> operator * (const Polynomial& P);
        Pair<Polynomial, float> operator / (const int& c);

        const Polynomial& operator = (const Polynomial& P);
};

/*================Definition of Polynomial class===================*/

Polynomial::Polynomial(int size): sizeArr(size), maxDeg(size){
    arr = new Pair<int, float>[size];
    for(int i = 0 ; i < size ; ++i)
        arr[i].first() = i;
}

Polynomial::~Polynomial(){
    delete[] arr;
}

void Polynomial::fixed(){
    int nonZero = 0;
    for(int i = 0 ; i < sizeArr ; ++i)
        if (arr[i].second()) ++nonZero;
    
    int cnt = nonZero;
    Pair<int, float> *tmp = new Pair<int, float>[nonZero];
    for(int i = sizeArr - 1 ; i >= 0 ; --i)
        if (arr[i].second())
            tmp[--cnt] = arr[i];

    sizeArr = nonZero;
    delete[] arr;
    arr = tmp;
}

istream& operator >> (istream& in, Polynomial& P){
    for(int i = 0 ; i < P.sizeArr ; ++i) 
        in >> P.arr[i].second();
    
    P.fixed();
    return in;
}

ostream& operator << (ostream& out, const Polynomial& P){
    for(int i = 0 ; i < P.sizeArr ; ++i)
        out << P.arr[i].second() << " ";
    return out;
}

Pair<Polynomial, float> Polynomial::operator / (const int& c){
    Polynomial res(maxDeg - 1);
    float r = 0;
    res.arr[0].second() = arr[0].second();;

    for(int i = 1 ; i < res.maxDeg ; ++i){
        int l = 0, r = sizeArr, ans = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if (arr[mid].first() <= i){
                ans = mid;
                l = mid  + 1;
            } else r = mid - 1;
        }

        if (ans != -1 && arr[ans].first() == i) ans = arr[ans].second();
        else ans = 0;

        res.arr[i].second() = ans + res.arr[i - 1].second() * c;
    }
    Pair<Polynomial, float> ans(res, r);
    return ans;
}

const Polynomial& Polynomial::operator = (const Polynomial& P){
    this -> sizeArr = P.sizeArr;
    this -> maxDeg = P.maxDeg;
    delete[] arr;
    arr = new Pair<int, float>[sizeArr];
    for(int i = 0 ; i < P.sizeArr ; ++i)
        arr[i] = P.arr[i];
    return *this;
}
