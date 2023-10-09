#include <iostream>
#include <iomanip>
#include <ios>
#include <cstring>

#include <yaml-cpp/yaml.h>
#include <glad/gl.h>
#include <windows.h>

// Patata Engine
#include "Patata_Engine.hpp"
#include "Log.hpp"

void Patata::Log::OpenGLInfo(YAML::Node CONFIG) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 9);
	std::cout << "OpenGL Info" << std::setw(3) << ":\n";
	SetConsoleTextAttribute(Terminal, 7);

	std::cout << std::setw(4) << ' ' << "Vendor"  << std::setw(20) << ": " << glGetString(GL_VENDOR) << "\n";

	std::cout << std::setw(4) << ' ' << "Renderer" << std::setw(18) << ": " << glGetString(GL_RENDERER) << "\n";

	{
		GLint glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		std::cout << std::setw(4) << ' ' << "Version" << std::setw(19) << ": " << glversion << "\n";
	}

	std::cout << std::setw(4) << ' ' << "GLSL Version" << std::setw(14) << ": " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	std::cout << std::setw(4) << ' ' << "GLAD Version" << std::setw(14) << ": " << GLAD_GENERATOR_VERSION << "\n";

	std::cout << std::setw(4) << ' ' << "Profile" << std::setw(19) << ": ";
	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		switch (contextflags) {
			case GL_CONTEXT_CORE_PROFILE_BIT :
				std::cout << "Core\n";
				break;

			case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT :
				std::cout << "Compatibility\n";
				break;

			default :
				std::cout << "Unknown\n";
				break;
		}
	}

	std::cout << std::setw(4) << ' ' << "Accelerated Visual" << std::setw(8) << ": ";
	{
		int accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		if (accel == 1)
			std::cout << "Hardware\n";
		else if (accel == 0)
			std::cout << "Software\n";
	}

	std::cout << std::setw(4) << ' ' << "Buffer" << std::setw(20) << ": ";
	{
		int buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		if (buff == 1)
			std::cout << "Double\n";
		else if (buff == 0)
			std::cout << "Single\n";
	}

	std::cout << std::setw(4) << ' ' << "Vsync" << std::setw(21) << ": ";
	if (CONFIG["vsync"].as<bool>()) {
		SetConsoleTextAttribute(Terminal, 10);
		std::cout << "Yes\n";
		SetConsoleTextAttribute(Terminal, 7);
	}
	else {
		SetConsoleTextAttribute(Terminal, 14);
		std::cout << "No\n";
		SetConsoleTextAttribute(Terminal, 7);
	}

	SetConsoleTextAttribute(Terminal, 9);
	std::cout << "\n" << std::setw(4) << ' ' << "Used Extensions" << std::setw(3) << ":\n";
	SetConsoleTextAttribute(Terminal, 7);

	if (strcmp(reinterpret_cast<const char *>(glGetString(GL_VENDOR)), reinterpret_cast<const char *>("ATI Technologies Inc")) != 0) {
		if (GL_AMD_performance_monitor)
			std::cout << std::setw(10) << ' ' << "GL_AMD_perfomance_monitor\n";
	}

	#if DEBUG
		SetConsoleTextAttribute(Terminal, 9);
		std::cout << "\n" << std::setw(4) << ' ' << "Available Extensions" << std::setw(3) << ":\n";
		SetConsoleTextAttribute(Terminal, 7);
		{
			GLint NumberOfExtensions = 0;
			glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

			for (GLint i = 0; i < NumberOfExtensions; i++)
				std::cout << std::setw(10) << ' ' << glGetStringi(GL_EXTENSIONS, i) << "\n";
		}
	#endif	

	std::cout << "\n";
}