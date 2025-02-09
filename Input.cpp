#include "Input.h"



void Input::UpdateEvent(vector<optional<Event>>& eventCollection)
{
    m_keysPressed.clear();

    auto it = eventCollection.begin();
    auto end = eventCollection.end();
    //All the event in this frame process here
    for (auto& psfEvent = it; it != end; psfEvent++)
    {
        auto& sfEvent = (*psfEvent);

        // Get all pressing key this frame
        if (sfEvent->is<Event::KeyPressed>())
        {
            m_keysPressed.insert(sfEvent->getIf<Event::KeyPressed>()->code);
        }
    }


}
/// <summary>
/// FOR TESTING ONLY! DOES NOT WORK IN REAL GAME
/// </summary>
/// <returns></returns>
void Input::collectInputKey()
{
    if (_kbhit())
    {
        char c = _getch();
        cout << c;
        m_consoleInput += c;
    }
}

void Input::resetConsoleInput()
{
    cout << "Console Input Deltion... : Delete \"" << m_consoleInput << "\"";
    m_consoleInput.clear();
}

string Input::getConsoleInput()
{
    return m_consoleInput;
}

bool Input::getAnyKeyPress()
{
    return m_keysPressed.size()!= 0;
}


bool Input::getKeyPress(Keyboard::Key k)
{
    auto it = m_keysPressed.find(k);
    return it != m_keysPressed.end();
}


bool Input::OnClick()
{
    return false;
}

void Input::resetFlag()
{

}


string Input::Key2Str(const Keyboard::Key& k) {
    string ret;
    switch (k) {

        K2S(A)
        K2S(B)
        K2S(C)
        K2S(D)
        K2S(E)
        K2S(F)
        K2S(G)
        K2S(H)
        K2S(I)
        K2S(J)
        K2S(K)
        K2S(L)
        K2S(M)
        K2S(N)
        K2S(O)
        K2S(P)
        K2S(Q)
        K2S(R)
        K2S(S)
        K2S(T)
        K2S(U)
        K2S(V)
        K2S(W)
        K2S(X)
        K2S(Y)
        K2S(Z)

    case sf::Keyboard::Key::Num0:

        ret = "0";
        break;
    case sf::Keyboard::Key::Num1:

        ret = "1";
        break;
    case sf::Keyboard::Key::Num2:

        ret = "2";
        break;
    case sf::Keyboard::Key::Num3:

        ret = "3";
        break;
    case sf::Keyboard::Key::Num4:

        ret = "4";
        break;
    case sf::Keyboard::Key::Num5:

        ret = "5";
        break;
    case sf::Keyboard::Key::Num6:

        ret = "6";
        break;
    case sf::Keyboard::Key::Num7:

        ret = "7";
        break;
    case sf::Keyboard::Key::Num8:

        ret = "8";
        break;
    case sf::Keyboard::Key::Num9:

        ret = "9";
        break;
    case sf::Keyboard::Key::Escape:

        ret = "Escape";
        break;
    case sf::Keyboard::Key::LControl:

        ret = "LControl";
        break;
    case sf::Keyboard::Key::LShift:

        ret = "LShift";
        break;
    case sf::Keyboard::Key::LAlt:

        ret = "LAlt";
        break;
    case sf::Keyboard::Key::LSystem:

        ret = "LSystem";
        break;
    case sf::Keyboard::Key::RControl:

        ret = "RControl";
        break;
    case sf::Keyboard::Key::RShift:

        ret = "RShift";
        break;
    case sf::Keyboard::Key::RAlt:

        ret = "RAlt";
        break;
    case sf::Keyboard::Key::RSystem:

        ret = "RSystem";
        break;
    case sf::Keyboard::Key::Menu:

        ret = "Menu";
        break;
    case sf::Keyboard::Key::LBracket:

        ret = "(";
        break;
    case sf::Keyboard::Key::RBracket:

        ret = ")";
        break;
    case sf::Keyboard::Key::Comma:

        ret = ",";
        break;
    case sf::Keyboard::Key::Period:

        ret = ".";
        break;

    case sf::Keyboard::Key::Slash:

        ret = "/";
        break;
    case sf::Keyboard::Key::Space:

        ret = " ";
        break;
    case sf::Keyboard::Key::Tab:

        ret = "Tab";
        break;
    case sf::Keyboard::Key::PageUp:

        ret = "PageUp";
        break;
    case sf::Keyboard::Key::PageDown:

        ret = "PageDown";
        break;
    case sf::Keyboard::Key::End:

        ret = "End";
        break;
    case sf::Keyboard::Key::Home:

        ret = "Home";
        break;
    case sf::Keyboard::Key::Insert:

        ret = "Insert";
        break;
    case sf::Keyboard::Key::Delete:

        ret = "Delete";
        break;
    case sf::Keyboard::Key::Add:

        ret = "Add";
        break;
    case sf::Keyboard::Key::Subtract:

        ret = "Subtract";
        break;
    case sf::Keyboard::Key::Multiply:

        ret = "Multiply";
        break;
    case sf::Keyboard::Key::Divide:

        ret = "Divide";
        break;
    case sf::Keyboard::Key::Left:

        ret = "Left";
        break;
    case sf::Keyboard::Key::Right:

        ret = "Right";
        break;
    case sf::Keyboard::Key::Up:

        ret = "Up";
        break;
    case sf::Keyboard::Key::Down:

        ret = "Down";
        break;
    case sf::Keyboard::Key::Numpad0:

        ret = "0";
        break;
    case sf::Keyboard::Key::Numpad1:

        ret = "1";
        break;
    case sf::Keyboard::Key::Numpad2:

        ret = "2";
        break;
    case sf::Keyboard::Key::Numpad3:

        ret = "3";
        break;
    case sf::Keyboard::Key::Numpad4:

        ret = "4";
        break;
    case sf::Keyboard::Key::Numpad5:

        ret = "5";
        break;
    case sf::Keyboard::Key::Numpad6:

        ret = "6";
        break;
    case sf::Keyboard::Key::Numpad7:

        ret = "7";
        break;
    case sf::Keyboard::Key::Numpad8:

        ret = "8";
        break;
    case sf::Keyboard::Key::Numpad9:

        ret = "9";
        break;
    K2S(F1)
    K2S(F2)
    K2S(F3)
    K2S(F4)
    K2S(F5)
    K2S(F6)
    K2S(F7)
    K2S(F8)
    K2S(F9)
    K2S(F10)
    K2S(F11)
    K2S(F12)
    K2S(Pause)


    default:
        ret = "Unknow";
        break;
    }
    return ret;
}


