#include <cstring>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <SDL.h>
#include <SDL_syswm.h>
#if defined(_WIN64)
#include <windows.h>
#endif

// Patata Engine
#include "Log.hpp"
#include "TerminalColors.hpp"
