#include "Vulkan_ImageView.hpp"

void Patata::Graphics::RaccoonRenderer::VulkanBackend::CreateImageView(uint32_t &GraphicsQueueFamilyIndex) {
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

	vk::Result Result = Device.createImage(&CreateImageInfo, nullptr, &DepthImage);

	if (Result != vk::Result::eSuccess)
		#if defined(_WIN64)
			fast_io::io::println(fast_io::out(), "DepthImage For BindImageMemory : ", vk::to_string(Result));
		#else
			fast_io::io::println(PATATA_TERM_BOLD, "DepthImage For BindImageMemory : ", PATATA_TERM_RESET, PATATA_TERM_COLOR_YELLOW, vk::to_string(Result), PATATA_TERM_RESET);
		#endif
	else
		#if defined(_WIN64)
			fast_io::io::println(fast_io::out(), "DepthImage For BindImageMemory : ", vk::to_string(Result));
		#else
			fast_io::io::println(PATATA_TERM_BOLD, "DepthImage For BindImageMemory : ", PATATA_TERM_RESET, PATATA_TERM_COLOR_GREEN, vk::to_string(Result), PATATA_TERM_RESET);
		#endif

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

	#if defined(_WIN64)
	fast_io::io::println(fast_io::out(), "Creating SwapChainBuffer : ");
	#else

	fast_io::io::println("Creating SwapChainBuffer : ");
	#endif
	for (uint32_t i = 0; i < SwapChainBuffers.size(); i++) {
		SwapChainBuffers[i].Image = SwapChainImages[i];
		
		Result = Device.createImageView(&CreateImageViewInfo, nullptr, &ImageView);
		
		if (Result != vk::Result::eSuccess)
			#if defined(_WIN64)
				fast_io::io::println(fast_io::out(), "SwapChainBuffer ImageView : ", vk::to_string(Result));
			#else
				fast_io::io::println("SwapChainBuffer ImageView : ", vk::to_string(Result));
			#endif
		else
			#if defined(_WIN64)
				fast_io::io::println(fast_io::out(), "SwapChainBuffer ImageView : ", vk::to_string(Result));
			#else
				fast_io::io::println("SwapChainBuffer ImageView : ", vk::to_string(Result));
			#endif

		//SwapChainBuffers[i].Views[1] = ImageView;

		Device.destroyImageView(ImageView);

		//SwapChainBuffers[i].FrameBuffer = ;
	}
	fast_io::io::println(fast_io::out(), "");
}
