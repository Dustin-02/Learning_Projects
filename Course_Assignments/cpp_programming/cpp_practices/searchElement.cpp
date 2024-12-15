#include <iostream>;
using namespace std;

int searchArray(int array[], int size, int num);

int main() {    
    int number[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(number)/sizeof(number[0]);
    int myNum;
    std::cout << "Please enter your number u want to search for: " << '\n';
    std::cin >> myNum;

    int index = searchArray(number, size, myNum);
    if (index != -1) std::cout << "The index for your number is: " << index << '\n';
    else std::cout << "Your number is not found in the array!\n";
    return 0;        
}

int searchArray(int array[], int size, int num){
    int index = 0;
    for (int i = 0; i < size; i++){
        if (array[i] == num) {
            return i;
        }
    }
    return -1;
}