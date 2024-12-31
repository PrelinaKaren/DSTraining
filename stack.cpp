//stack.cpp
// Created by Prelina  on 24-12-30.
//
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

// 初始化栈
void InitializeStack() {
    top = -1;
}

// 将元素压入栈
void Push(Element item) {
    if (top < MAX_STACK - 1) {
        stack[++top] = item;
    } else {
        printf("栈溢出！\n");
        exit(1);
    }
}

// 从栈中弹出元素
Element Pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("栈为空！\n");
        exit(1);
    }
}
