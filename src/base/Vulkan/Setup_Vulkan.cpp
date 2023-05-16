#include "Vulkan.hpp"

bool Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW) {
	// Get Extensions
	unsigned int extensionInstanceCount = 0;
	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr))
		std::cout << Bold << " X Error al obtener la lista de extensiones necesarias : " << Reset << SDL_GetError() << "\n";

	std::vector<const char*> extensionInstanceNames(extensionInstanceCount);
	extensionInstanceNames.push_back("VK_KHR_get_physical_device_properties2");

	if (!SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, extensionInstanceNames.data()))
		std::cout << Bold << " X Error al obtener la lista de extensiones necesarias : " << Reset << SDL_GetError() << "\n";
	else {
		std::cout << FindianRed1 << Bold << "+ Vulkan Instance Extensions :" << Reset << "\n";
		for (auto extension : extensionInstanceNames)
			std::cout << Bold << FindianRed1 << "| · " << Reset << extension << Reset << "\n";
	}

	vk::ApplicationInfo PatataEngineInfo {};
	PatataEngineInfo.pApplicationName = "Patata Engine";
	PatataEngineInfo.applicationVersion = 1;
	PatataEngineInfo.pEngineName = "Patata Engine";
	PatataEngineInfo.engineVersion = 1;
	PatataEngineInfo.apiVersion = VK_API_VERSION_1_3;

	const char * layer = {"VK_LAYER_KHRONOS_validation"};

	vk::InstanceCreateInfo VulkanInstanceInfo {};
	VulkanInstanceInfo.enabledLayerCount = 1;
	VulkanInstanceInfo.ppEnabledLayerNames = &layer;
	VulkanInstanceInfo.pApplicationInfo = &PatataEngineInfo;
	VulkanInstanceInfo.enabledExtensionCount = uint32_t(extensionInstanceCount);
	VulkanInstanceInfo.ppEnabledExtensionNames = extensionInstanceNames.data();
	
	vk::Result resultado;
	resultado = vk::createInstance(&VulkanInstanceInfo, nullptr, &VulkanInstance);
	if (resultado != vk::Result::eSuccess) {
		std::cout << FindianRed1 << "Vulkan Instance Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(resultado) << Reset << "\n";
		return false;
	}
	std::cout << FindianRed1 << "Vulkan Instance Result :\t" << Reset << Chartreuse1 << vk::to_string(resultado) << Reset << "\n";

	return true;
}

uint32_t Graphics::VulkanRenderer::CreateLogicalDeviceAndCreateQueue(void) {
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
	DeviceQueueCreateInfo.queueFamilyIndex = uint32_t(GraphicsQueueFamilyIndex);
	DeviceQueueCreateInfo.queueCount = 1;
	DeviceQueueCreateInfo.pQueuePriorities = &QueuePriority;

	const std::vector <const char *> DeviceExtensions = {
		"VK_KHR_swapchain",
		"VK_EXT_multi_draw",
		"VK_KHR_maintenance4"};

	vk::DeviceCreateInfo DeviceCreateInfo{};
	DeviceCreateInfo.enabledExtensionCount = uint32_t(DeviceExtensions.size());
	DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();
	DeviceCreateInfo.pNext = {};
	DeviceCreateInfo.queueCreateInfoCount = 1;
	DeviceCreateInfo.pQueueCreateInfos = &DeviceQueueCreateInfo;

	if (DeviceExtensions.size() >= 1) {
		std::cout << Bold << FindianRed1 << "+ Vulkan Device Extensions :" << Reset << "\n";
		for (auto Extensions : DeviceExtensions)
			std::cout << Bold << FindianRed1 << "| · " << Reset << Extensions << Reset << "\n";
	}

	vk::Result resultado = PhysicalDevice.createDevice(&DeviceCreateInfo, nullptr, &Device);
	if (resultado != vk::Result::eSuccess) {
		std::cout << FindianRed1 << "Vulkan Logical Device Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(resultado) << Reset << "\n";
		return 0;
	}
	else std::cout << FindianRed1 << "Vulkan Logical Device Result :\t" << Reset << Chartreuse1 << vk::to_string(resultado) << Reset << "\n";

	Queue = Device.getQueue(GraphicsQueueFamilyIndex, 0); 
	return GraphicsQueueFamilyIndex;
}

