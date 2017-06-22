#ifndef _DSAL_H_
#define _DSAL_H_

#include <iostream>
#include "dal.h"
#include <algorithm>
//=== Classe que representa um dicionário com vetor nao-ordenado
template < typename Key , typename DataType , typename KeyComparator >
class DSAL : public DAL<Key, DataType, KeyComparator >
{

    private:

        /*! \brief Método auxiliar de busca que recupera
         *         o elemento com chave 'k' e retorna seu índice. 
         *  \param k Chave do elemento que se deseja procurar.
         *  \return Índice do elemento se o mesmo for encontrado, -1 caso contário.
         */ 
        int _search ( const Key & k ) const;

    public:
        //=== Membros especiais
        DSAL(std::size_t size = DAL<Key, DataType, KeyComparator>::DEFAULT_SIZE);
        virtual ~ DSAL();

        //=== Interface pública

        /*! \brief Método que remove elemento com chave 'k' do dicionário. 
          * \param k Chave do elemento a ser removido.
          * \param info Informação associada a 'k'.
          * \return Verdadeiro se a remoção for bem sucedida, falso caso contário.
          */
        bool remove ( const Key & k , DataType & info ); 
        
         /*! \brief Método que insere novo elemento no dicionário. 
          *  \param new_key Chave do novo elemento.
          *  \param new_info Valor do novo elemento.
          *  \return Verdadeiro se a inserção for bem sucedida, falso caso contário.
          */
        bool insert ( const Key & new_key , const DataType & new_info ); 
        
        /*! \brief Método que retorna a menor chave. 
         *  \return Menor chave seguindo a ordem estrita definida.
         */
        Key min ( ) const; 
        
        /*! \brief Método que retorna a maior chave. 
         *  \return Maior chave seguindo a ordem estrita definida.
         */
        Key max ( ) const;
        
        /*! \brief Recupera informação cuja chave é imediatamente posterior
         *         a chave 'k' 
         *  \param k Chave do elemento anterior.
         *  \param k_ Chave estritamente maior que 'k'.
         *  \return Verdadeiro se a busca for bem sucedida, falso caso contário.
         */
        bool sucessor ( const Key & k , Key & k_ ) const;

        /*! \brief Recupera informação cuja chave é imediatamente anterior
         *         a chave 'k' 
         *  \param k Chave do elemento posterior.
         *  \param k_ Chave estritamente menor que 'k'.
         *  \return Verdadeiro se a busca for bem sucedida, falso caso contário.
         */
        bool predecessor ( const Key & k , Key & k_ ) const;

        void print(){
            auto data = DAL<Key, DataType, KeyComparator>::m_data;
            auto len = DAL<Key, DataType, KeyComparator>::m_len;
            std::cout << "Len " << len << std::endl;
            std::cout << "dict = [";
            for( auto i(0); i < len; ++i)
                std::cout <<"(" <<data[i].id.first <<" " << data[i].id.second <<") at "<< i << ", ";
            std::cout << "]\n";
        }


};

#include "dsal.inl"

#endif