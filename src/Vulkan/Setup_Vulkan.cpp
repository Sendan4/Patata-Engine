#include "Graphics/Vulkan.hpp"
#include "Core/terminal_colors.hpp"

// Instancia
void Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW) {
	// Obtener las extensiones
	unsigned int extensionInstanceCount = 0;
	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr))
		std::cout << "X Error al obtener la lista de extensiones necesarias: " << SDL_GetError() << std::endl;

	std::vector<const char*> extensionInstanceNames(extensionInstanceCount);
	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, extensionInstanceNames.data()))
		std::cout << "X Error al obtener la lista de extensiones necesarias: " << SDL_GetError() << std::endl;
	else {
		std::cout << FRojo3 << Bold << "+ Vulkan Instance Extensions :" << Reset << std::endl;
		for (int c = 0; c < int(extensionInstanceNames.size()); c++)
			std::cout << Bold << FRojo3 << "| · " << Reset << extensionInstanceNames[c] << Reset << std::endl;
		std::cout << Reset << std::endl;
	}

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
	VulkanInstanceInfo.enabledExtensionCount = uint32_t(extensionInstanceCount);
	VulkanInstanceInfo.ppEnabledExtensionNames = extensionInstanceNames.data();

	VulkanInstance = vk::createInstance(VulkanInstanceInfo);
}

// Enumerar los dispositivos fisicos
void Graphics::VulkanRenderer::PhysicalDevices(void) {
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	PhysicalDeviceProperties = PhysicalDevice.getProperties();

	std::cout << FRojo3 << Bold << "+ Informacion general de Vulkan :" << Reset << std::endl;
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;
	std::cout << FRojo3 << Bold << "| · " << Reset << Bold << "GPU / iGPU: \t" << Reset << PhysicalDeviceProperties.deviceName << Reset << std::endl;
	std::cout << FRojo3 << Bold << "| · " << Reset << Bold << "Vulkan Version:\t" << Reset << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << Reset << std::endl << std::endl;
}

void Graphics::VulkanRenderer::CreateSurface(SDL_Window * WINDOW) {
	if (!SDL_Vulkan_CreateSurface(WINDOW, VulkanInstance, (VkSurfaceKHR*)&Surface))
		std::cout << BLightGoldenRod1 << "X No se pudo crear la Superficie" << Reset << std::endl;

	SurfaceCapabilities = PhysicalDevice.getSurfaceCapabilitiesKHR(Surface);
}

void Graphics::VulkanRenderer::InitDevice(void) {
	vk::DeviceQueueCreateInfo DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), uint32_t(GraphicsQueueFamilyIndex), 1, &QueuePriority);

	vk::DeviceCreateInfo DeviceCreateInfo(vk::DeviceCreateFlags(), DeviceQueueCreateInfo);
	DeviceCreateInfo.enabledExtensionCount = uint32_t(DeviceExtensions.size());
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

	std::cout << Bold << FRojo3 << "+ Vulkan Device Extensions :" << Reset << std::endl;
	for (int c = 0; c <= int(DeviceExtensions.size()); c++)
		std::cout << Bold << FRojo3 << "| · " << Reset << DeviceExtensions[c] << Reset << std::endl;
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

	std::cout << " Compute Queue Family Index:\t" << GraphicsQueueFamilyIndex << std::endl << std::endl;
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

void Graphics::VulkanRenderer::Setup(void) {
	//
}

Graphics::VulkanRenderer::~VulkanRenderer(void) {
	vkDestroySurfaceKHR(VulkanInstance, Surface, nullptr);
	Device.freeCommandBuffers(CommandPool, CommandBuffer);
	Device.destroyCommandPool(CommandPool);
	Device.destroy();
	VulkanInstance.destroy();
}
