#pragma once

namespace RAPIER
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space					= 32,
		Apostrophe				= 39, /* ' */
		Comma					= 44, /* , */
		Minus					= 45, /* - */
		Period					= 46, /* . */
		Slash					= 47, /* / */

		D0						= 48, /* 0 */
		D1						= 49, /* 1 */
		D2						= 50, /* 2 */
		D3						= 51, /* 3 */
		D4						= 52, /* 4 */
		D5						= 53, /* 5 */
		D6						= 54, /* 6 */
		D7						= 55, /* 7 */
		D8						= 56, /* 8 */
		D9						= 57, /* 9 */

		Semicolon				= 59, /* ; */
		Equal					= 61, /* = */

		A						= 65,
		B						= 66,
		C						= 67,
		D						= 68,
		E						= 69,
		F						= 70,
		G						= 71,
		H						= 72,
		I						= 73,
		J						= 74,
		K						= 75,
		L						= 76,
		M						= 77,
		N						= 78,
		O						= 79,
		P						= 80,
		Q						= 81,
		R						= 82,
		S						= 83,
		T						= 84,
		U						= 85,
		V						= 86,
		W						= 87,
		X						= 88,
		Y						= 89,
		Z						= 90,

		LeftBracket				= 91,  /* [ */
		Backslash				= 92,  /* \ */
		RightBracket			= 93,  /* ] */
		GraveAccent				= 96,  /* ` */

		World1					= 161, /* non-US #1 */
		World2					= 162, /* non-US #2 */

		/* Function keys */
		Escape					= 256,
		Enter					= 257,
		Tab						= 258,
		Backspace				= 259,
		Insert					= 260,
		Delete					= 261,
		Right					= 262,
		Left					= 263,
		Down					= 264,
		Up						= 265,
		PageUp					= 266,
		PageDown				= 267,
		Home					= 268,
		End						= 269,
		CapsLock				= 280,
		ScrollLock				= 281,
		NumLock					= 282,
		PrintScreen				= 283,
		Pause					= 284,
		F1						= 290,
		F3						= 292,
		F4						= 293,
		F5						= 294,
		F6						= 295,
		F2						= 291,
		F7						= 296,
		F8						= 297,
		F9						= 298,
		F10						= 299,
		F11						= 300,
		F12						= 301,
		F13						= 302,
		F14						= 303,
		F15						= 304,
		F16						= 305,
		F17						= 306,
		F18						= 307,
		F19						= 308,
		F20						= 309,
		F21						= 310,
		F22						= 311,
		F23						= 312,
		F24						= 313,
		F25						= 314,

		/* Keypad */
		KP0						= 320,
		KP1						= 321,
		KP2						= 322,
		KP3						= 323,
		KP4						= 324,
		KP5						= 325,
		KP6						= 326,
		KP7						= 327,
		KP8						= 328,
		KP9						= 329,
		KPDecimal				= 330,
		KPDivide				= 331,
		KPMultiply				= 332,
		KPSubtract				= 333,
		KPAdd					= 334,
		KPEnter					= 335,
		KPEqual					= 336,

		LeftShift				= 340,
		LeftControl				= 341,
		LeftAlt					= 342,
		LeftSuper				= 343,
		RightShift				= 344,
		RightControl			= 345,
		RightAlt				= 346,
		RightSuper				= 347,
		Menu					= 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
	// From glfw3.h
	
}	//	END namespace RAPIER

