# HashTbl

## Sobre a classe

A classe ```HashTbl``` implementa uma tabela de dispersão, estrutura de dados cujo maior diferencial é possuir inserção, remoção e busca com custo, em média, constante. Por ser uma estrutura baseada em chave-valor, para realizar as operações básicas citadas acima, é preciso definir as chaves.

## Como executar

| #       | Descrição           | Comando  |
| :------------- |:-------------| :-----|
| 1      | Compilar | ```$ make``` |
| 2      | Executar   | ```$ ./build/drive_hash``` |

## Como utilizar em outros programas

1º Copie os arquivos .h e .inl da pasta ```include/```<br/>
2º Inclua o arquivo .h no seu programa.<br/>
3º Instancie a classe com o namespace ```ls```  o tipo dos elementos entre ```<>```

### Exemplo de uso
```cpp
#include <iostream>
#include "hash_tbl.h"

//Tipo de dado com função que retorna as chaves
struct Account{
    int bank_code;
    int branch_code;
    int account_code;
    float balance;
    std::string name;

    using AcctKey = std::pair < std::string , int >;

    Account( int b=1, int ag=11, int ac=11111, float c=0.0, 
    std::string n="Anonimo")
    :bank_code(b), branch_code(ag), account_code(ac), balance(c), name(n)
    {/*empty*/}

    AcctKey get_key()
    {
        std::pair<std::string, int> p(name, account_code);
        return p; 
    }
};

//Functor para a dispersão
struct KeyHash {
    std::size_t operator()( const Account::AcctKey & k_ ) const
    {

    return (std::hash <std::string >()( k_.first )  xor
        std::hash < int >()( k_.second )) ;
    }
};

//Functor para a comparação
struct KeyEqual{
    bool operator()( const Account::AcctKey &lhs, const Account::AcctKey &rhs) const{
        return (lhs.first == rhs.first and lhs.second == rhs.second);
    }
};

int main(){
    //Dados a serem inseridos na tabela
    Account accounts[] = {
        Account( 1, 51, 98765, 2000.50, "John Lennon"),
        Account( 2, 10, 56789, 1500.25, "Ringo Starr"),
        Account( 3, 40, 54321, 10000.0, "Paul McCartney"),
        Account( 4, 91, 12345, 1111.75, "George Harrison"),
    };

    //Cria tabela hash de tamanho 5
    HashTbl< AcctKey, Account, KeyHash, KeyEqual> hash_table(5);
    
    //Insere os elementos na tabela
    hash_table.insert( accounts[0].get_key(), accounts[0]);
    hash_table.insert( accounts[1].get_key(), accounts[1]);
    hash_table.insert( accounts[2].get_key(), accounts[2]);
    hash_table.insert( accounts[3].get_key(), accounts[3]);
    
    std::cout << "Temos " << hash_table.count() << " clientes ativos\n";
    
    //Remove "John Lennon"
    hash_table.remove( accounts[0].get_key() );
    std::cout << "Temos " << hash_table.count() << " clientes ativos\n";
    
    //Atualiza saldo de "Ringo Starr" 
    Account acc(2, 10, 56789, 2500.25, "Ringo Starr");
    hash_table.insert( acc.get_key(), acc);
    
    //Recupera o novo saldo de "Ringo Starr"
    Account rec;
    hash_table.retrieve( accounts[1].get_key(), rec);
    std::cout << "O cliente " << rec.name << "possui R$" << rec.balance << std::endl;

    return 0;
}
```

A saída do programa seria:
```
Temos 5 clientes ativos
Temos 4 clientes ativos
O cliente Ringo Starr possui R$2500.25
```


## Autoria

Desenvolvido por Mayra Dantas de Azevedo (<mayradazevedo@gmail.com >), 2017.1

&copy; IMD/UFRN 2017.
