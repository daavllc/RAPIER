#include "drpch.h"
#include "SubTexture2D.h"

namespace DAGGer
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
	{
		uint32_t AddX = 1;
		uint32_t AddY = spriteSize.y / spriteSize.x;
		if (AddY == 0)
		{
			AddX = spriteSize.x / spriteSize.y;
			if (AddX == 0)
			{
				AddX = 1;
				AddY = 1;
			}
		}
		glm::vec2 min = { (coords.x * (spriteSize.x / AddX)) / texture->GetWidth(), (coords.y * (spriteSize.y / AddY)) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + AddX) * (spriteSize.x / AddX)) / texture->GetWidth(), ((coords.y + AddY) * (spriteSize.y / AddY)) / texture->GetHeight() };
		return CreateRef<SubTexture2D>(texture, min, max);
	}

}	//	END namespace DAGGer