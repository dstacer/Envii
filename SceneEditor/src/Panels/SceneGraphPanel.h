#pragma once

#include "../Scene/Scene.h"
#include "../Scene/Entity.h"

namespace Envii
{
	class SceneGraphPanel
	{
	public:
		SceneGraphPanel() = default;
		SceneGraphPanel(const Ref<Scene>& scene);
		virtual ~SceneGraphPanel() {}

		void SetScene(const Ref<Scene>& scene);
		void OnImguiRender();

		Entity GetSelectedEntity() const { return m_Selected; }
		
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Scene;
		Entity m_Selected;
	};
}
