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

        std::size_t m_capacity; //!< Tamanho máximo de armazenamento
        std::size_t m_len;      //!< Tamanho lógico
        Node * m_data;          //!< Área de armazenamento

        int _search ( const Key & _x ) const;

    public:
        //=== Membros especiais
        DAL();
        //=== Interface pública

};

#endif