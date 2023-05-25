
Este proyecto usa Cmake y Meson para compilarse

# Linux
### Meson
Antes de configurar el proyecto asegurese de tener los paquetes necesarios para compilar.

### Fedora
```bash
sudo dnf install meson gcc gcc-c++ ninja-build git
```
### Debian

```bash
sudo apt install build-essential ninja-build g++ gcc meson git
```

y ahora obtenga las librerias.

### Fedora
```bash
sudo dnf install SDL2-devel SDL2_image-devel vulkan-headers vulkan-loader-devel vulkan-validation-layers-devel
```

## Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone el repositorio

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

si la carpeta `build` no esta creela.

```bash
mkdir build
```

configure el proyecto. `Release` es el seleccionado por defecto.

```bash
meson setup build && cd build
```

y compile con `ninja` usando varios nucleos.

```bash
ninja -j$(nproc)
```

o usando un solo nucleo.

```bash
ninja
```

encontrara el ejecutable en `build/`.

## Cmake

Antes de configurar el proyecto asegurese de tener los paquetes necesarios para compilar.

### Fedora
```bash
sudo dnf install cmake gcc gcc-c++ make.x86_64 git
```
### Debian

```bash
sudo apt install build-essential make g++ gcc cmake git
```


y ahora obtenga las librerias.

### Fedora
```bash
sudo dnf install SDL2-devel SDL2_image-devel vulkan-headers vulkan-loader-devel vulkan-validation-layers-devel
```

## Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone el repositorio

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

si la carpeta `build` no esta creela.

```bash
mkdir build && cd build
```

configure el proyecto. `Release` es el seleccionado por defecto.

```bash
cmake ..
```

Alternativamente usted puede usar ninja con cmake, asegurese de tener instalado `ninja-build`.

```bash
cmake .. -G ninja
```

para compilar con ninja usando todos los nucleos

```bash
ninja -j$(nproc)
```

Compile con `make` usando varios nucleos.

```bash
make -j$(nproc)
```

o usando un solo nucleo.

```bash
make
```

encontrara el ejecutable en `bin`

Si quiere compilar las librerias junto con Patata Engine, debe clonar el repositorio y sus submodulos.

```bash
git clone --recurse-submodules https://gitlab.com/448L/patata-engine.git
```

debe crear la carpeta build y bin si no estan.

```bash
mkdir build
mkdir bin
cd build
```

configure el proyecto con cmake.

```bash
cmake ..
```

le tocara satisfacer las dependencias para compilar librerias como `SDL2`, `SDL2_Image`, `SDL2_TTF`, `libconfig`.

### Enlazado Estatico o Enlazado dinamico
Por defecto se enlaza dinamicamente, puede usar `-DBUILD_TYPE=OFF` para tratar de enlazar las librerias que lo permitan de forma estatica.

Esto no va a enlazar todas las bibliotecas de forma estatica, debido a que hay librerias que no lo soportan, como `libvulkan`.

```-DUSE_EXTERNAL_LIBS=ON``` Para usar las librerias externas provenientes de los submodulos de git, esto compilara y enlazara las librerias externas y no las del sistema.

### Construyendo
```bash
git clone --recurse-submodules https://gitlab.com/448L/patata-engine.git && cd patata-engine
mkdir build && mkdir bin && cd build
cmake .. -DUSE_EXTERNAL_LIBS=ON
make -j$(nproc)
```
