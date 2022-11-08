#pragma once
#include "IComponent.h"
#include "empch.h"

namespace EM
{
	//Window Component
	class WinData : public IComponent
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