#include <iostream>
#include <ctime>

char userChoice();
char computerChoice();
void show(char choice);
void winner(char player, char computer);

int main(){
    char player, computer;
    player = userChoice();
    std::cout << "Your choice is: ";
    show(player);

    computer = computerChoice();
    std::cout << "Computer's choice is: ";
    show(computer);

    winner(player, computer);

    return 0;
}


char userChoice(){
    char player;
    do{
        std::cout << "enter your decision: ";
        std::cin >> player;   
        if ((player != 'r') && (player != 'p') && (player != 's')) std::cout << "Wrong parameter\n";
    } while ((player != 'r') && (player != 'p') && (player != 's'));    
    return player;
}

char computerChoice() {
    srand(time(NULL));
    int num = (rand() % 3) + 1;
    switch(num){
        case 1: 
            return 'r';
            break;
        case 2: 
            return 'p';
            break;
        case 3:
            return 's';
            break;
    }    
} 

void show(char choice){
    switch(choice) {
        case 'p': 
            std::cout << "Paper!\n";
            break;
        case 's':
            std::cout << "Scissor!\n";
            break;
        case 'r':
            std::cout << "Rock!\n";
            break;        
    }
}

void winner(char player, char computer) {
    if (player == 'p'){
        switch(computer){
            case 'p': 
                std::cout << "DRAW\n";
                break;
            case 's': 
                std::cout << "LOSE\n";
                break;
            case 'r': 
                std::cout << "WIN\n";
                break;
        }
    } else if (player == 'r'){
        switch(computer){
            case 'r': 
                std::cout << "DRAW\n";
                break;
            case 'p': 
                std::cout << "LOSE\n";
                break;
            case 's': 
                std::cout << "WIN\n";
                break;
        }       
    } else {
        switch(computer){
            case 's': 
                std::cout << "DRAW\n";
                break;
            case 'r': 
                std::cout << "LOSE\n";
                break;
            case 'p': 
                std::cout << "WIN\n";
                break;
        }
    }            
}