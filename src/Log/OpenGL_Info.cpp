#include <cstring>

#include <fast_io.h>
#include <yaml-cpp/yaml.h>
#include <glad/gl.h>

// Patata Engine
#include "PatataEngine/TerminalColors.hpp"
#include "PatataEngine/Log.hpp"

void Patata::Log::OpenGLInfo(YAML::Node CONFIG) {
	fast_io::io::println(Bold, FSteelBlue1, "OpenGL Info : ", Reset);

	fast_io::io::println(Bold, "    Vendor                  : ", Reset, std::string_view{ reinterpret_cast<const char *>(glGetString(GL_VENDOR)) });
	fast_io::io::println(Bold, "    Renderer                : ", Reset, std::string_view{ reinterpret_cast<const char *>(glGetString(GL_RENDERER)) });

	{
		GLint glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		fast_io::io::println(Bold, "    Version                 : ", Reset, glversion);
	}
	fast_io::io::println(Bold, "    GLSL Version            : ", Reset, std::string_view{ reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)) });
	fast_io::io::println(Bold, "    GLAD Version            : ", Reset, GLAD_GENERATOR_VERSION);

	fast_io::io::print(Bold, "    Profile                 : ", Reset);
	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

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

	fast_io::io::print(Bold, "    Accelerated Visual      : ", Reset);
	{
		int accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		if (accel == 1)
			fast_io::io::println("Hardware");
		else if (accel == 0)
			fast_io::io::println("Software");
	}

	fast_io::io::print(Bold, "    Buffer                  : ", Reset);
	{
		int buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		if (buff == 1)
			fast_io::io::println("Double");
		else if (buff == 0)
			fast_io::io::println("Double");
	}

	fast_io::io::print(Bold, "    Vsync                   : ", Reset);
	if (CONFIG["vsync"].as<bool>())
		fast_io::io::println(Chartreuse1, "Yes", Reset);
	else
		fast_io::io::println(BLightGoldenRod1, "No", Reset, "\n");

	fast_io::io::println("\n", Bold, FSteelBlue1, "    Used Extensions", Reset, Dim);

	if (strcmp(reinterpret_cast<const char *>(glGetString(GL_VENDOR)), reinterpret_cast<const char *>("ATI Technologies Inc")) != 0) {
		if (GL_AMD_performance_monitor)
			fast_io::io::println("        GL_AMD_perfomance_monitor");
	}
	fast_io::io::print(Reset);

	#if DEBUG
	fast_io::io::println("\n", Bold, FSteelBlue1, "    Available Extensions :", Reset, Dim);
		{
			GLint NumberOfExtensions = 0;
			glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

			for (GLint i = 0; i < NumberOfExtensions; i++)
				fast_io::io::println("        ", std::string_view{ reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)) });
		}
	#endif	

	fast_io::io::println(Reset);
}
