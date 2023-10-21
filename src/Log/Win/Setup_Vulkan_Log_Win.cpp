#include <vector>

#include <fast_io.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

// Patata Engine
#include "PatataEngine/Log.hpp"

void Patata::Log::ListVulkanInstanceExtensions(std::vector <const char *> LIST, SDL_bool FOUND_EXTENSIONS) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (FOUND_EXTENSIONS) {
		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::println(fast_io::out(), "Vulkan Instance Extensions");
		SetConsoleTextAttribute(Terminal, 7);

		for (const char * &extension : LIST)
			fast_io::io::println(fast_io::out(), std::string_view{ extension });
		fast_io::io::println(fast_io::out());
	}	
}

bool Patata::Log::VulkanInstanceResult(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	fast_io::io::print(fast_io::out(), "Instance                       : ");
	if (RESULT != vk::Result::eSuccess) {
		SetConsoleTextAttribute(Terminal, 14);
		fast_io::io::println(fast_io::out(), vk::to_string(RESULT), "\n");
		SetConsoleTextAttribute(Terminal, 7);
		return false;
	}
	else
		SetConsoleTextAttribute(Terminal, 10);

	fast_io::io::println(fast_io::out(), vk::to_string(RESULT), "\n");
	SetConsoleTextAttribute(Terminal, 7);
	return true;
}

void Patata::Log::ListVulkanDeviceResult(const std::vector <const char *> DEVICE_EXTENSIONS) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 12);
	fast_io::io::println(fast_io::out(), "Vulkan Device Extensions");
	SetConsoleTextAttribute(Terminal, 7);

	for (const char * Extensions : DEVICE_EXTENSIONS)
		fast_io::io::println(fast_io::out(), std::string_view{ Extensions });
	fast_io::io::println(fast_io::out());
}

void Patata::Log::VulkanLogicalDeviceResult(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	fast_io::io::print(fast_io::out(), "Logical Device                 : ");

	if (RESULT != vk::Result::eSuccess)
		SetConsoleTextAttribute(Terminal, 14);
	else
		SetConsoleTextAttribute(Terminal, 10);

	fast_io::io::println(fast_io::out(), vk::to_string(RESULT));
	SetConsoleTextAttribute(Terminal, 7);
}

void Patata::Log::CheckSurface(bool SURFACE) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	fast_io::io::print(fast_io::out(), "SDL Surface                    : ");
	if (SURFACE) {
		SetConsoleTextAttribute(Terminal, 10);
		fast_io::io::println(fast_io::out(), "Yes");
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		SetConsoleTextAttribute(Terminal, 14);
		fast_io::io::println(fast_io::out(), "No");
		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::println(fast_io::out(), "ERROR : ");
		SetConsoleTextAttribute(Terminal, 7);
		fast_io::io::println(std::string_view{ SDL_GetError() });
	}
}

void Patata::Log::CheckSwapChain(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	fast_io::io::print(fast_io::out(), "SwapChain                      : ");

	if (RESULT != vk::Result::eSuccess)
		SetConsoleTextAttribute(Terminal, 14);
	else
		SetConsoleTextAttribute(Terminal, 10);

	fast_io::io::println(fast_io::out(), vk::to_string(RESULT));
	SetConsoleTextAttribute(Terminal, 7);
} 

void Patata::Log::CheckCommandPool(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	fast_io::io::print(fast_io::out(), "CommandPool                    : ");

	if (RESULT != vk::Result::eSuccess)
		SetConsoleTextAttribute(Terminal, 14);
	else
		SetConsoleTextAttribute(Terminal, 10);

	fast_io::io::println(fast_io::out(), vk::to_string(RESULT));
	SetConsoleTextAttribute(Terminal, 7);
}

void Patata::Log::CheckRenderPass(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	
	fast_io::io::print(fast_io::out(), "RenderPass                     : ");

	if (RESULT != vk::Result::eSuccess)
		SetConsoleTextAttribute(Terminal, 14);
	else
		SetConsoleTextAttribute(Terminal, 10);

	fast_io::io::println(fast_io::out(), vk::to_string(RESULT));
	SetConsoleTextAttribute(Terminal, 7);
}
