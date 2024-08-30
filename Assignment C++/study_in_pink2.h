/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
// class MovingObject;
// class Position;
// class Configuration;
// class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType {PATH, WALL, FAKE_WALL};
enum RobotType { C=0, S, W, SW };

int distance(const Position &pos1, const Position &pos2){
    int result = abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
    return result;
}

int getNum(string a){
    int act_num = 0;
    for (char ch : a){
        int num = ch - '0';
        act_num = act_num * 10 + num;
    }
    return act_num;
};

class MapElement {
protected:
    ElementType type;        
public:
    MapElement(ElementType in_type) : type(in_type) {}
    virtual ~MapElement() {}
    virtual ElementType getType() const {
        return type;
    }
    virtual int getReqExp() const {}
};

class Path : public MapElement {
public:
    Path() : MapElement(ElementType::PATH) {}                
};

class Wall : public MapElement {
public:
    Wall() : MapElement(WALL) {}
};

class FakeWall : public MapElement {
    private:
        int req_exp;                        
    public:                
        FakeWall(int in_req_exp) : MapElement(FAKE_WALL), req_exp(in_req_exp) {}        
        int getReqExp() const {
            return req_exp;
        }
};

class Map {
private:
    int num_rows, num_cols;
    MapElement*** map; 
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) 
        : num_rows(num_rows), num_cols(num_cols) {                
        map = new MapElement**[num_rows];
        for (int i = 0; i < num_rows; i++) {
            map[i] = new MapElement*[num_cols];
            for (int j = 0; j < num_cols; j++) {
                map[i][j] = nullptr; // Khởi tạo tất cả các ô là nullptr
            }
        }

        for (int i = 0; i < num_walls; i++){            
            map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall();
        }
        for (int i = 0; i < num_fake_walls; i++){
            map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()] = 
            new FakeWall((array_fake_walls[i].getRow() * 257 + array_fake_walls[i].getCol() * 139 + 89) % 900 +1);
        }
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_cols; j++) {
                if (!map[i][j]) map[i][j] = new Path();                
            }
        }
    };
    ~Map(){
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    };
    bool isValid (const Position & pos , MovingObject * mv_obj ) const {
        if (mv_obj->getName() == "Watson" && this->map[pos.getRow()][pos.getCol()]->getType() == FAKE_WALL) {
            if (mv_obj->getEXP() && mv_obj->getEXP() < this->map[pos.getRow()][pos.getCol()]->getReqExp()) return false;
        }       
        return true;
    };
    int getNum_rows() const {
        return num_rows;
    };
    int getNum_cols() const {
        return num_cols;
    }
    MapElement*** getMap() const {
        return map;
    }
};

class Position {
private:
    int r, c;
public:
    static const Position npos;    
    Position(int r=0, int c=0) {
        this->r = r;
        this->c = c;
    };
    Position(const string & str_pos){
        size_t startStr = str_pos.find('(');
        size_t endStr = str_pos.find(')');
        string numStr = str_pos.substr(startStr + 1, endStr - startStr - 1);
        stringstream ss(numStr);
        char comma;
        ss >> r >> comma >> c;        
    }

    int getRow() const {
        return r;
    };
    int getCol() const {
        return c;
    };
    void setRow(int r) {
        this->r = r;
    };
    void setCol(int c) {
        this->c = c;
    };

    string str() const {
        stringstream ss;
        ss << '(' << r << ',' << c;
        return ss.str();
    };
    bool isEqual(int in_r, int in_c) const {        
        return ((this->r == in_r) && (this->c == in_c));
    };

    bool operator!=(const Position& other_pos) const {
        return (this->r != other_pos.r || this->c != other_pos.c);
    }
    bool operator==(const Position& other_pos) const {
        return (this->r == other_pos.r || this->c == other_pos.c);
    }
};

const Position Position::npos(-1,-1);

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;
public:
    MovingObject(int index, const Position pos, Map * map, const string & name="")
    : index(index), pos(pos), map(map), name(name){}
    virtual ~MovingObject() {}
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const {
        return pos;
    };
    string getName() const {return name;}
    virtual void move() = 0;
    virtual string str() const = 0;    
        virtual int getHP() const {}
    virtual void checkHP(int hp) {}
    virtual int getEXP() const {}
    virtual void checkEXP(int exp) {}
};

class Sherlock: public Character {
private:
    string moving_rule;
    int hp;
    int exp;
    size_t move_index;
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Sherlock", 13), moving_rule(moving_rule), hp(init_hp), exp(init_exp), move_index(0)
    {
        checkHP(hp);
        checkEXP(exp);
        bag = new SherlockBag(this);
    };    
    
    ~Sherlock() {
        delete bag;
    }

