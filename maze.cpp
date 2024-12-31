#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include "maze.h"

// 随机生成迷宫
void GenerateMaze(int m, int n) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == 0 && j == 0) || (i == m - 1 && j == n - 1)) {
                maze[i][j] = 0; // 确保入口和出口没有障碍
            } else {
                maze[i][j] = rand() % 2; // 随机生成0或1
            }
        }
    }
}

// 显示迷宫
void DisplayMaze(int m, int n) {
    printf("迷宫如下：\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

// 显示路径标记后的迷宫
void DisplayPath(int m, int n) {
    printf("路径标记后的迷宫如下：\n");
    int maze_with_path[MAX_SIZE][MAX_SIZE]; // 创建一个副本数组
    memcpy(maze_with_path, maze, sizeof(maze)); // 复制迷宫内容到副本数组

    // 标记路径
    for (int i = 0; i <= top; i++) {
        maze_with_path[stack[i].row][stack[i].col] = 8; // 标记路径为 8
    }

    // 打印标记后的迷宫
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", maze_with_path[i][j]);
        }
        printf("\n");
    }
}

// 生成迷宫直到找到通路
void GenerateUntilPathFound(int m, int n, int display_attempts) {
    int path_found = 0; // 标记是否找到通路
    int attempt_count = 0;

    char path_trace[1024] = ""; // 用于存储路径信息
    size_t path_trace_len = 0; // 当前路径信息已经使用的字符长度

    while (!path_found) {
        // 每次生成一个新迷宫
        GenerateMaze(m, n);
        attempt_count++;

        if (display_attempts) {
            // 用户选择显示迷宫时，显示当前生成的迷宫
            ClearScreen();
            printf("正在尝试生成通路的迷宫...\n");
            printf("尝试次数：%d\n", attempt_count);
            printf("\n当前生成的迷宫：\n");
            DisplayMaze(m, n);

            printf("\n检查当前迷宫是否有通路...\n");
        } else {
            // 用户选择隐藏迷宫时，仅显示动态加载状态
            ShowLoading(attempt_count);
        }

        // 检查当前迷宫是否有通路
        InitializeStack(); // 重新初始化栈
        FindPath(m, n);

        // 如果找到路径，退出循环
        if (top >= 0) { // 栈非空表示找到路径
            path_found = 1;

            // 保存路径信息
            snprintf(path_trace, sizeof(path_trace), "找到一条路径：\n");
            path_trace_len = strlen(path_trace); // 更新路径长度

            for (int i = 0; i <= top; i++) {
                // 追加路径步骤到路径信息中
                char step[32];
                snprintf(step, sizeof(step), "(%d, %d) -> ", stack[i].row, stack[i].col);

                // 确保不会超出 path_trace 的大小
                if (path_trace_len + strlen(step) < sizeof(path_trace)) {
                    strcat(path_trace, step);
                    path_trace_len += strlen(step);
                } else {
                    printf("路径信息超出内存限制，无法完整记录路径！\n");
                    break;
                }
            }

            // 追加结束标记
            if (path_trace_len + strlen("结束\n") < sizeof(path_trace)) {
                strcat(path_trace, "结束\n");
            }

            if (display_attempts) {
                printf("%s", path_trace); // 显示路径信息
            }
        }
    }

    // 显示最终的结果
    ClearScreen();
    printf("最终成功生成了一个有通路的迷宫！\n");
    printf("尝试次数：%d\n", attempt_count);
    printf("\n路径信息：\n%s", path_trace); // 在尝试次数后显示路径
    printf("\n最终生成的迷宫如下：\n");
    DisplayMaze(m, n); // 打印原始迷宫
    printf("\n路径标记后的迷宫：\n");
    DisplayPath(m, n); // 打印标记后的迷宫
}

// 显示旋转横杠的函数
void ShowLoading(int attempt_count) {
    static const char spinner[] = "|/-\\"; // 旋转横杠字符序列
    static int spinner_index = 0;         // 当前旋转字符索引

    // 清屏并显示尝试状态
    ClearScreen();
    printf("程序正在尝试，目前已尝试迷宫数：%d %c\n", attempt_count, spinner[spinner_index]);

    // 更新旋转字符索引
    spinner_index = (spinner_index + 1) % 4;
}

// 清空屏幕并将光标移至左上角
void ClearScreen() {
    printf("\033[H\033[J"); // ANSI 转义序列，作用是清空屏幕并将光标移至左上角
}
