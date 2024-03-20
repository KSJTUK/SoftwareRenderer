#pragma once

class GameObject {
public:
	GameObject(std::shared_ptr<class Mesh> mesh);
	virtual ~GameObject();

public:
	void Move(const DirectX::XMFLOAT3& shift);
	void Rotate(float yaw, float pitch, float roll);
	virtual void Render(const HDC hDCFrameBuffer);

private:
	std::shared_ptr<class Mesh> m_modelMesh{ };
	DirectX::XMFLOAT3 m_position{ };
	DirectX::XMFLOAT3 m_rotation{ };

	DirectX::XMFLOAT4X4 m_worldTransform{ Matrix4x4::Identity() };

	DWORD m_color{ RGB(0xff, 0x00, 0x00) };

	float m_moveSpeed{ };
	float m_rotationSpeed{ };
};

class Player : public GameObject {
public:
	Player(std::shared_ptr<class Mesh> mesh);
	virtual ~Player();

	void SetCamera(std::shared_ptr<class Camera> camera) { m_eye = camera; }

private:
	std::shared_ptr<class Camera> m_eye{ };
};