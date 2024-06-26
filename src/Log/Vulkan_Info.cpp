#include "Vulkan_Info.hpp"

void
Patata::Graphics::RaccoonRenderer::VulkanBackend::VulkanInfo (
    YAML::Node CONFIG,
    std::tuple<vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR>
        SWAPCHAIN_INFO)
{
  fast_io::io::println ("\n", PATATA_TERM_BOLD, PATATA_TERM_COLOR_PATATA,
                        "Raccoon Renderer ", PATATA_TERM_RESET, "INFO");

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
      case 65541:
        Vendor = "Mesa";
        break;
      default:
        Vendor = "Unknown";
        break;
      }

    fast_io::io::print (PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
                        "  [",
                        std::string_view{ abi::__cxa_demangle (
                            typeid (PhysicalDeviceProperties).name (), nullptr,
                            nullptr, nullptr) },
                        "]",
#else
                        "  [",
                        std::string_view{
                            typeid (PhysicalDeviceProperties).name () },
                        "]",
#endif
                        PATATA_TERM_RESET, PATATA_TERM_BOLD,
                        " Device Vendor : ", PATATA_TERM_RESET);

    switch (PhysicalDeviceProperties.vendorID)
      {
      case 32902:
        fast_io::io::println (PATATA_TERM_COLOR_BLUE, Vendor,
                              PATATA_TERM_RESET);
        break;
      case 4098:
        fast_io::io::println (PATATA_TERM_COLOR_RED, Vendor,
                              PATATA_TERM_RESET);
        break;
      case 4318:
        fast_io::io::println (PATATA_TERM_COLOR_GREEN, Vendor,
                              PATATA_TERM_RESET);
        break;
      case 65541:
        fast_io::io::println (PATATA_TERM_COLOR_GRAY1, Vendor,
                              PATATA_TERM_RESET);
        break;
      default:
        fast_io::io::println (Vendor);
        break;
      }
  }

  // Vulkan Hardware Vendor
  {
    fast_io::io::print (PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
                        "  [",
                        std::string_view{ abi::__cxa_demangle (
                            typeid (PhysicalDeviceProperties).name (), nullptr,
                            nullptr, nullptr) },
                        "]",
#else
                        "  [",
                        std::string_view{
                            typeid (PhysicalDeviceProperties.vendorID)
                                .name () },
                        "]",
#endif
                        PATATA_TERM_RESET, PATATA_TERM_BOLD,
                        " Device VendorID : ", PATATA_TERM_RESET);

    // Hexadecimal VendorID
    fast_io::io::print (PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
                        "[Hexadecimal] ", PATATA_TERM_RESET);
    switch (PhysicalDeviceProperties.vendorID)
      {
      case 32902:
        fast_io::io::print (PATATA_TERM_COLOR_BLUE);
        break;
      case 4098:
        fast_io::io::print (PATATA_TERM_COLOR_RED);
        break;
      case 4318:
        fast_io::io::print (PATATA_TERM_COLOR_GREEN);
        break;
      }
    fast_io::io::print (fast_io::mnp::hex (PhysicalDeviceProperties.vendorID),
                        PATATA_TERM_RESET, " ");

    // Decimal VendorID
    fast_io::io::print (PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0, "[Decimal] ",
                        PATATA_TERM_RESET);
    switch (PhysicalDeviceProperties.vendorID)
      {
      case 32902:
        fast_io::io::print (PATATA_TERM_COLOR_BLUE);
        break;
      case 4098:
        fast_io::io::print (PATATA_TERM_COLOR_RED);
        break;
      case 4318:
        fast_io::io::print (PATATA_TERM_COLOR_GREEN);
        break;
      }
    fast_io::io::println (PhysicalDeviceProperties.vendorID);
  }

  // Device Type
  {
    fast_io::io::println (PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
                          "  [",
                          std::string_view{ abi::__cxa_demangle (
                              typeid (PhysicalDeviceProperties).name (),
                              nullptr, nullptr, nullptr) },
                          "]",
#else
                          "  [",
                          std::string_view{
                              typeid (PhysicalDeviceProperties).name () },
                          "]",
#endif
                          PATATA_TERM_RESET, PATATA_TERM_BOLD,
                          " Device Type : ", PATATA_TERM_RESET,
                          vk::to_string (PhysicalDeviceProperties.deviceType));
  }

  // Device Name | GPU Vendor
  {
    fast_io::io::print (PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
                        "  [",
                        std::string_view{ abi::__cxa_demangle (
                            typeid (PhysicalDeviceProperties).name (), nullptr,
                            nullptr, nullptr) },
                        "]",
#else
                        "  [",
                        std::string_view{
                            typeid (PhysicalDeviceProperties).name () },
                        "]",
#endif
                        PATATA_TERM_RESET, PATATA_TERM_BOLD,
                        " Device Name : ", PATATA_TERM_RESET);

    switch (PhysicalDeviceProperties.vendorID)
      {
      case 32902:
        fast_io::io::print (PATATA_TERM_COLOR_BLUE);
        break;
      case 4098:
        fast_io::io::print (PATATA_TERM_COLOR_RED);
        break;
      case 4318:
        fast_io::io::print (PATATA_TERM_COLOR_GREEN);
        break;
      }
    fast_io::io::println (
        std::string_view{ PhysicalDeviceProperties.deviceName },
        PATATA_TERM_RESET);
  }

