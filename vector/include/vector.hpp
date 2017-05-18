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
			T * m_current; //<! Ponteiro para elemento de vector

		public:
			/* Construtor padrão para classe iterator. */
			explicit VectorIterator( T * current = nullptr );

			/* Returna uma referência para o objeto lozalizado na posição apontada pelo iterador */
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

			//!< Tamanho padrão
			static constexpr std::size_t DEFAULT_SIZE{100};
			
			T *m_data;         //!< Área de armmazenamento dinâmica
			std::size_t m_len; //!< Tamanho lógico.
			std::size_t m_size;//!< Tamanho da lista.


		public:

			using iterator = VectorIterator<T>;
			using const_iterator = VectorIterator<const T>;

			///////////////////////////
			//  [I] SPECIAL MEMBERS  //
			///////////////////////////

			/* Construtor padrão */
			explicit Vector(std::size_t size = DEFAULT_SIZE);

			/* Constroi a lista com os elementos do intervalo [first, last). */
			template< typename InputIt >
			Vector( InputIt first, InputIt last );

			/* Construtor cópia */
			Vector( const Vector& other );

			/* Construtor com conteúdo de initializer list. */
			Vector( std::initializer_list<T> init );

			/* Destructor. */
			~Vector( );

			/* Operador de substituição por cópia. */
			Vector& operator=( const Vector& other );

			/* Substitui o conteúdo da lista pelos elementos de ilist.*/
			Vector& operator=( std::initializer_list<T> ilist );

			///////////////////////////
			//  [II] ITERATORS       //
			///////////////////////////

			/* Retorna iterador que aponta para o começo do vetor. */
			iterator begin( void );

			/* Retorna iterador que aponta para o final do vetor. */
			iterator end( void );

			/* Retorna iterador constante que aponta para o começo do vetor. */
			const_iterator cbegin( void ) const;

			/* Retorna iterador constante que aponta para o final do vetor. */
			const_iterator cend( void ) const;

			///////////////////////////
			//  [III] CAPACITY       //
			///////////////////////////

			/* Returna número de elementos da lista. */
			std::size_t size() const;

			/* Retorna o tamanho físico da lista. */
			std::size_t capacity() const ;

			/* Verifica se o vetor não tem elementos. */
			bool empty ()const;

			/* Verifica se vetor está cheio. */
			bool full ()const;

			///////////////////////////
			//  [IV] MODIFIERS       //
			///////////////////////////

			/* Insere elemento no final da lista. */
			void push_back(const T & value);

			/* Insere elemento no início da lista. */
			void push_front(const T & value);

			/* Adiciona valor value antes de pos. */
			iterator insert( iterator pos, const T & value );

			/* Insere os elementos do intervalo [first; last) antes de pos. */
			template<typename InputItr>
			iterator insert( iterator , InputItr , InputItr );

			/* Insere elementos de std::initializer_list antes de pos. */
			iterator insert( iterator, std::initializer_list< T > );

			/* Removes o elemento na posição pos. */
			iterator erase( iterator );

			/*Remove os elementos no intervalo [first, last). */
			iterator erase( iterator, iterator );

			/* Remove o elemento no final da lista. */
			T pop_back();

			/* Remove o elemento no início do array. */
			void pop_front();

			/* Substitui o conteúdo da lista por cópias do valor 'value' */
			void assign( const T & value );

			/* Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last).*/
			template < typename InputItr>
			void assign( InputItr first, InputItr last);

			/* Substitui o conteúdo da lista pelos elementos de ilist. */
			void assign( std::initializer_list<T> ilist );

			/* Limpa vector. */
			void clear();

			/* Aumenta a capacidade de armazenamento da lista para um valor que é maior ou igual a new_cap. */
			void reserve( std::size_t new_cap );

			/* Remove capacidade que não é utilizada. */
			void shrink_to_fit();

			///////////////////////////
			//  [V] ELEMENT ACCESS   //
			///////////////////////////

			/* Imprime vector. */
			void print( ) const;

			/* Recupera elemento na posição pos. */
			T & at( std::size_t pos) const;

			/* Returna o objeto na posição pos. */
			T & operator[]( std::size_t pos) const;

			/* Returna primeiro elemento da lista. */
			T front() const;

			/* Returna último elemento da lista. */
			T back() const;

			///////////////////////////
			//  [V] OPERATORS        //
			///////////////////////////


	};

}
#include "vector.inl"

#endif
