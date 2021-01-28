#pragma once

#include "Entt.hpp"
#include "../Core/Timestep.h"
//#include "Component.h"

namespace Envii
{
	class Entity;
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() {}

		void OnUpdate(TimeStep ts);

		Entity CreateEntity(const std::string& name = "UnnamedEntity");
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}