#pragma once

#pragma once

#include <GLCore.h>

#include "3D/Camera/FirstPersonCamera.h"
#include "3D/Lighting/Light.h"
#include "3D/Lighting/Material.h"

class OpenGLSandbox : public GLCore::Layer
{
public:
    OpenGLSandbox();
    virtual ~OpenGLSandbox() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(GLCore::Timestep timestep) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(GLCore::Event& event) override;

private:
    void InitLights();
    void InitCamera();
    void GenerateTexture2D(const std::string& filepath, uint32_t* texture);

    bool OnWindowResized(GLCore::WindowResizeEvent& event);
private:
    uint32_t m_VAO;
    uint32_t m_LightCubeVAO;
    uint32_t m_VBO;
    uint32_t m_EBO;

    Material m_Material;

    // TODO : Use Shader Library
    std::unique_ptr<GLCore::Shader> m_Shader;
    std::unique_ptr<GLCore::Shader> m_FlatColorShader;

    //Camera
    std::unique_ptr<FirstPersonCamera> m_Camera;

    // Lights
    std::unique_ptr<DirectionalLight> m_DirectionalLight;
};
