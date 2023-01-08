#pragma once
#include "../Core.h"
#include <string>
#include <functional>

namespace Miros {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, Windowfocus, WindowLostFocus, WindowMoived,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryAppication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

//ʹ�ú�ѹ�� ��������
#define  EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
								virtual EventType GetEventType() const override { return GetEventType(); }\
								virtual const char* GetName() const override{return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override{return category;}

	class MIROS_API Event {
		friend class EventDispather;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}


	protected:
		bool m_Handled = false;
	};


	class  EventDispather {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispather(Event& event) 
			:m_Event(event){}


		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	//����
	//std::ostream& operator<<(std::ostream& os, const Event& e) {
	//	return os << e.ToString();
	//}

}