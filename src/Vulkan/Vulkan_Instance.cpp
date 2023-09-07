#include <vector>
#include <SDL_vulkan.h>

#include "Patata_Engine/Graphics/Vulkan_Renderer.hpp"
#include "Patata_Engine/Log.hpp"

bool Patata::Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW) {
	// Get Extensions
	unsigned int extensionInstanceCount = 0;

	SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr);

	std::vector<const char *> extensionInstanceNames(extensionInstanceCount);
	extensionInstanceNames.push_back("VK_KHR_get_physical_device_properties2");

	Patata::Log::ListVulkanInstanceExtensions(
		extensionInstanceNames,
		SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, extensionInstanceNames.data()));

	vk::ApplicationInfo PatataEngineInfo {};
	PatataEngineInfo.pApplicationName = "Patata Engine";
	PatataEngineInfo.applicationVersion = 0;
	PatataEngineInfo.pEngineName = "Patata Engine";
	PatataEngineInfo.engineVersion = 0;
	PatataEngineInfo.apiVersion = VK_API_VERSION_1_3;

	#if defined(DEBUG)
		const char * layer = {"VK_LAYER_KHRONOS_validation"};
	#endif

	vk::InstanceCreateInfo VulkanInstanceInfo {};
	#if defined(DEBUG)
		VulkanInstanceInfo.enabledLayerCount = 1;
		VulkanInstanceInfo.ppEnabledLayerNames = &layer;
	#endif
	VulkanInstanceInfo.pApplicationInfo = &PatataEngineInfo;
	VulkanInstanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensionInstanceCount);
	VulkanInstanceInfo.ppEnabledExtensionNames = extensionInstanceNames.data();
	
	vk::Result Result = vk::createInstance(&VulkanInstanceInfo, nullptr, &VulkanInstance);

	return Patata::Log::VulkanInstanceResult(Result);
}
