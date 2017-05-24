#include <iostream>
#include <cassert>

namespace ls{

    class Queue{

        private:
            int m_f;
            int m_r;
            std::size_t m_size;
            T * m_data;

        public:
            //Construtor padrão: apenas inicializa
            Queue( std::size_t sz = 10)
            : m_f( -1)
            , m_r( -1)
            , m_size( sz)
            , m_data( new T[sz]);
            {
                /* empty */
            }

            //Destrutor
            ~Queue()
            {
                delete [] m_data;
            }

            //insere no final da fila
            void enqueue( const T& value ){
                
                int prox_r = (m_r + 1) % m_size;

                if( prox_r != f ){
                    (m_f == -1) ? m_f = 0 : m_f = m_f;
                    m_data[prox_r] = value;
                } else{
                    assert(false);
                }
                
            }

            //remove elemento no começo da fila
            void dequeue(){
                if( m_f != -1){

                    //Se so houver um elemento, f e r voltam pra -1
                    if(m_f == m_r){
                        m_f = m_r = -1;
                    } 
                    //Se houver mais de 1 elemento, o f avança circularmente
                    else{
                        m_ f = (m_f + 1) % m_size;
                    }
                    
                }else{
                    assert(false);
                }
            }

            //consulta
            T front(){
                if(m_f != -1 )
                    return m_data[m_f];

                assert(false);
            }
    };
}