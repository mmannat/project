#include <iostream>
#include <vector>
#include <string>

class BankAccount {
private:
    double balance;
    std::string accountNumber;

public:
    BankAccount() : balance(0.0), accountNumber("") {}
    BankAccount(double initialBalance, std::string accountNumber) : balance(initialBalance), accountNumber(accountNumber) {}

    double getBalance() const { return balance; }
    std::string getAccountNumber() const { return accountNumber; }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        else {
            return false;
        }
    }

    void deposit(double amount) {
        balance += amount;
    }
};

class Customer {
private:
    std::string name;
    std::vector<BankAccount*> accounts;

public:
    Customer(std::string name) : name(name) {}

    std::string getName() const { return name; }
    const std::vector<BankAccount*>& getAccounts() const { return accounts; }

    void addAccount(BankAccount* account) {
        accounts.push_back(account);
    }

    void removeAccount(BankAccount* account) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (*it == account) {
                accounts.erase(it);
                break;
            }
        }
    }
};

class Bank {
private:
    std::vector<Customer*> customers;

public:
    const std::vector<Customer*>& getCustomers() const { return customers; }

    void addCustomer(Customer* customer) {
        customers.push_back(customer);
    }

    void removeCustomer(Customer* customer) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (*it == customer) {
                customers.erase(it);
                break;
            }
        }
    }

    bool transfer(BankAccount* from, BankAccount* to, double amount) {
        if (from->withdraw(amount)) {
            to->deposit(amount);
            return true;
        }
        else {
            return false;
        }
    }
};

int main() {
    BankAccount* acc1 = new BankAccount(1000.0, "123456");
    BankAccount* acc2 = new BankAccount(500.0, "654321");

    Customer* cust1 = new Customer("Alice");
    cust1->addAccount(acc1);

    Customer* cust2 = new Customer("Bob");
    cust2->addAccount(acc2);

    Bank* myBank = new Bank();
    myBank->addCustomer(cust1);
    myBank->addCustomer(cust2);

    std::cout << "Initial balances:" << std::endl;
    std::cout << "Alice's account balance: " << cust1->getAccounts()[0]->getBalance() << std::endl;
    std::cout << "Bob's account balance: " << cust2->getAccounts()[0]->getBalance() << std::endl;

    if (myBank->transfer(acc1, acc2, 500.0)) {
        std::cout << "Transfer successful" << std::endl;
    }
    else {
        std::cout << "Transfer failed" << std::endl;
    }

    std::cout << "Balances after transfer:" << std::endl;
    std::cout << "Alice's account balance: " << cust1->getAccounts()[0]->getBalance() << std::endl;
    std::cout << "Bob's account balance: " << cust2->getAccounts()[0]->getBalance() << std::endl;

    delete acc1;
    delete acc2;
   
}
