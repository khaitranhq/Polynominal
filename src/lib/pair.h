#pragma once

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
