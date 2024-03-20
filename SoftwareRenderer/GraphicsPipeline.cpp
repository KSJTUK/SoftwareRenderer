#include "pch.h"
#include "GraphicsPipeline.h"
#include "Camera.h"

DirectX::XMFLOAT4X4* GraphicsPipeline::m_world = nullptr;
DirectX::XMFLOAT4X4* GraphicsPipeline::m_viewProjection = nullptr;
Viewport* GraphicsPipeline::m_viewport = nullptr;

void GraphicsPipeline::SetViewPerspectiveProjectTransform(DirectX::XMFLOAT4X4* viewPerspectiveProject) {
	m_viewProjection = viewPerspectiveProject;
}

DirectX::XMFLOAT3 GraphicsPipeline::ScreenTransform(DirectX::XMFLOAT3& project) {
	DirectX::XMFLOAT3 screen = project;

	float halfWidth = m_viewport->width * 0.5f;
	float halfHeight = m_viewport->height * 0.5f;
	screen.x = m_viewport->left + (project.x * halfWidth) + halfWidth;
	screen.y = m_viewport->top + (-project.y * halfHeight) + halfHeight;

	return screen;
}

DirectX::XMFLOAT3 GraphicsPipeline::Project(DirectX::XMFLOAT3& model) {
	DirectX::XMMATRIX modelToProject = DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(m_world), DirectX::XMLoadFloat4x4(m_viewProjection));
	DirectX::XMFLOAT3 project{ };

	XMStoreFloat3(&project, DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&model), modelToProject));

	return project;
}
