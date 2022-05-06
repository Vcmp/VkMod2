
#include "GLFW/glfw3.h"
#include "VkInit.hpp"
#include "SwapChain.hpp"
#include <cstdio>

int main()
{
    printf("-->");
    std::cout <<(VKI.device)<< "\n";
    // std::cout <<(SW.imageCount)<< "\n";
    int aa = 0;

    
    while(!glfwWindowShouldClose(VKI.window))
    {
        // printf("%i \n", aa++);
    }
 

}