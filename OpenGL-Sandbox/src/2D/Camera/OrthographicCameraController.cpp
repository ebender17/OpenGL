#include "glpch.h"
#include "OrthographicCameraController.h"

using namespace GLCore;

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation, bool zoom, float nearPlane, float farPlane)
    : Camera2DBaseController(aspectRatio, nearPlane, farPlane), m_Rotation(rotation), m_Zoom(zoom)
{
}

void OrthographicCameraController::OnUpdate(GLCore::Timestep timestep)
{
    Camera2DBaseController::OnUpdate(timestep);

    if (Input::IsKeyPressed(Key::A))
    {
        m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
    }
    if (Input::IsKeyPressed(Key::D))
    {
        m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
    }
    if (Input::IsKeyPressed(Key::W))
    {
        m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
    }
    if (Input::IsKeyPressed(Key::S))
    {
        m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
        m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
    }

    m_Camera.SetPosition(m_CameraPosition);
    m_CameraTranslationSpeed = m_ZoomLevel;

    if (!m_Rotation) { return; }

    if (Input::IsKeyPressed(Key::Q))
        m_CameraRotation += m_CameraRotationSpeed * timestep;
    if (Input::IsKeyPressed(Key::E))
        m_CameraRotation -= m_CameraRotationSpeed * timestep;

    if (m_CameraRotation > 180.0f)
        m_CameraRotation -= 360.0f;
    else if (m_CameraRotation <= -180.0f)
        m_CameraRotation += 360.0f;

    m_Camera.SetRotation(m_CameraRotation);
}

void OrthographicCameraController::OnEvent(GLCore::Event& event)
{
    Camera2DBaseController::OnEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(GLCORE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
}

bool OrthographicCameraController::OnMouseScrolled(GLCore::MouseScrolledEvent& event)
{
    PROFILE_FUNCTION();

    if (!m_Zoom) { return false; }

    m_ZoomLevel -= event.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    CalculateView();
    return false;
}
