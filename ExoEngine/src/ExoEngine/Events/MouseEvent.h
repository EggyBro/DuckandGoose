#pragma once
#include "EventHandler.h"

namespace EM {


	class MouseMove : public EventHandler
	{
	public:
		MouseMove(float x, float y)
			: m_CursorX(x), m_CursorY(y) {}

		inline float GetCursorX() const { return m_CursorX; }
		inline float GetCursorY() const { return m_CursorY; }

		//for debug purpose
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoved:" << m_CursorX << ", " << m_CursorY;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MovingMouse"; }

		virtual int GetEventFlags() const override {
			return EventSetFlag::EventSetMouse | EventSetFlag::EventSetInput;
		}

	private:
		float m_CursorX, m_CursorY;
	};


	class MouseScrolled: public EventHandler
	{
	public:
		MouseScrolled(float offsetX, float offsetY)
			: m_offsetX(offsetX), m_offsetY(offsetX) {}

		inline float GetXOffset() const { return m_offsetX; }
		inline float GetYOffset() const { return m_offsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolled: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MovingMouse"; }

		virtual int GetEventFlags() const override {
			return EventSetFlag::EventSetMouse | EventSetFlag::EventSetInput;
		}
	private:
		float m_offsetX, m_offsetY;
	};


	class MouseButton : public EventHandler
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		virtual int GetEventFlags() const override {
			return EventSetFlag::EventSetMouse | EventSetFlag::EventSetInput;
		}

	protected:
		MouseButton(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class MouseButtonPressed : public MouseButton
	{
	public:
		MouseButtonPressed(int button)
			: MouseButton(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonPressed"; }
	};


	class MouseButtonReleased : public MouseButton
	{
	public:
		MouseButtonReleased(int button)
			: MouseButton(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonReleased"; }
	};
}