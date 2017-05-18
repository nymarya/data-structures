#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <iterator>


namespace ls{ 

	template<typename T>
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

	template<typename T>
	class Vector{
		private:

			//!< Default size for the vector
			static constexpr std::size_t DEFAULT_SIZE{100};
			
			T *m_data;       //!< Dynamic storage area
			std::size_t m_len; //!< Logical length.
			std::size_t m_size;//!< Size of the array.


		public:

			using iterator = VectorIterator<T>;
			using const_iterator = VectorIterator<const T>;

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

			/* Constructs the list with the contents of the initializer list. */
			Vector( std::initializer_list<T> init );

			/* Destructor. */
			~Vector( );

			/* Copy assignment operator. */
			Vector& operator=( const Vector& other );

			/* Replaces the contents with those identified by initializer list ilist.*/
			Vector& operator=( std::initializer_list<T> ilist );

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

			/* Inserts elements from the range [first; last) before pos. */
			template<typename InputItr>
			iterator insert( iterator , InputItr , InputItr );

			/* Inserts elements from the initializer list before pos. */
			iterator insert( iterator, std::initializer_list< T > );

			/* Removes o elemento na posição pos. */
			iterator erase( iterator );

			/*Remove os elementos no intervalo [first, last). */
			iterator erase( iterator, iterator );

			/* Removes the element at the end of the array. */
			T pop_back();

			/* Removes the element at the beginning of the array. */
			void pop_front();

			/* Replaces the content of the list with copies of value 'value' */
			void assign( const T & value );

			/* Replaces the contents of the list with copies of the elements in the range [first; last).*/
			template < typename InputItr>
			void assign( InputItr first, InputItr last);

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
