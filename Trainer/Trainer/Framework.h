#include "Compile.h"

class Framework
{

public:
	Framework();
	Framework(HINSTANCE hInstance);

	virtual bool Initialize();
	virtual bool InitializeWindow();
	virtual bool InitializeD3D();
	virtual bool InitializeGame();

	virtual bool InitializeVertexBuffer();
	virtual bool InitializeIndexBuffer();
	virtual bool InitializeSwapChain();
	virtual bool InitializeInputLayout();
	virtual bool InitializeConstantBuffer();
	virtual bool InitializeViewPort();
	virtual bool InitializeDepthStencil();
	virtual bool InitializeSamplerState();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void CleanD3D();

	int Run();
	void CalculateFrameStats();
	
	LRESULT MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual ~Framework();
	
protected:

	struct ObjectConstantBuffer{
		D3DXMATRIX WVP;
	};

	ObjectConstantBuffer cbPerObj; // Constant buffer structure

	ID3D11InputLayout *inputLayout;

	Timer* timer;
	std::wstring applicationTitle; 
	HWND hWindow; 
	HINSTANCE hInstance;
	DWORD windowStyle;
	LPCSTR windowClassName;
	WPARAM cWParam;
	LPARAM cLParam;


	IDXGISwapChain *swapChain;
	ID3D11Device *dev;     
	ID3D11DeviceContext *devCon;
	ID3D11RenderTargetView *backBuffer; 
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11SamplerState* samplerState;
	ID3D11Buffer *defaultConstantBuffer;

};


