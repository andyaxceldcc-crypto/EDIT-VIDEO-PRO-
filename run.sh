#!/bin/bash

echo "======================================"
echo "Instalando dependencias de Filmora Editor"
echo "======================================"

# Verificar Python
python3 --version > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "ERROR: Python 3 no está instalado"
    echo "Linux: sudo apt-get install python3"
    echo "macOS: brew install python3"
    exit 1
fi

echo "Python encontrado"
echo ""
echo "Instalando PyQt6..."
pip3 install PyQt6 --upgrade

if [ $? -ne 0 ]; then
    echo "ERROR: Falla al instalar PyQt6"
    exit 1
fi

echo ""
echo "======================================"
echo "Dependencias instaladas exitosamente"
echo "Ejecutando Filmora Editor..."
echo "======================================"
echo ""

python3 filmora_editor.py
