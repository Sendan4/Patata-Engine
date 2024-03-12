#include "Vulkan_SwapChain.hpp"

std::tuple<vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> Patata::Graphics::RaccoonRenderer::VulkanBackend::CreateSwapChain(uint32_t &GraphicsQueueFamilyIndex, YAML::Node CONFIG) {
	std::vector <vk::PresentModeKHR> PresentModes = PhysicalDevice.getSurfacePresentModesKHR(Surface);
	std::vector <vk::SurfaceFormatKHR> SurfaceFormats = PhysicalDevice.getSurfaceFormatsKHR(Surface);

	SwapChainExtent.width = 1280;
	SwapChainExtent.height = 720;

	if (CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
		for (const vk::PresentModeKHR &Mode : PresentModes) {
			if (Mode == vk::PresentModeKHR::eMailbox) {
				PresentMode = vk::PresentModeKHR::eMailbox;
				break;
			}
			if (Mode == vk::PresentModeKHR::eFifo) {
				PresentMode = vk::PresentModeKHR::eFifo;
				break;
			}
		}
	}
	else
		PresentMode = vk::PresentModeKHR::eImmediate;

	SurfaceFormat = SurfaceFormats[0];

	vk::SurfaceCapabilitiesKHR SurfaceCapabilities = PhysicalDevice.getSurfaceCapabilitiesKHR(Surface);

	//vk::Viewport Viewport = vk::Viewport(0.0f, 0.0f, static_cast<float>(SurfaceCapabilities.currentExtent.width), static_cast<float>(SurfaceCapabilities.currentExtent.height), 0, 1.0f);

	vk::SwapchainCreateInfoKHR SwapChainCreateInfo{};
	SwapChainCreateInfo.surface = Surface;
	SwapChainCreateInfo.minImageCount = SurfaceCapabilities.minImageCount;
	SwapChainCreateInfo.imageFormat = SurfaceFormat.format;
	SwapChainCreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
	SwapChainCreateInfo.imageExtent = SwapChainExtent;
	SwapChainCreateInfo.imageArrayLayers = 1;
	SwapChainCreateInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
	SwapChainCreateInfo.preTransform = SurfaceCapabilities.currentTransform;
	SwapChainCreateInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
	SwapChainCreateInfo.presentMode = PresentMode;
	SwapChainCreateInfo.clipped = VK_TRUE;
	SwapChainCreateInfo.queueFamilyIndexCount = GraphicsQueueFamilyIndex;
	SwapChainCreateInfo.oldSwapchain = nullptr;
	
	vk::Result Result = Device.createSwapchainKHR(&SwapChainCreateInfo, nullptr, &SwapChain);

	Patata::Log::VulkanCheck("SwapChain", Result);	

	return {PresentMode, vk::Format::eUndefined, SurfaceFormat.colorSpace};
}
