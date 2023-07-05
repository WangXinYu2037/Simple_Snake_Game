//
// Created by 王新宇 on 2023/7/4.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <fstream>
using namespace std;

const int MaxFood = 5;
const char EmptyTile = ' ';
const char WallTile = '#';
const char FoodTile = '$';
const char SnakeTile = '*';
const char SnakeHead = '+';

struct point{
    int row, col;
};

struct gameT{
    vector<string> world;
    int numRows, numCols;
    deque<point> snake;
    point velocity;
    int numEaten;
};
int CreateWorld();

void InitializeGame(gameT& game);

void OpenUserFile(ifstream& input);

void LoadWorld(gameT& game, ifstream& input);

point MakePoint(int row, int col);

void RunSimulation(gameT& game);

void PrintWorld(gameT& game);

void PerformAI(gameT& game);

void Pause(double time);

bool MoveSnake(gameT& game);

void PlaceFood(gameT& game);

point GetNextPosition(gameT& game, int dx, int dy);

bool Crashed(point nextHead, gameT& game);

void DisplayResult(gameT& game);

bool RandomChance(double turnRate);
#endif //SNAKE_GAME_H
