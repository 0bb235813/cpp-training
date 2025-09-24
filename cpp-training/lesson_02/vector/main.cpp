#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <typename T>
class MyVector
{
public:
    MyVector (initializer_list<T> list) 
    {
        cout << "DEFAULT CONSTRUCTOP" << endl;
        size_ = capacity_ = list.size();
        ptr = make_unique<T[]>(size_);
        for (int i{}; i < list.size(); ++i)
            ptr[i] = *(list.begin()+i);
    }

    MyVector (int size)
    {
        size_ = capacity_ = size;
        ptr = make_unique<T[]>(size_);
        for (int i{}; i < size; ++i)
            ptr[i] = 0;
    }

    MyVector (int size, int value)
    {
        size_ = capacity_ = size;
        ptr = make_unique<T[]>(size);
        for (int i{}; i < size; ++i)
            ptr[i] = value;
    }

    MyVector (const MyVector& other)
    {
        cout << "COPY CONSTRUCTOP" << endl;
        capacity_ = other.capacity_;
        size_ = other.size_;
        ptr = make_unique<T[]>(size_);
        for (int i{}; i < size_; ++i)
            ptr[i] = other.ptr[i];
    }

    MyVector (MyVector&& other)
    {
        cout << "MOVE CONSTRUCTOP" << endl;
        capacity_ = other.capacity_;
        size_ = other.size_;
        ptr.swap(other.ptr);
    }

    void print()
    {
        for (int i{}; i < size_; ++i)
            cout << ptr[i] << endl;
    }

    void push_back(T value) 
    {
        if (capacity_ == size_) vecrotFull();
        ptr[size_] = value;
        ++size_;
    }

    T operator[](int index)
    {
        return ptr[index];
    }

    size_t size () { return size_; }
    size_t capacity() { return capacity_; }

private:
    void vecrotFull()
    {
        capacity_*=2;
        unique_ptr<T[]> temp = make_unique<T[]>(capacity_);
        ptr.swap(temp);
        for (int i{}; i < capacity_; ++i)
        {
            if (i < size_) ptr[i] = temp[i];
            else ptr[i] = 0;
        }
    }
    unique_ptr<T[]> ptr;
    //T* ptr;
    size_t size_{};
    size_t capacity_{};
};

int main()
{
    MyVector<int> vec(MyVector<int>({1,2,3,4,5}));
    vec.print();
}
