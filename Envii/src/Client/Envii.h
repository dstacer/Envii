#pragma once

// This is an include file for client apps only
#include "../Core/App.h"
#include "../Core/Layer.h"
#include "../Core/Log.h"
#include "../Core/Timestep.h"
#include "../Core/Profiler.h"

// Input
#include "../Core/Input.h"
#include "../Core/KeyCodes.h"
#include "../Core/MouseButtonCodes.h"

// UI
#include "../Imgui/ImguiLayer.h"

// Render
#include "../Render/Renderer.h"
#include "../Render/Renderer2D.h"
#include "../Render/RenderCommand.h"

#include "../Render/VertexArray.h"
#include "../Render/Buffer.h"
#include "../Render/FrameBuffer.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "../Render/SubTexture2D.h"

#include "../Render/CameraController.h"

// Scene
#include "../Scene/Scene.h"
#include "../Scene/Entity.h"
#include "../Scene/Component.h"
#include "../Scene/ScriptableEntity.h"
#include "../Scene/SceneSerializer.h"


// Utils
#include "../Utils/PlatformUtils.h"
#include "../Math/Math.h"
