#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <cassert>

namespace ls{

    template <typename T>
    class Queue{

        private:
            int m_f;
            int m_r;
            std::size_t m_size;
            T * m_data;

        public:
            //Construtor padrão: apenas inicializa
            Queue( std::size_t sz = 10);

            //Destrutor
            ~Queue();

            //insere no final da fila
            void enqueue( const T& value );

            //remove elemento no começo da fila
            void dequeue();

            //consulta
            T front();

            //Verifica se está vazio
            bool isEmpty();

            //Limpa fila
            void makeEmpty();

            //Retorna numero de elementos na fila
            T size() const;
    };
}

#include "queue.inl"
#endif