#include "OpenGL_Renderer.hpp"

Patata::Graphics::RaccoonRenderer::OpenGLBackend::OpenGLBackend(YAML::Node & Config) {
	Patata::Log::OpenGLInfo(Config);
}
Patata::Graphics::RaccoonRenderer::OpenGLBackend::~OpenGLBackend(void) {}
