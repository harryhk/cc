#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;


class User
{
};




class ATM
{
public:

    bool logging()
    {
        cout << "ATM: Log in account " << endl;
        cout << "ATM: enter username and password " << endl;
        string username, password;
        cin>> username >> password;

        // check validation

        _is_logged_in = true;
    }

    bool createNewAccount()
    {
        cout << "ATM: create Accout " << endl;
        _is_logged_in = true;
    }

    void updateAccount( int amount )
    {
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
                    if( choice == 1)
                    {
                        logging(); 
                    }
                    else 
                    {
                        createNewAccount();
                        
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
    User _current_user;

};


int main()
{
    ATM atm;

    atm.run();
    
}
