#include "Graphics/Vulkan.hpp"
#include <iomanip>

void Patata::Graphics::VulkanRenderer::VulkanInfo(void) {
	std::cout << "\n" << FindianRed1 << Bold << "Vulkan Info:\n" << Reset;
	std::cout << Bold << "  SwapChainBuffer -> Size:\t" << SwapChainBuffers.size() << "\n";
	//std::cout << SwapChainBuffers[0].Image << "\n";

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	std::string vsync;
	if (PresentMode == vk::PresentModeKHR::eFifo) {
		std::string tmp = Dim;
		vsync = "Yes" + tmp + " | Using Fifo" + Reset;
	}
	else
		vsync = "No";

	std::cout << "  " << Bold << vk::to_string(PhysicalDeviceProperties.deviceType) << ":\t\t" << Reset;

	std::string Vendor;
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : std::cout << FSteelBlue1; Vendor = "Intel"; break;
		case 4098 : std::cout << FindianRed1; Vendor = "AMD"; break;
		case 4318 : std::cout << Chartreuse1; Vendor = "Nvidia"; break;
	}
	std::cout << PhysicalDeviceProperties.deviceName << Reset << "\n";

	std::cout << Bold << "  VendorID:\t\t\t" << Reset;

	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : std::cout << FSteelBlue1; break;
		case 4098 : std::cout << FindianRed1; break;
		case 4318 : std::cout << Chartreuse1; break;
	}
	std::cout << Vendor << Reset << Dim << ' ' << Reset << " Dec( " << Dim << PhysicalDeviceProperties.vendorID << Reset << " )" << std::hex << " Hex( " << Dim << std::showbase << PhysicalDeviceProperties.vendorID << Reset << std::dec << " )" << Reset << "\n";

	std::cout << Bold << "  Vulkan Version:\t\t" << Reset << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << Reset << "\n";
	std::cout << Bold << "  Driver Version:\t\t" << Reset << PhysicalDeviceProperties.driverVersion << "\n";
	std::cout << Bold << "  Vsync:\t\t\t" << Reset << Chartreuse1 << vsync << Reset << "\n";
	#if defined(DEBUG)
		std::cout << Bold << "  Validation Layer:\t\t" << Reset << Chartreuse1 << "Enabled\n" << Reset;
	#else
		std::cout << Bold << "  Validation Layer:\t\t" << Reset << BLightGoldenRod1 << "Disabled\n" << Reset;
	#endif
	std::cout << "\n";
}
