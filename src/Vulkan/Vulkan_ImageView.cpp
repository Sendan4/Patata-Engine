#include <iostream>

#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "Patata_Engine/Graphics/Vulkan_Renderer.hpp"
#include "Patata_Engine/Terminal_Colors.hpp"
#include "Patata_Engine/Log.hpp"

void Patata::Graphics::VulkanRenderer::CreateImageView(uint32_t &GraphicsQueueFamilyIndex) {
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
		std::cout << "  DepthImage For BindImageMemory -> Result :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n\n";
	else
		std::cout << "  DepthImage For BindImageMemory -> Result :\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n\n";

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

	std::cout << Bold << FindianRed1 << "  Creating SwapChainBuffer:\n" << Reset;
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
			std::cout << "SwapChainBuffer ImageView " << i << " :\t" << Reset << BLightGoldenRod1 << vk::to_string(Result) << Reset << "\n";
		else
			std::cout << "SwapChainBuffer ImageView " << i << ":\t" << Reset << Chartreuse1 << vk::to_string(Result) << Reset << "\n";

		SwapChainBuffers[i].Views[1] = ImageView;

		Device.destroyImageView(ImageView);

		//SwapChainBuffers[i].FrameBuffer = ;
	}
	std::cout << "\n";
}
