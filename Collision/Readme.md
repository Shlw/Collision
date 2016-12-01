# Collision 大作业

## 简要介绍

这是 2016 年计算概论 (实验班) 的三维建模 + 碰撞的大作业 Collision.

## 版本更改

1. lzh @ 2016.12.01.00.46
  1.1 建立了大体的框架, 分为 display, draw, update, game 四个部分, 分别对应渲染, 建模, 碰撞测试与界面逻辑.  
  1.2 使用 Cmake 来达到跨平台编译的效果.

## 目标与注释

1. lzh @ 2016.12.01.00.46
  1.1 CMakelists 中 Unix 系统的编译命令需要更新, 现在在 Unix 下编译会出错, 待更新, 目前可以使用命令行编译, 编译的文件应为 main.cpp display.cpp draw.cpp update.cpp game.cpp, 需要使用 glut 或 freeglut 库与 glm 库.  
  1.2 global.hpp 中声明的 Object 类与 Model 类的写法很愚蠢, 待建模的同学重写.  
  1.3 display.cpp 里面做了一个简单的demo, 可以将里面的东西删掉.
