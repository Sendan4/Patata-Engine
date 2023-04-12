#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>
#include <iostream>
#include <vector>
#include "terminal_colors.hpp"

namespace Graphics {
	class VulkanRenderer {
		public:
			void CreateInstance(SDL_Window *);
			void PhysicalDevices(void);
			void InitDevice(void);
			uint32_t CreateQueue(void);
			void CreateSwapChain(void);
			void CreateImageView(void);
			void CreateCommandBuffer(void);
			void VulkanInfo(void);

			VulkanRenderer(SDL_Window *);
			~VulkanRenderer(void);

		private:
			const char * layer = {"VK_LAYER_KHRONOS_validation"};
			const std::vector <const char *> DeviceExtensions = {
				"VK_KHR_swapchain",
				"VK_EXT_multi_draw",
				"VK_KHR_maintenance4"};
			std::vector <vk::ExtensionProperties> ExtensionProperties;

			vk::Instance VulkanInstance = nullptr;
			vk::SurfaceKHR Surface = nullptr;

			vk::Device Device = nullptr;
			vk::PhysicalDevice PhysicalDevice = nullptr;
			vk::PhysicalDeviceProperties PhysicalDeviceProperties;

			uint32_t GraphicsQueueFamilyIndex = 0;
			float QueuePriority = 0.0f;

			std::vector <vk::QueueFamilyProperties> QueueFamilyProperties;

			vk::CommandPool CommandPool = nullptr;
			std::vector <vk::CommandBuffer> CommandBuffer;

			vk::Format Format;
			vk::SurfaceCapabilitiesKHR SurfaceCapabilities;
			vk::Extent2D SwapChainExtent;
			vk::PresentModeKHR PresentMode;
			vk::SurfaceFormatKHR SurfaceFormat;

			vk::SwapchainKHR SwapChain;
			vk::Image Image;
			vk::DeviceMemory ImageMemory;
			vk::ImageView ImageView;
			vk::DeviceMemory DeviceMemory;
	};
}
