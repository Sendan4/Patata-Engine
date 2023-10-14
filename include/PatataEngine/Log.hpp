#include <vector>

#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>

// OS
#if __linux__ && !__ANDROID__
	#define OS "Linux"
#elif _WIN64 || _WIN32
	#define OS "Windows"
#endif

// Compiler
#if __GNUC__
	#if __MINGW64__
		#define COMPILER "MinGW-w64"
	#else
		#define COMPILER "GCC"
	#endif
#elif __clang__
	#define COMPILER "Clang"
#elif _MSC_VER <= 1929
	#define COMPILER "Older Visual Studio (MSVC)"
#elif _MSC_VER >= 1930
	#define COMPILER "Visual Studio (MSVC)"
#endif

namespace Patata {
	namespace Log {
		void StartMapache(void);
		void StartPatataLogInfo(void);
		void OpenGLInfo(YAML::Node);
		void WindowIconSetStatus(SDL_Surface *);

		// Vulkan Setup
		void ListVulkanInstanceExtensions(std::vector <const char *> &, SDL_bool);
		bool VulkanInstanceResult(vk::Result);
		void ListVulkanDeviceResult(const std::vector <const char *>);
		void VulkanLogicalDeviceResult(vk::Result);
		void CheckSwapChain(vk::Result);
		void CheckCommandPool(vk::Result);
		void CheckRenderPass(vk::Result);
		void CheckSurface(bool);
	}
}
