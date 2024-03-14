#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Check Condition
int checkHP(int & HP) {
    if (HP > 666) {
        return 666;
    } else if (HP < 0) {
        return 0;
    }
    return HP;
};

int checkEXP(int & EXP) {
    if (EXP > 600) {
        return 600;
    } else if (EXP < 0) {
        return 0;
    }
    return EXP;
};

int checkM(int & M) {
    if (M > 3000) {
        return 3000;
    } else if (M < 0) {
        return 0;
    }
    return M;
};

void checkCond(int & HP1, int & HP2, int & EXP1, int & EXP2, int & M1, int & M2) {
    HP1 = checkHP(HP1);
    HP2 = checkHP(HP2);
    EXP1 = checkEXP(EXP1);
    EXP2 = checkEXP(EXP2);
    M1 = checkM(M1);
    M2 = checkM(M2);
}

bool stop(int tra, int M0) {
        if (tra > 0.5 * M0) return true; 
        else return false;
};

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    // TODO: Complete this function
    if (e1 >= 0 && e1 <= 3) {
        switch (e1) {
            case 0:
                exp2 += 29;
                break;
            case 1:
                exp2 += 45;
                break;
            case 2:
                exp2 += 75;
                break;
            case 3:
                exp2 += 29 + 45 + 75;
                break;
        }
        int D = e1 * 3 + exp1 * 7;
        if (D % 2 == 0) {
            exp1 = ceil(exp1 + static_cast<float>(D)/200);            
        } else {
            exp1 = ceil(exp1 - static_cast<float>(D)/100);            
        }

    } else if (e1 >= 4 && e1 <=99) {
        if (e1 <= 19) {
            exp2 = ceil(exp2 + (static_cast<float>(e1)/4 + 19));
        } else if (e1 <= 49) {
            exp2 = ceil(exp2 + (static_cast<float>(e1)/9 + 21));
        } else if (e1 <= 65) {
            exp2 = ceil(exp2 + (static_cast<float>(e1)/16 + 17));            
        } else if (e1 <= 79) {
            exp2 = ceil(exp2 +(static_cast<float>(e1)/4 + 19));            
            if (exp2 > 200) {
                exp2 = ceil(exp2 + (static_cast<float>(e1)/9 + 21));                
            }
        } else {
            exp2 = ceil(exp2 + (static_cast<float>(e1)/4 + 19));            
            exp2 = ceil(exp2 + (static_cast<float>(e1)/9 + 21));        
            if (exp2 > 400) {
                exp2 = ceil(exp2 + (static_cast<float>(e1)/16 + 17));                
                exp2 = ceil(exp2*115.0/100);                
            }            
        }
        exp1 -= e1;
    }  else {
        return -99;
    }
    exp1 = checkEXP(exp1); exp2 = checkEXP(exp2);
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    // TODO: Complete this function
    // PATH 1
    float temp_1 = sqrt(static_cast<float>(EXP1));
    int sqrt_s1 = round(temp_1);
    int S1 = sqrt_s1 * sqrt_s1;
    float P1;
    if (EXP1 >= S1) P1 = 100; else P1 = ((static_cast<float>(EXP1) / S1 + 80) / 123)*100;
    
    //PATH 2    
    if (E2 % 2 == 1){
        int chi = 0;
        int M0 = M1;            
        while (true) {            
            if (HP1 < 200) {            
                M1 -= 150;            
                HP1 = ceil(HP1 * 13.0/10); 
                chi += 150;
                M1 = checkM(M1); HP1 = checkHP(HP1);
                if (stop(chi, M0)) break;
            } else {
                M1 -= 70;
                HP1 = ceil(HP1 * 11.0/10); 
                chi +=70;
                M1 = checkM(M1); HP1 = checkHP(HP1);
                if (stop(chi, M0)) break;     
            }            

            if (EXP1 < 400) {
                M1 -= 200;
                EXP1 = ceil(EXP1 * 113.0/100);
                chi += 200;
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (stop(chi, M0)) break;
            } else {
                M1 -= 120;
                EXP1 = ceil(EXP1 * 113.0/100);
                chi += 120;
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (stop(chi, M0)) break;  
            }                           

            if (EXP1 < 300) {
                M1 -= 100;
                EXP1 = ceil(EXP1 * 9.0/10);
                chi += 100;
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (stop(chi, M0)) break;     
            } else {
                M1 -= 120;
                EXP1 = ceil(EXP1 * 9.0/10);
                chi += 120;                
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (stop(chi, M0)) break;     
            }                    
        };
    } else {
        int a = 0;
        while (a < 1) {
            if (HP1 < 200) {            
                M1 -= 150;            
                HP1 = ceil(HP1 * 13.0/10); 
                M1 = checkM(M1); HP1 = checkHP(HP1);
                if (M1 <= 0) break;
            } else {
                M1 -= 70;
                HP1 = ceil(HP1 * 11.0/10);
                M1 = checkM(M1); HP1 = checkHP(HP1);
                if (M1 <= 0) break;
            }            

            if (EXP1 < 400) {
                M1 -= 200;
                EXP1 = ceil(EXP1 * 113.0/100);
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (M1 <= 0) break;
            } else {
                M1 -= 120; 
                EXP1 = ceil(EXP1 * 113.0/100);
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (M1 <= 0) break;
            }   
            

            if (EXP1 < 300) {
                M1 -= 100;   
                EXP1 = ceil(EXP1 * 9.0/10);
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (M1 <= 0) break;
            } else {
                M1 -= 120;  
                EXP1 = ceil(EXP1 * 9.0/10);
                M1 = checkM(M1); EXP1 = checkEXP(EXP1);
                if (M1 <= 0) break;
            }
            a++;                        
        }
    }
    EXP1 = ceil(EXP1 * 117.0/100);
    HP1 = ceil(HP1 * 83.0/100);
    HP1 = checkHP(HP1); EXP1 = checkEXP(EXP1);
    float temp_2 = sqrt(static_cast<float>(EXP1));
    int sqrt_s2 = round(temp_2);
    int S2 = sqrt_s2 * sqrt_s2;
    float P2;
    if (EXP1 >= S2) P2 = 100; else P2 = 100*((static_cast<float>(EXP1) / S2 + 80) / 123);

    //Path 3
    int P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    int i = 0;
    if (E2 < 10) i = E2;
    else i = (E2 % 10 + E2 / 10) % 10;
    int P3 = P[i];

    //After 3 paths
    int meanP;
    if ((P1 == 100) && (P2 == 100) && (P3 == 100)) {
        EXP1 = ceil(EXP1 * 75.0/100);
    } else {
        meanP = (P1 + P2 + P3) / 3;
        if (meanP < 50) {
            HP1 = ceil(HP1 * 85.0/100);
            EXP1 = ceil(EXP1 * 115.0/100);
        } else {
            HP1 = ceil(HP1 * 9.0/10);
            EXP1 = ceil(EXP1 * 12.0/10);
        };
    HP1 = checkHP(HP1); EXP1 = checkEXP(EXP1);
    };
    return HP1 + EXP1 + M1;     
}

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
    // ma tran taxi
    int Matrix[10][10] = {0};
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            Matrix[i][j] = ((E3 * j) + (i * 2)) * (i - j); // tinh diem            
        }
    };
    
    // ma tran Sherlock & Watson
    int SWMatrix[10][10] = {0};
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int maxScore = INT_MIN;
            // xet duong cheo trai
            for (int k = i, l = j; k < 10 && l < 10; ++k, ++l) {
                maxScore = max(maxScore, Matrix[l][k]);
            };
            for (int k = i, l = j; k >= 0 && l >= 0; --k, --l) {
                maxScore = max(maxScore, Matrix[l][k]);
            };
            // xet duong cheo phai
            for (int k = i, l = j; k < 10 && l >= 0; ++k, --l) {
                maxScore = max(maxScore, Matrix[l][k]);
            };
            for (int k = i, l = j; k >= 0 && l < 10; --k, ++l) {
                maxScore = max(maxScore, Matrix[l][k]);
            };
            SWMatrix[j][i] = abs(maxScore); // tinh diem            
        };
    }; 

    // diem gap nhau
    int count_1 = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (Matrix[i][j] > 2 * E3) count_1 += 1;            
        }            
    };    
    int count_2 = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (Matrix[i][j] < -E3) count_2 += 1;            
        };            
    };
    int i = count_1;
    int j = count_2;
    while (i >= 10) i = i % 10 + i / 10;
    while (j >= 10) j = j % 10 + j / 10;

    //duoi kip hay khong
    if (abs(Matrix[i][j]) > SWMatrix[i][j]) {
        EXP1 = ceil(EXP1 * 88.0/100);
        EXP2 = ceil(EXP2 * 88.0/100);
        HP1 = ceil(HP1 * 9.0/10);
        HP2 = ceil(HP2 * 9.0/10);
        HP1 = checkHP(HP1); HP2 = checkHP(HP2); 
        EXP1 = checkEXP(EXP1); EXP2 = checkEXP(EXP2);
        return Matrix[i][j];
    } else {
        EXP1 = ceil(EXP1 * 112.0/100);
        EXP2 = ceil(EXP2 * 112.0/100);
        HP1 = ceil(HP1 * 11.0/10);
        HP2 = ceil(HP2 * 11.0/10);
        HP1 = checkHP(HP1); HP2 = checkHP(HP2); 
        EXP1 = checkEXP(EXP1); EXP2 = checkEXP(EXP2);
        return SWMatrix[i][j];
    };

    return -1;
}; 

