#pragma once

#include <DAGGer.h>

class ExampleLayer : public DAGGer::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DAGGer::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DAGGer::Event& e) override;
private:
	DAGGer::ShaderLibrary m_ShaderLibrary;
	DAGGer::Ref<DAGGer::Shader> m_Shader;
	DAGGer::Ref<DAGGer::VertexArray> m_VertexArray;

	DAGGer::Ref<DAGGer::Shader> m_FlatColorShader;
	DAGGer::Ref<DAGGer::VertexArray> m_SquareVA;

	DAGGer::Ref<DAGGer::Texture2D> m_Texture, m_ChernoLogoTexture;

	DAGGer::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};