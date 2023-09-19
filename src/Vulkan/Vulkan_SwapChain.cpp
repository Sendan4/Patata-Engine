#include <iostream>
#include <vector>
#include <tuple>

#include <yaml-cpp/yaml.h>

#include "Patata_Engine/Patata_Engine.hpp"
#include "Patata_Engine/Graphics/Vulkan_Renderer.hpp"
#include "Patata_Engine/Terminal_Colors.hpp"
#include "Patata_Engine/Log.hpp"

std::tuple<vk::PresentModeKHR, vk::Format> Patata::Graphics::VulkanRenderer::CreateSwapChain(uint32_t &GraphicsQueueFamilyIndex, YAML::Node CONFIG) {
	std::vector <vk::SurfaceFormatKHR> Formats = PhysicalDevice.getSurfaceFormatsKHR(Surface);

	for (uint16_t i = 0; i < Formats.size(); i++)
		if (Formats[i].format == vk::Format::eB8G8R8A8Unorm)
			ColorFormat = vk::Format::eB8G8R8A8Unorm;
		else if (Formats[i].format == vk::Format::eUndefined)
			ColorFormat = Formats[i].format;

	SurfaceCapabilities = PhysicalDevice.getSurfaceCapabilitiesKHR(Surface);
	std::vector <vk::PresentModeKHR> PresentModes = PhysicalDevice.getSurfacePresentModesKHR(Surface);
	std::vector <vk::SurfaceFormatKHR> SurfaceFormats = PhysicalDevice.getSurfaceFormatsKHR(Surface);

	SwapChainExtent.width = 1280;
	SwapChainExtent.height = 720;

	if (CONFIG["vsync"].as<bool>()) {
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

	Patata::Log::CheckSwapChain(Result);	

	return {PresentMode, ColorFormat};
}
