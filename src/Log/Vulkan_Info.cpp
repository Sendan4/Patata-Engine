#include <cstring>
#include <tuple>

#include <fast_io.h>
#include <yaml-cpp/yaml.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "PatataEngine/TerminalColors.hpp"

void Patata::Graphics::VulkanRenderer::VulkanInfo(YAML::Node CONFIG, std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> SWAPCHAIN_INFO) {
	fast_io::io::println("\n", FindianRed1, Bold, "Vulkan Info :", Reset);

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	// Vendor
	{
		std::string Vendor;
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : Vendor = "Intel"; break;
			case 4098 : Vendor = "AMD (Advanced Micro Devices, Inc.)"; break;
			case 4318 : Vendor = "Nvidia (NVIDIA Corporation)"; break;
		}

		fast_io::io::print(Bold, "    Vendor                       : ", Reset);

		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : fast_io::io::println(FSteelBlue1, Vendor, Reset); break;
			case 4098 : fast_io::io::println(FindianRed1, Vendor, Reset); break;
			case 4318 : fast_io::io::println(Chartreuse1, Vendor, Reset); break;
		}
	}

	fast_io::io::print(Bold, "    VendorID                     : ", Reset);
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : fast_io::io::print(FSteelBlue1); break;
		case 4098 : fast_io::io::print(FindianRed1); break;
		case 4318 : fast_io::io::print(Chartreuse1); break;
	}
	fast_io::io::println(Dim, PhysicalDeviceProperties.vendorID, "  ", PhysicalDeviceProperties.vendorID, Reset);

	fast_io::io::print(Bold, "    Device Name                  : ", Reset);
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : fast_io::io::print(FSteelBlue1); break;
		case 4098 : fast_io::io::print(FindianRed1); break;
		case 4318 : fast_io::io::print(Chartreuse1); break;
	}
	fast_io::io::println(std::string_view{ PhysicalDeviceProperties.deviceName }, Reset);

	fast_io::io::print(Bold, "    Device Type                  : ", Reset);
	fast_io::io::println(vk::to_string(PhysicalDeviceProperties.deviceType), Reset);

	fast_io::io::print(Bold, "    Vulkan Version               : ", Reset);
	{
		std::string vk_version = std::to_string(VK_VERSION_MAJOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_MINOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_PATCH(VulkanVersion)) + '.' + std::to_string(VK_API_VERSION_VARIANT(VulkanVersion));
		fast_io::io::println(vk_version);
	}

	fast_io::io::println(Bold, "    Driver Version               : ", Reset, PhysicalDeviceProperties.driverVersion);

	fast_io::io::print(Bold, "    Vsync                        : ");
	if ((std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox || std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo) && CONFIG["vsync"].as<bool>())
		fast_io::io::println(Reset, Chartreuse1, "Yes", Reset);
	else if (std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate && !CONFIG["vsync"].as<bool>())
		fast_io::io::println(Reset, BLightGoldenRod1, "No", Reset);

	fast_io::io::println(Bold, "    Present Mode                 : ", Reset, vk::to_string(std::get<0>(SWAPCHAIN_INFO)));

	fast_io::io::println(Bold, "    SwapChain Images             : ", Reset, SwapChainBuffers.size());
	fast_io::io::println(Bold, "    SwapChain Image Color Format : ", Reset, vk::to_string(std::get<1>(SWAPCHAIN_INFO)));
	fast_io::io::println(Bold, "    SwapChain Image Color Space  : ", Reset, vk::to_string(std::get<2>(SWAPCHAIN_INFO)));

	#if defined(DEBUG)
		fast_io::io::println(Bold, "    Validation Layer             : ", Reset, Chartreuse1, "Enabled", Reset);
	#else
		fast_io::io::println(Bold, "    Validation Layer             : ", Reset, BLightGoldenRod1, "Disabled", Reset);
	#endif
		fast_io::io::println("");
}
