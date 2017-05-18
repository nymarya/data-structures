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
			/*! Construtor padrão para classe iterator. */
			explicit VectorIterator( T * current = nullptr );

			/*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.
			 *  \return O valor que o iterador aponta.
			 * */
			T & operator*( ) const;

			/*! Avança iterador para a próxima posição na lista. (++it)
			 *  \return O iterador requerido.
			 */
			VectorIterator & operator++( );

			/*! Avança iterador para a próxima posição na lista. (it++)
			 *  \return O iterador requerido.
			 */
			VectorIterator operator++( int );

			/*! Move iterador para a posição anterior na lista. (--it)
			 *  \return O iterador requerido.
			 */
			VectorIterator & operator--( ); 

			/*! Move iterador para a posição anterior na lista. (it--)
			 *  \return O iterador requerido.
			 */
			VectorIterator operator--( int );

			/*! Retorna verdadeiro se os iteradores fazem referência para o mesmo ponto da lista.
			 *  \return Verdadeiro se os iteradores são iguais, falso caso contrário.
			 */
			bool operator==( const VectorIterator & rhs ) const;

			/*! Retorna verdadeiro se os iteradores fazem referência para pontos diferentes da lista.
			 *  \return Verdadeiro se os iteradores são diferentes, falso caso contrário.
			 */
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
			using size_type = std::size_t;

			///////////////////////////
			//  [I] SPECIAL MEMBERS  //
			///////////////////////////

			/*! Construtor padrão
			 *  \param size Tamanho do vetor.
			 */
			explicit Vector(size_t size = DEFAULT_SIZE);

			/*! Constroi a lista com os elementos do intervalo [first, last).
			 *  \param first Iterador que aponta para o início do vetor a ser copiado.
			 *  \param last Iterador que aponta para o final da lista a ser copiado.
			 */
			template< typename InputIt >
			Vector( InputIt first, InputIt last );

			/*! Construtor cópia
			 *  \param other Vetor a ser copiado.
			 */
			Vector( const Vector& other );

			/*! Construtor com conteúdo de initializer list.
			 *  \param init Initializer list cujo conteúdo preenche a lista.
			 */
			Vector( std::initializer_list<T> init );

			/*! Destructor. */
			~Vector( );

			/*! Operador de atribuição por cópia.
			 *  \param other Vetor a ser copiado.
			 *  \return O novo objeto.
			 */
			Vector& operator=( const Vector& other );

			/*! Substitui o conteúdo da lista pelos elementos de ilist.
			 *  \param ilist Initializer list cujo conteúdo irá preencher a lista.
			 *  \return O novo objeto.
			 */
			Vector& operator=( std::initializer_list<T> ilist );

			///////////////////////////
			//  [II] ITERATORS       //
			///////////////////////////

			/*! Retorna iterador que aponta para o começo do vetor.
			 *  \return Iterador que aponta para o começo do vetor.
			 */
			iterator begin( void );

			/*! Retorna iterador que aponta para o final do vetor.
			 *  \return Iterador que aponta para o final do vetor.
			 */
			iterator end( void );

			/* Retorna iterador constante que aponta para o começo do vetor.
			 * \return Iterador que aponta para o começo do vetor.
			 */
			const_iterator cbegin( void ) const;

			/* Retorna iterador constante que aponta para o final do vetor.
			 * \return Iterador que aponta para o final do vetor.
			 */
			const_iterator cend( void ) const;

			///////////////////////////
			//  [III] CAPACITY       //
			///////////////////////////

			/*! Retorna número de elementos da lista.
			 *  \return Tamanho lógico da lista.
			 */
			size_type size() const;

			/*! Retorna o tamanho físico da lista.
			 *  \return Capacidade da lista.
			 */
			size_type capacity() const ;

			/*! Verifica se o vetor não tem elementos.
			 *  \return Verdadeiro se a lista está vazia, falso caso contrário.
			 */
			bool empty ()const;

			/*! Verifica se vetor está cheio.
			 *  \return Verdadeiro se a lista está cheia, falso caso contrário.
			 */
			bool full ()const;

			///////////////////////////
			//  [IV] MODIFIERS       //
			///////////////////////////

			/*! Insere elemento no final da lista.
			 *  \param value Valor a ser inserido no final da lista.
			 */
			void push_back(const T & value);

			/*! Insere elemento no início da lista.
			 *  \param value Valor a ser inserido no final da lista. 
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
