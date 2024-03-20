#include "pch.h"
#include "Camera.h"

void Viewport::SetViewPort(INT32 left, INT32 top, INT32 width, INT32 height) {
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
}

// --------------------------------------------------------------------------------------------
void Camera::SetFOVAngle(float FOVAngle) {
	m_FOVAngle = FOVAngle;
	m_projectRectDist = 1.f / std::tanf(DirectX::XMConvertToRadians(m_FOVAngle * 0.5f));
}

void Camera::GenerateViewMatrix() {
	DirectX::XMVECTOR look{ DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_look)) };
	DirectX::XMVECTOR up{ DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_up)) };
	DirectX::XMVECTOR right{ DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up, look)) };
	up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(look, right));

	DirectX::XMStoreFloat3(&m_look, look);
	DirectX::XMStoreFloat3(&m_right, right);
	DirectX::XMStoreFloat3(&m_up, up);

	m_view._11 = m_right.x; m_view._12 = m_up.x; m_view._13 = m_look.x;
	m_view._21 = m_right.y; m_view._22 = m_up.y; m_view._23 = m_look.y;
	m_view._31 = m_right.z; m_view._32 = m_up.z; m_view._33 = m_look.z;

	DirectX::XMVECTOR xmvPosition = DirectX::XMLoadFloat3(&m_position);
	m_view._41 = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(xmvPosition, right));
	m_view._42 = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(xmvPosition, up));
	m_view._43 = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(xmvPosition, look));

	DirectX::XMStoreFloat4x4(&m_viewPerspectiveProject, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&m_view), DirectX::XMLoadFloat4x4(&m_perspectiveProject)));
}

void Camera::GeneratePerspectiveProjectionMatrix(float nearPlaneDitance, float farPlaneDistance, float FOVAngle) {
	DirectX::XMStoreFloat4x4(&m_perspectiveProject, DirectX::XMMatrixPerspectiveFovRH(m_FOVAngle, m_aspectRatio, nearPlaneDitance, farPlaneDistance));
}

void Camera::SetViewport(int left, int top, int width, int height) {
	m_viewport.SetViewPort(left, top, width, height);
	m_aspectRatio = m_viewport.width / static_cast<float>(m_viewport.height);
}

void Camera::SetLookAt(DirectX::XMFLOAT3& position, DirectX::XMFLOAT3& lookAt, DirectX::XMFLOAT3& up) {
	m_position = position;
	DirectX::XMStoreFloat4x4(&m_view, DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&m_position), DirectX::XMLoadFloat3(&lookAt), DirectX::XMLoadFloat3(&up)));

	DirectX::XMVECTORF32 rightVec{ m_view._11, m_view._21, m_view._31, 0.0f };
	DirectX::XMVECTORF32 upVec{ m_view._12, m_view._22, m_view._32, 0.0f };
	DirectX::XMVECTORF32 lookVec{ m_view._13, m_view._23, m_view._33, 0.0f };

	DirectX::XMStoreFloat3(&m_right, DirectX::XMVector3Normalize(rightVec));
	DirectX::XMStoreFloat3(&m_up, DirectX::XMVector3Normalize(upVec));
	DirectX::XMStoreFloat3(&m_look, DirectX::XMVector3Normalize(lookVec));
}

void Camera::SetLookAt(DirectX::XMFLOAT3& lookAt, DirectX::XMFLOAT3& up) {
	SetLookAt(m_position, lookAt, up);
}
