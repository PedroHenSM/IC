#include <Rocket/Core.h>
#include "SystemInterface.h"

Rocket::Core::Input::KeyIdentifier RendererSystemInterface::TranslateKey(int glfwKey)
{
    using namespace Rocket::Core::Input;


    switch(glfwKey) {
        case GLFW_KEY_UNKNOWN:
            return KI_UNKNOWN;
            break;
        case GLFW_KEY_SPACE:
            return KI_SPACE;
            break;
        case GLFW_KEY_0:
            return KI_0;
            break;
        case GLFW_KEY_1:
            return KI_1;
            break;
        case GLFW_KEY_2:
            return KI_2;
            break;
        case GLFW_KEY_3:
            return KI_3;
            break;
        case GLFW_KEY_4:
            return KI_4;
            break;
        case GLFW_KEY_5:
            return KI_5;
            break;
        case GLFW_KEY_6:
            return KI_6;
            break;
        case GLFW_KEY_7:
            return KI_7;
            break;
        case GLFW_KEY_8:
            return KI_8;
            break;
        case GLFW_KEY_9:
            return KI_9;
            break;
        case GLFW_KEY_A:
            return KI_A;
            break;
        case GLFW_KEY_B:
            return KI_B;
            break;
        case GLFW_KEY_C:
            return KI_C;
            break;
        case GLFW_KEY_D:
            return KI_D;
            break;
        case GLFW_KEY_E:
            return KI_E;
            break;
        case GLFW_KEY_F:
            return KI_F;
            break;
        case GLFW_KEY_G:
            return KI_G;
            break;
        case GLFW_KEY_H:
            return KI_H;
            break;
        case GLFW_KEY_I:
            return KI_I;
            break;
        case GLFW_KEY_J:
            return KI_J;
            break;
        case GLFW_KEY_K:
            return KI_K;
            break;
        case GLFW_KEY_L:
            return KI_L;
            break;
        case GLFW_KEY_M:
            return KI_M;
            break;
        case GLFW_KEY_N:
            return KI_N;
            break;
        case GLFW_KEY_O:
            return KI_O;
            break;
        case GLFW_KEY_P:
            return KI_P;
            break;
        case GLFW_KEY_Q:
            return KI_Q;
            break;
        case GLFW_KEY_R:
            return KI_R;
            break;
        case GLFW_KEY_S:
            return KI_S;
            break;
        case GLFW_KEY_T:
            return KI_T;
            break;
        case GLFW_KEY_U:
            return KI_U;
            break;
        case GLFW_KEY_V:
            return KI_V;
            break;
        case GLFW_KEY_W:
            return KI_W;
            break;
        case GLFW_KEY_X:
            return KI_X;
            break;
        case GLFW_KEY_Y:
            return KI_Y;
            break;
        case GLFW_KEY_Z:
            return KI_Z;
            break;
        case GLFW_KEY_SEMICOLON:
            return KI_OEM_1;
            break;
        //case SDLK_PLUS: /******/
        //    return KI_OEM_PLUS;
        //    break;
        case GLFW_KEY_COMMA:
            return KI_OEM_COMMA;
            break;
        case GLFW_KEY_MINUS:
            return KI_OEM_MINUS;
            break;
        case GLFW_KEY_PERIOD:
            return KI_OEM_PERIOD;
            break;
        case GLFW_KEY_SLASH:
            return KI_OEM_2;
            break;
        //case SDLK_BACKQUOTE: /****/
        //    return KI_OEM_3;
        //    break;
        case GLFW_KEY_LEFT_BRACKET:
            return KI_OEM_4;
            break;
        case GLFW_KEY_BACKSLASH:
            return KI_OEM_5;
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            return KI_OEM_6;
            break;
        //case SDLK_QUOTEDBL: /*****/
        //    return KI_OEM_7;
        //    break;
        case GLFW_KEY_KP_0:
            return KI_NUMPAD0;
            break;
        case GLFW_KEY_KP_1:
            return KI_NUMPAD1;
            break;
        case GLFW_KEY_KP_2:
            return KI_NUMPAD2;
            break;
        case GLFW_KEY_KP_3:
            return KI_NUMPAD3;
            break;
        case GLFW_KEY_KP_4:
            return KI_NUMPAD4;
            break;
        case GLFW_KEY_KP_5:
            return KI_NUMPAD5;
            break;
        case GLFW_KEY_KP_6:
            return KI_NUMPAD6;
            break;
        case GLFW_KEY_KP_7:
            return KI_NUMPAD7;
            break;
        case GLFW_KEY_KP_8:
            return KI_NUMPAD8;
            break;
        case GLFW_KEY_KP_9:
            return KI_NUMPAD9;
            break;
        case GLFW_KEY_KP_ENTER:
            return KI_NUMPADENTER;
            break;
        case GLFW_KEY_KP_MULTIPLY:
            return KI_MULTIPLY;
            break;
        case GLFW_KEY_KP_ADD:
            return KI_ADD;
            break;
        case GLFW_KEY_KP_SUBTRACT:
            return KI_SUBTRACT;
            break;
        case GLFW_KEY_KP_DECIMAL:
            return KI_DECIMAL;
            break;
        case GLFW_KEY_KP_DIVIDE:
            return KI_DIVIDE;
            break;
        case GLFW_KEY_KP_EQUAL:
            return KI_OEM_NEC_EQUAL;
            break;
        case GLFW_KEY_BACKSPACE:
            return KI_BACK;
            break;
        case GLFW_KEY_TAB:
            return KI_TAB;
            break;
        //case SDLK_CLEAR: /****/
        //    return KI_CLEAR;
        //    break;
        case GLFW_KEY_ENTER:
            return KI_RETURN;
            break;
        case GLFW_KEY_PAUSE:
            return KI_PAUSE;
            break;
        case GLFW_KEY_CAPS_LOCK:
            return KI_CAPITAL;
            break;
        case GLFW_KEY_PAGE_UP:
            return KI_PRIOR;
            break;
        case GLFW_KEY_PAGE_DOWN:
            return KI_NEXT;
            break;
        case GLFW_KEY_END:
            return KI_END;
            break;
        case GLFW_KEY_HOME:
            return KI_HOME;
            break;
        case GLFW_KEY_LEFT:
            return KI_LEFT;
            break;
        case GLFW_KEY_UP:
            return KI_UP;
            break;
        case GLFW_KEY_RIGHT:
            return KI_RIGHT;
            break;
        case GLFW_KEY_DOWN:
            return KI_DOWN;
            break;
        case GLFW_KEY_INSERT:
            return KI_INSERT;
            break;
        case GLFW_KEY_DELETE:
            return KI_DELETE;
            break;
        //case SDLK_HELP: /****/
        //    return KI_HELP;
        //    break;
        case GLFW_KEY_F1:
            return KI_F1;
            break;
        case GLFW_KEY_F2:
            return KI_F2;
            break;
        case GLFW_KEY_F3:
            return KI_F3;
            break;
        case GLFW_KEY_F4:
            return KI_F4;
            break;
        case GLFW_KEY_F5:
            return KI_F5;
            break;
        case GLFW_KEY_F6:
            return KI_F6;
            break;
        case GLFW_KEY_F7:
            return KI_F7;
            break;
        case GLFW_KEY_F8:
            return KI_F8;
            break;
        case GLFW_KEY_F9:
            return KI_F9;
            break;
        case GLFW_KEY_F10:
            return KI_F10;
            break;
        case GLFW_KEY_F11:
            return KI_F11;
            break;
        case GLFW_KEY_F12:
            return KI_F12;
            break;
        case GLFW_KEY_F13:
            return KI_F13;
            break;
        case GLFW_KEY_F14:
            return KI_F14;
            break;
        case GLFW_KEY_F15:
            return KI_F15;
            break;
        case GLFW_KEY_NUM_LOCK:
            return KI_NUMLOCK;
            break;
        case GLFW_KEY_SCROLL_LOCK:
            return KI_SCROLL;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            return KI_LSHIFT;
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            return KI_RSHIFT;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            return KI_LCONTROL;
            break;
        case GLFW_KEY_RIGHT_CONTROL:
            return KI_RCONTROL;
            break;
        case GLFW_KEY_LEFT_ALT:
            return KI_LMENU;
            break;
        case GLFW_KEY_RIGHT_ALT:
            return KI_RMENU;
            break;
        //case SDLK_LGUI: /*****/
        //    return KI_LMETA;
        //    break;
        //case SDLK_RGUI: /*****/
        //    return KI_RMETA;
        //    break;
        /*case SDLK_LSUPER:
            return KI_LWIN;
            break;
        case SDLK_RSUPER:
            return KI_RWIN;
            break;*/
        default:
            return KI_UNKNOWN;
            break;
    }
}

