#pragma once
#include "empch.h"

#include "ExoEngine/Core.h"

namespace EM {
	//Event handler will dispath immediately 
	enum class EventType
	{
		None = 0,
		//For window
		WindowClose, WindowResize, WindowMoved,
		//For keyboard
		KeyPressed, KeyReleased,
		// for mouse
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventSetFlag //to filter all the different event
	{
		None = 0,
		EventSetApplication  = BIT(0),
		EventSetInput		 = BIT(1),
		EventSetKeyInput	 = BIT(2),
		EventSetMouse		 = BIT(3),
		EventSetMouseButtion = BIT(4)
	};


	class EM_API EventHandler
	{
	public:
		bool Handle = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventFlags() const = 0; // indicate which event is ongoing 
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInEvent(EventSetFlag setter)
		{
			return GetEventFlags() & setter;
		}
	};

	class EventDispatcher
	{
		template<typename T> // can be any event type
		using EventFunction = std::function<bool(T&)>;
	public:

		EventDispatcher(EventHandler& event) :m_Event(event) {}

		
		template<typename T>
		bool Dispatch(EventFunction<T> function)
		{ 
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handle = function(*(T*)&m_Event);
				return true;
			}

			return false;
		}

	private:
		EventHandler& m_Event;

	};

	inline std::ostream& operator<<(std::ostream& os, const EventHandler& event)
	{
		return os << event.ToString();
	}
}
