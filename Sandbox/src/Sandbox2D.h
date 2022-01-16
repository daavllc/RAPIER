#pragma once

#include <RAPIER.h>
#include "ParticleSystem.h"

class Sandbox2D : public RAPIER::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(RAPIER::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(RAPIER::Event& e) override;
private:
	RAPIER::OrthographicCameraController m_CameraController;

	RAPIER::Ref<RAPIER::Texture2D> m_CheckerboardTexture;
	RAPIER::Ref<RAPIER::Texture2D> m_SpriteSheet;

	std::unordered_map<char, RAPIER::Ref<RAPIER::SubTexture2D>> m_Textures;
	RAPIER::Ref<RAPIER::SubTexture2D> m_ErrTexture;
	uint32_t m_MapWidth, m_MapHeight = 0;

};