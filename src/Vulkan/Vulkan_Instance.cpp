#include <vector>
#include <SDL_vulkan.h>
#include <yaml-cpp/yaml.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "PatataEngine/Log.hpp"

bool Patata::Graphics::VulkanRenderer::CreateInstance(SDL_Window * WINDOW, YAML::Node CONFIG) {
	// Get Extensions
	unsigned int extensionInstanceCount = 0;

	SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr);

	std::vector<const char *> extensionInstanceNames(extensionInstanceCount);
	extensionInstanceNames.push_back("VK_KHR_get_physical_device_properties2");

	Patata::Log::ListVulkanInstanceExtensions(
		extensionInstanceNames,
		SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, extensionInstanceNames.data()));

	vk::ApplicationInfo PatataEngineInfo {};
	PatataEngineInfo.pApplicationName = PATATA_ENGINE_NAME;
	PatataEngineInfo.applicationVersion = 0;
	PatataEngineInfo.pEngineName = PATATA_ENGINE_NAME;
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
	
	vk::Result Result;
	try	{
		Result = vk::createInstance(&VulkanInstanceInfo, nullptr, &VulkanInstance);
		//throw(vk::Result::eErrorIncompatibleDriver);
	}
	catch (vk::Result & Error) {
		Patata::Log::FatalErrorMessage("Vulkan Error", vk::to_string(Error), CONFIG);
		throw("Vulkan Instance Fail");
	}

	return Patata::Log::VulkanInstanceResult(Result);
}
