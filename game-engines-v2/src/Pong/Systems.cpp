#include "print.h"
#include "Systems.h"
#include "Components.h"

HelloSystem::HelloSystem() {
  std::cout << "Hello System Constructor" << std::endl;
}

HelloSystem::HelloSystem(const HelloSystem& other) {
  std::cout << "Hello System Copy Constructor" << std::endl;
}

HelloSystem::~HelloSystem() {
    std::cout << "Hello System Destructor" << std::endl;
}

void HelloSystem::run() {
    std::cout << "Hello System!" << std::endl;
}

void RectRenderSystem::run(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

  const auto view = scene->r.view<TransformComponent, SizeComponent>();
  for (const entt::entity e : view) {
    const TransformComponent& t = view.get<TransformComponent>(e);
    const SizeComponent& c = view.get<SizeComponent>(e);
    const int x = t.position.x;
    const int y = t.position.y;
    const int w = c.w;
    const int h = c.h;

    SDL_Rect rect = { x, y, w, h };    
    SDL_RenderFillRect(renderer, &rect);
  }
}

MovementUpdateSystem::MovementUpdateSystem(int screen_width, int screen_height)
  : screen_width(screen_width), screen_height(screen_height) { }

void MovementUpdateSystem::run(double dT) {
  const auto view = scene->r.view<TransformComponent, SpeedComponent>();
  for (const entt::entity e : view) {
    TransformComponent& t = view.get<TransformComponent>(e);
    SpeedComponent& m = view.get<SpeedComponent>(e);

    if (m.x == 0 && m.y == 0) {
      continue;
    }

    if (t.position.x <= 0 || t.position.x >= screen_width - 20) {
      m.x *= -1;
    }
    if (t.position.y <= 0 || t.position.y >= screen_height - 20) {
      m.y *= -1;
    }
  
    t.position.x += m.x * dT;
    t.position.y += m.y * dT;
  }
}


void PlayerInputEventSystem::run(SDL_Event event) {
  scene->r.view<PlayerComponent, SpeedComponent>().each(
    [&](const auto& entity, PlayerComponent& player, SpeedComponent& speed) {
      if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            speed.y = -player.moveSpeed;
            break;
          case SDLK_RIGHT:
            speed.y = player.moveSpeed;
            break;
          case SDLK_w: // Handle 'W' key for the second paddle moving up
            speed.y = -player.moveSpeed;
            break;
          case SDLK_s: // Handle 'S' key for the second paddle moving down
            speed.y = player.moveSpeed;
            break;
        }
      }
    }
  );
}



void CollisionDetectionUpdateSystem::run(double dT) {
    const auto view = scene->r.view<TransformComponent, SizeComponent, ColliderComponent>();
    const auto view2 = scene->r.view<TransformComponent, SizeComponent>();
    const auto paddleView = scene->r.view<TransformComponent, SizeComponent, PlayerComponent>(); // Vista para los paddles

    // Check collisions with paddles
    view.each([&](auto e1, TransformComponent& t1, SizeComponent& s1, ColliderComponent& c1) {
        SDL_Rect box1 = { t1.position.x, t1.position.y, s1.w, s1.h };

        paddleView.each([&](auto e2, TransformComponent& t2, SizeComponent& s2, PlayerComponent& player) {
            SDL_Rect box2 = { t2.position.x, t2.position.y, s2.w, s2.h };

            if (SDL_HasIntersection(&box1, &box2)) {
                c1.triggered = true; // Activa el flag de colisión si hay colisión con el paddle
            }
        });
    });

    // Check collisions with other entities and screen edges
    view.each([&](auto e1, TransformComponent& t1, SizeComponent& s1, ColliderComponent& c1) {
        SDL_Rect box1 = { t1.position.x, t1.position.y, s1.w, s1.h };

        view2.each([&](auto e2, TransformComponent& t2, SizeComponent& s2) {
            if (e1 == e2) return;  // Saltar si es el mismo objeto

            SDL_Rect box2 = { t2.position.x, t2.position.y, s2.w, s2.h };

            if (SDL_HasIntersection(&box1, &box2)) {
                c1.triggered = true; // Activa el flag de colisión si hay colisión con otro objeto
            }
        });

        // Check screen edges
        if (t1.position.x + s1.w >= 650 || t1.position.x <= 0) {
            if (t1.position.x + s1.w >= 650) {
                std::cout << "La pelota ha tocado el borde derecho" << std::endl;
                print("PLAYER 1 WINS");
                exit(1);
            } else {
                std::cout << "La pelota ha tocado el borde izquierdo" << std::endl;
                print("PLAYER 2 WINS");
                exit(1);
            }
            // Aquí puedes realizar otras acciones si lo deseas
        }
    });
}





void BounceUpdateSystem::run(double dT) {
    const auto view = scene->r.view<ColliderComponent, SpeedComponent, TransformComponent>();

    view.each([&](auto entity, ColliderComponent& collider, SpeedComponent& speed, TransformComponent& transform) {
        if (collider.triggered) {
            collider.triggered = false;

            // Supongamos que la posición Y representa el centro del paddle
            int paddleY = transform.position.y;

            // Calcular la posición relativa de la colisión
            int relativeHitPosition = transform.position.y - speed.y * dT;

// Calcular la dirección de rebote basada en la posición relativa de la colisión
double hitAngle = (relativeHitPosition > paddleY) ? -0.5 * M_PI : 0.5 * M_PI;

// Modificar la dirección de la pelota basada en el ángulo de rebote
double speedMagnitude = sqrt(speed.x * speed.x + speed.y * speed.y);
speedMagnitude *= 1.1; // Aumenta la velocidad, puedes ajustar este factor según sea necesario

// Calcular el ángulo actual de movimiento
double currentAngle = atan2(speed.y, speed.x);

// Calcular el ángulo de rebote en el eje X (opuesto al ángulo actual)
double newAngleX = M_PI - currentAngle;

// Modificar la dirección de la pelota para el rebote en el eje X
speed.x = speedMagnitude * cos(newAngleX);
speed.y = speedMagnitude * sin(hitAngle); // Mantener la dirección en el eje Y

        }
    });
}


