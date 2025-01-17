#pragma once

#include <GLCore.h>

#include "../Animation/AnimatorTopDown.h"

class PlayerController
{
public:
    enum class PlayerState
    {
        Idle = 0,
        Turning,
        Walking
    };

    enum class Direction
    {
        Down = 0,
        Up,
        Left,
        Right
    };
public:
    PlayerController(const glm::vec3& position, const char* textureFilepath);
    ~PlayerController();

    void LoadAssets();

    void OnUpdate(GLCore::Timestep timestep);
    void OnRender();

    const glm::vec3& GetPosition() const { return m_Position; }
private:
    void ProcessPlayerInput();
    void Move(GLCore::Timestep timestep);

    void SetupAnimation(const char* animationName, bool isLoop, const glm::vec2& spriteSize, unsigned int row, size_t frameCount, float frameDuration, unsigned int reserveFrameCount);
    void OnAnimationEnd();

    void SetActiveIdleAnimation();
    void SetActiveWalkAnimation();
private:
    glm::vec3 m_Position;
    const char* m_TextureFilepath;

    GLCore::Ref<GLCore::Texture2D> m_SpriteSheet;
    GLCore::Ref<AnimatorTopDown> m_Animator;
    PlayerState m_PlayerState = PlayerState::Idle;

    float m_Speed = 4.0f;
    glm::vec3 m_InitialPosition;
    glm::vec2 m_InputDirection = glm::vec2(0.0);
    Direction m_Direction = Direction::Down;
    float m_PercentMovedToNextTile = 0.0f;

    // Animation Names
    const char* m_IdleDown = "idle-down";
    const char* m_IdleUp = "idle-up";
    const char* m_IdleLeft = "idle-left";
    const char* m_IdleRight = "idle-right";

    const char* m_WalkDown = "walk-down";
    const char* m_WalkUp = "walk-up";
    const char* m_WalkLeft = "walk-left";
    const char* m_WalkRight = "walk-right";
};

