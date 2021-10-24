//#include <deque> // include deque class template definition
//List - 1083315 - Mid 2#include <list> // include list class template definition
//#include<deque>
//#include<list>
using namespace std;

#include "C:\Users\James\Desktop\YZU\程設作業\MidExam2\Fine\List - 1083315 - Mid 2.h"
#include "C:\Users\James\Desktop\YZU\程設作業\MidExam2\Fine\Deque - 1083315 - Mid 2.h"

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Represents a term of a polynomial
struct Term
{
   int coef;
   int expon;
};

// Polynomial class template definition
template< typename T >
class Polynomial
{
   // Overloaded stream insertion operator
   template< typename U >
   friend ostream& operator<<( ostream &output, Polynomial< U > a );
public:
   Polynomial(); // Default constructor; Constructs an empty polynomial, with no terms.

   // Copy constructor; Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
   Polynomial( const Polynomial &polynomialToCopy );

   ~Polynomial(); // Destructor with empty body

   // Assignment operator; Copies all the terms from "right" into the polynomial
   const Polynomial& operator=( const Polynomial &right );

   void insert( Term termToInsert ); // Inserts a new term into the polynomial

   Polynomial operator*( Polynomial &multiplier ); // Returns the product of two polynomials
private:
   T polynomial; // a polynomial
}; // end class template Polynomial


// Default constructor; Constructs an empty polynomial, with no terms.
template< typename T >
Polynomial< T >::Polynomial()
   : polynomial()
{
}

// Copy constructor; Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
template< typename T >
Polynomial< T >::Polynomial( const Polynomial &polynomialToCopy )
   : polynomial( polynomialToCopy.polynomial )
{
}

// Destructor with empty body
template< typename T >
Polynomial< T >::~Polynomial()
{
}

// Assignment operator; Copies all the terms from "right" into the polynomial
template< typename T >
const Polynomial< T >& Polynomial< T >::operator=( const Polynomial< T > &right )
{
   if( &right != this ) // avoid self-assignment
      polynomial = right.polynomial;

   return *this; // enables x = y = z, for example
}

// Inserts a new term into the polynomial
template< typename T >
void Polynomial< T >::insert( Term termToInsert )
{
	auto it3 = polynomial.begin();//modify
	for (; it3 != polynomial.end(); ++it3)//modify
	{
		/*if (((termToInsert.coef + it3->coef) == 0) && termToInsert.expon == it3->expon) //delete
		{
			this->polynomial.erase(it3);
			return;
		}*/ //delete
		if (termToInsert.expon == it3->expon)//modify
		{
			it3->coef += termToInsert.coef;
			if (it3->coef == 0)//add
				polynomial.erase(it3);//add
			return;//add
		}
	}
	//auto it1 = this->polynomial.begin(), it2 = this->polynomial.begin();delete
	//++it2;delete
	//bool a = false;delete
	it3 = polynomial.begin();
	for (; it3 != polynomial.end(); ++it3)//modify
	{
		if (termToInsert.expon>it3->expon)//modify
		{
			//this->polynomial.insert(it2, termToInsert);delete
			//a = true;delete
			break;//add
		}
	}
	//if (a == false)delete
	//{delete
		polynomial.insert(it3, termToInsert);//modify
	//}delete
}

// Returns the product of two polynomials
template< typename T >
Polynomial< T > Polynomial< T >::operator*( Polynomial< T > &multiplier )
{
   Polynomial< T > product;
   Term newTerm;
   
   if( !polynomial.empty() && !multiplier.polynomial.empty() )
      for( typename T::iterator it1 = polynomial.begin(); it1 != polynomial.end(); ++it1 )
         for( typename T::iterator it2 = multiplier.polynomial.begin(); it2 != multiplier.polynomial.end(); ++it2 )
         {
            newTerm.coef = it1->coef * it2->coef;
            newTerm.expon = it1->expon + it2->expon;
            product.insert( newTerm );
         }

   return product;
}

// Overloaded stream insertion operator
template< typename T >
ostream& operator<<( ostream &output, Polynomial< T > a )
{
   if( a.polynomial.empty() ) // a is zero polynomial
   {
      output << 0;
      return output;
   }

   typename T::iterator it = a.polynomial.begin();
   for( ; it != a.polynomial.end(); ++it )
      output << it->coef << " " << it->expon << " ";

   return output; // enables cout << x << y;
} // end function operator<<

#endif
