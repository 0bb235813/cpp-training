#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <new>
#include <utility>

template <typename T>
class Vector
{
public:
    Vector (std::initializer_list<T> list) : size_(list.size()), capacity_(list.size())
    {
        ptr = (T*)::operator new(sizeof(T)*capacity_);
        for (int i{}; i < capacity_; ++i)
        {
            new(ptr+i) T(*(list.begin()+i));
        }
    }

    Vector (int size) : size_(size), capacity_(size)
    {
        ptr = (T*)operator new(sizeof(T)*capacity_);
        for (int i{}; i < size; ++i)
            new(ptr+i) T();
    }

    Vector (int size, T value) : size_(size), capacity_(size)
    {
        ptr = (T*)operator new(sizeof(T)*capacity_);
        for (int i{}; i < size; ++i)
            new(ptr+i) T(value);
    }

    Vector (const Vector& other) : size_(other.size_), capacity_(other.capacity_)
    {
        ptr = (T*)operator new(sizeof(T)*other.capacity_);
        for (int i{}; i < size_; ++i)
            new(ptr+i) T(other.ptr[i]);
    }

    Vector (Vector&& other) : size_(other.size_), capacity_(other.capacity_)
    {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    void print()
    {
        for (int i{}; i < size_; ++i)
            std::cout << ptr[i] << std::endl;
    }

    void push_back(T value) 
    {
        if (capacity_ == size_) vecrotFull();
        new(ptr+size_) T(value);
        ++size_;
    }

    T operator[](int index)
    {
        return ptr[index];
    }

    ~Vector ()
    {

        for (int i{}; i < size_; ++i)
            ptr[i].~T();

        operator delete(ptr);
    }

    size_t size () { return size_; }
    size_t capacity() { return capacity_; }

private:
    void vecrotFull()
    {
        capacity_*=2;
        T* temp = (T*)operator new(sizeof(T)*capacity_);
        for (int i{}; i < size_; ++i)
        {
            new(temp+i) T(ptr[i]);
            //if (i < size_) new(temp+i) T(ptr[i]);
            //else new(temp+i) T();
        }
        std::swap(temp, ptr);
        for (int i{}; i < size_; ++i)
            temp[i].~T();
        operator delete(temp);
    }
    T* ptr;
    size_t size_{};
    size_t capacity_{};
};

int main()
{
}
