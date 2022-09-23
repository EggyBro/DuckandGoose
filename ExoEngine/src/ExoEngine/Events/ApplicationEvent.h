#pragma once
#include "ExoEngine/Events/EventHandler.h"

namespace EM {


	class WindowResizingEvent : public EventHandler
	{
	public:
		WindowResizingEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resizing Event: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowResized"; }
		
		virtual int GetEventFlags() const override {
			return EventSetFlag::EventSetApplication;
		}
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowClosing : public EventHandler
	{
	public:
		WindowClosing() = default;
		
		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowClosed"; }

		virtual int GetEventFlags() const override {
			return EventSetFlag::EventSetApplication;
		}
	};
}