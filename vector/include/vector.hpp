#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <iterator>


namespace ls{ 

	template<typename T>

	class Vector{

		private:

			//!< Default size for the vector
			static constexpr std::size_t DEFAULT_SIZE{100};
			
			T *m_data;       //!< Dynamic storage area
			std::size_t m_len; //!< Logical length.
			std::size_t m_size;//!< Size of the array.


			void doubleArray(T * & A, std::size_t &currentSize);

		public:

			//!<Default constructor
			explicit Vector(std::size_t size = DEFAULT_SIZE);

			/* Copy constructor */
			Vector( Vector&& other );

			//!<Destructor
			~Vector( );

			//!< Return number of elements of array
			std::size_t size() const;

			//!< Returns true is vector has no elements
			bool empty ()const;

			//!< Returns true if vector is full
			bool full ()const;

			//!< Inserts element at the end of the array
			void push_back(const T & value);

			//!< Inserts element at the beginning of the array
			void push_front(const T & value);

			/** Removes the element at the end of the array. */
			T pop_back();

			/** Removes the element at the beginning of the array. */
			void pop_front();

			//!< Returns first element of the array
			T front() const;

			//!< Returns last element of the array
			T back();

			/* Replaces the content of the list with copies of value 'value' */
			void assign( const T & value )

			//!< Return the actual size of array
			std::size_t capacity() const ;

			//!< Clear vector 
			void clear();

			//!< Prints vector
			void print( ) const;

			//!< Gets element at some position
			T & at( std::size_t pos);

			//!< Returns the object at the position pos
			T & operator[]( std::size_t pos);

			/** Increase the storage capacity of the array to a value that’s is greater or equal to new_cap. */
			void reserve( std::size_t new_cap );

			void shrink_to_fit();
	};

}
#include "vector.inl"

#endif