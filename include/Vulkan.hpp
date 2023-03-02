#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>
#include <vector>

namespace Graphics {
	class Vulkan {
		public:
			void CreateInstance(void);
			void EnumeratePhysicalDevices(void);
			void InitDevice(void);
			void Finish(void);
	
		private:
			uint32_t extensionCount = 0;
			// Instance
			vk::Instance VulkanInstance;
			// Physical Device
			vk::PhysicalDevice PhysicalDevice;
			vk::PhysicalDeviceProperties PhysicalDeviceProperties;
			// Queue
			std::vector<vk::QueueFamilyProperties> QueueFamilyProperties;
			vk::DeviceQueueCreateInfo DeviceQueueCreateInfo;
			vk::Device Device;
	};
}
