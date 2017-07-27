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
			T * m_current; //<! Pointer

		public:
			/*! Iterator's default constructor. */
			explicit VectorIterator( T * current = nullptr );

			/*! Return a reference to the object located at the position pointed by the iterator.
			 *  \return The object located at the position pointed by the iterator.
			 * */
			T & operator*( ) const;

			/*! Advances iterator to the next location within the list (++it)
			 *  \return The required pointer.
			 */
			VectorIterator & operator++( );

			/*! Advances iterator to the next location within the list. (it++)
			 *  \return The required iterator.
			 */
			VectorIterator operator++( int );

			/*! Moves iterator to the previous location within the list. (--it)
			 *  \return The required iterator.
			 */
			VectorIterator & operator--( ); 

			/*! Moves iterator to the previous location within the list . (it--)
			 *  \return The required iterator.
			 */
			VectorIterator operator--( int );

			/*! Returns true if both iterators refer to the same location within the list.
			 *  \return True if both iterators refer to the same location, false otherwise.
			 */
			bool operator==( const VectorIterator & rhs ) const;

			/*! Returns true if both iterators refer to a different location within the list.
			 *  \return True if both iterators refer to a different location, false otherwise.
			 */
			bool operator!=( const VectorIterator & rhs ) const;
	};

	template<typename T>
	class Vector{
		private:

			//!< Default size of the list
			static constexpr std::size_t DEFAULT_SIZE{100};
			
			T *m_data;         //!< Dynamic storage area.
			std::size_t m_len; //!< Logic size of the list.
			std::size_t m_size;//!< Actual size of the list.

		public:
			using iterator = VectorIterator<T>;
			using const_iterator = VectorIterator<const T>;
			using size_type = std::size_t;

			///////////////////////////
			//  [I] SPECIAL MEMBERS  //
			///////////////////////////

			/*! Default constructor.
			 *  \param size Vector size.
			 */
			explicit Vector(size_t size = DEFAULT_SIZE);

			/*! Constructs the list with the contents of the range [first, last).
			 *  \param first Iterator pointing to the beginning of the range.
			 *  \param last Iterator pointing to the end of the range.
			 */
			template< typename InputIt >
			Vector( InputIt first, InputIt last );

			/*! Copy constructor.
			 *  \param other Vector to initialize the elements of the list with..
			 */
			Vector( const Vector& other );

			/*! Constructs the list with the contents of the initializer list.
			 *  \param init Initializer list to initialize the elements of the list with.
			 */
			Vector( std::initializer_list<T> init );

			/*! Destructor. */
			~Vector( );

			/*! Copy assignment operator.
			 *  \param other Vector to fill the list with..
			 *  \return The new object.
			 */
			Vector& operator=( const Vector& other );

			/*! Replace the content of the list with the contents of the initializer list.
			 *  \param ilist Initializer list to initialize the elements of the list with.
			 *  \return The new object.
			 */
			Vector& operator=( std::initializer_list<T> ilist );

			///////////////////////////
			//  [II] ITERATORS       //
			///////////////////////////

			/*! Returns an iterator pointing to the first item in the list.
			 *  \return Iterator pointing to the first item in the list.
			 */
			iterator begin( void );

			/*! Returns an iterator pointing to the end mark of the list.
			 *  \return Iterator pointing to the end mark of the list
			 */
			iterator end( void );

			/* Returns a constant iterator pointing to the first item in the list.
			 * \return Iterator pointing to the first item in the list.
			 */
			const_iterator cbegin( void ) const;

			/* Returns a constant iterator pointing to the end mark of the list.
			 * \return Iterator pointing to the the end mark of the list.
			 */
			const_iterator cend( void ) const;

			///////////////////////////
			//  [III] CAPACITY       //
			///////////////////////////

			/*! Returns the number of elements in the container.
			 *  \return Number of elements of the list.
			 */
			size_type size() const;

			/*! Return the capacity of the container.
			 *  \return Capacity of the list.
			 */
			size_type capacity() const ;

			/*! Checks if the container contains no elements.
			 *  \return True if list is empty, false otherwise.
			 */
			bool empty ()const;

			/*! Checks if the container is full.
			 *  \return True if the list is full, false otherwise.
			 */
			bool full ()const;

			///////////////////////////
			//  [IV] MODIFIERS       //
			///////////////////////////

			/*! Inserts element at the end of the list.
			 *  \param value Value to be inserted at the end of the list.
			 */
			void push_back(const T & value);

			/*! Inserts element at the beginning of the container.
			 *  \param value Value to be inserted at the beginning of the list. 
			 */
			void push_front(const T & value);

			/*! Adds value before 'pos'.
			 *  \param pos Iterator pointing to the position after the one in which the value will be inserted.
			 *  \param value Value to be inserted.
			 *  \return Iterator pointing to the inserted element.
			 */
			iterator insert( iterator pos, const T & value );

			/*! Inserts elements of the range [first; last) before 'pos'.
			 *  \param pos Iterator pointing to the position after the one in which the range will be inserted.
			 *  \param first Iterator pointing to the first value of the range of elements to insert.
			 *  \param last Iterator pointing to the position after the last value of the range of elements to insert.
			 *  \return Iterator pointing to the first inserted value.
			 */
			template<typename InputItr>
			iterator insert( iterator pos, InputItr first, InputItr last);

			/*! Inserts elements from std::initializer_list before pos.
			 *  \param pos Iterator pointing to the position after the one in which the list will be inserted.
			 *  \param ilist List to be inserted.
			 *  \return Iterator pointing to the first inserted value.
			 */
			iterator insert( iterator pos, std::initializer_list< T > ilist);

			/*! Removes the element at 'pos'.
			 *  \param pos Iterator pointing to the element to be removed.
			 *  \return Iterator following the removed element.
			 */
			iterator erase( iterator pos);

			/*! Removes elements of the range [first, last) form the container.
			 *  \param first Iterator pointing to the first element of the range.
			 *  \param last Iterator following the last removed element.
			 */
			iterator erase( iterator first, iterator last);

			/*! Removes the element at the end of the list.
			 *  \return New last element.
			 */
			T pop_back();

			/*! Removes the element at the beginning of the container. */
			void pop_front();

			/*! Replaces the content of the list with copies of 'value'.
			 *  \param value The value to initialize the list with.
			 */
			void assign( const T & value );

			/*! Replaces the content of the list with copies of the elements of the range [first,last).
			 *  \param first Iterator pointing to the first element of the range.
			 *  \param last Iterator pointing to the position after the last element of the range.
			 */
			template < typename InputItr>
			void assign( InputItr first, InputItr last);

			/*! Replaces the content of the list with copies of the elements of 'ilist'.
			 *  \param ilist Initializer list to repelace the content of the list with.
			 */
			void assign( std::initializer_list<T> ilist );

			/*! Removes all elements from container. */
			void clear();

			/*! Increase the storage capacity of the array to a value that’s is greater or equal to 'new_cap'.
			 *  \param new_cap New container size.
			 */
			void reserve( size_type new_cap );

			/*! Requests the removal of unused capacity. */
			void shrink_to_fit();

			///////////////////////////
			//  [V] ELEMENT ACCESS   //
			///////////////////////////

			/*! Prints vector. */
			void print( ) const;

			/*! Gets element at position 'pos' with bounds-checking.
			 *  \param pos Index of element at the array.
			 *  \return Reference to the object at the index pos in the array.
			 */
			T & at( size_type pos) const;

			/*! Gets the object at position 'pos'.
			 *  \param pos Index of element at the array.
			 *  \return Reference to the object at the index pos in the array..
			 */
			T & operator[]( size_type pos) const;

			/*! Returns the object at the beginning of the array.
			 *  \return First object of the array.
			 */
			T front() const;

			/*! Returns the object at the end of the array.
			 *  \return Last object of the array.
			 */
			T back() const;

			///////////////////////////
			//  [V] OPERATORS        //
			///////////////////////////


	};

}
#include "vector.inl"

#endif
