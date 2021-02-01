#include "evpch.h"
#include "Render/Renderer2D.h"
#include "Entity.h"
#include "Scene.h"
#include "Component.h"

namespace Envii
{
	void Scene::OnUpdate(TimeStep ts)
	{
		// Update scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, NativeScriptComponent& nsc)
		{
			if (!nsc.scriptable)
			{
				nsc.scriptable = nsc.InstantiateScript();
				nsc.scriptable->m_Entity = Entity(entity, this);
				nsc.scriptable->OnCreate();
			}
			nsc.scriptable->OnUpdate(ts);
		});


		Camera* mainCamera = nullptr;
		glm::mat4 camTransform;
		auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
		for (auto entity : group)
		{
			auto [camera, transform] = group.get<CameraComponent, TransformComponent>(entity);
			if (camera.Primary)
			{
				mainCamera = &camera.Cam;
				camTransform = transform.GetTransform();
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, camTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity); 
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}
			Renderer2D::EndScene();

		}
	}

	void Scene::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrollEvent>(EV_BIND_EVENT_CB(Scene::OnMouseScrollEvent));
	}

	bool Scene::OnMouseScrollEvent(MouseScrollEvent& event)
	{
		// Update scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, NativeScriptComponent& nsc)
		{
			if (!nsc.scriptable)
			{
				nsc.scriptable = nsc.InstantiateScript();
				nsc.scriptable->m_Entity = Entity(entity, this);
				nsc.scriptable->OnCreate();
			}
			nsc.scriptable->OnMouseScrollEvent(event);
		});
		return true;
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
