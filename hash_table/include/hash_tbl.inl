#include "hash_tbl.h"

template < typename KeyType ,
    typename DataType ,
    typename KeyHash ,
    typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::HashTbl(int tbl_size)
:m_data_table( new std::forward_list<Entry>[tbl_size] )
{/* empty*/ }

template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::~HashTbl()
{ delete [] m_data_table; }

template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert( const KeyType & key_ ,
                                                    const DataType & data_item_)
{ 
    
 }