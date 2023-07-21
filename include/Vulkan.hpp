#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>
#include <iostream>
#include <vector>
#include <array>

#include "terminal_colors.hpp"

namespace Graphics {
	class VulkanRenderer {
		public:
			bool CreateInstance(SDL_Window *);
			uint32_t CreateLogicalDeviceAndCreateQueue(void);
			void CreateSwapChain(uint32_t &);
			void CreateImageView(uint32_t &);
			void CreateCommandBuffer(uint32_t &);
			void CreateRenderPass(void);
			void CreatePipeline(void);
			void VulkanInfo(void);
			void TestColor(void);

			VulkanRenderer(SDL_Window *);
			~VulkanRenderer(void);

		private:
			vk::Instance VulkanInstance = nullptr;
			vk::SurfaceKHR Surface = nullptr;

			vk::Queue Queue;
			vk::Device Device = nullptr;
			vk::PhysicalDevice PhysicalDevice = nullptr;

			vk::CommandPool CommandPool = nullptr;
			std::vector <vk::CommandBuffer> CommandBuffers;

			vk::Format ColorFormat;
			vk::SurfaceCapabilitiesKHR SurfaceCapabilities;
			vk::Extent2D SwapChainExtent;
			vk::PresentModeKHR PresentMode;
			vk::SurfaceFormatKHR SurfaceFormat;

			vk::Image DepthImage;

			vk::SwapchainKHR SwapChain;
			struct SwapChainBuffer {
				vk::Image Image;
				std::array <vk::ImageView, 2> Views;
				vk::Framebuffer FrameBuffer;
			};
			std::vector <SwapChainBuffer> SwapChainBuffers;

			std::vector <vk::Image> SwapChainImages;
			vk::ImageView ImageView;
			vk::DeviceMemory ImageMemory;

			vk::RenderPass RenderPass;
			vk::Semaphore Semaphore;
			vk::Semaphore RenderCompleteSemaphore;

			vk::Pipeline PipeLine;
			vk::PipelineLayout PipeLineLayout;
			vk::PipelineCache PipeLineCache;			
	};
}
