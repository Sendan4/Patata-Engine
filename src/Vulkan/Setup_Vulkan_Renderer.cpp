#include <vector>
#include <tuple>

#include <SDL_vulkan.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "PatataEngine/TerminalColors.hpp"
#include "PatataEngine/Log.hpp"

Patata::Graphics::VulkanRenderer::VulkanRenderer(SDL_Window * WINDOW, YAML::Node CONFIG) {
	if (!CreateInstance(WINDOW, CONFIG)) return;

	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	uint32_t GraphicsQueueFamilyIndex = CreateLogicalDeviceAndCreateQueue();
	
	Patata::Log::CheckSurface(SDL_Vulkan_CreateSurface(WINDOW, VulkanInstance, reinterpret_cast<VkSurfaceKHR *>(&Surface)));

	std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> swapchaininfo = CreateSwapChain(GraphicsQueueFamilyIndex, CONFIG);
	CreateImageView(GraphicsQueueFamilyIndex);
	CreateCommandBuffer(GraphicsQueueFamilyIndex);
	CreateRenderPass();

	Semaphore = Device.createSemaphore(vk::SemaphoreCreateInfo());

	VulkanInfo(CONFIG, swapchaininfo);
}

Patata::Graphics::VulkanRenderer::~VulkanRenderer(void) {
	Device.destroySemaphore(Semaphore);
	Device.destroyRenderPass(RenderPass);
	Device.freeCommandBuffers(CommandPool, CommandBuffers);
	Device.destroyCommandPool(CommandPool);
	Device.freeMemory(ImageMemory);
	Device.destroyImage(DepthImage);
//	Device.destroyImageView(ImageView);
	Device.destroySwapchainKHR(SwapChain);
	VulkanInstance.destroySurfaceKHR(Surface);
	Device.destroy();
	VulkanInstance.destroy();
}
