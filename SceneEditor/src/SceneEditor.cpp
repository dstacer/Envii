#include <iostream>

#include "EntryPoint.h"
#include "SceneEditor.h"
#include "EditorLayer.h"

namespace Envii
{
	SceneEditor::SceneEditor()
		: App("Envii Editor")
	{
		PushLayer(new EditorLayer());
	}

	SceneEditor::~SceneEditor()
	{
	}

	App* CreateApp()
	{
		return new SceneEditor();
	}
}
