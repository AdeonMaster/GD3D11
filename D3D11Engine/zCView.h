#pragma once
#include "pch.h"
#include "HookedFunctions.h"
#include "oCGame.h"

class zCView
{
public:
	/** Hooks the functions of this Class */
	static void Hook()
	{
		DWORD dwProtect;

		HookedFunctions::OriginalFunctions.original_zCViewSetMode = (zCViewSetMode)GothicMemoryLocations::zCView::SetMode;

		VirtualProtect((void *)GothicMemoryLocations::zCView::SetMode, 0x1B9, PAGE_EXECUTE_READWRITE, &dwProtect); // zCView::SetMode

		// Replace the actual mode-change in zCView::SetMode. Only do the UI-Changes.
		REPLACE_RANGE(GothicMemoryLocations::zCView::REPL_SetMode_ModechangeStart, GothicMemoryLocations::zCView::REPL_SetMode_ModechangeEnd-1, INST_NOP);
		
#if BUILD_GOTHIC_2_6_fix
		XHook(HookedFunctions::OriginalFunctions.original_zCViewPrintChars, GothicMemoryLocations::zCView::PrintChars, hooked_PrintChars);
#endif
	}

	static void SetMode(int x, int y, int bpp, HWND* window = nullptr)
	{
		hook_infunc
		HookedFunctions::OriginalFunctions.original_zCViewSetMode(x,y,bpp, window);
		hook_outfunc
	}

	static void __fastcall hooked_PrintChars(zCView* thisptr, void* unknwn, int x, int y, const zSTRING& str) {
		// Sometimes there is garbage in the string
		//if (strlen(str.ToChar()) == 0) {
		//	return;
		//}

		hook_infunc
		
		HookedFunctions::OriginalFunctions.original_zCViewPrintChars(thisptr, x, y, str);
		
		hook_outfunc
	}

	/** Prints a message to the screen */
	void PrintTimed(int posX, int posY, const zSTRING& strMessage, float time = 3000.0f, DWORD* col = nullptr)
	{
		XCALL(GothicMemoryLocations::zCView::PrintTimed);
	}
};