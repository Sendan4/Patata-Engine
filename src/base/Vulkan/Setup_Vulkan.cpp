#include "Vulkan.hpp"

// Instancia
void Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW) {
	// Informacion de la aplicacion
	vk::ApplicationInfo PatataEngineInfo(
		"Patata Engine",
		VK_MAKE_VERSION(1,0,0),
		"Patata Engine",
		VK_MAKE_VERSION(1,0,0),
		VK_API_VERSION_1_2);

	std::vector <vk::ExtensionProperties> extensiones = vk::enumerateInstanceExtensionProperties();

	// Instancia
	vk::InstanceCreateInfo VulkanInstanceInfo(
		vk::InstanceCreateFlags(),
		&PatataEngineInfo, layer, nullptr);
	VulkanInstanceInfo.enabledExtensionCount = uint32_t(InstanceExtensions.size());
	VulkanInstanceInfo.ppEnabledExtensionNames = InstanceExtensions.data();

	VulkanInstance = vk::createInstance(VulkanInstanceInfo);
}

// Enumerar los dispositivos fisicos
void Graphics::VulkanRenderer::PhysicalDevices(void) {
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	PhysicalDeviceProperties = PhysicalDevice.getProperties();

	std::cout << "| Informacion general de Vulkan :" << std::endl;
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;
	std::cout << "|  · GPU / iGPU: " << PhysicalDeviceProperties.deviceName << std::endl;
	std::cout << "|  · Vulkan Version: " << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << std::endl << std::endl;
}

void Graphics::Vulkan::CreateSurface(SDL_Window * WINDOW) {


	//SurfaceCapabilities = PhysicalDevice.getSurfaceCapabilitiesKHR(Surface);
}

void Graphics::VulkanRenderer::InitDevice(void) {
	vk::DeviceQueueCreateInfo DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), uint32_t(GraphicsQueueFamilyIndex), 1, &QueuePriority);

	vk::DeviceCreateInfo DeviceCreateInfo(vk::DeviceCreateFlags(), DeviceQueueCreateInfo);
	DeviceCreateInfo.enabledExtensionCount = uint32_t(DeviceExtensions.size());
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

	std::cout << "| Vulkan Device Extensions :" << std::endl;
	for (int c = 0; c <= int(DeviceExtensions.size()); c++)
		std::cout << "|  · " << DeviceExtensions[c] << std::endl;
	std::cout << std::endl;

	Device = PhysicalDevice.createDevice(vk::DeviceCreateInfo(vk::DeviceCreateFlags(), DeviceQueueCreateInfo));
}

uint32_t Graphics::VulkanRenderer::CreateQueue(void) {
	QueueFamilyProperties = PhysicalDevice.getQueueFamilyProperties();

	for (uint32_t i = 0; i < QueueFamilyProperties.size(); i++)
		if ((QueueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) == vk::QueueFlagBits::eGraphics) {
			GraphicsQueueFamilyIndex = i;
			break;
		}

	std::cout << "|  · Compute Queue Family Index: " << GraphicsQueueFamilyIndex << std::endl << std::endl;
	return GraphicsQueueFamilyIndex;
}

void Graphics::VulkanRenderer::CreateCommandBuffer(void) {
	CommandPool = Device.createCommandPool(vk::CommandPoolCreateInfo(vk::CommandPoolCreateFlags(), GraphicsQueueFamilyIndex));
	CommandBuffer = Device.allocateCommandBuffers(vk::CommandBufferAllocateInfo(CommandPool, vk::CommandBufferLevel::ePrimary, 1)).front();
}

void Graphics::VulkanRenderer::CreateSwapChain(void) {

}

Graphics::VulkanRenderer::VulkanRenderer(SDL_Window * WINDOW) {
	CreateInstance(WINDOW);
	PhysicalDevices();
	CreateSurface(WINDOW);
	InitDevice();
	GraphicsQueueFamilyIndex = CreateQueue();
	CreateCommandBuffer();
	CreateSwapChain();
}

Graphics::VulkanRenderer::~VulkanRenderer(void) {
	vkDestroySurfaceKHR(VulkanInstance, Surface, nullptr);
	Device.freeCommandBuffers(CommandPool, CommandBuffer);
	Device.destroyCommandPool(CommandPool);
	Device.destroy();
	VulkanInstance.destroy();
}