// Vulkan Loader Version
#if defined(PATATA_VULKAN_LOADER_VERSION)
  if (strcmp (PATATA_VULKAN_LOADER_VERSION, "undefined") != 0)
    fast_io::io::println (PATATA_TERM_BOLD,
                          "  Loader Version : ", PATATA_TERM_RESET,
                          PATATA_VULKAN_LOADER_VERSION);
#endif

// Vulkan Headers Version
#if defined(PATATA_VULKAN_HEADERS_VERSION)
  fast_io::io::println (PATATA_TERM_BOLD,
                        "  Headers Version : ", PATATA_TERM_RESET,
                        PATATA_VULKAN_HEADERS_VERSION);
#endif

  // Vulkan Version
  {
    fast_io::io::print (
        PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
        "  [",
        std::string_view{ abi::__cxa_demangle (
            typeid (PhysicalDeviceProperties.apiVersion).name (), nullptr,
            nullptr, nullptr) },
        "]",
#else
        "  [",
        std::string_view{
            typeid (PhysicalDeviceProperties.apiVersion).name () },
        "]",
#endif
        PATATA_TERM_RESET, PATATA_TERM_BOLD,
        " Vulkan Version : ", PATATA_TERM_RESET);

    std::string vk_version
        = std::to_string (VK_VERSION_MAJOR (VulkanVersion)) + '.'
          + std::to_string (VK_VERSION_MINOR (VulkanVersion)) + '.'
          + std::to_string (VK_VERSION_PATCH (VulkanVersion)) + '.'
          + std::to_string (VK_API_VERSION_VARIANT (VulkanVersion));

    fast_io::io::println (vk_version);
  }

  /*
  // Vulkan Driver Name
  {
  }
  */

  // Driver Version
  {
    fast_io::io::println (
        PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
        "  [",
        std::string_view{ abi::__cxa_demangle (
            typeid (PhysicalDeviceProperties.driverVersion).name (), nullptr,
            nullptr, nullptr) },
        "]",
#else
        "  [",
        std::string_view{
            typeid (PhysicalDeviceProperties.driverVersion).name () },
        "]",
#endif
        PATATA_TERM_RESET, PATATA_TERM_BOLD,
        " Driver Version : ", PATATA_TERM_RESET,
        VK_VERSION_MAJOR (PhysicalDeviceProperties.driverVersion), ".",
        VK_VERSION_MINOR (PhysicalDeviceProperties.driverVersion), ".",
        VK_VERSION_PATCH (PhysicalDeviceProperties.driverVersion), ".",
        VK_API_VERSION_VARIANT (PhysicalDeviceProperties.driverVersion));
  }

  // Vulkan Version
  {
    fast_io::io::print (
        PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
        "  [",
        std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                               nullptr, nullptr, nullptr) },
        " -> ",
        std::string_view{
            abi::__cxa_demangle (typeid (std::get<0> (SWAPCHAIN_INFO)).name (),
                                 nullptr, nullptr, nullptr) },
        " && ",
        std::string_view{ abi::__cxa_demangle (typeid (CONFIG).name (),
                                               nullptr, nullptr, nullptr) },
        "]",
#else
        "  [", std::string_view{ typeid (SwapChain).name () }, " -> ",
        std::string_view{ typeid (std::get<0> (SWAPCHAIN_INFO)).name () },
        " && ", std::string_view{ typeid (CONFIG).name () }, "]",
