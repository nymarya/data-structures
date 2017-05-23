/**
 * @file stack.hpp
 * @author Mayra Dantas de Azevedo
 * @date 3 Maio 2017
 * @brief Arquivo com a declaração dos métodos da classe ls::Stack.
 */

#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <iterator>

namespace ls{ 
    template <typename T>
    class Stack
    {
        private:
            static const std::size_t SIZE = 10;
            std::size_t m_top;      //<! Topo da pilha
            std::size_t m_capacity; //<! Tamanho físico
            T * m_data;             //<! Area de armazenamento

        public:
            /**
             * @brief      Construtor padrão
             *
             * @param[in]  cap    Tamanho físico da lista.
             */
            Stack( std::size_t cap = SIZE);
            
             /**
              * @brief      Destrói o objeto.
              */
            ~Stack();

            /**
             * @brief      Construtor cópia
             *
             * @param[in]  <unnamed>  Cópia a ser feita
             */
            Stack( const Stack &) = delete;

             /**
              * @brief      Operador de atribuição
              *
              * @param[in]  <unnamed>  Cópia a ser feita
              *
              * @return     Uma pilha igual à repassada
              */
            Stack & operator=(const Stack &) = delete;

             /**
              * @brief      Insere um elemento na pilha.
              *
              * @param[in]  value Valor que será inserido na pilha.
              */
            void push( const T & value);

             /**
              * @brief      Remove último elemento da pilha.
              *
              * @return     Valor removido.
              */
            T pop ( void );

             /**
              * @brief      Retorna elemento no topo da pilha.
              *
              * @return     Último elemento da pilha
              */
            T top( void );  

             /**
              * @brief      Aumenta a capacidade de armazenamento da pilha para um valor que é maior ou igual a new_cap.
              *
              * @param[in]  new_cap Novo tamanho da pilha.
              */
            void reserve( std::size_t new_cap);

            /**
              * @brief      Verifica se pilha está vazia.
              *
              * @return     Verdadeiro se a pilha está vazia, falso caso contrário.
              */
            bool empty( void );
    };
}

#include "stack.inl"

#endif
