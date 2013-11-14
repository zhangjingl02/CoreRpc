#ifndef INCLUDED_STDAFX_H
#define INCLUDED_STDAFX_H

#pragma once

#if defined(WIN32)

#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : "
#define __TODO__ __FILE__ "("__STR1__(__LINE__)") : TODO : "

#ifndef WINVER				
#define WINVER 0x0500			// Windows 2K and above
#endif

#ifdef USING_MFC
	#define _AFX_ALL_WARNINGS
	#include <afxwin.h>         // MFC ��������ͱ�׼���
	#include <afxext.h>         // MFC ��չ
	#include <afxdisp.h>        // MFC �Զ�����
	#ifndef _AFX_NO_OLE_SUPPORT
		#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
	#endif
	#ifndef _AFX_NO_AFXCMN_SUPPORT
		#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
	#endif // _AFX_NO_AFXCMN_SUPPORT
#elif defined(USING_ATL)
	#ifndef STRICT
	#define STRICT
	#endif
	#ifdef _DEBUG
		#include <crtdbg.h>
		#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
	#else
		#define DEBUG_NEW new
	#endif 
	#define _ATL_APARTMENT_THREADED
	#define _ATL_NO_AUTOMATIC_NAMESPACE

	#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

	#include <atlbase.h>
	#include <atlcom.h>
	#include <atlwin.h>
	#include <atltypes.h>
	#include <atlctl.h>
	#include <atlhost.h>
	#include <comutil.h>

	using namespace ATL;
#else
	// for MSVC on WIN32 platform
	#ifdef _DEBUG
		#include <crtdbg.h>
		#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
	#else
		#define DEBUG_NEW new
	#endif 
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif


#ifndef _WIN32_WINNT		
#define _WIN32_WINNT 0x0500		// Windows 2K and above
#endif						

#ifndef _WIN32_WINDOWS		
#define _WIN32_WINDOWS 0x0500	//Windows 2K and above
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h>
#include <winsock2.h>

#else
// non-win32
#	define	DEBUG_NEW	new


#endif // #if defined(_MSC_VER)

#ifdef PRECOMPILE_HEADER
	// std include

#endif

#endif
