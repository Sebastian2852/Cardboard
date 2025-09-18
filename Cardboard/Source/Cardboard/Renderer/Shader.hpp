#pragma once

#include <string>

namespace Cardboard
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;

	private:
		uint32_t m_RendererId;
	};
}