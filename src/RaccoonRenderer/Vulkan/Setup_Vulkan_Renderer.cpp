#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif
#include <tuple>

#include <fast_io.h>
#include <SDL_vulkan.h>

#include "PatataEngine/Graphics/RaccoonRenderer.hpp"
#include "TerminalColors.hpp"
#include "Log.hpp"

Patata::Graphics::RaccoonRenderer::VulkanBackend::VulkanBackend(SDL_Window *& WINDOW, YAML::Node & CONFIG) {
	fast_io::io::println(
	#if defined(_WIN64)
		fast_io::out(),
	#endif
		PATATA_TERM_COLOR_RED,
	#if !defined(_WIN64)
		PATATA_TERM_BOLD,
	#endif
		"Vulkan",
	#if defined(_WIN64)
		PATATA_TERM_COLOR_WHITE,
	#else
		PATATA_TERM_RESET,
	#endif
	#if !defined(_WIN64)
		PATATA_TERM_BOLD,
	#endif
		" SETUP",
		PATATA_TERM_RESET);

	if (!CreateInstance(WINDOW, CONFIG)) return;

	PhysicalDevice = Instance.enumeratePhysicalDevices().front();
	uint32_t GraphicsQueueFamilyIndex = CreateLogicalDeviceAndCreateQueue();

	if (SDL_Vulkan_CreateSurface(WINDOW, Instance, reinterpret_cast<VkSurfaceKHR *>(&Surface))) {
		fast_io::io::println(
		#if defined(_WIN64)
			fast_io::out(),
		#endif
		#if !defined(_WIN64)
			PATATA_TERM_DIM,
		#endif
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"[", std::string_view{ abi::__cxa_demangle(typeid(Surface).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"[", std::string_view{ typeid(Surface).name() }, "]",
		#endif
		#if defined(_WIN64)
			PATATA_TERM_COLOR_WHITE,
		#else
			PATATA_TERM_RESET,
		#endif
		#if !defined(_WIN64)
			PATATA_TERM_BOLD,
		#endif
			" SDL Create Window Surface : ",
			PATATA_TERM_RESET,
			PATATA_TERM_COLOR_GREEN,
			"Success",
			PATATA_TERM_RESET);
	}
	else {
		fast_io::io::println(
		#if defined(_WIN64)
			fast_io::out(),
		#endif
		#if !defined(_WIN64)
			PATATA_TERM_DIM,
		#endif
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"[", std::string_view{ abi::__cxa_demangle(typeid(Surface).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"[", std::string_view{ typeid(Surface).name() }, "]",
		#endif
		#if defined(_WIN64)
			PATATA_TERM_COLOR_WHITE,
		#else
			PATATA_TERM_RESET,
		#endif
		#if !defined(_WIN64)
			PATATA_TERM_BOLD,
		#endif
			" SDL Create Window Surface : ",
			PATATA_TERM_RESET,
			PATATA_TERM_COLOR_YELLOW,
			"Fail",
			PATATA_TERM_RESET);

		Patata::Log::FatalErrorMessage("SDL", SDL_GetError(), CONFIG);
		return;
	}

	std::tuple <vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> swapchaininfo = CreateSwapChain(GraphicsQueueFamilyIndex, CONFIG);
	CreateImageView(GraphicsQueueFamilyIndex);
	CreateCommandBuffer(GraphicsQueueFamilyIndex);
	CreateRenderPass();

	Semaphore = Device.createSemaphore(vk::SemaphoreCreateInfo());

	VulkanInfo(CONFIG, swapchaininfo);
}

Patata::Graphics::RaccoonRenderer::VulkanBackend::~VulkanBackend(void) {        
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