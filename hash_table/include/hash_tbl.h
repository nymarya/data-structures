#ifndef _hash_tbl_h_
#define _hash_tbl_h_


#include <iostream>
#include <functional>
#include "forward_list.h"
#include <forward_list>

template < class KeyType , class DataType >
class HashEntry {

    public:
        HashEntry ( KeyType k_ , DataType d_ ) : m_key ( k_ ) , m_data ( d_ )
        { /* Empty */ };
        KeyType m_key;// ! < Stores the key for an entry .

        DataType m_data ; // ! < Stores the data for an entry .
};
using AcctKey = std::pair < std::string , int >;

template < typename KeyType ,
    typename DataType ,
    typename KeyHash = std::hash< KeyType > ,
    typename KeyEqual = std::equal_to< KeyType > >
class HashTbl{
    public:
        using Entry = HashEntry < KeyType, DataType>; // ! < Alias

    private:
        unsigned int m_size; // !< Tamanho físico da tabela.
        unsigned int m_len; // !< Tamanho lógico da tabela.
        std::forward_list < Entry > * m_data_table ;
        // std :: unique_ptr < std :: forward_list < Entry > [] > m_data_table ;
        static const short DEFAULT_SIZE = 11;

        /*! Aumenta a capacidade de armazenamento da tabela hash se  λ > 1.0
         */
        void rehash ();
        
    public:
        /*! Construtor padrão.
         * 
         */
        HashTbl ( int tbl_size_ = DEFAULT_SIZE );
        virtual ~ HashTbl ();

        bool insert ( const KeyType & key , const DataType & data_item );
        bool remove( const KeyType & k_ );
        bool retrieve ( const KeyType & k_ , DataType & d_ ) const;
        void clear( void );
        bool empty( void ) const;
        unsigned long int count ( void ) const;
        void print() const;
};

#include "hash_tbl.inl"

#endif