#include "Graphics/Vulkan.hpp"
#include "Core/terminal_colors.hpp"

bool Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW) {
	// Get Extensions
	unsigned int extensionInstanceCount = 0;
	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr))
		std::cout << Bold << " ❌ Error al obtener la lista de extensiones necesarias : " << Reset << SDL_GetError() << std::endl;

	std::vector<const char*> extensionInstanceNames(extensionInstanceCount);
	extensionInstanceNames.push_back("VK_KHR_get_physical_device_properties2");

	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, extensionInstanceNames.data()))
		std::cout << Bold << " ❌ Error al obtener la lista de extensiones necesarias : " << Reset << SDL_GetError() << std::endl;
	else {
		std::cout << FRojo3 << Bold << "+ Vulkan Instance Extensions :" << Reset << std::endl;
		for (int c = 0; c < int(extensionInstanceNames.size()); c++)
			std::cout << Bold << FRojo3 << "| · " << Reset << extensionInstanceNames[c] << Reset << std::endl;
		std::cout << Reset << std::endl;
	}

	vk::ApplicationInfo PatataEngineInfo {};
	PatataEngineInfo.pApplicationName = "Patata Engine";
	PatataEngineInfo.applicationVersion = 1;
	PatataEngineInfo.pEngineName = "Patata Engine";
	PatataEngineInfo.engineVersion = 1;
	PatataEngineInfo.apiVersion = VK_API_VERSION_1_3;

	vk::InstanceCreateInfo VulkanInstanceInfo {};
	VulkanInstanceInfo.enabledLayerCount = 1;
	VulkanInstanceInfo.ppEnabledLayerNames = &layer;
	VulkanInstanceInfo.pApplicationInfo = &PatataEngineInfo;
	VulkanInstanceInfo.enabledExtensionCount = uint32_t(extensionInstanceCount);
	VulkanInstanceInfo.ppEnabledExtensionNames = extensionInstanceNames.data();

	VulkanInstance = vk::createInstance(VulkanInstanceInfo);
}

void Graphics::VulkanRenderer::PhysicalDevices(void) {
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	PhysicalDeviceProperties = PhysicalDevice.getProperties();

	std::cout << FRojo3 << Bold << "+ Informacion general de Vulkan :" << Reset << std::endl;
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;
	std::cout << FRojo3 << Bold << "| · " << Reset << Bold << "GPU / iGPU: \t" << Reset << PhysicalDeviceProperties.deviceName << Reset << std::endl;
	std::cout << FRojo3 << Bold << "| · " << Reset << Bold << "Vulkan Version:\t" << Reset << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << Reset << std::endl << std::endl;
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

	return GraphicsQueueFamilyIndex;
}

