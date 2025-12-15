#pragma once
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstddef>

class Vector {
private:
    size_t capicity;
    size_t vec_size;
    int* array;
    void indexOutOfRange(size_t, const int) const;
    static const size_t MAX_VEC_SIZE = 10000;
    static const size_t MAX_VEC_capicity = 200000;
public:
    Vector();
    explicit Vector(long int size);
    Vector(std::initializer_list<int>);

    ~Vector();
    Vector(const Vector&);
    Vector& operator=(const Vector&);

    void Swap(Vector&);
    int& operator[](const size_t);
    const int& operator[](const size_t) const;

    int& At(const int);
    const int& At(const int) const;

    size_t Size() const;
    size_t Capacity() const;

    void PushBack(int);
    void PopBack();
    void Clear();
    void Reserve(int);          
};

std::ostream& operator<<(std::ostream& os, const Vector& vec);