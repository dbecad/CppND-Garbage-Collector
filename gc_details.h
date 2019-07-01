#pragma once
#include <iostream>
#include <assert.h>

// This class defines an element that is stored
// in the garbage collection information list.
//
template <class T>
class PtrDetails
{
  public:
    unsigned refcount; // current reference count
    T *memPtr;         // pointer to allocated memory
    
    // isArray is true if memPtr points to an allocated array. It is false otherwise.
    bool isArray; // true if pointing to array

    // If memPtr is pointing to an allocated array, then arraySize contains its size
    unsigned arraySize; // size of array

    // Here, mPtr points to the allocated memory.
    // If this is an array, then size specifies the size of the array.
    PtrDetails(T *ptr, unsigned size = 0)
    {
        //save reference to the pointer
        refcount = 1;
        memPtr = ptr;

        //Array related members
        arraySize = size;
        isArray = (size != 0);
    }
};

// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    if (ob1.memPtr == ob2.memPtr)
    {
        //Array members should also match
        if ((ob1.isArray != ob2.isArray) || (ob1.arraySize != ob2.arraySize))
            throw std::runtime_error("Objects refering to same location do not agree on array properties");
        return true;
    }
 
    return false;
}

//Test function
void testPtrDetails() {
    cout << "Testing PtrDetails..." << endl; 
    int *p1 = new int(5);
    PtrDetails<int> d1(p1);
    PtrDetails<int> d2(p1);
    assert(d1 == d2);

    int *p2 = new int[10];
    int *p3 = new int[10];
    PtrDetails<int> d3(p2, 10);

    //Corruption test!
    PtrDetails<int> d4(p2, 5);
    bool catchExcept = false;
    try {
        assert(d3 == d4);
    }
    catch(const std::runtime_error& e) {
        cerr << "   "<< e.what() << '\n';
        catchExcept = true;
    }
    assert(catchExcept == true);

    //Different vector
    PtrDetails<int> d5(p3, 10);
    assert(!(d3 == d5));    
    cout << "   Done..." << endl; 
}