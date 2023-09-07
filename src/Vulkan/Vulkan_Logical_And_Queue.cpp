#include <vector>

#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "Patata_Engine/Graphics/Vulkan_Renderer.hpp"
#include "Patata_Engine/Log.hpp"

uint32_t Patata::Graphics::VulkanRenderer::CreateLogicalDeviceAndCreateQueue(void) {
	uint32_t GraphicsQueueFamilyIndex = 0;
	float QueuePriority = 1.0f;
	std::vector <vk::QueueFamilyProperties> QueueFamilyProperties;

	QueueFamilyProperties = PhysicalDevice.getQueueFamilyProperties();

	for (uint32_t indexFlag = 0; indexFlag < QueueFamilyProperties.size(); indexFlag++)
		if ((QueueFamilyProperties[indexFlag].queueFlags & vk::QueueFlagBits::eGraphics) == vk::QueueFlagBits::eGraphics) {
			GraphicsQueueFamilyIndex = indexFlag;
			break;
		}

	vk::DeviceQueueCreateInfo DeviceQueueCreateInfo {};
	DeviceQueueCreateInfo.flags = vk::DeviceQueueCreateFlagBits();
	DeviceQueueCreateInfo.queueFamilyIndex = static_cast<uint32_t>(GraphicsQueueFamilyIndex);
	DeviceQueueCreateInfo.queueCount = 1;
	DeviceQueueCreateInfo.pQueuePriorities = &QueuePriority;

	const std::vector <const char *> DeviceExtensions = {
		"VK_KHR_swapchain",
		"VK_KHR_driver_properties",
		"VK_KHR_maintenance4"};

	vk::DeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();
	DeviceCreateInfo.pNext = {};
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;

	Patata::Log::ListVulkanDeviceResult(DeviceExtensions);

	vk::Result Result = PhysicalDevice.createDevice(&DeviceCreateInfo, nullptr, &Device);

	Patata::Log::VulkanLogicalDeviceResult(Result);

	Queue = Device.getQueue(GraphicsQueueFamilyIndex, 0); 
	return GraphicsQueueFamilyIndex;
}
