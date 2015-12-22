#include "sprite.h"
//#include "trace.h"

#include <d3dx9.h>

CSprite::CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		//trace(L"[ERROR] Failed to get information from image file '%s'", FilePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), // 176, 224, 248
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		//trace(L"[ERROR] Failed to create texture from file '%s'", FilePath);
		return;
	}
}


void CSprite::Render(int fisrSpriteX, int firstSpriteY, int distanceBetweenSprites, int X, int Y, int vpx, int vpy)
{
	RECT srect;

	srect.left = fisrSpriteX + (_Index % _SpritePerRow) * (_Width + distanceBetweenSprites);
	srect.top = firstSpriteY + (_Index / _SpritePerRow) * (_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height + 1;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 2, 2, 1);
	_SpriteHandler->SetTransform(&mt1);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);

}

void CSprite::Render(int X, int Y, int vpx, int vpy)
{
	RECT srect;

	srect.left = (_Index % _SpritePerRow) * (_Width);
	srect.top = (_Index / _SpritePerRow) * (_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height + 1;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 2, 2, 1);
	_SpriteHandler->SetTransform(&mt1);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);

}

void CSprite::Render(Animation *anim, int X, int Y, int vpx, int vpy)
{
	RECT srect;
	if (anim->startFrame > 1)
		srect.left = ((anim->startFrame % _SpritePerRow) * _Width) + (anim->index % (anim->startFrame)) * (_Width);
	//original value =((anim->startFrame % _SpritePerRow) * _Width + 1) + (anim->index % (anim->startFrame)) * (_Width);
	else if (anim->startFrame <= 1)
		srect.left = anim->index * _Width;
	srect.top = (anim->index / _SpritePerRow) * (_Height);//original value srect.top = (anim->index / _SpritePerRow) * (_Height)
	srect.right = srect.left + _Width;//original value srect.right = srect.left + _Width-1
	srect.bottom = srect.top + _Height;//original value srect.bottom = srect.top + _Height + 1;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	/*D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 1.5, 1.5, 1);
	_SpriteHandler->SetTransform(&mt1);*/

	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);

}

void CSprite::Next()
{
	_Index = (_Index + _Count - 1) % _Count;
}

void CSprite::NextLeft()
{
	_Index = (_Index + _Count + 1) % _Count;
}

void CSprite::Reset()
{
	_Index = 0;
}

void CSprite::ResetLeft()
{
	_Index = _Count - 1;
}

CSprite::~CSprite()
{
	_Image->Release();
}

void CSprite::SetIndex(int index)
{
	_Index = index;
}