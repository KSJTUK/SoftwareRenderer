#include "pch.h"
#include "GameObject.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"

GameObject::GameObject(std::shared_ptr<class Mesh> mesh) : m_modelMesh{ mesh } { }

GameObject::~GameObject() { }

void GameObject::Move(const DirectX::XMFLOAT3& shift) { 
	
}

void GameObject::Rotate(float yaw, float pitch, float roll) {

}

void GameObject::Render(const HDC hDCFrameBuffer) {
	if (m_modelMesh) {
		GraphicsPipeline::SetWorldTransform(std::addressof(m_worldTransform));

		HPEN hPen{ ::CreatePen(PS_SOLID, 0, m_color) };
		HPEN hOldPen{ reinterpret_cast<HPEN>(::SelectObject(hDCFrameBuffer, hPen)) };

		
		m_modelMesh->Render(hDCFrameBuffer);

		::SelectObject(hDCFrameBuffer, hOldPen);
		::DeleteObject(hPen);
	}
}

// -------------------------------------------------------------------------------
Player::Player(std::shared_ptr<class Mesh> mesh) : GameObject{ mesh } { }

Player::~Player() { }
