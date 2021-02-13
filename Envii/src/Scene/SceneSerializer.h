#pragma once

#include "Scene.h"

namespace Envii
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);
		virtual ~SceneSerializer() {}

		void SerializeText(const std::string& filepath);
		void SerializeBinary(const std::string& filepath);

		bool DeserializeText(const std::string& filepath);
		bool DeserializeBinary(const std::string& filepath);

	private:
		Ref<Scene> m_Scene;
	};
}