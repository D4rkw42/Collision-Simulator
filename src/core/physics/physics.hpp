// Determina como as regras da física funcionam no mundo

#pragma once

// Definições padrões da física
const double ELASTIC_COEFFICIENT = 1.f;
const double TERMINAL_VELOCITY = 10.f;

void BodyElasticCollision(double& velX1, double& velY1, double& velX2, double& velY2); // usado para calcular as novas velocidades de um corpo após uma colisão
