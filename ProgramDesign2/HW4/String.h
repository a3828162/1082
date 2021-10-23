// string internal header

#ifndef STRING
#define STRING

#include <cstddef>

// CLASS StringVal
class StringVal
{
public:
   using value_type = char;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   StringVal()
      : bx(),
        mySize( 0 ),
        myRes( 15 )
   {
   }

   value_type* myPtr()
   {
      if( myRes < 16 )
         return bx.buf;
      else
         return bx.ptr;
   }

   const value_type* myPtr() const
   {
      if( myRes < 16 )
         return bx.buf;
      else
         return bx.ptr;
   }

   union Bxty // storage for small buffer or pointer to larger one
   {
      value_type buf[ 16 ];
      pointer ptr;
   } bx;

   size_type mySize; // current length of string
   size_type myRes;  // current storage reserved for string
};

class string // null-terminated transparent array of elements
{
   using ScaryVal = StringVal;

public:
   using value_type = char;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty string constructor (default constructor)
   // Constructs an empty string, with a length of zero characters.
   string();

   // from buffer
   // Copies the first "count" characters from the array of characters pointed by ptr.
   string( const char *const ptr, const size_type count );

   // fill constructor
   // Fills the string with "count" consecutive copies of character ch.
   string( const size_type count, const char ch );

   // copy constructor
   // Constructs a copy of "right".
   string( const string &right );

   // String destructor
   // Destroys the string object.
   // Deallocates all the storage capacity allocated by the string.
   ~string();

   // String assignment
   // Assigns a new value to the string, replacing its current contents.
   string &operator=( const string &right );

   // Inserts character ch into the string right before the character
   // indicated by "where".
//   iterator insert( const_iterator where, const char ch );

   // Erases the character pointed by p.
//   iterator erase( const_iterator where );

   // Erases the contents of the string, which becomes an empty string
   // (with a length of 0 characters).
   void clear(); // erase all

   // Returns an iterator pointing to the first character of the string.
   iterator begin();

   // Returns an iterator pointing to the first character of the string.
   const_iterator begin() const;

   // Returns an iterator pointing to the past-the-end character of the string.
   // The past-the-end character is a theoretical character
   // that would follow the last character in the string.
   // It shall not be dereferenced.
   // If the object is an empty string, this function returns the same as string::begin.
   iterator end();

   // Returns an iterator pointing to the past-the-end character of the string.
   // The past-the-end character is a theoretical character
   // that would follow the last character in the string.
   // It shall not be dereferenced.
   // If the object is an empty string, this function returns the same as string::begin.
   const_iterator end() const;

   // Returns a const_iterator pointing to the first character of the string.
   const_iterator cbegin() const;

   // Returns a const_iterator pointing to the past-the-end character of the string.
   // If the object is an empty string, this function returns the same as string::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const;

   // Returns a reference to the character at position pos in the string.
   reference operator[]( const size_type off );

   // Returns a reference to the character at position pos in the string.
   const_reference operator[]( const size_type off ) const;

   // Appends character ch to the end of the string, increasing its length by one.
   void push_back( char ch );

   // Erases the last character of the string,
   // effectively reducing its length by one.
   void pop_back();

   // Returns a reference to the first character of the string.
   // This function shall not be called on empty strings.
   reference front();

   // Returns a reference to the first character of the string.
   // This function shall not be called on empty strings.
   const_reference front() const;

   // Returns a reference to the last character of the string.
   // This function shall not be called on empty strings.
   reference back();

   // Returns a reference to the last character of the string.
   // This function shall not be called on empty strings.
   const_reference back() const;

   // Returns a pointer to an array that contains a null-terminated sequence of characters
   // (i.e., a C-string) representing the current value of the string object.
   const char* c_str() const;

   // Returns the length of the string, in terms of bytes.
   // This is the number of actual bytes that conform the contents of the string,
   // which is not necessarily equal to its storage capacity.
   size_type size() const;

   // Resizes the string to a length of "newSize" characters.
   // If "newSize" is smaller than the current string length,
   // the current value is shortened to its first "newSize" character,
   // removing the characters beyond the "newSize"th.
   // If "newSize" is greater than the current string length,
   // the current content is extended by inserting at the end
   // as many characters as needed to reach a size of "newSize".
   // The new elements are initialized as copies of ch,
   void resize( const size_type newSize, const char ch = char() );

   // Returns the size of the storage space currently allocated for the string,
   // expressed in terms of bytes.
   // This capacity is not necessarily equal to the string length.
   // It can be equal or greater, with the extra space allowing the object
   // to optimize its operations when new characters are added to the string.
   size_type capacity() const;

   // Returns whether the string is empty (i.e. whether its length is 0).
   bool empty() const;

   // compare [ 0, size() ) with right for equality
   bool equal( const string &right ) const;

private:
   ScaryVal myData;
};

bool operator==( const string &left, const string &right );

#endif // STRING