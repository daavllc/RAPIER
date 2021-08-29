/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted definition for GraphicsContexts
////////////////////////////////
#pragma once

namespace DAGGer
{
	struct GraphicsInfo
	{
		int TextureSlots;
		int MaxTextureCoords;
		int MaxCombinedTextureImageUnits;
	};

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);

	};	//	END class GraphicsContext

}	//	END namespace DAGGer