    Position getNextPosition() override {        
        if (hp == 0 || exp == 0) return Position::npos;
        char direction = moving_rule[move_index % moving_rule.size()];
        move_index++;
        int next_row = this->pos.getRow();
        int next_col = this->pos.getCol();
        switch (direction) {
            case 'L':
                next_col--;
                break;
            case 'R':
                next_col++;
                break;
            case 'U':
                next_row--;
                break;
            case 'D':
                next_row++;
                break;
        }
        
        Position next_pos(next_row, next_col);
        if (map->isValid(next_pos, this)) {            
            return next_pos;
        } else return Position::npos;
    };
    void move() {
        Position next_pos = getNextPosition();
        if (next_pos != Position::npos) {
            pos = next_pos;
        }
    };
    string str() {
        string result = "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
        return result;
    };      
    int getHP() const override {return hp;}
    int getEXP() const override {return exp;}
    void checkHP(int hp) override {
        if (hp > 500) this->hp = 500;        
        else this->hp = hp;
    } 
    void checkEXP(int exp) override {
        if (exp > 900) this->exp = 900; 
        else this->exp = exp;       
    }

};

class Watson: public Character {
private:
    string moving_rule;
    int hp;
    int exp;
    size_t move_index;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Watson", 15), moving_rule(moving_rule), hp(init_hp), exp(init_exp), move_index(0)
    {
        checkHP(hp);
        checkEXP(exp);
        bag = new WatsonBag(this);
    };    
    
    ~Watson() {
        delete bag;
    }

    Position getNextPosition() override {        
        if (hp == 0 || exp == 0) return Position::npos;
        char direction = moving_rule[move_index % moving_rule.size()];
        move_index++;
        int next_row = pos.getRow();
        int next_col = pos.getCol();
        switch (direction) {
            case 'L':
                next_col--;
                break;
            case 'R':
                next_col++;
                break;
            case 'U':
                next_row--;
                break;
            case 'D':
                next_row++;
                break;
        }
        
        Position next_pos(next_row, next_col);
        if (map->isValid(next_pos, this)) {            
            return next_pos;
        } else return Position::npos;
    };
    void move() {
        Position next_pos = getNextPosition();
        if (next_pos != Position::npos) {
            pos = next_pos;
        }
    };
    string str() {
        string result = "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
        return result;
    };      
    void checkHP(int hp) override {
        if (hp > 500) this->hp = 500;  
        else this->hp = hp;       
    }
    void checkEXP(int exp) override {
        if (exp > 900) this->exp = 900;  
        else this->exp = exp;       
    } 
    int getHP() const override {return hp;}
    int getEXP() const override {return exp;}

    bool ArrestCriminal() {}
};

class Criminal: public Character {
private:
    int move_count;
    ArrayMovingObject* moving_objects;
    Sherlock* sherlock;
    Watson* watson;
public:
    Criminal(int index, const Position & init_pos, Map * map, ArrayMovingObject* arr, Sherlock * sherlock, Watson * watson)
    : Character(index, init_pos, map, "Criminal"), move_count(0), moving_objects(arr), sherlock(sherlock), watson(watson) {}
    ~Criminal() {}

    bool isOccupied(const Position &pos) {
        return !((pos != sherlock->getCurrentPosition()) && (pos != watson->getCurrentPosition()));
    }    
    Position getNextPosition() override {             
        int dir = 0;
        int max_distance = 0;        
        struct classifier {       
            Position pos;     
            int dx;
            int dy;            
        };
        classifier direction[8];

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {                
                if ((dx == 0) && (dy == 0)) continue;
                Position spec_pos(pos.getRow() + dy, pos.getCol() + dx);                
                if (map->isValid(spec_pos, this) && !isOccupied(spec_pos)) {                    
                    int d_Sherlock = distance(spec_pos, sherlock->getCurrentPosition());
                    int d_Watson = distance(spec_pos, watson->getCurrentPosition());
                    int total_distance = d_Sherlock + d_Watson;
                    if (total_distance > max_distance) {
                        max_distance = total_distance;
                    }
                    direction[dir++] = {spec_pos, dx, dy};
                }   
            }
        }
        
        struct Priority {
            char dir;
            int dx;
            int dy;
        };
        Priority priorities[] = {
            {'U', 0, -1},
            {'L', -1, 0},
            {'D', 0, 1},
            {'R', 1, 0}
        };

