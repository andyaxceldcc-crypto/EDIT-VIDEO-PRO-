# Filmora Editor Pro - Editor de Video Profesional

## Descripción
Editor de video de escritorio tipo Filmora con características profesionales, sistema de suscripción mensual ($100/mes) y exportación sin límites.

## Características

### Edición de Video
- ✅ Timeline interactivo con múltiples pistas
- ✅ Importación de videos en múltiples formatos
- ✅ Corte, fusión y edición de clips
- ✅ Vista previa en tiempo real
- ✅ Zoom y navegación en la timeline

### Efectos y Filtros
- ✅ +50 efectos profesionales
- ✅ Efectos de color (brillo, contraste, saturación)
- ✅ Filtros de desenfoque
- ✅ Efectos artísticos (sepia, escala de grises)
- ✅ Transiciones suaves

### Sistema de Suscripción
- ✅ Plan Premium: $100/mes
- ✅ Exportación sin límites
- ✅ Acceso a todos los efectos
- ✅ Soporte prioritario
- ✅ Uso comercial permitido

### Exportación
- ✅ Presets de exportación (720p, 1080p, 4K)
- ✅ Control de bitrate y FPS
- ✅ Formatos: MP4, AVI, MOV, WebM
- ✅ Codificación de hardware acelerada

### Gestión de Proyectos
- ✅ Guardar/Cargar proyectos
- ✅ Base de datos SQLite
- ✅ Historial de cambios
- ✅ Exportar en múltiples formatos

## Requisitos del Sistema

### Dependencias de Desarrollo
- **Qt 6.x** (Core, Gui, Widgets, Multimedia, Network, Sql)
- **C++17**
- **FFmpeg** (para procesamiento de video)
- **CMake 3.16+**

### Sistema Operativo
- Windows 10/11
- macOS 10.13+
- Linux (Ubuntu 18.04+)

## Instalación

### 1. Clonar el repositorio
```bash
git clone https://github.com/usuario/filmora-editor.git
cd filmora-editor
```

### 2. Instalar dependencias

#### En Windows (con MSVC)
```bash
# Instalar Qt6
winget install Qt.Qt6

# Instalar CMake
winget install CMake

# Instalar FFmpeg
winget install FFmpeg
```

#### En macOS
```bash
brew install qt6 cmake ffmpeg
```

#### En Linux
```bash
sudo apt-get install qt6-base-dev cmake libavcodec-dev libavformat-dev
```

### 3. Compilar el proyecto
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 4. Ejecutar la aplicación
```bash
# Windows
./Release/FilmoraEditor.exe

# macOS/Linux
./FilmoraEditor
```

## Estructura del Proyecto

```
filmora-editor/
├── src/
│   ├── main.cpp                 # Punto de entrada
│   ├── mainwindow.h/cpp         # Ventana principal
│   ├── videotimeline.h/cpp      # Control de timeline
│   ├── videoeditor.h/cpp        # Lógica de edición
│   ├── paymentmanager.h/cpp     # Sistema de pagos
│   ├── subscriptionmanager.h/cpp # Gestión de suscripción
│   ├── effectsmanager.h/cpp     # Gestor de efectos
│   ├── exportmanager.h/cpp      # Gestor de exportación
│   └── database.h/cpp           # Gestor de base de datos
├── CMakeLists.txt               # Configuración de CMake
├── resources.qrc                # Recursos (iconos, estilos)
└── README.md                    # Este archivo
```

## Uso

### Importar Video
1. Haz clic en "📁 Importar" en la barra de herramientas
2. Selecciona un archivo de video (MP4, AVI, MOV, etc.)
3. El video aparecerá en la timeline

### Agregar Efectos
1. Selecciona un clip en la timeline
2. Haz clic en "+ Agregar Efecto"
3. Selecciona el efecto deseado
4. Ajusta la intensidad según sea necesario

### Agregar Transiciones
1. Selecciona la posición entre clips
2. Haz clic en "+ Agregar Transición"
3. Elige el tipo de transición (Fade, Slide, etc.)
4. Configura la duración

### Exportar Video
1. Configura los efectos y transiciones
2. Haz clic en "💾 Exportar"
3. Selecciona la calidad (720p, 1080p, 4K)
4. Elige la ubicación de guardado
5. La exportación comenzará automáticamente

### Activar Suscripción
1. Haz clic en "⭐ Premium ($100/mes)"
2. Ingresa los datos de tu tarjeta
3. Confirma el pago
4. ¡Acceso completo activado!

## Sistema de Pago

Se integran los siguientes gateways de pago:
- **Stripe** - Pago con tarjeta de crédito
- **PayPal** - Pago rápido con PayPal
- **Razorpay** - Soporte global

## Configuración del Gateway de Pago

### Stripe (Recomendado)
```cpp
// En paymentmanager.cpp
const QString STRIPE_API_KEY = "sk_live_xxxxxxxxxxxxx";
const QString STRIPE_PUBLIC_KEY = "pk_live_xxxxxxxxxxxxx";
```

### PayPal
```cpp
const QString PAYPAL_CLIENT_ID = "xxxxxxxxxxxxxxxxxx";
const QString PAYPAL_CLIENT_SECRET = "xxxxxxxxxxxxxxxxxx";
```

## Atajos de Teclado

| Atajo | Función |
|-------|---------|
| Ctrl+N | Nuevo proyecto |
| Ctrl+O | Abrir proyecto |
| Ctrl+S | Guardar proyecto |
| Ctrl+E | Exportar video |
| Space | Play/Pause |
| Ctrl+Z | Deshacer |
| Ctrl+Y | Rehacer |
| Ctrl+C | Copiar clip |
| Ctrl+V | Pegar clip |
| Del | Eliminar clip |

## Contribuciones

Las contribuciones son bienvenidas. Para cambios importantes:

1. Fork el proyecto
2. Crea una rama (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## Licencia

Este proyecto está bajo la licencia MIT. Ver archivo `LICENSE` para más detalles.

## Soporte

Para soporte técnico:
- 📧 Email: support@filmoraeditor.com
- 💬 Chat en vivo: www.filmoraeditor.com/support
- 📱 WhatsApp: +1-800-FILMORA

## Changelog

### v1.0.0 - Lanzamiento Inicial
- ✅ Editor de video funcional
- ✅ Sistema de suscripción
- ✅ Timeline interactivo
- ✅ 50+ efectos
- ✅ Exportación 4K
- ✅ Base de datos de proyectos

## Roadmap

### v1.1.0 (Próxima)
- [ ] Editor de audio avanzado
- [ ] Efectos de IA
- [ ] Capas de imagen
- [ ] Grabación de pantalla

### v1.2.0
- [ ] Colaboración en nube
- [ ] Presets de plantillas
- [ ] Librería de música y efectos de sonido
- [ ] Tutor interactivo

## Developers

- **Desarrollador Principal**: Tu Nombre
- **Diseñador UI/UX**: Tu Nombre
- **Backend**: Tu Nombre

---

**Filmora Editor Pro** © 2026. Todos los derechos reservados.
