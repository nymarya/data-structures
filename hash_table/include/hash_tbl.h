#ifndef _hash_tbl_h_
#define _hash_tbl_h_

template < class KeyType , class DataType >
class HashEntry {

    public:
        HashEntry ( KeyType k_ , DataType d_ ) : m_key ( k_ ) , m_data ( d_ )
        { /* Empty */ };
        KeyType m_key;// ! < Stores the key for an entry .

        DataType m_data ; // ! < Stores the data for an entry .
};

class HashTblv1{
    private:
        unsigned int m_size ; // !< Tamanho físico da tabela.
        unsigned int m_count ; // !< Tamanho lógico da tabela.
        std::forward_list < Entry > * m_data_table ;
        // std :: unique_ptr < std :: forward_list < Entry > [] > m_data_table ;
        static const short DEFAULT_SIZE = 11;

        /*! Aumenta a capacidade de armazenamento da tabela hash se  λ > 1.0
         */
        void rehash ();
        
    public:
        using Entry = HashEntry < KeyType , DataType >; // ! < Alias
        HashTbl ( i n t tbl_size_ = DEFAULT_SIZE );
        virtual ~ HashTbl ();
        bool insert ( const KeyType & k_ , const DataType & d_ );
        bool remove( const KeyType & k_ );
        bool retrieve ( const KeyType & k_ , DataType & d_ ) const;
        void clear( void );
        bool empty( void ) const;
        unsigned long int count ( void ) const;
        void print() const;
};

#include "hash_tbl.inl"

#endif