#!/bin/bash
# Script de compilación para Linux/macOS

echo "======================================"
echo "Compilando Filmora Editor Pro"
echo "======================================"

# Verificar dependencias
echo "Verificando dependencias..."

# Qt
if ! command -v qmake &> /dev/null; then
    echo "ERROR: Qt no está instalado"
    echo "Instale con: sudo apt-get install qt6-base-dev (Linux)"
    echo "o: brew install qt6 (macOS)"
    exit 1
fi

# FFmpeg
if ! command -v ffmpeg &> /dev/null; then
    echo "ERROR: FFmpeg no está instalado"
    echo "Instale con: sudo apt-get install libavcodec-dev (Linux)"
    echo "o: brew install ffmpeg (macOS)"
    exit 1
fi

echo "Dependencias OK"
echo ""

# Crear directorio de build
mkdir -p build
cd build

# Generar Makefile con qmake
echo "Generando archivos de proyecto..."
qmake ../FilmoraEditor.pro

# Compilar
echo ""
echo "Compilando..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "ERROR: La compilación falló"
    exit 1
fi

echo ""
echo "======================================"
echo "Compilación completada exitosamente!"
echo "Ejecutable: build/FilmoraEditor"
echo "======================================"
