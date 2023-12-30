#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <windows.h>
#include <fast_io.h>
#include <glad/gl.h>

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"

void Patata::Log::OpenGLInfo(const YAML::Node & CONFIG) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 9);
	fast_io::io::print(fast_io::out(), "OpenGL");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::println(fast_io::out(), " INFO :");

	// GPU Vendor
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(glGetString(GL_VENDOR)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(glGetString(GL_VENDOR)).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Vendor : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), std::string_view{ reinterpret_cast<const char *>(glGetString(GL_VENDOR)) });

	// GPU Name
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(glGetString(GL_RENDERER)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(glGetString(GL_RENDERER)).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Renderer : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), std::string_view{ reinterpret_cast<const char *>(glGetString(GL_RENDERER)) });

	// OpenGL Version
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(glGetIntegerv(GL_MAJOR_VERSION, 0)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(glGetIntegerv(GL_MAJOR_VERSION, 0)).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Version : ");
	{
		auto glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::println(fast_io::out(), glversion);
	}

	// GLslang or GLSL Version
	{
		auto glslang_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(glslang_version).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(glslang_version).name() }, "]");
		#endif

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), " GLslang Version : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::println(fast_io::out(), std::string_view{ reinterpret_cast<const char *>(glslang_version) });
	}

	// GLAD Loader Version
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Glad Loader Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), GLAD_GENERATOR_VERSION);

	// OpenGL Profile Context
	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(contextflags).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(contextflags).name() }, "]");
		#endif

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), " Profile : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		switch (contextflags) {
			case GL_CONTEXT_CORE_PROFILE_BIT :
				fast_io::io::println(fast_io::out(), "Core");
				break;

			case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT :
				fast_io::io::println(fast_io::out(), "Compatibility");
				break;

			default :
				fast_io::io::println(fast_io::out(), "Unknown");
				break;
		}
	}

	// Hardware Or Software Accelerated
	{
		auto accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(accel).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(accel).name() }, "]");
		#endif

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), " Accelerated Visual : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		if (accel == 1)
			fast_io::io::println(fast_io::out(), "Hardware");
		else if (accel == 0)
			fast_io::io::println(fast_io::out(), "Software");
	}

	// Buffer Type
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Buffer : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	{
		auto buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		if (buff == 1)
			fast_io::io::println(fast_io::out(), "Double");
		else if (buff == 0)
			fast_io::io::println(fast_io::out(), "Double");
	}

	// Vsync
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(CONFIG).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(CONFIG).name() }, "]");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), " Vsync : ");
	if (CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), "Yes");
		if (CONFIG["patata-engine"]["raccoon-renderer"]["opengl-adaptative-vsync"].as<bool>()) {
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			fast_io::io::print(fast_io::out(), " Adaptative");
		}
		fast_io::io::println(fast_io::out());
	}
	else {
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN);
		fast_io::io::println(fast_io::out(), "No");
	}

	// ImGui Version
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  ImGui Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_IMGUI_VERSION);

	fast_io::io::println(fast_io::out());
}
