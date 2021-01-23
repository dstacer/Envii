#pragma once

#include "Entt.hpp"
#include "../Core/Timestep.h"
#include "Component.h"

namespace Envii
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() {}

		void OnUpdate(TimeStep ts);

		Entity CreateEntity(const std::string& name = "UnnamedEntity");

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}