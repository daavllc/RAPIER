/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file contains DAGGer KeyCode defines
////////////////////////////////
#pragma once

namespace DAGGer
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
	
}	//	END namespace DAGGer

// From glfw3.h
#define Dr_KEY_SPACE           ::DAGGer::Key::Space
#define Dr_KEY_APOSTROPHE      ::DAGGer::Key::Apostrophe    /* ' */
#define Dr_KEY_COMMA           ::DAGGer::Key::Comma         /* , */
#define Dr_KEY_MINUS           ::DAGGer::Key::Minus         /* - */
#define Dr_KEY_PERIOD          ::DAGGer::Key::Period        /* . */
#define Dr_KEY_SLASH           ::DAGGer::Key::Slash         /* / */
#define Dr_KEY_0               ::DAGGer::Key::D0
#define Dr_KEY_1               ::DAGGer::Key::D1
#define Dr_KEY_2               ::DAGGer::Key::D2
#define Dr_KEY_3               ::DAGGer::Key::D3
#define Dr_KEY_4               ::DAGGer::Key::D4
#define Dr_KEY_5               ::DAGGer::Key::D5
#define Dr_KEY_6               ::DAGGer::Key::D6
#define Dr_KEY_7               ::DAGGer::Key::D7
#define Dr_KEY_8               ::DAGGer::Key::D8
#define Dr_KEY_9               ::DAGGer::Key::D9
#define Dr_KEY_SEMICOLON       ::DAGGer::Key::Semicolon     /* ; */
#define Dr_KEY_EQUAL           ::DAGGer::Key::Equal         /* = */
#define Dr_KEY_A               ::DAGGer::Key::A
#define Dr_KEY_B               ::DAGGer::Key::B
#define Dr_KEY_C               ::DAGGer::Key::C
#define Dr_KEY_D               ::DAGGer::Key::D
#define Dr_KEY_E               ::DAGGer::Key::E
#define Dr_KEY_F               ::DAGGer::Key::F
#define Dr_KEY_G               ::DAGGer::Key::G
#define Dr_KEY_H               ::DAGGer::Key::H
#define Dr_KEY_I               ::DAGGer::Key::I
#define Dr_KEY_J               ::DAGGer::Key::J
#define Dr_KEY_K               ::DAGGer::Key::K
#define Dr_KEY_L               ::DAGGer::Key::L
#define Dr_KEY_M               ::DAGGer::Key::M
#define Dr_KEY_N               ::DAGGer::Key::N
#define Dr_KEY_O               ::DAGGer::Key::O
#define Dr_KEY_P               ::DAGGer::Key::P
#define Dr_KEY_Q               ::DAGGer::Key::Q
#define Dr_KEY_R               ::DAGGer::Key::R
#define Dr_KEY_S               ::DAGGer::Key::S
#define Dr_KEY_T               ::DAGGer::Key::T
#define Dr_KEY_U               ::DAGGer::Key::U
#define Dr_KEY_V               ::DAGGer::Key::V
#define Dr_KEY_W               ::DAGGer::Key::W
#define Dr_KEY_X               ::DAGGer::Key::X
#define Dr_KEY_Y               ::DAGGer::Key::Y
#define Dr_KEY_Z               ::DAGGer::Key::Z
#define Dr_KEY_LEFT_BRACKET    ::DAGGer::Key::LeftBracket   /* [ */
#define Dr_KEY_BACKSLASH       ::DAGGer::Key::Backslash     /* \ */
#define Dr_KEY_RIGHT_BRACKET   ::DAGGer::Key::RightBracket  /* ] */
#define Dr_KEY_GRAVE_ACCENT    ::DAGGer::Key::GraveAccent   /* ` */
#define Dr_KEY_WORLD_1         ::DAGGer::Key::World1        /* non-US #1 */
#define Dr_KEY_WORLD_2         ::DAGGer::Key::World2        /* non-US #2 */