void Graphics::VulkanRenderer::CreateSwapChain(uint32_t &GraphicsQueueFamilyIndex) {
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

	for (auto Mode : PresentModes)
		(Mode == vk::PresentModeKHR::eFifo) ? PresentMode = vk::PresentModeKHR::eFifo : PresentMode = Mode;

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
	
	vk::Result Result;
	Result = Device.createSwapchainKHR(&SwapChainCreateInfo, nullptr, &SwapChain);
	if (Result != vk::Result::eSuccess)
		std::cout << FindianRed1 << "SwapChain Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
	else
		std::cout << FindianRed1 << "SwapChain Result :\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";
}

void Graphics::VulkanRenderer::CreateImageView(uint32_t &GraphicsQueueFamilyIndex) {
	vk::ImageCreateInfo CreateImageInfo{};
	CreateImageInfo.imageType = vk::ImageType::e2D;
	CreateImageInfo.setExtent(vk::Extent3D {SwapChainExtent.width, SwapChainExtent.height, 1});
	CreateImageInfo.mipLevels = 1;
	CreateImageInfo.arrayLayers = 1;
	CreateImageInfo.format = vk::Format::eD32SfloatS8Uint;
	CreateImageInfo.tiling = vk::ImageTiling::eOptimal;
	CreateImageInfo.usage = vk::ImageUsageFlagBits::eDepthStencilAttachment | vk::ImageUsageFlagBits::eTransferSrc;
	//CreateImageInfo.usage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferSrc;
	CreateImageInfo.setInitialLayout(vk::ImageLayout::eUndefined);
	CreateImageInfo.samples = vk::SampleCountFlagBits::e1;
	CreateImageInfo.queueFamilyIndexCount = 1;
	CreateImageInfo.pQueueFamilyIndices = &GraphicsQueueFamilyIndex;

	vk::Result Result;
	Result = Device.createImage(&CreateImageInfo, nullptr, &DepthImage);
	if (Result != vk::Result::eSuccess)
		std::cout << FindianRed1 << "DepthImage For BindImageMemory -> Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
	else
		std::cout << FindianRed1 << "DepthImage For BindImageMemory -> Result :\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";

	// create Depht and color Image

	vk::PhysicalDeviceMemoryProperties MemoryProperties = PhysicalDevice.getMemoryProperties();
	vk::MemoryRequirements MemoryReq;

	MemoryReq = Device.getImageMemoryRequirements(DepthImage);

	uint32_t MemoryTypeIndex = 0;
	
	for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++)
		if ((MemoryReq.memoryTypeBits & (1 << i)) && (MemoryProperties.memoryTypes[i].propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal)) {
			MemoryTypeIndex = i;
			break;
		}
	
	vk::MemoryAllocateInfo CreateMemoryAllocateInfo {};
	CreateMemoryAllocateInfo.allocationSize = MemoryReq.size;
	CreateMemoryAllocateInfo.memoryTypeIndex = MemoryTypeIndex;

	ImageMemory = Device.allocateMemory(CreateMemoryAllocateInfo);
	Device.bindImageMemory(DepthImage, ImageMemory, 0);

	vk::ImageViewCreateInfo CreateImageViewInfo{};
	CreateImageViewInfo.image = DepthImage;
	CreateImageViewInfo.setViewType(vk::ImageViewType::e2D);
	CreateImageViewInfo.format = vk::Format::eD32SfloatS8Uint;
	CreateImageViewInfo.setSubresourceRange(vk::ImageSubresourceRange(
		vk::ImageAspectFlagBits::eStencil, 0, 1, 0, 1));	

	std::vector <vk::Image> SwapChainImages = Device.getSwapchainImagesKHR(SwapChain);
	SwapChainBuffers.resize(SwapChainImages.size());

	std::cout << Bold << "\nCreating SwapChainBuffer\n" << Reset;
	std::cout << "SwapChainImages -> NumberOfImages :\t" << SwapChainImages.size() << "\n";
	for (uint32_t i = 0; i < SwapChainBuffers.size(); i++) {
		SwapChainBuffers[i].Image = SwapChainImages[i];

		//Result = Device.createImageView(&CreateImageViewInfo, nullptr, &ImageView);
		//if (Result != vk::Result::eSuccess)
		//	std::cout << FindianRed1 << Bold << "SwapChainBuffer -> ImageView Result " << i << " :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
		//else
		//	std::cout << FindianRed1 << Bold << "SwapChainBuffer -> ImageView Result " << i << ":\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";
		//SwapChainBuffers[i].Views[0] = ColorImageView;
		
		Result = Device.createImageView(&CreateImageViewInfo, nullptr, &ImageView);
		if (Result != vk::Result::eSuccess)
			std::cout << FindianRed1 << "SwapChainBuffer -> ImageView Result " << i << " :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
		else
			std::cout << FindianRed1 << "SwapChainBuffer -> ImageView Result " << i << ":\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";

		SwapChainBuffers[i].Views[1] = ImageView;

		Device.destroyImageView(ImageView);

		//SwapChainBuffers[i].FrameBuffer = ;
	}
	std::cout << "\n";
}

