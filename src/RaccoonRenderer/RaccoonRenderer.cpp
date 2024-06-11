#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif

#if defined(_WIN64)
#include <windows.h>
#endif

#include <fast_io.h>

// Patata Engine
#include "PatataEngineImpl.hpp"
#include "TerminalColors.hpp"

#include "ExitLog.hpp"

Patata::Graphics::RaccoonRenderer::RaccoonRenderer (YAML::Node &  Config,
                                                    SDL_Window *& Window)
{
	pVulkanBackend = new Patata::Graphics::RaccoonRenderer::VulkanBackend (
		Window, Config);
}

Patata::Graphics::RaccoonRenderer::~RaccoonRenderer (void)
{
	Patata::Log::DeleteAndLogPtr ("Vulkan Backend", pVulkanBackend);
}