        Position best_position;
        for (auto &priority : priorities) {
            for (int i = 0; i < dir; i++) {
                if (direction[i].dx == priority.dx && direction[i].dy == priority.dy) {
                    int d_Sherlock = distance(direction[i].pos, sherlock->getCurrentPosition());
                    int d_Watson = distance(direction[i].pos, watson->getCurrentPosition());
                    int total_distance = d_Sherlock + d_Watson;
                    if (total_distance == max_distance) {
                        best_position = direction[i].pos;
                        return best_position;
                    }
                }
            }
        }
        return Position::npos;
    };
    void move() {
        Position next_pos = getNextPosition();
        if (next_pos != Position::npos) {
            pos = next_pos;
            move_count++;
            if (move_count % 3 == 0) createRobot();
        }
    };
    void createRobot(){
        if (this->moving_objects->isFull()) return;
        Position robotPos = pos; // Position before the move

        if (this->moving_objects->size() == 0) {
            RobotC* robot = new RobotC(moving_objects->size(), robotPos, map, this);
            moving_objects->add(robot);
        } else {
            // Calculate distances to Sherlock and Watson
            int distanceToSherlock = distance(pos, sherlock->getCurrentPosition());
            int distanceToWatson = distance(pos, watson->getCurrentPosition());

            if (distanceToSherlock < distanceToWatson) {
                RobotS* robot = new RobotS(moving_objects->size(), robotPos, map, this, sherlock);
                moving_objects->add(robot);
            } else if (distanceToWatson < distanceToSherlock) {
                RobotW* robot = new RobotW(moving_objects->size(), robotPos, map, this, watson);
                moving_objects->add(robot);
            } else {
                RobotSW* robot = new RobotSW(moving_objects->size(), robotPos, map, this, sherlock, watson);
                moving_objects->add(robot);
            }
        }
    }
    string str() {
        string result = "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
        return result;
    };      
};

class ArrayMovingObject {
private:
    // TODO
    MovingObject** arr_mv_objs;
    int count;
    int capacity;
public:
    ArrayMovingObject(int capacity) : count(0), capacity(capacity) {
        arr_mv_objs = new MovingObject*[capacity];
        moveAll();
    }

    ~ArrayMovingObject() {
        for (int i = 0; i < count; ++i) {
            delete arr_mv_objs[i];
        }
        delete[] arr_mv_objs;
    } ;
    bool isFull() const {
        return capacity == count;
    };
    bool add(MovingObject * mv_obj) {
        if (isFull()) {
            return false;
        }
        arr_mv_objs[count++] = mv_obj;
        return true;        
    };
    MovingObject * get(int index) const {
        if (index >= 0 && index < count) {
            return arr_mv_objs[index];
        }
        return nullptr;
    };
    int size() const{
        return count;
    }; // return current number of elements in the array
    string str() const{
        string result = "ArrayMovingObject[count=" + to_string(count) + "]" + ";capacity=" + to_string(capacity); 
        for (int i = 0; i < count; i++){
            result += arr_mv_objs[i]->str();
            if (i < count - 1) {
                result += ";";
            }
        }
        result += "]";
        return result;
    };
    void moveAll() {
        for (int i = 0; i < count; ++i) {
            arr_mv_objs[i]->move();
        }
    }
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO
    int map_num_rows, map_num_cols, max_num_moving_objects, num_walls, num_fake_walls, 
        sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp, num_steps;
    Position* arr_walls;
    Position* arr_fake_walls;
    Position sherlock_init_pos, watson_init_pos, criminal_init_pos;
    string sherlock_moving_rule, watson_moving_rule;
public:    
    void parseArrayPositions(const std::string& value, Position* &positions, int& num_positions) {
        num_positions = 0;
        for (char c : value) {
            if (c == '(') num_positions++;
        }
        
        positions = new Position[num_positions];
        int index = 0;
        std::string temp;

        for (char c : value) {
            if (c == '[' || c == ']') continue;
            if (c == ';') {
                positions[index++] = Position(temp);
                temp.clear();
            } else {
                temp += c;
            }
        }
        if (!temp.empty()) {
            positions[index] = Position(temp);
        }
    }
    
