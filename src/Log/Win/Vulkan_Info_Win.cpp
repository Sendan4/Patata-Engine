#include <cstring>
#include <tuple>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <yaml-cpp/yaml.h>
#include <windows.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"

void Patata::Graphics::VulkanRenderer::VulkanInfo(YAML::Node CONFIG, std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> SWAPCHAIN_INFO) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 12);
	fast_io::io::print(fast_io::out(), "\nVulkan ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::println(fast_io::out(), "INFO :");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	// Vulkan Vendor String
	{
		std::string Vendor;
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : Vendor = "Intel"; break;
			case 4098 : Vendor = "AMD (Advanced Micro Devices, Inc.)"; break;
			case 4318 : Vendor = "Nvidia (NVIDIA Corporation)"; break;
		}

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(PhysicalDeviceProperties).name() }, "]");
	#endif

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), " Vendor : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

	// Vulkan Hardware Vendor
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties.vendorID).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(PhysicalDeviceProperties.vendorID).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " VendorID : ");
	// Hexadecimal VendorID
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "[Hex]");
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	fast_io::io::print(fast_io::out(), " ", fast_io::mnp::hex(PhysicalDeviceProperties.vendorID), " ");
	// Decimal VendorID
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "[Dec]");
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	fast_io::io::println(fast_io::out(), " ", PhysicalDeviceProperties.vendorID);

	// Device Type
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(PhysicalDeviceProperties).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Type : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), vk::to_string(PhysicalDeviceProperties.deviceType));

	// Device Name | GPU Vendor
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(PhysicalDeviceProperties).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Name : ");
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : SetConsoleTextAttribute(Terminal, 1); break;
		case 4098 : SetConsoleTextAttribute(Terminal, 12); break;
		case 4318 : SetConsoleTextAttribute(Terminal, 10); break;
	}
	fast_io::io::println(fast_io::out(), std::string_view{ PhysicalDeviceProperties.deviceName });
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	// Vulkan Loader Version
	#if defined(PATATA_VULKAN_LOADER_VERSION)
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Loader Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_VULKAN_LOADER_VERSION);
	#endif

	// Vulkan Version
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties.apiVersion).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(PhysicalDeviceProperties.apiVersion).name() }, "]");
	#endif

	{
		std::string vk_version = std::to_string(VK_VERSION_MAJOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_MINOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_PATCH(VulkanVersion)) + '.' + std::to_string(VK_API_VERSION_VARIANT(VulkanVersion));

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), " Vulkan Version : ");

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::println(fast_io::out(), vk_version);
	}

	// Driver Version
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties.driverVersion).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(PhysicalDeviceProperties.driverVersion).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Driver Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), VK_VERSION_MAJOR(PhysicalDeviceProperties.driverVersion), ".", VK_VERSION_MINOR(PhysicalDeviceProperties.driverVersion), ".", VK_VERSION_PATCH(PhysicalDeviceProperties.driverVersion), ".", VK_API_VERSION_VARIANT(PhysicalDeviceProperties.driverVersion));

	// Vsync
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(CONFIG).name(), nullptr, nullptr, nullptr) }, " && ", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(CONFIG).name() }, " && ", std::string_view{ typeid(SwapChain).name() },"]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Vsync : ");
	if ((std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox || std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo) && CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fast_io::io::println(fast_io::out(), "Yes");
	}
	else if (std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate && !CONFIG["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fast_io::io::println(fast_io::out(), "No");
	}

	// SwapChain Present Mode
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, " -> ", std::string_view{ abi::__cxa_demangle(typeid(std::get<0>(SWAPCHAIN_INFO)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(SwapChain).name() }, " <- ", std::string_view{ typeid(std::get<0>(SWAPCHAIN_INFO)).name() },"]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Present Mode : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), vk::to_string(std::get<0>(SWAPCHAIN_INFO)));

	// SwapChain Images
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(SwapChain).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Images : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), SwapChainBuffers.size());

	// SwapChain Image Color Format
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, " -> ", std::string_view{ abi::__cxa_demangle(typeid(std::get<1>(SWAPCHAIN_INFO)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(SwapChain).name() }, " <- ", std::string_view{ typeid(std::get<1>(SWAPCHAIN_INFO)).name() },"]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Image Color Format : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), vk::to_string(std::get<1>(SWAPCHAIN_INFO)));

	// SwapChain Image Color Space
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, " -> ", std::string_view{ abi::__cxa_demangle(typeid(std::get<2>(SWAPCHAIN_INFO)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(SwapChain).name() }, " <- ", std::string_view{ typeid(std::get<2>(SWAPCHAIN_INFO)).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Image Color Space : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), vk::to_string(std::get<2>(SWAPCHAIN_INFO)));

	// Vulkan Validation Layer
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Validation Layer : ");
	#if defined(DEBUG)
		SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fast_io::io::println(fast_io::out(), "Enabled");
	#else
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fast_io::io::println(fast_io::out(), "Disabled");
	#endif
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	// ImGUI Version
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  [ImGUI]");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_IMGUI_VERSION);

	fast_io::io::println(fast_io::out(), "");
}
