#pragma once

namespace Mizu {
	typedef enum class MouseCode : uint16_t
	{
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,
								 
		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define MZ_MOUSE_BUTTON_0         ::Mizu::Mouse::Button0
#define MZ_MOUSE_BUTTON_1         ::Mizu::Mouse::Button1
#define MZ_MOUSE_BUTTON_2         ::Mizu::Mouse::Button2
#define MZ_MOUSE_BUTTON_3         ::Mizu::Mouse::Button3
#define MZ_MOUSE_BUTTON_4         ::Mizu::Mouse::Button4
#define MZ_MOUSE_BUTTON_5         ::Mizu::Mouse::Button5
#define MZ_MOUSE_BUTTON_6         ::Mizu::Mouse::Button6
#define MZ_MOUSE_BUTTON_7         ::Mizu::Mouse::Button7
#define MZ_MOUSE_BUTTON_LAST      ::Mizu::Mouse::ButtonLast
#define MZ_MOUSE_BUTTON_LEFT      ::Mizu::Mouse::ButtonLeft
#define MZ_MOUSE_BUTTON_RIGHT     ::Mizu::Mouse::ButtonRight
#define MZ_MOUSE_BUTTON_MIDDLE    ::Mizu::Mouse::ButtonMiddle