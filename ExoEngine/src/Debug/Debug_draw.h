#pragma once

#include "../ExoEngine/Math/Math.h"
#include <glm/glm.hpp>

namespace EM
{
	class draw
	{
	public:
		void SetColour(glm::vec4 colour);
		void SetPos(Vec2 Pos);
		void Draw_Line(Vec2 NewPos);
		void Draw_Circle(Vec2 center, float radius);
		void Draw_Rect(Vec2 center, float size);
		void Draw_Seg(Vec2 start, Vec2 end);
		

			static draw Instance;
	private:
		friend class Graphics;
		void Flush();
		struct LineSet
		{
			glm::vec4 Colour;
			unsigned Segments;
		};

		struct LineSeg
		{
			Vec2 A;
			Vec2 B;
		};

		Vec2 CurrPos;
		glm::vec4 Colour;
		unsigned SegDrawn;
		std::vector<LineSet> Set_list;
		std::vector<LineSeg> LineSeg_list;
		void Clear();

		};
}

