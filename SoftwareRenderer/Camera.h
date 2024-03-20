#pragma once

struct Viewport {
	INT32 left{ };
	INT32 top{ };
	INT32 width{ };
	INT32 height{ };

	void SetViewPort(INT32 left, INT32 top, INT32 width, INT32 height);
};

class Camera {
public:
	DirectX::XMFLOAT4X4			m_view{ Matrix4x4::Identity() };
	DirectX::XMFLOAT4X4			m_perspectiveProject{ Matrix4x4::Identity() };
	DirectX::XMFLOAT4X4			m_viewPerspectiveProject{ Matrix4x4::Identity() };

	Viewport					m_viewport{ };

public:
	void SetFOVAngle(float FOVAngle);

	void GenerateViewMatrix();
	void GeneratePerspectiveProjectionMatrix(float nearPlaneDitance, float farPlaneDistance, float FOVAngle);
	void SetViewport(int left, int top, int width, int height);

	void SetLookAt(DirectX::XMFLOAT3& position, DirectX::XMFLOAT3& lookAt, DirectX::XMFLOAT3& up);
	void SetLookAt(DirectX::XMFLOAT3& lookAt, DirectX::XMFLOAT3& up);

	void Move(const DirectX::XMFLOAT3& shift);
	void Move(float x, float y, float z);
	void Rotate(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f);
	//void Update(Player* player, DirectX::XMFLOAT3& lookAt, float timeElapsed = 0.016f);

private:
	DirectX::XMFLOAT3 m_position{ };
	DirectX::XMFLOAT3 m_right{ 1.f, 0.f, 0.f };
	DirectX::XMFLOAT3 m_up{ 0.f, 1.f, 0.f };
	DirectX::XMFLOAT3 m_look{ 0.f, 0.f, 1.f };

	float m_FOVAngle{ 90.f };
	float m_projectRectDist{ 1.f };
	float m_aspectRatio{ FRAMEBUFFER_WIDTH / static_cast<float>(FRAMEBUFFER_HEIGHT) };
};

