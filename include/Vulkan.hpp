#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>
#include <iostream>
#include <vector>

namespace Graphics {
	class Vulkan {
		public:
			void CreateInstance(void);
			void PhysicalDevices(void);
			uint32_t CreateQueue(void);
			void InitDevice(void);
			void Finish(void);
	
		private:
			uint32_t extensionCount = 0;
			uint32_t ComputeQueueFamilyIndex = 0;
			float QueuePriority = 0.0f;
			// Instance
			vk::Instance VulkanInstance;
			const std::vector<const char*> Layers = { "VK_LAYER_KHRONOS_validation" };
			// Device
			vk::Device Device;
			vk::PhysicalDevice PhysicalDevice;
			vk::PhysicalDeviceProperties PhysicalDeviceProperties;
			// Queue
			std::vector<vk::QueueFamilyProperties> QueueFamilyProperties;
	};
}
