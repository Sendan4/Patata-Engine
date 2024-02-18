#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif

#include <fast_io.h>

#include "PatataEngine/Graphics/RaccoonRenderer.hpp"
#include "Log.hpp"

#include <SDL_vulkan.h>

#if defined(_WIN64)
#include <windows.h>
#endif

#include "TerminalColors.hpp"
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

#define PATATA_GAME_VERSION VK_MAKE_VERSION(PATATA_GAME_VERSION_MAYOR, PATATA_GAME_VERSION_MINOR, PATATA_GAME_VERSION_PATCH)
#define PATATA_ENGINE_VERSION_VK VK_MAKE_VERSION(PATATA_ENGINE_VERSION_MAYOR, PATATA_ENGINE_VERSION_MINOR, PATATA_ENGINE_VERSION_PATCH)

bool Patata::Graphics::RaccoonRenderer::VulkanBackend::CreateInstance(SDL_Window *& WINDOW, YAML::Node & CONFIG) {
	vk::ApplicationInfo PatataEngineInfo(
		PATATA_GAME_NAME, PATATA_GAME_VERSION,
		PATATA_ENGINE_NAME, PATATA_ENGINE_VERSION_VK,
		VK_API_VERSION_1_3);

	// Layers
	#if defined(DEBUG)
	const char * layer { "VK_LAYER_KHRONOS_validation" };
	Patata::Log::VulkanList(&layer, 0, true, "Layers");
	#endif

	// Get Extensions 
	// Array -> 2 debe ser iniciado desde aqui para indicar la cantidad de extensiones a usar
	// Array -> 1 SDL Extensions // Array -> 2 My extensions
	// Por alguna razon, aqui hay que comenzar a contar desde 1 cuando se inicia un array con valores, eso es raro.
	// mas abajo se comienza a contar desde 0, como tiene que ser.
	uint32_t extensionInstanceCount[2] { 0, 1 };

	// SDL por alguna razon develve un numero extra en el conteo de extensiones
	SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount[0], nullptr);

	extensionInstanceCount[1] += extensionInstanceCount[0];

	const char ** pExtensionInstanceNames = new const char * [extensionInstanceCount[1]];

	bool found_extensions = SDL_Vulkan_GetInstanceExtensions(WINDOW, &extensionInstanceCount[0], pExtensionInstanceNames);

	// Desde aqui se deben agregar las otras extensiones, desde el conteo que devuelve SDL en adelante
	pExtensionInstanceNames[extensionInstanceCount[0]] = "VK_KHR_get_physical_device_properties2";

	Patata::Log::VulkanList(pExtensionInstanceNames, extensionInstanceCount[1] - 1, found_extensions, "Instance Extensions");

	// Create Instance
	vk::InstanceCreateInfo InstanceInfo({}, &PatataEngineInfo,
		#if defined(DEBUG)
		1, &layer,
		#else
		0, nullptr,
		#endif
		extensionInstanceCount[1], pExtensionInstanceNames);


	vk::Result Result;
	try	{
		Result = vk::createInstance(&InstanceInfo, nullptr, &Instance);
		Patata::Log::VulkanCheck("Instance", Result);
	}
	catch (const vk::Result & Error) {
		Patata::Log::FatalErrorMessage("Vulkan Error", vk::to_string(Error), CONFIG);
		return false;
	}

	Patata::Log::DeleteAndLogArrPtr("Instance Extensions", pExtensionInstanceNames);

	#if defined(_WIN64)
	fast_io::io::println(fast_io::out());
	#else
	fast_io::io::println("");
	#endif

	return true; 
}
