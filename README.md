# C++五子棋项目
## 简介
## 编译
### Release版本
```bash
g++ -std=c++17 -O2 -DNDEBUG -Iinclude src/core/*.cpp src/ai/*.cpp src/input/*.cpp src/player/*.cpp src/ui/*.cpp src/ui/backend/*.cpp src/utils/*.cpp src/app/*.cpp src/command/*.cpp src/task/*.cpp src/menu/*.cpp  -o GobangCpp.exe
```