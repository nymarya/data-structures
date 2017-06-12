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
{ 
    clear();
    delete [] m_data_table; 
}

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
    auto begin = m_data_table[end].begin();
    while( begin != m_data_table[end].end() ){
        ++before_end;++begin;
    }
    
    m_data_table[end].insert_after(before_end, new_entry);
    m_len++; //!< Atualiza tamanho
    return true;
}

template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove( const KeyType & key ){
    KeyHash hashFunc; //!< Instancia função hash
    KeyEqual equalFunc; //!< Instancia função de comparação

    //!< Calcula posição do elemento
    auto end( hashFunc(key) % m_size );

    //!< Percorre a lista de colisões
    for( auto it( m_data_table[end].before_begin() ); it != m_data_table[ end ].end();){
        auto target(it);
        ++it;
        //!< Compara com as chaves na lista de colisões
        if( equalFunc(it->m_key, key)){
            //!< Anterior aponta para a entrada após it

            m_data_table[ end ].erase_after(target);
            m_len--;
            return true;
        }
    }
    
    return false;
}

template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve ( const KeyType & key , DataType & data ) const{
    KeyHash hashFunc; //!< Instancia função hash
    KeyEqual equalFunc; //!< Instancia função de comparação

    //!< Calcula posição do elemento
    auto end( hashFunc(key) % m_size );

    //!< Percorre a lista de colisões
    for( auto it( m_data_table[end].before_begin() ); it != m_data_table[ end ].end(); ++it){
        //!< Compara com as chaves na lista de colisões
        if( equalFunc(it->m_key, key)){
            //!< Se encontrar a chave, guarda o valor
            data = it->m_data;
            return true;
        }
    }
    
    return false;
}

template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear( void ){
    //!< Percore tabela
    for( auto i(  0ul ); i < m_size; ++i){
        //!< Limpa cada lista encadeada
        m_data_table[i].clear();
    }
}

template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
unsigned long int HashTbl<KeyType, DataType, KeyHash, KeyEqual>::count( ) const
{  return m_len; }