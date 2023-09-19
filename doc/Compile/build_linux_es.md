Este proyecto usa Cmake y Meson para compilarse

# Linux
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

### Meson

configure el proyecto. `Release` es el seleccionado por defecto.

```bash
meson setup build
```

y compile con `ninja` usando varios nucleos.

```bash
meson compile -C build -j$(nproc)
```

o usando un solo nucleo.

```bash
meson compile -C build
```

encontrara el ejecutable en `build/`.

### CMake

Configure el proyecto

```bash
cmake -B build
```

compile y enlaze el programa

```bash
cmake --build build --config Release
```

si quiere usar varios nucleos

```bash
cmake --build build --config Release -j$(nproc)
```

alternativamente puede compilar las librerias junto con patata engine y enlazarlas. si hace esto, debe satisfacer las dependencias de las librerias de terceros.

pero antes, Clone el repositorio con sus submodulos.

```
git clone --recurse-submodules https://gitlab.com/Sendan/patata-engine.git
```

si ya tiene el repositorio y no tiene los submodulos

```bash
git submodule update --init --recursive
```
configure el projecto

```bash
cmake -B build -DUSE_EXTERNAL_LIBS=ON
```

tambien puede intentar hacer un enlazado estatico si es posible (no todas las librerias pueden ser enlazadas estaticamente)

```bash
cmake -B build -DUSE_EXTERNAL_LIBS=ON -DSHARED_BUILD=OFF
```
