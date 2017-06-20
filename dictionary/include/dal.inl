#include "dal.h"

template < typename Key , typename DataType , typename KeyComparator >
DAL<Key, DataType, KeyComparator>::DAL( std::size_t size)
:m_capacity( size )
,m_len(0)
,m_data( new Node[size])
{ /* empty*/ }

template < typename Key , typename DataType , typename KeyComparator >
DAL<Key, DataType, KeyComparator>::~DAL()
{ delete [] m_data; }

template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::search ( const Key & k , DataType & info ) const 
{
    for( auto i(0ul); i < m_len ++i){
        if( m_len[i].key == k){
            info = m_len[i].data;
            return true;
        }
    }

    return false;
}

template < typename Key , typename DataType , typename KeyComparator >
bool DAL<Key, DataType, KeyComparator>::insert( const Key & new_key , const DataType & info ); 
{
    m_len++;//!<Atualiza tamanho

}