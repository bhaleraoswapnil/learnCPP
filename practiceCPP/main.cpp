//
//  main.cpp
//  practiceCPP
//
//  Created by Swapnil Bhalerao on 13/09/21.
//clang++ -std=c++14 -stdlib=libc++ main.cpp myVector.cpp myVector.hpp

#include <iostream>
using namespace std;
//==============================================================================================================================
template <class T>
class myVector
{
private:
    T *ptr;
    int mCap;
    int mCurr;

public:
    myVector();
    myVector(const myVector &);
    myVector &operator=(const myVector &);
    myVector(myVector &&);
    void operator=(myVector &&);
    ~myVector();

    // push_back() & pop_back()
    void push_back(T);
    void pop_back();
    void getInfo();
};
//==============================================================================================================================
template <class T>
myVector<T>::myVector()
{
    cout << "Default Constructor" << endl;
    this->mCap = 2;
    this->mCurr = 0;
    this->ptr = new T[this->mCap];
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myVector<T>::~myVector()
{
    cout << "Destructor" << endl;
    if (nullptr != this->ptr)
    {
        delete[] this->ptr;
        this->ptr = nullptr;
        this->mCap = 0;
        this->mCurr = 0;
    }
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myVector<T>::myVector(const myVector &rhs)
{
    cout << "Copy Constructor" << endl;
    this->mCap = rhs.mCap;
    this->ptr = new T[this->mCap];
    this->mCurr = rhs.mCurr;
    for (int i = 0; i < this->mCurr; i++)
    {
        this->ptr[i] = rhs.ptr[i];
    }
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myVector<T> &myVector<T>::operator=(const myVector &rhs)
{
    cout << "Assignment Operator" << endl;
    if (this == &rhs)
    {
        return (*this);
    }
    else
    {
        if (this->mCap != rhs.mCap)
        {
            delete[] this->ptr;
            this->mCap = rhs.mCap;
            this->ptr = new T[this->mCap];
        }
        this->mCurr = rhs.mCurr;
        for (int i = 0; i < this->mCurr; i++)
        {
            this->ptr[i] = rhs.ptr[i];
        }
        return (*this);
    }
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myVector<T>::myVector(myVector &&rhs)
{
    cout << "Move Constructor" << endl;
    this->ptr = rhs.ptr;
    this->mCap = rhs.mCap;
    this->mCurr = rhs.mCurr;
    rhs.ptr = nullptr;
    rhs.mCap = 0;
    rhs.mCurr = 0;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
void myVector<T>::operator=(myVector &&rhs)
{
    cout << "Move Assignment Operator" << endl;
    delete[] this->ptr;
    this->mCap = rhs.mCap;
    this->mCurr = rhs.mCurr;
    this->ptr = rhs.ptr;
    rhs.ptr = nullptr;
    rhs.mCap = 0;
    rhs.mCurr = 0;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
void myVector<T>::push_back(T obj)
{
    if (this->mCurr >= this->mCap)
    {
        T *temp = this->ptr;
        this->mCap = this->mCap * 2;
        this->ptr = new T[this->mCap];
        for (int i = 0; i < this->mCurr; i++)
        {
            this->ptr[i] = temp[i];
        }
        delete[] temp;
    }

    this->ptr[this->mCurr++] = obj;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
void myVector<T>::pop_back()
{
    this->mCurr--;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
void myVector<T>::getInfo()
{
    cout << "Capacity = " << this->mCap << "\t Current = " << this->mCurr << "\t add = " << this->ptr << endl;
    for (int i = 0; i < this->mCurr; i++)
    {
        cout << this->ptr[i] << "\t";
    }
    cout << endl;
}
//==============================================================================================================================
int main(int argc, const char *argv[])
{
    // insert code here...
    std::cout << "~~~~~~~~~~~~~~~Vector class Implementation~~~~~~~~~~~~~~~\n";

    myVector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i + 1);
        v1.getInfo();
        cout << endl;
    }

    myVector<int> v2;
    v2 = move(v1);

    myVector<int> v3 = move(v2);
    return 0;
}
//==============================================================================================================================