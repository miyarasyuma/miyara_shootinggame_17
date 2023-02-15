#pragma once

class KeyManager
{
private:
	static char oldKey[256];
	static char nowKey[256];

	static int  oldMouse;
	static int  nowMouse;
 
private:
	KeyManager() = default;

public://\‘¢‘Ì‚ğì‚ç‚È‚¢‚½‚ß
	static void Update();
	static bool OnKeyClick(int key);   //‰Ÿ‚µ‚½uŠÔ
	static bool OnKeyReleased(int key);//—£‚µ‚½uŠÔ
	static bool OnKeyPressed(int key); //‰Ÿ‚³‚ê‚Ä‚¢‚éŠÔ

	static bool OnMouseClick(int key);   //‰Ÿ‚µ‚½uŠÔ
	static bool OnMouseReleased(int key);//—£‚µ‚½uŠÔ
	static bool OnMousePressed(int key); //‰Ÿ‚³‚ê‚Ä‚¢‚éŠÔ
};

