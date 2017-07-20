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

			/*! Advances iterator to the previous location within the list. (--it)
			 *  \return The required iterator.
			 */
			VectorIterator & operator--( ); 

			/*! Advances iterator to the previous location within the list . (it--)
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

			/*! Substitui o conteúdo da lista pelos elementos de ilist.
			 *  \param ilist Initializer list to initialize the elements of the list with..
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

			/* Returns a constant iterator pointing to the first item in the list
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

			/*! Adiciona valor value antes de pos.
			 *  \param pos Iterador que aponta para a posição posterior aonde o valor será inserido.
			 *  \param value Valor a ser inserido.
			 *  \return Iterador que aponta para a posição do item inserido.
			 */
			iterator insert( iterator pos, const T & value );

			/*! Insere os elementos do intervalo [first; last) antes de pos.
			 *  \param pos Iterador que aponta para a posição posterior aonde o intervalo será inserido.
			 *  \param first Iterador que aponta para a posição do primeiro valor que será inserido.
			 *  \param last Iterador que aponta para a posição posterior ao ultimo valor que será inserido.
			 *  \return Iterador que aponta para a posição do item inserido.
			 */
			template<typename InputItr>
			iterator insert( iterator , InputItr , InputItr );

			/*! Insere elementos de std::initializer_list antes de pos.
			 *  \param pos Iterador que aponta para a posição posterior aonde a lista será inserido.
			 *  \param ilist Lista que será inserida no vetor.
			 *  \return Iterador que aponta para a posição do item inserido.
			 */
			iterator insert( iterator, std::initializer_list< T > );

			/*! Remove o elemento na posição pos.
			 *  \param pos Iterador que aponta para o elemento a ser removido.
			 *  \return Iterador para o elemento que segue pos antes de o método ser chamado.
			 */
			iterator erase( iterator );

			/*! Remove os elementos no intervalo [first, last).
			 *  \param first Iterador que aponta para o primeiro elemento a ser removido.
			 *  \param last Iterador que aponta para o elemento posterior ao último a ser removido.
			 */
			iterator erase( iterator, iterator );

			/*! Remove o elemento no final da lista.
			 *  \return Novo último elemento do vetor.
			 */
			T pop_back();

			/*! Remove o elemento no início do array.
			 */
			void pop_front();

			/*! Substitui o conteúdo da lista por cópias do valor 'value'.
			 *  \param value Valor que será atribuído à lista.
			 */
			void assign( const T & value );

			/*! Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last).
			 *  \param first Iterador que aponta para o primeiro valor no intervalo que será copiado.
			 *  \param last Iterador que aponta para a posição posterior ao último elemento do intervalo.
			 */
			template < typename InputItr>
			void assign( InputItr first, InputItr last);

			/*! Substitui o conteúdo da lista pelos elementos de ilist.
			 *  \param ilist Initializer list que será copiada para a lista.
			 */
			void assign( std::initializer_list<T> ilist );

			/*! Limpa vector. */
			void clear();

			/*! Aumenta a capacidade de armazenamento da lista para um valor que é maior ou igual a new_cap.
			 *  \param new_cap Novo tamanho da lista.
			 */
			void reserve( size_type new_cap );

			/*! Remove capacidade que não é utilizada. */
			void shrink_to_fit();

			///////////////////////////
			//  [V] ELEMENT ACCESS   //
			///////////////////////////

			/*! Imprime vector. */
			void print( ) const;

			/*! Recupera elemento na posição pos.
			 *  \param pos Posição do elemento a ser retornado.
			 *  \return Refêrência para o elemento.
			 */
			T & at( size_type pos) const;

			/*! Retorna o objeto na posição pos.
			 *  \param pos Posição do elemento a ser retornado.
			 *  \return Refêrência para o elemento.
			 */
			T & operator[]( size_type pos) const;

			/*! Retorna primeiro elemento da lista.
			 *  \return Valor do primeiro elemento da lista.
			 */
			T front() const;

			/*! Retorna último elemento da lista.
			 *  \return Valor do último elemento da lista.
			 */
			T back() const;

			///////////////////////////
			//  [V] OPERATORS        //
			///////////////////////////


	};

}
#include "vector.inl"

#endif
