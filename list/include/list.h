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

                /*! Construtor simples para o nó. */
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

            /*! Classe aninhada const_iterator.*/
            class const_iterator;

            /*! Classe aninhada iterator. */
            class iterator;

            /*! Construtor padrão. */
            List( );

            /*! Constrói a lista com count cópias de T. */
            explicit List( size_type count );

            /*! Destrutor. */
            ~List( );

            List( const List & );

            List( List && );

            List & operator= ( const List & );

            List & operator=( List && );

            ///////////////////////////
            // [II] ITERADORES       //
            ///////////////////////////

            /*! Retorna iterador que aponta para o começo da lista.
             *  \return Iterador que aponta para o começo da lista.
             */
            iterator begin( );

            /* Retorna iterador constante que aponta para o começo da lista.
             * \return Iterador que aponta para o começo da lista.
             */
            const_iterator cbegin( ) const;

            /*! Retorna iterador que aponta para o final da lista.
             *  \return Iterador que aponta para o final da lista.
             */
            iterator end( );

            /* Retorna iterador constante que aponta para o final da lista.
             * \return Iterador que aponta para o final da lista.
             */
            const_iterator cend( ) const;

            ///////////////////////////
            // [III] CAPACIDADE      //
            ///////////////////////////

            /*! Retorna número de elementos da lista.
             *  \return Tamanho lógico da lista.
             */
            size_type size( ) const;

            /*! Verifica se a lista não tem elementos.
             *  \return Verdadeiro se a lista está vazia, falso caso contrário.
             */
            bool empty( ) const;

            ///////////////////////////
            // [IV] CONSULTA         //
            ///////////////////////////

            /*! Retorna uma referência para o primeiro elemento da lista.
             *  \return Valor do primeiro elemento da lista.
             */
            T & front( );

            /*! Retorna uma refrência constante para o primeiro elemento da lista.
             *  \return Valor do primeiro elemento da lista.
             */
            const T & front( ) const;

            T & back( );

            const T & back( ) const;

            ///////////////////////////
            // [V] MODIFICADORES     //
            ///////////////////////////

            void clear( );

            /*! Insere elemento no começo da lista.
             *  \param value Valor a ser inserido no final da lista.
             */
            void push_front( const T & value );

            /*! Insere elemento no final da lista.
             *  \param value Valor a ser inserido no final da lista.
             */
            void push_back( const T & value );

            void pop_front( );

            void pop_back( );

            void assign(const T& value );

            template <class InItr >
            void assign( InItr first, InItr last );

            void assign( std::initializer_list<T> ilist );

            iterator insert( const_iterator itr, const T & value );

            iterator insert( const_iterator pos, std::initializer_list<T> ilist );

            iterator erase( const_iterator itr );

            iterator erase( const_iterator first, const_iterator last );

            const_iterator find( const T & value ) const;
    
    };

    template <typename T>
    class List<T>::const_iterator {
        protected:
            Node *m_ptr;
            friend class List<T>;

        public:
            /*! Construtor padrão para classe const_iterator. */
            const_iterator( Node *p);

            /*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             */
            const T & operator*( ) const;

            /*! Avança iterador para a próxima posição na lista. (++it)
             *  \return O iterador requerido.
             */
            const_iterator & operator++( );

            /*! Avança iterador para a próxima posição na lista. (it++)
             *  \return O iterador requerido.
             */
            const_iterator operator++( int ); 

            /*! Move iterador para a posição anterior na lista. (--it)
             *  \return O iterador requerido.
             */
            const_iterator & operator--( );
           
            /*! Move iterador para a posição anterior na lista. (it--)
             *  \return O iterador requerido.
             */
            const_iterator operator--( int ); 

            /*! Retorna verdadeiro se os iteradores fazem referência para o mesmo ponto da lista.
             *  \return Verdadeiro se os iteradores são iguais, falso caso contrário.
             */            
            bool operator==( const const_iterator & rhs ) const;

            /*! Retorna verdadeiro se os iteradores fazem referência para pontos diferentes da lista.
             *  \return Verdadeiro se os iteradores são diferentes, falso caso contrário.
             */
            bool operator!=( const const_iterator & rhs ) const;
    };

    template <typename T>
    class List<T>::iterator : public List<T>::const_iterator {
        protected:
            friend class List<T>;
        
        public:
            /*! Construtor padrão para classe iterator. */
            iterator( Node * p );

            /*! Retorna uma referência constante para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             */
            const T & operator*( ) const;

            /*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             */
            T & operator*( );

            /*! Avança iterador para a próxima posição na lista. (++it)
             *  \return O iterador requerido.
             */
            iterator & operator++( );
            
            /*! Move iterador para a posição anterior na lista. (--it)
             *  \return O iterador requerido.
             */
            iterator operator++( int ); 

            /*! Move iterador para a posição anterior na lista. (--it)
             *  \return O iterador requerido.
             */
            iterator & operator--( );
            
            /*! Move iterador para a posição anterior na lista. (it--)
             *  \return O iterador requerido.
             */
            iterator operator--( int );
    };
} 


#include "list.inl"
#endif