/*!*************************************************************************
****
\file WinData.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Window Component used to stored data regarding the window such as
height and width of the window

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#pragma once
#include "IComponent.h"
#include "empch.h"

namespace EM
{
	//Window Component
	class WinData : public JSONSerializer
	{
	public:
		WinData();
		~WinData() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		std::string GetTitle() { return mTitle; }
		unsigned int GetWidth() { return mWidth; }
		unsigned int GetHeight() { return mHeight; }
		unsigned int GetCurrWidth() { return mCurrentWidth; }
		unsigned int GetCurrHeight() { return mCurrentHeight; }

		void SetTitle(std::string Title) { mTitle = Title; }
		void SetWidth(unsigned int Width) { mWidth = Width; }
		void SetHeight(unsigned int Height) { mHeight = Height; }
		void SetCurrWidth(unsigned int CurrWidth) { mCurrentWidth = CurrWidth; }
		void SetCurrHeight(unsigned int CurrHeight) { mCurrentHeight = CurrHeight; }

	private:
		std::string mTitle;
		unsigned int mWidth,
			mHeight,
			mCurrentWidth,
			mCurrentHeight;
	};
}