#include <Rish/Core/Application.h>
#include <Rish/Core/Time.h>
#include <Rish/Renderer/Renderer2D.h>
#include <Rish/Math/AABB.h>
#include <Rish/ImGui.h>

#include "EditController.h"

namespace rl {

EditController::EditController()
{
}

void EditController::onAttach(const Ref<Scene> &scene)
{
    SceneTargetPanel::onAttach(scene);
    m_cameraController = MakeRef<OrthographicCameraController>(
        Application::Get().getWindow().getAspectRatio());
    m_editorGrid.onAttach(m_cameraController);
}

void EditController::onDetach()
{
    SceneTargetPanel::onDetach();
}

void EditController::onUpdate(Time dt)
{
    m_cameraController->setState(m_sceneWindowFocused);
    m_cameraController->onUpdate(dt);
    m_editorGrid.onUpdate();

    if(isSelected())
    {
        auto ent = getTarget();
        auto &transform = ent.getComponent<TransformComponent>();
        // Draw Border
        Renderer2D::DrawRect(transform.translate, transform.scale);
    }
}

void EditController::onImGuiRender()
{
    // states
    m_sceneWindowFocused = ImGui::IsWindowFocused();
    m_sceneWindowHovered = ImGui::IsWindowHovered();

    ImVec2 mr = ImGui::GetMousePosRelatedToWindowNormalize();
    sceneMousePosNormalize = glm::vec2{mr.x, mr.y};
    mr = ImGui::GetMousePosRelatedToWindowNormalizeCenter();
    sceneMousePosCenterNormalize = glm::vec2{mr.x, mr.y};

    // To world space
    float xaxis = glm::lerp(m_cameraController->getBounds().right, m_cameraController->getBounds().left, 1.f - sceneMousePosNormalize.x)
            + m_cameraController->getPosition().x;
    float yaxis = glm::lerp(m_cameraController->getBounds().bottom, m_cameraController->getBounds().top, 1.f - sceneMousePosNormalize.y)
            + m_cameraController->getPosition().y;
    glm::vec2 mposInWorld{xaxis, yaxis};

    // Click to select a entity
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        Entity frontEntity;
        float maxZ{-100.f};
        // Iterate through all entities
        m_currentScene->m_registry.each([&](auto entityID)
        {
            Entity ent{entityID, m_currentScene.get()};
            // AABB
            m_curEntPos = ent.getComponent<TransformComponent>().translate;
            m_curSize = ent.getComponent<TransformComponent>().scale;

            if(Math::AABB2DPoint(m_curEntPos, m_curSize, mposInWorld))
            {
                // Pick the max Z one
                if (maxZ < m_curEntPos.z) {
                    frontEntity = ent;
                    maxZ = m_curEntPos.z;
                }
            }
        });

        if(frontEntity)
        {
            setTarget(frontEntity);
        }
    }

    // Entity move
    if(ImGui::IsMouseDown(ImGuiMouseButton_Left) && isSelected())
    {
        auto ent = getTarget();
        auto &entPos = ent.getComponent<TransformComponent>().translate;
        const auto &entSize = ent.getComponent<TransformComponent>().scale;
        //
        // No moving entity
        if(!m_isNowMovingEntity)
        {
            if (Math::AABB2DPoint(entPos, entSize, mposInWorld)) {
                m_moveEntityDiff = entPos - glm::vec3(mposInWorld, 0.f);
                m_isNowMovingEntity = true;
            }
        }
        else
        {
            entPos = glm::vec3(mposInWorld, 0.f) + m_moveEntityDiff;
        }
    }
    else
    {
        m_isNowMovingEntity = false;
        m_moveEntityDiff = glm::vec3{0.f};
    }

    // Camera pane
    if(m_sceneWindowFocused &&
       ImGui::IsMouseDown(ImGuiMouseButton_Right))
    {
        if(!m_isNowMovingCamera)
        {
            m_isNowMovingCamera = true;
            auto camPos = m_cameraController->getPosition();
            m_moveCameraDiff = camPos - glm::vec3(mposInWorld, 0.f);
            m_preMPos = mposInWorld;
        }
        else if(m_isNowMovingCamera && mposInWorld != m_preMPos)
        {
            // Natural pane (inverse)
            glm::vec2 vec = mposInWorld - m_preMPos;
            m_cameraController->move(-vec);
            m_isNowMovingCamera = false;
        }
    }
    else
    {
        m_isNowMovingCamera = false;
        m_moveCameraDiff = glm::vec3{0.f};
    }

    // Preserve window padding
    auto padding = ImGui::GetStyle().WindowPadding;
    ImGui::PopStyleVar();
    //
    if(m_debugEditorController)
    {
        ImGui::Begin("EditController");

        ImGui::End();
    }
    if(m_debugEditorGrid)
        m_editorGrid.onImGuiRender();
    if(m_debugCameraController)
        m_cameraController->onImGuiRender();
    //
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
}

void EditController::onEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<MouseScrolledEvent>(RL_BIND_EVENT_FUNC(EditController::onMouseScrolled));
    //
    if(m_sceneWindowFocused && m_sceneWindowHovered)
        m_cameraController->onEvent(e);
}

bool EditController::onMouseScrolled(MouseScrolledEvent &e)
{
    // TODO: camera translate when zooming
//    RL_INFO("onMouseScrolled {:.2f}, {:.2f}", sceneMousePosCenterNormalize.x, sceneMousePosCenterNormalize.y);
//    if(e.yOffset >= 0.f)
//        m_cameraController->move(-sceneMousePosCenterNormalize);
//    else
//        m_cameraController->move(sceneMousePosCenterNormalize);
    return false;
}

} // end of namespace rl