void Graphics::VulkanRenderer::InitDevice(void) {
	vk::DeviceQueueCreateInfo DeviceQueueCreateInfo {};
	DeviceQueueCreateInfo.flags = vk::DeviceQueueCreateFlagBits();
	DeviceQueueCreateInfo.queueFamilyIndex = uint32_t(GraphicsQueueFamilyIndex);
	DeviceQueueCreateInfo.queueCount = 1;
	DeviceQueueCreateInfo.pQueuePriorities = &QueuePriority;

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
	CreateImageInfo.imageType = vk::ImageType::e2D;
	CreateImageInfo.setExtent(vk::Extent3D {SwapChainExtent.width, SwapChainExtent.height, 1});
	CreateImageInfo.setMipLevels(1);
	CreateImageInfo.setArrayLayers(1);
	CreateImageInfo.format = Format;
	CreateImageInfo.tiling = vk::ImageTiling::eOptimal;
	CreateImageInfo.setUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferSrc);
	CreateImageInfo.setInitialLayout(vk::ImageLayout::eUndefined);

	Image = Device.createImage(CreateImageInfo);

	vk::PhysicalDeviceMemoryProperties MemoryProperties = PhysicalDevice.getMemoryProperties();
	vk::MemoryRequirements MemoryReq = Device.getImageMemoryRequirements(Image);

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
	CreateImageViewInfo.image = Image;
	CreateImageViewInfo.setViewType(vk::ImageViewType::e2D);
	CreateImageViewInfo.format = Format;
	CreateImageViewInfo.setSubresourceRange(vk::ImageSubresourceRange(
    	vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

	ImageView = Device.createImageView(CreateImageViewInfo);

	SwapChainImages = Device.getSwapchainImagesKHR(SwapChain);
}

void Graphics::VulkanRenderer::CreateCommandBuffer(void) {
	vk::CommandPoolCreateInfo CreateCommandPoolInfo {};
	CreateCommandPoolInfo.flags = vk::CommandPoolCreateFlagBits::eTransient;
	CreateCommandPoolInfo.queueFamilyIndex = GraphicsQueueFamilyIndex;

	CommandPool = Device.createCommandPool(CreateCommandPoolInfo);

	vk::CommandBufferAllocateInfo CreateCommandBufferInfo{};
	CreateCommandBufferInfo.commandPool = CommandPool;
	CreateCommandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
	CreateCommandBufferInfo.commandBufferCount = 1;

	CommandBuffer = Device.allocateCommandBuffers(CreateCommandBufferInfo);
}

void Graphics::VulkanRenderer::CreateRenderPass(void) {
	vk::AttachmentDescription CreateAttachmentDescription {};
	CreateAttachmentDescription.format = Format;
	CreateAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
	CreateAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
	CreateAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
	CreateAttachmentDescription.initialLayout = vk::ImageLayout::eColorAttachmentOptimal;
	CreateAttachmentDescription.finalLayout = vk::ImageLayout::eGeneral;

	vk::AttachmentReference CreateAttachmentReference (0, vk::ImageLayout::eGeneral);

	vk::SubpassDescription CreateSubpassDescription {};
	CreateSubpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
	CreateSubpassDescription.inputAttachmentCount = 1;
	CreateSubpassDescription.pInputAttachments = &CreateAttachmentReference;
	CreateSubpassDescription.colorAttachmentCount = 1;
	CreateSubpassDescription.pColorAttachments = &CreateAttachmentReference;

	vk::SubpassDependency Dep(
		/* srcSubpass */ 0, 
		/* dstSubpass */ VK_SUBPASS_EXTERNAL, 
		/* srcStageMask */ vk::PipelineStageFlagBits::eColorAttachmentOutput, 
		/* dstStageMask */ vk::PipelineStageFlagBits::eColorAttachmentOutput, 
		/* srcAccessMask */ vk::AccessFlagBits::eColorAttachmentWrite, 
		/* dstAccessMask */ vk::AccessFlagBits::eColorAttachmentWrite, 
		/* dependencyFlags */ vk::DependencyFlagBits::eByRegion);	

	vk::RenderPassCreateInfo CreateRenderPassInfo {};
	CreateRenderPassInfo.attachmentCount = 1;
	CreateRenderPassInfo.pAttachments = &CreateAttachmentDescription;
	CreateRenderPassInfo.subpassCount = 1;
	CreateRenderPassInfo.pSubpasses = &CreateSubpassDescription;
	CreateRenderPassInfo.dependencyCount = 1;
	CreateRenderPassInfo.pDependencies = &Dep;

	RenderPass = Device.createRenderPass(CreateRenderPassInfo);
}

void Graphics::VulkanRenderer::VulkanInfo(void) {
	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	std::string vsync;
	if (PresentMode == vk::PresentModeKHR::eFifo) {
		std::string tmp = Dim;
		vsync = "Yes" + tmp + " | Using eFifo" + Reset;
	}
	else
		vsync = "No";

	std::cout <<  FindianRed1 << Bold << "+ Informacion general de Vulkan :" << Reset << std::endl;	
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << vk::to_string(PhysicalDeviceProperties.deviceType) << ":\t" << Reset << PhysicalDeviceProperties.deviceName << Dim << " " << PhysicalDeviceProperties.vendorID << Reset << std::endl;
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Vulkan Version:\t" << Reset << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << Reset << std::endl;
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Driver Version:\t" << Reset << PhysicalDeviceProperties.driverVersion << std::endl;
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Vsync:\t" << Reset << vsync << std::endl;

	std::cout << std::endl;
}

Graphics::VulkanRenderer::VulkanRenderer(SDL_Window * WINDOW) {
	CreateInstance(WINDOW);
	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	GraphicsQueueFamilyIndex = CreateQueue();
	InitDevice();

	if (!SDL_Vulkan_CreateSurface(WINDOW, VulkanInstance, reinterpret_cast<VkSurfaceKHR*>(&Surface)))
		std::cout << BLightGoldenRod1 << " ❌ Error: No se pudo crear la Superficie" << Reset << std::endl;

	CreateSwapChain();
	CreateImageView();
	CreateCommandBuffer();
	CreateRenderPass();

	Semaphore = Device.createSemaphore(vk::SemaphoreCreateInfo());

	VulkanInfo();
}

Graphics::VulkanRenderer::~VulkanRenderer(void) {
	Device.destroySemaphore(Semaphore);
	Device.destroyRenderPass(RenderPass);
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
