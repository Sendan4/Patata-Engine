#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>

#include <SDL_vulkan.h>
#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "Log.hpp"

#if defined(_WIN64)
#include <windows.h>
#else
#include "TerminalColors.hpp"
#endif

#include "ExitLog.hpp"

#ifndef PATATA_GAME_NAME
#define PATATA_GAME_NAME "Unknown"
#endif
#ifndef PATATA_GAME_VERSION_MAYOR
#define PATATA_GAME_VERSION_MAYOR 0
#endif
#ifndef PATATA_GAME_VERSION_MINOR
#define PATATA_GAME_VERSION_MINOR 0
#endif
#ifndef PATATA_GAME_VERSION_PATCH
#define PATATA_GAME_VERSION_PATCH 0
#endif

bool Patata::Graphics::VulkanRenderer::CreateInstance(SDL_Window *& WINDOW, YAML::Node CONFIG) {
	// Get Extensions
	uint32_t extensionInstanceCount = 0;

	SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, nullptr);
	//extensionInstanceCount++;

	const char ** pExtensionInstanceNames = new const char * [extensionInstanceCount];

	bool found_extensions = static_cast<bool>(SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount, pExtensionInstanceNames));

	Patata::Log::VulkanList(pExtensionInstanceNames, extensionInstanceCount - 1, found_extensions, "Instance Extensions");

	vk::ApplicationInfo PatataEngineInfo(PATATA_GAME_NAME, VK_MAKE_VERSION(PATATA_GAME_VERSION_MAYOR, PATATA_GAME_VERSION_MINOR, PATATA_GAME_VERSION_PATCH),
										PATATA_ENGINE_NAME, VK_MAKE_VERSION(PATATA_ENGINE_VERSION_MAYOR, PATATA_ENGINE_VERSION_MINOR, PATATA_ENGINE_VERSION_PATCH),
										VK_API_VERSION_1_3);

	#if defined(DEBUG)
	const char * layer = { "VK_LAYER_KHRONOS_validation" };
	#endif

	vk::InstanceCreateInfo InstanceInfo = vk::InstanceCreateInfo()
		.setPApplicationInfo(&PatataEngineInfo)
		#if defined(DEBUG)
		.setEnabledLayerCount(1)
		.setPpEnabledLayerNames(&layer)
		#endif
		.setEnabledExtensionCount(extensionInstanceCount)
		.setPpEnabledExtensionNames(pExtensionInstanceNames);

	vk::Result Result;
	try	{
		// Posible Error
		Result = vk::createInstance(&InstanceInfo, nullptr, &Instance);
		//throw(vk::Result::eErrorIncompatibleDriver);
		Patata::Log::VulkanCheck("Instance", Result);
	}
	catch (vk::Result & Error) {
		Patata::Log::FatalErrorMessage("Vulkan Error", vk::to_string(Error), CONFIG);
		throw("Vulkan Instance Fail");
	}

	Patata::Log::DeleteAndLogArrPtr("Instance Extensions", pExtensionInstanceNames);

	return true; 
}
