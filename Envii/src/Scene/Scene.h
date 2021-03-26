#pragma once

#include "Entt.hpp"
#include "../Core/Timestep.h"
#include "../Events/MouseEvent.h"
#include "../Core/Core.h"

namespace Envii
{
	class Entity;
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() {}

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& event);
		bool OnMouseScrollEvent(MouseScrollEvent& event);

		Entity CreateEntity(const std::string& name = "UnnamedEntity");
		void DestroyEntity(Entity entity);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCamera();

	private:
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneGraphPanel;
		friend class SceneSerializer;
	};
}