#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1, '0' )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1, '0' )
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
const HugeInteger& HugeInteger::operator=( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
//   return operator==( integer, right.integer );
   return ( integer == right.integer );
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::operator<( const HugeInteger &right ) const
{
    HugeInteger int1(*this);
    HugeInteger int2(right);

    unsigned int size1 = integer.size();
    unsigned int size2 = right.integer.size();

    string::iterator it1 = int1.integer.end() - 1;
    string::iterator it2 = int2.integer.end() - 1;

    if (size1 > size2)
        return false;
    else if (size1 < size2)
        return true;
    else
    {
        for (; it1 >= int1.integer.begin(); --it1, --it2)
        {
            if (*it1 > * it2)
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
bool HugeInteger::operator<=( const HugeInteger &right ) const
{
   return ( *this == right || *this < right );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   string::iterator it1 = integer.begin();
   string::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   string::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 = ( *it3 - '0' ) + ( *it2 - '0' ) + '0';

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > '9' )
      {
         ( *it3 ) = ( *it3 - '0' ) - 10 + '0';
         ( *( it3 + 1 ) ) = ( *( it3 + 1 ) - '0' ) + 1 + '0';
      }

   if( *it3 == '0' )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-( HugeInteger &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
      return zero;

   HugeInteger difference( *this );

   string::iterator it1 = op2.integer.begin();
   string::iterator it2 = difference.integer.begin();

   for (it2 = difference.integer.begin(); it1 != op2.integer.end(); ++it1, ++it2)
       *it2 = (*it2 - '0') - (*it1 - '0') + '0';

   for (it2 = difference.integer.begin(); it2 < difference.integer.end(); ++it2)
   {
       if (*it2 < '0')
       {
           *(it2) = (*it2 - '0') + 10 + '0';
           (*(it2 + 1)) = (*(it2 + 1) - '0') - 1 + '0';
       }
   }

   for (it2 = difference.integer.end() - 1; *it2 == '0'; --it2)
       difference.integer.pop_back();

   return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );

   string::iterator it1 = integer.begin();
   string::iterator it2 = op2.integer.begin();
   string::iterator it3 = product.integer.begin();

   for (unsigned int i = 0; i < integer.size(); ++i)
       for (unsigned int j = 0; j < op2.integer.size(); ++j)
       {
           unsigned int a = (integer[i] - '0') * (op2.integer[j] - '0');

           if (a > 9)
           {
               product.integer[i + j + 1] += a / 10;
               product.integer[i + j] += a % 10;
           }
           else
           {
               product.integer[i + j] += a;
           }

           if (product.integer[i+j] > '9')
           {
               product.integer[i + j + 1] += (product.integer[i + j] - '0') / 10;
               product.integer[i + j] = (product.integer[i + j] - '0') % 10 + '0';
           }
       }
   
   for (it3 = product.integer.end() - 1; *it3 == '0'; --it3)
       product.integer.pop_back();

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator/( HugeInteger &op2 )
{
   HugeInteger zero;
   if( *this < op2 )
      return zero;
   HugeInteger quotient;

   HugeInteger  remainder(*this);

   unsigned int dividendSize = integer.size();
   unsigned int divisorSize = op2.integer.size();
   unsigned int quotientSize = quotient.integer.size();
   unsigned int remainderSize = remainder.integer.size();
   unsigned int n = dividendSize - divisorSize;

   string::iterator it1 = integer.begin();
   string::iterator it2 = op2.integer.begin();
   string::iterator it3 = quotient.integer.begin();
   string::iterator it4 = remainder.integer.begin();

   unsigned int bufferSize = divisorSize + n;

   HugeInteger buffer(dividendSize);
   string::iterator it5 = buffer.integer.begin();

   for (unsigned int i = divisorSize; i > 0; i--)
       *(it5 + n + i - 1) = *(it2 + i - 1);

   quotientSize = dividendSize - divisorSize;

   if (*this < buffer)
       buffer.divideByTen();
   else
   {
       quotientSize++;
       quotient.integer.resize(quotientSize);
   }
   
   quotient.integer.resize(quotientSize);

   for (int i = 0; i < quotientSize; i++)
       quotient.integer[i] = '0';

   for (int i=quotientSize-1; i>=0; i--)
   {
       while (buffer <= remainder)
       {

           HugeInteger a(remainder - buffer);
           remainder = a;
           quotient.integer[i] += 1;

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
HugeInteger HugeInteger::operator%( HugeInteger &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger product = quotient * op2;
   HugeInteger remainder = ( *this ) - product;
   return remainder;
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( string &str )
{
   integer.resize( str.size() );
   string::iterator it1 = integer.end() - 1;
   string::iterator it2 = str.begin();
   for( ; it2 != str.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( string::iterator it = integer.begin(); it != integer.end(); ++it )
      if( *it != '0' )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   string::iterator it = integer.begin();
   string::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
ostream& operator<<( ostream &output, const HugeInteger &hugeInteger )
{
   string::const_iterator it = hugeInteger.integer.end() - 1;

   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it <= '9' )
         output << *it;

   return output; // enables cout << x << y;
} // end function output
