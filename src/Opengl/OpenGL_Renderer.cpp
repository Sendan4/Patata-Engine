#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>

// Patata Engine
#include "PatataEngine/Graphics/OpenGLRenderer.hpp"
#include "Log.hpp"

Patata::Graphics::OpenGLRenderer::OpenGLRenderer(YAML::Node & Config) {
	Patata::Log::OpenGLInfo(Config);
}
Patata::Graphics::OpenGLRenderer::~OpenGLRenderer(void) {}
