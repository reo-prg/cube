#pragma once
#ifdef _DEBUG

#include <Windows.h>
#include <memory>

// �f�o�b�O���b�Z�[�W�p��`
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes,"%s %d�s��",__FILE__,__LINE__);\
	MessageBox(0,ast_mes,"���ĕ\��",MB_OK);\
}

#define TRACE(fmt,...) printf(fmt, __VA_ARGS__);

class _DebugConOut
{
	// Singlton
	static _DebugConOut &GetInstance(void)
	{
		return *sInstance;
	}

public:

private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugConOut)const
		{
			delete _debugConOut;
		}
	};

	_DebugConOut();
	~_DebugConOut();

	FILE* _dfp = nullptr;

	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> sInstance;
};

#else	// _DEBUG
#define AST();
#define TRACE(fmt,...)

#endif	// _DEBUG

