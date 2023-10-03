#include <iostream>
#include <iomanip>
#include <vector>

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

// Patata Engine
#include "Log.hpp"
#include "Terminal_Colors.hpp"

void Patata::Log::ListVulkanInstanceExtensions(std::vector <const char *> &LIST, SDL_bool FOUND_EXTENSIONS) {
	if (FOUND_EXTENSIONS) {
		std::cout << FindianRed1 << Bold << "Vulkan Instance Extensions" << Reset << "\n";
		for (const auto &extension : LIST)
			std::cout << std::setw(10) << Dim << extension << Reset << "\n";
		std::cout << Reset << "\n";
	}
	else {
		std::cout << Bold << "  Error al obtener la lista de extensiones necesarias : " << Reset << SDL_GetError() << "\n";
	}
}

bool Patata::Log::VulkanInstanceResult(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess) {
		std::cout << Bold << "Instance" << std::setw(23) << ": " << Reset << BLightGoldenRod1 << vk::to_string(RESULT) << Reset << "\n\n";
		return false;
	}
	else {
		std::cout << Bold << "Instance" << std::setw(23) << ": " << Reset << Chartreuse1 << vk::to_string(RESULT) << Reset << "\n\n";
		return true;
	}
}

void Patata::Log::ListVulkanDeviceResult(const std::vector <const char *> DEVICE_EXTENSIONS) {
	std::cout << Bold << FindianRed1 << "Vulkan Device Extensions" << Reset << "\n";
	for (auto Extensions : DEVICE_EXTENSIONS)
		std::cout << std::setw(10) << Dim << Extensions << Reset << "\n";
	std::cout << "\n";
}

void Patata::Log::VulkanLogicalDeviceResult(vk::Result RESULT) {	
	if (RESULT != vk::Result::eSuccess) {
		std::cout << Bold << "Logical Device" << std::setw(17) << ": " << Reset << BLightGoldenRod1 << vk::to_string(RESULT) << Reset << "\n";
	}
	else std::cout << Bold << "Logical Device" << std::setw(17) << ": " << Reset << Chartreuse1 << vk::to_string(RESULT) << Reset << "\n";
}

void Patata::Log::CheckSurface(bool SURFACE) {
	std::cout << Bold << "SDL Surface" << std::setw(20) << ": " << Reset;
	if (SURFACE)
		std::cout << Chartreuse1 << "Yes\n" << Reset;
	else {
		std::cout << BLightGoldenRod1 << "No\n" << Reset;
		std::cout << SDL_GetError() << "\n";
	}
}

void Patata::Log::CheckSwapChain(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess)
		std::cout << Bold << "SwapChain" << std::setw(22) << ": " << Reset << BLightGoldenRod1 << vk::to_string(RESULT) << Reset << "\n";
	else
		std::cout << Bold << "SwapChain" << std::setw(22) << ": " << Reset << Chartreuse1 << vk::to_string(RESULT) << Reset << "\n";
}

void Patata::Log::CheckCommandPool(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess)
		std::cout << Bold << "CommandPool" << std::setw(20) << ": " << Reset << BLightGoldenRod1 << vk::to_string(RESULT) << Reset << "\n";
	else
		std::cout << Bold << "CommandPool" << std::setw(20) << ": " << Reset << Chartreuse1 << vk::to_string(RESULT) << Reset << "\n";
}

void Patata::Log::CheckRenderPass(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess)
		std::cout << Bold << "RenderPass" << std::setw(21) << ": " << Reset << BLightGoldenRod1 << vk::to_string(RESULT) << Reset << "\n";
	else
		std::cout << Bold << "RenderPass" << std::setw(21) << ": " << Reset << Chartreuse1 << vk::to_string(RESULT) << Reset << "\n";
}
