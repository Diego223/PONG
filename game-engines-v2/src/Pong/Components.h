#include "ECS/Components.h"

struct SizeComponent {
  int w;
  int h;
};

struct ColliderComponent {
  bool triggered;
};

struct PlayerComponent {
  short moveSpeed;
};
