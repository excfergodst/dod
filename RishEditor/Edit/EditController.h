#pragma once

#include <Rish/rlpch.h>
#include <Rish/Events/Event.h>

#include "Panels/SceneTargetPanel.h"
#include "Edit/EditorGrid.h"

namespace rl {

class RL_API EditController : public SceneTargetPanel
{
public:
    EditController();
    ~EditController() override = default;
    //
    void onAttach(const Ref<Scene> &scene) override;
    void onDetach() override;
    void onUpdate(Time dt) override;
    void onImGuiRender() override;
    void onEvent(Event &e);

    Ref<OrthographicCameraController> getCameraController() const { return m_cameraController; }
private:
    EditorGrid m_editorGrid;                              ///< Editor grid
    Ref<OrthographicCameraController> m_cameraController; ///< Editor camera

    // Attributes of current selected entity
    glm::vec3 m_curEntPos{}, m_curSize{};

    glm::vec3 m_moveEntityDiff{0.f};
    bool m_isNowMovingEntity = false;

    glm::vec2 m_curMousePosInCamera;
    glm::vec2 m_preMousePosInCamera;

    bool m_sceneWindowFocused = false; ///< Is Scene window focused?
    bool m_sceneWindowHovered = false; ///< Is Scene window hovered?
public:
    bool m_debugEditorGrid = false;
    bool m_debugCameraController = false;
};

} // end of namespace rl


