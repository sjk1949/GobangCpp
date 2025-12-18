#pragma once
/**
 * @brief 这段代码来自deepseek关于非阻塞式跨平台输入读取的生成代码
 * @author DeepSeek
 * @todo 目前这段代码还不能实现Linux转义序列的读取操作
 */
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/select.h>
#endif

class NonBlockingInput
{
public:
    NonBlockingInput() {
#ifdef _WIN32
        // Windows不需要特殊初始化
#else
        // Linux/Unix: 保存原始设置
        tcgetattr(STDIN_FILENO, &original_tty);
        struct termios new_tty = original_tty;
        new_tty.c_lflag &= ~(ICANON | ECHO);
        new_tty.c_cc[VMIN] = 1;
        new_tty.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tty);
#endif
    }
    
    ~NonBlockingInput() {
#ifndef _WIN32
        // 恢复终端设置
        tcsetattr(STDIN_FILENO, TCSANOW, &original_tty);
#endif
    }
    
    bool kbhit() {
#ifdef _WIN32
        return _kbhit() != 0;
#else
        struct timeval tv = {0L, 0L};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
#endif
    }
    
    char getch() {
#ifdef _WIN32
        return _getch();
#else
        char ch = 0;
        read(STDIN_FILENO, &ch, 1);
        return ch;
#endif
    }

private:
#ifndef _WIN32
    struct termios original_tty;
#endif
};