#include <vector>

#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>

// OS
#if __linux__ && !__ANDROID__
	#define PATATA_OS "Linux"
#elif _WIN64 || _WIN32
	#define PATATA_OS "Windows"
#endif

// Compiler
#if __GNUC__
	#if __MINGW64__
		#define PATATA_COMPILER "MinGW-w64 -> "
	#else
		#define PATATA_COMPILER "GCC -> "
	#endif
#elif __clang__
	#define PATATA_COMPILER "Clang -> "
#elif _MSC_VER <= 1929
	#define PATATA_COMPILER "Old Microsoft Visual C++ (MSVC) -> "
#elif _MSC_VER >= 1930
	#define PATATA_COMPILER "Microsoft Visual C++ (MSVC) -> "
#endif

namespace Patata {
	namespace Log {
		void StartMapache(void);
		void StartPatataLogInfo(void);
		void OpenGLInfo(YAML::Node);
		void WindowIconSetStatus(SDL_Surface *);

		// Vulkan Setup
		void ListVulkanInstanceExtensions(std::vector <const char *>, SDL_bool);
		bool VulkanInstanceResult(vk::Result);
		void ListVulkanDeviceResult(std::vector <const char *>);
		void VulkanLogicalDeviceResult(vk::Result);
		void CheckSwapChain(vk::Result);
		void CheckCommandPool(vk::Result);
		void CheckRenderPass(vk::Result);
		void CheckSurface(bool);

		// Errors
		void YamlFileErrorMessage(void);
		void FatalErrorMessage(std::string, std::string, YAML::Node);
		void ErrorMessage(std::string);
	}
}
