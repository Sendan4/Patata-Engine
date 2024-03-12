#pragma once

#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <vulkan/vulkan.hpp>
#include <SDL.h>
#include <yaml-cpp/yaml.h>

namespace Patata {
	namespace Graphics {
		class RaccoonRenderer {
			public:
				RaccoonRenderer(YAML::Node &, SDL_Window *&, const bool &);
				~RaccoonRenderer(void);

				const bool * Backend = &backend;
				SDL_GLContext * GameGLContext = nullptr;

			private:
				bool backend = true;

				void RaccoonBackendInit(YAML::Node &, SDL_Window *&);

				class VulkanBackend {
					public:
						bool CreateInstance(SDL_Window *&, YAML::Node &);
						uint32_t CreateLogicalDeviceAndCreateQueue(void);
						std::tuple<vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR> CreateSwapChain(uint32_t &, YAML::Node);
						void CreateImageView(uint32_t &);
						void CreateCommandBuffer(uint32_t &);
						void CreateRenderPass(void);
						void CreatePipeline(void);
						void VulkanInfo(YAML::Node CONFIG, std::tuple<vk::PresentModeKHR, vk::Format, vk::ColorSpaceKHR>);

						VulkanBackend(SDL_Window *&, YAML::Node &);
						~VulkanBackend(void);

					private:
						vk::Instance Instance = nullptr;
						vk::SurfaceKHR Surface = nullptr;

						vk::Queue Queue;
						vk::Device Device = nullptr;
						vk::PhysicalDevice PhysicalDevice = nullptr;

						vk::CommandPool CommandPool = nullptr;
						std::vector <vk::CommandBuffer> CommandBuffers;

						vk::Format ColorFormat;
						vk::Extent2D SwapChainExtent;
						vk::PresentModeKHR PresentMode;
						vk::SurfaceFormatKHR SurfaceFormat;

						vk::Image DepthImage;

						vk::SwapchainKHR SwapChain;
						struct SwapChainBuffer {
							vk::Image Image;
							std::array <vk::ImageView, 2> Views;
							vk::Framebuffer FrameBuffer;
						};
						std::vector <SwapChainBuffer> SwapChainBuffers;

						std::vector <vk::Image> SwapChainImages;
						vk::ImageView ImageView;
						vk::DeviceMemory ImageMemory;

						vk::RenderPass RenderPass;
						vk::Semaphore Semaphore;
						vk::Semaphore RenderCompleteSemaphore;

						vk::Pipeline PipeLine;
						vk::PipelineLayout PipeLineLayout;
						vk::PipelineCache PipeLineCache;			
				} * pVulkanBackend = nullptr;

				class OpenGLBackend {
					public:	
						OpenGLBackend(YAML::Node & Config);
						~OpenGLBackend(void);

						void OpenGLResizeViewPort(SDL_Window *);
						void OpenGLSetViewPort(uint32_t, uint32_t);

					private:

			} * pOpenGLBackend = nullptr;
		};
	}
}
