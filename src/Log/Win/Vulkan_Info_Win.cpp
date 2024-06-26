#include "Vulkan_Info.hpp"

void
Patata::Graphics::RaccoonRenderer::VulkanBackend::VulkanInfo (
    YAML::Node CONFIG,
    std::tuple<vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR>
        SWAPCHAIN_INFO)
{
  HANDLE Terminal = GetStdHandle (STD_OUTPUT_HANDLE);
  DWORD  mode     = 0;
  GetConsoleMode (Terminal, &mode);
  SetConsoleMode (Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);

  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_PATATA,
                        "\nRaccoon Renderer", PATATA_TERM_COLOR_WHITE,
                        " INFO :");

  // Backend
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        "  Graphics Backend : ", PATATA_TERM_COLOR_RED,
                        "Vulkan", PATATA_TERM_RESET);

  vk::PhysicalDeviceProperties PhysicalDeviceProperties
      = PhysicalDevice.getProperties ();
  const uint32_t VulkanVersion = PhysicalDeviceProperties.apiVersion;

  // Vulkan Vendor String
  {
    std::string Vendor;
    switch (PhysicalDeviceProperties.vendorID)
      {
      case 32902:
        Vendor = "Intel";
        break;
      case 4098:
        Vendor = "AMD";
        break;
      case 4318:
        Vendor = "Nvidia";
        break;
      }

#if defined(__GNUC__) || defined(__MINGW64__)
    fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
                        std::string_view{ abi::__cxa_demangle (
                            typeid (PhysicalDeviceProperties).name (), nullptr,
                            nullptr, nullptr) },
                        "]");
#else
    fast_io::io::print (
        fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
        std::string_view{ typeid (PhysicalDeviceProperties).name () }, "]");
#endif
    fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        " Device Vendor : ");
    switch (PhysicalDeviceProperties.vendorID)
      {
      case 32902:
        fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_BLUE, Vendor);
        break;
      case 4098:
        fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_RED, Vendor);
        break;
      case 4318:
        fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_GREEN,
                              Vendor);
        break;
      }
  }

// Vulkan Hardware Vendor
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
                      std::string_view{ abi::__cxa_demangle (
                          typeid (PhysicalDeviceProperties.vendorID).name (),
                          nullptr, nullptr, nullptr) },
                      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (PhysicalDeviceProperties.vendorID).name () },
      "]");
#endif
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                      " Device VendorID : ");

  // Hexadecimal VendorID
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0,
                      "[Hexadecimal]");
  switch (PhysicalDeviceProperties.vendorID)
    {
    case 32902:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_BLUE);
      break;
    case 4098:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_RED);
      break;
    case 4318:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GREEN);
      break;
    }
  fast_io::io::print (fast_io::out (), " ",
                      fast_io::mnp::hex (PhysicalDeviceProperties.vendorID),
                      " ");

  // Decimal VendorID
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "[Decimal]");
  switch (PhysicalDeviceProperties.vendorID)
    {
    case 32902:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_BLUE);
      break;
    case 4098:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_RED);
      break;
    case 4318:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GREEN);
      break;
    }
  fast_io::io::println (fast_io::out (), " ",
                        PhysicalDeviceProperties.vendorID);

// Device Type
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
                      std::string_view{ abi::__cxa_demangle (
                          typeid (PhysicalDeviceProperties).name (), nullptr,
                          nullptr, nullptr) },
                      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (PhysicalDeviceProperties).name () }, "]");
#endif
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        " Device Type : ", PATATA_TERM_COLOR_GRAY1,
                        vk::to_string (PhysicalDeviceProperties.deviceType));

// Device Name | GPU Vendor
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
                      std::string_view{ abi::__cxa_demangle (
                          typeid (PhysicalDeviceProperties).name (), nullptr,
                          nullptr, nullptr) },
                      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (PhysicalDeviceProperties).name () }, "]");
#endif
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                      " Device Name : ");
  switch (PhysicalDeviceProperties.vendorID)
    {
    case 32902:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_BLUE);
      break;
    case 4098:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_RED);
      break;
    case 4318:
      fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GREEN);
      break;
    }
  fast_io::io::println (
      fast_io::out (),
      std::string_view{ PhysicalDeviceProperties.deviceName });

// Vulkan Loader Version
#if defined(PATATA_VULKAN_LOADER_VERSION)
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        "  Loader Version : ", PATATA_TERM_RESET,
                        PATATA_VULKAN_LOADER_VERSION);
#endif

// Vulkan Loader Version
#if defined(PATATA_VULKAN_HEADERS_VERSION)
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        "  Headers Version : ", PATATA_TERM_RESET,
                        PATATA_VULKAN_HEADERS_VERSION);
#endif

// Vulkan Version
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
                      std::string_view{ abi::__cxa_demangle (
                          typeid (PhysicalDeviceProperties.apiVersion).name (),
                          nullptr, nullptr, nullptr) },
                      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (PhysicalDeviceProperties.apiVersion).name () },
      "]");
