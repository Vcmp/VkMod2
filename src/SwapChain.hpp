

#include "Vks.tpp"


#include <array>

#include <vector>


#pragma once

struct SwapChain
{
    VkPhysicalDevice physdevice;
    VkSurfaceKHR surface;
    VkExtent2D swapChainExtent=getCurrentSwapChainSurfaceCapabilities();
    VkRenderPass renderpass=createRenderPass(VK_IMAGE_LAYOUT_UNDEFINED, false);
    VkSurfaceFormatKHR         swapChainImageFormat=setupImageFormats();
    VkPresentModeKHR presentMode;
    // VkExtent2D swapChainExtent=capabilities.currentExtent;
    VkFramebuffer frameBuffer=createFramebuffers(renderpass);
    VkSwapchainKHR swapChain=createSwapChain(swapChainImageFormat);;
    //std::array<VkImage, Frames> image = getSwapChainImages(Frames);
     std::array<VkImageView, Frames> imageViews = createImageViews(getSwapChainImages(Frames));
    SwapChain(VkPhysicalDevice physdevice, VkSurfaceKHR surface):physdevice(physdevice), surface(surface){};
    auto setupImageFormats() -> VkSurfaceFormatKHR;
    [[nodiscard]] auto getSwapChainImages(uint32_t) -> std::array<VkImage, Frames>;
    [[nodiscard]] auto createSwapChain(VkSurfaceFormatKHR) -> VkSwapchainKHR;
    [[nodiscard]] auto createImageViews(std::array<VkImage, Frames> image) -> std::array<VkImageView, Frames>;
    auto createFramebuffers(VkRenderPass) -> VkFramebuffer;
    [[nodiscard]] auto createRenderPass(VkImageLayout, bool) -> VkRenderPass;
    [[nodiscard]] auto getCurrentSwapChainSurfaceCapabilities() const -> VkExtent2D;

} __attribute__((aligned(128)));
