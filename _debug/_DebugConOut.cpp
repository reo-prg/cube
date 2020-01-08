#ifdef _DEBUG

#include <_debug/_DebugConOut.h>

std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter> _DebugConOut::sInstance(new _DebugConOut());

_DebugConOut::_DebugConOut()
{
	AllocConsole();
	freopen_s(&_dfp, "CONOUT$","w",stdout);
	freopen_s(&_dfp, "CONIN$", "r", stdin);

}


_DebugConOut::~_DebugConOut()
{
	FreeConsole();
}

#else	// _DEBUG
#define AST();

#endif	// _DEBUG