#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
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
		glm::vec3 Translation = { 0.f, 0.f, 0.f };
		glm::vec3 Rotation = { 0.f, 0.f, 0.f };
		glm::vec3 Scale = { 1.f, 1.f, 1.f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const 
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), Translation);
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
			glm::mat4 scale = glm::scale(glm::mat4(1.f), Scale);

			return translation * rotation * scale;
		}
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
		ScriptableEntity* scriptable = nullptr;
		
		// Creation/Destruction
		std::function<ScriptableEntity*()> InstantiateScript;
		std::function<void()> DestroyScript;

		template<typename T>
		void Bind()
		{
			InstantiateScript = [&]() { return new T(); };
			DestroyScript =		[&]() { delete (T*)scriptable; scriptable = nullptr; };
		}
	};
}
