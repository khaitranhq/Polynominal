#include <iostream>
#include <stdio.h>
#include <string>
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

/*=====================================*/



/*=====================================*/

template <class S, class T>
class Pair
{
public:
    Pair(){}
    Pair(const S &, const T &);
    Pair(const Pair &);
    const Pair &operator=(const Pair &other);

    S &first();
    T &second();

private:
    S f;
    T s;
};

// 2-param constructor
template <class S, class T>
Pair<S, T>::Pair(const S &x, const T &y)
{
   f = x; s= y;
}

//copy constructor
template <class S, class T>
Pair<S, T>::Pair(const Pair<S, T> &other)
{
    f = other.f;
    s = other.s;
}

template <class S, class T>
const Pair<S, T> &Pair<S, T>::operator=(const Pair<S, T> &other)
{
    f = other.f; s = other.s;
    return *this;
}

template <class S, class T>
S& Pair<S, T>::first()
{
    return this -> f;
}

template <class S, class T>
T& Pair<S, T>::second()
{
    return this -> s;
}

/*=======================================================*/

class Polynomial
{
private:
    Pair<int, double> *arr;
    int sizeArr, maxDeg;

public:
    Polynomial(int = 0);
    Polynomial(const Polynomial &);
    ~Polynomial();

    void fixed();

    friend istream &operator>>(istream &in, Polynomial &P);
    friend ostream &operator<<(ostream &out, const Polynomial &P);

    Polynomial operator+(const Polynomial&);
    Polynomial operator-(const Polynomial&);
    Polynomial operator*(const Polynomial&);
    Pair<Polynomial, double> operator/(const double&);

    Polynomial &operator=(const Polynomial &P);
};

/*================Definition of Polynomial class===================*/

Polynomial::Polynomial(int size) : sizeArr(size), maxDeg(size)
{
    arr = new Pair<int, double>[size];
}

Polynomial::Polynomial(const Polynomial &other)
{
    sizeArr = other.sizeArr;
    maxDeg = other.maxDeg;
    delete[] arr;
    arr = new Pair<int, double>[sizeArr];
    for (int i = 0; i < sizeArr; ++i)
        arr[i] = other.arr[i];
}

Polynomial::~Polynomial()
{
    delete[] arr;
}

void Polynomial::fixed()
{
    int nonZero = 0;
    for (int i = 0; i < sizeArr; ++i)
        if (arr[i].second())
            ++nonZero;

    int cnt = nonZero;
    Pair<int, double> *tmp = new Pair<int, double>[nonZero];
    for (int i = sizeArr - 1; i >= 0; --i)
        if (arr[i].second())
            tmp[--cnt] = arr[i];

    sizeArr = nonZero;
    delete[] arr;
    arr = tmp;
}

istream &operator>>(istream &in, Polynomial &P)
{   
    string str;
    getline(in, str);
    str.append("+");

    int cnt = -1, deg = 0;
    double coef = 0;
    bool isCoef = 1, isNegative = 0, afterPoint = 0;
    for(int i = 0 ; i < str.size() ; ++i)  {
        if (str[i] == '^') isCoef ^= 1;
        if (str[i] == '.') afterPoint = 1;

        if (isdigit(str[i])){
            int digit = str[i] - '0';
            if (isCoef) coef = coef * (afterPoint ? 0.1f : 10) + digit;
            else deg = deg * 10 + digit;
        }
        
        if (str[i] == 'x' && (i == str.size() - 1 || str[i + 1] != '^'))
            deg = 1;

        if (str[i] == '+' || str[i] == '-'){
            // debug(cnt) 
            while(cnt < P.maxDeg - deg - 2){
                ++cnt;
                P.arr[cnt] = Pair<int, double>(P.maxDeg - cnt, 0);
            }

            if (coef == 0 && deg) coef = 1;
            coef *=  (isNegative ? -1 : 1);

            P.arr[++cnt] = Pair<int, double>(deg, coef);

            if (str[i] == '-') isNegative = 1;
            if (str[i] == '+') isNegative = 0;

            coef = 0, deg = 0;
            isCoef = 1; afterPoint = 0;
        }
    }
    P.fixed();
    return in;
}

