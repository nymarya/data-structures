#ifndef _hash_tbl_h_
#define _hash_tbl_h_


#include <iostream>
#include <functional>
#include "forward_list.h"
#include <forward_list>

//=== Classe que define as entradas
template < class KeyType , class DataType >
class HashEntry {

    //=== Membros públicos
    public:   
        KeyType m_key;// !< Guarda a chave da entrada.
        DataType m_data ; // !< Guarda o valor da entrada.
    
        //=== Membros especiais
        HashEntry ( KeyType k_ , DataType d_ ) : m_key ( k_ ) , m_data ( d_ )
        { /* Empty */ };

};
using AcctKey = std::pair < std::string , int >;

//=== Classe que define a tabela de dispersão
template < typename KeyType ,
    typename DataType ,
    typename KeyHash = std::hash< KeyType > ,
    typename KeyEqual = std::equal_to< KeyType > >
class HashTbl{
    public:
        //=== Aliases
        using Entry = HashEntry < KeyType, DataType>;
        using size_type = usigned int;

    //=== Membros privados
    private:
        size_type m_size; // !< Tamanho físico da tabela.
        size_type unsigned int m_len; // !< Tamanho lógico da tabela.
        std::forward_list < Entry > * m_data_table ;
        // std :: unique_ptr < std :: forward_list < Entry > [] > m_data_table ;
        static const short DEFAULT_SIZE = 11; //!< Tamanho padrão da tabela

        /*! \brief Aumenta a capacidade de armazenamento da tabela hash se  λ > 1.0. */
        void rehash ();
        
    public:
        //=== Membros especiais
        /*! \brief Construtor padrão. */
        HashTbl ( int tbl_size_ = DEFAULT_SIZE );
        /*! \brief Destrutor. */
        virtual ~ HashTbl ();

        //=== Interface pública
        /*! \brief Insere na tabela a informaç̃ao contida em 'data_item' 
         *         e associada a uma chave 'key'. 
         *  \param key Chave à qual o dado será associado.
         *  \param data_item Dado que será inserido na tabela.
         *  \return Verdadeiro se a inserção for bem sucedida, falso caso contário.
         */ 
        bool insert ( const KeyType & key , const DataType & data_item );
        bool remove( const KeyType & key );
        bool retrieve ( const KeyType & key , DataType & data ) const;
        void clear( void );
        bool empty( void ) const;
        unsigned long int count ( void ) const;
        void print() const;
};

#include "hash_tbl.inl"

#endif