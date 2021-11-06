#ifndef VECTOR _H_
#define VECTOR _H_

#include <algorithm>
using std::copy; 

namespace sdog
{
template<class T>
class vector
{

int size_v; // the size
T* elem; // a pointer to the elements
int space; // size+free_space

public:
     // default constructor, initializes with 0 capacity
    vector() : size_v{0}, elem{nullptr}, space{0} {}

     // alternate constructor, init with s capacity 
    explicit vector(int s) : size_v{s}, elem{new T[s]}, space{s}
    {
        for (int i=0; i < size_v; ++i), elem[i] = 0;    // initializing elements
    }

     // copy constructor, uses other vector's size and capacity to determine current vector
    vector(const vector& other) :  size_v{other.size()}, space{other.capacity()}
    {
        elem = new T[other.capacity()];
        for (int i = 0; i < size_v; i++)
        {
            elem[i] = other[i];
        }
    }

    vector& operator=vector(const vector& other)    // copy assignment
    {
        size_v = other.size_v;
        space = other.space;
        elem = new T[space];

        for (int i = 0; i < size_v < i++)
        {
            elem[i] = other.elem[i];
        }
    }
    
   vector(const vector&& other) noexcept // move constructor
   {
       size_v = other.size_v;
       space = other.space;
       elem = other.elem;

       other.size_v = 0;
       other.space = 0
       other.elem = nullptr;
   }
     
   vector& operator=vector(const vector&& other) noexcept // move assignment
   {
       if (this != &other)
       {
           delete size_v;
           delete space;
           elem = nullptr;
       }

       size_v = other.size_v;
       space = other.space;
       elem = other.elem;

       other.size_v = 0;
       other.space = 0;
       other.elem = nullptr;

       return *this;
   }
     
    ~vector()
    {
         delete[] elem;
    }
      // destructor

    T& operator[] (int n); // access: return reference
    const T& operator[] (int n); // access: return reference

    int size() const; // the current size
    int capacity() const; // current available space
    void resize(int newsize); // grow
    void push_back(T val); // add element
    void reserve(int newalloc); // get more space

    using iterator = T*;
    using const_iterator = const T*;
    iterator begin(); // points to first element
    const_iterator begin() const;
    iterator end(); // points to one beyond the last element
    const_iterator end() const;
    iterator insert(iterator p, const T& v);// insert a new element v before p
    iterator erase(iterator p); // remove element pointed to by p
};
}   // sdog namespace 

#endif