// Task 4
bool validPassword(const char* s, string se) {
    const char* kitu = "@#%$!";
    
    // Kiểm tra độ dài mật khẩu
    if (strlen(s) < 8 || strlen(s) > 20) {
        return false;
    }
    
    // Kiểm tra chuỗi 'se' không xuất hiện trong mật khẩu
    if (strstr(s, se.c_str()) != nullptr) {
        return false;
    }

    // Kiểm tra các ký tự liên tiếp giống nhau
    for (const char *i = s + 2; *i != '\0'; i++){        
        if ((*i == *(i-1)) && (*i == *(i-2))) {
            return false;
        }
    }
    bool co_kitu = false;
    for (const char *i = s; *i != '\0'; i++){   
        if (!(isdigit(*i) || isalpha(*i) || strchr(kitu, *i) != nullptr)) {
            return false;
        }     
        if (strchr(kitu, *i) != nullptr) {
            co_kitu = true;
        }        
    }
    if (!co_kitu) return false;
    return true;       
}

int checkPassword(const char * s, const char * email) {
    // TODO: Complete this function    
    if (strlen(email) > 100) {
        cout << "invalid input" << endl; 
        return -99;
    }

    int count = 0;
    for (const char *i = email; *i != '\0'; i++) {                        
        if (*i == '@') count++;
        if (count >= 2) {
        cout << "invalid input" << endl; 
        return -99;
        }
    }
    string se = "";
    for (const char *i = email; *i != '@' && *i != '\0'; i++) {        
        se += *i;
    }; 

    // Check mat khau    
    if (validPassword(s, se)) {
        return -10;
    }    
    if (strlen(s) < 8) {
            return -1;            
    }            
    if (strlen(s) > 20) {
            return -2;            
    }
    if (strstr(s, se.c_str()) != nullptr) {
        int sei = strstr(s, se.c_str()) - s;
        return -(300 + sei);            
    }
    
    for (const char *i = s; *i != '\0'; i++){        
        if ((i - s > 1) && (*i == *(i-1)) && (*i == *(i-2))) {
            int sci = i - s - 2;
            return -(400 + sci);                   
            break;     
        }
    }    
    const char* kitu = "@#%$!";        
    bool co_kitu = false;
    for (const char *i = s; *i != '\0'; i++){   
        if (strchr(kitu, *i) != nullptr) {
            co_kitu = true;                   
            break;         
        }
    }
    if (!co_kitu) {
        return -5;                
    }
    
    for (const char *i = s; *i != '\0'; i++){   
        if (!(isdigit(*i) || isalpha(*i) || strchr(kitu, *i) != nullptr)) {
            return (i-s);  
            break;          
        }
    }
    
    return 10;
} 

// Task 5
struct PasswordInfo {
    const char* password;
    int count;
    int length;
};

int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    // TODO: Complete this function
    PasswordInfo password_info[num_pwds];    
    for (int i = 0; i < num_pwds; ++i) {
        password_info[i].password = arr_pwds[i];
        password_info[i].count = 0;
        password_info[i].length = strlen(arr_pwds[i]);
    }
    for (int i = 0; i < num_pwds; ++i) {
        for (int j = 0; j < num_pwds; ++j) {
            if (strcmp(password_info[i].password, arr_pwds[j]) == 0) {
                password_info[i].count++;
            }
        }
    }    

    int max_count = 0;
    int max_length = 0;
    const char* correct_password = nullptr;
    for (int i = 0; i < num_pwds; ++i) {
        if (password_info[i].count > max_count || (password_info[i].count == max_count && password_info[i].length > max_length)) {
            correct_password = password_info[i].password;
            max_count = password_info[i].count;
            max_length = password_info[i].length;
        }
    }
    for (int i = 0; i < num_pwds; ++i) {
        if (strcmp(arr_pwds[i], correct_password) == 0) {
            return i;
        }
    }
    return -1;
} 

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////