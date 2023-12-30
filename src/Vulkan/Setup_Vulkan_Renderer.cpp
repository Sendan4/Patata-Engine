#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif
#include <vector>
#include <tuple>

#include <fast_io.h>
#include <SDL_vulkan.h>

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "TerminalColors.hpp"
#include "Log.hpp"

Patata::Graphics::VulkanRenderer::VulkanRenderer(SDL_Window *& WINDOW, YAML::Node CONFIG) {
	#if defined(_WIN64)
	#else
	fast_io::io::println(FindianRed1, Bold, "Vulkan", Reset, Bold, " SETUP", Reset);
	#endif

	if (!CreateInstance(WINDOW, CONFIG)) return;
	#if defined(_WIN64)
	fast_io::io::println(fast_io::out());
	#else
	fast_io::io::println("");
	#endif

	PhysicalDevice = Instance.enumeratePhysicalDevices().front();
	uint32_t GraphicsQueueFamilyIndex = CreateLogicalDeviceAndCreateQueue();
	
	SDL_Vulkan_CreateSurface(WINDOW, Instance, reinterpret_cast<VkSurfaceKHR *>(&Surface));
	/*if (static_cast<bool>(SDL_HasWindowSurface(WINDOW))) {
		#if defined(_WIN64)
		fast_io::io::println("SDL Surface::", std::string_view{ abi::__cxa_demangle(typeid(SDL_GetWindowSurface(WINDOW)).name(), nullptr, nullptr, nullptr) }, "::Yes");
		#else
		fast_io::io::println(Bold, "SDL Surface::", Reset, Dim, std::string_view{ abi::__cxa_demangle(typeid(SDL_GetWindowSurface(WINDOW)).name(), nullptr, nullptr, nullptr) }, Reset, Bold, "::", Reset, BLightGoldenRod1, "Yes", Reset);
		#endif
	}
	else {

	}*/

	std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> swapchaininfo = CreateSwapChain(GraphicsQueueFamilyIndex, CONFIG);
	CreateImageView(GraphicsQueueFamilyIndex);
	CreateCommandBuffer(GraphicsQueueFamilyIndex);
	CreateRenderPass();

	Semaphore = Device.createSemaphore(vk::SemaphoreCreateInfo());

	VulkanInfo(CONFIG, swapchaininfo);
}

Patata::Graphics::VulkanRenderer::~VulkanRenderer(void) {        
	Device.destroySemaphore(Semaphore);
	Device.destroyRenderPass(RenderPass);
	Device.freeCommandBuffers(CommandPool, CommandBuffers);
	Device.destroyCommandPool(CommandPool);
	Device.freeMemory(ImageMemory);
	Device.destroyImage(DepthImage);
	//Device.destroyImageView(ImageView);
	Device.destroySwapchainKHR(SwapChain);
	Instance.destroySurfaceKHR(Surface);
	Device.destroy();
	Instance.destroy();

}
