#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>
#include <iostream>
#include <vector>

namespace Graphics {
	class VulkanRenderer {
		public:
			void CreateInstance(SDL_Window *);
			void PhysicalDevices(void);
			void CreateSurface(SDL_Window *);
			uint32_t CreateQueue(void);
			void InitDevice(void);
			void CreateCommandBuffer(void);
			void CreateSwapChain();

			VulkanRenderer(SDL_Window *);
			~VulkanRenderer(void);

			vk::Instance VulkanInstance = nullptr;
			vk::SurfaceKHR Surface = nullptr;
		private:
			uint32_t GraphicsQueueFamilyIndex = 0;
			float QueuePriority = 0.0f;
			// Instance
			// Extensiones
			const char * layer = {"VK_LAYER_KHRONOS_validation"};
			const std::vector <const char *> InstanceExtensions = {"VK_KHR_surface"};
			const std::vector <const char *> DeviceExtensions = {"VK_KHR_swapchain"};
			std::vector <vk::ExtensionProperties> ExtensionProperties;
			// Device
			vk::Device Device = nullptr;
			vk::PhysicalDevice PhysicalDevice = nullptr;
			vk::PhysicalDeviceProperties PhysicalDeviceProperties;
			// Queue
			std::vector<vk::QueueFamilyProperties> QueueFamilyProperties;
			// Command Buffer
			vk::CommandPool CommandPool = nullptr;
			vk::CommandBuffer CommandBuffer = nullptr;
			// Surface
			vk::SurfaceCapabilitiesKHR SurfaceCapabilities;
	};
}
