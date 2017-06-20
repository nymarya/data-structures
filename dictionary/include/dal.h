#ifndef _DAL_H_
#define _DAL_H_

#include <iostream>
//=== Classe que representa um dicionário com vetor nao-ordenado
template < typename Key , typename DataType , typename KeyComparator >
class DAL{

    protected:
        
        //!< Estrutura do nó que guarda chave e informação
        struct Node {
            Key id ;        //!< A chave é um inteiro simples
            DataType data ; //!< A informação é uma cadeia de caracteres .
        };

        static const int DEFAULT_SIZE=50;
        int m_capacity; //!< Tamanho máximo de armazenamento
        int m_len;      //!< Tamanho lógico
        Node * m_data;  //!< Área de armazenamento

        /*! \brief Método auxiliar de busca que recupera
         *         o elemento com chave 'k' e retorna seu índice. 
         *  \param k Chave do elemento que se deseja procurar.
         *  \return Índice do elemento se o mesmo for encontrado, -1 caso contário.
         */ 
        int _search ( const Key & k ) const;

    public:
        //=== Membros especiais
        DAL(std::size_t size = DEFAULT_SIZE);
        virtual ~ DAL();

        //=== Interface pública

        /*! \brief Método que remove elemento com chave 'k' do dicionário. 
          * \param k Chave do elemento a ser removido.
          * \param info Informação associada a 'k'.
          * \return Verdadeiro se a remoção for bem sucedida, falso caso contário.
          */
        bool remove ( const Key & k , DataType & info ); 
        
        /*! \brief Método de busca que recupera o elemento
         *         com chave 'k' e guarda seu valor em 'info'. 
         *  \param k Chave do elemento que se deseja procurar.
         *  \param info Variável que guarda o elemento recuperado.
         *  \return Verdadeiro se o elemento for encontrado, falso caso contário.
         */
        bool search ( const Key & d , DataType & info ) const ; 
        
         /*! \brief Método que insere novo elemento no dicionário. 
          *  \param new_key Chave do novo elemento.
          *  \param new_info Valor do novo elemento.
          *  \return Verdadeiro se a inserção for bem sucedida, falso caso contário.
          */
        bool insert ( const Key & new_key , const DataType & new_info ); 
        
        Key min ( ) const; 
        
        Key max ( ) const;
        
        bool sucessor ( const Key & k , Key & k_ ) const;

        bool predecessor ( const Key & k , Key & k_ ) const;


};

#include "dal.inl"

#endif