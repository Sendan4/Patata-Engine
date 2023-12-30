project('imgui', 'cpp',
  version : '1.90',
  meson_version : '>=1.2.0')

dependencies = []

if get_option('use_external_libs') == true and build_machine.system() != 'windows'
  cmake = import('cmake')

  buildtypeforcmake = ''
  if get_option('buildtype') == 'debug'
    buildtypeforcmake = 'Debug'
  elif get_option('buildtype') == 'debugoptimized'
    buildtypeforcmake = 'RelWithDebInfo'
  elif get_option('buildtype') == 'release'
    buildtypeforcmake = 'Release'
  elif get_option('buildtype') == 'minsize'
    buildtypeforcmake = 'MinSizeRel'
  endif

  vk_opt = cmake.subproject_options()
  vk_opt.add_cmake_defines(
    { 'UPDATE_DEPS' : true },
    { 'BUILD_TESTS' : false },
    { 'CMAKE_INSTALL_PREFIX' : join_paths(meson.global_build_root(), '../bin') },
    { 'CMAKE_INSTALL_LIBDIR' : '.' },
    { 'CMAKE_BUILD_TYPE' : buildtypeforcmake })

  if get_option('xorg_support') == false
    vk_opt.add_cmake_defines(
      { 'BUILD_WSI_XCB_SUPPORT' : false },
      { 'BUILD_WSI_XLIB_SUPPORT' : false })
  endif

  if build_machine.system() == 'linux'
    vk_opt.add_cmake_defines({ 'BUILD_WSI_WAYLAND_SUPPORT' : true })
  endif

  vk = cmake.subproject('Vulkan-Loader', options : vk_opt)
  Vulkan = vk.dependency('vulkan')

  sdl2_opt = cmake.subproject_options()
  sdl2_opt.add_cmake_defines(
    { 'CMAKE_INSTALL_PREFIX' : join_paths(meson.global_build_root(), '../bin/') },
    { 'CMAKE_INSTALL_LIBDIR' : '.' },
    { 'CMAKE_BUILD_TYPE' : buildtypeforcmake },
    { 'SDL_TEST' : false },
    { 'SDL_DIRECTX' : false },
    { 'SDL_RENDER_D3D' : false },
    { 'SDL_OPENGLES' : false },
    { 'SDL_SHARED' : true }, { 'SDL_STATIC' : false })

  if get_option('xorg_support') == false
    sdl2_opt.add_cmake_defines(
      { 'SDL_X11' : false },
      { 'SDL_X11_SHARED' : false })
  endif

  vkh_opt = cmake.subproject_options()
  vkh_opt.add_cmake_defines(
    { 'BUILD_TESTS' : false },
    { 'CMAKE_INSTALL_PREFIX' : join_paths(meson.global_build_root(), '../bin') },
    { 'CMAKE_INSTALL_LIBDIR' : '.' },
    { 'CMAKE_BUILD_TYPE' : buildtypeforcmake })
  vkh = cmake.subproject('Vulkan-Headers', options : vkh_opt)
  Vulkan_Headers = vkh.dependency('Vulkan-Headers')

  sdl2 = cmake.subproject('SDL', options : sdl2_opt)
  sdl2_dep = sdl2.dependency('SDL2')

  dependencies += [Vulkan_Headers]
else
    sdl2_dep = dependency('sdl2',
        required : true,
        static : false,
        version : '>=2.24.1',
        modules : ['SDL2::SDL2'])

    Vulkan = dependency('Vulkan',
        static : false,
        required : true)
endif

dependencies += [Vulkan, sdl2_dep]

meson.get_compiler('cpp').check_header('stdio.h', required : true)
meson.get_compiler('cpp').check_header('stdint.h', required : true)
meson.get_compiler('cpp').check_header('float.h', required : true)
meson.get_compiler('cpp').check_header('stdarg.h', required : true)
meson.get_compiler('cpp').check_header('stddef.h', required : true)
meson.get_compiler('cpp').check_header('string.h', required : true)
meson.get_compiler('cpp').check_header('assert.h', required : false)
meson.get_compiler('cpp').check_header('stdlib.h', required : true)
meson.get_compiler('cpp').check_header('limits.h', required : true)
meson.get_compiler('cpp').check_header('math.h', required : true)

if target_machine.system() == 'windows'
  meson.get_compiler('cpp').check_header('Windows.h', required : true)
endif

Sources = ['imgui.cpp',
    'imgui_draw.cpp',
    'imgui_demo.cpp',
    'imgui_tables.cpp',
    'imgui_widgets.cpp',
    'backends/imgui_impl_opengl3.cpp']

Include = include_directories('.')

backends = include_directories('backends/')
backends_str = 'OpenGL, '

if Vulkan.found() or get_option('use_external_libs') == true
    meson.get_compiler('cpp').check_header('vulkan/vulkan.h', required : true)
    Sources += ['backends/imgui_impl_vulkan.cpp']
    backends_str += 'Vulkan, '
endif

if sdl2_dep.found() or get_option('use_external_libs') == true
    Sources += ['backends/imgui_impl_sdl2.cpp']
    backends_str += 'SDL2'
endif

librarytype = ''

force_static = false
if get_option('use_external_libs') == true and get_option('libs_shared_build') == true and build_machine.system() != 'windows'
    if get_option('use_external_libs') == true
        warning('Prefer the library type as static for ImGui')
    endif

    force_static = true
endif

if get_option('libs_shared_build') == true and force_static == false
    lib = shared_library(meson.project_name(),
        Sources,
        include_directories : [Include, backends],
        d_import_dirs : [Include, backends],
        dependencies : [dependencies],
        soversion : meson.project_version(),
        install : true,
        install_dir : join_paths(meson.global_build_root(),'../bin'))

    librarytype = 'Shared'
elif get_option('libs_shared_build') == false or force_static == true
    lib = static_library(meson.project_name(),
        Sources,
        include_directories : [Include, backends],
        d_import_dirs : [Include, backends],
        dependencies : [dependencies],
        install : true,
        install_dir : join_paths(meson.global_build_root(),'../bin'))

    librarytype = 'Static'
endif

project_dep = declare_dependency(
  include_directories : [Include, backends],
  d_import_dirs : [Include, backends],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)

# Manualy Set
Info = {
  'Backends' : backends_str,
  'OpenGL Version' : '3',
  'Build Type' : get_option('buildtype'),
  'Library Type' : librarytype
}

summary({
  'Backends' : Info['Backends'],
  'OpenGL Version' : Info['OpenGL Version']},
  bool_yn : true)

summary({
  'Build Type' : Info['Build Type'],
  'Library Type' : Info['Library Type']},
  bool_yn : true,
  section : 'Library')
