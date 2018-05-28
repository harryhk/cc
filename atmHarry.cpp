#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
using namespace std;


class User
{
public:
    User(string name, string password ): username_m( name ), password_m( password ){}
    Account & getAccount(){ return account_m; } // has to be reference
    bool isValidPassword( string & pass ) { return pass == password_m; }

private:
    string username_m;
    string password_m;
    Account account_m;
};

class Account
{
public:
    Account(): balance_m(0) {}

    void update( int amount )
    {
        if( balance_m + amount < 0 )
        {
            throw runtime_error( "not enough balance" );
        }

        balance += amount;
    }

private:
    int balance_m; 
};

class UsersInfo
{
public:
    UsersInfo()
    {
        userInfo_m["harry"] = User("harry", "haha");
        userInfo_m["cc"] = User("cc", "cc");
    }
    
    User & getUser( string & name, string & pass )
    { 
        // TODO: check exist, password
        userInfo_m[name]; 
    }

    User & createUser( string & name, string & pass )
    {
        // TODO: check validity 
        userInfo_m[name] = User(name, pass );
        return userInfo_m[name];
    }


private:
    unordered_map<string, User> userInfo_m; //stores username --> user 
};


class ATM
{
public:
    
    ATM( UsersInfo * p ): _all_users(p) {}
    
    User & logging()
    {
        cout << "ATM: Log in account " << endl;
        cout << "ATM: enter username and password " << endl;
        string username, password;
        cin>> username >> password;
        
        // check validation throw exception when not match
        auto user = _all_users.getUser(username, password);

        _is_logged_in = true;
        return user;
    }
    
    User & createNewAccount() //throw exception when user exist
    {
        cout << "ATM: create Accout " << endl;
        cout << "ATM: enter username and password" << endl;
        string username, password;
        cin>> username >> password;
        auto user = _all_users.createUser( username, password );
        _is_logged_in = true;
        return user;
    }
    

    void insertCash( int amount )
    {
        cout << "ATM: insertCash" << amount << endl;
    }

    void dispenseCash( int amount )
    {
        cout << "ATM: dispense" << amount << endl;
    }


    void updateAccount( int amount )
    {
        if( amount > 0 )
        {
            insertCash( amount );
            _current_user.getAccount().update( amount );
        }
        else
        {
            //TODO dispense case
            _current_user.getAccount().update( amount );
            dispenseCash( amount );
        }
        cout << "ATM: update Account " << amount << endl;
    }
    
    void reset()
    {
        _is_logged_in = false;
        _current_user = User();
    }
    
    void run()
    {
        while(1)
        {
            try
            {
                if( ! _is_logged_in )
                {
                    cout << "ATM: New user(1) or Log in(2) " << endl;
                    int choice;
                    cin >> choice;
                    if( choice == 2)
                    {
                        _current_user = logging();
                    }
                    else
                    {
                        _current_user = createNewAccount();
                        
                    }
                }
                
                if( _is_logged_in )
                {
                    cout << "ATM: Deposite(1) or Withdraw(2) " << endl;
                    int choice, amount;
                    cin >> choice;
                    cout << "ATM: Enter amount " << endl;
                    cin >> amount;
                    
                    if( choice == 1 )
                    {
                        updateAccount( amount );
                    }
                    else
                    {
                        updateAccount( -1 * amount );
                    }
                }
                
                reset();
            }
            catch( runtime_error &e )
            {
                cerr << "ATM: error: " << e.what() << endl;
                reset();
            }
            
        }
    }
    
private:
    bool _is_logged_in;
    User & _current_user;
    UsersInfo * _all_users;
    double _cash;
};


int main()
{
    allUsers * users = new allUsers();
    ATM atm(users);
    atm.run();
    
}
