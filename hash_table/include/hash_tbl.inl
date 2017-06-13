#include "hash_tbl.h"

/// Construtor padrão
template < typename KeyType ,
    typename DataType ,
    typename KeyHash ,
    typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::HashTbl(int tbl_size)
:m_size(tbl_size)
,m_len(0),
m_data_table( new std::forward_list<Entry>[tbl_size] )
{/* empty*/ }

/// Destrutor
template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::~HashTbl()
{ 
    clear(); //!< Limpa elementos da tabela
    delete [] m_data_table; //!< Libera a memória
}

/// Insere na tabela a informaç̃ao contida em 'data_item' e associada a uma chave 'key'
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert( const KeyType & key,
                                                       const DataType & data_item)
{ 
    //!< Se fator de carga for maior ou igual a 1, chama método rehash()
    if( m_len / m_size >= 1 ) rehash();

    KeyHash hashFunc; //!< Instancia função hash
    KeyEqual equalFunc; //!< Instancia função de comparação

    Entry new_entry(key, data_item); //!< Cria entrada com dados inseridos

    //!< Calcula posição na qual o dado será inserido
    auto end( hashFunc(key) % m_size );

    //!< Percorre a lista encadeada
    for( auto it( m_data_table[end].begin() ); it != m_data_table[ end ].end(); it++){
        //!< Compara com as chaves na lista de colisões
        if( equalFunc(it->m_key, new_entry.m_key)){
            //!< Atualiza valores se a chave já estiver na lista
            it->m_data = data_item;
            return false;
        }
    }
    
    //!< Insere elemento
    m_data_table[end].push_front(new_entry);
    m_len++; //!< Atualiza tamanho
    return true;
}

/// Remove da tabela a informaç̃ao associada a uma chave 'key'
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove( const KeyType & key )
{
    KeyHash hashFunc; //!< Instancia função hash
    KeyEqual equalFunc; //!< Instancia função de comparação

    //!< Calcula posição do elemento
    auto end( hashFunc(key) % m_size );

    //!< Percorre a lista de colisões
    for( auto it( m_data_table[end].before_begin() ); it != m_data_table[ end ].end(); /*empty*/){
        auto prev_target(it); //!< Guarda o anterior
        ++it; //!< Avança o ponteiro
        
        //!< Compara com as chaves na lista de colisões
        if( equalFunc(it->m_key, key)){
            //!< Apaga o posterior a perv_target(it)
            m_data_table[ end ].erase_after(prev_target);
            m_len--; //!< Atualiza tamanho
            return true;
        }
    }
    
    //!< Não encontrou a chave, então retorna falso
    return false;
}

/// Recupera da tabela a informaç̃ao associada a uma chave 'key' e guarda o elemento recuperado em 'data'. 
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve ( const KeyType & key , DataType & data ) const
{
    KeyHash hashFunc; //!< Instancia função hash
    KeyEqual equalFunc; //!< Instancia função de comparação

    //!< Calcula posição do elemento
    auto end( hashFunc(key) % m_size );

    //!< Percorre a lista de colisões
    for( auto it( m_data_table[end].begin() ); it != m_data_table[ end ].end(); ++it){
        //!< Compara com as chaves na lista de colisões
        if( equalFunc(it->m_key, key)){
            //!< Se encontrar a chave, guarda o valor
            data = it->m_data;
            return true;
        }
    }
    
    //!< Não encontrou a chave, então retorna falso
    return false;
}

/// Libera toda a memória associada às listas de colisão da tabela, removendo todos os seus elementos.
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear( void ){
    //!< Percore tabela
    for( auto i(  0ul ); i < m_size; ++i){
        //!< Limpa cada lista encadeada
        m_data_table[i].clear();
    }
    m_len = 0; //!< Atualiza tamanho
}

/// Verifica se a tabela de dispersão está vazia.
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty( ) const
{
    //!< Percorre a tabela de dispersão
    for( auto i(0ul); i< m_size; ++i){
        //<! Verifica se todas as listas estão vazias
        if( not m_data_table[i].empty() )return false;     
    }
   return true;
}

/// Consulta o número de elementos na tabela.
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
unsigned long int HashTbl<KeyType, DataType, KeyHash, KeyEqual>::count( ) const
{  return m_len; }

/// Método que imprime os itens da tabela de dispersão
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::print( ) const
{
    //!< Percorre a tabela de dispersão
    for( auto i(0ul); i< m_size; ++i){
        //<! Percorre a lista de colisões
        for( auto it(m_data_table[i].cbegin() ); it != m_data_table[i].cend();++it ){
            std::cout << it->m_data << "\n";
        }
    }

}

/// Aumenta a capacidade de armazenamento da tabela hash se  λ > 1.0.
template < typename KeyType, typename DataType, typename KeyHash ,typename KeyEqual >
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash( )
{
    //!< Calcula menor número primo maior que o dobro do tamanho da tabela
    auto new_size( 2 * m_size); //!< Novo tamanho
    auto is_prime = false;
    while( not is_prime ){
        new_size++; //!< Checa próximo número
        is_prime = true; //!< Liga a flag

        //!< Verifica de 2 até raiz do número
        for( auto i(2ul); i <= sqrt(new_size); ++i)
            if( new_size % i == 0) is_prime = false;       
    }

    //!< Aloca nova memória
    auto temp = new std::forward_list<Entry>[ new_size ];

    KeyHash hashFunc; //!< Instancia função de dispersão

    //!< Percorre a tabela de dispersão
    for( auto i(0ul); i< m_size; ++i){
        //<! Percorre a lista de colisões
        for( auto it(m_data_table[i].cbegin() ); it != m_data_table[i].cend();++it ){
            //!< Calcula posição na qual o dado será inserido
            auto end( hashFunc(it->m_key) % m_size );
            
            //!< Insere elemento na nova lista;
            temp[end].push_front(  Entry(it->m_key, it->m_data));
        }
    }

    //!< Libera espaço de armazenamento existente
    delete [] m_data_table;

    m_data_table = temp; //!< Transfere o ponteiro para o novo endereço
    m_size = new_size;   //!< Atualiza tamanho
}