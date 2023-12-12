#include <cstring>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "TerminalColors.hpp"

void Patata::Graphics::VulkanRenderer::VulkanInfo(YAML::Node CONFIG, std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> SWAPCHAIN_INFO) {
	fast_io::io::println("\n", FindianRed1, Bold, "Vulkan ", Reset, Bold, "INFO", Reset);

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

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(PhysicalDeviceProperties).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Vendor : ", Reset);

		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : fast_io::io::println(FSteelBlue1, Vendor, Reset); break;
			case 4098 : fast_io::io::println(FindianRed1, Vendor, Reset); break;
			case 4318 : fast_io::io::println(Chartreuse1, Vendor, Reset); break;
		}
	}
	
	// Vulkan Hardware Vendor
	{
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(PhysicalDeviceProperties.vendorID).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " VendorID : ", Reset);

		// Hexadecimal VendorID
		fast_io::io::print(Dim, CGREY66, "[Hex] ", Reset);
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : fast_io::io::print(FSteelBlue1); break;
			case 4098 : fast_io::io::print(FindianRed1); break;
			case 4318 : fast_io::io::print(Chartreuse1); break;
		}
		fast_io::io::print(fast_io::mnp::hex(PhysicalDeviceProperties.vendorID), Reset,  " ");

		// Decimal VendorID
		fast_io::io::print(Dim, CGREY66, "[Dec] ", Reset);
		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : fast_io::io::print(FSteelBlue1); break;
			case 4098 : fast_io::io::print(FindianRed1); break;
			case 4318 : fast_io::io::print(Chartreuse1); break;
		}
		fast_io::io::println(PhysicalDeviceProperties.vendorID);
	}

	// Device Type
	{
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(PhysicalDeviceProperties).name() }, "]", Reset);
		#endif

		fast_io::io::println(Bold, " Type : ", Reset, vk::to_string(PhysicalDeviceProperties.deviceType), Reset);
	}

	// Device Name | GPU Vendor
	{		
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(PhysicalDeviceProperties).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Name : ", Reset);

		switch (PhysicalDeviceProperties.vendorID) {
			case 32902 : fast_io::io::print(FSteelBlue1); break;
			case 4098 : fast_io::io::print(FindianRed1); break;
			case 4318 : fast_io::io::print(Chartreuse1); break;
		}
		fast_io::io::println(std::string_view{ PhysicalDeviceProperties.deviceName }, Reset);
	}

	// Vulkan Loader Version
	#if defined(PATATA_VULKAN_LOADER_VERSION)
	fast_io::io::println(Bold, "  Loader Version : ", Reset, PATATA_VULKAN_LOADER_VERSION);
	#endif

	// Vulkan Version
	{
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties.apiVersion).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(PhysicalDeviceProperties.apiVersion).name() }, "]", Reset);
		#endif
			
		fast_io::io::print(Bold, " Vulkan Version : ", Reset);

		std::string vk_version = std::to_string(VK_VERSION_MAJOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_MINOR(VulkanVersion)) + '.' + std::to_string(VK_VERSION_PATCH(VulkanVersion)) + '.' + std::to_string(VK_API_VERSION_VARIANT(VulkanVersion));
		fast_io::io::println(vk_version);
	}

	/*
	// Vulkan Driver Name
	{
	}
	*/

	// Driver Version
	{
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(PhysicalDeviceProperties.driverVersion).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(PhysicalDeviceProperties.driverVersion).name() }, "]", Reset);
		#endif

		fast_io::io::println(Bold, " Driver Version : ", Reset, VK_VERSION_MAJOR(PhysicalDeviceProperties.driverVersion), ".", VK_VERSION_MINOR(PhysicalDeviceProperties.driverVersion), ".", VK_VERSION_PATCH(PhysicalDeviceProperties.driverVersion), ".", VK_API_VERSION_VARIANT(PhysicalDeviceProperties.driverVersion));
	}

	// Vulkan Version
	{
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(CONFIG).name(), nullptr, nullptr, nullptr) }, " && ", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(CONFIG).name() }, " && ", std::string_view{ typeid(SwapChain).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Vsync : ");

		if ((std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox || std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo) && CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>())
			fast_io::io::println(Reset, Chartreuse1, "Yes", Reset);
		else if (std::get<0>(SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate && !CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>())
			fast_io::io::println(Reset, BLightGoldenRod1, "No", Reset);
	}

	// SwapChain Present Mode
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, " -> ", std::string_view{ abi::__cxa_demangle(typeid(std::get<0>(SWAPCHAIN_INFO)).name(), nullptr, nullptr, nullptr) }, "]", Reset);
	#else
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(SwapChain).name() }, " <- ", std::string_view{ typeid(std::get<0>(SWAPCHAIN_INFO)).name() }, "]", Reset);
	#endif
	fast_io::io::println(Bold, " Present Mode : ", Reset, vk::to_string(std::get<0>(SWAPCHAIN_INFO)));

	// SwapChain Images
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, "]", Reset);
	#else
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(SwapChain).name() }, "]", Reset);
	#endif
	fast_io::io::println(Bold, " Images : ", Reset, SwapChainBuffers.size());

	// SwapChain Image Color Format
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, " -> ", std::string_view{ abi::__cxa_demangle(typeid(std::get<1>(SWAPCHAIN_INFO)).name(), nullptr, nullptr, nullptr) }, "]", Reset);
	#else
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(SwapChain).name() }, " <- ", std::string_view{ typeid(std::get<1>(SWAPCHAIN_INFO)).name() }, "]", Reset);
	#endif
	fast_io::io::println(Bold, " Image Color Format : ", Reset, vk::to_string(std::get<1>(SWAPCHAIN_INFO)));

	// SwapChain Image Color Space
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(SwapChain).name(), nullptr, nullptr, nullptr) }, " -> ", std::string_view{ abi::__cxa_demangle(typeid(std::get<2>(SWAPCHAIN_INFO)).name(), nullptr, nullptr, nullptr) }, "]", Reset);
	#else
		fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(SwapChain).name() }, " <- ", std::string_view{ typeid(std::get<2>(SWAPCHAIN_INFO)).name() }, "]", Reset);
	#endif
	fast_io::io::println(Bold, " Image Color Space : ", Reset, vk::to_string(std::get<2>(SWAPCHAIN_INFO)));

	#if defined(DEBUG)
		fast_io::io::println(Bold, "  Validation Layer : ", Reset, Chartreuse1, "Enabled", Reset);

		// Vulkan Loader Version
		#if defined(PATATA_VULKAN_VALIDATION_LAYERS_VERSION)
		fast_io::io::println(Bold, "  Validation Layer Version : ", Reset, PATATA_VULKAN_VALIDATION_LAYERS_VERSION);
		#endif
	#else
		fast_io::io::println(Bold, "  Validation Layer : ", Reset, BLightGoldenRod1, "Disabled", Reset);
	#endif

	#if defined(PATATA_IMGUI_VERSION)
		fast_io::io::println(Bold, "  Imgui Version : ", Reset, PATATA_IMGUI_VERSION);
	#endif
		fast_io::io::println("");
}