#endif
  {
    std::string vk_version
        = std::to_string (VK_VERSION_MAJOR (VulkanVersion)) + '.'
          + std::to_string (VK_VERSION_MINOR (VulkanVersion)) + '.'
          + std::to_string (VK_VERSION_PATCH (VulkanVersion)) + '.'
          + std::to_string (VK_API_VERSION_VARIANT (VulkanVersion));

    fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                          " Vulkan Version : ", PATATA_TERM_COLOR_GRAY1,
                          vk_version);
  }

// Driver Version
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ abi::__cxa_demangle (
          typeid (PhysicalDeviceProperties.driverVersion).name (), nullptr,
          nullptr, nullptr) },
      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{
          typeid (PhysicalDeviceProperties.driverVersion).name () },
      "]");
#endif
  fast_io::io::println (
      fast_io::out (), PATATA_TERM_COLOR_WHITE,
      " Driver Version : ", PATATA_TERM_COLOR_GRAY1,
      VK_VERSION_MAJOR (PhysicalDeviceProperties.driverVersion), ".",
      VK_VERSION_MINOR (PhysicalDeviceProperties.driverVersion), ".",
      VK_VERSION_PATCH (PhysicalDeviceProperties.driverVersion), ".",
      VK_API_VERSION_VARIANT (PhysicalDeviceProperties.driverVersion));

// Vsync
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<0> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      " && ",
      std::string_view{ abi::__cxa_demangle (typeid (CONFIG).name (), nullptr,
                                             nullptr, nullptr) },
      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (SwapChain).name () }, " -> ",
      std::string_view{ typeid (std::get<0> (SWAPCHAIN_INFO)).name () },
      " && ", std::string_view{ typeid (CONFIG).name () }, "]");
#endif

  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_WHITE, " Vsync : ");
  if ((std::get<0> (SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox
       || std::get<0> (SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo)
      && CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool> ())
    {
      fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_GREEN, "Yes");
    }
  else if (std::get<0> (SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate
           && !CONFIG["vsync"].as<bool> ())
    {
      fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_YELLOW, "No");
    }

// SwapChain Present Mode
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<0> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (SwapChain).name () }, " -> ",
      std::string_view{ typeid (std::get<0> (SWAPCHAIN_INFO)).name () }, "]");
#endif
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        " Present Mode : ", PATATA_TERM_COLOR_GRAY1,
                        vk::to_string (std::get<0> (SWAPCHAIN_INFO)));

// SwapChain Images
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      "]");
#else
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
                      std::string_view{ typeid (SwapChain).name () }, "]");
#endif
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        " Images : ", PATATA_TERM_COLOR_GRAY1,
                        SwapChainBuffers.size ());

// SwapChain Image Color Format
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<1> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (SwapChain).name () }, " -> ",
      std::string_view{ typeid (std::get<1> (SWAPCHAIN_INFO)).name () }, "]");
#endif
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        " Image Color Format : ", PATATA_TERM_COLOR_GRAY1,
                        vk::to_string (std::get<1> (SWAPCHAIN_INFO)));

// SwapChain Image Color Space
#if defined(__GNUC__) || defined(__MINGW64__)
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<2> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      "]");
#else
  fast_io::io::print (
      fast_io::out (), PATATA_TERM_COLOR_GRAY0, "  [",
      std::string_view{ typeid (SwapChain).name () }, " -> ",
      std::string_view{ typeid (std::get<2> (SWAPCHAIN_INFO)).name () }, "]");
#endif
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        " Image Color Space : ", PATATA_TERM_COLOR_GRAY1,
                        vk::to_string (std::get<2> (SWAPCHAIN_INFO)));

  // Vulkan Validation Layer
  fast_io::io::print (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                      "  Validation Layer : ");
#if defined(DEBUG) && defined(PATATA_USE_VVL)
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_GREEN, "Enabled");

#if defined(PATATA_VULKAN_VALIDATION_LAYERS_VERSION)
  fast_io::io::println (
      fast_io::out (), PATATA_TERM_COLOR_WHITE,
      "  Validation Layer Version : ", PATATA_TERM_COLOR_GRAY1,
      PATATA_VULKAN_VALIDATION_LAYERS_VERSION);
#endif
#else
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_YELLOW, "Disabled");
#endif

// ImGUI Version
#if defined(PATATA_IMGUI_VERSION)
  fast_io::io::println (fast_io::out (), PATATA_TERM_COLOR_WHITE,
                        "  ImGui Version : ", PATATA_TERM_COLOR_GRAY1,
                        PATATA_IMGUI_VERSION);
#endif

  fast_io::io::println (fast_io::out (), PATATA_TERM_RESET);
  SetConsoleMode (Terminal, mode);
}
