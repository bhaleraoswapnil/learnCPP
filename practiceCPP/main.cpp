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
    dummy(int x, int y) : a(x), b(y) { cout << "dummy object constructor\n"; }
    ~dummy() { cout << "dummy object deleted\n"; }
    int sum() { return (a + b); }
};
//==============================================================================================================================
template <class T>
class myUniquePtr
{
private:
    T *ptr;
    string name = "*";

public:
    myUniquePtr(string);
    myUniquePtr(T *, string);
    ~myUniquePtr();
    myUniquePtr(myUniquePtr &&);
    void operator=(myUniquePtr &&);
    myUniquePtr(const myUniquePtr &) = delete;
    myUniquePtr &operator=(const myUniquePtr &) = delete;
    T *operator->();
    T &operator*();
    void setObjectName(string s) { this->name = s; }
};
//==============================================================================================================================
template <class T>
myUniquePtr<T>::myUniquePtr(string s)
{
    this->name = s;
    cout << this->name << " myUniquePtr Default Constructor " << endl;
    this->ptr = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myUniquePtr<T>::myUniquePtr(T *p, string s)
{
    this->name = s;
    cout << this->name << " myUniquePtr Parameter Constructor " << endl;
    this->ptr = p;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myUniquePtr<T>::~myUniquePtr()
{
    cout << this->name << " myUniquePtr Destructor " << endl;
    if (nullptr != this->ptr)
    {
        delete this->ptr;
    }
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
myUniquePtr<T>::myUniquePtr(myUniquePtr &&rhs)
{
    cout << this->name << " Move Copy Constructor" << endl;
    this->ptr = rhs.ptr;
    rhs.ptr = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
void myUniquePtr<T>::operator=(myUniquePtr &&rhs)
{
    cout << this->name << " Move Assignment Operator" << endl;
    delete[] this->ptr;
    this->ptr = rhs.ptr;
    rhs.ptr = nullptr;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
T *myUniquePtr<T>::operator->()
{
    if (this->ptr == nullptr)
    {
        cout << "!!! WARNING -- NULL POINTER !!!\n";
    }
    return this->ptr;
}
//------------------------------------------------------------------------------------------------------------------------------
template <class T>
T &myUniquePtr<T>::operator*()
{
    return *(this->ptr);
}
//==============================================================================================================================
int main(int argc, const char *argv[])
{
    // insert code here...
    std::cout << "\n\n~~~~~~~~~~~~~~~Unique Pointer class Implementation~~~~~~~~~~~~~~~\n\n";
    {
        myUniquePtr<dummy> p1(new dummy(10, 20), "p1");
        cout << "p1 sum == " << p1->sum() << endl;

        myUniquePtr<dummy> p2(new dummy(1, 2), "p2");
        cout << "p2 sum == " << p2->sum() << endl;

        myUniquePtr<dummy> p3("p3");
        p3 = move(p2);
        cout << "p3 sum == " << p3->sum() << endl;

        myUniquePtr<dummy> p4(move(p1));
        p4.setObjectName("p4");
        cout << "p4 sum == " << p4->sum() << endl;
    }
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    return 0;
}
//==============================================================================================================================