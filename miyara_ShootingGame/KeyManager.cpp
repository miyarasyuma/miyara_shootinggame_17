#include "KeyManager.h"
#include"DxLib.h"

char  KeyManager::oldKey[256];
char  KeyManager::nowKey[256];

int KeyManager::oldMouse;
int KeyManager::nowMouse;

void  KeyManager::Update() 
{
	for (int i = 0; i < 256;i++)
	{
		oldKey[i] = nowKey[i];
	}

	if (GetHitKeyStateAll(nowKey) == -1)
	{
		throw - 1;
	}

	oldMouse = nowMouse;
	nowMouse = GetMouseInput();
}

bool KeyManager::OnKeyClick(int key)  //‰Ÿ‚µ‚½uŠÔ
{
	bool ret = ((nowKey[key] == 1) && (oldKey[key] != 1));
	return ret;
}

bool KeyManager::OnKeyReleased(int key)//—£‚µ‚½uŠÔ
{
	bool ret = ((nowKey[key] == 0) && (oldKey[key] == 1));
	//bool ret = ((nowKey[key] != 1) && (oldKey[key] == 1));
	return ret;
}

bool KeyManager::OnKeyPressed(int key) //‰Ÿ‚³‚ê‚Ä‚¢‚éŠÔ
{
	int ret = (nowKey[key] == 1);
	return ret;
}

bool KeyManager::OnMouseClick(int key)  //‰Ÿ‚µ‚½uŠÔ
{
	bool ret = ((nowMouse & key) && (~oldMouse & key));
	return ret;
}

bool KeyManager::OnMouseReleased(int key)//—£‚µ‚½uŠÔ
{
	bool ret = ((~nowMouse & key) && (oldMouse & key));
	//bool ret = ((nowKey[key] != 1) && (oldKey[key] == 1));
	return ret;
}

bool KeyManager::OnMousePressed(int key) //‰Ÿ‚³‚ê‚Ä‚¢‚éŠÔ
{
	int ret = (nowMouse & key);
	return ret;
}