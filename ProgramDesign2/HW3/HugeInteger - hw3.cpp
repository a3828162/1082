// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{
    HugeInteger int1(*this);
    HugeInteger int2(right);

    unsigned int size1 = integer.size();
    unsigned int size2 = right.integer.size();

    vector::iterator it1 = int1.integer.end()-1;
    vector::iterator it2 = int2.integer.end()-1;

    if (size1 == size2)
    {
        for (; it1 >= int1.integer.begin(); --it1, --it2)
        {
            if (*it1 != *it2)
                return false;
        }

        return true;
    }
    else
    {
        return false;
    }
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{
    HugeInteger int1(*this);
    HugeInteger int2(right);

    unsigned int size1 = integer.size();
    unsigned int size2 = right.integer.size();

    vector::iterator it1 = int1.integer.end()-1;
    vector::iterator it2 = int2.integer.end()-1;

    if (size1 > size2)
        return false;
    else if (size1 < size2)
        return true;
    else
    { 
        for (; it1 >= int1.integer.begin(); --it1, --it2)
        {
            if (*it1 > *it2)
                return false;
            else if (*it1 < *it2)
                return true;
            else if (*it1 == *it2)
                continue;
        }

        return false;
    }

} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract( HugeInteger &op2 )
{
   HugeInteger zero;

   if( equal( op2 ) )
      return zero;

   HugeInteger difference( *this );

   vector::iterator it1 = op2.integer.begin();
   vector::iterator it2 = difference.integer.begin();

   for (; it1 != op2.integer.end(); ++it1, ++it2)
       *it2 -= *it1;

   for (it2 = difference.integer.begin(); it2 < difference.integer.end(); ++it2)
   {
       if (*it2 < 0)
       {
           *it2 += 10;
           *(it2 + 1) -= 1;
       }
   }

   for (it2 = difference.integer.end() - 1; *it2 == 0; --it2)
       difference.integer.pop_back();

   return difference;

} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );
   
   vector::iterator it1 = integer.begin();
   vector::iterator it2 = op2.integer.begin();
   vector::iterator it3 = product.integer.begin();

    for (unsigned int i = 0; i < integer.size(); ++i)
        for (unsigned int j = 0; j < op2.integer.size(); ++j)
            *(it3 + i + j) += *(it1 + i) * *(it2 + j);

    for (it3 = product.integer.begin(); it3 < product.integer.end(); ++it3)
        if (*it3 >= 10) 
        {
            *(it3 + 1) += *(it3) / 10;
            *(it3) %= 10;
        }

    for (it3 = product.integer.end() - 1; *it3 == 0; --it3)
        product.integer.pop_back();

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide(HugeInteger& op2)
{
    HugeInteger zero;
    if (less(op2))
        return zero;
    HugeInteger quotient;

    /*if (equal(op2))
    {
        quotient.integer.begin()[0] = 1;
        return quotient;
    }*/

    HugeInteger  remainder(*this);

    unsigned int dividendSize = integer.size();
    unsigned int divisorSize = op2.integer.size();
    unsigned int quotientSize = quotient.integer.size();
    unsigned int remainderSize = remainder.integer.size();
    unsigned int n = dividendSize - divisorSize;

    vector::iterator it1 = integer.begin();
    vector::iterator it2 = op2.integer.begin();
    vector::iterator it3 = quotient.integer.begin();
    vector::iterator it4 = remainder.integer.begin();

    unsigned int bufferSize = divisorSize + n;

    HugeInteger buffer(dividendSize);
    vector::iterator it5 = buffer.integer.begin();

    //for (int i = divisorSize; i > 0; i--)
        //buffer.integer.begin()[n + i - 1] = op2.integer.begin()[i - 1];

    for (unsigned int i = divisorSize; i > 0; i--)
        *(it5 + n + i - 1) = *(it2 + i - 1);

    quotientSize = dividendSize - divisorSize;

    if (less(buffer))
        buffer.divideByTen();
    else
    {
        quotientSize++;
        quotient.integer.resize(quotientSize);
    }

    quotient.integer.resize(quotientSize);

   for (it3 = quotient.integer.end() - 1; it3 >= quotient.integer.begin(); --it3)
   {
       while (buffer.lessEqual(remainder))
       {     

           HugeInteger a(remainder.subtract(buffer));
           remainder.assign(a);
           ++*it3;

           if (remainder.isZero())
           {
               return quotient;
           }
       }
       buffer.divideByTen();
   }
                                        
   return quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( HugeInteger &op2 )
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector &v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output