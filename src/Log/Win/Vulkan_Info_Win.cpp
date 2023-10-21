#include <iomanip>
#include <ios>
#include <iostream>
#include <cstring>
#include <tuple>

#include <yaml-cpp/yaml.h>
#include <windows.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"

void Patata::Graphics::VulkanRenderer::VulkanInfo(YAML::Node CONFIG, std::tuple <vk::PresentModeKHR, vk::Format> SWAPCHAIN_INFO) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 12);
	std::cout << "\n" << "Vulkan Info" << std::setw(3) << ":\n";
	SetConsoleTextAttribute(Terminal, 7);

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	{
		std::string Vendor;
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 :
				SetConsoleTextAttribute(Terminal, 1);
				Vendor = "Intel";
				SetConsoleTextAttribute(Terminal, 7);
				break;
			case 4098 :
				SetConsoleTextAttribute(Terminal, FOREGROUND_RED);
				Vendor = "AMD (Advanced Micro Devices, Inc.)";
				SetConsoleTextAttribute(Terminal, 7);
				break;
			case 4318 :
				SetConsoleTextAttribute(Terminal, 10);
				Vendor = "Nvidia (NVIDIA Corporation)";
				SetConsoleTextAttribute(Terminal, 7);
				break;
		}

		std::cout << std::setw(4) << ' ' << "Vendor" << std::setw(25) << ": ";

		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 :
				SetConsoleTextAttribute(Terminal, 1);
				std::cout << Vendor << "\n";
				SetConsoleTextAttribute(Terminal, 7);
				break;
			case 4098 :
				SetConsoleTextAttribute(Terminal, 12);
				std::cout << Vendor << "\n";
				SetConsoleTextAttribute(Terminal, 7);
				break;
			case 4318 :
				SetConsoleTextAttribute(Terminal, 10);
				std::cout << Vendor << "\n";
				SetConsoleTextAttribute(Terminal, 7);
				break;
		}
	}

	std::cout << std::setw(4) << ' ' << "VendorID" << std::setw(23) << ": ";
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	std::cout << PhysicalDeviceProperties.vendorID << std::hex << std::showbase << "  " << PhysicalDeviceProperties.vendorID << std::dec << "\n";
	SetConsoleTextAttribute(Terminal, 7);

	std::cout << std::setw(4) << ' ' << "Device Name" << std::setw(20) << ": ";
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	std::cout << PhysicalDeviceProperties.deviceName << "\n";
	SetConsoleTextAttribute(Terminal, 7);

	std::cout << std::setw(4) << ' ' << "Device Type" << std::setw(20) << ": ";
	std::cout << vk::to_string(PhysicalDeviceProperties.deviceType) << "\n";

	std::cout << std::setw(4) << ' ' << "Vulkan Version" << std::setw(17) << ": ";
	{
		std::string vk_version = std::to_string(VK_VERSION_MAJOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_MINOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_PATCH(VulkanVersion)) + '.' + std::to_string(VK_API_VERSION_VARIANT(VulkanVersion));
		std::cout << vk_version << "\n";
	}

	std::cout << std::setw(4) << ' ' << "Driver Version" << std::setw(17) << ": " << PhysicalDeviceProperties.driverVersion << "\n";

	std::cout << std::setw(4) << ' ' << "Vsync" << std::setw(26) << ": ";
	if ((std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox || std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo) && CONFIG["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, 10);
		std::cout << "Yes" << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else if (std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate && !CONFIG["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, 14);
		std::cout << "No" << "\n";
		SetConsoleTextAttribute(Terminal, 7);
	}

	std::cout << std::setw(4) << ' ' << "Present Mode" << std::setw(19) << ": " << vk::to_string(std::get<0>(SWAPCHAIN_INFO)) << "\n";

	std::cout << std::setw(4) << ' ' << "SwapChain Images" << std::setw(15) << ": " << SwapChainBuffers.size() << "\n";
	std::cout << std::setw(4) << ' ' << "SwapChain Color Format" << std::setw(9) << ": " << vk::to_string(std::get<1>(SWAPCHAIN_INFO)) << "\n";

	std::cout << std::setw(4) << ' ' << "Validation Layer" << std::setw(15) << ": ";
	#if defined(DEBUG)
		SetConsoleTextAttribute(Terminal, 10);
		std::cout << "Enabled\n";
		SetConsoleTextAttribute(Terminal, 7);
	#else
		SetConsoleTextAttribute(Terminal, 14);
		std::cout << "Disabled\n";
		SetConsoleTextAttribute(Terminal, 7);
	#endif
	std::cout << "\n";
}
