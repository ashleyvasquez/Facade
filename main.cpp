
//Código basado en https://advancedcppwithexamples.blogspot.com/2010/09/c-example-for-facade-design-pattern.html

//El programa utiliza una clase facade que implementa tres subclases privadas para aprobar un préstamo.


#include <iostream>
#include<string>


using namespace std;


class Client
        {
                public:
                Client (const string& name) : name_(name){}
                const string& Name(void)
                {
                    return name_;
                }
                private:
                Client();
                string name_;
        };

/**
 * La 'Subsystem ClassA': Verifica en el banco si tiene ahorros suficientes
 */

class Bank
{
public:
    bool HasSufficientSavings(Client c, int amount)
    {
        cout << "Consultando cuentas de " <<c.Name()<<endl;
        return true;
    }
};


/**
 * La 'Subsystem ClassB': Verifica si tiene un buen historial de crédito
 */

class Credit
{
public:
    bool HasGoodCredit(Client c, int amount)
    {
        cout << "Consultando historial de crédito de " <<c.Name()<<endl;
        return true;
    }
};

/**
 * La 'Subsystem ClassC': Verifica si tiene la posibilidad de pago
 */

class Loan
{
public:
    bool HasPosibility(Client c, int amount)
    {
        cout << "Consultando posibilidad de préstamo para " <<c.Name()<<endl;
        return true;
    }
};

/**
 * La clase Mortgage es la clase Facade que utiliza las Subsystem Class Bank, Credit y Loan que son privadas.
 */
class Mortgage
{
public:
    bool IsEligible(Client cust, int amount)
    {
        cout << cust.Name() << " aplica por un préstamo de $" << amount <<endl;
        bool eligible = true;

        eligible = bank_.HasSufficientSavings(cust, amount);

        if(eligible)
            eligible = loan_.HasPosibility(cust, amount);

        if(eligible)
            eligible = credit_.HasGoodCredit(cust, amount);

        return eligible;
    }

private:
    Bank bank_;
    Loan loan_;
    Credit credit_;
};



int main()
{
    Mortgage mortgage;

    cout << "Igrese su nombre" << endl;
    string nombre;
    cin >> nombre;
    Client client(nombre);

    cout << "Ingrese el monto por el que desea hacer el préstamo" << endl;
    int amount;
    cin >> amount;
    bool eligible = mortgage.IsEligible(client, amount);

    cout << "\n" << client.Name() << ", tu préstamo ha sido:  " << (eligible ? "Aprobado" : "Rechazado") << endl;

    return 0;
}