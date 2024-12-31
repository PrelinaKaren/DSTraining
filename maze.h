//maze.h
// Created by Prelina  on 24-12-30.
//
#ifndef MAZE_H
#define MAZE_H

#define MAX_STACK 100  // 栈的最大容量
#define MAX_SIZE 20    // 迷宫的最大尺寸

typedef struct {
    int row;  // 当前行
    int col;  // 当前列
    int dir;  // 当前方向
} Element;

// 全局变量
extern int maze[MAX_SIZE][MAX_SIZE];  // 迷宫矩阵
extern int mark[MAX_SIZE][MAX_SIZE];  // 标记矩阵
extern Element stack[MAX_STACK];      // 栈
extern int top;                       // 栈顶指针
extern int rows, cols;                // 迷宫的行数和列数

// 栈操作函数
void InitializeStack();
void Push(Element item);
Element Pop();

// 迷宫操作函数
void GenerateMaze(int m, int n);    //生成迷宫
void DisplayMaze(int m, int n);     //显示迷宫
void GenerateUntilPathFound(int m, int n, int display_attempts);
void ClearScreen();                 //清除屏幕
void ShowLoading(int attempt_count);//给GenerateUntilPathFound函数使用

// 路径操作函数
void FindPath(int m, int n);
void DisplayPath(int m, int n);

#endif
