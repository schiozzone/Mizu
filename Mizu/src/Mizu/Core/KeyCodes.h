#pragma once

namespace Mizu {
	typedef enum class KeyCode : uint16_t
	{
		/* Printable keys */
		Space             = 32,
		Apostrophe        = 39,  /* ' */
		Comma             = 44,  /* , */
		Minus             = 45,  /* - */
		Period            = 46,  /* . */
		Slash             = 47,  /* / */

		D0                = 48,
		D1                = 49,
		D2                = 50,
		D3                = 51,
		D4                = 52,
		D5                = 53,
		D6                = 54,
		D7                = 55,
		D8                = 56,
		D9                = 57,

		Semicolon         = 59,  /* ; */
		Equal             = 61,  /* = */

		A                 = 65,
		B                 = 66,
		C                 = 67,
		D                 = 68,
		E                 = 69,
		F                 = 70,
		G                 = 71,
		H                 = 72,
		I                 = 73,
		J                 = 74,
		K                 = 75,
		L                 = 76,
		M                 = 77,
		N                 = 78,
		O                 = 79,
		P                 = 80,
		Q                 = 81,
		R                 = 82,
		S                 = 83,
		T                 = 84,
		U                 = 85,
		V                 = 86,
		W                 = 87,
		X                 = 88,
		Y                 = 89,
		Z                 = 90,

		LeftBracket       = 91,  /* [ */
		Backslash         = 92,  /* \ */
		RightBracket      = 93,  /* ] */
		GraveAccent       = 96,  /* ` */

		World1            = 161, /* non-US #1 */
		World2            = 162, /* non-US #2 */

		/* Function keys */
		Escape            = 256,
		Enter             = 257,
		Tab               = 258,
		Backspace         = 259,
		Insert            = 260,
		Delete            = 261,
		Right             = 262,
		Left              = 263,
		Down              = 264,
		Up                = 265,
		PageUp            = 266,
		PageDown          = 267,
		Home              = 268,
		End               = 269,
		CapsLock          = 280,
		ScrollLock        = 281,
		NumLock           = 282,
		PrintScreen       = 283,
		Pasue             = 284,
		F1                = 290,
		F2                = 291,
		F3                = 292,
		F4                = 293,
		F5                = 294,
		F6                = 295,
		F7                = 296,
		F8                = 297,
		F9                = 298,
		F10               = 299,
		F11               = 300,
		F12               = 301,
		F13               = 302,
		F14               = 303,
		F15               = 304,
		F16               = 305,
		F17               = 306,
		F18               = 307,
		F19               = 308,
		F20               = 309,
		F21               = 310,
		F22               = 311,
		F23               = 312,
		F24               = 313,
		F25               = 314,

		/* Keypad */
		KP0               = 320,
		KP1               = 321,
		KP2               = 322,
		KP3               = 323,
		KP4               = 324,
		KP5               = 325,
		KP6               = 326,
		KP7               = 327,
		KP8               = 328,
		KP9               = 329,
		KPDecimal         = 330,
		KPDivide          = 331,
		KPMultiply        = 332,
		KPSubtract        = 333,
		KPAdd             = 334,
		KPEnter           = 335,
		KPEqual           = 336,

		LeftShift         = 340,
		LeftControl       = 341,
		LeftAlt           = 342,
		LeftSuper         = 343,
		RightShift        = 344,
		RightControl      = 345,
		RightAlt          = 346,
		RightSuper        = 347,
		Menu              = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys */
#define MZ_KEY_SPACE              ::Mizu::Key::Space
#define MZ_KEY_APOSTROPHE         ::Mizu::Key::Apostrophe
#define MZ_KEY_COMMA              ::Mizu::Key::Comma
#define MZ_KEY_MINUS              ::Mizu::Key::Minus
#define MZ_KEY_PERIOD             ::Mizu::Key::Period
#define MZ_KEY_SLASH              ::Mizu::Key::Slash
#define MZ_KEY_0                  ::Mizu::Key::D0
#define MZ_KEY_1                  ::Mizu::Key::D1
#define MZ_KEY_2                  ::Mizu::Key::D2
#define MZ_KEY_3                  ::Mizu::Key::D3
#define MZ_KEY_4                  ::Mizu::Key::D4
#define MZ_KEY_5                  ::Mizu::Key::D5
#define MZ_KEY_6                  ::Mizu::Key::D6
#define MZ_KEY_7                  ::Mizu::Key::D7
#define MZ_KEY_8                  ::Mizu::Key::D8
#define MZ_KEY_9                  ::Mizu::Key::D9
#define MZ_KEY_SEMICOLON          ::Mizu::Key::Semicolon
#define MZ_KEY_EQUAL              ::Mizu::Key::Equal
#define MZ_KEY_A                  ::Mizu::Key::A
#define MZ_KEY_B                  ::Mizu::Key::B
#define MZ_KEY_C                  ::Mizu::Key::C
#define MZ_KEY_D                  ::Mizu::Key::D
#define MZ_KEY_E                  ::Mizu::Key::E
#define MZ_KEY_F                  ::Mizu::Key::F
#define MZ_KEY_G                  ::Mizu::Key::G
#define MZ_KEY_H                  ::Mizu::Key::H
#define MZ_KEY_I                  ::Mizu::Key::I
#define MZ_KEY_J                  ::Mizu::Key::J
#define MZ_KEY_K                  ::Mizu::Key::K
#define MZ_KEY_L                  ::Mizu::Key::L
#define MZ_KEY_M                  ::Mizu::Key::M
#define MZ_KEY_N                  ::Mizu::Key::N
#define MZ_KEY_O                  ::Mizu::Key::O
#define MZ_KEY_P                  ::Mizu::Key::P
#define MZ_KEY_Q                  ::Mizu::Key::Q
#define MZ_KEY_R                  ::Mizu::Key::R
#define MZ_KEY_S                  ::Mizu::Key::S
#define MZ_KEY_T                  ::Mizu::Key::T
#define MZ_KEY_U                  ::Mizu::Key::U
#define MZ_KEY_V                  ::Mizu::Key::V
#define MZ_KEY_W                  ::Mizu::Key::W
#define MZ_KEY_X                  ::Mizu::Key::X
#define MZ_KEY_Y                  ::Mizu::Key::Y
#define MZ_KEY_Z                  ::Mizu::Key::Z
#define MZ_KEY_LEFT_BRACKET       ::Mizu::Key::LeftBracket
#define MZ_KEY_BACKSLASH          ::Mizu::Key::Backslash
#define MZ_KEY_RIGHT_BRACKET      ::Mizu::Key::RightBracket
#define MZ_KEY_GRAVE_ACCENT       ::Mizu::Key::GraveAccent
#define MZ_KEY_WORLD_1            ::Mizu::Key::World1
#define MZ_KEY_WORLD_2            ::Mizu::Key::World2

/* Function keys */
#define MZ_KEY_ESCAPE             ::Mizu::Key::Escape
#define MZ_KEY_ENTER              ::Mizu::Key::Enter
#define MZ_KEY_TAB                ::Mizu::Key::Tab
#define MZ_KEY_BACKSPACE          ::Mizu::Key::Backspace
#define MZ_KEY_INSERT             ::Mizu::Key::Insert
#define MZ_KEY_DELETE             ::Mizu::Key::Delete
#define MZ_KEY_RIGHT              ::Mizu::Key::Right
#define MZ_KEY_LEFT               ::Mizu::Key::Left
#define MZ_KEY_DOWN               ::Mizu::Key::Down
#define MZ_KEY_UP                 ::Mizu::Key::Up
#define MZ_KEY_PAGE_UP            ::Mizu::Key::PageUp
#define MZ_KEY_PAGE_DOWN          ::Mizu::Key::PageDown
#define MZ_KEY_HOME               ::Mizu::Key::Home
#define MZ_KEY_END                ::Mizu::Key::End
#define MZ_KEY_CAPS_LOCK          ::Mizu::Key::CapsLock
#define MZ_KEY_SCROLL_LOCK        ::Mizu::Key::ScrollLock
#define MZ_KEY_NUM_LOCK           ::Mizu::Key::NumLock
#define MZ_KEY_PRINT_SCREEN       ::Mizu::Key::PrintScreen
#define MZ_KEY_PAUSE              ::Mizu::Key::Pasue
#define MZ_KEY_F1                 ::Mizu::Key::F1
#define MZ_KEY_F2                 ::Mizu::Key::F2
#define MZ_KEY_F3                 ::Mizu::Key::F3
#define MZ_KEY_F4                 ::Mizu::Key::F4
#define MZ_KEY_F5                 ::Mizu::Key::F5
#define MZ_KEY_F6                 ::Mizu::Key::F6
#define MZ_KEY_F7                 ::Mizu::Key::F7
#define MZ_KEY_F8                 ::Mizu::Key::F8
#define MZ_KEY_F9                 ::Mizu::Key::F9
#define MZ_KEY_F10                ::Mizu::Key::F10
#define MZ_KEY_F11                ::Mizu::Key::F11
#define MZ_KEY_F12                ::Mizu::Key::F12
#define MZ_KEY_F13                ::Mizu::Key::F13
#define MZ_KEY_F14                ::Mizu::Key::F14
#define MZ_KEY_F15                ::Mizu::Key::F15
#define MZ_KEY_F16                ::Mizu::Key::F16
#define MZ_KEY_F17                ::Mizu::Key::F17
#define MZ_KEY_F18                ::Mizu::Key::F18
#define MZ_KEY_F19                ::Mizu::Key::F19
#define MZ_KEY_F20                ::Mizu::Key::F20
#define MZ_KEY_F21                ::Mizu::Key::F21
#define MZ_KEY_F22                ::Mizu::Key::F22
#define MZ_KEY_F23                ::Mizu::Key::F23
#define MZ_KEY_F24                ::Mizu::Key::F24
#define MZ_KEY_F25                ::Mizu::Key::F25
#define MZ_KEY_KP_0               ::Mizu::Key::KP0
#define MZ_KEY_KP_1               ::Mizu::Key::KP1
#define MZ_KEY_KP_2               ::Mizu::Key::KP2
#define MZ_KEY_KP_3               ::Mizu::Key::KP3
#define MZ_KEY_KP_4               ::Mizu::Key::KP4
#define MZ_KEY_KP_5               ::Mizu::Key::KP5
#define MZ_KEY_KP_6               ::Mizu::Key::KP6
#define MZ_KEY_KP_7               ::Mizu::Key::KP7
#define MZ_KEY_KP_8               ::Mizu::Key::KP8
#define MZ_KEY_KP_9               ::Mizu::Key::KP9
#define MZ_KEY_KP_DECIMAL         ::Mizu::Key::KPDecimal
#define MZ_KEY_KP_DIVIDE          ::Mizu::Key::KPDivide
#define MZ_KEY_KP_MULTIPLY        ::Mizu::Key::KPMultiply
#define MZ_KEY_KP_SUBTRACT        ::Mizu::Key::KPSubtract
#define MZ_KEY_KP_ADD             ::Mizu::Key::KPAdd
#define MZ_KEY_KP_ENTER           ::Mizu::Key::KPEnter
#define MZ_KEY_KP_EQUAL           ::Mizu::Key::KPEqual
#define MZ_KEY_LEFT_SHIFT         ::Mizu::Key::LeftShift
#define MZ_KEY_LEFT_CONTROL       ::Mizu::Key::LeftControl
#define MZ_KEY_LEFT_ALT           ::Mizu::Key::LeftAlt
#define MZ_KEY_LEFT_SUPER         ::Mizu::Key::LeftSuper
#define MZ_KEY_RIGHT_SHIFT        ::Mizu::Key::RightShift
#define MZ_KEY_RIGHT_CONTROL      ::Mizu::Key::RightControl
#define MZ_KEY_RIGHT_ALT          ::Mizu::Key::RightAlt
#define MZ_KEY_RIGHT_SUPER        ::Mizu::Key::RightSuper
#define MZ_KEY_MENU               ::Mizu::Key::Menu