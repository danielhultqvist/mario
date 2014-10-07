#include "IndestructableBox.h"
#include "../helpers/GraphicsHelper.h"
#include "../helpers/Require.h"
#include "../engine/TextureStore.h"
#include "../engine/GameEngine.h"
#include "../constants/ApplicationConstants.h"

const int X_POS = 0, Y_POS = 1, W_POS = 2, H_POS = 3;
const int TEXTURE_POS = 4;

IndestructableBox::IndestructableBox(std::deque<std::string> values)
{
	Require::equal(values.size(), size_t(5));

	m_x = atoi(values.at(X_POS).c_str());
	m_y = atoi(values.at(Y_POS).c_str());
	m_w = atoi(values.at(W_POS).c_str());
	m_h = atoi(values.at(H_POS).c_str());
	m_texture_path = Mario::RESOURCE_FOLDER + "/" + Mario::IMAGES_FOLDER + "/" + values.at(TEXTURE_POS);	
}

void IndestructableBox::draw()
{
	TextureStore* store = GameEngine::getInstance().getTextureStore();
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), store->getOrLoadTexture(m_texture_path), NULL, &getBoundingBox());		
}

void IndestructableBox::draw(int offsetX, int offsetY)
{
	TextureStore* store = GameEngine::getInstance().getTextureStore();
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), store->getOrLoadTexture(m_texture_path), NULL, &getBoundingBox(offsetX, offsetY));		
}

SDL_Rect IndestructableBox::getBoundingBox()
{
	SDL_Rect bb;
	bb.x = m_x;
	bb.y = m_y;
	bb.w = m_w;
	bb.h = m_h;
	return bb;
}

SDL_Rect IndestructableBox::getBoundingBox(int offsetX, int offsetY)
{
	SDL_Rect bb;
	bb.x = m_x + offsetX;
	bb.y = m_y + offsetY;
	bb.w = m_w;
	bb.h = m_h;
	return bb;
}