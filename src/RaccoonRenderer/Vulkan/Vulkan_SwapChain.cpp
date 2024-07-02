#include "Vulkan_SwapChain.hpp"

std::tuple<vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR>
Patata::Graphics::RaccoonRenderer::VulkanBackend::CreateSwapChain (
    uint32_t & GraphicsQueueFamilyIndex, YAML::Node CONFIG, SDL_Window * WINDOW)
{
  // Present Modes
  vk::PresentModeKHR * PresentModes;
  uint32_t PresentModesCount = 0;

  vk::Result Result;

  Result = PhysicalDevice.getSurfacePresentModesKHR(Surface, &PresentModesCount, nullptr);
  std::future<void> ReturnVulkanCheck0 = std::async(std::launch::async, Patata::Log::VulkanCheck, "Get Surface Present Modes - Obtaining the count", Result);

  PresentModes = new vk::PresentModeKHR[PresentModesCount];

  Result = PhysicalDevice.getSurfacePresentModesKHR(Surface, &PresentModesCount, PresentModes);
  std::future<void> ReturnVulkanCheck1 = std::async(std::launch::async, Patata::Log::VulkanCheck, "Get Surface Present Modes", Result);

  // Surface Formats
  vk::SurfaceFormatKHR * SurfaceFormats;
  uint32_t SurfaceFormatsCount = 0;

  Result = PhysicalDevice.getSurfaceFormatsKHR(Surface, &SurfaceFormatsCount, nullptr);
  std::future<void> ReturnVulkanCheck2 = std::async(std::launch::async, Patata::Log::VulkanCheck, "Get Surface Formats - Obtaining the count", Result);

  SurfaceFormats = new vk::SurfaceFormatKHR[SurfaceFormatsCount];

  Result = PhysicalDevice.getSurfaceFormatsKHR(Surface, &SurfaceFormatsCount, SurfaceFormats);
  std::future<void> ReturnVulkanCheck3 = std::async(std::launch::async, Patata::Log::VulkanCheck, "Get Surface Formats", Result);

  // Extent
  {
	  int * w, * h; 
	  SDL_Vulkan_GetDrawableSize(WINDOW, w, h);

	  SwapChainExtent.width  = *w;
	  SwapChainExtent.height = *h;
  }

  // Encontrar un Modo de presentacion
  if (CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool> ())
    {
      for (uint32_t i = 0; i < PresentModesCount; ++i)
        {
          if (PresentModes[i] == vk::PresentModeKHR::eMailbox)
            {
              PresentMode = vk::PresentModeKHR::eMailbox;
              break;
            }
          if (PresentModes[i] == vk::PresentModeKHR::eFifo)
            {
              PresentMode = vk::PresentModeKHR::eFifo;
              break;
            }
        }
    }
  else
	  PresentMode = vk::PresentModeKHR::eImmediate;

  // Encontrar un formato de superficie
  for (uint32_t i = 0; i < SurfaceFormatsCount; ++i) {
	  if (CONFIG["patata-engine"]["raccoon-renderer"]["10bit-image"].as<bool> ()) {
		  // 10 Bits
		  if (SurfaceFormats[i].format == vk::Format::eA2B10G10R10UnormPack32 ||
				  SurfaceFormats[i].format == vk::Format::eA2B10G10R10UnormPack32) {
			  SurfaceFormat = SurfaceFormats[i];
			  break;
		  }
	  }
	  else {
		  // 8 Bits
		  if (SurfaceFormats[i].format == vk::Format::eB8G8R8A8Srgb ||
				  SurfaceFormats[i].format == vk::Format::eR8G8B8A8Unorm ||
				  SurfaceFormats[i].format == vk::Format::eR8G8B8Srgb) {
			  SurfaceFormat = SurfaceFormats[i];
			  break;
		  }
	  }
  }

  vk::SurfaceCapabilitiesKHR SurfaceCapabilities
      = PhysicalDevice.getSurfaceCapabilitiesKHR (Surface);

  vk::SwapchainCreateInfoKHR SwapChainCreateInfo{};
  SwapChainCreateInfo.surface          = Surface;
  SwapChainCreateInfo.minImageCount    = SurfaceCapabilities.minImageCount;
  SwapChainCreateInfo.imageFormat      = SurfaceFormat.format;
  SwapChainCreateInfo.imageColorSpace  = SurfaceFormat.colorSpace;
  SwapChainCreateInfo.imageExtent      = SwapChainExtent;
  SwapChainCreateInfo.imageArrayLayers = 1;
  SwapChainCreateInfo.imageUsage   = vk::ImageUsageFlagBits::eColorAttachment;
  SwapChainCreateInfo.preTransform = SurfaceCapabilities.currentTransform;
  SwapChainCreateInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
  SwapChainCreateInfo.presentMode    = PresentMode;
  SwapChainCreateInfo.clipped        = true;
  SwapChainCreateInfo.queueFamilyIndexCount = GraphicsQueueFamilyIndex;
  SwapChainCreateInfo.oldSwapchain          = nullptr;

  Result = Device.createSwapchainKHR (&SwapChainCreateInfo, nullptr, &SwapChain);

  delete[] PresentModes;

  std::future<void> ReturnVulkanCheck4 = std::async(std::launch::async, Patata::Log::VulkanCheck, "SwapChain", Result);

  return { PresentMode, SurfaceFormat.format, SurfaceFormat.colorSpace };
}
