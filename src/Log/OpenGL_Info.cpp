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

#include "TerminalColors.hpp"
#include "Log.hpp"

void Patata::Log::OpenGLInfo(const YAML::Node & CONFIG) {
	fast_io::io::println(PATATA_TERM_BOLD,
		PATATA_TERM_COLOR_PATATA,
		"Raccoon Renderer ",
		PATATA_TERM_RESET,
		"INFO");

	fast_io::io::println(PATATA_TERM_BOLD,
		"  Graphics Backend : ",
		PATATA_TERM_RESET,
		PATATA_TERM_COLOR_BLUE,
		"OpenGL");

	// GPU Vendor
	{
		auto Vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));

		fast_io::io::println(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(Vendor).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(Vendor)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" Device Vendor : ",
			PATATA_TERM_RESET,
			std::string_view{ Vendor });
	}

	// GPU Name
	{
		auto Name = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

		fast_io::io::println(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(Name).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(Name)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" Device Name : ",
			PATATA_TERM_RESET,
			std::string_view{ Name });
	}

	// OpenGL Version
	{
		GLint glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		fast_io::io::println(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(glmayorversion).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(glmayorversion)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" OpenGL Version : ",
			PATATA_TERM_RESET,
			glversion);
	}

	// GLslang or GLSL Version
	{
		auto GLslang = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));

		fast_io::io::println(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(GLslang).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(GLslang)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" GLslang Version : ",
			PATATA_TERM_RESET,
			std::string_view{ GLslang });
	}

	// GLAD Loader Version
	fast_io::io::println(PATATA_TERM_BOLD, "  GLAD Loader Version : ", PATATA_TERM_RESET, GLAD_GENERATOR_VERSION);

	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		fast_io::io::print(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(contextflags).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(contextflags)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" Profile : ",
			PATATA_TERM_RESET);

		switch (contextflags) {
			case GL_CONTEXT_CORE_PROFILE_BIT : fast_io::io::println("Core"); break;

			case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT : fast_io::io::println("Compatibility"); break;

			default : fast_io::io::println("Unknown"); break;
		}
	}

	// Hardware Or Software Accelerated
	{
		GLint accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		fast_io::io::print(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(accel).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(accel)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" Accelerated Visual : ",
			PATATA_TERM_RESET);

		if (accel == 1)
			fast_io::io::println("Hardware");
		else if (accel == 0)
			fast_io::io::println("Software");
	}

	// Buffer Type
	{
		GLint buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		fast_io::io::print(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(buff).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(buff)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" Buffer : ",
			PATATA_TERM_RESET);

		if (buff == 1)
			fast_io::io::println("Double");
		else if (buff == 0)
			fast_io::io::println("Double");
	}

	// Vsync
	{
		fast_io::io::print(PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"  [", std::string_view{ abi::__cxa_demangle(typeid(CONFIG).name(), nullptr, nullptr, nullptr) }, "]",
		#else
			"  [", std::string_view{ typeid(glGetString(CONFIG)).name() }, "]",
		#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			" Vsync : ",
			PATATA_TERM_RESET);

		if (CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
			fast_io::io::print(PATATA_TERM_COLOR_GREEN, "Yes", PATATA_TERM_RESET);
			if (CONFIG["patata-engine"]["raccoon-renderer"]["opengl-adaptative-vsync"].as<bool>())
				fast_io::io::print(PATATA_TERM_DIM, " Adaptative");
			fast_io::io::println(PATATA_TERM_RESET);
		}
		else fast_io::io::println(PATATA_TERM_COLOR_YELLOW, "No", PATATA_TERM_RESET, "\n");
	}

	// ImGui Version
	#if defined(PATATA_IMGUI_VERSION)
	fast_io::io::println(PATATA_TERM_BOLD, "  ImGui Version : ", PATATA_TERM_RESET, PATATA_IMGUI_VERSION);
	#endif

	/*
	fast_io::io::println("\n", Bold, FSteelBlue1, "    Used Extensions", Reset, Dim);

	if (strcmp(reinterpret_cast<const char *>(glGetString(GL_VENDOR)), reinterpret_cast<const char *>("ATI Technologies Inc")) != 0) {
		if (GL_AMD_performance_monitor)
			fast_io::io::println("        GL_AMD_perfomance_monitor");
	}
	fast_io::io::print(Reset);*/

	#if DEBUG
	/*fast_io::io::println("\n", Bold, FSteelBlue1, "    Available Extensions :", Reset, Dim);
		{
			GLint NumberOfExtensions = 0;
			glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

			for (GLint i = 0; i < NumberOfExtensions; i++)
				fast_io::io::println("        ", std::string_view{ reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)) });
		}*/
	#endif	

	fast_io::io::println(PATATA_TERM_RESET);
}
