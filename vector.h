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

    // originally const - changed for the sake of testing the parser
    vector(vector&& other) noexcept // move constructor
   {
       size_v = other.size_v;
       space = other.space;
       elem = other.elem;

       other.size_v = 0;
       other.space = 0;
       other.elem = nullptr;
   }


   vector& operator=(vector&& other) noexcept // move assignment
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
        if (newsize > space)
        {
            for (int i = 0; i < size_v; i++)
            {
                temp[i] = elem[i];
            }
        }
        // if number of elements in old vector is greater than the new capacity
        // i.e. more elements than space, cannot copy over elements normally
        else
        {
            size_v = 0; // size_v is set to newsize so that we do not copy over more elements than new capacity

            // copy elements in vector up to the new capacity
            for (int i = 0; i < newsize; i++)
            {
                temp[i] = elem[i];
                if (elem[i])
                {
                    size_v++;
                }
            }
        }

        space = newsize;
        delete[] elem; // delete old elem
        elem = temp; // elem is now a vector with new capacity
    }

    void push_back(T val) // add element
    {
        //check to see whether the vector has room for a new element
        if (size_v < space)
        {
            elem[size_v] = val; // insert val into vector
            size_v++; // increment size of vector
        }
    }

    void reserve(int newalloc) // get more space
    {
        if (newalloc != space)
        {
            if (newalloc > space)
            {
                space = newalloc;
                T* temp = new T[space]; // create temp vector with new capacity

                // copy elements into temp vector
                for (int i = 0; i < size_v; i++)
                {
                    temp[i] = elem[i];
                }

                delete[] elem; // delete old elem
                elem = temp; // elem is now a vector with updated capacity
            }
        }
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
        T temp;
        T temp2;
        int diff = &elem[space - 1] - p;

        if (size_v + 1 <= space)
        {
            temp = *p;
            for (int i = 0; i < diff; i++)
            {
                temp2 = *(p + 1);
                p = p + 1;
                *p = temp;
                temp = temp2;
            }

            for (int revert = 0; revert < diff; revert++)
            {
                p = p + 1;
            }
            *p = v;
            size_v++;
        }
        return p;
    }

    iterator erase(iterator p) // remove element pointed to by p
    {
        T temp;
        int diff = &elem[size_v - 1] - p;

        *p = 0;
        for(int i = 0; i < diff; i++)
        {
            temp = *(p + 1);
            *p = temp;
            p = p + 1;
        }
        *p = 0;

        for (int revert = 0; revert < diff; revert++)
        {
            p = p - 1;
        }
        size_v--;

        return p;
    }
};
}   // sdog namespace

#endif
