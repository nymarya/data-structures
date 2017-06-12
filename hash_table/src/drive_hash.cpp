#include "hash_tbl.h"
#include <vector>
#include <cassert>
int main(){

    struct Account{
        int bank;
        int agency;
        int account;
        float cash;
        std::string name;

        using AcctKey = std::pair < std::string , int >;

        Account( int b=1, int ag=11, int ac=11111, float c=0.0, 
        std::string n="")
        :bank(b), agency(ag), account(ac), cash(c), name(n)
        {/*empty*/}

        AcctKey get_key()
        {
            std::pair<std::string, int> p(name, account);
            return p; 
        }
    };

    struct KeyHash {
        std::size_t operator()( const Account::AcctKey & k_ ) const
        {

        return (std::hash <std::string >()( k_.first )  xor
            std::hash < int >()( k_.second )) ;
        }
    };

    struct KeyEqual{
        bool operator()( const Account::AcctKey &lhs, const Account::AcctKey &rhs) const{
            return (lhs.first == rhs.first and lhs.second == rhs.second);
        }
    };

    std::vector<Account> accounts = {
        Account( 1, 51, 98765, 2000.50, "John Lennon"),
        Account( 2, 10, 56789, 1500.25, "Ringo Starr"),
        Account( 3, 40, 54321, 10000.0, "Paul McCartney"),
        Account( 4, 91, 12345, 1111.75, "George Harrison"),
    };

    KeyHash hashF;
    std::cout << hashF( accounts[0].get_key() ) % 11 << "\n";
    std::cout << hashF( accounts[1].get_key() ) % 11<< "\n";
    std::cout << hashF( accounts[2].get_key() ) % 11<< "\n";
    std::cout << hashF( accounts[3].get_key() ) % 11<< "\n";

    HashTbl< AcctKey, Account, KeyHash, KeyEqual> hash_table;
    //Teste insert
    assert( hash_table.insert( accounts[0].get_key(), accounts[0]) );
    assert( hash_table.count() == 1);

    assert( hash_table.insert( accounts[1].get_key(), accounts[1]) );
    assert( hash_table.insert( accounts[2].get_key(), accounts[2]) );

    //Teste remove
    assert( hash_table.remove( accounts[0].get_key() ));

    return 0;
}