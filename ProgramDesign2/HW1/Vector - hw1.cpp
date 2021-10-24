#include "Vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
    //myFirst = myLast = myEnd = nullptr;
    value_type* str = new value_type[count]();
    delete myFirst;
    myFirst = str;
    myEnd = myLast = str + count;


}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    //myFirst = myLast = myEnd = nullptr;
    value_type s = right.myLast - right.myFirst;
    value_type c = right.myEnd - right.myFirst;
    value_type* str = new value_type[s]();
    delete myFirst;
    myFirst = str;
    myLast = str + s;
    myEnd = str + s;

    if (right.myFirst != nullptr) {
        for (value_type i = 0; i < s; i++) 
            str[i] = *(right.myFirst + i);
    }
    else {
        myFirst = nullptr;
        myLast = nullptr;
        myEnd = nullptr;
    }
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
   size_type originalSize = size();
   resize( originalSize + 1 );
   myFirst[ originalSize ] = val;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
       value_type right_s = right.myLast - right.myFirst;
       value_type right_c = right.myEnd - right.myFirst;

       if (myFirst == nullptr)
       {
           value_type* str = new value_type[right_s]();
           delete myFirst;
           myFirst = str;
           myLast = str + right_s;
           myEnd = str + right_s;

           for (value_type i = 0; i < right_s; i++)
               str[i] = *(right.myFirst + i);
       }
       else
       {
           if (right_s > capacity())
           {
               value_type of = capacity() * 1.5;
               if (of <= right_s) {
                   value_type* str = new value_type[right_s]();   
                   delete myFirst;
                   myFirst = str;
                   myLast = str + right_s;
                   myEnd = str + right_s;
                   for (value_type i = 0; i < right_s; i++)
                       str[i] = *(right.myFirst + i);
               }
               else {
                   value_type* str = new value_type[of]();
                   delete myFirst;
                   myFirst = str;
                   myLast = str + right_s;
                   myEnd = str + of;
                   for (value_type i = 0; i < right_s; i++)
                       str[i] = *(right.myFirst + i);
               }
           }
           else
           {
               myLast = myFirst + right_s;

               for (value_type i = 0; i < right_s; i++)
                   *(myFirst + i) = *(right.myFirst + i);
           }
       }
   }

   return *this; // enables x = y = z, for example
}

// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize( const size_type newSize )
{
    if (newSize > capacity())
    {
        value_type of = capacity() * 1.5;
        if (of <= newSize) {

            value_type* str = new value_type[newSize]();
            myEnd = str + newSize;
            for (value_type i = 0; i < size(); i++)
                str[i] = *(myFirst + i);
            //clear();
            delete myFirst;
            myFirst = str;
            myLast = str + newSize;
        }
        else {
            value_type* str = new value_type[of]();
            myEnd = str + of;
            for (value_type i = 0; i < size(); i++)
                str[i] = *(myFirst + i);
            //clear();
            delete myFirst;
            myFirst = str;
            myLast = str + newSize;
        }
    }
    else
    {
        myLast = myFirst + newSize;
    }
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
      --myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::pointer vector::begin()
{
   return myFirst;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return ( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return ( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element( const size_type pos )
{
   return myFirst[ pos ];
}