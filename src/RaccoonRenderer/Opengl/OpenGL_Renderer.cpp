// Patata Engine
#include "PatataEngine/Graphics/RaccoonRenderer.hpp"
#include "Log.hpp"

Patata::Graphics::RaccoonRenderer::OpenGLBackend::OpenGLBackend(YAML::Node & Config) {
	Patata::Log::OpenGLInfo(Config);
}
Patata::Graphics::RaccoonRenderer::OpenGLBackend::~OpenGLBackend(void) {}
