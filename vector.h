#ifndef VECTOR_H_
#define VECTOR_H_

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
    explicit vector(int s) : size_v{0}, elem{new T[s]}, space{s} {}

     // copy constructor, uses other vector's size and capacity to determine current vector
    vector(const vector& other) :  size_v{other.size_v}, space{other.space}
    {
        elem = new T[other.space];
        for (int i = 0; i < size_v; i++)
        {
            elem[i] = other[i];
        }
    }

    vector& operator=(const vector& other)    // copy assignment
    {
        size_v = other.size_v;
        space = other.space;
        elem = new T[space];

        for (int i = 0; i < size_v; i++)
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
       other.space = 0;
       other.elem = nullptr;
   }
     
   vector& operator=(const vector&& other) noexcept // move assignment
   {
       if (this != &other)
       {
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

    T& operator[] (int n) // access: return reference
    {
        return elem[n]; // element returned is modifiable
    }

    const T& operator[] (int n) const // access: return reference
    {
        return elem[n]; // element returned is const and non-modifiable
    }

    int size() const // the current size
    {
        return size_v;
    } 
   
    int capacity() const // current available space
    {
        return space;
    }

    void resize(int newsize) // grow
    {
        T* temp = new T[newsize]; // create temp vector with new newsize as capacity

        // if the new capacity is larger than old vector or the number of elements
        // in old vector is less than the new capacity, can copy over elements normally
        if (space < newsize || size_v < newsize)
        {
            for (int i = 0; i < size_v; i++)
            {
                temp[i] = elem[i];
            }
        }
        // if number of elements in old vector is greater than the new capacity
        // i.e. more elements than space, cannot copy over elements normally
        else if (space > newsize && size_v > newsize)
        {
            size_v = newsize; // size_v is set to newsize so that we do not copy over more elements than new capacity

            // copy elements in vector up to the new capacity
            for (int i = 0; i < size_v; i++)
            {
                temp[i] = elem[i];
            }
        }
        
        delete[] elem; // delete old elem
        elem = temp; // elem is now a vector with new capacity
        space = newsize; // assign newsize to space
    }

    void push_back(T val) // add element
    {
        // check to see whether the vector has room for a new element
        if (size_v + 1 > space)
        {
            reserve(1); // if not call reserve to increase vector's capacity by 1
        }

        elem[size_v] = val; // insert val into vector
        size_v++; // increment size of vector
    }

    void reserve(int newalloc) // get more space
    {
        space = space + newalloc; // increase capacity by newalloc

        T* temp = new T[space]; // create temp vector with new capacity

        // copy elements into temp vector
        for (int i = 0; i < size_v; i++)
        {
            temp[i] = elem[i];
        }

        delete[] elem; // delete old elem
        elem = temp; // elem is now a vector with updated capacity
    }

    using iterator = T*;
    using const_iterator = const T*;
    iterator begin() // points to first element
    {
        if (size_v == 0)
        {
            return nullptr;
        }
        return &elem[0];
    }

    const_iterator begin() const
    {
        if (size_v == 0)
        {
            return nullptr;
        }
        return &elem[0];
    }

    iterator end() // points to one beyond the last element
    {
        if (size_v == 0)
        {
            return nullptr;
        }
        return &elem[size_v];
    }

    const_iterator end() const
    {
        if (size_v == 0)
        {
            return nullptr;
        }
        return &elem[size_v];
    }

    iterator insert(iterator p, const T& v)// insert a new element v before p
    {
        // check if there is space
        if (size_v != space)
        {
            iterator index = p - 1; // index is 1 place before p
            ++size_v; // increment size since we are inserting an element

            // set pos to be the final element and loop through, shifting
            // all elements from the index upwards by 1
            for (iterator pos = end() - 1; pos != index; --pos)
            {
                *pos = *(pos - 1); // copy element one position to the right
            }

            *index = v; // insert element at the index
        }

        return p;
    }

    iterator erase(iterator p) // remove element pointed to by p
    {
        if (p == end())
        {
            return p;
        }

        for (iterator pos = p + 1; pos != end(); ++pos)
        {
            *(pos - 1) = *pos; // copy element one position to the left
        }

        // delete (end() - 1)
        --size_v;
        return p;
    }
};
}   // sdog namespace 

#endif
