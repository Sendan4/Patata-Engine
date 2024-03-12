#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif
#include <tuple>

#include <fast_io.h>
#include <SDL_vulkan.h>

#include "RaccoonRenderer.hpp"
#include "TerminalColors.hpp"
#include "Log.hpp"
