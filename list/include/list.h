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


            iterator begin( );

            const_iterator cbegin( ) const;

            iterator end( );

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

            T & front( );

            const T & front( ) const;

            T & back( );

            const T & back( ) const;

            ///////////////////////////
            // [V] MODIFICADORES     //
            ///////////////////////////

            void clear( );

            void push_front( const T & value );

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
            Node *current;
            const_iterator( Node * p ) : current( p ){}
            friend class List<T>;

        public:
            /*! Construtor padrão para classe iterator. */
            const_iterator( );

            /*! Retorna uma referência para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             * */
            const T & operator*( ) const;
            const_iterator & operator++( );
            // ++it;
            const_iterator operator++( int ); // it++;
            const_iterator & operator--( );
            // --it;
            const_iterator operator--( int ); // it--;
            bool operator==( const const_iterator & rhs ) const;
            bool operator!=( const const_iterator & rhs ) const;
    };

    template <typename T>
    class List<T>::iterator : public List<T>::const_iterator {
        protected:
            iterator( Node *p ):const_iterator( p ){}
            friend class List<T>;
        
        public:
            iterator( ): const_iterator() { /* Empty */ }
            const T & operator*( ) const;
            T & operator*( );
            const_iterator & operator++( );
            // ++it;
            const_iterator operator++( int ); // it++;
            const_iterator & operator--( );
            // --it;
            const_iterator operator--( int ); // it--;
    };
} 


#include "list.inl"
#endif