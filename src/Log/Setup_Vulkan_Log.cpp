#include <vector>

#include <fast_io.h>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

// Patata Engine
#include "PatataEngine/Log.hpp"
#include "PatataEngine/TerminalColors.hpp"

void Patata::Log::ListVulkanInstanceExtensions(std::vector <const char *> LIST, SDL_bool FOUND_EXTENSIONS) {
	if (FOUND_EXTENSIONS) {
		fast_io::io::println(FindianRed1, Bold, "Vulkan Instance Extensions", Reset);
		for (const char * &extension : LIST)
			fast_io::io::println(Dim, std::string_view{ extension }, Reset);
		fast_io::io::println(Reset);
	}
	else {
		fast_io::io::perrln("ERROR Fatal : ", std::string_view{ SDL_GetError() });
	}
}

bool Patata::Log::VulkanInstanceResult(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess) {
		fast_io::io::println(Bold, "Instance                       : ", Reset, BLightGoldenRod1, vk::to_string(RESULT), Reset, "\n");
		return false;
	}
	else {
		fast_io::io::println(Bold, "Instance                       : ", Reset, Chartreuse1, vk::to_string(RESULT), Reset, "\n");
		return true;
	}
}

void Patata::Log::ListVulkanDeviceResult(const std::vector <const char *> DEVICE_EXTENSIONS) {
	fast_io::io::println(Bold, FindianRed1, "Vulkan Device Extensions", Reset);
	for (const char * Extensions : DEVICE_EXTENSIONS)
		fast_io::io::println(Dim, std::string_view{ Extensions },  Reset);
	fast_io::io::println("");
}

void Patata::Log::VulkanLogicalDeviceResult(vk::Result RESULT) {	
	if (RESULT != vk::Result::eSuccess) {
		fast_io::io::println(Bold, "Logical Device                  : ", Reset, BLightGoldenRod1, vk::to_string(RESULT), Reset);
	}
	else fast_io::io::println(Bold, "Logical Device                 : ", Reset, Chartreuse1, vk::to_string(RESULT), Reset);
}

void Patata::Log::CheckSurface(bool SURFACE) {
	fast_io::io::print(Bold, "SDL Surface                    : ", Reset);
	if (SURFACE)
		fast_io::io::println(Chartreuse1, "Yes", Reset);
	else {
		fast_io::io::println(BLightGoldenRod1, "No", Reset);
		fast_io::io::println(Bold, CSalmon1, "ERROR Fatal : ", Reset, std::string_view{ SDL_GetError() });
	}
}

void Patata::Log::CheckSwapChain(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess)
		fast_io::io::println(Bold, "SwapChain                      : ", Reset, BLightGoldenRod1, vk::to_string(RESULT), Reset);
	else
		fast_io::io::println(Bold, "SwapChain                      : ", Reset, Chartreuse1, vk::to_string(RESULT), Reset);
} 

void Patata::Log::CheckCommandPool(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess)
		fast_io::io::println(Bold, "CommandPool                    : ", Reset, BLightGoldenRod1, vk::to_string(RESULT), Reset);
	else
		fast_io::io::println(Bold, "CommandPool                    : ", Reset, Chartreuse1, vk::to_string(RESULT), Reset);
}

void Patata::Log::CheckRenderPass(vk::Result RESULT) {
	if (RESULT != vk::Result::eSuccess)
		fast_io::io::println(Bold, "RenderPass                     : ", Reset, BLightGoldenRod1, vk::to_string(RESULT), Reset);
	else
		fast_io::io::println(Bold, "RenderPass                     : ", Reset, Chartreuse1, vk::to_string(RESULT), Reset);
}
