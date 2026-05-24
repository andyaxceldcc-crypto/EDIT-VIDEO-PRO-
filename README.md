# Filmora Editor Pro - Editor de Video Profesional

## Descripción
Editor de video de escritorio tipo Filmora con características profesionales, sistema de suscripción mensual ($100/mes) y exportación sin límites.

---

## 📦 REQUISITOS DE SOFTWARE PARA COMPILAR

### Software Necesario (Versiones Exactas)

#### 🪟 Windows (RECOMENDADO)

| Software | Versión | Descarga | Peso |
|----------|---------|----------|------|
| **Visual Studio Build Tools 2022** | 17.x | https://visualstudio.microsoft.com/downloads/ | ~2 GB |
| **Qt 6.6.x** | 6.6.2 (LTS) | https://www.qt.io/download-qt-installer | ~1.5 GB |
| **CMake** | 3.26+ | https://cmake.org/download/ | ~30 MB |
| **FFmpeg** | 6.0 (o superior) | https://ffmpeg.org/download.html | ~70 MB |
| ** Strawberry Perl** | 5.36+ | https://strawberryperl.com/ | ~300 MB |

**Nota:** Para Qt 6.6.2, seleccionar durante instalación:
- **Qt 6.6.2** → MSVC2022 64-bit
- **Qt Creator** 
- **Qt 6.6.2** → Additional Libraries → Qt Multimedia, Qt SQL, Qt Network, Qt Concurrent

#### 🍎 macOS

| Software | Versión | Comando |
|----------|---------|---------|
| **Xcode** | 15+ | App Store |
| **Qt 6** | 6.6.x | `brew install qt@6` |
| **CMake** | 3.26+ | `brew install cmake` |
| **FFmpeg** | 6.0+ | `brew install ffmpeg` |

#### 🐧 Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y qt6-base-dev qt6-multimedia-dev qt6-network-auth \
    cmake build-essential libavcodec-dev libavformat-dev libavutil-dev \
    libswscale-dev libsqlite3-dev
```

---

## 🔧 INSTALACIÓN PASO A PASO (Windows)

### Paso 1: Instalar Visual Studio Build Tools 2022

1. Descargar de: https://visualstudio.microsoft.com/downloads/
2. Ejecutar el instalador
3. Seleccionar: **"Desarrollo de escritorio con C++"**
4. Marcar estos componentes:
   - ✅ MSVC v143 - VS 2022 C++ x64/x86
   - ✅ Windows 11 SDK (o Windows 10 SDK)
   - ✅ C++ ATL para las últimas versiones de Build Tools

### Paso 2: Instalar Qt 6.6.2

1. Descargar el instalador: https://www.qt.io/download-qt-installer
2. Crear cuenta (gratis) en qt.io
3. Durante instalación seleccionar:
   - ✅ Qt 6.6.2 → MSVC2022 64-bit
   - ✅ Qt Creator 12.x
   - ✅ Qt 6.6.2 → Additional Libraries:
     - ☑️ Qt Multimedia
     - ☑️ Qt SQL
     - ☑️ Qt Network
     - ☑️ Qt Concurrent
     - ☑️ Qt 5 Compatibility

4. Anotar la ruta de instalación: `C:\Qt\6.6.2\msvc2022_64`

### Paso 3: Instalar CMake

1. Descargar: https://cmake.org/download/ → Windows x64 Installer
2. Instalar y marcar: ✅ "Add CMake to system PATH for all users"
3. Reiniciar terminal

### Paso 4: Instalar FFmpeg

**Opción A: vcpkg (Recomendado)**
```cmd
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
bootstrap-vcpkg.bat
vcpkg install ffmpeg:x64-windows
```

**Opción B: Binarios precompilados**
1. Descargar: https://www.gyan.dev/ffmpeg/builds/
2. Seleccionar: `ffmpeg-release-essentials.zip`
3. Extraer a: `C:\ffmpeg`
4. Agregar al PATH: `C:\ffmpeg\bin`

### Paso 5: Configurar Variables de Entorno

En Windows Search: `variables de entorno` → Editar variables de entorno del sistema

Agregar a **Path**:
```
C:\Qt\6.6.2\msvc2022_64\bin
C:\Qt\Tools\QtCreator\bin
C:\vcpkg\installed\x64-windows\bin
C:\Program Files\CMake\bin
```

Agregar nuevas variables:
```
Qt6_DIR = C:\Qt\6.6.2\msvc2022_64\lib\cmake\Qt6
CMAKE_PREFIX_PATH = C:\Qt\6.6.2\msvc2022_64
```

---

## 🚀 COMPILACIÓN DEL PROYECTO

### Opción 1: Script Automático (Más Fácil)

```cmd
# Ejecutar en la carpeta del proyecto
COMPILAR_FINAL.bat
```

### Opción 2: Manual con Qt Creator

1. Abrir Qt Creator
2. Archivo → Abrir archivo/proyecto → `FilmoraEditor.pro`
3. Seleccionar kit: **Desktop Qt 6.6.2 MSVC2022 64-bit**
4. Click en **Configurar proyecto**
5. Compilar: `Ctrl+B`
6. Ejecutar: `Ctrl+R`

### Opción 3: Línea de Comandos

```cmd
# Abrir "x64 Native Tools Command Prompt for VS 2022"

cd C:\ruta\a\EDIT-VIDEO-PRO-

# Crear carpeta de compilación
mkdir build
cd build

