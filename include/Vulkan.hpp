#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>
#include <iostream>
#include <vector>

namespace Graphics {
	class Vulkan {
		public:
			void CreateInstance(SDL_Window *);
			void PhysicalDevices(void);
			uint32_t CreateQueue(void);
			void InitDevice(void);
			void CreateCommandBuffer(void);
			void CreateSurface(SDL_Window *);
			void CreateSwapChain();
			Vulkan(SDL_Window *);
			void Finish(void);
	
		private:
			unsigned int extensionCount = 0;
			uint32_t ComputeQueueFamilyIndex = 0;
			float QueuePriority = 0.0f;
			// Instance
			vk::Instance VulkanInstance = nullptr;
			// Extensiones
			const char * layer = {"VK_LAYER_KHRONOS_validation"};
			const char ** extensionsNames = nullptr;
			// Device
			vk::Device Device = nullptr;
			vk::PhysicalDevice PhysicalDevice = nullptr;
			vk::PhysicalDeviceProperties PhysicalDeviceProperties;
			// Queue
			std::vector<vk::QueueFamilyProperties> QueueFamilyProperties;
			// Command Buffer
			vk::CommandPool CommandPool = nullptr;
			vk::CommandBuffer CommandBuffer = nullptr;
			// SwapChain
			std::vector<vk::SurfaceFormatKHR> Formats;
			vk::Format Format;
			// Surface
			vk::SurfaceKHR Surface = nullptr;
	};
}
