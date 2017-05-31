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
			 *  \param other Vetor a ser copiado.
			 */
            List( const List & other );

            List( std::initializer_list<T> ilist );

            List & operator= ( const List & );

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

            template <class InItr >
            void assign( InItr first, InItr last );

            void assign( std::initializer_list<T> ilist );

            /*! \brief Adiciona valor value antes de pos.
             *  \param pos Iterador que aponta para a posição posterior aonde o valor será inserido.
             *  \param value Valor a ser inserido.
             *  \return Iterador que aponta para a posição do item inserido.
             */
            iterator insert( const_iterator pos, const T & value );

            iterator insert( const_iterator pos, std::initializer_list<T> ilist );

            /*! \brief Remove o elemento na posição pos.
			 *  \param pos Iterador que aponta para o elemento a ser removido.
			 *  \return Iterador para o elemento que segue pos antes de o método ser chamado.
			 */
            iterator erase( const_iterator pos );

            iterator erase( const_iterator first, const_iterator last );

            const_iterator find( const T & value ) const;
    
    };

    template <typename T>
    class List<T>::const_iterator {
        protected:
            Node *m_ptr;
            friend class List<T>;

        public:
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

            /*! \brief Acessa o elemento para o qual o iterator aponta.
             *  \return Nó para o qual o iterador aponta.
             */
            T * operator->( void ) const;
    };

    template <typename T>
    class List<T>::iterator : public List<T>::const_iterator {
        protected:
            friend class List<T>;
        
        public:
            /*! \brief Construtor padrão para classe iterator. */
            iterator( Node * p );

            /*! \brief Retorna uma referência constante para o objeto lozalizado na posição apontada pelo iterador.
             *  \return O valor que o iterador aponta.
             */
            const T & operator*( ) const;

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

             T * operator->( void );
    };
} 


#include "list.inl"
#endif