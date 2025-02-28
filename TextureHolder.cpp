#include "TextureHolder.h"

#include <assert.h>
#include <iostream>

#include "Debug.h"

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::getTexture(string const filename)
{
	auto& m = m_s_Instance->m_TextureStore;
	auto kvp = m.find(filename);
	if (kvp != m.end())
	{
		//found
		return kvp->second;
	}
	else
	{
		//not found
		//Create new kvp
		auto& texture = m[filename];
		if (texture.loadFromFile(filename))
			return texture;
#ifdef DEBUG_MODE
		cout << "TextureHolder::getTexture fail to load texture from path\n"
			<< filename << endl;
#endif // DEBUG_MODE


	}
}