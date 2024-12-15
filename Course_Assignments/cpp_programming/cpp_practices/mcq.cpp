#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

int main(){
    std::string questions[] = {"1. What year was C++ created?",
                    "2. Who intented C++?",
                    "3. What is the predecessor of C++?",
                    "4. Is the Earth flat?"};
    std::string choices[][4] = {{"A. 69", "B. 75", "C. 85", "D. 89"},
                        {"A. Rossum", "B. Strousstrup", "C. ABC", "D. xyz"},
                        {"A. C", "B. C+", "C. C--", "D. B++"},
                        {"A. yes", "B. no", "C. sometimes", "D. What's Earth?"}};
    char answerKey[] = {'C', 'B', 'A', 'B'};

    int size = sizeof(questions)/sizeof(questions[0]);
    char guess;
    int score = 0;
    
    std::cout << "Quiz game!!!\n";
    for (int i = 0; i < size; i++){        
        std::cout << questions[i] << '\n';
        for (int j = 0; j < (sizeof(choices[i])/sizeof(choices[i][0])); j++){
            std::cout << choices[i][j] << '\n';
        }        
        std::cout << "------------" << '\n';
        std::cout << "Enter your answer (A, B, C, D): ";
        std::cin >> guess;
        if (guess == answerKey[i]){
            score += 1;
            std::cout << "!Correct!\n";
        }  else std::cout << "!Incorrect!\n";
        std::cout << "------------" << '\n';
    }

    std::cout << "Your total score is: " << score; 
    return 0;
}