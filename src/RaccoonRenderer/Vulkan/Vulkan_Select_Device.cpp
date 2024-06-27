#include "Vulkan_Select_Device.hpp"

bool
Patata::Graphics::RaccoonRenderer::VulkanBackend::SelectDevice (
    YAML::Node & Config)
{
  uint32_t   GpuCount = 0;
  vk::Result Result;

  // Esta funcion devuelve un numero extra (Conteo Humano desde el 1)
  Result = Instance.enumeratePhysicalDevices (&GpuCount, nullptr);

  std::future<void> ReturnVulkanCheck0 = std::async(std::launch::async, Patata::Log::VulkanCheck, "Enumerate Physical Devices - Obtaining device count ", Result);

  if (GpuCount == 0)
    {
      Patata::Log::FatalErrorMessage ("Patata - Raccoon Renderer",
                                      "No vulkan compatible device found",
                                      Config);
      return false;
    }

  vk::PhysicalDevice * TMPPhysicalDevice;

  // Si solo tienes una GPU compatible, la tomare directamente.
  if (GpuCount == 1)
    {
      fast_io::io::println (
#if defined(_WIN64)
          fast_io::out (),
#endif
#if !defined(_WIN64)
          PATATA_TERM_BOLD,
#endif
          PATATA_TERM_COLOR_PATATA, "\nRaccoon Renderer", PATATA_TERM_RESET,
          " : Only one vulkan compatible device found\n");

      PhysicalDevice = Instance.enumeratePhysicalDevices ().front ();
      vk::PhysicalDeviceFeatures DeviceFeatures
          = PhysicalDevice.getFeatures ();

      // Necesito que la GPU tenga geometryShader
      if (!DeviceFeatures.geometryShader)
        {
          Patata::Log::ErrorMessage ("Your GPU Dont Support Geometry Shader");
          PhysicalDevice = nullptr;
          return false;
        }

      return true;
    }
  else
    {
      TMPPhysicalDevice = new vk::PhysicalDevice[GpuCount];
      Result
          = Instance.enumeratePhysicalDevices (&GpuCount, TMPPhysicalDevice);

	  std::future<void> ReturnVulkanCheck1 = std::async(std::launch::async, Patata::Log::VulkanCheck, "Enumerate Physical Devices - Looking for the devices", Result);
    }
 
  fast_io::io::println (
#if defined(_WIN64)
      fast_io::out (),
#endif
#if !defined(_WIN64)
      PATATA_TERM_BOLD,
#endif
      PATATA_TERM_COLOR_PATATA, "\nRaccoon Renderer", PATATA_TERM_RESET,
      " : Found ", GpuCount, " vulkan compatible devices");

  uint64_t * GpuScore = new uint64_t[GpuCount];

  for (uint32_t i = 0; i < GpuCount; i++)
    {
      vk::PhysicalDeviceProperties2 DeviceProperties
          = TMPPhysicalDevice[i].getProperties2 ();
      vk::PhysicalDeviceFeatures2 DeviceFeatures
          = TMPPhysicalDevice[i].getFeatures2 ();

      switch (DeviceProperties.properties.deviceType)
        {
        case vk::PhysicalDeviceType::eDiscreteGpu:
          GpuScore[i] += 1000;
          break;
        case vk::PhysicalDeviceType::eIntegratedGpu:
          GpuScore[i] += 50;
          break;

        case vk::PhysicalDeviceType::eCpu:
        case vk::PhysicalDeviceType::eOther:
        case vk::PhysicalDeviceType::eVirtualGpu:
          break;
        }

      // Tamaño maximo de textura posible.
      GpuScore[i] += DeviceProperties.properties.limits.maxImageDimension2D;

      // Necesito que la GPU tenga geometryShader
      if (!DeviceFeatures.features.geometryShader)
        {
          GpuScore[i] = 0;

          Patata::Log::ErrorMessage ("Your GPU Dont Support Geometry Shader");
        }

      fast_io::io::println (
#if defined(_WIN64)
          fast_io::out (),
#endif
#if !defined(_WIN64)
		  PATATA_TERM_DIM,
#endif
          PATATA_TERM_COLOR_GRAY0, "  [",
          std::string_view{ vk::to_string (DeviceProperties.properties.deviceType) },
          "] ", PATATA_TERM_RESET,
          std::string_view{ DeviceProperties.properties.deviceName }, " ", GpuScore[i]);
    }

  fast_io::io::println (
#if defined(_WIN64)
      fast_io::out (),
#endif
      "");

  uint64_t HighestScore   = 0;
  uint32_t GpuIndexWinner = 0;

  for (uint32_t i = 0; i < GpuCount; i++)
    {
      if (GpuScore[i] > HighestScore)
        {
          HighestScore   = GpuScore[i];
          GpuIndexWinner = i;
        }
    }

  // Soy muy pesado con el soporte de geometryShader
  if (GpuScore[GpuIndexWinner] == 0)
    {
      Patata::Log::FatalErrorMessage ("Patata - Raccoon Renderer",
                                      "Cannot select a device (GPU) which does not support geometry shader",
                                      Config);
      return false;
    }

  // Seleccionar el dispositivo
  PhysicalDevice = TMPPhysicalDevice[GpuIndexWinner];

  delete[] TMPPhysicalDevice;
  delete[] GpuScore;

  return true;
}