#endif
        PATATA_TERM_RESET, PATATA_TERM_BOLD, " Vsync : ");

    if ((std::get<0> (SWAPCHAIN_INFO) == vk::PresentModeKHR::eMailbox
         || std::get<0> (SWAPCHAIN_INFO) == vk::PresentModeKHR::eFifo)
        && CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool> ())
      fast_io::io::println (PATATA_TERM_COLOR_GREEN, "Yes", PATATA_TERM_RESET);
    else if (std::get<0> (SWAPCHAIN_INFO) == vk::PresentModeKHR::eImmediate
             && !CONFIG["patata-engine"]["raccoon-renderer"]["vsync"]
                     .as<bool> ())
      fast_io::io::println (PATATA_TERM_COLOR_YELLOW, "No", PATATA_TERM_RESET);
  }

  // SwapChain Present Mode
  fast_io::io::println (
      PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
      "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<0> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      "]",
#else
      "  [", std::string_view{ typeid (SwapChain).name () }, " <- ",
      std::string_view{ typeid (std::get<0> (SWAPCHAIN_INFO)).name () }, "]",
#endif
      PATATA_TERM_RESET, PATATA_TERM_BOLD,
      " Present Mode : ", PATATA_TERM_RESET,
      vk::to_string (std::get<0> (SWAPCHAIN_INFO)));

  // SwapChain Images
  fast_io::io::println (
      PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
      "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      "]",
#else
      "  [", std::string_view{ typeid (SwapChain).name () }, "]",
#endif
      PATATA_TERM_RESET, PATATA_TERM_BOLD, " Images : ", PATATA_TERM_RESET,
      SwapChainBuffers.size ());

  // SwapChain Image Color Format
  fast_io::io::println (
      PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
      "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<1> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      "]",
#else
      "  [", std::string_view{ typeid (SwapChain).name () }, " <- ",
      std::string_view{ typeid (std::get<1> (SWAPCHAIN_INFO)).name () }, "]",
#endif
      PATATA_TERM_RESET, PATATA_TERM_BOLD,
      " Image Color Format : ", PATATA_TERM_RESET,
      vk::to_string (std::get<1> (SWAPCHAIN_INFO)));

  // SwapChain Image Color Space
  fast_io::io::println (
      PATATA_TERM_DIM, PATATA_TERM_COLOR_GRAY0,
#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
      "  [",
      std::string_view{ abi::__cxa_demangle (typeid (SwapChain).name (),
                                             nullptr, nullptr, nullptr) },
      " -> ",
      std::string_view{
          abi::__cxa_demangle (typeid (std::get<2> (SWAPCHAIN_INFO)).name (),
                               nullptr, nullptr, nullptr) },
      "]",
#else
      "  [", std::string_view{ typeid (SwapChain).name () }, " <- ",
      std::string_view{ typeid (std::get<2> (SWAPCHAIN_INFO)).name () }, "]",
#endif
      PATATA_TERM_RESET, PATATA_TERM_BOLD,
      " Image Color Space : ", PATATA_TERM_RESET,
      vk::to_string (std::get<2> (SWAPCHAIN_INFO)));

#if defined(DEBUG)
  fast_io::io::println (PATATA_TERM_BOLD,
                        "  Validation Layer : ", PATATA_TERM_RESET,
                        PATATA_TERM_COLOR_GREEN, "Enabled", PATATA_TERM_RESET);

// Vulkan Validation Layer Version
#if defined(PATATA_VULKAN_VALIDATION_LAYERS_VERSION)
  fast_io::io::println (PATATA_TERM_BOLD,
                        "  Validation Layer Version : ", PATATA_TERM_RESET,
                        PATATA_VULKAN_VALIDATION_LAYERS_VERSION);
#endif
#else
  fast_io::io::println (
      PATATA_TERM_BOLD, "  Validation Layer : ", PATATA_TERM_RESET,
      PATATA_TERM_COLOR_YELLOW, "Disabled", PATATA_TERM_RESET);
#endif

#if defined(PATATA_IMGUI_VERSION)
  fast_io::io::println (PATATA_TERM_BOLD,
                        "  Imgui Version : ", PATATA_TERM_RESET,
                        PATATA_IMGUI_VERSION);
#endif
  fast_io::io::println ("");
}
