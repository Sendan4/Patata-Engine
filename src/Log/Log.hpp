#pragma once

#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
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
		void VulkanList(const char *List[], const size_t &, const std::string &);

		// Errors
		void YamlFileErrorMessage(void);
		void FatalErrorMessage(const std::string &, const std::string &, const YAML::Node &);
		void ErrorMessage(const std::string &);
		void WarningMessage(const std::string &);
	}
}
