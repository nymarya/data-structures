#include "dsal.h"

///Construtor padrão
template < typename Key , typename DataType , typename KeyComparator >
DSAL<Key, DataType, KeyComparator>::DSAL( std::size_t size)
:m_capacity( size )
,m_len(0)
,m_data( new Node[size])
{ /* empty*/ }

/// Destrutor
template < typename Key , typename DataType , typename KeyComparator >
DSAL<Key, DataType, KeyComparator>::~DSAL()
{ delete [] m_data; }