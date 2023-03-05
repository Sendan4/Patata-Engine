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
		&PatataEngineInfo, Layers, nullptr);


	VulkanInstance = vk::createInstance(VulkanInstanceInfo);
}

// Enumerar los dispositivos fisicos
void Graphics::Vulkan::PhysicalDevices(void) {
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	PhysicalDeviceProperties = PhysicalDevice.getProperties();
	
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;
	std::cout << "GPU / iGPU: " << PhysicalDeviceProperties.deviceName << std::endl;
	std::cout << "Vulkan Version: " << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << std::endl;
}

uint32_t Graphics::Vulkan::CreateQueue(void) {
	QueueFamilyProperties = PhysicalDevice.getQueueFamilyProperties();
	auto PropertiesIterator = std::find_if(QueueFamilyProperties.begin(), QueueFamilyProperties.end(), [](const vk::QueueFamilyProperties& Propiedad){
			return Propiedad.queueFlags & vk::QueueFlagBits::eCompute;
	});
	ComputeQueueFamilyIndex = std::distance(QueueFamilyProperties.begin(), PropertiesIterator);
	std::cout << "Compute Queue Family Index: " << ComputeQueueFamilyIndex << std::endl;
	return ComputeQueueFamilyIndex;
}


void Graphics::Vulkan::InitDevice(void) {
	vk::DeviceQueueCreateInfo DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), (uint32_t)ComputeQueueFamilyIndex, 1, &QueuePriority);
	vk::DeviceCreateInfo DeviceCreateInfo(vk::DeviceCreateFlags(), DeviceQueueCreateInfo);
	Device = PhysicalDevice.createDevice(vk::DeviceCreateInfo(vk::DeviceCreateFlags(), DeviceQueueCreateInfo));
}

void Graphics::Vulkan::CreateCommandBuffer(void) {
	CommandPool = Device.createCommandPool(vk::CommandPoolCreateInfo(vk::CommandPoolCreateFlags(), ComputeQueueFamilyIndex));
	CommandBuffer = Device.allocateCommandBuffers(vk::CommandBufferAllocateInfo(CommandPool, vk::CommandBufferLevel::ePrimary, 1)).front();
}

void Graphics::Vulkan::CreateSurface(SDL_Window * WINDOW) {
	VkSurfaceKHR _surface;
	SDL_Vulkan_GetInstanceExtensions(WINDOW, extensionCountSDL, LayersSDL);
	SDL_Vulkan_CreateSurface(WINDOW, VulkanInstance, &_surface);
	Surface = vk::SurfaceKHR(_surface);
	//SurfaceCapabilities = PhysicalDevice.getSurfaceCapabilitiesKHR(Surface);
}

void Graphics::Vulkan::CreateSwapChain(void) {
	Formats = PhysicalDevice.getSurfaceFormatsKHR(Surface);
	Format = (Formats[0].format == vk::Format::eUndefined) ? vk::Format::eB8G8R8A8Unorm : Formats[0].format;
}

void Graphics::Vulkan::Finish(void) {
	Device.freeCommandBuffers(CommandPool, CommandBuffer);
	Device.destroyCommandPool(CommandPool);
	Device.destroy();
	VulkanInstance.destroy();
}