    Configuration(const string & filepath){
        ifstream file(filepath);
        std::string line;
        struct map{
            string key;
            string value;
        };
        map config[15];
        int i_config = 0;
        // arr_walls = nullptr; arr_fake_walls = nullptr;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                config[i_config++] = {key, value};
            }
        }
        file.close();

        for (int i = 0; i < i_config; ++i) {
            if (config[i].key == "MAP_NUM_ROWS") {
                map_num_rows = std::stoi(config[i].value);
            } else if (config[i].key == "MAP_NUM_COLS") {
                map_num_cols = std::stoi(config[i].value);
            } else if (config[i].key == "MAX_NUM_MOVING_OBJECTS") {
                max_num_moving_objects = std::stoi(config[i].value);
            } else if (config[i].key == "ARRAY_WALLS") {                
                parseArrayPositions(config[i].value, arr_walls, num_walls);
            } else if (config[i].key == "ARRAY_FAKE_WALLS") {
                parseArrayPositions(config[i].value, arr_fake_walls, num_fake_walls);
            } else if (config[i].key == "SHERLOCK_MOVING_RULE") {
                sherlock_moving_rule = config[i].value;
            } else if (config[i].key == "SHERLOCK_INIT_POS") {
                sherlock_init_pos = Position(config[i].value);
            } else if (config[i].key == "SHERLOCK_INIT_HP") {
                sherlock_init_hp = std::stoi(config[i].value);
            } else if (config[i].key == "SHERLOCK_INIT_EXP") {
                sherlock_init_exp = std::stoi(config[i].value);
            } else if (config[i].key == "WATSON_MOVING_RULE") {
                watson_moving_rule = config[i].value;
            } else if (config[i].key == "WATSON_INIT_POS") {
                watson_init_pos = Position(config[i].value);
            } else if (config[i].key == "WATSON_INIT_HP") {
                watson_init_hp = std::stoi(config[i].value);
            } else if (config[i].key == "WATSON_INIT_EXP") {
                watson_init_exp = std::stoi(config[i].value);
            } else if (config[i].key == "CRIMINAL_INIT_POS") {
                criminal_init_pos = Position(config[i].value);
            } else if (config[i].key == "NUM_STEPS") {
                num_steps = std::stoi(config[i].value);
            }
        }
    };
    ~Configuration(){
        delete[] arr_walls;
        delete[] arr_fake_walls;        
    };
    string str() const {
        std::stringstream ss;
        ss << "Configuration[\n"
        << "MAP_NUM_ROWS=" << map_num_rows << "\n"
        << "MAP_NUM_COLS=" << map_num_cols << "\n"
        << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << "\n"
        << "ARRAY_WALLS=[";
        for (int i = 0; i < num_walls; ++i) {
            ss << arr_walls[i].str() << (i < num_walls - 1 ? ";" : "");
        }
        ss << "]\n"
        << "ARRAY_FAKE_WALLS=[";
        for (int i = 0; i < num_fake_walls; ++i) {
            ss << arr_fake_walls[i].str() << (i < num_fake_walls - 1 ? ";" : "");
        }
        ss << "]\n"
        << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << "\n"
        << "SHERLOCK_INIT_POS=" << sherlock_init_pos.str() << "\n"
        << "SHERLOCK_INIT_HP=" << sherlock_init_hp << "\n"
        << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << "\n"
        << "WATSON_MOVING_RULE=" << watson_moving_rule << "\n"
        << "WATSON_INIT_POS=" << watson_init_pos.str() << "\n"
        << "WATSON_INIT_HP=" << watson_init_hp << "\n"
        << "WATSON_INIT_EXP=" << watson_init_exp << "\n"
        << "CRIMINAL_INIT_POS=" << criminal_init_pos.str() << "\n"
        << "NUM_STEPS=" << num_steps << "\n"
        << "]";
        return ss.str();
    };

    Position get_s_init_pos() const {return sherlock_init_pos;}
    Position get_w_init_pos() const {return watson_init_pos;}
    Position get_c_init_pos() const {return criminal_init_pos;}
    int get_s_init_hp() const {return sherlock_init_hp;}
    int get_s_init_exp() const {return sherlock_init_exp;}
    int get_w_init_hp() const {return watson_init_hp;}
    int get_w_init_exp() const {return watson_init_exp;}
    string get_s_moving_rule() const {return sherlock_moving_rule;}
    string get_w_moving_rule() const {return watson_moving_rule;}
};

class Robot: public MovingObject{
protected:
    RobotType robot_type;
    BaseItem * item;
    struct classifier {       
        Position pos;     
        int distance;
        int dx;
        int dy;            
    };  
    static Position optimalPos(classifier* direction, int num_dir, int compVal){
        struct Priority {
            char dir;
            int dx;
            int dy;
        };
        Priority priorities[] = {
            {'U', 0, -1},
            {'L', -1, 0},
            {'D', 0, 1},
            {'R', 1, 0}
        };

        Position optimal_position;
        for (auto &priority : priorities) {
            for (int i = 0; i < num_dir; i++) {
                if (direction[i].dx == priority.dx && direction[i].dy == priority.dy) {                
                    if (direction[i].distance == compVal) {
                        optimal_position = direction[i].pos;
                        return optimal_position;
                    }
                }
            }
        }
        return Position::npos;
    };
    static Position optimalPos_2(classifier* direction, int num_dir, int compVal){
        struct Priority {
            char dir;
            int dx;
            int dy;
        };
        Priority priorities[] = {
            {'U', 0, -2},
            {'L', -2, 0},
            {'D', 0, 2},
            {'R', 2, 0}
        };

        Position optimal_position;
        for (auto &priority : priorities) {
            for (int i = 0; i < num_dir; i++) {
                if (direction[i].dx == priority.dx && direction[i].dy == priority.dy) {                
                    if (direction[i].distance == compVal) {                        
                        return direction[i].pos;
                    }
                }
            }
        }
        return Position::npos;
    };
    static bool moveAllowed(Position next_pos, Map* map){
        MapElement*** element_map = map->getMap();
        if (element_map) {
            int row = next_pos.getRow();
            int col = next_pos.getCol();
            
            // Kiểm tra xem vị trí tiếp theo có nằm trong biên của bản đồ không
            if (row >= 0 && row < map->getNum_rows() &&
                col >= 0 && col < map->getNum_cols() &&
                element_map[row][col] && element_map[row][col]->getType() == WALL) {
                return false;
            }
        }
            // Kiểm tra xem ô đó có phải là Wall không
        return true;
    }
    static Position getClosestPos(const Position& pos, Map* map, MovingObject* robot){
        int num_dir = 0;
        int min_distance = INT_MAX;            
        classifier direction[8];

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {                
                if ((dx == 0) && (dy == 0)) continue;
                Position spec_pos(pos.getRow() + dy, pos.getCol() + dx);                
                if (moveAllowed(spec_pos, map)) {                    
                    int spec_dis = distance(spec_pos, robot->getCurrentPosition());                                    
                    min_distance = std::min(min_distance, spec_dis);
                    direction[num_dir++] = {spec_pos, spec_dis, dx, dy};
                }   
            }
        }

