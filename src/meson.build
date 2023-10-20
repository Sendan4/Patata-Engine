source = files([
  'Core/Start_And_End.cpp',
  'Core/Input.cpp',
  'Core/Render.cpp',
  'Window/Window.cpp',
  'Window/Window_Icon.cpp',
  'Opengl/Opengl_Context.cpp',
  'Opengl/OpenGL_Set_ViewPort_And_Resize.cpp',
  'Opengl/OpenGL_Renderer.cpp',
  'Vulkan/Setup_Vulkan_Renderer.cpp',
  'Vulkan/Vulkan_Instance.cpp',
  'Vulkan/Vulkan_Logical_And_Queue.cpp',
  'Vulkan/Vulkan_SwapChain.cpp',
  'Vulkan/Vulkan_ImageView.cpp',
  'Vulkan/Vulkan_CommandBuffer.cpp',
  'Vulkan/Vulkan_PipeLine.cpp',
  'Vulkan/Vulkan_RenderPass.cpp',
  'Log/Mapache.cpp',
  'Log/YamlErrors.cpp',
  'Log/ErrorMessages.cpp'])

if target_machine.system() == 'windows'
  source += files([
    'Log/Win/Start_Patata_Log_Info_Win.cpp',
    'Log/Win/Window_Icon_Set_Status_Win.cpp',
    'Log/Win/Setup_Vulkan_Log_Win.cpp',
    'Log/Win/Vulkan_Info_Win.cpp',
    'Log/Win/OpenGL_Info_Win.cpp'])
else
  source += files([
    'Log/Start_Patata_Log_Info.cpp',
    'Log/Window_Icon_Set_Status.cpp',
    'Log/Setup_Vulkan_Log.cpp',
    'Log/Vulkan_Info.cpp',
    'Log/OpenGL_Info.cpp'])
endif

lib = library(meson.project_name(),
  source,
  include_directories : [include],
  d_import_dirs : [include],
  dependencies : [dependencies],
  build_by_default : true,
  install : true,
  link_args : link_arguments,
  install_dir : join_paths(meson.global_build_root(),'../bin'),
  install_rpath : join_paths(meson.global_build_root(),'../bin'),
  build_rpath : join_paths(meson.global_build_root(),'../bin'))

project_dep = declare_dependency(
  include_directories : [include],
  d_import_dirs : [include],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)
