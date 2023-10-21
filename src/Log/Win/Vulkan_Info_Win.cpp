#include <fast_io.h>
#include <cstring>
#include <tuple>

#include <yaml-cpp/yaml.h>
#include <windows.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"

void Patata::Graphics::VulkanRenderer::VulkanInfo(YAML::Node CONFIG, std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> SWAPCHAIN_INFO) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 12);
	fast_io::io::println(fast_io::out(), "\nVulkan Info :");
	SetConsoleTextAttribute(Terminal, 7);

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	{
		std::string Vendor;
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : Vendor = "Intel"; break;
			case 4098 : Vendor = "AMD (Advanced Micro Devices, Inc.)"; break;
			case 4318 : Vendor = "Nvidia (NVIDIA Corporation)"; break;
		}

		fast_io::io::print(fast_io::out(), "    Vendor                       : ");

		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 :
				SetConsoleTextAttribute(Terminal, 1);
				fast_io::io::println(fast_io::out(), Vendor);
				break;
			case 4098 :
				SetConsoleTextAttribute(Terminal, 12);
				fast_io::io::println(fast_io::out(), Vendor);
				break;
			case 4318 :
				SetConsoleTextAttribute(Terminal, 10);
				fast_io::io::println(fast_io::out(), Vendor);
				break;
		}
		SetConsoleTextAttribute(Terminal, 7);
	}

	fast_io::io::print(fast_io::out(), "    VendorID                     : ");
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	fast_io::io::println(fast_io::out(), "Hex[", fast_io::mnp::hex(PhysicalDeviceProperties.vendorID), "]  Dec[", PhysicalDeviceProperties.vendorID, "]");
	SetConsoleTextAttribute(Terminal, 7);

	fast_io::io::print(fast_io::out(), "    Device Type                  : ");
	
	fast_io::io::println(fast_io::out(), vk::to_string(PhysicalDeviceProperties.deviceType));

	fast_io::io::print(fast_io::out(), "    Device Name                  : ");
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	fast_io::io::println(fast_io::out(), std::string_view{ PhysicalDeviceProperties.deviceName });
	SetConsoleTextAttribute(Terminal, 7);

	fast_io::io::print(fast_io::out(), "    Vulkan Version               : ");
	{
		std::string vk_version = std::to_string(VK_VERSION_MAJOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_MINOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_PATCH(VulkanVersion)) + '.' + std::to_string(VK_API_VERSION_VARIANT(VulkanVersion));
		fast_io::io::println(fast_io::out(), vk_version);
	}

	fast_io::io::println(fast_io::out(), "    Driver Version               : ", PhysicalDeviceProperties.driverVersion);

	fast_io::io::print(fast_io::out(), "    Vsync                        : ");
	if ((std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox || std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo) && CONFIG["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, 10);
		fast_io::io::println(fast_io::out(), "Yes");
	}
	else if (std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate && !CONFIG["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, 14);
		fast_io::io::println(fast_io::out(), "No");
	}
	SetConsoleTextAttribute(Terminal, 7);

	fast_io::io::println(fast_io::out(), "    Present Mode                 : ", vk::to_string(std::get<0>(SWAPCHAIN_INFO)));
	fast_io::io::println(fast_io::out(), "    SwapChain Images             : ", SwapChainBuffers.size());
	fast_io::io::println(fast_io::out(), "    SwapChain Image Color Format : ", vk::to_string(std::get<1>(SWAPCHAIN_INFO)));
	fast_io::io::println(fast_io::out(), "    SwapChain Image Color Space  : ", vk::to_string(std::get<2>(SWAPCHAIN_INFO)));
	
	fast_io::io::print(fast_io::out(), "    Validation Layer             : ");
	#if defined(DEBUG)
		SetConsoleTextAttribute(Terminal, 10);
		fast_io::io::println(fast_io::out(), "Enabled");
	#else
		SetConsoleTextAttribute(Terminal, 14);
		fast_io::io::println(fast_io::out(), "Disabled");
	#endif
	SetConsoleTextAttribute(Terminal, 7);
	fast_io::io::println(fast_io::out(), "");
}
