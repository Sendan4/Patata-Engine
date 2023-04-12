#include "Vulkan.hpp"
//#include <vulkan/vulkan_enums.hpp>

void Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW) {
	// Get Extensions
	unsigned int extensionInstanceCount = 0;
	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr))
		std::cout << "X Error al obtener la lista de extensiones necesarias : " << SDL_GetError() << std::endl;

	std::vector<const char*> extensionInstanceNames(extensionInstanceCount);
	extensionInstanceNames.push_back("VK_KHR_get_physical_device_properties2");

	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, extensionInstanceNames.data()))
		std::cout << "X Error al obtener la lista de extensiones necesarias : " << SDL_GetError() << std::endl;
	else {
		std::cout << FindianRed1 << Bold << "+ Vulkan Instance Extensions :" << Reset << std::endl;
		for (auto extension : extensionInstanceNames)
			std::cout << Bold << FindianRed1 << "| · " << Reset << extension << Reset << std::endl;
		std::cout << Reset << std::endl;
	}

	vk::ApplicationInfo PatataEngineInfo(
		"Patata Engine",
		VK_MAKE_VERSION(1,0,0),
		"Patata Engine",
		VK_MAKE_VERSION(1,0,0),
		VK_API_VERSION_1_3);

	std::vector <vk::ExtensionProperties> extensiones = vk::enumerateInstanceExtensionProperties();

	vk::InstanceCreateInfo VulkanInstanceInfo(
		vk::InstanceCreateFlags(),
		&PatataEngineInfo, layer, nullptr);
	VulkanInstanceInfo.enabledExtensionCount = uint32_t(extensionInstanceCount);
	VulkanInstanceInfo.ppEnabledExtensionNames = extensionInstanceNames.data();

	VulkanInstance = vk::createInstance(VulkanInstanceInfo);
}

void Graphics::VulkanRenderer::PhysicalDevices(void) {
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	PhysicalDeviceProperties = PhysicalDevice.getProperties();
}

uint32_t Graphics::VulkanRenderer::CreateQueue(void) {
	QueueFamilyProperties = PhysicalDevice.getQueueFamilyProperties();

	for (uint32_t i = 0; i < QueueFamilyProperties.size(); i++)
		if ((QueueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) == vk::QueueFlagBits::eGraphics) {
			GraphicsQueueFamilyIndex = i;
			break;
		}
	return GraphicsQueueFamilyIndex;
}

void Graphics::VulkanRenderer::InitDevice(void) {
	vk::DeviceQueueCreateInfo DeviceQueueCreateInfo(
			vk::DeviceQueueCreateFlags(),
			uint32_t(GraphicsQueueFamilyIndex), 1,
			&QueuePriority);

	vk::DeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.enabledExtensionCount = uint32_t(DeviceExtensions.size());
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();
	DeviceCreateInfo.pNext = {};
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;

	if (DeviceExtensions.size() >= 1) {
		std::cout << Bold << FindianRed1 << "+ Vulkan Device Extensions :" << Reset << std::endl;
		for (auto Extensions : DeviceExtensions)
			std::cout << Bold << FindianRed1 << "| · " << Reset << Extensions << Reset << std::endl;
		std::cout << std::endl;
	}

	Device = PhysicalDevice.createDevice(DeviceCreateInfo);
}

void Graphics::VulkanRenderer::CreateSwapChain(void) {
	std::vector <vk::SurfaceFormatKHR> Formats = PhysicalDevice.getSurfaceFormatsKHR(Surface);
	Format = (Formats[0].format == vk::Format::eUndefined) ? vk::Format::eB8G8R8A8Unorm : Formats[0].format;

	SurfaceCapabilities = PhysicalDevice.getSurfaceCapabilitiesKHR(Surface);
	std::vector <vk::PresentModeKHR> PresentModes = PhysicalDevice.getSurfacePresentModesKHR(Surface);
	std::vector <vk::SurfaceFormatKHR> SurfaceFormats = PhysicalDevice.getSurfaceFormatsKHR(Surface);

	SwapChainExtent.width = 1280;
	SwapChainExtent.height = 720;

	for (auto Mode : PresentModes)
		Mode = (Mode == vk::PresentModeKHR::eFifo) ? PresentMode = vk::PresentModeKHR::eFifo : PresentMode = Mode;

	SurfaceFormat = SurfaceFormats[0];

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

	SwapChain = Device.createSwapchainKHR(SwapChainCreateInfo);
}

