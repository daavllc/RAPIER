#pragma once

#include <RAPIER.h>

class ExampleLayer : public RAPIER::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(RAPIER::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(RAPIER::Event& e) override;
private:
	RAPIER::ShaderLibrary m_ShaderLibrary;
	RAPIER::Ref<RAPIER::Shader> m_Shader;
	RAPIER::Ref<RAPIER::VertexArray> m_VertexArray;

	RAPIER::Ref<RAPIER::Shader> m_FlatColorShader;
	RAPIER::Ref<RAPIER::VertexArray> m_SquareVA;

	RAPIER::Ref<RAPIER::Texture2D> m_Texture, m_ChernoLogoTexture;

	RAPIER::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};