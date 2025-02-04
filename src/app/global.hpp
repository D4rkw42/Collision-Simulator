// Variáveis globais da aplicação

#pragma once

#include "core/geometric/Shape.hpp"
#include "core/geometric/Line.hpp"

#include "utils/world/camera.hpp"

// estados
inline bool gravity = false;

// utilidades
inline std::shared_ptr<Camera> camera = std::make_shared<Camera>(0, 0);

// Entidades geométricas do mundo
inline ShapeList shapeList;
inline LineList lineList;

// Peças selecionadas
inline std::shared_ptr<Line> lineSelected = nullptr;
inline std::shared_ptr<Shape> shapeSelected = nullptr;

inline bool isElementSelected = false; // se algum elemento está selecionado
