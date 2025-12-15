#include "vector_impl.h"


Vector::Vector() : capicity{0}, vec_size{0}, array{nullptr} {}

Vector::Vector(long int vec_size){
    if (vec_size < 0L)
        throw std::out_of_range("Size of array out of range " + std::to_string(vec_size));
    
    this -> vec_size = static_cast<size_t>(vec_size);
    if (this -> vec_size > MAX_VEC_SIZE) 
        throw std::length_error("Requested vector size is too large");

    capicity = this -> vec_size;
    array = new int[capicity]();
}

Vector::Vector(std::initializer_list<int> ls)
    : Vector(static_cast<int>(ls.size()))
{
    if (ls.size() > static_cast<size_t>(MAX_VEC_SIZE)) {
        throw std::length_error("Initializer list too large");
    }
    std::copy(ls.begin(), ls.end(), array);
}

Vector::~Vector()
{
    delete[] array;  
}
 
Vector::Vector(const Vector& other) 
    : capicity{other.capicity}, vec_size{other.vec_size}, array{nullptr}
{
    array = new int[capicity]();
    std::copy(other.array, other.array + other.vec_size, array);
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)                         
        return *this;
    
    delete[] array;
    
    capicity = other.capicity;
    vec_size = other.vec_size;
    
    array = new int[other.capicity]();
    std::copy(other.array, other.array + other.vec_size, array);
    
    return *this;
}

size_t Vector::Size() const
{
    return vec_size;
}


void Vector::Swap(Vector& other)
{
    std::swap(capicity, other.capicity);
    std::swap(vec_size, other.vec_size);
    std::swap(array, other.array);
}

int& Vector::operator[](const size_t index)
{
    return array[index];
}

const int& Vector::operator[](const size_t index) const
{
    return array[index];
}

int& Vector::At(const int index)
{
    indexOutOfRange(vec_size, index);
    return array[index];   
}

const int& Vector::At(const int index) const
{
    indexOutOfRange(vec_size, index);
    return array[index];   
}

void Vector::indexOutOfRange(size_t vec_size, const int index) const
{
    if (index < 0)
        throw std::out_of_range("Index = " + std::to_string(index) + "< 0");
    if (static_cast<size_t>(index) >= vec_size)  
        throw std::out_of_range("Index= " + std::to_string(index) + " >= size of array " + std::to_string(vec_size));
    if (static_cast<size_t>(index) > MAX_VEC_SIZE)  
        throw std::out_of_range("Index= " + std::to_string(index) + " Is so big, need < " + std::to_string(MAX_VEC_SIZE));
}


size_t Vector::Capacity() const
{
    return capicity;
}

void Vector::PushBack(int num)
{
    if (vec_size >= capicity){
        size_t new_capicity = (capicity == 0) ? 1 : capicity * 2;
        if (new_capicity > MAX_VEC_capicity)
            throw std::length_error("Your array is very big, need smaller than " + std::to_string(MAX_VEC_capicity));
        
        int* new_array = new int[new_capicity];
        std::copy(array, array + vec_size, new_array);
        delete[] array;
        
        capicity = new_capicity;
        array = new_array;
    }

    array[vec_size] = num;
    vec_size++;
}

void Vector::PopBack()
{
    if (vec_size > 0)
        vec_size--;
    else
        throw std::out_of_range("Out of range! Your try to delete a element in empty array");
}

void Vector::Clear()
{
    vec_size = 0;
}

void Vector::Reserve(int new_capacity)
{
    if (new_capacity < 0)
        throw std::out_of_range("Negative capacity: " + std::to_string(new_capacity));
    
    size_t u_capacity = static_cast<size_t>(new_capacity);
    if (u_capacity > MAX_VEC_capicity)
        throw std::length_error("Capacity too large: " + std::to_string(new_capacity));
    
    if (u_capacity > capicity) {
        int* new_array = new int[u_capacity];
        std::copy(array, array + vec_size, new_array);
        delete[] array;
        array = new_array;
        capicity = u_capacity;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector& vec)
{
    os << '[';
    for (size_t i = 0; i < vec.Size(); i++){  
        if (i > 0) os << ", ";
        os << vec[i];
    }
    os << ']';
    return os;
}