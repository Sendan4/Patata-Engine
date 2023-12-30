#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif
#include <cstdlib>

#include <SDL_syswm.h>
#include <fast_io.h>

// Patata Engine
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::WindowLog(SDL_Window * Window) {
	#if defined(__GNUC__) || defined(__MINGW64__)
	fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(Window).name(), nullptr, nullptr, nullptr) }, "] ", LightSalmon3, Bold, "Window ", Reset, Bold, "INFO", Reset);
	#else
	fast_io::io::println(Dim, CGREY66, "[", std::string_view{ typeid(Window).name() }, "] ", LightSalmon3, Bold, "Window ", Reset, Bold, "INFO", Reset);
	#endif

	SDL_SysWMinfo WindowInfo;
	SDL_VERSION(&WindowInfo.version);
	SDL_GetWindowWMInfo(Window, &WindowInfo);
	const char * XDG_SESSION_TYPE = getenv("XDG_SESSION_TYPE");

	switch(WindowInfo.subsystem) {
		case SDL_SYSWM_WAYLAND:
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::println(Bold, "  Window System : ", Reset, "Wayland ", Dim, CGREY66, "[(", std::string_view{ abi::__cxa_demangle(typeid(XDG_SESSION_TYPE).name(), nullptr, nullptr, nullptr) },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
			fast_io::io::println(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(WindowInfo.info.wl.display).name(), nullptr, nullptr, nullptr) }, "]", Reset, Bold, " Window Type", Reset);
			fast_io::io::println(Dim, CGREY66,"  [", std::string_view{ abi::__cxa_demangle(typeid(WindowInfo.info.wl.surface).name(), nullptr, nullptr, nullptr) }, "]", Reset, Bold, " Surface Type", Reset);
			#else
			fast_io::io::println(Bold, "  Window System : ", Reset, "Wayland ", Dim, CGREY66, " [(", std::string_view{ typeid(XDG_SESSION_TYPE).name() },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
			fast_io::io::println(Dim, CGREY66, "  [", std::string_view{ typeid(WindowInfo.info.wl.display).name() }, "]", Reset, Bold, " Window Type", Reset);
			fast_io::io::println(Dim, CGREY66,"  [", std::string_view{ typeid(WindowInfo.info.wl.surface).name() }, "]", Reset, Bold, " Surface Type", Reset);
			#endif
			break;

		#if defined(PATATA_LINUX_XORG_SUPPORT) && defined(SDL_VIDEO_DRIVER_X11)
		case SDL_SYSWM_X11:
			if (strcmp(XDG_SESSION_TYPE, "wayland") == 0)
				#if defined(__GNUC__) || defined(__MINGW64__)
				fast_io::io::println(Bold, "  Window System : ", Reset, "XWayland", Dim, CGREY66, " [(", std::string_view{ abi::__cxa_demangle(typeid(XDG_SESSION_TYPE).name(), nullptr, nullptr, nullptr) },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
				#else
				fast_io::io::println(Bold, "  Window System : ", Reset, "XWayland", Dim, CGREY66, " [(", std::string_view{ typeid(XDG_SESSION_TYPE).name() },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
				#endif
			else {
				#if defined(__GNUC__) || defined(__MINGW64__)
				fast_io::io::println(Bold, "  Window System : ", Reset, "X11", Dim, CGREY66, " [(", std::string_view{ abi::__cxa_demangle(typeid(XDG_SESSION_TYPE).name(), nullptr, nullptr, nullptr) },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
				fast_io::io::println(Dim, CGREY66, "  [", std::string_view{ abi::__cxa_demangle(typeid(WindowInfo.info.x11.window).name(), nullptr, nullptr, nullptr) }, "]", Reset, Bold, " Window Type", Reset);
				fast_io::io::println(Dim, CGREY66,"  [", std::string_view{ abi::__cxa_demangle(typeid(WindowInfo.info.x11.display).name(), nullptr, nullptr, nullptr) }, "]", Reset, Bold, " Surface Type", Reset);
				#else
				fast_io::io::println(Bold, "  Window System : ", Reset, "X11 ", Dim, CGREY66, " [(", std::string_view{ typeid(XDG_SESSION_TYPE).name() },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
				fast_io::io::println(Dim, CGREY66, "  [", std::string_view{ typeid(WindowInfo.info.x11.display).name() }, "]", Reset, Bold, " Window Type", Reset);
				fast_io::io::println(Dim, CGREY66,"  [", std::string_view{ typeid(WindowInfo.info.x11.surface).name() }, "]", Reset, Bold, " Surface Type", Reset);
				#endif
			}
			break;
		#endif

		case SDL_SYSWM_MIR:
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::println(Bold, "  Window System : ", Reset, "Mir", Dim, CGREY66, " [(", std::string_view{ abi::__cxa_demangle(typeid(XDG_SESSION_TYPE).name(), nullptr, nullptr, nullptr) },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
			#else
			fast_io::io::println(Bold, "  Window System : ", Reset, "Mir ", Dim, CGREY66, " [", std::string_view{ typeid(XDG_SESSION_TYPE).name() }," [XDG_SESSION_TYPE]] ", Reset, std::string_view { XDG_SESSION_TYPE });
			#endif
			break;
				
		default :
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::println(Bold, "  Window System : ", Reset, "Unknown", Dim, CGREY66, " [(", std::string_view{ abi::__cxa_demangle(typeid(XDG_SESSION_TYPE).name(), nullptr, nullptr, nullptr) },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
			#else
			fast_io::io::println(Bold, "  Window System : ", Reset, "Unknown ", Dim, CGREY66, " [(", std::string_view{ typeid(XDG_SESSION_TYPE).name() },") XDG_SESSION_TYPE] ", Reset, std::string_view { XDG_SESSION_TYPE });
			#endif
			break;
	}

	const char * XDG_CURRENT_DESKTOP = getenv("XDG_CURRENT_DESKTOP");

	if (XDG_CURRENT_DESKTOP != nullptr)
		#if defined(__GNUC__) || defined(__MINGW64__)
		fast_io::io::println(Dim, CGREY66, "  [(", std::string_view{ abi::__cxa_demangle(typeid(XDG_CURRENT_DESKTOP).name(), nullptr, nullptr, nullptr) },") XDG_CURRENT_DESKTOP]", Reset, Bold, " Desktop : ", Reset, std::string_view{ XDG_CURRENT_DESKTOP }, "\n");
		#else
		fast_io::io::println(Dim, CGREY66, "  [(", std::string_view{ typeid(XDG_CURRENT_DESKTOP).name() },") XDG_CURRENT_DESKTOP]", Reset, Bold, " Desktop : ", Reset, std::string_view{ XDG_CURRENT_DESKTOP }, "\n");
		#endif
}

