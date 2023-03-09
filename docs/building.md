# Build

Este proyecto usa Cmake y Meson para compilarse

# Linux
## Meson

Antes de configurar el proyecto asegurese de tener los paquetes necesarios para compilar

### Fedora
```bash
sudo dnf install meson.noarch gcc.x86_64 gcc-c++.x86_64 ninja-build.x86_64 git
```
### Debian

```bash
sudo apt install build-essential ninja-build g++ gcc meson git
```


y ahora obtenga las librerias

### Fedora
```bash
sudo dnf install SDL2-devel.x86_64 SDL2_image-devel.x86_64 vulkan-headers.noarch vulkan-loader-devel.x86_64 vulkan-validation-layers-devel.x86_64
```

## Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone el repositorio

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

si la carpeta `build` no esta creela

```
mkdir build
```

configure el proyecto. `Release` es el seleccionado por defecto.

```
meson setup build && cd build
```

y compile con `ninja` usando varios nucleos

```
ninja -j$(nproc)
```

o usando un solo nucleo

```
ninja
```

encontrara el ejecutable en `build/`

## Cmake

Antes de configurar el proyecto asegurese de tener los paquetes necesarios para compilar

### Fedora
```bash
sudo dnf install cmake.x86_64 gcc.x86_64 gcc-c++.x86_64 make.x86_64 git
```
### Debian

```bash
sudo apt install build-essential make g++ gcc cmake git
```


y ahora obtenga las librerias

### Fedora
```bash
sudo dnf install SDL2-devel.x86_64 SDL2_image-devel.x86_64 vulkan-headers.noarch vulkan-loader-devel.x86_64 vulkan-validation-layers-devel.x86_64
```

## Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone el repositorio

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

si la carpeta `build` no esta creela

```
mkdir build && cd build
```

configure el proyecto. `Release` es el seleccionado por defecto.

```
cmake ..
```

- Alternativamente usted puede usar ninja con cmake, asegurese de tener instalado `ninja-build`.

- ```bash
cmake .. -G ninja
```


y compile con `make` usando varios nucleos

```
make -j$(nproc)
```

o usando un solo nucleo

```
make
```

encontrara el ejecutable en `build/`