# Configurar con qmake
qmake ..\FilmoraEditor.pro -spec win32-msvc CONFIG+=release

# Compilar
nmake /NOLOGO

# Si todo sale bien, el .exe estará en build/release/
```

---

## 📦 CREAR PAQUETE .EXE CON TODAS LAS DLLs

### Usando windeployqt (Windows)

Después de compilar, ejecutar:

```cmd
cd build\release

# Desplegar todas las DLLs de Qt
C:\Qt\6.6.2\msvc2022_64\bin\windeployqt.exe FilmoraEditor.exe

# Agregar FFmpeg (copiar manualmente)
copy C:\vcpkg\installed\x64-windows\bin\*.dll .
```

### Script Completo de Despliegue

Crear archivo `DESPLOY.bat`:
```batch
@echo off
chcp 65001 >nul
cd /d "%~dp0"

echo ================================================
echo   CREANDO PAQUETE PORTABLE FilmoraEditor
echo ================================================

cd build\release

echo Copiando DLLs de Qt...
C:\Qt\6.6.2\msvc2022_64\bin\windeployqt.exe FilmoraEditor.exe --no-translations

echo Copiando DLLs de FFmpeg...
if exist "C:\vcpkg\installed\x64-windows\bin" (
    copy "C:\vcpkg\installed\x64-windows\bin\avcodec*.dll" . 2>nul
    copy "C:\vcpkg\installed\x64-windows\bin\avformat*.dll" . 2>nul
    copy "C:\vcpkg\installed\x64-windows\bin\avutil*.dll" . 2>nul
    copy "C:\vcpkg\installed\x64-windows\bin\swscale*.dll" . 2>nul
    copy "C:\vcpkg\installed\x64-windows\bin\swresample*.dll" . 2>nul
)

echo ================================================
echo   PAQUETE CREADO EXITOSAMENTE!
echo ================================================
dir FilmoraEditor.exe
pause
```

---

## 📋 VERIFICACIÓN DE DEPENDENCIAS

Para verificar que todo está instalado correctamente, ejecutar en terminal:

```cmd
# Verificar Qt
qmake --version

# Verificar CMake
cmake --version

# Verificar MSVC
cl

# Verificar FFmpeg (si se instaló)
ffmpeg -version
```

**Resultados esperados:**
```
QMake version: 3.1
Using Qt version 6.6.2 in C:/Qt/6.6.2/msvc2022_64/lib

cmake version 3.26.x
Microsoft (R) C/C++ Optimizing Compiler Version 19.36.x
```

---

## 🔍 SOLUCIÓN DE PROBLEMAS

### "qmake no se reconoce" o "Cannot find module Qt"
- Verificar que las variables de entorno están configuradas
- Reiniciar el sistema después de instalar Qt
- Abrir "x64 Native Tools Command Prompt for VS 2022" desde el menú inicio

### "No se encontró FFmpeg"
- Instalar FFmpeg con vcpkg o descargar binarios
- Verificar que la ruta está en el PATH

### "Error de compilación: cannot find -lxxx"
- Verificar que las librerías están en las rutas correctas
- En FilmoraEditor.pro, ajustar las rutas INCLUDEPATH y LIBS

### "windeployqt no funciona"
- Ejecutar desde x64 Native Tools Command Prompt
- Verificar que el .exe compiló correctamente primero

### "Error: LNK1112: module machine type x86 conflicts with target machine type x64"
- Asegurarse de usar el compilador x64, no x86
- En Qt Creator: Proyectos → Kit → Qt 6.6.2 MSVC2022 64-bit

---

## 📁 ESTRUCTURA DEL PROYECTO

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
│   ├── imagemanager.h/cpp      # Gestor de imágenes
│   ├── colorgradingmanager.h/cpp # Corrección de color
│   ├── titlesmanager.h/cpp      # Gestor de títulos
│   ├── audiomanager.h/cpp       # Gestor de audio
│   ├── exportmanager.h/cpp      # Gestor de exportación
│   └── database.h/cpp           # Gestor de base de datos
├── CMakeLists.txt               # Configuración de CMake
├── FilmoraEditor.pro            # Archivo de proyecto Qt
├── resources.qrc                # Recursos (iconos, estilos)
├── compile.sh                  # Script de compilación Linux/macOS
├── COMPILAR_FINAL.bat          # Script de compilación Windows
├── COMPILACION.md              # Guía de compilación
└── README.md                   # Este archivo
```

---

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

---

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

---

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

---

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

---

## Contribuciones

Las contribuciones son bienvenidas. Para cambios importantes:

1. Fork el proyecto
2. Crea una rama (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature'`)
5. Abre un Pull Request

---

## Licencia

Este proyecto está bajo la licencia MIT. Ver archivo `LICENSE` para más detalles.

---

## Soporte

Para soporte técnico:
- 📧 Email: support@filmoraeditor.com
- 💬 Chat en vivo: www.filmoraeditor.com/support
- 📱 WhatsApp: +1-800-FILMORA

---

## Changelog

### v1.0.0 - Lanzamiento Inicial
- ✅ Editor de video funcional
- ✅ Sistema de suscripción
- ✅ Timeline interactivo
- ✅ 50+ efectos
- ✅ Exportación 4K
- ✅ Base de datos de proyectos

---

## Developers

- **Desarrollador Principal**: Tu Nombre
- **Diseñador UI/UX**: Tu Nombre
- **Backend**: Tu Nombre

---

**Filmora Editor Pro** © 2026. Todos los derechos reservados.
