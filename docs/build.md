# Build Guide

## Requisitos

### Sistema Operativo
- Windows 10+
- macOS 10.14+
- Linux (Ubuntu 20.04+)

### Herramientas
- CMake 3.16+
- Git 2.30+
- Visual Studio 2019+ / GCC 9+ / Clang 10+

### Librerías (apt/brew/vcpkg)
```bash
# Ubuntu/Debian
sudo apt-get install qt5-default libqt5opengl5-dev libgl1-mesa-dev
sudo apt-get install libopenexr-dev libopencolorio-dev
sudo apt-get install libglm-dev

# macOS
brew install qt5 openexr opencolorio glm

# Windows (vcpkg)
vcpkg install qt5 openexr opencolorio glm
```

### GPU (Optional)
```bash
# CUDA 11+
whget https://developer.nvidia.com/cuda-downloads
# https://docs.nvidia.com/cuda/cuda-installation-guide/
```

## Compilación

### Windows (MSVC)
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### macOS (Clang)
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(sysctl -n hw.ncpu)
```

### Linux (GCC)
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

## Instalación

```bash
# Instalar en /usr/local/ (Linux/macOS) o Program Files (Windows)
cmake --install .

# O especificar directorio
cmake --install . --prefix /custom/install/path
```

## Ejecución

```bash
# Ejecutar desde build directory
./bin/EDIT-VIDEO-PRO

# O desde install directory
/usr/local/bin/EDIT-VIDEO-PRO
```

## Build Options

```bash
# Con GPU acceleration
cmake .. -DBUILD_WITH_CUDA=ON

# Con tests
cmake .. -DBUILD_WITH_TESTS=ON
ctest

# Con Python bindings
cmake .. -DBUILD_PYTHON_BINDINGS=ON

# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

## Troubleshooting

### Qt not found
```bash
# Especificar ruta Qt
cmake .. -DQt5_DIR=/path/to/qt5/lib/cmake/Qt5
```

### OpenEXR not found
```bash
cmake .. -DOPENEXR_DIR=/path/to/openexr
```

### CUDA compilation errors
```bash
# Asegurar arquitectura GPU correcta
cmake .. -DCUDA_ARCH=sm_75  # Para RTX
```

## Performance Profiling

```bash
# Con VTune
cmake .. -DENABLE_VTUNE=ON

# Con Nvidia Nsight
cmake .. -DENABLE_NSIGHT=ON

# Con sanitizers (debug)
cmake .. -DENABLE_ASAN=ON
```
