
#include "Vks.tpp"

#pragma once
static struct SwapChain
{
    VkSurfaceCapabilitiesKHR capabilities{};
    uint32_t       imageCount;
    VkSwapchainKHR swapChain;
    VkImage image[3];
    VkImageView imageViews[3];
    VkRenderPass renderpass;
    VkSurfaceFormatKHR         swapChainImageFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D swapChainExtent{854, 480};
    const VkFramebuffer frameBuffer;
    SwapChain(/* VkPhysicalDevice physdevice, VkSurfaceKHR surface */) : frameBuffer(createFramebuffers())
    {
        setupImageFormats();
        createSwapChain();
        createImageViews();
        // createFramebuffers();
        createRenderPass();
      
    };
    void setupImageFormats();
    void createSwapChain();
    void createImageViews();
    VkFramebuffer createFramebuffers();
    void createRenderPass();

} SW;