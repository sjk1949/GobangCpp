# C++五子棋项目
## 简介
这是C++程序设计课程的大作业，制作人为Sjk1949，内容是一个可以用终端显示的五子棋程序，支持人人对战，人机对战，机机对战模式，并实现了非阻塞式刷新以及恒定帧率运行，内置菜单，计时器等必备组件，并支持悔棋功能。
## 编译
### Release版本
```bash
g++ -std=c++17 -O2 -DNDEBUG -Iinclude src/core/*.cpp src/ai/*.cpp src/input/*.cpp src/player/*.cpp src/ui/*.cpp src/ui/backend/*.cpp src/utils/*.cpp src/app/*.cpp src/command/*.cpp src/task/*.cpp src/menu/*.cpp -o GobangCpp.exe
```
## License

This project is licensed under the MIT License.
See the LICENSE file for details.

Copyright (c) 2026 Sjk1949.
