#include "evpch.h"
#include "Render/Renderer2D.h"
#include "Entity.h"
#include "Scene.h"

namespace Envii
{
	Envii::Scene::Scene()
	{
		
	}
	
	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity); 
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}

	Entity Scene::CreateEntity(const std::string& tagName)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(tagName);
		return entity;
	}
}
