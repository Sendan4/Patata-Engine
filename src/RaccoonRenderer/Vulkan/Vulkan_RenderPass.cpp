#include <fast_io.h>

#include "PatataEngine/Graphics/RaccoonRenderer.hpp"
#include "Log.hpp"

void Patata::Graphics::RaccoonRenderer::VulkanBackend::CreateRenderPass(void) {
	// Color
	vk::AttachmentDescription CreateColorAttachmentDescription {};
	CreateColorAttachmentDescription.format = ColorFormat;
	CreateColorAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
	CreateColorAttachmentDescription.storeOp = vk::AttachmentStoreOp::eStore;
	CreateColorAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
	CreateColorAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
	CreateColorAttachmentDescription.finalLayout = vk::ImageLayout::ePresentSrcKHR;
	// Depth
	vk::AttachmentDescription CreateDepthAttachmentDescription {};
	CreateDepthAttachmentDescription.format = vk::Format::eD32SfloatS8Uint;
	CreateDepthAttachmentDescription.loadOp = vk::AttachmentLoadOp::eClear;
	CreateDepthAttachmentDescription.storeOp = vk::AttachmentStoreOp::eDontCare;
	CreateDepthAttachmentDescription.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
	CreateDepthAttachmentDescription.initialLayout = vk::ImageLayout::eUndefined;
	CreateDepthAttachmentDescription.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

	std::vector <vk::AttachmentDescription> Attachments;
	Attachments.push_back(CreateColorAttachmentDescription);
	Attachments.push_back(CreateDepthAttachmentDescription);

	// Color
	vk::AttachmentReference CreateColorAttachmentReference (0, vk::ImageLayout::eColorAttachmentOptimal);
	// Depth
	vk::AttachmentReference CreateDepthAttachmentReference (1, vk::ImageLayout::eDepthStencilAttachmentOptimal);

	vk::SubpassDescription CreateSubpassDescription {};
	CreateSubpassDescription.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
	CreateSubpassDescription.inputAttachmentCount = 0;
	CreateSubpassDescription.pInputAttachments = nullptr;
	CreateSubpassDescription.colorAttachmentCount = 1;
	CreateSubpassDescription.pColorAttachments = &CreateColorAttachmentReference;
	CreateSubpassDescription.pDepthStencilAttachment = &CreateDepthAttachmentReference;

	std::vector <vk::SubpassDependency> Dep = {
		vk::SubpassDependency(
			~0U,
			0,
			vk::PipelineStageFlagBits::eBottomOfPipe,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::AccessFlagBits::eMemoryRead,
			vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite,
			vk::DependencyFlagBits::eByRegion
		),
		vk::SubpassDependency(
			0,
			~0U,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::PipelineStageFlagBits::eBottomOfPipe,
			vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite,
			vk::AccessFlagBits::eMemoryRead,
			vk::DependencyFlagBits::eByRegion
	)};	

	vk::RenderPassCreateInfo CreateRenderPassInfo {};
	CreateRenderPassInfo.attachmentCount = Attachments.size();
	CreateRenderPassInfo.pAttachments = Attachments.data();
	CreateRenderPassInfo.subpassCount = 1;
	CreateRenderPassInfo.pSubpasses = &CreateSubpassDescription;
	CreateRenderPassInfo.dependencyCount = static_cast<uint32_t>(Dep.size());
	CreateRenderPassInfo.pDependencies = Dep.data();
	
	vk::Result Result = Device.createRenderPass(&CreateRenderPassInfo, nullptr, &RenderPass);
	Patata::Log::VulkanCheck("RenderPass", Result);
}
