#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>

namespace Patata {
	namespace Log {
		void StartMapache(void);
		void StartPatataLogInfo(void);
		void OpenGLInfo(const YAML::Node &);
		void WindowLog(SDL_Window *);

		// Vulkan Setup
		void VulkanCheck(const std::string &, const vk::Result &);
		void VulkanList(const char *List[], const unsigned int &, bool, const std::string &);

		// Errors
		void YamlFileErrorMessage(void);
		void FatalErrorMessage(const std::string &, const std::string &, YAML::Node);
		void ErrorMessage(const std::string &);
	}
}