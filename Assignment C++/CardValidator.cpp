#include <iostream>;
using namespace std;


int getDigit(const int number);
int sumOddDigit(const std::string cardNumber);
int sumEvenDigit(const std::string cardNumber);
int main(){
    std::string cardNumber;
    std::cout << "input card number: ";
    getline(std::cin, cardNumber);
    
    int sumEven = sumEvenDigit(cardNumber);
    int sumOdd = sumOddDigit(cardNumber);
    int sum = sumEven + sumOdd;
    
    if (sum % 10 == 0) std::cout << cardNumber << " is valid\n";
    else std::cout << cardNumber << " is not valid\n";

    return 0;
}
int getDigit(const int number){

    return (number % 10) + (number / 10);
}
int sumOddDigit(const std::string cardNumber){
    int sum = 0;
    for (int i = cardNumber.size() - 1; i >= 0; i -= 2){
        sum += getDigit(cardNumber[i] - '0');
    }
    return sum;
}
int sumEvenDigit(const std::string cardNumber){
    int sum = 0;
    for (int i = cardNumber.size() - 2; i >= 0; i -= 2){
        sum += getDigit((cardNumber[i] - '0') * 2);
    }
    return sum;
}