#pragma once
#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace Graphics {
	class Vulkan {
		public:
			void CreateInstance(void);
	
		private:
			uint32_t extensionCount = 0;
			vk::Instance VulkanInstance;
	};
}
