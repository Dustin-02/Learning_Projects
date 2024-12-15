#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

// Student may implement another function as need
class AbstractEmployee{
    virtual void AskForPromotion()=0;
};

class Employee:AbstractEmployee {
private:
    string Name;
    string Company;
    int Age;
public:
    void setName(string name) {        
        Name = name;
        for (char c : name) {
            if (!isdigit(c)) Name = "Invalid";
        }        
    }
    void setCompany(string comp){
        Company = comp;
    }
    void setAge(int age) {
        if (age > 18) Age = age;
        else Age = 18;
    }
    string getName() {
        return Name;
    }
    string getCompany() {
        return Company;
    }
    int getAge(){
        return Age;
    }
    
    void IntroduceMyself() {
        cout << "Name - " << Name << '\n';
        cout << "Age - " << Age << '\n';
        cout << "Company - " << Company << '\n';
    }    
    void AskForPromotion() {
        if (Age > 30) 
            cout << Name << " got promoted" << '\n';
        else
            cout << Name << ", no promotion for you" << '\n';
    }
    Employee(string name, string company, int age) {
        Name = name;
        Company = company;
        Age = age;
    }   
    virtual void Work(){
        cout << Name << " is working!" << '\n';
    }
};

class Developer: public Employee {
private:
    string FavLang;
public:     
    Developer(string name, string company, int age, string favLang)
    :Employee(name, company, age)
    {
        FavLang = favLang;
    }
    string getFavLang(){
        return FavLang;
    }
    void fixBug() {
        cout << getName() << " fixed bug using " << getFavLang() << '\n';
    }
    void Work(){
        cout << getName() << " is coding " << getFavLang() << '\n';
    }
};

int main(){
    Employee emp1 = Employee("Thu", "NCKUOH", 32);
    Developer dev1 = Developer("Tin", "NCKUOH", 21, "Python");
    Employee *p1 = &dev1; 
    Employee *p2 = &emp1; 
    p1->Work();
    p2->Work();
};

/* 
struct LInode{
    string data;
    LInode *pNext; 
};
void LI_insert(LINode * & pHead, const string & a, int idx){
    if (pHead){
        if (idx) {
            
        }
        else {
            /* LINode *p = new LINode(a, nullptr);
            p->pNext = pHead;
            pHead - p; 
        }
    }
    else { pHead = new LINode{a, nullptr}}} 
*/

// insert
    // pHead = empty -> 
    // index = 0 -> 
// remove at index


/* Dynamic
    int *pNum = NULL;
    pNum = new int;
    delete pNum;
*/
 
/*  Dynamic
    char* pGrade = NULL;
    pGrade = new char[size];
    delete[] pGrade;
*/

/*  function template
    template <typename T, typename U>;
    U max(T x, U y)
*/

/* struct
    struct student{
        std::string name;
        double gpa;
        bool enrolled;
    }
    int main(){
        student student1;
        student.name = "Spongebob";
        student.gpa = 7.6;
        student.enrolled = true;
        
    }
*/

/* typedef
typedef std::string text_t; */

/* type conversion
int correct = 8;
    int total = 10;
    double avr = correct/(double)total * 100;
    std::cout << avr << '\n'; */

/* get input: getline(cin >> ws, name); */
/* max, min, pow, sqrt, abs, round, ceil, floor */
/* switch case break default */
/* condition ? expression 1 : expression 2; */
/* logical operation: && || ! */
/* string: 
.length() - (name.length() > 10) ? cout << "name should not be over 12 char" : cout << "welcome " << name << "!\n";
.empty() - name.empty() ? cout << "Blank name is not allowed" : cout << "Welcome " << name;
.clear - clear the argument value 
.append(@hcmut.edu.vn) - append at the last value 
.at(3) - return the character at specific location 
.insert(0, "@") - return the string with @ added at O 
.find(" ") - return the location where " " is situated
.erase(0, 3) - return the string of which is truncated from 0 - 3 */
// break - exit the loop
// continue - neglect or skip the current step
// pseudo-random srand(time(NULL))| (rand() % 6) + 1 - random number from 1 to 6

/*  
    std::string students[] = {"Spongebob", "Patrick", "Squidward"};
    for (int i = 0; i < sizeof(students)/sizeof(students[0]); i++){
        std::cout << students[i] << '\n';

    int grades[] = {65,72,83,92};
    for (int grade : grades) {
        std::cout << grade << '\n';
    }
    } */

/* call array
double total = getTotal(prices, size);
double getTotal(double prices[], int size){
    double total = 0;
    for (int i = 0; i < size; i++){
        total += prices[i];
    }
    return total;
}; */

// fill(begin, end, value)

