#include "ComponentSelectionPanel.h"

#include <Rish/Scene/ComponentManager.h>
#include <Rish/Scene/ScriptableEntity.h>

#include <Rish/ImGui.h>
#include <entt/entt.hpp>

namespace rl {

void ComponentSelectionPanel::onImGuiRender()
{
    // TODO: search widget
    std::string filterText;
    ImGui::InputText("##ComponentSelection", &filterText);

    if(ImGui::ListBoxHeader("##Components"))
    {
        auto &mapping = ComponentManager::getAddMapping();
        for (auto &&[k, v] : mapping) {
            if (ImGui::Selectable(k.c_str() + 4))
            {
                ComponentManager::addComponentByTypeName(getSelectedEntity(), k);
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::ListBoxFooter();
    }
}

void ComponentSelectionPanel::onAttach(const Ref<Scene> &scene)
{
    SceneTargetPanel::onAttach(scene);
    ComponentManager::registerComponent<TransformComponent>();
    ComponentManager::registerComponent<RenderComponent>();
    ComponentManager::registerComponent<CameraComponent>();
    ComponentManager::registerComponent<NativeScriptComponent>();
    ComponentManager::registerComponent<RigidBody2DComponent>();
    ComponentManager::registerComponent<BoxCollider2DComponent>();
    ComponentManager::registerComponent<Joint2DComponent>();
    ComponentManager::registerComponent<ParticleComponent>();
}

} // end of namespace rl
