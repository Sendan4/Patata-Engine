#include <cstring>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <glad/gl.h>

// Patata Engine
#include "TerminalColors.hpp"
#include "Log.hpp"

void Patata::Log::OpenGLInfo(const YAML::Node & CONFIG) {
	fast_io::io::println(Bold, FSteelBlue1, "OpenGL ", Reset, Bold, "INFO");

	// GPU Vendor
	{
		auto Vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(Vendor).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(Vendor)).name() }, "]", Reset);
		#endif
		fast_io::io::println(Bold, " Vendor : ", Reset, std::string_view{ Vendor });
	}

	// GPU Name
	{
		auto Name = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(Name).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(Name)).name() }, "]", Reset);
		#endif
		fast_io::io::println(Bold, " Renderer : ", Reset, std::string_view{ Name });
	}

	// OpenGL Version
	{
		GLint glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(glmayorversion).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(glmayorversion)).name() }, "]", Reset);
		#endif

		fast_io::io::println(Bold, " Version : ", Reset, glversion);
	}

	// GLslang or GLSL Version
	{
		auto GLslang = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(GLslang).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(GLslang)).name() }, "]", Reset);
		#endif

		fast_io::io::println(Bold, " GLslang Version : ", Reset, std::string_view{ GLslang });
	}

	// GLAD Loader Version
	fast_io::io::println(Bold, "  GLAD Loader Version : ", Reset, GLAD_GENERATOR_VERSION);

	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(contextflags).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(contextflags)).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Profile : ", Reset);

		switch (contextflags) {
			case GL_CONTEXT_CORE_PROFILE_BIT :
				fast_io::io::println("Core");
				break;

			case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT :
				fast_io::io::println("Compatibility");
				break;

			default :
				fast_io::io::println("Unknown");
				break;
		}
	}

	// Hardware Or Software Accelerated
	{
		GLint accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(accel).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(accel)).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Accelerated Visual : ", Reset);

		if (accel == 1)
			fast_io::io::println("Hardware");
		else if (accel == 0)
			fast_io::io::println("Software");
	}

	// Buffer Type
	{
		GLint buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(buff).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(buff)).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Buffer : ", Reset);

		if (buff == 1)
			fast_io::io::println("Double");
		else if (buff == 0)
			fast_io::io::println("Double");
	}

	// Vsync
	{
		#if defined(__GNUC__) || defined(__MINGW64__)	
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(CONFIG).name(), nullptr, nullptr, nullptr) }, "]", Reset);
		#else
			fast_io::io::print(Dim, CGREY66, "  [", std::string_view{ typeid(glGetString(CONFIG)).name() }, "]", Reset);
		#endif

		fast_io::io::print(Bold, " Vsync : ", Reset);

		if (CONFIG["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
			fast_io::io::print(Chartreuse1, "Yes", Reset);
			if (CONFIG["patata-engine"]["raccoon-renderer"]["opengl-adaptative-vsync"].as<bool>())
				fast_io::io::print(Dim, " Adaptative");
			fast_io::io::println(Reset);
		}
		else fast_io::io::println(BLightGoldenRod1, "No", Reset, "\n");
	}

	// ImGui Version
	#if defined(PATATA_IMGUI_VERSION)
	fast_io::io::println(Bold, "  ImGui Version : ", Reset, PATATA_IMGUI_VERSION);
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

	fast_io::io::println(Reset);
}
