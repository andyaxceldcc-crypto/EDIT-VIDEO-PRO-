# EDIT-VIDEO-PRO-COMPOSITOR

**Compositor VFX Profesional basado en Nuke**

> Aplicación de composición nodal de nivel profesional para producción VFX, diseñada con arquitectura modular C++ y Python.

## 🎬 Características Principales

### Interfaz Profesional
- **Dark Theme VFX** - Interfaz oscura optimizada para trabajo VFX profesional
- **Node Graph Avanzado** - Sistema de nodos interconectables tipo Nuke
- **Viewer Interactivo** - Visor de alta precisión con LUT en tiempo real
- **Timeline Profesional** - Control temporal completo
- **Panel de Propiedades** - Inspector dinámico de parámetros
- **Histograma y Scopes** - Herramientas de color profesionales

### Nodos Disponibles
- **Read** - Lectura de imágenes y secuencias EXR
- **Write** - Escritura de resultados con opciones avanzadas
- **Merge** - Composición con múltiples operaciones blend
- **Transform** - Transformaciones 2D (escala, rotación, translación)
- **Blur** - Desenfoque Gaussian y motion blur
- **Grade** - Corrección de color y curvas
- **Keyer** - Chroma key y luminance key
- **Roto** - Rotomación con splines
- **Tracker** - Seguimiento de movimiento 2D/3D

### Arquitectura Técnica
- **Backend**: C++ con multithreading
- **Interfaz**: Qt/PySide2
- **Rendering**: OpenGL + GPU acceleration
- **Color Management**: OpenColorIO (OCIO)
- **Formato de Imagen**: OpenEXR
- **Sistema de Plugins**: Arquitectura extensible

## 📁 Estructura del Proyecto

```
EDIT-VIDEO-PRO-/
├── src/
│   ├── core/              # Motor de composición
│   ├── nodes/             # Sistema de nodos
│   ├── ui/                # Interfaz gráfica (Qt/PySide)
│   ├── rendering/         # Motor de renderizado GPU
│   ├── colorspace/        # OCIO integration
│   └── plugins/           # API de plugins
├── python/
│   ├── bindings/          # PyQt/PySide bindings
│   ├── api/               # Python API
│   └── scripts/           # Utilidades Python
├── resources/
│   ├── icons/             # Iconografía profesional
│   ├── themes/            # Temas de interfaz
│   └── shaders/           # Shaders GLSL
├── tests/
│   ├── unit/              # Tests unitarios
│   └── integration/       # Tests de integración
├── docs/
│   ├── architecture.md    # Documentación de arquitectura
│   ├── node-dev.md        # Guía de desarrollo de nodos
│   └── plugin-dev.md      # Guía de desarrollo de plugins
├── cmake/
│   ├── FindOpenEXR.cmake
│   ├── FindOCIO.cmake
│   └── FindOpenGL.cmake
├── CMakeLists.txt
├── requirements.txt
└── ROADMAP.md
```

## 🚀 Quick Start

### Requisitos
- CMake 3.16+
- C++17
- Qt 5.15+ o PySide2
- OpenEXR 2.5+
- OpenColorIO 2.0+
- CUDA 11+ (opcional, para GPU acceleration)

### Compilación

```bash
# Clonar repositorio
git clone https://github.com/andyaxceldcc-crypto/EDIT-VIDEO-PRO-.git
cd EDIT-VIDEO-PRO-

# Crear directorio de build
mkdir build && cd build

# Configurar con CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Compilar
cmake --build . --config Release -j$(nproc)

# Instalar
cmake --install .
```

### Ejecución

```bash
# Ejecutar aplicación
./EDIT-VIDEO-PRO

# O con Python
python3 -m edit_video_pro
```

## 🏗️ Arquitectura del Sistema

### Core Engine (C++)
- **NodeGraph**: Gestión de dependencias y DAG
- **CompositionEngine**: Motor de composición
- **FrameBuffer**: Gestión de buffers GPU/CPU
- **ThreadPool**: Multithreading optimizado

### Rendering Pipeline
1. **Compile** - Optimización del DAG
2. **Render** - Procesamiento en GPU
3. **Composite** - Mezcla de resultados
4. **Output** - Envío al visor

### Python Integration
- Acceso a C++ via bindings
- Scripting de workflows
- Plugins Python
- API completa de nodos

## 📊 Sistema de Nodos

Cada nodo implementa:
- **Inputs**: Conectores de entrada tipados
- **Outputs**: Conectores de salida
- **Properties**: Panel de propiedades dinámico
- **Knobs**: Parámetros ajustables
- **Compute**: Lógica de procesamiento

## 🎨 Interfaz de Usuario

### Componentes Principales
- **NodeGraph Widget** - Edición visual de nodos
- **Viewer Widget** - Visor de composición
- **Properties Panel** - Inspector de parámetros
- **Timeline** - Control temporal
- **Scopes Panel** - Análisis de color

## 🔌 Sistema de Plugins

Desarrolla plugins personalizados:

```python
from edit_video_pro.plugin import Node, Input, Output

class CustomNode(Node):
    def __init__(self):
        super().__init__()
        self.add_input("input", InputType.IMAGE)
        self.add_output("output", OutputType.IMAGE)
    
    def compute(self, frame):
        # Tu lógica aquí
        return processed_frame
```

## 📈 Roadmap

### Fase 1: MVP (Semanas 1-4)
- [x] Arquitectura base
- [x] Node Graph básico
- [x] Nodos esenciales (Read, Write, Merge)
- [x] Viewer simple

### Fase 2: Funcionalidad Core (Semanas 5-8)
- [ ] Todos los nodos principales
- [ ] Timeline funcional
- [ ] GPU acceleration
- [ ] Sistema de plugins

### Fase 3: Optimización (Semanas 9-12)
- [ ] Profiling y optimización
- [ ] Caché de frames
- [ ] Render distribuido
- [ ] Performance profesional

### Fase 4: Producción (Semanas 13+)
- [ ] Testing exhaustivo
- [ ] Documentación completa
- [ ] Integración con VCS
- [ ] Stabilidad de producción

## 📚 Documentación

- [Arquitectura Detallada](docs/architecture.md)
- [Guía de Desarrollo de Nodos](docs/node-dev.md)
- [API de Plugins](docs/plugin-dev.md)
- [Build Instructions](docs/build.md)

## 🤝 Contribuir

```bash
git checkout -b feature/nueva-caracteristica
# Hacer cambios
git commit -am "Descripción clara"
git push origin feature/nueva-caracteristica
```

## 📄 Licencia

MIT License - Ver LICENSE.md

## 👥 Equipo

**Equipo Senior VFX Engineering**
- Director Técnico
- Ingenieros C++
- Especialistas GPU
- Ingenieros de UI/UX

---

**Estado**: 🚧 En Desarrollo Activo  
**Versión**: 0.1.0-alpha  
**Última Actualización**: 2026-06-06