// From glfw3.h
#define RP_KEY_SPACE           ::RAPIER::Key::Space
#define RP_KEY_APOSTROPHE      ::RAPIER::Key::Apostrophe    /* ' */
#define RP_KEY_COMMA           ::RAPIER::Key::Comma         /* , */
#define RP_KEY_MINUS           ::RAPIER::Key::Minus         /* - */
#define RP_KEY_PERIOD          ::RAPIER::Key::Period        /* . */
#define RP_KEY_SLASH           ::RAPIER::Key::Slash         /* / */
#define RP_KEY_0               ::RAPIER::Key::D0
#define RP_KEY_1               ::RAPIER::Key::D1
#define RP_KEY_2               ::RAPIER::Key::D2
#define RP_KEY_3               ::RAPIER::Key::D3
#define RP_KEY_4               ::RAPIER::Key::D4
#define RP_KEY_5               ::RAPIER::Key::D5
#define RP_KEY_6               ::RAPIER::Key::D6
#define RP_KEY_7               ::RAPIER::Key::D7
#define RP_KEY_8               ::RAPIER::Key::D8
#define RP_KEY_9               ::RAPIER::Key::D9
#define RP_KEY_SEMICOLON       ::RAPIER::Key::Semicolon     /* ; */
#define RP_KEY_EQUAL           ::RAPIER::Key::Equal         /* = */
#define RP_KEY_A               ::RAPIER::Key::A
#define RP_KEY_B               ::RAPIER::Key::B
#define RP_KEY_C               ::RAPIER::Key::C
#define RP_KEY_D               ::RAPIER::Key::D
#define RP_KEY_E               ::RAPIER::Key::E
#define RP_KEY_F               ::RAPIER::Key::F
#define RP_KEY_G               ::RAPIER::Key::G
#define RP_KEY_H               ::RAPIER::Key::H
#define RP_KEY_I               ::RAPIER::Key::I
#define RP_KEY_J               ::RAPIER::Key::J
#define RP_KEY_K               ::RAPIER::Key::K
#define RP_KEY_L               ::RAPIER::Key::L
#define RP_KEY_M               ::RAPIER::Key::M
#define RP_KEY_N               ::RAPIER::Key::N
#define RP_KEY_O               ::RAPIER::Key::O
#define RP_KEY_P               ::RAPIER::Key::P
#define RP_KEY_Q               ::RAPIER::Key::Q
#define RP_KEY_R               ::RAPIER::Key::R
#define RP_KEY_S               ::RAPIER::Key::S
#define RP_KEY_T               ::RAPIER::Key::T
#define RP_KEY_U               ::RAPIER::Key::U
#define RP_KEY_V               ::RAPIER::Key::V
#define RP_KEY_W               ::RAPIER::Key::W
#define RP_KEY_X               ::RAPIER::Key::X
#define RP_KEY_Y               ::RAPIER::Key::Y
#define RP_KEY_Z               ::RAPIER::Key::Z
#define RP_KEY_LEFT_BRACKET    ::RAPIER::Key::LeftBracket   /* [ */
#define RP_KEY_BACKSLASH       ::RAPIER::Key::Backslash     /* \ */
#define RP_KEY_RIGHT_BRACKET   ::RAPIER::Key::RightBracket  /* ] */
#define RP_KEY_GRAVE_ACCENT    ::RAPIER::Key::GraveAccent   /* ` */
#define RP_KEY_WORLD_1         ::RAPIER::Key::World1        /* non-US #1 */
#define RP_KEY_WORLD_2         ::RAPIER::Key::World2        /* non-US #2 */

