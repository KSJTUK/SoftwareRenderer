#pragma once

// Data types
// --------------------------------------------------
struct Vertex {
	DirectX::XMFLOAT3 position{ };
};

class Poly {
public:
	Poly() = default;
	Poly(size_t nVertices);
	~Poly();

public:
	void SetVertex(size_t size, const Vertex&& vertex);
	
public:
	size_t m_nVertices{ };
	Vertex* m_vertices{ nullptr };
};
// ---------------------------------------------------

namespace Matrix4x4 {
	inline DirectX::XMFLOAT4X4 Identity()
	{
		DirectX::XMFLOAT4X4 rtMatrix{ };
		DirectX::XMStoreFloat4x4(&rtMatrix, DirectX::XMMatrixIdentity());
		return rtMatrix;
	}
}