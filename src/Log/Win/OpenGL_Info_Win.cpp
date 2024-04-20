#include "OpenGL_Info.hpp"

void Patata::Log::OpenGLInfo(const YAML::Node & CONFIG) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(Terminal, &mode);
	SetConsoleMode(Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);

	fast_io::io::println(fast_io::out(),
		PATATA_TERM_COLOR_PATATA,
		"Raccoon Renderer",
		PATATA_TERM_COLOR_WHITE,
		" INFO :");

	// Backend
	fast_io::io::println(fast_io::out(),
		PATATA_TERM_COLOR_WHITE,
		"  Graphics Backend : ",
		PATATA_TERM_COLOR_BLUE,
		"OpenGL",
		PATATA_TERM_RESET);

	// GPU Vendor
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
		"  [", std::string_view{ abi::__cxa_demangle(typeid(glGetString(GL_VENDOR)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ typeid(glGetString(GL_VENDOR)).name() }, "]");
	#endif

	fast_io::io::println(fast_io::out(),
		PATATA_TERM_COLOR_WHITE,
		" Device Vendor : ",
		PATATA_TERM_COLOR_GRAY1,
		std::string_view{ reinterpret_cast<const char *>(glGetString(GL_VENDOR)) });

	// GPU Name
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ abi::__cxa_demangle(typeid(glGetString(GL_RENDERER)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ typeid(glGetString(GL_RENDERER)).name() }, "]");
	#endif

	fast_io::io::println(fast_io::out(),
		PATATA_TERM_COLOR_WHITE,
		" Device Name : ",
		PATATA_TERM_COLOR_GRAY1,
		std::string_view{ reinterpret_cast<const char *>(glGetString(GL_RENDERER)) });

	// OpenGL Version
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ abi::__cxa_demangle(typeid(glGetIntegerv(GL_MAJOR_VERSION, 0)).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ typeid(glGetIntegerv(GL_MAJOR_VERSION, 0)).name() }, "]");
	#endif

	fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, " Version : ");
	{
		auto glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_GRAY1, glversion);
	}

	// GLslang or GLSL Version
	{
		auto glslang_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
				"  [", std::string_view{ abi::__cxa_demangle(typeid(glslang_version).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
				"  [", std::string_view{ typeid(glslang_version).name() }, "]");
		#endif

		fast_io::io::println(fast_io::out(),
			PATATA_TERM_COLOR_WHITE,
			" GLslang Version : ",
			PATATA_TERM_COLOR_GRAY1,
			std::string_view{ reinterpret_cast<const char *>(glslang_version) });
	}

	// GLAD Loader Version
	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Glad Loader Version : ", PATATA_TERM_COLOR_GRAY1, GLAD_GENERATOR_VERSION);

	// OpenGL Profile Context
	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
				"  [", std::string_view{ abi::__cxa_demangle(typeid(contextflags).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
				"  [", std::string_view{ typeid(contextflags).name() }, "]");
		#endif

		fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, " Profile : ", PATATA_TERM_COLOR_GRAY1);

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

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
				"  [", std::string_view{ abi::__cxa_demangle(typeid(accel).name(), nullptr, nullptr, nullptr) }, "]");
		#else
			fast_io::io::print(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
				"  [", std::string_view{ typeid(accel).name() }, "]");
		#endif

		fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, " Accelerated Visual : ", PATATA_TERM_COLOR_GRAY1);

		if (accel == 1)
			fast_io::io::println(fast_io::out(), "Hardware");
		else if (accel == 0)
			fast_io::io::println(fast_io::out(), "Software");
	}

	// Buffer Type
	fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Buffer : ", PATATA_TERM_COLOR_GRAY1);
	{
		auto buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		if (buff == 1)
			fast_io::io::println(fast_io::out(), "Double");
		else if (buff == 0)
			fast_io::io::println(fast_io::out(), "Double");
	}

	// Vsync
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ abi::__cxa_demangle(typeid(CONFIG).name(), nullptr, nullptr, nullptr) }, "]");
	#else
		fast_io::io::print(fast_io::out(),
			PATATA_TERM_COLOR_GRAY0,
			"  [", std::string_view{ typeid(CONFIG).name() }, "]");
	#endif

	fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, " Vsync : ");
	if (CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
		fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_GREEN, "Yes");
		if (CONFIG["patata-engine"]["raccoon-renderer"]["opengl-adaptative-vsync"].as<bool>()) {
			fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_GRAY0, " Adaptative");
		}
		fast_io::io::println(fast_io::out());
	}
	else {
		fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_YELLOW, "No");
	}

	// ImGUI Version
	#if defined(PATATA_IMGUI_VERSION)
		fast_io::io::println(fast_io::out(),
			PATATA_TERM_COLOR_WHITE,
			"  ImGui Version : ",
			PATATA_TERM_COLOR_GRAY1,
			PATATA_IMGUI_VERSION);
	#endif

	fast_io::io::println(fast_io::out(), PATATA_TERM_RESET);
	SetConsoleMode(Terminal, mode);
}
