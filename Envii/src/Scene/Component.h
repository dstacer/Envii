#pragma once

#include <functional>
#include <glm/glm.hpp>
#include "../Render/SceneCamera.h"
#include "ScriptableEntity.h"

namespace Envii
{
	struct MeshComponent
	{
		bool flag = false;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tagName)
			: Tag(tagName) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.f, 1.f, 1.f, 1.f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Cam;
		bool Primary = true;
		bool FixedAspect = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* script = nullptr;
		// Creation/Destruction
		std::function<void()> InstanceFunc;
		std::function<void()> DeInstanceFunc;

		// ScriptableEntity Iface
		std::function<void()> OnCreateFunc;
		std::function<void()> OnDestroyFunc;
		std::function<void(TimeStep ts)> OnUpdateFunc;

		template<typename T>
		void Bind()
		{
			InstanceFunc =   [&]() { script = new T(); };
			DeInstanceFunc = [&]() { delete (T*)script; };
			OnCreateFunc =   [&]() { ((T*)script)->OnCreate(); };
			OnDestroyFunc =  [&]() { ((T*)script)->OnDestroy(); };
			OnUpdateFunc =   [&](TimeStep ts) { ((T*)script)->OnUpdate(ts); };
		}
	};
}
