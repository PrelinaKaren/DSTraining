//main.cpp
#include <stdio.h>
#include "maze.h"

/*Prelina:测试的时候发现在Windows CMD下运行会乱码，
 *所以加了这个部分，如果监测到运行环境是Windows，则配置Windows控制台为UTF-8编码*/
#ifdef _WIN32
#include <windows.h>
void ConfigureConsoleForUTF8() {
    UINT currentCP = GetConsoleOutputCP();
    if (currentCP != 65001) {
        SetConsoleOutputCP(65001);
    }
}
#endif

// 全局变量
int maze[MAX_SIZE][MAX_SIZE];
int mark[MAX_SIZE][MAX_SIZE];
Element stack[MAX_STACK];
int top = -1;
int rows, cols;

// 显示菜单
void Menu() {
    int choice;
    char display_attempts;

    do {
        printf("\n菜单：\n");
        printf("1. 显示迷宫\n");
        printf("2. 寻找迷宫路径\n");
        printf("3. 重新生成迷宫\n");
        printf("4. 生成直到找到通路\n");
        printf("5. 退出程序\n");
        printf("请输入您的选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                DisplayMaze(rows, cols);
                break;
            case 2:
                FindPath(rows, cols);
                DisplayPath(rows, cols);
                break;
            case 3:
                GenerateMaze(rows, cols);
                printf("迷宫已重新生成！\n");
                DisplayMaze(rows, cols); // 重新生成后显示新迷宫
                break;
            case 4:
                printf("是否显示每次尝试生成的迷宫？(y/n): ");
                scanf(" %c", &display_attempts);
                GenerateUntilPathFound(rows, cols, display_attempts == 'y' || display_attempts == 'Y');
                break;
            case 5:
                printf("程序退出，感谢使用！\n");
                break;
            default:
                printf("无效选择，请重新输入！\n");
        }
    } while (choice != 5);
}

int main() {
#ifdef _WIN32
    ConfigureConsoleForUTF8(); // 配置 Windows 控制台为 UTF-8 编码
#endif

    printf("请输入迷宫的行和列数：");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 || rows > MAX_SIZE || cols > MAX_SIZE) {
        printf("行列大小无效，请确保 1 <= 行列 <= %d。\n", MAX_SIZE);
        return 1;
    }

    char choice;
    printf("您想手动输入迷宫还是自动生成迷宫？(m: 手动输入, a: 自动生成): ");
    scanf(" %c", &choice);

    if (choice == 'm' || choice == 'M') {
        printf("请按行输入迷宫，每行输入 %d 个数字（0 表示无障碍，1 表示障碍）：\n", cols);

        int valid_input = 1; // 标记输入是否有效
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (scanf("%d", &maze[i][j]) != 1 || (maze[i][j] != 0 && maze[i][j] != 1)) {
                    valid_input = 0; // 如果输入无效则标记
                }
            }
        }

        // 检查迷宫入口和出口是否合法
        if (maze[0][0] != 0 || maze[rows - 1][cols - 1] != 0) {
            printf("迷宫的入口 (0,0) 和出口 (%d,%d) 必须为 0（无障碍）！\n", rows - 1, cols - 1);
            return 1;
        }

        if (!valid_input) {
            printf("无效的迷宫输入！请确保输入的仅为 0 和 1。\n");
            return 1;
        }

        // 显示用户输入的迷宫供检查
        printf("您输入的迷宫为：\n");
        DisplayMaze(rows, cols);

    } else if (choice == 'a' || choice == 'A') {
        GenerateMaze(rows, cols);
        printf("自动生成的迷宫为：\n");
        DisplayMaze(rows, cols); // 显示自动生成的迷宫
    } else {
        printf("无效选择，请重新运行程序。\n");
        return 1;
    }

    InitializeStack();
    Menu();

    return 0;
}
