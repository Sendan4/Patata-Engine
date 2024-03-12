#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif
#include <cstddef> // std::size_t

#include <fast_io.h>
#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>

#if defined(_WIN64)
#include <windows.h>
#endif

#include "Log.hpp"
#include "TerminalColors.hpp"
