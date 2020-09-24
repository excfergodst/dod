#include <RishEngine.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ComponentEditPanel.h"
#include "Panels/ComponentSelectionPanel.h"
#include "Panels/ErrorModal.h"

#include "Edit/EditorGrid.h"
#include "Edit/EditController.h"

namespace rl {

class EditorLayer : public Layer
{
public:
	EditorLayer();

	virtual ~EditorLayer() = default;
	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onUpdate(Time dt) override;
	virtual void onImGuiRender() override;
	virtual void onEvent(rl::Event& event) override;

private:
    void onImGuiMainMenuRender();

    // Debug
    Entity debugEntity;
    std::unordered_map<UUID, int> test;

    //////////////////////////////////////////
    // Editor Layer
    //////////////////////////////////////////

    enum class SceneState
    {
        Editor = 0,
        Play,
        Pause
    };
    SceneState m_sceneState = SceneState::Editor;

    //////////////////////////////////////////
    // Scene
    //////////////////////////////////////////
	Ref<Framebuffer> m_editorFramebuffer;
    //
	Ref<Framebuffer> m_sceneFramebuffer;
    Ref<Scene> m_scene;        /// Current Scene
    Ref<Scene> m_editorScene;  /// Editor Scene
    Ref<Scene> m_runtimeScene; /// Runtime Scene
	//
	std::string m_scenePath;
	bool m_sceneLoaded = false;
    glm::vec2 m_sceneViewportPanelSize {0.f, 0.f};

    //////////////////////////////////////////
    // Editor Panels
    //////////////////////////////////////////
	Ref<EditController> m_editController;
    Ref<SceneHierarchyPanel> m_sceneHierarchyPanel;
    Ref<ComponentEditPanel> m_componentEditPanel;

	std::vector<Ref<ScenePanel>> m_panelList;

    //////////////////////////////////////////
    // Common Widgets
    //////////////////////////////////////////
	ErrorModal m_errorModal;
};

}