        return optimalPos(direction, num_dir, min_distance);
    }
public:
    Robot(int index, const Position& init_pos, Map* map, RobotType type, const string& name="")
        : MovingObject(index, pos, map, name), robot_type(type), item(nullptr) 
    {
        generateItem();
    }
    virtual ~Robot() { delete item; }
    BaseItem * getItem() const { return item; }
    RobotType getType() const { return robot_type; }
    Position getPosition() const { return pos; }

    virtual Position getNextPosition() {}
    virtual int getDistance() const {}
    virtual void move() override {
        Position next_pos = getNextPosition();
        if (next_pos != Position::npos) {
            pos = next_pos;
        }
    }
    virtual string str() const override {
        stringstream ss;
        ss << "Robot[pos=" << pos.str() << ";type=";
        switch (robot_type) {
        case RobotType::C:
            ss << "C";
            break;
        case RobotType::S:
            ss << "S";
            break;
        case RobotType::W:
            ss << "W";
            break;
        case RobotType::SW:
            ss << "SW";
            break;
        }
        ss << ";dist=";                
        if (robot_type != C) ss << getDistance();
        ss << "]";
        return ss.str();
    }
    void generateItem() {
        int i = pos.getRow();
        int j = pos.getCol();
        int p = i * j;

        int s = 0;
        int temp = p;
        while (temp > 0) {
            s += temp % 10;
            temp /= 10;
        }

        while (s > 9) {
            int new_s = 0;
            while (s > 0) {
                new_s += s % 10;
                s /= 10;
            }
            s = new_s;
        }
        if (s >= 0 && s <= 1) {
            item = new MagicBook();
        } else if (s >= 2 && s <= 3) {
            item = new EnergyDrink();
        } else if (s >= 4 && s <= 5) {
            item = new FirstAid();
        } else if (s >= 6 && s <= 7) {
            item = new ExcemptionCard();
        } else if (s >= 8 && s <= 9) {
            int t = (i*11 + j)%4;
            if (t == 0) {
                item = new PassingCard("RobotS");
            } else if (t == 1) {
                item = new PassingCard("RobotC");
            } else if (t == 2) {
                item = new PassingCard("RobotSW");
            } else {
                item = new PassingCard("all");
            }
        }
    }
};

class RobotC: public Robot{
private:
    Criminal* criminal;
public:
    RobotC(int index, const Position & init_pos, Map * map, Criminal* criminal) 
        : Robot(index, init_pos, map, RobotType::C, "RobotC"), criminal(criminal) {}
    
    Position getNextPosition() override {
        Position next_pos = criminal->getCurrentPosition();        
        return next_pos;
    }
    int getDistance(Sherlock* sherlock) const {
        return distance(getPosition(), sherlock->getCurrentPosition());
    }
    int getDistance(Watson* watson) const {
        return distance(getPosition(), watson->getCurrentPosition());
    }
};

class RobotS : public Robot {
private:
    Criminal* criminal;
    Sherlock* sherlock;
public:
    RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
        : Robot(index, init_pos, map, RobotType::S, "RobotS"), criminal(criminal), sherlock(sherlock) {}
    
    int getDistance(Sherlock* sherlock) const {
        return distance(getPosition(), sherlock->getCurrentPosition());
    }

    Position getNextPosition() override {
        return getClosestPos(sherlock->getCurrentPosition(), map, this);
    }    

};

class RobotW : public Robot {
private:
    Criminal* criminal;
    Watson* watson;
public:
    RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson)
        : Robot(index, init_pos, map, RobotType::W, "RobotW"), criminal(criminal), watson(watson) {}

    int getDistance(Watson* watson) {
        return distance(getPosition(), watson->getCurrentPosition());
    }

    Position getNextPosition() override {
        return getClosestPos(watson->getCurrentPosition(), map, this);
    }
};

