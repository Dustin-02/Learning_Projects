// Banking practice

#include <iostream>
#include <iomanip>

void ShowBalance(double balance);
double deposit();
double withdraw(double balance);

int main() {   
    double balance = 0;
    int choice;

    do{
        std::cout << "Enter your choice: \n";
        std::cout << "1. Show balance\n";
        std::cout << "2. Deposit money\n";
        std::cout << "3. Withdraw money\n";
        std::cout << "4. Exit\n";
        std::cin >> choice;

        switch(choice){
            case 1:                
                ShowBalance(balance);
                break;
            case 2:                
                balance += deposit();
                ShowBalance(balance);
                break;
            case 3:
                balance -= withdraw(balance);
                ShowBalance(balance);
                break;
            case 4: 
                std::cout << "Thank you for visiting\n";
                break;
            default:
                std::cout << "Please enter right choice\n";
        } 
    } while (choice != 4);
        
    return 0;
}

void ShowBalance(double balance) {
    std::cout << " Your balance is: $" << std::setprecision(2) << std::fixed << balance << '\n';
}

double deposit() {
    double amount = 0;
    
    do {
        std::cout << "enter your deposit amount: ";
        std::cin >> amount;    
        if (amount < 0) std::cout << "negative is not allowed!\n";
    }while (amount < 0);   
    return amount;
}

double withdraw(double balance) {
    double amount;
    do {
    std::cout << "please enter your withdrawn amount: ";
    std::cin >> amount;
    if (amount < 0) std::cout << "negative is not valid\n";
    if (amount > balance) {
        std::cout << "Insufficient funds\n"; 
    } 
    } while (amount < 0 || amount > balance);
    return amount;
}