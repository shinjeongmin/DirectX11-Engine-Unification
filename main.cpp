#include <Windows.h>

// â�� �̺�Ʈ�� ó���ϴ� �Լ�.
// �ݹ�(Callback).
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// â�� ������ ���α׷� ����.
	switch (uMsg)
	{
	case WM_DESTROY:
		// ���� �޽��� �߻� ��Ŵ.
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	// ������ Ŭ���� ����.
	WNDCLASS wc;

	// ��� 0���� �ʱ�ȭ.
	ZeroMemory(&wc, sizeof(wc));

	// �ʿ��� ���� ���� (�ؿ��� �ٽ� ����.)
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("GraphicsEngine");
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == false) // ���� ���� ������ ��, �Ǽ����� ���� �����ϱ�.
	{
		MessageBox(nullptr, L"Ŭ���� ��� ����", L"����", 0);
		exit(-1);
	}

	// Window viewport ���� ����
	RECT rect = { 0, 0, 1600, 900 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// â ���� (�����).
	// â�� ���� ���� �����Ǹ� �ڵ� �� ��ȯ.
	HWND hwnd = CreateWindow( // �Լ� �Ķ���͸� �� ���� Ctrl+Shift+Space ������ ����.
		wc.lpszClassName, // ����� Ŭ���� �̸����� ������ ������Ѵ�.
		TEXT("Graphic Engine Unificated"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		1280, 800,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(nullptr, L"������ ���� ����", L"����", 0);
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
			// �׸��� (DirectX 11).
		}
	}

	return 0;
}