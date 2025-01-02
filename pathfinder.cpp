//pathfinder.cpp
// Created by Prelina  on 24-12-30.
//
#include <stdio.h>
#include "maze.h"

// 四个移动方向：右、下、左、上
int move[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

// 寻找迷宫路径
void FindPath(int m, int n) {
    int row = 0, col = 0, dir, found = 0;
    int next_row, next_col;
    Element position;

    // 初始化标记矩阵
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mark[i][j] = 0;
        }
    }

    mark[0][0] = 1; // 标记入口
    position.row = 0;
    position.col = 0;
    position.dir = 0;
    Push(position);

    while (top > -1 && !found) {
        position = Pop();
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 4 && !found) {
            next_row = row + move[dir][0];
            next_col = col + move[dir][1];

            // 检查是否到达出口
            if (next_row == m - 1 && next_col == n - 1 && maze[next_row][next_col] == 0) {
                found = 1;

                // 将当前点和出口点压入栈
                Element final_position = {row, col, dir};
                Push(final_position);
                Element exit_position = {next_row, next_col, 0};
                Push(exit_position);

                break;
            }
            // 检查是否为可通行点
            else if (next_row >= 0 && next_row < m && next_col >= 0 && next_col < n &&
                     maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0) {
                mark[next_row][next_col] = 1; // 标记走过的点

                // 将当前点压入栈并移动到下一点
                position.row = row;
                position.col = col;
                position.dir = dir + 1;
                Push(position);

                row = next_row;
                col = next_col;
                dir = 0; // 重置方向
                     } else {
                         dir++; // 尝试下一个方向
                     }
        }
    }

    if (found) {
        printf("找到一条路径：\n");

        // 输出路径
        for (int i = 0; i <= top; i++) {
            printf("(%d, %d) -> ", stack[i].row, stack[i].col);
        }
        printf("结束\n");
    } else {
        printf("迷宫没有出路！\n");
    }
}
