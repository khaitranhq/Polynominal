#pragma once

template <typename S, typename T>
class Pair
   {
      public:
               Pair();
               Pair(S,T);
               Pair(Pair &);
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
Pair<S,T>::Pair(Pair &other)
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
