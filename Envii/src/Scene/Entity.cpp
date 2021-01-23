#include "evpch.h"
#include "Entity.h"

namespace Envii
{
	Envii::Entity::Entity(entt::entity id, Scene* scene)
		: m_Id(id),
		  m_Scene(scene) { }
}
