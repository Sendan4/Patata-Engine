#include <iostream>
#include <iomanip>
#include <vector>

#include <windows.h>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

// Patata Engine
#include "Log.hpp"

void Patata::Log::ListVulkanInstanceExtensions(std::vector <const char *> &LIST, SDL_bool FOUND_EXTENSIONS) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (FOUND_EXTENSIONS) {
		SetConsoleTextAttribute(Terminal, 12);
		std::cout << "Vulkan Instance Extensions\n";
		SetConsoleTextAttribute(Terminal, 7);

		for (const auto &extension : LIST)
			std::cout << std::setw(10) << ' ' << extension << "\n";
		std::cout << "\n";
	}
	else {
		std::cout << "Error al obtener la lista de extensiones necesarias : " << SDL_GetError() << "\n";
	}
}

bool Patata::Log::VulkanInstanceResult(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (RESULT != vk::Result::eSuccess) {
		std::cout << "Instance" << std::setw(23) << ": ";

		SetConsoleTextAttribute(Terminal, 14);
		std::cout << vk::to_string(RESULT) << "\n\n";
		SetConsoleTextAttribute(Terminal, 7);

		return false;
	}
	else {
		std::cout << "Instance" << std::setw(23) << ": ";

		SetConsoleTextAttribute(Terminal, 10);
		std::cout << vk::to_string(RESULT) << "\n\n";
		SetConsoleTextAttribute(Terminal, 7);

		return true;
	}
}

void Patata::Log::ListVulkanDeviceResult(const std::vector <const char *> DEVICE_EXTENSIONS) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 12);
	std::cout << "Vulkan Device Extensions\n";
	SetConsoleTextAttribute(Terminal, 7);

	for (auto Extensions : DEVICE_EXTENSIONS)
		std::cout << std::setw(10) << ' ' << Extensions << "\n";
	std::cout << "\n";
}

void Patata::Log::VulkanLogicalDeviceResult(vk::Result RESULT) {	
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (RESULT != vk::Result::eSuccess) {
		std::cout << "Logical Device" << std::setw(17) << ": ";

		SetConsoleTextAttribute(Terminal, 14);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		std::cout << "Logical Device" << std::setw(17) << ": ";

		SetConsoleTextAttribute(Terminal, 10);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
}

void Patata::Log::CheckSurface(bool SURFACE) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "SDL Surface" << std::setw(20) << ": ";
	if (SURFACE) {
		SetConsoleTextAttribute(Terminal, 10);
		std::cout << "Yes\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		SetConsoleTextAttribute(Terminal, 14);
		std::cout << "No\n";
		std::cout << SDL_GetError() << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
}

void Patata::Log::CheckSwapChain(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (RESULT != vk::Result::eSuccess) {
		std::cout << "SwapChain" << std::setw(22) << ": ";

		SetConsoleTextAttribute(Terminal, 14);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		std::cout << "SwapChain" << std::setw(22) << ": ";

		SetConsoleTextAttribute(Terminal, 10);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
}

void Patata::Log::CheckCommandPool(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (RESULT != vk::Result::eSuccess) {
		std::cout << "CommandPool" << std::setw(20) << ": ";

		SetConsoleTextAttribute(Terminal, 14);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		std::cout << "CommandPool" << std::setw(20) << ": ";

		SetConsoleTextAttribute(Terminal, 10);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
}

void Patata::Log::CheckRenderPass(vk::Result RESULT) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (RESULT != vk::Result::eSuccess) {
		std::cout << "RenderPass" << std::setw(21) << ": ";

		SetConsoleTextAttribute(Terminal, 14);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		std::cout << "RenderPass" << std::setw(21) << ": ";

		SetConsoleTextAttribute(Terminal, 10);
		std::cout << vk::to_string(RESULT) << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
}
