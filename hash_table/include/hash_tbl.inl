#include "hash_tbl.h"

template < typename KeyType ,
    typename DataType ,
    typename KeyHash ,
    typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::HashTbl(int tbl_size)
:m_size(tbl_size)
,m_len(0),
m_data_table( new std::forward_list<Entry>[tbl_size] )
{/* empty*/ }

template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::~HashTbl()
{ delete [] m_data_table; }

template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert( const KeyType & key,
                                                       const DataType & data_item)
{ 
    KeyHash hashFunc; //!< Instancia função hash
    KeyEqual equalFunc; //!< Instancia função de comparação

    Entry new_entry(key, data_item); //!< Cria entrada com dados inseridos

    //!< Calcula posição na qual o dado será inserido
    auto end( hashFunc(key) % m_size );

    //!< Percorre a lista encadeada
    for( auto it( m_data_table[end].begin() ); it != m_data_table[ end ].end(); it++){
        //!< Compara com as chaves na lista de colisões
        if( equalFunc(it->m_key, new_entry.m_key)){
            //!< Atualiza valores
            it->m_data = data_item;
            return false;
        }
    }
    //!< Se o item não estiver na lista, ele será inserido
    auto before_end = m_data_table[end].before_begin();
    for (auto& _ : m_data_table[end])
        ++before_end;
    m_data_table[end].insert_after(before_end, new_entry);
    m_len++;
    return true;
}