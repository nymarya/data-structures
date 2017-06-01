#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>

namespace ls{
    
    template <typename T>
    class List {
        private:
            struct Node {
                T data;      //<! Valor armazenado no nó
                Node * prev; //<! Ponteiro para o nó anterior
                Node * next; //<! Ponteiro para o pŕóximo nó

                /*! \brief Construtor simples para o nó. */
                Node( const T & d = T( ), Node * p = nullptr, Node * n = nullptr )
                : data( d ), prev(p), next( n ) { /* Empty */ }
            };

            std::size_t m_size; //<! Tamanho da lista
            Node *m_head;       //<! Cabeça da lista
            Node *m_tail;       //<! Calda da lista

        public:

            using size_type = std::size_t;

            ///////////////////////////
            // [I] MEMBROS ESPECIAIS //
            ///////////////////////////

            /*! \brief Classe aninhada const_iterator.*/
            class const_iterator;

            /*! \brief Classe aninhada iterator. */
            class iterator;

            /*! \brief Construtor padrão. */
            List( );

            /*! \brief Constrói a lista com count cópias de T. 
             *  \param count Números de instâncias de T.
             */
            explicit List( size_type count );

            /*! \brief Destrutor. */
            ~List( );

            /*! \brief Constroi a lista com os elementos do intervalo [first, last).
			 *  \param first Iterador que aponta para o início da lista a ser copiada.
			 *  \param last Iterador que aponta para o final da lista a ser copiada.
			 */
            template< typename InputIt >
            List( InputIt first, InputIt last );

            /*! \brief Construtor cópia
			 *  \param other Lista a ser copiado.
			 */
            List( const List & other );

            /*! \brief Construtor com conteúdo de initializer list.
			 *  \param init Initializer list cujo conteúdo preenche a lista.
			 */
            List( std::initializer_list<T> ilist );

            /*! \brief Operador de atribuição por cópia.
			 *  \param other Lista a ser copiada.
			 *  \return O novo objeto.
			 */
            List & operator= ( const List & );

            /*! \brief Substitui o conteúdo da lista pelos elementos de ilist.
			 *  \param ilist Initializer list cujo conteúdo irá preencher a lista.
			 *  \return O novo objeto.
			 */
            List& operator=( std::initializer_list<T> ilist );

            ///////////////////////////
            // [II] ITERADORES       //
            ///////////////////////////

            /*! \brief Retorna iterador que aponta para o começo da lista.
             *  \return Iterador que aponta para o começo da lista.
             */
            iterator begin( );

            /* \brief Retorna iterador constante que aponta para o começo da lista.
             * \return Iterador que aponta para o começo da lista.
             */
            const_iterator cbegin( ) const;

            /*! \brief Retorna iterador que aponta para o final da lista.
             *  \return Iterador que aponta para o final da lista.
             */
            iterator end( );

            /* \brief Retorna iterador constante que aponta para o final da lista.
             * \return Iterador que aponta para o final da lista.
             */
            const_iterator cend( ) const;

            ///////////////////////////
            // [III] CAPACIDADE      //
            ///////////////////////////

            /*! \brief Retorna número de elementos da lista.
             *  \return Tamanho lógico da lista.
             */
            size_type size( ) const;

            /*! \brief Verifica se a lista não tem elementos.
             *  \return Verdadeiro se a lista está vazia, falso caso contrário.
             */
            bool empty( ) const;

            ///////////////////////////
            // [IV] CONSULTA         //
            ///////////////////////////

            /*! \brief Retorna uma referência para o primeiro elemento da lista.
             *  \return Valor do primeiro elemento da lista.
             */
            T & front( );

            /*! \brief Retorna uma refrência constante para o primeiro elemento da lista.
             *  \return Valor do primeiro elemento da lista.
             */
            const T & front( ) const;

            /*! \brief Retorna uma referência para o último elemento da lista.
			 *  \return Valor do último elemento da lista.
			 */
            T & back( );

            /*! \brief Retorna uma referência constante para o último elemento da lista.
			 *  \return Valor do último elemento da lista.
			 */
            const T & back( ) const;

            ///////////////////////////
            // [V] MODIFICADORES     //
            ///////////////////////////

            /*! \brief Limpa lista. */
            void clear( );

            /*! \brief Insere elemento no começo da lista.
             *  \param value Valor a ser inserido no final da lista.
             */
            void push_front( const T & value );

            /*! \brief Insere elemento no final da lista.
             *  \param value Valor a ser inserido no final da lista.
             */
            void push_back( const T & value );

            /*! \brief Remove o elemento no início da lista.
			 */
            void pop_front( );

            /*! \brief Remove o elemento no final da lista.
			 */
            void pop_back( );

            /*! \brief Substitui o conteúdo da lista por cópias do valor 'value'.
			 *  \param value Valor que será atribuído à lista.
			 */
            void assign(const T& value );

            /*! \brief Substitui o conteúdo da lista por cópias dos elementes no intervalo [first,last).
			 *  \param first Iterador que aponta para o primeiro valor no intervalo que será copiado.
			 *  \param last Iterador que aponta para a posição posterior ao último elemento do intervalo.
			 */
            template <class InItr >
            void assign( InItr first, InItr last );

