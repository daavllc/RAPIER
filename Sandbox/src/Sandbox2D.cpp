#include "Sandbox2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWDDDDDDDWWWWWWWWWWW"
"WWWWWWDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDDWWW"
"WWWWDDDDDDDDDDDDDDDDDDWW"
"WWWDDDDDDDDDDDDDDDDDDDWW"
"WWDDDDDDDDDDDDDDDDDDDWWW"
"WWDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDWWWDDDDDDDDDDDWWWW"
"WWDDDDWWDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDDDDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDWWWWWW"
"WWDDDDDDDDDDDDDDDDWWWWWW"
"WWDDDDDDDDDDDDDDDDDWWWWW"
"WWDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDDDDDDDDDDDDDDWWWW"
"WWDDDDDWWWWWDDDDDDDDWWWW"
"WWWDDDDWWWWWWDDDDDDDWWWW"
"WWWDDDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWWWWWDDDDDDDWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	RPPROFILE_FUNCTION();

	m_CheckerboardTexture = RAPIER::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = RAPIER::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_Textures['W'] = RAPIER::SubTexture2D::CreateFromCoords(m_SpriteSheet, DrPos2(11, 11), DrSize2(128, 128));
	m_Textures['D'] = RAPIER::SubTexture2D::CreateFromCoords(m_SpriteSheet, DrPos2(6, 11), DrSize2(128, 128));
	m_Textures['G'] = RAPIER::SubTexture2D::CreateFromCoords(m_SpriteSheet, DrPos2(1, 11), DrSize2(128, 128));

	m_ErrTexture = RAPIER::SubTexture2D::CreateFromCoords(m_SpriteSheet, DrPos2(4, 1), DrSize2(128, 128));

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / m_MapWidth;

	m_CameraController.SetZoomLevel(5.0f);

}

void Sandbox2D::OnDetach()
{
	RPPROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(RAPIER::Timestep ts)
{
	RPPROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	
	// Reset Stats here
	RAPIER::Renderer2D::ResetStats();

	// Render
	{
		RPPROFILE_SCOPE("Renderer Prep");

		RAPIER::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RAPIER::RenderCommand::Clear();
	}

	{
		RPPROFILE_SCOPE("Renderer Draw");
		RAPIER::Renderer2D::BeginScene(m_CameraController.GetCamera());

		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		RAPIER::Renderer2D::DrawQuad(DrPos1(0.0f), DrSize2(1.0f, 1.0f), DrColor(0.8f, 0.2f, 0.3f, 1.0f));
		RAPIER::Renderer2D::DrawRotatedQuad(DrPos2(2.0f, 2.0f), DrSize2(1.0f, 1.0f), DrRotate(rotation), DrColor(0.8f, 0.2f, 0.3f, 1.0f));
		RAPIER::Renderer2D::DrawQuad(DrPos2(-1.0f, 0.0f), DrSize2(1.0f, 1.0f), DrColor(0.3f, 0.2f, 0.8f, 1.0f));
		RAPIER::Renderer2D::DrawQuad(DrPos2(0.0f, 1.0f), DrSize2(1.0f, 1.0f), DrColor(0.2f, 0.8f, 0.3f, 1.0f));
		RAPIER::Renderer2D::DrawQuad(DrPos3(0.0f, 0.0f, -0.1f), DrSize2(50.0f, 50.0f), m_CheckerboardTexture);
		RAPIER::Renderer2D::EndScene();

		RAPIER::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//for (float y = -5.0f; y < 5.0f; y += 0.5f)
		//{
		//	for (float x = -5.0f; x < 5.0f; x += 0.5f)
		//	{
		//		DrVec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
		//		RAPIER::Renderer2D::DrawQuad(DrPos2(x, y), DrSize2(0.45f, 0.45f), color);
		//	}
		//}

		for (uint32_t y = 0; y < m_MapHeight; y++)
		{
			for (uint32_t x = 0; x < m_MapWidth; x++)
			{
				char tileType = s_MapTiles[x * y * m_MapWidth];
				RAPIER::Ref<RAPIER::SubTexture2D> texture;
				if (m_Textures.find(tileType) != m_Textures.end())
					texture = m_Textures[tileType];
				else
					texture = m_ErrTexture;

				RAPIER::Renderer2D::DrawQuad(DrPos3( x - m_MapWidth / 2.0f, y - m_MapHeight / 2.0f, 0.5f), DrSize2(1.0f, 1.0f), texture);
			}
		}
		RAPIER::Renderer2D::EndScene();
	}
	
}
void Sandbox2D::OnImGuiRender()
{
	RPPROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = RAPIER::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void Sandbox2D::OnEvent(RAPIER::Event& e)
{
	m_CameraController.OnEvent(e);
}