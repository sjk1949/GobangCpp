#include "input/NonBlockingInput.hpp"

 namespace Test {
    class InputTest
    {
    public:
        static int testNonBlockingInput() {
            NonBlockingInput nbi;
            
            std::cout << "非阻塞输入示例" << std::endl;
            std::cout << "按任意键查看ASCII码，按ESC退出" << std::endl;
            
            int counter = 0;
            while (true) {
                if (nbi.kbhit()) {
                    char ch = nbi.getch();
                    
                    // 特殊键处理（Windows下箭头等扩展键）
                    if (ch == 0 || ch == -32) {
        #ifdef _WIN32
                        ch = _getch();  // 获取扩展键码
                        std::cout << "特殊键: " << (int)ch << std::endl;
        #endif
                    } else {
                        std::cout << "字符: " << ch 
                                << " ASCII: " << (int)ch 
                                << std::endl;
                        
                        if (ch == 27) {  // ESC键
                            std::cout << "退出程序" << std::endl;
                            break;
                        }
                    }
                }
                
                // 主循环可以同时做其他工作
                if (counter++ % 100 == 0) {
                    std::cout << "." << std::flush;
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            
            return 0;
        }
    };
};