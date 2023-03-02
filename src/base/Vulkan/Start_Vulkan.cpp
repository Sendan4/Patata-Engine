#include "Vulkan.hpp"

// Instancia
void Graphics::Vulkan::CreateInstance(void) {
	// Informacion de la aplicacion
	vk::ApplicationInfo PatataEngineInfo(
		"Patata Engine",
		VK_MAKE_VERSION(1,0,0),
		"Patata Engine",
		VK_MAKE_VERSION(1,0,0),
		VK_API_VERSION_1_2);
	// Instancia
	vk::InstanceCreateInfo VulkanInstanceInfo(
		vk::InstanceCreateFlags(),
		&PatataEngineInfo, 0, nullptr);

	VulkanInstance = vk::createInstance(VulkanInstanceInfo);
}

// Enumerar los dispositivos fisicos
void Graphics::Vulkan::EnumeratePhysicalDevices(void) {
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	PhysicalDeviceProperties = PhysicalDevice.getProperties();
}

void Graphics::Vulkan::InitDevice(void) {
	QueueFamilyProperties = PhysicalDevice.getQueueFamilyProperties();
	
	Device = PhysicalDevice.createDevice(vk::DeviceCreateInfo(vk::DeviceCreateFlags(), DeviceQueueCreateInfo));
}

void Graphics::Vulkan::Finish(void) {
	VulkanInstance.destroy();
}
