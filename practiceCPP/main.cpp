//
//  main.cpp
//  practiceCPP
//
//  Created by Swapnil Bhalerao on 13/09/21.
//clang++ -std=c++14 -stdlib=libc++ main.cpp

#include <iostream>
#include <string>
using namespace std;

//==============================================================================================================================
class dummy
{
private:
    int a;
    int b;

public:
    dummy(int x, int y) : a(x), b(y) { cout << " dummy object constructor\n"; }
    ~dummy() { cout << "\n dummy object deleted\n"; }
    int sum() { return (a + b); }
};
//==============================================================================================================================
template <class T>
class mySharedPtr
{
private:
    T *ptr;
    int *ref;

public:
    mySharedPtr();
    mySharedPtr(T *);
    ~mySharedPtr();
    mySharedPtr(const mySharedPtr &obj)
    {
        cout << " mySharedPtr Copy Constructor " << endl;
        this->ptr = obj.ptr;
        this->ref = obj.ref;
        *this->ref = *this->ref + 1;
    }
    mySharedPtr &operator=(const mySharedPtr<T> &obj)
    {
        cout << " mySharedPtr Assignment operator " << endl;
        if (this != &obj)
        {
            this->ptr = obj.ptr;
            this->ref = obj.ref;
            *this->ref = *this->ref + 1;
        }
        return *this;
    }
    mySharedPtr(mySharedPtr &&);
    void operator=(mySharedPtr &&);

    T *operator->();
    T &operator*();
    bool validPointer()
    {
        if (this->ptr == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};
//==============================================================================================================================
template <class T>
mySharedPtr<T>::mySharedPtr()
{
    cout << " mySharedPtr Default Constructor " << endl;
    this->ptr = nullptr;
    this->ref = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
mySharedPtr<T>::mySharedPtr(T *p)
{
    cout << " mySharedPtr Parameter Constructor " << endl;
    this->ptr = p;
    this->ref = new int;
    *this->ref = 1;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
mySharedPtr<T>::~mySharedPtr()
{

    if (this->ref != nullptr)
    {
        *this->ref = *this->ref - 1;
    }
    cout << " mySharedPtr Destructor, ref count = " << *this->ref;
    if (*this->ref < 1)
    {
        cout << ", deleted memory";
        delete this->ptr;
        this->ptr = nullptr;
    }
    cout << endl;
}
//------------------------------------------------------------------------------------------------------------------------------

template <class T>
mySharedPtr<T>::mySharedPtr(mySharedPtr &&rhs)
{
    cout << " Move Copy Constructor" << endl;
    this->ptr = rhs.ptr;
    this->ref = rhs.ref;
    rhs.ptr = nullptr;
    rhs.ref = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
void mySharedPtr<T>::operator=(mySharedPtr &&rhs)
{
    cout << this->name << " Move Assignment Operator" << endl;
    *this->ref = *this->ref - 1;
    if (*this->ref < 1)
    {
        delete this->ptr;
        delete this->ref;
    }

    this->ptr = rhs.ptr;
    rhs.ptr = nullptr;

    this->ref = rhs.ref;
    rhs.ref = nullptr;
}

//------------------------------------------------------------------------------------------------------------------------------
template <class T>
T *mySharedPtr<T>::operator->()
{
    if (nullptr == this->ptr)
    {
        cout << "!!! WARNING -- NULL POINTER !!!\n";
    }
    return this->ptr;
}

//------------------------------------------------------------------------------------------------------------------------------
template <class T>
T &mySharedPtr<T>::operator*()
{
    if (nullptr == this->ptr)
    {
        cout << "!!! WARNING -- NULL POINTER !!!\n";
    }
    return *(this->ptr);
}
//==============================================================================================================================
int main(int argc, const char *argv[])
{
    // insert code here...
    std::cout << "\n\n~~~~~~~~~~~~~~~Shared Pointer class Implementation~~~~~~~~~~~~~~~\n\n";
    {
        mySharedPtr<dummy> p3;
        {
            mySharedPtr<dummy> p1(new dummy(10, 20));
            mySharedPtr<dummy> p2;
            p2 = p1;
            p3 = p2;
            mySharedPtr<dummy> p4 = p3;
        }
        cout << p3->sum() << endl;
    }
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    return 0;
}
//==============================================================================================================================