/* Function keys */
#define Dr_KEY_ESCAPE          ::DAGGer::Key::Escape
#define Dr_KEY_ENTER           ::DAGGer::Key::Enter
#define Dr_KEY_TAB             ::DAGGer::Key::Tab
#define Dr_KEY_BACKSPACE       ::DAGGer::Key::Backspace
#define Dr_KEY_INSERT          ::DAGGer::Key::Insert
#define Dr_KEY_DELETE          ::DAGGer::Key::Delete
#define Dr_KEY_RIGHT           ::DAGGer::Key::Right
#define Dr_KEY_LEFT            ::DAGGer::Key::Left
#define Dr_KEY_DOWN            ::DAGGer::Key::Down
#define Dr_KEY_UP              ::DAGGer::Key::Up
#define Dr_KEY_PAGE_UP         ::DAGGer::Key::PageUp
#define Dr_KEY_PAGE_DOWN       ::DAGGer::Key::PageDown
#define Dr_KEY_HOME            ::DAGGer::Key::Home
#define Dr_KEY_END             ::DAGGer::Key::End
#define Dr_KEY_CAPS_LOCK       ::DAGGer::Key::CapsLock
#define Dr_KEY_SCROLL_LOCK     ::DAGGer::Key::ScrollLock
#define Dr_KEY_NUM_LOCK        ::DAGGer::Key::NumLock
#define Dr_KEY_PRINT_SCREEN    ::DAGGer::Key::PrintScreen
#define Dr_KEY_PAUSE           ::DAGGer::Key::Pause
#define Dr_KEY_F1              ::DAGGer::Key::F1
#define Dr_KEY_F2              ::DAGGer::Key::F2
#define Dr_KEY_F3              ::DAGGer::Key::F3
#define Dr_KEY_F4              ::DAGGer::Key::F4
#define Dr_KEY_F5              ::DAGGer::Key::F5
#define Dr_KEY_F6              ::DAGGer::Key::F6
#define Dr_KEY_F7              ::DAGGer::Key::F7
#define Dr_KEY_F8              ::DAGGer::Key::F8
#define Dr_KEY_F9              ::DAGGer::Key::F9
#define Dr_KEY_F10             ::DAGGer::Key::F10
#define Dr_KEY_F11             ::DAGGer::Key::F11
#define Dr_KEY_F12             ::DAGGer::Key::F12
#define Dr_KEY_F13             ::DAGGer::Key::F13
#define Dr_KEY_F14             ::DAGGer::Key::F14
#define Dr_KEY_F15             ::DAGGer::Key::F15
#define Dr_KEY_F16             ::DAGGer::Key::F16
#define Dr_KEY_F17             ::DAGGer::Key::F17
#define Dr_KEY_F18             ::DAGGer::Key::F18
#define Dr_KEY_F19             ::DAGGer::Key::F19
#define Dr_KEY_F20             ::DAGGer::Key::F20
#define Dr_KEY_F21             ::DAGGer::Key::F21
#define Dr_KEY_F22             ::DAGGer::Key::F22
#define Dr_KEY_F23             ::DAGGer::Key::F23
#define Dr_KEY_F24             ::DAGGer::Key::F24
#define Dr_KEY_F25             ::DAGGer::Key::F25

/* Keypad */
#define Dr_KEY_KP_0            ::DAGGer::Key::KP0
#define Dr_KEY_KP_1            ::DAGGer::Key::KP1
#define Dr_KEY_KP_2            ::DAGGer::Key::KP2
#define Dr_KEY_KP_3            ::DAGGer::Key::KP3
#define Dr_KEY_KP_4            ::DAGGer::Key::KP4
#define Dr_KEY_KP_5            ::DAGGer::Key::KP5
#define Dr_KEY_KP_6            ::DAGGer::Key::KP6
#define Dr_KEY_KP_7            ::DAGGer::Key::KP7
#define Dr_KEY_KP_8            ::DAGGer::Key::KP8
#define Dr_KEY_KP_9            ::DAGGer::Key::KP9
#define Dr_KEY_KP_DECIMAL      ::DAGGer::Key::KPDecimal
#define Dr_KEY_KP_DIVIDE       ::DAGGer::Key::KPDivide
#define Dr_KEY_KP_MULTIPLY     ::DAGGer::Key::KPMultiply
#define Dr_KEY_KP_SUBTRACT     ::DAGGer::Key::KPSubtract
#define Dr_KEY_KP_ADD          ::DAGGer::Key::KPAdd
#define Dr_KEY_KP_ENTER        ::DAGGer::Key::KPEnter
#define Dr_KEY_KP_EQUAL        ::DAGGer::Key::KPEqual

#define Dr_KEY_LEFT_SHIFT      ::DAGGer::Key::LeftShift
#define Dr_KEY_LEFT_CONTROL    ::DAGGer::Key::LeftControl
#define Dr_KEY_LEFT_ALT        ::DAGGer::Key::LeftAlt
#define Dr_KEY_LEFT_SUPER      ::DAGGer::Key::LeftSuper
#define Dr_KEY_RIGHT_SHIFT     ::DAGGer::Key::RightShift
#define Dr_KEY_RIGHT_CONTROL   ::DAGGer::Key::RightControl
#define Dr_KEY_RIGHT_ALT       ::DAGGer::Key::RightAlt
#define Dr_KEY_RIGHT_SUPER     ::DAGGer::Key::RightSuper
#define Dr_KEY_MENU            ::DAGGer::Key::Menu
