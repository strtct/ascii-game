#!/bin/bash

mkdir -p build/engine build/game bin

# 1) Compilar engine/**/*.cpp a objetos en build/engine
find engine -name '*.cpp' -exec sh -c '
  for file; do
    obj="build/engine/${file#engine/}"
    obj="${obj%.cpp}.o"
    mkdir -p "$(dirname "$obj")"
    g++ -Wall -std=c++17 -Iengine -c "$file" -o "$obj"
  done
' sh {} +

# 2) Crear la librería estática con los objetos engine
find build/engine -name '*.o' -print0 | xargs -0 ar rcs build/engine/libengine.a

# 3) Compilar game/**/*.cpp a objetos en build/game
find game -name '*.cpp' -exec sh -c '
  for file; do
    obj="build/game/${file#game/}"
    obj="${obj%.cpp}.o"
    mkdir -p "$(dirname "$obj")"
    # Aquí el include engine para que game pueda #include "engine/file.hpp"
    g++ -Wall -std=c++17 -Iengine -c "$file" -o "$obj"
  done
' sh {} +

# 4) Linkear todos los objetos game y la librería engine + libtickit en bin/game
g++ build/game/*.o build/engine/libengine.a -ltickit -o bin/game
