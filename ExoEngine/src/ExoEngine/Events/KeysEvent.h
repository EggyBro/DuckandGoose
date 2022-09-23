#pragma once
#include "EventHandler.h"

namespace EM {

	//just a key event to handle pressed & released
	class EM_API KeysEvent : public EventHandler
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; } // will be reading from glfw_keycode
		virtual int GetEventFlags() const override { return EventSetFlag::EventSetKeyInput| EventSetFlag::EventSetInput; }
	protected:
		KeysEvent(int keycode)
			:m_KeyCode(keycode) {}

			int m_KeyCode;
	};
	
	class KeyIsPressed : public KeysEvent
	{
	public:
		//ctor
		KeyIsPressed(int keycode, int repeatedcount)
			:KeysEvent(keycode), m_Count(repeatedcount) {}

		inline int GetRepeatedCount() const { return m_Count; }

		//for debug purpose
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed:" << m_KeyCode << " " << m_Count << "times";
			return ss.str();
		}
		
		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override {return GetStaticType();}
		virtual const char* GetName() const override { return "KeyPressed"; }
	private:
		int m_Count; //count the number of times the same key has been pressed
	};

	class KeyReleased : public KeysEvent
	{
	public:
		KeyReleased(int keycode)
			:KeysEvent(keycode){}
		
		//debug Purpose
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << m_KeyCode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleased"; }
	};
	/*
	class KeyTyped : public KeysEvent
	{
	public:
		KeyTyped(int keycode)
			: KeysEvent(keycode) {}
		//debug Purpose
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << m_KeyCode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleased"; }
	};
	*/
}