#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
	map<string, Texture> m_TextureStore;
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();

	static Texture& getTexture(string const filename);
};