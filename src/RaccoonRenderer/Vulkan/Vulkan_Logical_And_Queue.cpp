#include "Vulkan_Logical_And_Queue.hpp"

uint32_t Patata::Graphics::RaccoonRenderer::VulkanBackend::CreateLogicalDeviceAndCreateQueue(void) {
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

	const char * DeviceExtensions[] = {
		"VK_KHR_swapchain",
		"VK_KHR_driver_properties"
	};

	vk::DeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.enabledExtensionCount = std::size(DeviceExtensions) - 1;
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions;
	DeviceCreateInfo.pNext = {};
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;

	Patata::Log::VulkanList(DeviceExtensions, std::size(DeviceExtensions) - 1, "Device Extensions");

	vk::Result Result = PhysicalDevice.createDevice(&DeviceCreateInfo, nullptr, &Device);

	Patata::Log::VulkanCheck("Physical Device", Result);

	Queue = Device.getQueue(GraphicsQueueFamilyIndex, 0); 
	return GraphicsQueueFamilyIndex;
}
