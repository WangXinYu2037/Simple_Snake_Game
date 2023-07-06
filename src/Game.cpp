//
// Created by 王新宇 on 2023/7/4.
//
#include "Game.h"
#include<iostream>

using namespace std;
int CreateWorld(){
    int i, j;
    for(i = 0; i < 15; i ++){
        if(i == 0 or i == 14) {
            for (j = 0; j < 15; j++) {
                cout << "#";
            }
        }
        else if(i == 1 or i == 13){
            cout << "#$";
            for(j = 0; j < 11; j ++){
                cout << " ";
            }
            cout << "$#";
        }
        else if(i == 7){
            cout << "#";
            for(j = 0; j < 6; j++) cout << " ";
            cout << "*";
            for(j = 0; j < 6; j++) cout << " ";
            cout << "#";
        }
        else if (i == 4 or i == 10){
            cout << "#   #  $  #   #";
        }
        else{
            cout << "#   #     #   #";
        }
        cout << "\n";
    }
    return 0;
}

void OpenUserFile(ifstream& input){
    while(true){
        cout << "Please enter the file name of World." << endl;
        cout << "the level.txt is an example" << endl;
        string filename = "level.txt";
//        getline(cin, filename);
        input.open(filename);
        if(input.is_open()) {
//            string tmp;
//            while(getline(input, tmp)){
//                cout << tmp << endl;
//            }
            break;
        }
        else{
            cout << "Sorry, can't find the file";
            input.close();
            input.clear();
        }
    }
}


void InitializeGame(gameT& game){
    ifstream input;
    /* 打开指定文件，绑定输入流 */
    OpenUserFile(input);
    /* 根据流input的内容，加载游戏参数到game */
    LoadWorld(game, input);
}

void LoadWorld(gameT& game, ifstream& input){
    input >> game.numRows >> game.numCols;
    game.world.resize(game.numRows);
    input >> game.velocity.row >> game.velocity.col;
    /* 流提取符 >> 读完数字后，会留下该行的\n，意味指针还是在该行，需要下面一步过渡*/
    string empty_line;
    getline(input, empty_line);
    for(int i = 0; i < game.numRows; i++){
        getline(input, game.world[i]);
        /* 读入的同时顺便寻找头部位置 */
        int col = int(game.world[i].find(SnakeHead));
        if(col != string::npos){
            point head = MakePoint(i, col);
            game.snake.push_back(head);
        }
    }
    /* 设置初始值 */
    game.numEaten = 0;
}

point MakePoint(int row, int col){
    point result{};
    result.row = row;
    result.col = col;
    return result;
}

void RunSimulation(gameT& game){
    /* 在没吃够前一直循环 */

    while(game.numEaten < MaxFood){
        /* 打印game中的世界内容，并显示已吃掉的food数量 */
        PrintWorld(game);
        Pause(1);
        cout << "-----------------------------" << endl;
        cout << endl;
        /* AI来操控snake的轨迹，设置snake的方向 */
        //PerformAI(game);
        /* 人来操控snake的轨迹 */
        PerformPlayer(game);

        cout << game.velocity.row << ", " << game.velocity.col << endl;
        /* 根据AI的选择的方向，移动snake并判断撞墙，吃food，生长*/
        if(!MoveSnake(game))
            break;

        system("cls");


    }
    PrintWorld(game);
    DisplayResult(game);
    Pause(10);

}

void DisplayResult(gameT& game){
    if(game.numEaten >= MaxFood){
        cout << "You Win!! The Snake have eaten enough food" << endl;
    }
    else{
        cout << "The snake crashed" << endl;
    }
}
void Pause(double time){
    /* 暂停time s */
    clock_t startTime = clock();
    while(static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC < time);
}
void PrintWorld(gameT& game){
    for(int i = 0; i < game.numRows; i++){
        cout << game.world[i] << endl;
    }
    cout << "Food Eaten: " << game.numEaten << endl;
}

void PerformAI(gameT& game){
    /* 获得snake head的下一个位置 */
    point nextHead = GetNextPosition(game, game.velocity.row, game.velocity.col);

    /* 如果下一个位置要撞墙就转向,或者就随机地决定转向 */
    if(Crashed(nextHead, game) || RandomChance(0.2)){

        /* 向左转 */
        int dxLeft = -game.velocity.col;
        int dyLeft = game.velocity.row;

        /* 向右转 */
        int dxRight = game.velocity.col;
        int dyRight = -game.velocity.row;

        bool canLeft = !Crashed(GetNextPosition(game, dxLeft, dyLeft), game);
        bool canRight = !Crashed(GetNextPosition(game, dxRight, dyRight), game);

        /* 是否可以左转 */
        bool turnLeft = false;
        if(!canLeft && !canRight)
            return; // 直接退出
        else if(!canLeft && canRight)
            turnLeft = false;
        else if(canLeft && ! canRight)
            turnLeft = true;
        else
            turnLeft = RandomChance(0.5);

        game.velocity.row = turnLeft ? dxLeft : dxRight;
        game.velocity.col = turnLeft ? dyLeft : dyRight;
    }

}

/* 判断是否移动了，如果能移动则返回true，不能移动则返回false */
/* 吃够了也视为不能移动 */
bool MoveSnake(gameT& game){
    point nextHead = GetNextPosition(game, game.velocity.row, game.velocity.col);\
    /* 是否crash */
    if(!Crashed(nextHead, game)){
        /* 将该点加入到snake中 */
        game.snake.push_front(nextHead);
        /* 有没有吃到food，没吃到则要丢掉尾部 */
        /* 此处的bug，要先判断是否是food，再更新world的内容 */
        bool isFood = (game.world[nextHead.row][nextHead.col] == FoodTile);

        if(isFood){
            /* 将原来的头部变成身体 */
            auto head2 = game.snake.begin() + 1;
            game.world[head2->row][head2->col] = SnakeTile;
            /* 判断吃够没有，够了就不移动 */
            game.numEaten += 1;
            if(game.numEaten >= MaxFood)
                return false;
            /* 产生一个新food */
            PlaceFood(game);
        }
        else{
            point tail = game.snake.back();
            game.snake.pop_back();
            game.world[tail.row][tail.col] = EmptyTile;
            /* 将原来的头部变成身体 */
            auto head2 = game.snake.begin() + 1;
            if(head2 != game.snake.end())
                game.world[head2->row][head2->col] = SnakeTile;
        }
        /* 要最后再更新world中的内容 */

        game.world[nextHead.row][nextHead.col] = SnakeHead;
        return true;
    }
    return false;
}

void PlaceFood(gameT& game){
    while(true){
        int row = rand() % game.numRows;
        int col = rand() % game.numCols;
        if(game.world[row][col] == EmptyTile){
            game.world[row][col] = FoodTile;
            break;
        }
    }
}
point GetNextPosition(gameT& game, int dx, int dy){
    point head =game.snake.front();
    head.row += dx;
    head.col += dy;
    return head;
}

bool Crashed(point nextHead, gameT& game){
    int row = nextHead.row;
    int col = nextHead.col;
    if(game.world[row][col] == WallTile or game.world[row][col] == SnakeTile){
        return true;
    }
    return false;
}

bool RandomChance(double turnRate){
//    cout << rand() << " " << RAND_MAX << " " << endl;
//    cout << (double)(rand() / (RAND_MAX + 1)) << endl;
    return ((double)rand() / (RAND_MAX + 1)) < turnRate;
}