#include "Sandbox2D.h"

#include "Platform/OpenGL/Debug/OpenGLDebug.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace GLCore;

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.f / 720.0f, false, -2.0f, 2.0f)
{
}

void Sandbox2D::OnAttach()
{
    PROFILE_FUNCTION();

    EnableGLDebugging();
    SetGLDebugLogLevel(DebugLogLevel::Notification);

    m_CheckerboardTexture = Texture2D::Create("assets/textures/checkerboard.png");
    m_PlayerTexture = Texture2D::Create("assets/textures/emily-pokemon-style.png");
    m_Tileset = Texture2D::Create("assets/textures/TilesetFloor.png");

    m_ExampleSubTexture = SubTexture2D::CreateFromCoords(m_Tileset, { 3, 3 }, { 16, 16 }, { 1, 2 });
}

void Sandbox2D::OnDetach()
{
    PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(GLCore::Timestep timestep)
{
    PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(timestep);

    // Render
    {
        PROFILE_SCOPE("Renderer Prep");
        RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        RenderCommand::Clear();
    }

    Renderer2D::ResetStats();
    {
        PROFILE_SCOPE("Renderer Draw");
        Renderer2D::BeginScene(m_CameraController.GetCamera());
        Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, m_QuadColor);
        Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
        Renderer2D::DrawQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, m_ExampleSubTexture);
        Renderer2D::DrawRotatedQuad({ -2.0f, -2.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(45.0f), m_PlayerTexture);

        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.6f, (y + 5.0f) / 10.0f, 0.7f };
                Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");

    auto stats = Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_QuadColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(GLCore::Event& event)
{
    m_CameraController.OnEvent(event);
}
