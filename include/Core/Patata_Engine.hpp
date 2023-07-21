#pragma once
#include <cstdint>
#include <string>

#include "Core/Window.hpp"

namespace Patata {
	class PatataEngine {
		public:
			PatataEngine (std::string, uint32_t, uint32_t, bool);
			~PatataEngine (void);
			void MainLoop(void);
			void GLSwapMainLoopWrapper(void);
	};

	enum api { Vulkan = true, Opengl = false };
}

