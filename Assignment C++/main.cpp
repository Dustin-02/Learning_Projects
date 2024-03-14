/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink1.h"

using namespace std;

void sa_tc_01() {
    cout << "----- Sample Testcase 01 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    checkCond(HP1, HP2, EXP1, EXP2, M1, M2);
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E1: " << E1 << endl;
    int result = firstMeet(EXP1, EXP2, E1);
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", result: " << result << endl;
}

void sa_tc_02() {
    cout << "----- Sample Testcase 02 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    checkCond(HP1, HP2, EXP1, EXP2, M1, M2);
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", E2: " << E2 << endl;
    int result = traceLuggage(HP1, EXP1, M1, E2);
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", result: " << result << endl;
}

void sa_tc_03() {
    cout << "----- Sample Testcase 03 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    checkCond(HP1, HP2, EXP1, EXP2, M1, M2);
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", HP2: " << HP2 << ", EXP2: " << EXP2 << ", E3: " << E3 << endl;
    int result = chaseTaxi(HP1, EXP1, HP2, EXP2, E3);
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", HP2: " << HP2 << ", EXP2: " << EXP2 << ", result: " << result << endl;
}

void tc_1234()
{
std::cout << "----- Testcase 1234 -----" << std::endl;
int E2 = 12, HP1 = 34, EXP1 = 56, M1 = 78;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}

void tc_1184()
{
std::cout << "----- Testcase 1184 -----" << std::endl;
int E2 = 44, HP1 = 111, EXP1 = 222, M1 = 333;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}
void tc_1243()
{
std::cout << "----- Testcase 1243 -----" << std::endl;
int E2 = 98, HP1 = 89, EXP1 = 98, M1 = 89;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}

void tc_1342()
{
cout << "----- Testcase 342 -----" << endl;

char email[] = "pf23@hcmut.edu.vn";
char s[] = "aoD1qwr1%%%23";
cout << "email: \"" << email << "\", s: \"" << s << "\"\n";

int result = checkPassword(s, email);
cout << "email: \"" << email << "\", s: \"" << s
<< "\", result: " << result << endl;
}

void tc_1344()
{
cout << "----- Testcase 344 -----" << endl;

char email[] = "pf23@hcmut.edu.vn";
char s[] = "23$KKKqof@@@@@@34k";
cout << "email: \"" << email << "\", s: \"" << s << "\"\n";

int result = checkPassword(s, email);
cout << "email: \"" << email << "\", s: \"" << s
<< "\", result: " << result << endl;
}

void tc_1343()
{
cout << "----- Testcase 343 -----" << endl;

char email[] = "pf23@hcmut.edu.vn";
char s[] = "qi%$#uur537kfj7!!";
cout << "email: \"" << email << "\", s: \"" << s << "\"\n";

int result = checkPassword(s, email);
cout << "email: \"" << email << "\", s: \"" << s
<< "\", result: " << result << endl;
}
void tc_1161()
{
std::cout << "----- Testcase 1161 -----" << std::endl;
int E2 = 78, HP1 = 200, EXP1 = 300, M1 = 741;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}
void tc_1230()
{
std::cout << "----- Testcase 1230 -----" << std::endl;
int E2 = 24, HP1 = 420, EXP1 = 240, M1 = 2112;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}
void tc_1316()
{
cout << "----- Testcase 316 -----" << endl;
int E3 = 65, HP1 = 420, EXP1 = 598, HP2 = 184, EXP2 = 138;
cout << "E3: " << E3 << ", HP1: " << HP1 << ", EXP1: " << EXP1
<< ", HP2: " << HP2 << ", EXP2: " << EXP2 << endl;

int result = chaseTaxi(HP1, EXP1, HP2, EXP2, E3);
cout << "E3: " << E3 << ", HP1: " << HP1 << ", EXP1: " << EXP1
<< ", HP2: " << HP2 << ", EXP2: " << EXP2
<< ", result: " << result
<< endl;
}

void tc_1153()
{
std::cout << "----- Testcase 1153 -----" << std::endl;
int E2 = 64, HP1 = 128, EXP1 = 2, M1 = 256;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}
void tc_1154()
{
std::cout << "----- Testcase 1154 -----" << std::endl;
int E2 = 78, HP1 = 227, EXP1 = 130, M1 = 777;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}
void tc_1157()
{
std::cout << "----- Testcase 1157 -----" << std::endl;
int E2 = 54, HP1 = 126, EXP1 = 143, M1 = 128;
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << std::endl;
int result = traceLuggage(HP1, EXP1, M1, E2);
std::cout << "E2: " << E2 << ", HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << std::endl;
}
int main(int argc, const char * argv[]) {
    //sa_tc_01();
    //sa_tc_02();
    //sa_tc_03();
    /* const char *arr_pwds[] = {"pink@123", "123!pink", "1234#xyz", "pink#pink", "pink#pink", "pink@123"};
    int num_pwds = sizeof(arr_pwds) / sizeof(arr_pwds[0]);
    int result = findCorrectPassword(arr_pwds, num_pwds);
    cout << result;
    return 0; */
    //tc_1234();
    //tc_1184();
    //tc_1243();
    //tc_1342();
    //tc_1344();
    //tc_1343();
    //tc_1161();
    //tc_1230();
    //tc_1316();
    //tc_1153();
    //tc_1154();
    tc_1157();
}