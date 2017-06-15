#include "hash_tbl.h"
#include <vector>
#include <cassert>
#include <iomanip>
#include <algorithm>

 struct Account{
    int bank_code;
    int branch_code;
    int account_code;
    float balance;
    std::string name;

    using AcctKey = std::pair < std::string , int >;
    using AcctKeyV3 = std::tuple < std::string , int , int , int >; //nome, banco, agencia e conta

    Account( int b=1, int ag=11, int ac=11111, float c=0.0, 
    std::string n="Anonimo")
    :bank_code(b), branch_code(ag), account_code(ac), balance(c), name(n)
    {/*empty*/}

    AcctKey get_key()
    {
        std::pair<std::string, int> p(name, account_code);
        return p; 
    }

    AcctKeyV3 get_key_v3()
    {
        std::tuple<std::string, int, int, int> p(name, bank_code, branch_code, account_code);
        return p; 
    }
    
     friend std::ostream &operator<<( std::ostream & _os, const Account & acct );
};

 std::ostream &operator<<( std::ostream & _os, const Account & acct ){
        _os << "[ Cliente: " << std::setw(18) << acct.name <<
            " | Banco: " << std::setw(3)  << acct.bank_code <<
            " | Agência: " << std::setw(3) << acct.branch_code <<
            " | Conta: " << std::setw(6) << acct.account_code <<
            " | Saldo: R$" << std::setw(10) << std::fixed << std::setprecision(2) << acct.balance << "> ]";
        return _os;
    }

//=== Função de dispersão para versão 2
struct KeyHash {
    std::size_t operator()( const Account::AcctKey & k_ ) const
    {

    return (std::hash <std::string >()( k_.first )  xor
        std::hash < int >()( k_.second )) ;
    }
};

//=== Função de comparação para versao 2
struct KeyEqual{
    bool operator()( const Account::AcctKey &lhs, const Account::AcctKey &rhs) const{
        return (lhs.first == rhs.first and lhs.second == rhs.second);
    }
};

//== Função de dispersão para versão 3
struct KeyHashV3 {
    std::size_t operator()( const Account::AcctKeyV3 & k_ ) const
    {
        std::string message = "";

        std::vector< std::string > keys = { std::get<0>(k_)
            , std::to_string( std::get<1>(k_) )
            , std::to_string( std::get<2>(k_) )
            , std::to_string( std::get<3>(k_) ) };

        std::sort(keys.begin(), keys.end() );

        for( auto e: keys )
            message += e;

        return (std::hash <std::string >()( message )  ) ;
    }
};

//== Função de comparação para versão 3
struct KeyEqualV3{
    bool operator()( const Account::AcctKeyV3 &lhs, const Account::AcctKeyV3 &rhs) const{
        return (std::get<0>(lhs) == std::get<0>(rhs)  and std::get<1>(lhs)  == std::get<1>(rhs) 
                and std::get<2>(lhs) == std::get<2>(rhs) and std::get<3>(lhs)  == std::get<3>(rhs) );
    }
};

int main(){

    std::vector<Account> accounts = {
        Account( 1, 51, 98765, 2000.50, "John Lennon"),
        Account( 2, 10, 56789, 1500.25, "Ringo Starr"),
        Account( 3, 40, 54321, 10000.0, "Paul McCartney"),
        Account( 4, 91, 12345, 1111.75, "George Harrison"),
        Account( 5, 67, 13579, 2100.00, "Pete Best"),
        Account( 6, 76, 24680, 2010.00, "Stuart Sutcliffe"),
    };

    //Cria tabela hash de tamanho 5
    HashTbl< AcctKey, Account, KeyHash, KeyEqual> hash_table(5);
    
    //Teste empty()
    assert( hash_table.empty());
    
    //Teste insert()
    assert( hash_table.insert( accounts[0].get_key(), accounts[0]) );
    assert( hash_table.empty() == false);
    assert( hash_table.count() == 1);

    assert( hash_table.insert( accounts[1].get_key(), accounts[1]) );
    assert( hash_table.insert( accounts[2].get_key(), accounts[2]) );
    assert( hash_table.insert( accounts[3].get_key(), accounts[3]) );
    assert( hash_table.insert( accounts[4].get_key(), accounts[4]) );
    
    //Teste print()
    hash_table.print();
    std::cout << std::endl;

    //Teste remove()
    assert( hash_table.remove( accounts[0].get_key() ));
    assert( hash_table.count() == 4);

    std::cout << "Removendo \"" << accounts[0].name << " \": \n";
    hash_table.print();
    std::cout << std::endl;

    //Teste retrieve()
    Account ac;
    assert( hash_table.retrieve( accounts[0].get_key(), ac ) == false);
    
    assert( hash_table.retrieve( accounts[3].get_key(), ac ));

    KeyEqual cmp;
    assert( cmp(ac.get_key(), accounts[3].get_key()) );

    //Teste rehash()
    assert( hash_table.insert( accounts[5].get_key(), accounts[5]) );

    Account acc(1, 77, 89898, 9000.80, "David Bowie"); //!< Rehash chamado aqui
    assert( hash_table.insert( acc.get_key(), acc) );

    Account a;
    assert( hash_table.insert( a.get_key(), a) );

    //Atualiza 
    Account rec(2, 10, 56789, 2500.25, "Ringo Starr");
    hash_table.insert( rec.get_key(), rec);

    std::cout << "Clientes na tabela da versão 2:\n";
    hash_table.print();
    std::cout << std::endl;

    ///////////////////////////////////
    //                               //
    // Teste com versao 3 das chaves //
    //                               //
    ///////////////////////////////////

    HashTbl< Account::AcctKeyV3, Account, KeyHashV3, KeyEqualV3> hash_table_v3(5);
    
    //Teste empty()
    assert( hash_table_v3.empty());
    
    //Teste insert()
    assert( hash_table_v3.insert( accounts[0].get_key_v3(), accounts[0]) );
    assert( hash_table_v3.empty() == false);
    assert( hash_table_v3.count() == 1);

    assert( hash_table_v3.insert( accounts[1].get_key_v3(), accounts[1]) );
    assert( hash_table_v3.insert( accounts[2].get_key_v3(), accounts[2]) );
    assert( hash_table_v3.insert( accounts[3].get_key_v3(), accounts[3]) );
    assert( hash_table_v3.insert( accounts[4].get_key_v3(), accounts[4]) );

    //Teste remove()
    assert( hash_table_v3.remove( accounts[0].get_key_v3() ));
    assert( hash_table_v3.count() == 4);

    //Teste retrieve()
    assert( hash_table_v3.retrieve( accounts[0].get_key_v3(), ac ) == false);
    
    assert( hash_table_v3.retrieve( accounts[3].get_key_v3(), ac ));

    KeyEqualV3 cmp_v3;
    assert( cmp_v3(ac.get_key_v3(), accounts[3].get_key_v3()) );

    //Teste rehash()
    assert( hash_table_v3.insert( accounts[5].get_key_v3(), accounts[5]) );

    assert( hash_table_v3.insert( acc.get_key_v3(), acc) );

    assert( hash_table_v3.insert( a.get_key_v3(), a) );

    //Atualiza 
    hash_table_v3.insert( rec.get_key_v3(), rec);

    std::cout << "Clientes na tabela da versão 3:\n";
    hash_table_v3.print();


    std::cout << "\n>>>Passou em todos os testes!\n";

    return 0;
}