class RobotSW : public Robot {
private:
    Criminal* criminal;
    Sherlock* sherlock;
    Watson* watson;

public:
    RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson)
        : Robot(index, init_pos, map, RobotType::SW, "RobotSW"), criminal(criminal), sherlock(sherlock), watson(watson) {}

    int getDistance(Sherlock* sherlock, Watson* watson) {
        return distance(getPosition(), sherlock->getCurrentPosition()) + distance(getPosition(), watson->MovingObject::getCurrentPosition());
    }
    
    Position getNextPosition() override {
        Position pos = getCurrentPosition();
        int num_dir = 0;
        int min_distance = INT_MAX;
        classifier direction[8];

        for (int dx = -2; dx <= 2; dx += 2) {
            for (int dy = -2; dy <= 2; dy += 2) {
                if ((dx == 0) && (dy == 0)) continue;
                Position spec_pos(pos.getRow() + dy, pos.getCol() + dx);
                if (moveAllowed(spec_pos, map)) {
                    int dis = distance(spec_pos, sherlock->getCurrentPosition()) + distance(spec_pos, watson->getCurrentPosition());
                    min_distance = std::min(min_distance, dis);
                    direction[num_dir++] = {spec_pos, dis, dx, dy};
                } 
            }
        }
        
        return optimalPos_2(direction, num_dir, min_distance);
    }
};

class Character: public MovingObject {
public:
    BaseBag* bag;
    Character(int index, const Position pos, Map * map, const string & name="", int max_bag_size)
    : MovingObject(index, pos, map, name), bag(new BaseBag(max_bag_size, this)) {} 
    virtual ~Character() {
        delete bag;
    }

    string getName() {return name;}

    bool hasItem(ItemType itemType) {
        if (bag == nullptr) return false;
        Node* current = bag->getNode();
        while (current) {
            if (current->item->getType() == itemType) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Method to add an item to the character's inventory
    void addItem(BaseItem* item) {
        bag->insert(item);
    }
};

class BaseItem{
private:
    ItemType type;
public:
    BaseItem(ItemType type) : type(type){}
    virtual ~BaseItem() {}
    virtual bool canUse(Character* obj, Robot * robot) = 0;
    virtual void use(Character* obj, Robot * robot) = 0;
    ItemType getType() const { return type;}
};

class MagicBook: public BaseItem{
public:
    MagicBook(): BaseItem(MAGIC_BOOK) {}
    virtual bool canUse(Character* obj, Robot * robot) override {
        if (obj->getEXP() <= 350){
            return true;
        }
        return false;
    }

    void use(Character* obj, Robot* robot) override {
        // Increase EXP by 25% (with a bonus)
        int expIncrease = obj->getEXP() * 0.25;
        obj->checkEXP(obj->getEXP() + expIncrease);
    }
};

class EnergyDrink : public BaseItem {
public:
    EnergyDrink() : BaseItem(ENERGY_DRINK) {}
    bool canUse(Character* obj, Robot* robot) override {
        // Check if character's HP is low (<= 100)
        if (obj->getHP() <= 100) {
            return true;
        }
        return false;
    }

    void use(Character* obj, Robot* robot) override {
        // Increase HP by 20% (with a bonus)
        int hpIncrease = obj->getHP() * 0.2;
        obj->checkHP(obj->getHP() + hpIncrease);
    }
};

class FirstAid : public BaseItem {
public:
    FirstAid() : BaseItem(FIRST_AID) {}
    bool canUse(Character* obj, Robot* robot) override {
        // Check if character's HP or EXP is low (<= 100 or <= 350)
        if (obj->getHP() <= 100 || obj->getEXP() <= 350) {
            return true;
        }
        return false;
    }

    void use(Character* obj, Robot* robot) override {
        // Increase HP by 50% (with a bonus)
        int hpIncrease = obj->getHP() * 0.5;
        obj->checkHP(obj->getHP() + hpIncrease);
    }
};

class ExcemptionCard : public BaseItem {
public:
    ExcemptionCard() : BaseItem(EXCEMPTION_CARD) {}
    bool canUse(Character* obj, Robot* robot) override {
        // Only Sherlock can use this item
        if (obj->getName() == "Sherlock" && obj->getHP() % 2 != 0) {
            return true;
        } else return false;
    }

    void use(Character* obj, Robot* robot) override {
        // Exempt Sherlock from HP and EXP loss when failing a challenge
        std::cout << "Sherlock sử dụng ExcemptionCard và được miễn trừ HP và EXP khi thất bại." << std::endl;
    }
};

class PassingCard : public BaseItem {
private:
    std::string challenge; // Challenge type (e.g., RobotS)
public:
    PassingCard(const std::string& challenge) : BaseItem(PASSING_CARD), challenge(challenge) {}

    bool canUse(Character* obj, Robot* robot) override {
        // Only Watson can use this item
        if (obj->getName() == "Watson" && obj->getHP() % 2 == 0) {
            return true;
        } else return false;
    }

    void use(Character* obj, Robot* robot) override {
    // Exempt Watson from the challenge of the corresponding robot type
        if (challenge == "all" || robot->getName() == challenge) {
            
        } else {
            // If the challenge type doesn't match, reduce Watson's EXP by 50
            obj->checkEXP(obj->getEXP() - 50);
        }
    }
};

class BaseBag {
protected:
    Node* head;
    int max_size;
    int size;
    Character* owner;
public:
    BaseBag(int max_size, Character* in_own) : head(nullptr), max_size(max_size), size(0), owner(in_own) {}
    virtual ~BaseBag() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->item;
            delete temp;
        }
    }