ostream &operator<<(ostream &out, const Polynomial &P)
{
    for (int i = 0; i < P.sizeArr; ++i) {
        if (i && P.arr[i].second() > 0) out << " + ";
        if (i && P.arr[i].second() < 0) out << " - ";
        if (P.arr[i].first() == 0 || P.arr[i].second() != 1) out << P.arr[i].second();
        if (P.arr[i].first() >= 1)  {
            out << "x";
            if (P.arr[i].first() > 1) out << "^" << P.arr[i].first();
        }
    }
    return out;
}

Pair<int, double>& findIndex(Pair<int, double>* arr, int size, int index){
    int l = 0, r = size - 1, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if (arr[mid].first() <= index){
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    
    if (ans != -1 && arr[ans].first() == index)
        return arr[ans];
    else {
        static Pair<int, double> tmp(-1, 0);
        return tmp;
    }
} 

Polynomial Polynomial::operator + (const Polynomial& other){
    Polynomial res(max(other.maxDeg, this->maxDeg));
    for(int i = 0 ; i < res.maxDeg ; ++i) {
        res.arr[i].first() = res.maxDeg - i - 1;
        Pair<int, double> x = findIndex(arr, sizeArr, maxDeg - i - 1);
        Pair<int, double> y = findIndex(other.arr, other.sizeArr, maxDeg - i - 1);
        res.arr[i].second() = (x.first() != -1) ? x.second() : 0;
        res.arr[i].second() += (y.first() != -1) ? y.second() : 0;
    }   
    res.fixed();
    return res;
}

Polynomial Polynomial::operator - (const Polynomial& other){
    Polynomial res(max(other.maxDeg, this->maxDeg));
    for(int i = 0 ; i < res.maxDeg ; ++i) {
        res.arr[i].first() = res.maxDeg - i - 1;
        Pair<int, double> x = findIndex(arr, sizeArr, maxDeg - i - 1);
        Pair<int, double> y = findIndex(other.arr, other.sizeArr, maxDeg - i - 1);
        res.arr[i].second() = (x.first() != -1) ? x.second() : 0;
        res.arr[i].second() -= (y.first() != -1) ? y.second() : 0;
    }   
    res.fixed();
    return res;
}

Polynomial Polynomial::operator * (const Polynomial& other){
    Polynomial res(maxDeg + other.maxDeg);
    for(int i = 0 ; i < res.sizeArr ; ++i)
        res.arr[i].first() = res.maxDeg - i - 1;
    for(int i = 0 ; i < sizeArr ; ++i)
        for(int j = 0 ; j < other.sizeArr ; ++j){
            Pair<int, double> x = arr[i];
            Pair<int, double> y = other.arr[j];
            // debug(x.first()) debug(x.second())
            // debug(y.first()) debug(y.second()) cout << endl;
            int index = x.first() +  y.first();
            index = res.maxDeg - index - 1;
            res.arr[index].second() += x.second() * y.second();
        }
    res.fixed();
    return res;
}

Pair<Polynomial, double> Polynomial::operator/(const double &c)
{
    Polynomial res(maxDeg - 1);
    double remain = 0;

    for(int i = 0 ; i < res.sizeArr ; ++i)
        res.arr[i].first() = res.maxDeg - i - 1;

    res.arr[0].second() = arr[0].second();
    for (int i = 1; i <= res.maxDeg; ++i)
    {
        Pair<int, double> ans = findIndex(arr, sizeArr, maxDeg - i - 1);
        
        // debug(i)
        if (ans.first() == -1) ans.second() = 0;
        // debug(ans.first()) debug(ans.second()) cout << endl;
        double coef = ans.second() + res.arr[i - 1].second() * c;
        if (i < res.maxDeg)
            res.arr[i].second() = coef;
        else 
            remain = coef;
    }
    res.fixed();
    Pair<Polynomial, double> ans(res, remain);
    return ans;
}

Polynomial &Polynomial::operator=(const Polynomial &P)
{
    this->sizeArr = P.sizeArr;
    this->maxDeg = P.maxDeg;
    delete[] arr;
    this->arr = new Pair<int, double>[sizeArr];
    for (int i = 0; i < P.sizeArr; ++i)
        arr[i] = P.arr[i];
    return *this;
}

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