            /*! \brief Substitui o conteúdo da lista pelos elementos de ilist.
			 *  \param ilist Initializer list que será copiada para a lista.
			 */
            void assign( std::initializer_list<T> ilist );

            /*! \brief Adiciona valor value antes de pos.
             *  \param pos Iterador que aponta para a posição posterior aonde o valor será inserido.
             *  \param value Valor a ser inserido.
             *  \return Iterador que aponta para a posição do item inserido.
             */
            iterator insert( const_iterator pos, const T & value );

            /*! \brief Insere os elementos do intervalo [first; last) antes de pos.
			 *  \param pos Iterador que aponta para a posição posterior aonde o intervalo será inserido.
			 *  \param first Iterador que aponta para a posição do primeiro valor que será inserido.
			 *  \param last Iterador que aponta para a posição posterior ao ultimo valor que será inserido.
			 *  \return Iterador que aponta para a posição seguinte ao último item inserido.
			 */
            template < typename InItr>
            iterator insert( iterator pos, InItr first, InItr last );

            /*! \brief Insere elementos de std::initializer_list antes de pos.
			 *  \param pos Iterador que aponta para a posição posterior aonde a lista será inserido.
			 *  \param ilist Lista que será inserida na lista.
			 *  \return Iterador que aponta para a posição seguinte ao último item inserido.
			 */
            iterator insert( const_iterator pos, std::initializer_list<T> ilist );

            /*! \brief Remove o elemento na posição pos.
			 *  \param pos Iterador que aponta para o elemento a ser removido.
			 *  \return Iterador para o elemento que segue pos antes de o método ser chamado.
			 */
            iterator erase( const_iterator pos );

            /*! \brief Remove os elementos no intervalo [first, last).
			 *  \param first Iterador que aponta para o primeiro elemento a ser removido.
			 *  \param last Iterador que aponta para o elemento posterior ao último a ser removido.
			 */
            iterator erase( iterator first, iterator last );

            const_iterator find( const T & value ) const;
    
    };

    template <typename T>
    class List<T>::const_iterator {
        protected:
            Node *m_ptr;
            friend class List<T>;

        public:
            using difference_type = std::ptrdiff_t;

            /*! \brief Construtor padrão para classe const_iterator. */
            const_iterator( Node *p);

            /*! \brief Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             */
            const T & operator*( ) const;

            /*! \brief Avança iterador para a próxima posição na lista. (++it)
             *  \return O iterador requerido.
             */
            const_iterator & operator++( );

            /*! \brief Avança iterador para a próxima posição na lista. (it++)
             *  \return O iterador requerido.
             */
            const_iterator operator++( int ); 

            /*! \brief Move iterador para a posição anterior na lista. (--it)
             *  \return O iterador requerido.
             */
            const_iterator & operator--( );
           
            /*! \brief Move iterador para a posição anterior na lista. (it--)
             *  \return O iterador requerido.
             */
            const_iterator operator--( int ); 

            /*! \brief Retorna verdadeiro se os iteradores fazem referência para o mesmo ponto da lista.
             *  \return Verdadeiro se os iteradores são iguais, falso caso contrário.
             */            
            bool operator==( const const_iterator & rhs ) const;

            /*! \brief Retorna verdadeiro se os iteradores fazem referência para pontos diferentes da lista.
             *  \return Verdadeiro se os iteradores são diferentes, falso caso contrário.
             */
            bool operator!=( const const_iterator & rhs ) const;

            /*! \brief Avança iterador step vezes.
             *  \param step Vezes que o iterador irá avançar.
             *  \return O iterador requerido.
             */
            const_iterator operator+=( difference_type step ) ;

            /*! \brief Move iterador step vezes para trás.
             *  \param step Vezes que o iterador irá mover-se.
             *  \return O iterador requerido.
             */
            const_iterator operator-=( difference_type step ) ;
    };

    template <typename T>
    class List<T>::iterator : public List<T>::const_iterator {
        protected:
            friend class List<T>;
        
        public:
            /*! \brief Construtor padrão para classe iterator. */
            iterator( Node * p );

            /*! \brief Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             */
            T & operator*( );

            /*! \brief Avança iterador para a próxima posição na lista. (++it)
             *  \return O iterador requerido.
             */
            iterator & operator++( );
            
            /*! \brief Move iterador para a posição anterior na lista. (--it)
             *  \return O iterador requerido.
             */
            iterator operator++( int ); 

            /*! \brief Move iterador para a posição anterior na lista. (--it)
             *  \return O iterador requerido.
             */
            iterator & operator--( );
            
            /*! \brief Move iterador para a posição anterior na lista. (it--)
             *  \return O iterador requerido.
             */
            iterator operator--( int );

            /*! \brief Avança iterador step vezes.
             *  \param step Vezes que o iterador irá avançar.
             *  \return O iterador requerido.
             */
            iterator operator+=( typename const_iterator::difference_type step ) ;

            /*! \brief Move iterador step vezes para trás.
             *  \param step Vezes que o iterador irá mover-se.
             *  \return O iterador requerido.
             */
            iterator operator-=( typename const_iterator::difference_type step ) ;
    };
} 


#include "list.inl"
#endif