    Node* getNode() {
        return head;
    }
    virtual bool insert(BaseItem* item) {
        if (size >= max_size) {
            return false;
        }
        Node* new_node = new Node(item);
        new_node->next = head;
        head = new_node;
        size++;
        return true;
    }

    virtual BaseItem* get(ItemType itemType = MAGIC_BOOK) {
        if (!head) {
            return nullptr;
        }

        Node* prev = nullptr;
        Node* current = head;

        while (current) {
            if (current->item->getType() == itemType) {
                if (prev) {
                    prev->next = current->next;
                    } else {
                    head = current->next;
                }
                size--;
                BaseItem* item = current->item;
                delete current;
                return item;
            }
            prev = current;
            current = current->next;
        }

        return nullptr;
    }

    virtual std::string str() const {
        std::ostringstream oss;
        oss << "Bag[count=" << size << ";";
        Node* current = head;
        while (current) {
            switch (current->item->getType()) {
                case MAGIC_BOOK: oss << "MagicBook"; break;
                case ENERGY_DRINK: oss << "EnergyDrink"; break;
                case FIRST_AID: oss << "FirstAid"; break;
                case EXCEMPTION_CARD: oss << "ExcemptionCard"; break;
                case PASSING_CARD: oss << "PassingCard"; break;
            }
            if (current->next) {
                oss << ",";
            }
            current = current->next;
        }
        oss << "]";
        return oss.str();
    }
    bool transfer_items(BaseBag& other, ItemType item_type) {
        bool transferred = false;
        while (true) {
            BaseItem* item = get(item_type);
            if (item != nullptr) {
                other.insert(item);
                transferred = true;
            } else {
                break;
            }
        }
        return transferred;
    }
};

class Node {
public:
    BaseItem* item;
    Node* next;

    Node(BaseItem* item) : item(item), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    int max_size;
    int size;

    LinkedList(int max_size) : head(nullptr), max_size(max_size), size(0) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->item;
            delete temp;
        }
    }

    bool insert(BaseItem* item) {
        if (size >= max_size) {
            return false;
        }
        Node* new_node = new Node(item);
        new_node->next = head;
        head = new_node;
        size++;
        return true;
    }
    BaseItem* get(ItemType itemType) {
        if (!head) {
            return nullptr;
        }

        Node* prev = nullptr;
        Node* current = head;

        while (current) {
            if (current->item->getType() == itemType) {
                if (prev) {
                    prev->next = current->next;
                    current->next = head;
                    head = current;
                }
                head = head->next;
                size--;
                BaseItem* item = current->item;
                delete current;
                return item;
            }
            prev = current;
            current = current->next;
        }

        return nullptr;
    }
    bool transfer_items(LinkedList& other, ItemType item_type) {
        bool transferred = false;
        while (true) {
            BaseItem* item = get(item_type);
            if (item != nullptr) {
                other.insert(item);
                transferred = true;
            } else {
                break;
            }
        }
        return transferred;
    }
    std::string str() const {
        std::ostringstream oss;
        oss << "Bag[count=" << size << ";";
        Node* current = head;
        while (current) {
            switch (current->item->getType()) {
                case MAGIC_BOOK: oss << "MagicBook"; break;
                case ENERGY_DRINK: oss << "EnergyDrink"; break;
                case FIRST_AID: oss << "FirstAid"; break;
                case EXCEMPTION_CARD: oss << "ExcemptionCard"; break;
                case PASSING_CARD: oss << "PassingCard"; break;
            }
            if (current->next) {
                oss << ",";
            }
            current = current->next;
        }
        oss << "]";
        return oss.str();
    }
};

class SherlockBag : public BaseBag {
public:
    SherlockBag(Sherlock* sherlock) : BaseBag(13, sherlock) {}
};