/* Function keys */
#define RP_KEY_ESCAPE          ::RAPIER::Key::Escape
#define RP_KEY_ENTER           ::RAPIER::Key::Enter
#define RP_KEY_TAB             ::RAPIER::Key::Tab
#define RP_KEY_BACKSPACE       ::RAPIER::Key::Backspace
#define RP_KEY_INSERT          ::RAPIER::Key::Insert
#define RP_KEY_DELETE          ::RAPIER::Key::Delete
#define RP_KEY_RIGHT           ::RAPIER::Key::Right
#define RP_KEY_LEFT            ::RAPIER::Key::Left
#define RP_KEY_DOWN            ::RAPIER::Key::Down
#define RP_KEY_UP              ::RAPIER::Key::Up
#define RP_KEY_PAGE_UP         ::RAPIER::Key::PageUp
#define RP_KEY_PAGE_DOWN       ::RAPIER::Key::PageDown
#define RP_KEY_HOME            ::RAPIER::Key::Home
#define RP_KEY_END             ::RAPIER::Key::End
#define RP_KEY_CAPS_LOCK       ::RAPIER::Key::CapsLock
#define RP_KEY_SCROLL_LOCK     ::RAPIER::Key::ScrollLock
#define RP_KEY_NUM_LOCK        ::RAPIER::Key::NumLock
#define RP_KEY_PRINT_SCREEN    ::RAPIER::Key::PrintScreen
#define RP_KEY_PAUSE           ::RAPIER::Key::Pause
#define RP_KEY_F1              ::RAPIER::Key::F1
#define RP_KEY_F2              ::RAPIER::Key::F2
#define RP_KEY_F3              ::RAPIER::Key::F3
#define RP_KEY_F4              ::RAPIER::Key::F4
#define RP_KEY_F5              ::RAPIER::Key::F5
#define RP_KEY_F6              ::RAPIER::Key::F6
#define RP_KEY_F7              ::RAPIER::Key::F7
#define RP_KEY_F8              ::RAPIER::Key::F8
#define RP_KEY_F9              ::RAPIER::Key::F9
#define RP_KEY_F10             ::RAPIER::Key::F10
#define RP_KEY_F11             ::RAPIER::Key::F11
#define RP_KEY_F12             ::RAPIER::Key::F12
#define RP_KEY_F13             ::RAPIER::Key::F13
#define RP_KEY_F14             ::RAPIER::Key::F14
#define RP_KEY_F15             ::RAPIER::Key::F15
#define RP_KEY_F16             ::RAPIER::Key::F16
#define RP_KEY_F17             ::RAPIER::Key::F17
#define RP_KEY_F18             ::RAPIER::Key::F18
#define RP_KEY_F19             ::RAPIER::Key::F19
#define RP_KEY_F20             ::RAPIER::Key::F20
#define RP_KEY_F21             ::RAPIER::Key::F21
#define RP_KEY_F22             ::RAPIER::Key::F22
#define RP_KEY_F23             ::RAPIER::Key::F23
#define RP_KEY_F24             ::RAPIER::Key::F24
#define RP_KEY_F25             ::RAPIER::Key::F25

/* Keypad */
#define RP_KEY_KP_0            ::RAPIER::Key::KP0
#define RP_KEY_KP_1            ::RAPIER::Key::KP1
#define RP_KEY_KP_2            ::RAPIER::Key::KP2
#define RP_KEY_KP_3            ::RAPIER::Key::KP3
#define RP_KEY_KP_4            ::RAPIER::Key::KP4
#define RP_KEY_KP_5            ::RAPIER::Key::KP5
#define RP_KEY_KP_6            ::RAPIER::Key::KP6
#define RP_KEY_KP_7            ::RAPIER::Key::KP7
#define RP_KEY_KP_8            ::RAPIER::Key::KP8
#define RP_KEY_KP_9            ::RAPIER::Key::KP9
#define RP_KEY_KP_DECIMAL      ::RAPIER::Key::KPDecimal
#define RP_KEY_KP_DIVIDE       ::RAPIER::Key::KPDivide
#define RP_KEY_KP_MULTIPLY     ::RAPIER::Key::KPMultiply
#define RP_KEY_KP_SUBTRACT     ::RAPIER::Key::KPSubtract
#define RP_KEY_KP_ADD          ::RAPIER::Key::KPAdd
#define RP_KEY_KP_ENTER        ::RAPIER::Key::KPEnter
#define RP_KEY_KP_EQUAL        ::RAPIER::Key::KPEqual

#define RP_KEY_LEFT_SHIFT      ::RAPIER::Key::LeftShift
#define RP_KEY_LEFT_CONTROL    ::RAPIER::Key::LeftControl
#define RP_KEY_LEFT_ALT        ::RAPIER::Key::LeftAlt
#define RP_KEY_LEFT_SUPER      ::RAPIER::Key::LeftSuper
#define RP_KEY_RIGHT_SHIFT     ::RAPIER::Key::RightShift
#define RP_KEY_RIGHT_CONTROL   ::RAPIER::Key::RightControl
#define RP_KEY_RIGHT_ALT       ::RAPIER::Key::RightAlt
#define RP_KEY_RIGHT_SUPER     ::RAPIER::Key::RightSuper
#define RP_KEY_MENU            ::RAPIER::Key::Menu