void Graphics::VulkanRenderer::CreateCommandBuffer(uint32_t &GraphicsQueueFamilyIndex) {
	vk::CommandPoolCreateInfo CreateCommandPoolInfo {};
	CreateCommandPoolInfo.flags = vk::CommandPoolCreateFlagBits::eTransient;
	CreateCommandPoolInfo.queueFamilyIndex = GraphicsQueueFamilyIndex;

	vk::Result Result;
	Result = Device.createCommandPool(&CreateCommandPoolInfo, nullptr, &CommandPool);
	if (Result != vk::Result::eSuccess)
		std::cout << FindianRed1 << "CommandPool Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
	else
		std::cout << FindianRed1 << "CommandPool Result :\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";

	std::vector <vk::Image> SwapChainImages = Device.getSwapchainImagesKHR(SwapChain);

	vk::CommandBufferAllocateInfo CreateCommandBufferInfo{};
	CreateCommandBufferInfo.commandPool = CommandPool;
	CreateCommandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
	CreateCommandBufferInfo.commandBufferCount = SwapChainImages.size();
	
	CommandBuffers = Device.allocateCommandBuffers(CreateCommandBufferInfo);
}

void Graphics::VulkanRenderer::CreateRenderPass(void) {
	// Color
	vk::AttachmentDescription CreateColorAttachmentDescription {};
	CreateColorAttachmentDescription.format = ColorFormat;
	CreateColorAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
	CreateColorAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
	CreateColorAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
	CreateColorAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
	CreateColorAttachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;
	// Depth
	vk::AttachmentDescription CreateDepthAttachmentDescription {};
	CreateDepthAttachmentDescription.format = vk::Format::eD32SfloatS8Uint;
	CreateDepthAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
	CreateDepthAttachmentDescription.storeOp = vk::AttachmentStoreOp::eDontCare;
	CreateDepthAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
	CreateDepthAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
	CreateDepthAttachmentDescription.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

	std::vector <vk::AttachmentDescription> Attachments;
	Attachments.push_back(CreateColorAttachmentDescription);
	Attachments.push_back(CreateDepthAttachmentDescription);

	// Color
	vk::AttachmentReference CreateColorAttachmentReference (0, vk::ImageLayout::eColorAttachmentOptimal);
	// Depth
	vk::AttachmentReference CreateDepthAttachmentReference (1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

	vk::SubpassDescription CreateSubpassDescription {};
	CreateSubpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
	CreateSubpassDescription.inputAttachmentCount = 0;
	CreateSubpassDescription.pInputAttachments = nullptr;
	CreateSubpassDescription.colorAttachmentCount = 1;
	CreateSubpassDescription.pColorAttachments = &CreateColorAttachmentReference;
	CreateSubpassDescription.pDepthStencilAttachment = &CreateDepthAttachmentReference;

	std::vector <vk::SubpassDependency> Dep = {
		vk::SubpassDependency(
			~0U,
			0,
			vk::PipelineStageFlagBits::eBottomOfPipe,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::AccessFlagBits::eMemoryRead,
			vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite,
			vk::DependencyFlagBits::eByRegion
		),
		vk::SubpassDependency(
			0,
			~0U,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::PipelineStageFlagBits::eBottomOfPipe,
			vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite,
			vk::AccessFlagBits::eMemoryRead,
			vk::DependencyFlagBits::eByRegion
	)};	

	vk::RenderPassCreateInfo CreateRenderPassInfo {};
	CreateRenderPassInfo.attachmentCount = Attachments.size();
	CreateRenderPassInfo.pAttachments = Attachments.data();
	CreateRenderPassInfo.subpassCount = 1;
	CreateRenderPassInfo.pSubpasses = &CreateSubpassDescription;
	CreateRenderPassInfo.dependencyCount = static_cast<uint32_t>(Dep.size());
	CreateRenderPassInfo.pDependencies = Dep.data();
	
	vk::Result Result;
	Result = Device.createRenderPass(&CreateRenderPassInfo, nullptr, &RenderPass);
	if (Result != vk::Result::eSuccess)
		std::cout << FindianRed1 << "RenderPass Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
	else
		std::cout << FindianRed1 << "RenderPass Result :\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";
}

void Graphics::VulkanRenderer::CreatePipeline(void) {
	/*vk::RenderPassCreateInfo RenderPassCreateInfo {};
	RenderPassCreateInfo.attachmentCount = 0;
	RenderPassCreateInfo.subpassCount = 0;
	RenderPassCreateInfo.pAttachments = NULL;
	RenderPassCreateInfo.pSubpasses = NULL;
	RenderPassCreateInfo.dependencyCount = 0;
	RenderPassCreateInfo.pDependencies = NULL;
	//RenderPassCreateInfo.pClearValues = 

	RenderPass = Device.createRenderPass(RenderPassCreateInfo);*/
}

Graphics::VulkanRenderer::VulkanRenderer(SDL_Window * WINDOW) {
	CreateInstance(WINDOW);

	PhysicalDevice = VulkanInstance.enumeratePhysicalDevices().front();
	uint32_t GraphicsQueueFamilyIndex = CreateLogicalDeviceAndCreateQueue();

	if (!SDL_Vulkan_CreateSurface(WINDOW, VulkanInstance, reinterpret_cast<VkSurfaceKHR *>(&Surface)))
		std::cout << "SDL Surface :\t" << Reset << BLightGoldenRod1 << "No" << Reset << "\n";
	else
		std::cout << "SDL Surface :\t" << Reset << Chartreuse1 << "Yes" << Reset << "\n";
	
	CreateSwapChain(GraphicsQueueFamilyIndex);
	CreateImageView(GraphicsQueueFamilyIndex);
	CreateCommandBuffer(GraphicsQueueFamilyIndex);
	CreateRenderPass();

	Semaphore = Device.createSemaphore(vk::SemaphoreCreateInfo());

	VulkanInfo();
}

Graphics::VulkanRenderer::~VulkanRenderer(void) {
	Device.destroySemaphore(Semaphore);
	Device.destroyRenderPass(RenderPass);
	Device.freeCommandBuffers(CommandPool, CommandBuffers);
	Device.destroyCommandPool(CommandPool);
	Device.freeMemory(ImageMemory);
	Device.destroyImage(DepthImage);
	//Device.destroyImageView(ImageView);
	Device.destroySwapchainKHR(SwapChain);
	VulkanInstance.destroySurfaceKHR(Surface);
	Device.destroy();
	VulkanInstance.destroy();
}


void Graphics::VulkanRenderer::TestColor(void) {
	//vk::ClearColorValue ClearColor = {1.0f, 0.0f, 0.0f, 1.0f};
	
}
