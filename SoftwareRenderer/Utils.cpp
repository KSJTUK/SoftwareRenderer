#include "pch.h"
#include "Utils.h"

Poly::Poly(size_t nVertices) : m_nVertices{ nVertices } {
	m_vertices = new Vertex[m_nVertices]{ };
}

Poly::~Poly() {
	if (m_vertices) delete[] m_vertices;
}

void Poly::SetVertex(size_t index, const Vertex&& vertex) {
	if (0 > index or m_nVertices <= index) exit(EXIT_FAILURE);

	if (m_vertices) {
		m_vertices[index] = vertex;
	}
}