int RendererSystemInterface::TranslateMouseButton(unsigned char button)
{
    return button;
}

int RendererSystemInterface::GetKeyModifiers(int modifiers)
{
    int retval = 0;

    if(modifiers & GLFW_MOD_CONTROL)
        retval |= Rocket::Core::Input::KM_CTRL;

    if(modifiers & GLFW_MOD_SHIFT)
        retval |= Rocket::Core::Input::KM_SHIFT;

    if(modifiers & GLFW_MOD_ALT)
        retval |= Rocket::Core::Input::KM_ALT;

    return retval;
}

float RendererSystemInterface::GetElapsedTime()
{
	return glfwGetTime();
}

bool RendererSystemInterface::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
{
	std::string Type;

	switch(type)
	{
	case Rocket::Core::Log::LT_ALWAYS:
		Type = "[Always]";
		break;
	case Rocket::Core::Log::LT_ERROR:
		Type = "[Error]";
		break;
	case Rocket::Core::Log::LT_ASSERT:
		Type = "[Assert]";
		break;
	case Rocket::Core::Log::LT_WARNING:
		Type = "[Warning]";
		break;
	case Rocket::Core::Log::LT_INFO:
		Type = "[Info]";
		break;
	case Rocket::Core::Log::LT_DEBUG:
		Type = "[Debug]";
		break;
    case Rocket::Core::Log::LT_MAX:
        break;
	};

	printf("%s - %s\n", Type.c_str(), message.CString());

	return true;
};
