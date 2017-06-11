#include "hash_tbl.h"

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

    HashTbl< AcctKey, Account, KeyHash, KeyEqual> hash_table;
}