void Graphics::VulkanRenderer::CreateImageView(void) {
	vk::ImageCreateInfo CreateImageInfo{};
	CreateImageInfo.setImageType(vk::ImageType::e2D);
	CreateImageInfo.setExtent(vk::Extent3D {SwapChainExtent.width, SwapChainExtent.height, 1});
	CreateImageInfo.setMipLevels(1);
	CreateImageInfo.setArrayLayers(1);
	CreateImageInfo.setFormat(Format);
	CreateImageInfo.setTiling(vk::ImageTiling::eOptimal);
	CreateImageInfo.setUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferSrc);
	CreateImageInfo.setInitialLayout(vk::ImageLayout::eUndefined);

	Image = Device.createImage(CreateImageInfo);

	vk::PhysicalDeviceMemoryProperties MemoryProperties = PhysicalDevice.getMemoryProperties();
	vk::MemoryRequirements MemoryReq = Device.getImageMemoryRequirements(Image);
	uint32_t MemoryHeapSize = MemoryProperties.memoryHeaps[0].size;
	uint32_t MemoryTypeIndex = 0;

	for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++)
		if ((MemoryReq.memoryTypeBits & (1 << i)) && (MemoryProperties.memoryTypes[i].propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal)) {
			MemoryTypeIndex = i;
			break;
		}

	vk::MemoryAllocateInfo CreateMemoryAllocateInfo{};
	CreateMemoryAllocateInfo.allocationSize = MemoryReq.size;
	CreateMemoryAllocateInfo.memoryTypeIndex = MemoryTypeIndex;

	ImageMemory = Device.allocateMemory(CreateMemoryAllocateInfo);
	Device.bindImageMemory(Image, ImageMemory, 0);

	vk::ImageViewCreateInfo CreateImageViewInfo{};
	CreateImageViewInfo.setImage(Image);
	CreateImageViewInfo.setViewType(vk::ImageViewType::e2D);
	CreateImageViewInfo.setFormat(Format);
	CreateImageViewInfo.setSubresourceRange(vk::ImageSubresourceRange(
    	vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

	ImageView = Device.createImageView(CreateImageViewInfo);
}

void Graphics::VulkanRenderer::CreateCommandBuffer(void) {
	vk::CommandPoolCreateInfo CreateCommandPoolInfo(
			vk::CommandPoolCreateFlags(), GraphicsQueueFamilyIndex);

	CommandPool = Device.createCommandPool(CreateCommandPoolInfo);

	vk::CommandBufferAllocateInfo CreateCommandBufferInfo{};
	CreateCommandBufferInfo.commandPool = CommandPool;
	CreateCommandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
	CreateCommandBufferInfo.commandBufferCount = 1;

	CommandBuffer = Device.allocateCommandBuffers(CreateCommandBufferInfo);
}

void Graphics::VulkanRenderer::VulkanInfo(void) {
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	std::string vsync;
	if (PresentMode == vk::PresentModeKHR::eFifo)
		vsync = "Yes | Using eFifo";
	else
		vsync = "No";

	std::cout <<  FindianRed1 << Bold << "+ Informacion general de Vulkan :" << Reset << std::endl;	
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << vk::to_string(PhysicalDeviceProperties.deviceType) << ":\t" << Reset << PhysicalDeviceProperties.deviceName << " " << PhysicalDeviceProperties.vendorID << Reset << std::endl;
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Vulkan Version:\t" << Reset << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << Reset << std::endl;
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Driver Version:\t" << Reset << PhysicalDeviceProperties.driverVersion << std::endl;
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Vsync:\t" << Reset << vsync << std::endl;

	std::cout << std::endl;
}

Graphics::VulkanRenderer::VulkanRenderer(SDL_Window * WINDOW) {
	CreateInstance(WINDOW);
	PhysicalDevices();
	GraphicsQueueFamilyIndex = CreateQueue();
	InitDevice();

	if (!SDL_Vulkan_CreateSurface(WINDOW, VulkanInstance, reinterpret_cast<VkSurfaceKHR*>(&Surface)))
		std::cout << BLightGoldenRod1 << "X No se pudo crear la Superficie" << Reset << std::endl;

	CreateSwapChain();
	CreateImageView();
	CreateCommandBuffer();
	VulkanInfo();
}

Graphics::VulkanRenderer::~VulkanRenderer(void) {
	Device.freeCommandBuffers(CommandPool, CommandBuffer);
	Device.destroyCommandPool(CommandPool);

	Device.freeMemory(ImageMemory);
	Device.destroyImage(Image);
	Device.destroyImageView(ImageView);
	Device.destroySwapchainKHR(SwapChain);
	VulkanInstance.destroySurfaceKHR(Surface);
	Device.destroy();
	VulkanInstance.destroy();
}
