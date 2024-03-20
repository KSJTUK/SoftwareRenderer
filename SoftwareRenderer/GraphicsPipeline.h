#pragma once

class GraphicsPipeline {
private:
	static DirectX::XMFLOAT4X4* m_world;
	static DirectX::XMFLOAT4X4 * m_viewProjection;
	static struct Viewport* m_viewport;

public:
	static void SetWorldTransform(DirectX::XMFLOAT4X4* world) { m_world = world; }
	static void SetViewPerspectiveProjectTransform(DirectX::XMFLOAT4X4* viewPerspectiveProject);
	static void SetViewport(struct Viewport* viewport) { m_viewport = viewport; }

	static DirectX::XMFLOAT3 ScreenTransform(DirectX::XMFLOAT3& project);
	static DirectX::XMFLOAT3 Project(DirectX::XMFLOAT3& model);
};