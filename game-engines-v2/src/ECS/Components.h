#pragma once

#include <glm/glm.hpp>
#include <string>

struct NameComponent {
  std::string tag;
};

struct TransformComponent {
  glm::ivec2 position;
  // glm::vec2 scale;
  // double rotation;
};

struct SpeedComponent {
  int x;
  int y;
};