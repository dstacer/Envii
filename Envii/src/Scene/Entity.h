#pragma once

#include "Scene.h"

namespace Envii
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity id, Scene* scene);
		Entity(const Entity& other) = default;
		virtual ~Entity() {};

		template<typename T> bool HasComponent() 
		{ 
			return m_Scene->m_Registry.has<T>(m_Id); 
		}

		template<typename T> T& GetComponent() 
		{ 
			EV_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have this component."); 
			return m_Scene->m_Registry.get<T>(m_Id);
		}

		template<typename T> void RemoveComponent()
		{
			EV_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have this component.");
			return m_Scene->m_Registry.remove<T>(m_Id);
		}

		template<typename T, typename... Args> T& AddComponent(Args&&... args)
		{
			EV_CORE_ASSERT(!HasComponent<T>(), "Entity already has component.");
			return m_Scene->m_Registry.emplace<T>(m_Id, std::forward<Args>(args)...);
		}

		operator bool() const { return m_Id != entt::null; }
		operator uint32_t() const { return (uint32_t)m_Id; }
		operator entt::entity() const { return m_Id; }

		bool operator==(const Entity& other) const 
		{
			return (m_Id == other.m_Id && m_Scene == other.m_Scene);
		}

		bool operator!=(const Entity& other) const { return !(*this == other); }

	private:
		entt::entity m_Id{ entt::null };
		Scene* m_Scene = nullptr;
	};
}
