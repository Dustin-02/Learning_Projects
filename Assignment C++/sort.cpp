#include <iostream>;
using namespace std;

void sortArray(int array[], int size);

int main(){
    // sort array
    int numbers[] = {10, 1, 2, 9, 6, 4, 7, 5, 8, 3};
    int size = sizeof(numbers)/sizeof(numbers[0]);

    sortArray(numbers, size);    

    for (int element : numbers){
        std::cout << element << " ";
    }
    
}


void sortArray(int array[], int size){    
    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){            
            if (array[j] > array[j+1]) {
                int temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            }
        }
    }
}