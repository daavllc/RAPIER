#pragma once

#include <DAGGer.h>
#include "ParticleSystem.h"

class Sandbox2D : public DAGGer::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(DAGGer::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(DAGGer::Event& e) override;
private:
	DAGGer::OrthographicCameraController m_CameraController;

	DAGGer::Ref<DAGGer::Texture2D> m_CheckerboardTexture;
	DAGGer::Ref<DAGGer::Texture2D> m_SpriteSheet;

	std::unordered_map<char, DAGGer::Ref<DAGGer::SubTexture2D>> m_Textures;
	DAGGer::Ref<DAGGer::SubTexture2D> m_ErrTexture;
	uint32_t m_MapWidth, m_MapHeight = 0;

};