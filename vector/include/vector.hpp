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
			explicit Vector(std::size_t size = DEFAULT_SIZE)
                : m_data(new T[size + 1]) //<! Posição extra para end()
                , m_len(0)
                , m_size(size)
                {/*empty*/}

			~Vector( ){
                delete [] m_data;
            }

			//!< Return number of elements of array
			std::size_t size() const;

			//!< Returns true is vector has no elements
			bool empty ()const;

			//!< Returns true if vector is full
			bool full ()const;

			//!< Inserts element at the end of the array
			void push_back(const T & value);

			void push_front(const T & value);

			T pop_back();

			void pop_front();

			//!< Returns first element of the array
			T front() const;

			//!< Returns last element of the array
			T back();

			//!< Return the actual size of array
			std::size_t capacity() const ;

			//!< Clear vector 
			void clear();

			void print( ) const;

			T & at( std::size_t pos);

			T & operator[]( std::size_t pos);
	};

}
#include "vector.inl"

#endif