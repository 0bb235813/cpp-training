#include <cassert>
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
        int i{};
        try {
            for (; i < capacity_; ++i)
            {
                new(ptr+i) T(*(list.begin()+i));
            }
        } catch (...) {
            for (int j{}; j < i; ++j)
                ptr[j].~T();
            operator delete(ptr);
            throw;
        }
    }

    Vector (int size) : size_(size), capacity_(size)
    {
        ptr = (T*)operator new(sizeof(T)*capacity_);
        int i{};
        try {
            for (; i < capacity_; ++i)
               new(ptr+i) T();
        } catch (...) {
           for (int j{}; j < i; ++j)
                ptr[j].~T();
            operator delete(ptr);
            throw;
        }
    }

    Vector (int size, T value) : size_(size), capacity_(size)
    {
        ptr = (T*)operator new(sizeof(T)*capacity_);
        int i{};
        try {
            for (int i{}; i < capacity_; ++i)
                new(ptr+i) T(value);
        } catch (...) {
            for (int j{}; j < i; ++j)
                ptr[j].~T();
            operator delete(ptr);
            throw;
        }
    }

    Vector (const Vector& other) : size_(other.size_), capacity_(other.capacity_)
    {
        ptr = (T*)operator new(sizeof(T)*other.capacity_);
        int i{};
        try {
            for (; i < size_; ++i)
                new(ptr+i) T(other.ptr[i]);
        } catch (...) {
            for (int j{}; j < i; ++j)
                ptr[j].~T();
            operator delete(ptr);
            throw;
        }
    }

    Vector (Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), ptr(other.ptr)
    {
        other.ptr = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
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

    T& operator[](int index)
    {
        return ptr[index];
    }

    ~Vector ()
    {

        for (int i{}; i < size_; ++i)
            ptr[i].~T();

        operator delete(ptr);
    }

    size_t size () const { return size_; }
    size_t capacity() const { return capacity_; }

private:
    void vecrotFull()
    {
        capacity_*=2;
        T* temp = (T*)operator new(sizeof(T)*capacity_);
        int i{};
        try {
            for (; i < size_; ++i)
            {
                new(temp+i) T(ptr[i]);
                //if (i < size_) new(temp+i) T(ptr[i]);
                //else new(temp+i) T();
            }
        } catch (...) {
            for (int j{}; j < i; ++j)
                temp[j].~T();
            operator delete(temp);
            throw;
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

void test_push_back()
{
    Vector<int> vec(2);
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    assert(vec.size() == 5);
    assert(vec.capacity() == 8);
    assert(vec[2] == 10);
    assert(vec[3] == 20);
    assert(vec[4] == 30);
}

void test_constreuctor()
{
    Vector<int> vec(3, 84);
    assert(vec.size() == 3);
    assert(vec.capacity() == 3);
    assert(vec[0] == 84);
    assert(vec[1] == 84);
    assert(vec[2] == 84);
}

void test_initializer_list()
{
    Vector<int> vec {1,2,3,4,5};
    assert(vec.size() == 5);
    assert(vec.capacity() == 5);

    for (int i{}; i < 5; ++i)
        assert(vec[i] == i+1);
}

void test_copy_constructor()
{
    Vector<int> vec {1,2,3};
    Vector<int> copy(vec);

    assert(copy.size() == 3);
    assert(copy.capacity() == 3);

    for (int i{}; i < 3; ++i)
    {
        assert(vec[i] == i+1);
        assert(copy[i] == i+1);
    }

    copy[0] = 5;
    assert(copy[0] == 5);
    assert(vec[0] == 1);
}

void test_move_constructor()
{
    Vector<int> vec {1,2,3};
    Vector<int> move (std::move(vec));

    assert(move[0] == 1);
    assert(move[1] == 2);
    assert(move[2] == 3);
    
    assert(vec.size() == 0 && vec.capacity() == 0);
}

void test()
{
    class TestClass
    {
    public:
        TestClass() {
            throw "Copy ERROR";
        }
    };


    try {
        Vector<TestClass> vec(5);
    } catch (const char* e) {
        std::cout << e << std::endl;
        assert(std::string(e) == "Copy ERROR");
    }
}

int main()
{
    test_constreuctor();
    test_copy_constructor();
    test_initializer_list();
    test_push_back();
    test_move_constructor();
    test();

    std::cout << "All tests passed" << std::endl;
}
