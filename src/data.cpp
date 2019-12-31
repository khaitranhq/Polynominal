#include <iostream>
#include <stdio.h>
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

template <typename S, typename T>
class Pair
   {
      public:
               Pair();
               Pair(S,T);
               Pair(const Pair &);
               ~Pair();
               const Pair &operator=(const Pair &other);

               S& first();
               T& second();
      private:
               S *f;
               T *s;
               static int count;

   };
// 0-parameter constructor
template <typename S, typename T>
Pair<S,T>::Pair()
   {
      f = new S;
      s = new T;
   }

// 2-param constructor
template <typename S, typename T>
Pair<S,T>::Pair(S x, T y)
   {
      f = new S;  *f = x;
      s = new T;  *s = y;
   }

//copy constructor
template <typename S, typename T>
Pair<S,T>::Pair(const Pair &other)
{
    f = NULL; s = NULL;
    if(other.f != NULL)
    f = new S(*other.f);

    if(other.s != NULL)
    s = new T(*other.s);
}
//destructor

template <typename S, typename T>
Pair<S,T>::~Pair()
{
    if(f != NULL)
    delete f;

    if(s != NULL)
    delete s;

    f = NULL;
    s = NULL;
}

//deep assignment

template <typename S, typename T>
const Pair<S,T> & Pair<S,T>::operator=(const Pair<S,T> &other)
{
    if(this != &other)
    {
        if(f != NULL)
        delete f;

        if(s != NULL)
        delete s;

        f = NULL; s = NULL;

        if(other.f != NULL)
        f = new S(*other.f);

        if(other.s != NULL)
        s = new T(*other.s);
    }
    return *this;
}

template<typename S, typename T>
S& Pair<S, T>::first(){
    return *f;
}

template<typename S, typename T>
T& Pair<S, T>::second(){
    return *s;
}


class Polynomial{
    private:
        Pair<int, float> *arr;
        int sizeArr, maxDeg;
    public:
        Polynomial(int = 0);
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
    Polynomial res;;
    float r = 0;
    debug(r)
    //res.arr[0].second() = arr[0].second();

    Pair<Polynomial, float> ans(res, r);
    return ans;
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
        // debug(res.arr[i].second())
    }
}

const Polynomial& Polynomial::operator = (const Polynomial& P){
    this -> sizeArr = P.sizeArr;
    this -> maxDeg = P.maxDeg;
    delete[] arr;
    this -> arr = new Pair<int, float>[sizeArr];
	cout << (*(arr + 1)).first() << endl;
    return *this;
    for(int i = 0 ; i < P.sizeArr ; ++i) {
        arr[i] = P.arr[i];
        debug(arr[i].second())
    }
}

int main()
{
	freopen("DATA1", "r", stdin);
	freopen("DATA2", "w", stdout);

	int n, c;
	cin >> n;
	Polynomial P(n);
	cin >> P;
	cin >> c;

	(P / c);


	// cout << ans.first() << endl;
	// cout << ans.second();
	return 0;
}
