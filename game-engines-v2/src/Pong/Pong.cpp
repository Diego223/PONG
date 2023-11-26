#include "print.h"
#include "Pong.h"
#include "Systems.h"
#include "Components.h"
#include "ECS/Entity.h"

Pong::Pong() : Game("Pong", SCREEN_WIDTH, SCREEN_HEIGHT) {
    std::unique_ptr<Scene> gameplayScene = createGameplayScene();
    setScene(std::move(gameplayScene));
}

Pong::~Pong() {
    // destructor implementation
}
const int paddleWidth = 20; // Replace 100 with the desired width of the paddle
const int paddleHeight = 100; // Replace 20 with the desired height of the paddle

std::unique_ptr<Scene> Pong::createGameplayScene()
{
    // Create a unique_ptr to hold the created scene
    std::unique_ptr<Scene> gameplayScene = std::make_unique<Scene>("Gameplay");

    Entity ball = gameplayScene->createEntity("ball", 100, 100);
    ball.addComponent<SpeedComponent>(200, 200);
    ball.addComponent<SizeComponent>(30, 30);
    ball.addComponent<ColliderComponent>(false);

int paddleY = (SCREEN_HEIGHT - paddleHeight) / 2; // Calculate Y position for the center
int paddleX = SCREEN_WIDTH - paddleWidth - 10; // 10 pixels away from the right edge
int leftPaddleX = 10; 

Entity paddle = gameplayScene->createEntity("paddle", paddleX, paddleY);
paddle.addComponent<SpeedComponent>(0, 0);
paddle.addComponent<SizeComponent>(paddleWidth, paddleHeight);
paddle.addComponent<PlayerComponent>(200);

Entity leftPaddle = gameplayScene->createEntity("left_paddle", leftPaddleX, paddleY);
leftPaddle.addComponent<SpeedComponent>(0, 0);
leftPaddle.addComponent<SizeComponent>(paddleWidth, paddleHeight);
leftPaddle.addComponent<PlayerComponent>(200);

    gameplayScene->addSetupSystem<HelloSystem>();
    gameplayScene->addRenderSystem<RectRenderSystem>();
    gameplayScene->addUpdateSystem<MovementUpdateSystem>(SCREEN_WIDTH, SCREEN_HEIGHT);
    gameplayScene->addEventSystem<PlayerInputEventSystem>();
    gameplayScene->addUpdateSystem<CollisionDetectionUpdateSystem>();
    gameplayScene->addUpdateSystem<BounceUpdateSystem>();

    return gameplayScene;
}

