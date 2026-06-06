# NUKE-PRO Installation Guide

## Requisitos del Sistema

### Mínimos
- OS: Windows 10/11, macOS 10.14+, Linux (Ubuntu 20.04+)
- CPU: Intel Core i7 / AMD Ryzen 5 o superior
- RAM: 8GB (16GB recomendado)
- GPU: NVIDIA (CUDA 11.8+) | AMD (HIP) | Intel (Xe)
- Storage: 2GB espacio libre

### Recomendados
- CPU: Intel Xeon W / AMD Threadripper
- RAM: 32GB+
- GPU: NVIDIA RTX 4000+ con 24GB+ VRAM
- Storage: SSD NVMe para caché

## Dependencias Necesarias

### Windows
```bash
# Visual Studio 2022 or MinGW
# CMake 3.20+
# Python 3.9+
# CUDA Toolkit 11.8
# Qt 6.5
```

### macOS
```bash
brew install cmake python qt6 openexr
```

### Linux (Ubuntu)
```bash
sudo apt-get install cmake python3 python3-dev qt6-base-dev \
  libopenexr-dev libocio-dev libopencv-dev
```

## Compilación

### 1. Clonar Repositorio
```bash
git clone https://github.com/andyaxceldcc-crypto/EDIT-VIDEO-PRO-.git
cd EDIT-VIDEO-PRO-
git checkout develop/vfx-compositor
```

### 2. Crear Directorio de Build
```bash
mkdir build
cd build
```

### 3. Configurar CMake

#### Con GPU (CUDA)
```bash
cmake -DCMAKE_BUILD_TYPE=Release \
      -DENABLE_CUDA=ON \
      -DCUDA_ARCH_BIN="75 86" \
      ..
```

#### Sin GPU
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### 4. Compilar
```bash
# Linux/macOS
cmake --build . --config Release -j$(nproc)

# Windows (MSVC)
cmake --build . --config Release -j%NUMBER_OF_PROCESSORS%
```

### 5. Instalar
```bash
cmake --install . --prefix /path/to/install
```

## Instalación Python

### Crear Entorno Virtual
```bash
python3 -m venv venv
source venv/bin/activate  # Linux/macOS
# o
venv\Scripts\activate  # Windows
```

### Instalar Dependencias
```bash
pip install -r requirements.txt
```

## Ejecución

### Desde Build Directory
```bash
./bin/nuke-pro  # Linux/macOS
# o
bin\nuke-pro.exe  # Windows
```

### Desde Instalación
```bash
/path/to/install/bin/nuke-pro
```

## Troubleshooting

### CMake no encuentra Qt6
```bash
cmake -DCMAKE_PREFIX_PATH="/path/to/Qt6" ..
```

### Error con CUDA
- Verificar instalación de CUDA Toolkit
- Verificar drivers NVIDIA
```bash
nvcc --version
```

### Errores de compilación
```bash
# Limpiar build
rm -rf build
mkdir build && cd build

# Configurar nuevamente
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## Desarrollo

### Setup de Desarrollo
```bash
pip install -r requirements-dev.txt
```

### Tests
```bash
cd build
ctest --verbose
```

### Debug
```bash
gdb ./bin/nuke-pro
```

## Configuración de IDEs

### Visual Studio Code
```json
{
  "cmake.configureOnOpen": true,
  "cmake.buildDirectory": "${workspaceFolder}/build",
  "cmake.sourceDirectory": "${workspaceFolder}"
}
```

### CLion
- Open as CMake project
- Configure run targets

## Documentación Adicional

- [Build System](./BUILD.md)
- [Plugin Development](./PLUGIN_DEVELOPMENT.md)
- [Python Scripting](./PYTHON_SCRIPTING.md)
