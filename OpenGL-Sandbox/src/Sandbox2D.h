#pragma once

#include "GLCore.h"

class Sandbox2D : public GLCore::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(GLCore::Timestep timestep) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(GLCore::Event& event) override;
private:
    GLCore::OrthographicCameraController m_CameraController;

    glm::vec4 m_QuadColor = { 0.584f, 0.0f, 1.0f, 1.0f };
    
    GLCore::Ref<GLCore::Texture2D> m_CheckerboardTexture;
};

