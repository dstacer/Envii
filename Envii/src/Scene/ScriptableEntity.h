#pragma once

#include "Entity.h"

namespace Envii
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

		template<typename T> 
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnMouseScrollEvent(MouseScrollEvent e) {}

	private:
		Entity m_Entity;

		friend class Scene;
	};
}