class WatsonBag : public BaseBag {
public:
    WatsonBag(Watson* watson) : BaseBag(15, watson) {}
};
/*
class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    Map * map;
    ArrayMovingObject * arr_mv_objs;

public:
    void handleInteraction(MovingObject* obj) {
        if (obj->getName() == "Sherlock") {
            handleSherlockInteraction(sherlock);
        } else if (obj->getName() == "Watson") {
            handleWatsonInteraction(watson);
        }
    }

    void handleSherlockInteraction(Sherlock* sherlock, RobotS* robotS, RobotW* robotW, RobotSW* robotSW, RobotC* robotC) {
        // ... handle interaction with RobotS ...
        if (sherlock->getCurrentPosition() == robotS->getPosition()) {
            if (sherlock->getEXP() > 400) {            
                sherlock->bag->insert(robotS->getItem());
            } else {
                sherlock->checkEXP(sherlock->getEXP() - 0.1*sherlock->getEXP());
            }
            return;
        }

        // ... handle interaction with RobotW ...
        if (sherlock->getCurrentPosition() == robotW->getPosition()) {
            sherlock->bag->insert(robotW->getItem());
            return;
        }

        // ... handle interaction with RobotSW ...
        if (sherlock->getCurrentPosition() == robotSW->getPosition()) {
            if (sherlock->getEXP() > 300 && sherlock->getHP() > 335) {
                sherlock->bag->insert(robotSW->getItem());
            } else {
                sherlock->checkHP(sherlock->getHP() - 0.1*sherlock->getHP());
                sherlock->checkEXP(sherlock->getEXP() - 0.15*sherlock->getEXP());
            }
            return;
        }

        // ... handle interaction with RobotC ...
        if (sherlock->getCurrentPosition() == robotC->getPosition()) {
            if (sherlock->getEXP() > 500) {
            } else {
                sherlock->bag->insert(robotC->getItem());
            }
            return;
        }

        // ... handle interaction with FakeWall ...
        for (int i = 0; i < config->getNumFakeWalls(); ++i) {
            if (sherlock->getPosition() == config->getFakeWallPos(i)) {
                config->destroyFakeWall(i);
                break;
            }
        } 

        // ... check and use items ...
    }

    void handleWatsonInteraction(Watson* watson, RobotS* robotS, RobotW* robotW, RobotSW* robotSW, RobotC* robotC) {
        Position watsonPosition = watson->getCurrentPosition();
        
        // Handle interaction with RobotS
        if (watsonPosition == robotS->getPosition()) {
            // Watson doesn't do anything with RobotS
            return;
        }
        
        // Handle interaction with RobotW
        if (watsonPosition == robotW->getPosition()) {
            if (watson->getHP() > 350) {
                watson->bag->insert(robotW->getItem());
            } else {
                watson->bag->checkHP(watson->getHP() - 0.05 * watson->getHP());
            }
            return;
        }
    
    // Handle interaction with RobotSW
        if (watsonPosition == robotSW->getPosition()) {
            if (watson->getEXP() > 600 && watson->getHP() > 165) {
                watson->bag->insert(robotSW->getItem());
            } else {
                watson->checkHP(watson->getHP() - 0.15 * watson->getHP());
                watson->checkEXP(watson->getEXP() - 0.15 * watson->getEXP());
            }
            return;
        }
        
        // Handle interaction with RobotC
        if (watsonPosition == robotC->getPosition()) {
            // Watson can't catch the criminal yet
            return;
        }
    
        // Handle interaction with FakeWall
         for (int i = 0; i < config->getNumFakeWalls(); ++i) {
            if (watsonPosition == config->getFakeWallPos(i)) {
                config->destroyFakeWall(i);
                break;
            }
        } 
    }

    StudyPinkProgram(const string & config_file_path) {
        this->config = new Configuration(config_file_path);
        this->sherlock = new Sherlock(map, config->get_s_init_pos, config->get_s_init_hp(), config->get_s_init_exp(), config->get_s_moving_rule());
        this->watson = new Watson(map, config->get_w_init_pos, config->get_w_init_hp(), config->get_w_init_exp(), config->get_w_moving_rule());
        this->criminal = new Criminal(map, config->get_c_init_pos(), arr_mv_objs, sherlock, watson);
        this->arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
        this->arr_mv_objs->add(criminal);
        this->arr_mv_objs->add(sherlock);
        this->arr_mv_objs->add(watson);
    };

    ~StudyPinkProgram() {
        delete config;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete arr_mv_objs;
    }

    bool isStop() const {
        return sherlock->getHP() == 1 || watson->getHP() == 1 || 
        (sherlock->getCurrentPosition() == this->criminal->getCurrentPosition()) || 
        (watson->getCurrentPosition() == this->criminal->getCurrentPosition());
    };

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--" 
            << this->sherlock->str() << "--|--" << this->watson->str() << "--|--" << this->criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();

                if (isStop()) {
                    printStep(istep);
                    break;
                }

                handleInteraction(arr_mv_objs->get(i));

                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

};
*/
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
