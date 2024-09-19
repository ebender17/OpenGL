#pragma once

#include "Core.h"

#include "LayerStack.h"
#include "Timestep.h"
#include "Window.h"
#include "GLCore/Events/Event.h"
#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/KeyEvent.h"
#include "GLCore/Events/MouseEvent.h"
#include "GLCore/ImGui/ImGuiLayer.h"

namespace GLCore {

    class Application
    {
    public:
        Application(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }

        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication();

}