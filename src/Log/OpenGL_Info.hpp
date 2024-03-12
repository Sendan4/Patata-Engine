#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <glad/gl.h>
#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>

#if defined(_WIN64)
#include <windows.h>
#endif

#include "TerminalColors.hpp"
#include "Log.hpp"
