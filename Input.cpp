#include "Input.h"



void Input::UpdateEvent(vector<optional<Event>>& eventCollection)
{
    m_keysPressed.clear();
    m_isMouseDown = false;
    m_MousePos = {-1,-1};

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

        if (sfEvent->is<Event::MouseButtonPressed>())
        {
            
            if (sfEvent->getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
            {
                m_isMouseDown = true;
                m_MousePos = sfEvent->getIf<Event::MouseButtonPressed>()->position;
            }
        }
    }
}
#ifdef DEBUG


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
    cout << "\nConsole Input Deletion... : Delete \"" << m_consoleInput << "\"\n" ;
    m_consoleInput.clear();
}

string Input::getConsoleInput()
{
    string s = m_consoleInput;
    resetConsoleInput();
    return s;
}
#endif // !DEBUG

bool Input::getAnyKeyPress()
{
    return m_keysPressed.size()!= 0;
}


bool Input::getKeyPress(Keyboard::Key k)
{
    auto it = m_keysPressed.find(k);
    return it != m_keysPressed.end();
}

bool Input::isMouseDown()
{
    return m_isMouseDown;
}

Vector2i Input::getMousePos()
{
    return m_MousePos;
}


bool Input::OnClick()
{
    return false;
}
