#pragma once

#include "Math/Math.hpp"
#include <memory>

namespace Cardboard
{

	class Triangle
	{
	public:
		Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 color);
		~Triangle();

		void UpdateVertexPositions(Vector3 v1, Vector3 v2, Vector3 v3);
		void Render();

	private:
		uint32_t m_VertexArray;
		uint32_t m_VertexBuffer;

		Vector3 m_Color;
	};

}