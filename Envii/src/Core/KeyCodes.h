#pragma once

namespace Envii
{
	using KeyCode = uint16_t;
	enum : KeyCode
	{
		 EV_KEY_SPACE              = 32,
		 EV_KEY_APOSTROPHE         = 39,  /* ' */
		 EV_KEY_COMMA              = 44,  /* , */
		 EV_KEY_MINUS              = 45,  /* - */
		 EV_KEY_PERIOD             = 46,  /* . */
		 EV_KEY_SLASH              = 47,  /* / */
		 EV_KEY_0                  = 48,
		 EV_KEY_1                  = 49,
		 EV_KEY_2                  = 50,
		 EV_KEY_3                  = 51,
		 EV_KEY_4                  = 52,
		 EV_KEY_5                  = 53,
		 EV_KEY_6                  = 54,
		 EV_KEY_7                  = 55,
		 EV_KEY_8                  = 56,
		 EV_KEY_9                  = 57,
		 EV_KEY_SEMICOLON          = 59,  /* ; */
		 EV_KEY_EQUAL              = 61,  /* = */
		 EV_KEY_A                  = 65,
		 EV_KEY_B                  = 66,
		 EV_KEY_C                  = 67,
		 EV_KEY_D                  = 68,
		 EV_KEY_E                  = 69,
		 EV_KEY_F                  = 70,
		 EV_KEY_G                  = 71,
		 EV_KEY_H                  = 72,
		 EV_KEY_I                  = 73,
		 EV_KEY_J                  = 74,
		 EV_KEY_K                  = 75,
		 EV_KEY_L                  = 76,
		 EV_KEY_M                  = 77,
		 EV_KEY_N                  = 78,
		 EV_KEY_O                  = 79,
		 EV_KEY_P                  = 80,
		 EV_KEY_Q                  = 81,
		 EV_KEY_R                  = 82,
		 EV_KEY_S                  = 83,
		 EV_KEY_T                  = 84,
		 EV_KEY_U                  = 85,
		 EV_KEY_V                  = 86,
		 EV_KEY_W                  = 87,
		 EV_KEY_X                  = 88,
		 EV_KEY_Y                  = 89,
		 EV_KEY_Z                  = 90,
		 EV_KEY_LEFT_BRACKET       = 91,  /* [ */
		 EV_KEY_BACKSLASH          = 92,  /* \ */
		 EV_KEY_RIGHT_BRACKET      = 93,  /* ] */
		 EV_KEY_GRAVE_ACCENT       = 96,  /* ` */
		 EV_KEY_WORLD_1            = 161, /* non-US #1 */
		 EV_KEY_WORLD_2            = 162, /* non-US #2 */
 
		/* Function keys */
		 EV_KEY_ESCAPE             = 256,
		 EV_KEY_ENTER              = 257,
		 EV_KEY_TAB                = 258,
		 EV_KEY_BACKSPACE          = 259,
		 EV_KEY_INSERT             = 260,
		 EV_KEY_DELETE             = 261,
		 EV_KEY_RIGHT              = 262,
		 EV_KEY_LEFT               = 263,
		 EV_KEY_DOWN               = 264,
		 EV_KEY_UP                 = 265,
		 EV_KEY_PAGE_UP            = 266,
		 EV_KEY_PAGE_DOWN          = 267,
		 EV_KEY_HOME               = 268,
		 EV_KEY_END                = 269,
		 EV_KEY_CAPS_LOCK          = 280,
		 EV_KEY_SCROLL_LOCK        = 281,
		 EV_KEY_NUM_LOCK           = 282,
		 EV_KEY_PRINT_SCREEN       = 283,
		 EV_KEY_PAUSE              = 284,
		 EV_KEY_F1                 = 290,
		 EV_KEY_F2                 = 291,
		 EV_KEY_F3                 = 292,
		 EV_KEY_F4                 = 293,
		 EV_KEY_F5                 = 294,
		 EV_KEY_F6                 = 295,
		 EV_KEY_F7                 = 296,
		 EV_KEY_F8                 = 297,
		 EV_KEY_F9                 = 298,
		 EV_KEY_F10                = 299,
		 EV_KEY_F11                = 300,
		 EV_KEY_F12                = 301,
		 EV_KEY_F13                = 302,
		 EV_KEY_F14                = 303,
		 EV_KEY_F15                = 304,
		 EV_KEY_F16                = 305,
		 EV_KEY_F17                = 306,
		 EV_KEY_F18                = 307,
		 EV_KEY_F19                = 308,
		 EV_KEY_F20                = 309,
		 EV_KEY_F21                = 310,
		 EV_KEY_F22                = 311,
		 EV_KEY_F23                = 312,
		 EV_KEY_F24                = 313,
		 EV_KEY_F25                = 314,
		 EV_KEY_KP_0               = 320,
		 EV_KEY_KP_1               = 321,
		 EV_KEY_KP_2               = 322,
		 EV_KEY_KP_3               = 323,
		 EV_KEY_KP_4               = 324,
		 EV_KEY_KP_5               = 325,
		 EV_KEY_KP_6               = 326,
		 EV_KEY_KP_7               = 327,
		 EV_KEY_KP_8               = 328,
		 EV_KEY_KP_9               = 329,
		 EV_KEY_KP_DECIMAL         = 330,
		 EV_KEY_KP_DIVIDE          = 331,
		 EV_KEY_KP_MULTIPLY        = 332,
		 EV_KEY_KP_SUBTRACT        = 333,
		 EV_KEY_KP_ADD             = 334,
		 EV_KEY_KP_ENTER           = 335,
		 EV_KEY_KP_EQUAL           = 336,
		 EV_KEY_LEFT_SHIFT         = 340,
		 EV_KEY_LEFT_CONTROL       = 341,
		 EV_KEY_LEFT_ALT           = 342,
		 EV_KEY_LEFT_SUPER         = 343,
		 EV_KEY_RIGHT_SHIFT        = 344,
		 EV_KEY_RIGHT_CONTROL      = 345,
		 EV_KEY_RIGHT_ALT          = 346,
		 EV_KEY_RIGHT_SUPER        = 347,
		 EV_KEY_MENU               = 348
	};
	/* From glfw3.h */

}