#include <iomanip>
#include <ios>
#include <iostream>
#include <cstring>
#include <tuple>

#include <yaml-cpp/yaml.h>

#include "Patata_Engine/Graphics/Vulkan_Renderer.hpp"
#include "Patata_Engine/Terminal_Colors.hpp"

void Patata::Graphics::VulkanRenderer::VulkanInfo(YAML::Node CONFIG, std::tuple <vk::PresentModeKHR, vk::Format> SWAPCHAIN_INFO) {
	std::cout << "\n" << FindianRed1 << Bold << "Vulkan Info" << std::setw(3) << ":\n" << Reset;

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	{
		std::string Vendor;
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : std::cout << FSteelBlue1; Vendor = "Intel"; break;
			case 4098 : std::cout << FindianRed1; Vendor = "AMD (Advanced Micro Devices, Inc.)"; break;
			case 4318 : std::cout << Chartreuse1; Vendor = "Nvidia (NVIDIA Corporation)"; break;
		}

		std::cout << Reset << Bold << std::setw(4) << ' ' << "Vendor" << std::setw(25) << ": " << Reset;

		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : std::cout << FSteelBlue1 << Vendor << Reset << "\n"; break;
			case 4098 : std::cout << FindianRed1 << Vendor << Reset << "\n"; break;
			case 4318 : std::cout << Chartreuse1 << Vendor << Reset << "\n"; break;
		}
	}

	std::cout << Bold << std::setw(4) << ' ' << "VendorID" << std::setw(23) << ": " << Reset;
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : std::cout << FSteelBlue1; break;
		case 4098 : std::cout << FindianRed1; break;
		case 4318 : std::cout << Chartreuse1; break;
	}
	std::cout << Dim << PhysicalDeviceProperties.vendorID << std::hex << std::showbase << "  " << PhysicalDeviceProperties.vendorID << Reset << std::dec << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "Device Name" << std::setw(20) << ": " << Reset;
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : std::cout << FSteelBlue1; break;
		case 4098 : std::cout << FindianRed1; break;
		case 4318 : std::cout << Chartreuse1; break;
	}
	std::cout << PhysicalDeviceProperties.deviceName << Reset << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "Device Type" << std::setw(20) << ": " << Reset;
	std::cout << vk::to_string(PhysicalDeviceProperties.deviceType) << Reset << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "Vulkan Version" << std::setw(17) << ": " << Reset;
	{
		std::string vk_version = std::to_string(VK_VERSION_MAJOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_MINOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_PATCH(VulkanVersion)) + '.' + std::to_string(VK_API_VERSION_VARIANT(VulkanVersion));
		std::cout << vk_version << Reset << "\n";
	}

	std::cout << Bold << std::setw(4) << ' ' << "Driver Version" << std::setw(17) << ": " << Reset << PhysicalDeviceProperties.driverVersion << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "Vsync" << std::setw(26) << ": ";
	if ((std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox || std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo) && CONFIG["vsync"].as<bool>())
		std::cout << Reset << Chartreuse1 << "Yes" << Reset << "\n";
	else if (std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate && !CONFIG["vsync"].as<bool>())
		std::cout << Reset << BLightGoldenRod1 << "No" << Reset << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "Present Mode" << Reset << std::setw(19) << ": " << vk::to_string(std::get<0>(SWAPCHAIN_INFO)) << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "SwapChain Images" << std::setw(15) << ": " << Reset << SwapChainBuffers.size() + 1 << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "SwapChain Color Format" << std::setw(9) << ": " << Reset << vk::to_string(std::get<1>(SWAPCHAIN_INFO)) << "\n";

	#if defined(DEBUG)
		std::cout << Bold << std::setw(4) << ' ' << "Validation Layer" << std::setw(15) << ": " << Reset << Chartreuse1 << "Enabled\n" << Reset;
	#else
		std::cout << Bold << std::setw(4) << ' ' << "Validation Layer" << std::setw(15) << ": " << Reset << BLightGoldenRod1 << "Disabled\n" << Reset;
	#endif
	std::cout << "\n";
}
