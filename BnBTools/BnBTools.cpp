#include"../Share/Simple/Simple.h"

bool OnCreate(Alice &a) {
	// embed not working thanks! DX7
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Alice a(L"test", L"test", 800, 600, hInstance);
	a.SetOnCreate(OnCreate);
	a.Run();
	a.Wait();
	a.EmbedOff();
	return 0;
}
