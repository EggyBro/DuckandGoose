#include "Debug_draw.h"
#include "../src/empch.h"

namespace EM
{
	draw draw::Instance;

	void draw::Flush()
	{
		if (SegDrawn>0)
		{
			LineSet set = { Colour , SegDrawn };
			Set_list.push_back(set);
			SegDrawn = 0;
		}
	}

	void draw::SetPos(Vec2 Pos)
	{
		CurrPos = Pos;
	}

	void draw::SetColour(glm::vec4 colour)
	{
		Flush();
		Colour = colour;
	}

	void draw::Draw_Line(Vec2 NewPos)
	{
		LineSeg curr_seg{ CurrPos,NewPos };
		LineSeg_list.push_back(curr_seg);
		++SegDrawn;
		CurrPos = NewPos;
	}

	void draw::Clear() //clears the total line segments
	{
		SegDrawn = 0;
		Set_list.clear();
		LineSeg_list.clear();
	}

	void draw::Draw_Seg(Vec2 start, Vec2 end) //Draws the line segment
	{
		SetPos(start);
		Draw_Line(end);;
	}

	void  draw::Draw_Circle(Vec2 center, float radius) //draws a circle around the point
	{
		const unsigned numberOfSegments = 16;
		const float increment = 2.0f * (PI) / float(numberOfSegments);

		float theta = 0.0f;
		SetPos(center + radius * Vec2(cosf(theta), sinf(theta)));
		for (unsigned i = 1; i <= numberOfSegments; ++i)
		{
			Draw_Line(center + radius * Vec2(cosf(increment * i), sinf(increment * i)));
		}
	}

	void  draw::Draw_Rect(Vec2 center, float size)
	{
		
		SetPos(center + Vec2(size/2.0f, size / 2.0f));
		Draw_Line(center + Vec2(size/2.0f, -size/2.0f));
		Draw_Line(center + Vec2(-size/2.0f, -size/2.0f));
		Draw_Line(center + Vec2(-size/2.0f, size/2.0f));
		Draw_Line(center + Vec2(size/2.0f, size/2.0f));
	}

}