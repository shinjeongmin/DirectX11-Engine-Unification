#include <Windows.h>

// 창의 이벤트를 처리하는 함수.
// 콜백(Callback).
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 창이 닫히면 프로그램 종료.
	switch (uMsg)
	{
	case WM_DESTROY:
		// 종료 메시지 발생 시킴.
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	// 윈도우 클래스 선언.
	WNDCLASS wc;

	// 모두 0으로 초기화.
	ZeroMemory(&wc, sizeof(wc));

	// 필요한 값만 설정 (밑에서 다시 설명.)
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("GraphicsEngine");
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == false) // 설정 값을 지정할 때, 실수했을 수도 있으니까.
	{
		MessageBox(nullptr, L"클래스 등록 실패", L"오류", 0);
		exit(-1);
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 1600, 900 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 창 생성 (만들기).
	// 창이 문제 없이 생성되면 핸들 값 반환.
	HWND hwnd = CreateWindow( // 함수 파라미터를 볼 때는 Ctrl+Shift+Space 누르면 보임.
		wc.lpszClassName, // 등록한 클래스 이름으로 지정을 해줘야한다.
		TEXT("Graphic Engine Unificated"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		1280, 800,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(nullptr, L"윈도우 생성 실패", L"오류", 0);
		exit(-1);
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 그리기 (DirectX 11).
		}
	}

	return 0;
}