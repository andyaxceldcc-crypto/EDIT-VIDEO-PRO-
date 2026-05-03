# Filmora Editor Pro - Guía de Compilación

## Opción 1: Compilación Automática (Recomendado)

### Windows
1. Ejecuta: `compile.bat`
2. Espera a que se complete
3. El ejecutable estará en: `build/release/FilmoraEditor.exe`

### Linux/macOS
1. Ejecuta: `bash compile.sh`
2. Espera a que se complete
3. El ejecutable estará en: `build/FilmoraEditor`

## Opción 2: Compilación Manual con Qt Creator

### Windows
1. Abre Qt Creator
2. Archivo → Abrir → `FilmoraEditor.pro`
3. Haz clic en "Configurar proyecto"
4. Presiona `Ctrl+B` para compilar
5. Presiona `Ctrl+R` para ejecutar

### Linux/macOS
```bash
qmake FilmoraEditor.pro
make
./build/FilmoraEditor
```

## Requisitos Previos

### Windows
1. **Qt 6.x** - Descargar de https://www.qt.io/download
   - Selecciona: Desktop (MSVC)
   - Mínimo 6.0 o superior

2. **Visual Studio 2022 Community**
   - Descargar de: https://visualstudio.microsoft.com/es/
   - O usar las herramientas de compilación de MSVC

3. **FFmpeg** (Opcional para exportación)
   - Descargar de: https://ffmpeg.org/download.html

### macOS
```bash
brew install qt@6 ffmpeg
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install qt6-base-dev qt6-multimedia-dev libavcodec-dev libavformat-dev
```

## Solución de Problemas

### "qmake no se reconoce"
- Windows: Agrega `C:\Qt\6.x\msvc2019_64\bin` a Path del sistema
- Linux/macOS: Instala Qt con `apt-get install qt6-base-dev` o `brew`

### "Error: Cannot find module Qt"
- Reinstala Qt desde cero
- Asegúrate de que qmake apunte a la versión correcta

### "FFmpeg no encontrado"
- La exportación funcionará sin FFmpeg (funcionalidad limitada)
- Instala FFmpeg en tu sistema

## Compilación Exitosa

Si ves este mensaje:
```
Compilación completada exitosamente!
Ejecutable: build/release/FilmoraEditor.exe
```

¡El editor está listo para usar!

## Próximos Pasos

1. Ejecuta la aplicación
2. Crea un nuevo proyecto
3. Importa un video
4. Prueba los efectos
5. Activa la suscripción ($100/mes)
6. Exporta tu video
