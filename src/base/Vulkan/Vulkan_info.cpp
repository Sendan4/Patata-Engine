#include "Vulkan.hpp"
#include <iomanip>

void Graphics::VulkanRenderer::VulkanInfo(void) {
	std::cout << "SwapChainBuffer -> Size :\t" << SwapChainBuffers.size() << "\n";
	//std::cout << SwapChainBuffers[0].Image << "\n";

	vk::PhysicalDeviceProperties PhysicalDeviceProperties = PhysicalDevice.getProperties();
	const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

	std::string vsync;
	if (PresentMode == vk::PresentModeKHR::eFifo) {
		std::string tmp = Dim;
		vsync = "Yes" + tmp + " | Using eFifo" + Reset;
	}
	else
		vsync = "No";

	std::cout << FindianRed1 << Bold << "+ Informacion general de Vulkan :" << Reset << "\n";

	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << vk::to_string(PhysicalDeviceProperties.deviceType) << " :\t" << Reset;

	std::string Vendor;
	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : std::cout << FSteelBlue1; Vendor = "Intel"; break;
		case 4098 : std::cout << FindianRed1; Vendor = "AMD"; break;
		case 4318 : std::cout << Chartreuse1; Vendor = "Nvidia"; break;
	}
	std::cout << PhysicalDeviceProperties.deviceName << Reset << "\n";

	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "VendorID :\t" << Reset;

	switch (PhysicalDeviceProperties.vendorID) {
		case 32902 : std::cout << FSteelBlue1; break;
		case 4098 : std::cout << FindianRed1; break;
		case 4318 : std::cout << Chartreuse1; break;
	}
	std::cout << Vendor << Reset << Dim << " |" << Reset << " Dec( " << Dim << PhysicalDeviceProperties.vendorID << Reset << " )" << std::hex << " Hex( " << Dim << std::showbase << PhysicalDeviceProperties.vendorID << Reset << std::dec << " )" << Reset << "\n";

	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Vulkan Version :\t" << Reset << VK_VERSION_MAJOR(VulkanVersion) << '.' << VK_VERSION_MINOR(VulkanVersion) << '.' << VK_VERSION_PATCH(VulkanVersion) << '.' << VK_API_VERSION_VARIANT(VulkanVersion) << Reset << "\n";
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Driver Version :\t" << Reset << PhysicalDeviceProperties.driverVersion << "\n";
	std::cout << FindianRed1 << Bold << "| · " << Reset << Bold << "Vsync :\t" << Reset << Chartreuse1 << vsync << Reset << "\n";

	std::cout << "\n";
}
