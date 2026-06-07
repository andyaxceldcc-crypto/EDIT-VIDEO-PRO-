

# NUKE-PRO - Compositor Profesional de VFX

## Descripción
NUKE-PRO es un compositor profesional de VFX inspirado en Foundry Nuke, Blender y DaVinci Resolve. Construido con Qt6, OpenCV y FFmpeg.

---

## 🔗 Sistema Node-Based (Nuke-like)

Sistema de nodos inspirado en **Foundry Nuke** para construir pipelines de composición y efectos visuales.

### Archivos del Sistema

| Archivo | Descripción |
|---------|-------------|
| `src/core/nodes/node_base.h/cpp` | Clase base para todos los nodos (parámetros, conexiones, posición) |
| `src/core/nodes/node_connection.h/cpp` | Conexiones entre nodos (puertos de entrada/salida) |
| `src/core/graph/node_graph.h/cpp` | Gestor del grafo con ejecución en orden topológico |
| `src/core/nodes/viewer_node.h/cpp` | Nodo visor con múltiples modos de color |
| `src/core/nodes/grade_node.h/cpp` | Color grading profesional (Lift/Gamma/Gain) |
| `src/core/nodes/colorspace_node.h/cpp` | Conversión de espacios de color |
| `src/core/nodes/exposure_node.h/cpp` | Control de exposición |
| `src/core/nodes/curves_node.h/cpp` | Editor de curvas RGB |
| `src/core/nodes/levels_node.h/cpp` | Ajuste de niveles |
| `src/core/nodes/hue_saturation_node.h/cpp` | Matiz y saturación |
| `src/core/nodes/channel_mix_node.h/cpp` | Mezcla de canales RGB |
| `src/core/nodes/blur_node.h/cpp` | Desenfoque gaussiano y de movimiento |
| `src/core/nodes/merge_node.h/cpp` | Fusión de capas |
| `src/core/nodes/transform_node.h/cpp` | Transformaciones 2D |
| `src/core/nodes/keyer_node.h/cpp` | Extraer mate por croma |
| `src/core/nodes/roto_node.h/cpp` | Rotoscopia con splines |
| `src/core/nodes/tracker_node.h/cpp` | Seguimiento de movimiento |
| `src/core/write_node.h/cpp` | Nodo de salida/escritura |

### Cómo Crear un Pipeline (Ejemplo)

```cpp
// Crear el grafo
NodeGraph graph;

// Crear nodos
ViewerNode* read = new ViewerNode("entrada");
GradeNode* grade = new GradeNode("color");
WriteNode* write = new WriteNode("output.mp4");

// Añadir nodos al grafo
graph.addNode(read);
graph.addNode(grade);
graph.addNode(write);

// Conectar nodos (output -> input)
graph.createConnection(read, 0, grade, 0);
graph.createConnection(grade, 0, write, 0);

// Ejecutar pipeline
graph.executeFrame(0);
```

### Compilación

```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="/ruta/a/Qt/6.6.2"
cmake --build . --config Release
```

### Notas y Limitaciones

- ⚠️ Implementación de ejemplo/didáctica: las operaciones de E/S son simuladas (placeholders)
- Para producción: integrar FFmpeg/libav o APIs de GPU
- El orden de ejecución usa topological sort simple
- Puede mejorarse con detección de ciclos robusta

---

## Requisitos

- Qt 6.x (Core, Gui, Widgets, Multimedia, Network, Sql, Concurrent, OpenGL)
- OpenCV 4.x
- FFmpeg (libavcodec, libavformat, libavutil, libswscale)
- CMake 3.16+
- C++17

---

## Estructura del Proyecto

```
NUKE-PRO/
├── src/
│   ├── main.cpp
│   ├── core/
│   │   ├── graph/node_graph.h/cpp
│   │   └── nodes/
│   │       ├── node_base.h/cpp
│   │       ├── node_connection.h/cpp
│   │       └── [nodos de procesamiento]
│   ├── ui/
│   │   ├── main_window.h/cpp
│   │   ├── theme/dark_theme.h/cpp
│   │   └── panels/
│   └── [módulos legacy]
├── CMakeLists.txt
├── compile.sh
└── README.md
```

---

## Próximos Pasos

- [ ] Integrar lectura/escritura real con FFmpeg
- [ ] Añadir ejecutable de test que compile automáticamente
- [ ] Soporte para nodos de rotoscopia avanzada
- [ ] Nodos de tracking con detección de movimiento
- [ ] Integración con GPU (OpenGL/Vulkan)
