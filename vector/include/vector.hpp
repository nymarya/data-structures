#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <iterator>


namespace ls{ 

	template<typename T>

	class Vector{

		public:
			class VectorIterator {
				private:
					T * m_current;

				public:

					explicit VectorIterator( T * current = nullptr );
					T & operator*( ) const;
					VectorIterator & operator++( );   // ++it;
					VectorIterator operator++( int ); // it++;
					VectorIterator & operator--( );   // --it;
					VectorIterator operator--( int ); // it--;
					bool operator==( const VectorIterator & rhs ) const;
					bool operator!=( const VectorIterator & rhs ) const;
				
			};
		

		private:

			//!< Default size for the vector
			static constexpr std::size_t DEFAULT_SIZE{100};
			
			T *m_data;       //!< Dynamic storage area
			std::size_t m_len; //!< Logical length.
			std::size_t m_size;//!< Size of the array.


		public:

			using iterator = VectorIterator;
			using const_iterator = const VectorIterator;

			///////////////////////////
			//  [I] SPECIAL MEMBERS  //
			///////////////////////////

			/* Default constructor */;
			explicit Vector(std::size_t size = DEFAULT_SIZE);

			/* Constructs the list with the contents of the range [first, last). */
			template< typename InputIt >
			Vector( InputIt first, InputIt last );

			/* Copy constructor */
			Vector( const Vector& other );

			/* Move constructor. */
			Vector( Vector && );

			/* Constructs the list with the contents of the initializer list. */
			Vector( std::initializer_list<T> init );

			/* Destructor. */
			~Vector( );

			/* Copy assignment operator. */
			Vector& operator=( const Vector& other );

			/* Move assignment operator. */
			Vector& operator=( Vector&& other );

			///////////////////////////
			//  [II] ITERATORS       //
			///////////////////////////

			iterator begin( void );
			iterator end( void );
			const_iterator cbegin( void ) const;
			const_iterator cend( void ) const;

			///////////////////////////
			//  [III] CAPACITY       //
			///////////////////////////

			/* Return number of elements of array. */
			std::size_t size() const;

			/* Return the actual size of array. */
			std::size_t capacity() const ;

			/* Returns true is vector has no elements. */
			bool empty ()const;

			/* Returns true if vector is full. */
			bool full ()const;

			///////////////////////////
			//  [IV] MODIFIERS       //
			///////////////////////////

			/* Inserts element at the end of the array. */
			void push_back(const T & value);

			/* Inserts element at the beginning of the array. */
			void push_front(const T & value);

			/* Adds value into the list before the position given by the iterator pos. */
			iterator insert( iterator pos, const T & value );

			/* Removes the element at the end of the array. */
			T pop_back();

			/* Removes the element at the beginning of the array. */
			void pop_front();

			/* Replaces the content of the list with copies of value 'value' */
			void assign( const T & value );

			/* Clear vector. */
			void clear();

			/* Increase the storage capacity of the array to a value that’s is greater or equal to new_cap. */
			void reserve( std::size_t new_cap );

			/* Requests the removal of unused capacity. */
			void shrink_to_fit();

			///////////////////////////
			//  [V] ELEMENT ACCESS   //
			///////////////////////////

			/* Prints vector. */
			void print( ) const;

			/* Gets element at some position. */
			T & at( std::size_t pos) const;

			/* Returns the object at the position pos. */
			T & operator[]( std::size_t pos) const;

			/* Returns first element of the array. */
			T front() const;

			/* Returns last element of the array. */
			T back() const;

			///////////////////////////
			//  [V] OPERATORS        //
			///////////////////////////


	};

}
#include "vector.inl"

#endif
