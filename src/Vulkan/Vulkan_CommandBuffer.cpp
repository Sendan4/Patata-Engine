#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "Log.hpp"

void Patata::Graphics::VulkanRenderer::CreateCommandBuffer(uint32_t &GraphicsQueueFamilyIndex) {
	vk::CommandPoolCreateInfo CreateCommandPoolInfo {};
	CreateCommandPoolInfo.flags = vk::CommandPoolCreateFlagBits::eTransient;
	CreateCommandPoolInfo.queueFamilyIndex = GraphicsQueueFamilyIndex;

	vk::Result Result = Device.createCommandPool(&CreateCommandPoolInfo, nullptr, &CommandPool);
	Patata::Log::VulkanCheck("CommandPool", Result);

	std::vector <vk::Image> SwapChainImages = Device.getSwapchainImagesKHR(SwapChain);

	vk::CommandBufferAllocateInfo CreateCommandBufferInfo{};
	CreateCommandBufferInfo.commandPool = CommandPool;
	CreateCommandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
	CreateCommandBufferInfo.commandBufferCount = SwapChainImages.size();
	
	CommandBuffers = Device.allocateCommandBuffers(CreateCommandBufferInfo);
}
