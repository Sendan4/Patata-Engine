#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif
#include <tuple>

#include <SDL_vulkan.h>
#include <fast_io.h>

#include "Log.hpp"
#include "RaccoonRenderer.hpp"
#include "TerminalColors.hpp"
