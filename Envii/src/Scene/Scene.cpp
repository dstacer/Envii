#include "evpch.h"
#include "Render/Renderer2D.h"
#include "Entity.h"
#include "Scene.h"

namespace Envii
{
	void Scene::OnUpdate(TimeStep ts)
	{
		
		Camera* mainCamera = nullptr;
		glm::mat4* camTransform;
		auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
		for (auto entity : group)
		{
			auto& [camera, transform] = group.get<CameraComponent, TransformComponent>(entity);
			if (camera.Primary)
			{
				mainCamera = &camera.Cam;
				camTransform = &transform.Transform;
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *camTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity); 
				Renderer2D::DrawQuad(transform, sprite.Color);
			}
			Renderer2D::EndScene();

		}
	}

	Entity Scene::CreateEntity(const std::string& tagName)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(tagName);
		return entity;
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);
			if (!camera.FixedAspect)
			{
				camera.Cam.SetViewportSize(width, height);
			}
		}
	}
}
