/***************************************************************************/
/***************************************************************************/
/*                        DISCLAIMER OF WARRANTIES.                        */
/***************************************************************************/
/***************************************************************************/
/*                                                                         */
/*  Copyright (C) 1995 IBM Corporation                                     */
/*                                                                         */
/*      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        */
/*      sample code created by IBM Corporation. This sample code is not    */
/*      part of any standard or IBM product and is provided to you solely  */
/*      for  the purpose of assisting you in the development of your       */
/*      applications.  The code is provided "AS IS", without               */
/*      warranty of any kind.  IBM shall not be liable for any damages     */
/*      arising out of your use of the sample code, even if they have been */
/*      advised of the possibility of such damages.                        */
/***************************************************************************/
#pragma alloc_text ( CODESTARTKEEP, UCMenuDrgDrpMsg               )
#pragma alloc_text ( CODESTARTKEEP, MyMalloc                      )
#pragma alloc_text ( CODESTARTKEEP, MenuWndProc                   )
#pragma alloc_text ( CODESTARTKEEP, UCMenuWndProc                 )
#pragma alloc_text ( CODESTARTKEEP, BubbleWndProc                 )
#pragma alloc_text ( CODESTARTKEEP, UCMenuCalcUnscaledItemSize    )
#pragma alloc_text ( CODESTARTKEEP, UCMenuCalcItemSize            )
#pragma alloc_text ( CODESTARTKEEP, UCMenuCalcTextSize            )
#pragma alloc_text ( CODESTARTKEEP, SubmenuWndProc                )
#pragma alloc_text ( CODESTARTKEEP, CreateUCMenu                  )
#pragma alloc_text ( CODESTARTKEEP, UCMenuCalcBmpPos              )
#pragma alloc_text ( CODESTARTKEEP, MyFree                        )
#pragma alloc_text ( CODESTARTKEEP, UCMenu3DFrame                 )
#pragma alloc_text ( CODESTARTKEEP, HideWndProc                   )
#pragma alloc_text ( CODESTARTKEEP, GetMaxItemSize                )
#pragma alloc_text ( CODESTARTKEEP, UCMenuCheckScrolling          )
#pragma alloc_text ( CODESTARTKEEP, UCMenuSetBmpBgColor           )
// (MAM) Added to KEEP code seg:
#pragma alloc_text ( CODESTARTKEEP, UCAdjacentItemBlank           )

#pragma alloc_text ( CODESTARTDROP, UCMenuGetBitmapFullName       )
#pragma alloc_text ( CODESTARTDROP, UCMenuLoadBitmap              )
#pragma alloc_text ( CODESTARTDROP, UCMenuLoadMenuData            )
#pragma alloc_text ( CODESTARTDROP, UCMenuLoadItemBmp             )
#pragma alloc_text ( CODESTARTDROP, UCMenuGetBitmapPath           )
#pragma alloc_text ( CODESTARTDROP, UCMenuSelectColor             )
#pragma alloc_text ( CODESTARTDROP, UCMenuCreateFromTemplate      )
#pragma alloc_text ( CODESTARTDROP, UCMenuCreate                  )

//----------------------------------------------------------------------------
//
// UCMENUS.C
//
// User-Customizable Menus utility
//-------------------------------------+--------------------------------------
//                                     |   Advanced Commercial Applications
// Version: 2.01                       |   IBM T.J. Watson Research Center
//                                     |   P.O. Box 218
//                                     |   Yorktown Heights, NY 10598
//-------------------------------------+--------------------------------------
// History:
// --------
//
// created: Feb 10 1993 by Alex BERTRAND
//
// updates: Jun 20 1993 (AB) : Save/Load Menu Template functions
//          Jul 10 1993 (AB) : Pop-up menus (Settings)
//          Aug 04 1993 (AB) : Drag and Drop support
//          Oct 04 1993 (GLS): UCS_ styles
//          Feb 01 1994 (GLS): More Drag and Drop support
//          ===> Build Version 2.01
//          Mar 07 1995 (MAM): Fixed drag/drop of MIS_SPACER items
//          Mar 07 1995 (MAM): Added new bitmap for dragging of spacers (diff from no-bmp items)
//          Mar 07 1995 (MAM): Don't draw edges of adjacent spacer items
//          Mar 15 1995 (MAM): Delete bitmap loaded for drag/drop (plug possible memory leak)
//          Mar 15 1995 (MAM): Fix truncated text on customization dialog
//          Mar 15 1995 (MAM): Added OK/Cancel buttons to customzation dlg, remove confirm box
//          Mar 15 1995 (MAM): Clarified some messages (NLS_xxxx in ucmenus.rc)
//          Mar 21 1995 (MAM): Fixed some missing notify messages when items drag/dropped
//                               -- e.g. only UCN_ADDEDITEM was generated, no UCN_DELETEDITEM
//          Mar 23 1995 (MAM): Fixed many problems with submenus:
//                               -- was unable to drag/drop reoder items in a submenu
//                               -- drag from a submenu left some junk pixels when menu dismissed
//                               -- drag from a submenu did not delete source item (e.g. copied)
//                               -- context menu left dark grey line on main menu
//                               -- missing many UCN_* notify messages when submenus customized
//                               -- mouse-move notify messages gave incorrect item IDs
//                               -- style changes did not change already-opened submenus.  changing
//                                  text of a submenu item did not resize the submenu (autoresize style)
//                               -- SUBMENU placeholders cannot be MIA_NODISMISS, each individual item of
//                                  the submenu to be non-dismissable must have MIA_NODISMISS attribute.
//                                  (This is different than std PM menus, but necessary to prevent
//                                  dismiss of submenus during drag/drop operations).
//          Mar 23 1995 (MAM): UCMenuIdFromCoord() off by one pixel on right/top edges
//          Mar 23 1995 (MAM): Made checkmark (thick brdr) visible on hilited items (3-pel thick bdr)
//          Mar 24 1995 (MAM): Remove ability to use MIS_BREAK on submenus
//                               -- PM bug gives wrong coordinates on MM_QUERYITEMRECT for submenus w/BREAK
//          Mar 24 1995 (MAM): Updated version to "2.02" (ucmenus.h)
//         ----------------------------- Version 2.02 Build (DevCon CD, Volumne 7) ----------------------------------------
//          Mar 27 1995 (MAM): Dismiss submenu before sending WM_CONTROL msg to owner (non-NODISMISS items).
//          Mar 29 1995 (MAM): Dismiss submenu before deleting parent menu item.
//          Mar 29 1995 (MAM): Dismiss submenu before processing WM_DESTROY.
//          Mar 29 1995 (MAM): Remove MIA_NODISMISS attribute when copy/moving parent item of a submenu
//         ----------------------------- Version 2.03 Build (Compuserve) ----------------------------------------
//          Apr 04 1995 (MAM): Improved UCN_MOUSEMOVE control messages:
//                               - Only get message when ID changes instead of every movement
//                               - Always get final msg with ID=0 when mouse leaves menu window
//          Apr 05 1995 (MAM): Replace (HWND)0 with NULLHANDLE for better portability.
//          Apr 05 1995 (MAM): Fix prototype of UCMenuGetVersion() and include <stddef.h>  (Thanks Bill K.)
//          Apr 10 1995 (MAM): Use WinDrawText() to measure space needed for text strings.  GpiQueryTextBox() not always accurate.
//          Apr 12 1995 (MAM): Add support for bubble-help
//                               - UCS_BUBBLEHELP style flag
//                               - UCN_QRYBUBBLEHELP WM_CONTROL message to application
//                                   update passed structure w/string (freed by UCmenus when done --
//                                   app must allocate string with UCMenuAlloc()).
//                               - UCMENU_SETBUBBLETIMERS:
//                                    mp1 = (LONG) new delay in msec, maximum of 65000 (65 seconds)
//                                    mp2 = (LONG) new read-time in msec
//                                    returns 0 (reserved)
//                               App must supply initial delay in UCMINFO data
//          ---NOTE--- Need to recompile apps to get larger UCMINFO structure size
//          Apr 13 1995 (MAM): Remove code to un-hilight current item when context menu invoked
//                               (did not work, no longer needed anyway)
//          Apr 13 1995 (MAM): Add support for application-supplied context menu:
//                               - UCN_QRYCONTEXTHWND message
//                                   mp1 = (UCMenu ID, UCN_QRYCONTEXTHWND)
//                                   mp2 = ptr to MENUITEM structure (usID zero if not over an item)
//                                   return HWND of application popup menu, or NULL if none
//                               - Owner of UCMenu control will get UCN_CMITEM ctrl messages (just like built-in menu)
//          Apr 21 1995 (MAM): Fix: always register UCMenu window class in case DLL is freed
//                             and reloaded by the same process (otherwise class points to window
//                             proc in old freed DLL instance).
//          Apr 21 1995 (MAM): Added UCMINRES.RES to build process to create minimal-resource .RES
//                             file.  For use by apps that don't use the UCMenus built-in context
//                             menu or customization dialogs.
//          Apr 24 1995 (MAM): Fix possible trap in UCMenuSetBmpBgColor() due to uninitialized ptr
//          Apr 24 1995 (MAM): Changed all "(TYPE)0" null pointers to "NULL" or "NULLHANDLE" as appropriate
//          Apr 24 1995 (MAM): Added UCMenuStrdup() to API set (useful during UCN_QRYBUBBLEHELP).
//          Apr 24 1995 (MAM): Changed internal use of UCMenuFree() to MyFree() -- eliminate func call in non-debug mode
//          Apr 25 1995 (MAM): Code cleanup, removed lots of unused vars, etc.
//          Apr 26 1995 (MAM): Don't process MM_DELETEITEM for submenu item in main menu proc.
//          Apr 27 1995 (MAM): Added UCMENU_ACTIVECHG message -- reqd for apps using UCN_BUBBLEHELP style
//                                mp1 = (SHORT1) TRUE -- app is being activated
//                                               FALSE-- app is being deactivated
//                                      (SHORT2) Reserved
//                                mp2 = Reserved
//          Apr 27 1995 (MAM): Dismiss open submenus when app becomes inactive
//          May 01 1995 (MAM): Fixed drawing of overall menu frame when !UCN_FRAMED
//          May 01 1995 (MAM): Chg meaning of UCS_FORCESIZE (just sets size of bitmap, item still sizes to larger of bitmap or text)
//                                (e.g. text is NEVER clipped).  Also FORCESIZE can now scale
//                                the bitmap up or down in size (instead of just down).
//          May 02 1995 (MAM): Added UCMENU_QUERYRECT message to get position of a menu item in UCMenu window
//          May 02 1995 (MAM): Added UCMENU_DISABLEUPDATE to improve performance when app inserts/deletes lots of items
//                                mp1 = (BOOL)  TRUE -- do not update menu
//                                              FALSE-- update when needed
//                                mp2 = reserved
//                             Application should always send UCMENUS_UPDATE after re-enabling update.
//                             Initial state is disabled=FALSE (e.g. update on every insert/delete, etc).
//          May 08 1995 (MAM): Chngd UCMENU_QUERYSIZE to return real size for CMS_MATRIX style (instead of size based in num of row/cols requested)
//          May 09 1995 (MAM): Added UCMenuItemDup() and UCMenuItemFree() functions to copy/free UCMITEM structures
//          May 10 1995 (MAM): Added UCN_CHANGEDITEM msg when MM_SETITEM or MM_SETITEMHANDLE is received (notify of change to item, extent of change is unknown)
//          May 15 1995 (MAM): Fixed memory leak by freeing pszParameters when item is deleted (MM_DELETEITEM processing)
//          May 24 1995 (MAM): Use UCMString2Int() to better distinguish btw bitmap resource numbers and file names (previous code would take "123G.BMP" as resource ID 123).
//          May 24 1995 (MAM): Store binary form of bitmap ID in upper word of ulFlags in UCMITEM structure
//          May 24 1995 (MAM): UCMI_FROMBMPFILE in ulFlags is set if pszBmp[] is a filename (even if the file was not found and a default resource bitmap is being used instead)
//          May 24 1995 (MAM): pszDefaultBitmap in UCMINFO can now be a resource ID (string form) or a file name
//          May 25 1995 (MAM): Fix bug in algorithm for choosing best bitmap when .BMP file contains array of bitmaps
//         June 03 1995 (MAM): Fix test of uninitialized variable in UCMenuNew().
//         June 06 1995 (MAM): Enhanced UCMenuLoadBitmap() to load icons from non-BMP files using WinLoadFileIcon.  Makes it easy to show WPS representation of any file.
//                               -- Commented out because of black-background problem (requires more code to solve).
//         June 06 1995 (MAM): If toolbar is empty set size to size of a normal PM menu.
//         June 13 1995 (MAM): Changed UCMENUS.RCH to UCMLOCAL.H (some build systems need .H extension for all header files)
//         June 13 1995 (MAM): Fixed trap/hang if application had its own drag/drop implementation in addition to the UCMenu control
//                               (dragging over the UCMenu from a same-process, non-UCMenu window would trap/hang due to bad assumption in DM_DRAGOVER processing)
//         July 20 1995 (MAM): Changed background color mapping of bitmaps:
//                              - Added new style "UCS_CHNGBMPBG_AUTO" to use lower-leftmost pixel of bitmap to determine bitmap background color (BgBmp of UCMINFO will be ignored)
//                              - Improved UCMenuSetBmpBgColor() to not assume 256 color bitmaps (less memory allocated and better performance for 2 or 16-color bitmaps)
//                              - Bitmap backgrounds are now mapped (only) when bitmaps are loaded (not at WM_DRAWITEM time)
//                              - All bitmaps are reloaded (and color mapped) when the menu background color is changed (fixes bug where multiple color changes would lose colors in the bitmaps)
//                              - Removed lCurBmpBgColor from UCMITEM structure (no longer needed since colors are mapped only when bitmaps are loaded)
//         July 20 1995 (MAM): Removed use of BitBlt to shift image of items during hilight/unhilight (BltBit method leaves stray pixels in many cases when item is partially obscured by another window).
//                              Now just fully draw the item every time.  Less efficient but more robust.
//         July 21 1995 (MAM): Fixed spurious display of bubble help when pointer passes through toolbar (check for ptr in toolbar window during WM_TIMER (TIMER_BUBBLE) processing)
//         July 21 1995 (MAM): Reduced timer for detecting ptr leaving toolbar to 1/2 second
//         July 21 1995 (MAM): Fixed visual corruption when bubble is removed if underlaying window changed (remove WS_SAVEBITS style)
//         July 21 1995 (MAM): Fixed visual corruption when bubble is quickly hidden/shown (get/dispatch all WM_PAINT messages between HIDE/SHOW so underlaying windows are sure to paint)
//         July 21 1995 (MAM): Added several HWNDs to UCMDATA to elimiate many WinQueryWindow() calls.
//         July 21 1995 (MAM): Added UCMUI #define to create smaller module with no user-customization or context menu functions.
//         ----------------------------- Version 2.1 Build ----------------------------------------
//         Aug  08 1995 (MAM): Activate frame on button 2 down (prevent context menu on inactive frame)
//         Aug  10 1995 (MAM): Fix render of larger fonts by getting new PS in WM_DRAWITEM instead of using PS supplied by PM
//         Aug  16 1995 (MAM): Removed MIS_TEXT bit flag from MIS_SPACER definition -- OS/2 2.1 does not send WM_MEASUREITEM messages if MIS_TEXT flag is set
//         Aug  29 1995 (MAM): Fixed double-painting of toolbar when sized after creationg (changed WM_SIZE from Post to Send)
//         Aug  29 1995 (MAM): Comment-out UCMENUS_DEBUG for memory allocate
//         Aug  30 1995 (MAM): Fix memory leak from unclosed device context (WM_DESTROY processing)
//         Sept  1 1995 (MAM): Fix memory leak from unfreed drag/drop transfer shared memory
//         Sept 14 1995 (MAM): Improved scrolling algorithms (don't reset scroll posn when window size changes)
//         Sept 18 1995 (MAM): Fixed UCN_SIZE notification logic to only send size change notification when dimension of interest changes (e.g. vert dim of a HORZ menu)
//         Sept 21 1995 (MAM): Fixed painting of disabled menu items (render our own half-tone).
//         Sept 28 1995 (MAM): Added CMS_MATRIX_VERT and CMS_MATRIX_HORZ styles for scrollable matrix menus
//         ----------------------------- Version 2.11 Build ----------------------------------------
//         Oct   2 1995 (MAM): Fixed UCN_DELETED notification to be sent after DELETE is complete
//         May  23 1996 (MAM): Fixed missing 3D edge of scroll buttons which occures on Merlin //c1
//         ----------------------------- Version 2.12 Build ----------------------------------------
//----------------------------------------------------------------------------
// Nice to-dos for future versions:
//
// - Improve performance of UCMenuGetNewID() with following algorithm:
//      1. if the given ID is zero, make it 1 (zero has some special meanings)
//      2. use MM_QUERYITEM to see if given ID is used, if not just return it as a valid ID
//      3. id = pick a random number btw 1->32K.
//      4. use MM_QUERYITEM.  If ID is not used, return it, else:
//      5.   id = id+1
//      6. goto 4 (increment id until we find an unused one)
// - consolidate bubble-handling of button and context menus to one function
// - fix accelarator handling or remove the capability ("~" in text)
// - Optimize repainting for performance:
//    - On size change, repaint entire bar only if:
//         - vertical size changed, or
//         - scroll bar status (on/off) changed
//         otherwise repaint only items affected by the resizing.
//    - On insert/delete, repaint only toolbar area
//      to the right of the inserted/delete item.  Repaint entire
//      bar only if insert/delete causes change in scrollbar status.
//
// - put mouse capture code into Hide window and modify bubble
//   proc to not change active status when pointer moves into hide window.
//   Have hide window generate dummy ID?
//
// - improve loading of bitmaps from resource file by accessing
//   bitmap resource directly and using same bitmap selection algorithm as
//   UCMenuLoadBitmap() does loading from a file (e.g. select resolution
//   *closest* to screen size instead of exact-match only).
//
//----------------------------------------------------------------------------
// Known problems/limitations:
//
//  - Bug in Warp 3.0 can cause corruption of a random toolbar bitmaps
//    during drag/drop operations.  No known workaround. 
//    This problem does not occure on 2.X versions of OS/2.  Severity 1 APAR
//    submitted to Boca, APAR number PJ17913.  Fixed in fix pack #9.
//
//  - Bug in Warp 3.0 causes 64K byte memory leak on every use of WinFileDlg().
//    APAR number PJ16382.  Fixed in fix pack #9.
//
//  - Cannot support MIS_BREAK on submenus due to PM bug in MM_QUERYITEMRECT
//    which can return wrong coordinates when an OWNERDRAW submenu has breaks.
//    Any MIS_BREAK style flags will be removed when the UCMenu is created.
//    Need to create simple testcase and submit OS/2 defect report.
//
//  - Bubble window on submenus not implemented.
//
//----------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------
#define INCL_BASE
#define INCL_PM
#define INCL_WINSTDDRAG
#define MTI_INCLUDED   // PM menu templates
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define OPENREAD(fn)   fopen(fn, "rb")
#define OPENWRITE(fn)  fopen(fn, "wb")
#define FILEHANDLE     FILE *
#define NULLFILE       NULLHANDLE
#define CLOSEFILE(h)   fclose(h)
#define READFILE(Buff,Size,Cnt,h)  fread(Buff, Size, Cnt, h)
#define WRITEFILE(Buff,Size,Cnt,h) fwrite(Buff, Size, Cnt, h)
#define pcslstrchr     strchr
#define SEEKOK(rc)     (rc==0)
#define AnsiUpperBuff(str,len) strupr(str)

#include "UCMENUS.H"     // Externalized definitions
#include "UCMLOCAL.H"    // Internal definitions

//------------------------------------------------------------------------
// Remove the following to generate a smaller module without
// any user-customization functions.  Application-supplied context
// menu will work, but UCMenu will have no context menu of its own.
// Also the UCMenu...BuffetDlg() functions do nothing.  This is for
// use in applications which supply all context menu and customization
// functions.
//------------------------------------------------------------------------
#define UCMUI

//...use 2nd for real build...
//#define DRAGDEBUG (PVOID)0x80000000        // Allow msg dispatching during DrgDrag().
#define DRAGDEBUG NULL                       // Normal drag

// ---------------------------------------------------
// -- Memory allocation switches,
// ---------------------------------------------------
#ifdef DEBUGMENUS
    #define UCMENUS_DEBUG
#else
   #undef UCMENUS_DEBUG
#endif
// #define UCMENUS_DEBUG           // -- switches on debug mem allocation
// #define MYMALLOC_RIGHT_BOUNDARY // -- switches the debug mem alloc on right boundary

//----------------------------------------------------------------------------
// Debug memory allocations
//----------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// -- The non debug version uses malloc, which does less checkings than DosAllocMem
// -- So when debugging, we use DosAllocMem, which will trap earlier than malloc in case
// -- of access violation. But the granularity of DosAllocMem is 1 page (4096 bytes) so
// -- if we want to check the violations at the right boundary of the memory we allocate
// -- we put the end of the memory on a page boundary.
// -------------------------------------------------------------------------------------


#ifdef UCMENUS_DEBUG
   VOID  * MyMalloc(size_t size);
   VOID    MyFree(VOID * p);
   char  * MyStrdup(const char * string);
   #define ERRPRT0(a)       fprintf(stderr,a)
   #define ERRPRT1(a,b)     fprintf(stderr,a,b)
   #define ERRPRTKEEP1(a,b) fprintf(stderr,a,b)
#else
   #define MyMalloc malloc
   #define MyFree   free
   char  * MyStrdup(const char * string);
   #define ERRPRT0(a)
   #define ERRPRT1(a,b)
   #define ERRPRTKEEP1(a,b) b
#endif


//----------------------------------------------------------------------------
// local constants
//----------------------------------------------------------------------------
#define UCAPPNAME   "UCMenus"     //MEK 09/15/94 - for ini file processing
#define UCKEYNAME   "UCKeyName"
#define UCMCLASS    "UCMenu"      // UCMenu window class
#define BUBBLECLASS "UCMBbl"      // Bubble-help window class
#define MAXDESCLEN 256
#define MAX_TMPSIZE 16384
#define MAX_FONTNAMELEN 100       // Max length of a font name
#define MAX_INT         32767     // Max SHORT integer
#define DEFAULT_DELAY   2500      // Default bubble delay time in msec.
#define MIN_BUBBLE_DELAY 150      // Less delay than this treated as zero delay
#define QWL_UCMDATA  4
#define PTR_CHECK_DELAY  500L     // Interval for checking ptr leaving toolbar windows
#define BBLDISMISS_DELAY 4000L    // Auto dismiss of bubble help

#define GETTING_FOCUS   WM_USER +  0x1000  // Note UCMENU_* start with 0x2000
#define UCMNBP1_NEWBMP  WM_USER +  0x1001
#define MSG_ITEMCHANGE  WM_USER +  0x1002  // Notice to bubble window ptr moved to diff item
#define MSG_ENABLE_BUBBLE  WM_USER+0x1003  // Enable bubble window
#define MSG_DISABLE_BUBBLE WM_USER+0x1004  // Disable bubble window
#define MSG_UPDATE_BUBBLE  WM_USER+0x1005  // Used internally in bubble window proc

#define TIMER_BUBBLE       TID_USERMAX-1   // Timer ID for buble help
#define TIMER_BUBBLE_FAKE  TID_USERMAX-2   // Pseudo timer event ID
#define TIMER_PTRCHECK     TID_USERMAX-3   // Check ptr for in/out of menu window
#define TIMER_BBLAUTODISMISS TID_USERMAX-4 // Auto dismiss of bubble help window
// --
// maximum size of the bitmap drawn while dragging
// --
#define UCM_MAX_DRG_CX 100
#define UCM_MAX_DRG_CY 100
// --
// We leave a 2 pixel frame around the item
// --
#define ITEM_FRAME_THICK_LEFT       2
#define ITEM_FRAME_THICK_RIGHT      2
#define ITEM_FRAME_THICK_BOTTOM     2
#define ITEM_FRAME_THICK_TOP        2
#define SUM_ITEM_FRAME_THICK_HORZ   4
#define SUM_ITEM_FRAME_THICK_VERT   4
// --
// We leave some space right and left of the text
// --
#define TEXT_FRAME_THICK_HORZ       1
#define SUM_TEXT_FRAME_THICK_HORZ   2
// --
// There is a frame around the ucmenu (actually it is the frame
//  of the scrollbar which has the same size as the UCM and is drawn
//  over it)
// --
#define UCM_FRAME_THICK             1
#define SUM_UCM_FRAME_THICK         2
// --
// There is a frame around the menu (it is drawn in the hide window
//  which is drawn inside the ucmenu frame )
// --
#define MENU_FRAME_THICK            1
#define SUM_MENU_FRAME_THICK        2
// --
// (MAM) Added constants
// Constants for UCAdjacentItemBlank() Left/Right parameter
//
#define ADJACENT_LEFT               -1
#define ADJACENT_ABOVE              -1
#define ADJACENT_RIGHT              1
#define ADJACENT_BELOW              1

#if defined(_LE_PPC)                                                    
//----------------------------------------------------------------------
// GpiQueryColorData is OK under OS/2 for PowerPC SDK.                  
//----------------------------------------------------------------------
#define GpiQueryColordata GpiQueryColorData                             
#else                                                                   
#endif /* _LE_PPC */                                                    

//----------------------------------------------------------------------------
// Macros
//----------------------------------------------------------------------------
#define POST_TO_MENU  (MRESULT)WinPostMsg(UCMData->hwndMenu, msg, mp1, mp2)
#define SEND_TO_MENU  WinSendMsg(UCMData->hwndMenu, msg, mp1, mp2)
#define MSGBOX(Owner,Title,Msg) WinMessageBox(HWND_DESKTOP,Owner,Msg,Title,0,MB_OK|MB_INFORMATION)

//----------------------------------------------------------------------------
// local structures
//----------------------------------------------------------------------------

typedef struct _UCMDATA {  // Main structure we hang off most window words, has all kinds of useful stuff
   ULONG        size                ;             // Size of this structure
   PFNWP        OldMenuProc         ;             // We subclass the menu & submenu window procedure
   PFNWP        OldSubMenuProc      ;
   HWND         hwndOwner           ;             // Owner of UCMenu
   HWND         hwndUCM             ;             // UCMenu window handle
   HWND         hwndHide            ;             // Hide window handle
   HWND         hwndScroll          ;             // Scrollbar window handle
   HWND         hwndCM              ;             // context menu : loaded once.
   HWND         hwndUserCM          ;             // context menu provided by application, if any
   HWND         hwndMenu            ;             // Handle of the PM menu associated to the ucmenu
   HWND         hwndCMOrig          ;             // Handle of the (sub)menu from which the CM was popped
   HWND         hwndHelpInstance    ;             // Handle of the help instance
   HWND         hwndBubble          ;             // Bubble-help (hover) window
#if defined(UCMUI)
   HWND         hwndTemp            ;             // Temporary window handle
   HWND         hwndSettings        ;             // Window handle of the settings dialog
   HWND         hwndPage1           ;             // Pages of the dialog
   HWND         hwndPage2           ;
   HWND         hwndPage0           ;
#endif
   ULONG        MaxVerticalWidth    ;             // The widest item of vertical UCMENU
   ULONG        MaxHorizontalHeight ;             // The tallest item of horizontal UCMENU
   ULONG        SumItemWidths       ;
   ULONG        SumItemHeights      ;
   ULONG        Style               ;
   ULONG        cx                  ;             // Size to give to all the items if UCS_FORCESIZE
   ULONG        cy                  ;             //
   ULONG        BubbleDelay         ;             // Bubble-help delay (msec)
   ULONG        BubbleRead          ;             // Bubble-help read time (msec)
   ULONG        ulBmpTempId;
   ULONG        MenuPtrTimer        ;             // Timer handle for menu window
   LONG         BgColor             ;             // RGB value of the current background color
   LONG         ItemBgColor         ;             // RGB value of the current item background color
   LONG         BmpInset            ;             // Num of pixels from edge of window that scrollbar arrow bitmaps are drawn //c1
   LONG         BgBmp               ;             // RGB value of the initial bitmap color to be replaced with ItemBgColor
   HMODULE      hModUCM             ;             // Module that we use...
   HMODULE      hModBmp             ;             // Module where we look for the bitmaps
   HBITMAP      hBmpTemp            ;             // Temporary bitmap handle
   HPS          hpsMem              ;             // HPS associated to a mem device context, to perform bitmap manipulations
   PACCELTABLE  AccelTable          ;
   PSZ          pszFontNameSize     ;             // Font of the ucmenu
   USHORT       UCMenuID            ;             // ID of UCMenu window
   USHORT       usItem              ;             // ID of the current submenu
   USHORT       ContextID           ;             // ID of the item over which the context menu is called
   USHORT       TargetID            ;             // ID of the item being target of a drag&drop
   USHORT       HoverID             ;             // ID of item the mouse is hovering over
   USHORT       MinID, MaxID        ;
   USHORT       NbOfRows            ;
   USHORT       NbOfCols            ;
   BOOL         bBmpTempFromFile    ;             // TRUE if hBmpTemp from file, FALSE if from resource
   BOOL         bItemCreation       ;             // TRUE if we are creating an item
   BOOL         bProcessingPP       ;             // TRUE if we are processing a WM_PRESPARAMCHANGED
   BOOL         Active              ;             // Is our app active?  Track UCMENU_ACTIVECHG status.
   BOOL         DisableUpdate       ;             // Update disabled by owner
   TID          tid;                              // Used to store temp thread ids
#if defined(UCMUI)
   CHAR         szTemplatePath[CCHMAXPATH];       // Last path used for the templates
   CHAR         szBitmapPath[CCHMAXPATH];         // Last path used for the bitmaps
#endif
   CHAR         szBitmapSearchPath[MAXPATHL];     // Bitmap search path
   CHAR         szDefaultBitmap[MAXPATHL];
} UCMDATA, *PUCMDATA;

typedef struct _UCMINFO {
   ULONG  cb;                   // size of this structure
   HWND    hwndMenu;            // Menu window-handle
   HMODULE hModule;             // Module where the bitmaps are
   USHORT  NbOfCols;            // Number of Columns (used for a matrix UCM)
   USHORT  NbOfRows;            // Number of Rows    (used for a matrix UCM)
   PSZ     pszBitmapSearchPath; // Path(s) to search for bitmap files.
                                // Environment variables separated by spaces.
   PSZ     pszDefaultBitmap;    // Bitmap to use if bitmap specified for
                                //  a menu item can't be resolved or loaded.
   ULONG   Style;               // Style of item (combination of UCS_ flags )
   ULONG   cx;                  // Size to give to all the items if UCS_FORCESIZE
   ULONG   cy;                  //
   LONG    BgBmp;               // RGB value of the color of the bmp which has to be replaced with ItemBgColor
   LONG    BgColor;             // RGB color of the UCMenu background
   LONG    ItemBgColor;         // RGB color of the UCMenu items background, used if UCS_CHNGBMPBG is set
   PSZ     pszFontNameSize;     // String describing the font of the UCMenu (such as used
   ULONG   ulTmplVersion;       //  in WinSetPresParam), if NULL, UCM_DEFAULTFONT is used
   ULONG   BubbleDelay;         // Bubble-help delay (msec)
   ULONG   BubbleRead;          // Bubble-help read time (msec)
   HMODULE hModUCM;             // Module that we use...
} UCMINFO2, *PUCMINFO2;

typedef struct _MTI {
  USHORT afStyle;
  USHORT afAttribute;
  USHORT idItem;
  CHAR   c[2];
} MTI, *PMTI;

typedef struct _MENUTEMPLATE {
  USHORT Length;
  USHORT Version;
  USHORT CodePage;
  USHORT Offset;
  USHORT Count;
  CHAR   c[2];
} MENUTEMPLATE, *PMENUTEMPLATE;

typedef struct _UCMDLGINFO {
  ULONG    ulSize;
  HWND     hwndUCMenu;
  HWND     hwndBuffet;
  ULONG    ulBuffetMenuID;
  HMODULE  hmodBuffetMenu;
  PVOID    pTemplate;
  BOOL     bFromTemplate;
  PFNWP    OldShredderWndProc;
  PUCMDATA UCMData;
} UCMDLGINFO, * PUCMDLGINFO;

//----------------------------------------------------------------------------
// GpiQueryColorData in pmgpi.h but GpiQueryColordata in os2386.lib
//----------------------------------------------------------------------------
BOOL  APIENTRY GpiQueryColordata(HPS hps, LONG lCount, PLONG alArray);



//----------------------------------------------------------------------------
// local function declarations
//----------------------------------------------------------------------------
MRESULT EXPENTRY          UCMenuWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY          ScrollbarProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY            HideWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY         SubmenuWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY            MenuWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY          BubbleWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY  UCMenuSettingsDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY      UCMenuNBP1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY      UCMenuNBP2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY      UCMenuNBP0DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY     UCMenuStyleDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY      BitmapFileDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY UCMenuCreateBmpDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY          ResBmpDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY             UCMDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY        ShredderWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT _Optlink        UCMenuDrgDrpMsg(PUCMDATA UCMData, HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2, PFNWP WindowProc);
VOID _Optlink  UCMenuRemoveDropEmphasis(PUCMDATA UCMdata, HWND hwnd );
BOOL _Optlink     UCMenuCheckScrolling(HWND hwndUCMenu);
BOOL _Optlink               UCMenuSize(HWND hwndMenu, USHORT Style);
VOID _Optlink       UCMenuLoadMenuData(HWND hwndMenu, PUCMDATA UCMData, ULONG ulVersion, HWND hwndUCM );
VOID _Optlink        UCMenuLoadItemBmp(MENUITEM *Item, PUCMDATA UCMData );
VOID _Optlink       UCMenuCalcItemSize(POWNERITEM poi, USHORT Style, HWND hwndUCMenu, ULONG * pCx, ULONG * pCy);
VOID _Optlink UCMenuCalcUnscaledItemSize(PUCMITEM pUCMI, USHORT Style, HWND hwndUCMenu, ULONG * pCx, ULONG * pCy);
VOID _Optlink         UCMenuCalcBmpPos(POWNERITEM poi, HWND hwndUCM, USHORT Style, POINTL aptlPoints[4], PUCMDATA UCMData);
VOID _Optlink       UCMenuCalcTextSize(PUCMITEM pUCMI, HWND hwndUCM, ULONG * pWidth, ULONG * pHeight);
ULONG _Optlink       UCMenuSelectColor(LONG Color, HPS hps);
VOID _Optlink      UCMenuSetBmpBgColor(PUCMITEM pUCMItem, PUCMDATA UCMData, HPS hps);
VOID _Optlink            UCMenu3DFrame(HPS hps, PRECTL rcl, USHORT hilited);
VOID _Optlink        UCMenuContextMenu(HWND hwndUCMenu, HWND hwndMenu, ULONG FromMouse);
VOID   _Optlink           UCMenuNBP1OK(HWND hwnd);
VOID   _Optlink           UCMenuNBP2OK(HWND hwnd);
BOOL   _Optlink           UCMenuNBP0OK(HWND hwndPage);
VOID   _Optlink       UCMenuStyleDlgOK(HWND hwnd);
VOID   _Optlink       UCMenuUpdateMenu(HWND hwndMenu, BOOL UpdateSubmenus);
VOID    _Optlink      UCMenuUnselectAll(HWND hwndMenu);
USHORT  _Optlink         UCMenuGetNewID(HWND hwndMenu, SHORT sID, PUCMDATA UCMData);
VOID    _Optlink      UCMenuReplaceMenu(HWND hwndOldMenu, HWND hwndNewMenu);
BOOL    _Optlink         UCMenuInitDrag(HWND hwnd, SHORT x, SHORT y);
MRESULT _Optlink         UCMenuDragOver(PUCMDATA UCMData, HWND hwnd, PDRAGINFO pDragInfo);
VOID    _Optlink             UCMenuDrop(HWND hwnd, PDRAGINFO pDraginfo);
VOID    _Optlink UCMenuPresParamChanged(PUCMDATA UCMData, HWND hwnd, MPARAM mp1);
PSZ     _Optlink       UCMenuGetExePath(VOID);
USHORT  _Optlink    UCMenuGetBitmapPath(PUCMDATA UCMDATA, PSZ pszBmp, PSZ pszPathName);
USHORT _Optlink UCMenuGetBitmapFullName(PUCMDATA UCMDATA, PSZ pszBmp, PSZ pszFullName);
VOID    _Optlink         GetMaxItemSize(PUCMDATA UCMData, HWND hwndUCMenu, HWND hwndMenu);
VOID    _Optlink   UCMenuNBP0Initialize(PUCMDATA UCMData, HWND hwnd);
VOID    _Optlink   UCMenuNBP1Initialize(PUCMDATA UCMData, HWND hwnd);
VOID    _Optlink   UCMenuNBP2Initialize(PUCMDATA UCMData, HWND hwnd);
VOID    _Optlink      UCMenuEditBmpFile(HWND hwndNBP1, PSZ pszBmpFileName);
VOID    _System     UCMenuEditBmpFileT2(PVOID pArgs);
BOOL    _Optlink    UCMenuCreateBmpFile(PSZ pszBmpFileName, ULONG cx, ULONG cy);
VOID    _Optlink    UCMenuNBP1UpdateBmp(HWND hwnd, PSZ pszFileName);
VOID    _Optlink    UCMenuDisplayHelp(PUCMDATA UCMData, USHORT usPanelID, USHORT usCustomID);
VOID    _Optlink     InitializeStyleDlg(PUCMDATA UCMData, HWND hwnd);
BOOL    _Optlink         TranslateAccel(PUCMDATA UCMData, HWND HwndMenu, USHORT Key, PQMSG QMsg);
VOID    _Optlink           AddAccelItem(PUCMDATA UCMData, USHORT Key, ULONG id);
VOID    _Optlink        RemoveAccelItem(PUCMDATA UCMData, USHORT Key);
PSZ     _Optlink           SubMemStrdup(PVOID pSubMem, PSZ pszSource);
PSZ     _Optlink          nlsgetmessage(HAB Hab, HMODULE HModule, SHORT msg, SHORT buffnum);
PVOID   _Optlink    UCMenuMakeTemplate2(HWND hwndMenu, PVOID pBuf, USHORT MenuAttr);
ULONG   _Optlink      UCMenuTemplateLen(HWND hwndMenu);
HWND    _Optlink           UCMenuCreate(HAB hab, HWND hParent, HWND hOwner, ULONG ulStyle,
                                        LONG x, LONG y, LONG cx, LONG cy, HWND hInsertBehind,
                                        ULONG ulID, PUCMINFO2 pUCMInfo2);
VOID    _System    UCMenuExecuteProgram(PSZ pszName);
SHORT   _Optlink     UCMenuGetActionID2(HWND hwndMenu, PSZ pszAction, BOOL bSubmenus, SHORT sStartID);
VOID    _System        UCMenuLoadResBmp(PVOID pArgs);
VOID    _Optlink         UCMenuNotifAll(PUCMDATA UCMData, HWND hMenu, USHORT usNotif);
BOOL    _Optlink    UCAdjacentItemBlank(HWND MenuHwnd, SHORT ItemID, int LeftRight);
void    _Optlink UCMenuCreateBubbleWindow(HWND UCMenuHwnd, UCMDATA *UCMData);
LONG    _Optlink UCMString2Int(char *lpString, BOOL *lpTranslated);

//----------------------------------------------------------------------------
// UCMenuCreateFromResource
//----------------------------------------------------------------------------
// :function res=&IDF_UCMCREATERES. name='UCMenuCreateFromResource' text='Create a ucmenu from a resource menu'.
// This function creates a ucmenu using a menu template stored in the resources.
// :syntax name='UCMenuCreateFromResource' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID hmodResource usMenuID pUCMInfo phTextMenu' return='hUCMenu' .
// :fparams.
// :fparam name='hab' type='HAB' io='input' .
// Handle of the anchor-block.
// :fparam name='hParent' type='HWND' io='input' .
// Handle of the parent window
// :fparam name='hOwner' type='HWND' io='input' .
// Handle of the owner window
// :fparam name='flStyle' type='ULONG' io='input' .
// Style flags of the ucmenu window, combination of WS_ flags and CMS_VERT CMS_HORZ or CMS_MATRIX
// :fparam name='x' type='ULONG' io='input'.
// x coordinate of ucmenu window position
// :fparam name='y' type='ULONG' io='input'.
// y coordinate of ucmenu window position
// :fparam name='cx' type='ULONG' io='input'.
// width of the ucmenu window, ignored if vertical or matrix ucmenu
// :fparam name='cy' type='ULONG' io='input'.
// height of the ucmenu window, ignored if horizontal or matrix ucmenu
// :fparam name='hInsertBehind' type='ULONG' io='input'.
// Sibling window behind which the ucmenu is placed, can also be HWND_TOP or HWND_BOTTOM.
// :fparam name='ulID' type='ULONG' io='input'.
// ID given to the ucmenu.
// :fparam name='hmodResource' type='HMODULE' io='input'.
// Handle of the module where the menu resource is to be found.
// :fparam name='usMenuID' type='USHORT' io='input'.
// ID of the resource menu used as a template to create the ucmenu.
// :fparam name='pUCMInfo' type='PUCMINFO' io='input'.
// Pointer to the ucmenu creation structure
// :fparam name='phTextMenu' type='PHWND' io='output'.
// Handle of the menu loaded from the resource.
// It should normally not be used.
// :freturns.
// :fparam name='hUCMenu' type='PSZ' io='return'.
// Handle of the ucmenu or zero if the creation failed.
// :efparams.
// :remarks.
// :related.
// UCMInfo
// :efunction.
//----------------------------------------------------------------------------
HWND    APIENTRY UCMenuCreateFromResource(HAB hab, HWND hParent, HWND hOwner,
                                          ULONG ulStyle, LONG x, LONG y, LONG cx, LONG cy,
                                          HWND hInsertBehind, ULONG ulID,
                                          HMODULE hmodResource, USHORT usMenuID,
                                          PUCMINFO pUCMInfo, PHWND phTextMenu )
{
   HWND     hMenu;
   ERRORID  err;

   hMenu = WinLoadMenu( HWND_OBJECT, hmodResource, usMenuID );

   if ( hMenu ){
      UCMINFO2 UCMInfo2;

      WinSetWindowUShort( hMenu, QWS_ID, (USHORT)ulID );

      UCMInfo2.cb = sizeof( UCMINFO2 );
      UCMInfo2.hwndMenu = hMenu;
      UCMInfo2.hModule              = pUCMInfo->hModule;
      UCMInfo2.NbOfCols             = pUCMInfo->NbOfCols;
      UCMInfo2.NbOfRows             = pUCMInfo->NbOfRows;
      UCMInfo2.pszBitmapSearchPath  = pUCMInfo->pszBitmapSearchPath;
      UCMInfo2.pszDefaultBitmap     = pUCMInfo->pszDefaultBitmap;
      UCMInfo2.Style                = pUCMInfo->Style;
      UCMInfo2.cx                   = pUCMInfo->cx;
      UCMInfo2.cy                   = pUCMInfo->cy;
      UCMInfo2.BgBmp                = pUCMInfo->BgBmp;
      UCMInfo2.BgColor              = pUCMInfo->BgColor;
      UCMInfo2.ItemBgColor          = pUCMInfo->ItemBgColor;
      UCMInfo2.pszFontNameSize      = pUCMInfo->pszFontNameSize;
      UCMInfo2.BubbleDelay          = pUCMInfo->BubbleDelay;  // V2.04 
      UCMInfo2.BubbleRead           = pUCMInfo->BubbleRead;   // V2.04
      UCMInfo2.hModUCM              = pUCMInfo->hModUCM;      // V2.04 
      UCMInfo2.ulTmplVersion        = UCMTMPLVERSION;

      *phTextMenu = hMenu;
      return UCMenuCreate( hab, hParent,  hOwner, ulStyle, x, y, cx, cy,
                           hInsertBehind, ulID, &UCMInfo2 );
   } else {
      return NULLHANDLE;
   } // endif

}

//----------------------------------------------------------------------------
// UCMenuCreateFromHMenu
//----------------------------------------------------------------------------
// :function res=&IDF_UCMCREATEHMENU. name='UCMenuCreateFromHMenu' text='Create a ucmenu from a menu handle'.
// This function creates a ucmenu using an already loaded or created menu.
// :syntax name='UCMenuCreateFromHMenu' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID  hMenu pUCMInfo' return='hUCMenu'.
// :fparams.
// :fparam name='hab' type='HAB' io='input' .
// Handle of the anchor-block.
// :fparam name='hParent' type='HWND' io='input' .
// Handle of the parent window
// :fparam name='hOwner' type='HWND' io='input' .
// Handle of the owner window
// :fparam name='flStyle' type='ULONG' io='input' .
// Style flags of the ucmenu window, combination of WS_ flags and CMS_VERT CMS_HORZ or CMS_MATRIX
// :fparam name='x' type='ULONG' io='input'.
// x coordinate of ucmenu window position
// :fparam name='y' type='ULONG' io='input'.
// y coordinate of ucmenu window position
// :fparam name='cx' type='ULONG' io='input'.
// width of the ucmenu window, ignored if vertical or matrix ucmenu
// :fparam name='cy' type='ULONG' io='input'.
// height of the ucmenu window, ignored if horizontal or matrix ucmenu
// :fparam name='hInsertBehind' type='ULONG' io='input'.
// Sibling window behind which the ucmenu is placed, can also be HWND_TOP or HWND_BOTTOM.
// :fparam name='ulID' type='ULONG' io='input'.
// ID given to the ucmenu.
// :fparam name='hMenu' type='HWND' io='input'.
// Handle of the menu used as a template to create the ucmenu
// :fparam name='pUCMInfo' type='PUCMINFO' io='input'.
// Pointer to the ucmenu creation structure
// :freturns.
// :fparam name='hUCMenu' type='PSZ' io='return'.
// Handle of the ucmenu or zero if the creation failed.
// :efparams.
// :remarks.
// It is useful in case you want to create a void ucmenu and dynamically fill it.
// :related.
// UCMInfo
// :efunction.
//----------------------------------------------------------------------------
HWND    APIENTRY UCMenuCreateFromHMenu( HAB hab, HWND hParent, HWND hOwner,
                                        ULONG ulStyle, LONG x, LONG y, LONG cx, LONG cy,
                                        HWND hInsertBehind, ULONG ulID,
                                        HWND hMenu, PUCMINFO pUCMInfo )
{
   if ( hMenu ){
      UCMINFO2 UCMInfo2;

      UCMInfo2.cb = sizeof( UCMINFO2 );
      UCMInfo2.hwndMenu = hMenu;
      UCMInfo2.hModule              = pUCMInfo->hModule;
      UCMInfo2.NbOfCols             = pUCMInfo->NbOfCols;
      UCMInfo2.NbOfRows             = pUCMInfo->NbOfRows;
      UCMInfo2.pszBitmapSearchPath  = pUCMInfo->pszBitmapSearchPath;
      UCMInfo2.pszDefaultBitmap     = pUCMInfo->pszDefaultBitmap;
      UCMInfo2.Style                = pUCMInfo->Style;
      UCMInfo2.cx                   = pUCMInfo->cx;
      UCMInfo2.cy                   = pUCMInfo->cy;
      UCMInfo2.BgBmp                = pUCMInfo->BgBmp;
      UCMInfo2.BgColor              = pUCMInfo->BgColor;
      UCMInfo2.ItemBgColor          = pUCMInfo->ItemBgColor;
      UCMInfo2.pszFontNameSize      = pUCMInfo->pszFontNameSize;
      UCMInfo2.BubbleDelay          = pUCMInfo->BubbleDelay;  // V2.04 
      UCMInfo2.BubbleRead           = pUCMInfo->BubbleRead;   // V2.04
      UCMInfo2.hModUCM              = pUCMInfo->hModUCM;      // V2.04 
      UCMInfo2.ulTmplVersion        = UCMTMPLVERSION;
      return UCMenuCreate( hab, hParent,  hOwner, ulStyle, x, y, cx, cy,
                           hInsertBehind, ulID, &UCMInfo2 );
   } else {
      return NULLHANDLE;
   } // endif

}


//----------------------------------------------------------------------------
// UCMenuCreateFromTemplate
//----------------------------------------------------------------------------
// :function res=&IDF_UCMCREATETMPL. name='UCMenuCreateFromTemplate' text='Create a ucmenu from a menu template'.
// This function creates a ucmenu using a menu template stored in the resources.
// :syntax name='UCMenuCreateFromTemplate' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID pMenuTemplate pUCMInfo phTextMenu' return='hUCMenu' .
// :fparams.
// :fparam name='hab' type='HAB' io='input' .
// Handle of the anchor-block.
// :fparam name='hParent' type='HWND' io='input' .
// Handle of the parent window
// :fparam name='hOwner' type='HWND' io='input' .
// Handle of the owner window
// :fparam name='flStyle' type='ULONG' io='input' .
// Style flags of the ucmenu window, combination of WS_ flags and CMS_VERT CMS_HORZ or CMS_MATRIX
// :fparam name='x' type='ULONG' io='input'.
// x coordinate of ucmenu window position
// :fparam name='y' type='ULONG' io='input'.
// y coordinate of ucmenu window position
// :fparam name='cx' type='ULONG' io='input'.
// width of the ucmenu window, ignored if vertical or matrix ucmenu
// :fparam name='cy' type='ULONG' io='input'.
// height of the ucmenu window, ignored if horizontal or matrix ucmenu
// :fparam name='hInsertBehind' type='ULONG' io='input'.
// Sibling window behind which the ucmenu is placed, can also be HWND_TOP or HWND_BOTTOM.
// :fparam name='ulID' type='ULONG' io='input'.
// ID given to the ucmenu.
// :fparam name='pmtMenuTemplate' type='PVOID' io='input'.
// Pointer to the menu template in binary format
// :fparam name='pUCMInfo' type='PUCMINFO' io='input'.
// Pointer to the ucmenu creation structure
// :fparam name='phTextMenu' type='PHWND' io='output'.
// Handle of the menu loaded from the resource.
// It should normally not be used.
// :freturns.
// :fparam name='hUCMenu' type='PSZ' io='return'.
// Handle of the ucmenu or zero if the creation failed.
// :efparams.
// :remarks.
// :related.
// UCMInfo
// :efunction.
//----------------------------------------------------------------------------
HWND    APIENTRY UCMenuCreateFromTemplate(HAB hab, HWND hParent, HWND hOwner,
                                          ULONG ulStyle, LONG x, LONG y, LONG cx, LONG cy,
                                          HWND hInsertBehind, ULONG ulID,
                                          PVOID pmtMenuTemplate,
                                          PUCMINFO pUCMInfo, PHWND phTextMenu )
{
   HWND     hMenu;
   UCMINFO2 UCMInfo2;


   if ( *( (PULONG)pmtMenuTemplate ) == UCMTMPLSIG ){
      UCMInfo2.ulTmplVersion = *( (PULONG)( (PBYTE)pmtMenuTemplate + 4 ) );
      hMenu = WinCreateMenu( HWND_OBJECT, (PVOID)((PBYTE)pmtMenuTemplate+8) );
   } else {
//      UCMInfo2.ulTmplVersion = 0;
//      hMenu = WinCreateMenu( HWND_OBJECT, pmtMenuTemplate );
      return NULLHANDLE;
   } // endif

   if ( hMenu ){

      WinSetWindowUShort( hMenu, QWS_ID, (USHORT)ulID );

      UCMInfo2.cb = sizeof( UCMINFO2 );
      UCMInfo2.hwndMenu = hMenu;
      UCMInfo2.hModule              = pUCMInfo->hModule;
      UCMInfo2.NbOfCols             = pUCMInfo->NbOfCols;
      UCMInfo2.NbOfRows             = pUCMInfo->NbOfRows;
      UCMInfo2.pszBitmapSearchPath  = pUCMInfo->pszBitmapSearchPath;
      UCMInfo2.pszDefaultBitmap     = pUCMInfo->pszDefaultBitmap;
      UCMInfo2.Style                = pUCMInfo->Style;
      UCMInfo2.cx                   = pUCMInfo->cx;
      UCMInfo2.cy                   = pUCMInfo->cy;
      UCMInfo2.BgBmp                = pUCMInfo->BgBmp;
      UCMInfo2.BgColor              = pUCMInfo->BgColor;
      UCMInfo2.ItemBgColor          = pUCMInfo->ItemBgColor;
      UCMInfo2.pszFontNameSize      = pUCMInfo->pszFontNameSize;
      UCMInfo2.BubbleDelay          = pUCMInfo->BubbleDelay;  // V2.04 
      UCMInfo2.BubbleRead           = pUCMInfo->BubbleRead;   // V2.04
      UCMInfo2.hModUCM              = pUCMInfo->hModUCM;      // V2.04 
      *phTextMenu = hMenu;
      return UCMenuCreate( hab, hParent,  hOwner, ulStyle, x, y, cx, cy,
                           hInsertBehind, ulID, &UCMInfo2 );
   } else {
      return NULLHANDLE;
   } // endif

}

//----------------------------------------------------------------------------
// UCMenuCreate
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UCMCREATE. name='UCMenuCreate' text='Create a ucmenu from a menu'.
// This function creates a ucmenu using a menu already loaded.
// :syntax name='UCMenuCreateFromTemplate' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID pUCMInfo2 ' return='hUCMenu' .
// :fparams.
// :fparam name='hab' type='HAB' io='input' .
// Handle of the anchor-block.
// :fparam name='hParent' type='HWND' io='input' .
// Handle of the parent window
// :fparam name='hOwner' type='HWND' io='input' .
// Handle of the owner window
// :fparam name='flStyle' type='ULONG' io='input' .
// Style flags of the ucmenu window, combination of WS_ flags and CMS_VERT CMS_HORZ or CMS_MATRIX
// :fparam name='x' type='ULONG' io='input'.
// x coordinate of ucmenu window position
// :fparam name='y' type='ULONG' io='input'.
// y coordinate of ucmenu window position
// :fparam name='cx' type='ULONG' io='input'.
// width of the ucmenu window, ignored if vertical or matrix ucmenu
// :fparam name='cy' type='ULONG' io='input'.
// height of the ucmenu window, ignored if horizontal or matrix ucmenu
// :fparam name='hInsertBehind' type='ULONG' io='input'.
// Sibling window behind which the ucmenu is placed, can also be HWND_TOP or HWND_BOTTOM.
// :fparam name='ulID' type='ULONG' io='input'.
// ID given to the ucmenu.
// :fparam name='pUCMInfo2' type='PUCMINFO2' io='input'.
// Pointer to the ucmenu creation structure
// :freturns.
// :fparam name='hUCMenu' type='PSZ' io='return'.
// Handle of the ucmenu or zero if the creation failed.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
HWND    _Optlink UCMenuCreate( HAB hab, HWND hParent, HWND hOwner,
                               ULONG ulStyle, LONG x, LONG y, LONG cx, LONG cy,
                               HWND hInsertBehind, ULONG ulID,
                               PUCMINFO2 pUCMInfo2 )
{


 /* Register UCMenu class with storage for 2 pointers */

 /* (MAM) Note we must always register the class, even if it already */
 /* exists.  Otherwise an app might free and reload the UCMenus DLL  */
 /* in the same process and the class window proc pointer would be   */
 /* out of date.  Reregistration will replace existing class parms.  */

 if ( !WinRegisterClass( hab, UCMCLASS, (PFNWP)UCMenuWndProc, (ULONG)CS_SIZEREDRAW, (ULONG)(2*sizeof(PVOID)) ) ) {
    return NULLHANDLE;
 } // endif

 return  WinCreateWindow( hParent,
                          UCMCLASS,
                          "",
                          ulStyle,
                          x,
                          y,
                          cx,
                          cy,
                          hOwner,
                          hInsertBehind,
                          ulID,
                          (PVOID)pUCMInfo2,
                          NULL );

}

//----------------------------------------------------------------------------
// UCMenuLoadBitmap
//----------------------------------------------------------------------------
// :function res=&IDF_LOADBIT. name='UCMenuLoadBitmap' text='Loads a bitmap'.
// This function loads a bitmap from a file and returns its handle.
// :syntax name='UCMenuLoadBitmap' params='pszFileName' return='hBitmap' .
// :fparams.
// :fparam name='pszFileName' type='PSZ' io='input' .
// Name of the file to load.
// :freturns.
// :fparam name='hBitmap' type='LONG' io='return'.
// Bit-map handle (0 if error)
// :efparams.
// :remarks.
// If there is an array of bitmaps, the bitmap the most appropriate to the
// current display will be chosen.
// :related.
// :efunction.
//----------------------------------------------------------------------------
LONG APIENTRY    UCMenuLoadBitmap(PSZ pszFileName)
{
  HBITMAP                 hBmp = 0;
  FILEHANDLE              File;
  ULONG                   rc;
  USHORT                  usType = 0;           // #@!!! compiler warnings
  PBITMAPARRAYFILEHEADER2 pbafh2 = NULL;        // (MAM) chng init values to NULL instead of ptr to 0
  PBITMAPFILEHEADER2      pbfh2  = NULL;                       
  PBITMAPINFOHEADER2      pbih2  = NULL;                       
  PBITMAPINFO2            pbmi2  = NULL;                       
  PBITMAPARRAYFILEHEADER  pbafh  = NULL;                       
  PBITMAPFILEHEADER       pbfh   = NULL;                       
  PBITMAPINFOHEADER       pbih   = NULL;                       
  BOOL                    f2;        // format 1.x or 2.x
  ULONG                   ulOffset;
  PBYTE                   pData  = NULL;
  ULONG                   ulDataSize;
  SIZEL                   sizel;
  HPS                     hPS = WinGetPS(HWND_DESKTOP);

  /* If this is not a .BMP file, let PM try to extract an icon from it */
  //...removed because bitmaps made from icons have black backgrounds
  //...unless you do a lot more work to mask the background bits.
//{
//  char *BmpFn;
//  BmpFn = strdup(pszFileName);
//  AnsiUpperBuff(BmpFn, strlen(BmpFn));
//  if (strstr(BmpFn, ".BMP")==NULL) {
//    HPOINTER Icon;
//    POINTERINFO IconInfo;
//    HBITMAP  IconBmp = 0;
//
//    free(BmpFn);
//    Icon = WinLoadFileIcon(pszFileName, TRUE);
//    if (Icon != 0) {
//      if (WinQueryPointerInfo(Icon, &IconInfo)) {
//        if ((IconInfo.hbmPointer!=0) && (IconInfo.hbmColor!=0)) {
//          IconBmp = IconInfo.hbmColor;
//          //...what we should do here to get a good bitmap from a file, is
//          //...use the hbmPointer bitmap (which is a 2X high monochrome bitmap
//          //...consisting of and AND mask and an XOR mask) and the hbmColor
//          //...bitmap and create a new bitmap that has the background bits set
//          //...to the background color.  The black pixels of the AND mask indicate
//          //...background pixels of the color bitmap.
//          //...Hummm... maybe can use WinDrawPointer() to do all this for us,
//          //...and draw into a bitmap which is pre-filled w/the background color?
//        }
//        WinFreeFileIcon(Icon);
//      }
//    }
//
//    return IconBmp; // Return file bitmap if we found it
//  }
//  free(BmpFn);
//}

  //--- open the file
  File = OPENREAD(pszFileName);
  if (File == NULLFILE) goto ExitLoadBMP;

  /* Read image type, and reset the stream...................................*/
  /* The image type is a USHORT, so we only read that........................*/
  rc = READFILE(&usType, 1, sizeof(usType), File);
  if (rc != sizeof(usType)) goto ExitLoadBMP;


  /* Next read the bitmap info header........................................*/
  // we allocate enough to hold a complete bitmap array file header
  pbafh2 = (PBITMAPARRAYFILEHEADER2)MyMalloc(sizeof(*pbafh2)+256*sizeof(RGB2));
  if (!pbafh2) goto ExitLoadBMP;
  /* Next we assign pointers to the file header and bitmap info header...*/
  /* Both the 1.x and 2.x structures are assigned just in case...........*/
  pbfh2 = &pbafh2->bfh2;
  pbih2 = &pbfh2->bmp2;
  pbmi2 = (PBITMAPINFO2)pbih2;
  pbafh = (PBITMAPARRAYFILEHEADER)pbafh2;
  pbfh  = &pbafh->bfh;
  pbih  = &pbfh->bmp;
  switch (usType) {
    case BFT_BMAP:
    case BFT_ICON:
    case BFT_POINTER:
    case BFT_COLORICON:
    case BFT_COLORPOINTER: {
      /* Now we assume the image is a 2.0 image and so we read a bitmap-file-*/
      /* Now we reset the stream, next we'll read the bitmap info header. To do .*/
      /* this we need to reset the stream to 0...................................*/
      rc = fseek(File, 0, SEEK_SET);
      if (!SEEKOK(rc)) goto ExitLoadBMP;
      /*-header-2 structure..................................................*/
      rc = READFILE(pbfh2, 1, sizeof(*pbfh2), File);
      if (rc != sizeof(*pbfh2)) goto ExitLoadBMP;

      f2 = pbih2->cbFix > sizeof(*pbih); // 1.x or 2.x bitmap
      /* We will need to read the color table. Thus we position the stream...*/
      /* so that the next read will read IT. This, of course, depends on the.*/
      /* type of the bitmap (old vs new), note that in the NEW case, we can..*/
      /* not be certain of the size of the bitmap header.....................*/
      ulOffset = (f2) ? sizeof(*pbfh2) + pbih->cbFix - sizeof(*pbih2):
                        sizeof(*pbfh);
    } break;

    case BFT_BITMAPARRAY: {
      /* Now we are dealing with a bitmap array. This is a collection of ....*/
      /* bitmap files and each has its own file header.......................*/
      BOOL   bBest = FALSE;
      ULONG  ulCurOffset, ulOffsetTemp = 0;
      LONG   lScreenWidth;
      LONG   lScreenHeight;
      LONG   lClrsDev, lClrsTemp = 0;
      LONG   lClrs;
      ULONG  ulSizeDiff, ulSizeDiffTemp = 0xffffffff;
      HDC    hdc;

      // -- We will browse through the array and chose the bitmap best suited
      // -- for the current display size and color capacities.
      hdc = GpiQueryDevice( hPS );
      DevQueryCaps( hdc, CAPS_COLORS, 1, &lClrsDev );
      DevQueryCaps( hdc, CAPS_WIDTH,  1, &lScreenWidth );
      DevQueryCaps( hdc, CAPS_HEIGHT, 1, &lScreenHeight );
      pbafh2->offNext = 0;
      do {
         ulCurOffset = pbafh2->offNext;
         rc = fseek( File, pbafh2->offNext, SEEK_SET );
         if ( !SEEKOK(rc) ){
            goto ExitLoadBMP;
         } // endif
         rc = READFILE( pbafh2, 1, sizeof(*pbafh2), File );
         if ( rc != sizeof(*pbafh2) ){
            goto ExitLoadBMP;
         } // endif
         f2 = pbih2->cbFix > sizeof(*pbih);
         if ( f2 ){
          lClrs = 1 << ( pbafh2->bfh2.bmp2.cBitCount * pbafh2->bfh2.bmp2.cPlanes);
         } else {
          lClrs = 1 << ( pbafh->bfh.bmp.cBitCount * pbafh->bfh.bmp.cPlanes);
         } //endif
         if ( ( pbafh2->cxDisplay == 0 ) && ( pbafh2->cyDisplay == 0 ) ) {
            // This is a device independant bitmap
            // Process it as a VGA
            pbafh2->cxDisplay = 640;
            pbafh2->cyDisplay = 480;
         } // endif
         ulSizeDiff = abs( pbafh2->cxDisplay - lScreenWidth ) + abs( pbafh2->cyDisplay - lScreenHeight );
         if ( ( lClrsDev == lClrs ) &&
              ( ulSizeDiff == 0 ) ){
            // We found the perfect match
            bBest = TRUE;
            ulOffsetTemp = ulCurOffset;
         } else {
            if (    ( ulOffsetTemp == 0 )                                // First time thru
                 || ( ulSizeDiff < ulSizeDiffTemp )                      // Better fit than any previous
                 || ( ( lClrs > lClrsTemp ) && ( lClrs < lClrsDev ) )    // More colors than prev & less than device
                 || ( ( lClrs < lClrsTemp ) && ( lClrs > lClrsDev ) ) ){
              ulOffsetTemp = ulCurOffset;                                // Make this our current pick
              lClrsTemp   = lClrs;
              ulSizeDiffTemp = ulSizeDiff;
           } // endif
         } // endif
      } while ( ( pbafh2->offNext != 0 ) && !bBest ); // enddo

      // Now retrieve the best bitmap
      rc = fseek( File, ulOffsetTemp, SEEK_SET );
      if ( !SEEKOK(rc) ){
         goto ExitLoadBMP;
      } // endif
      rc = READFILE( pbafh2, 1, sizeof(*pbafh2), File );
      if ( rc != sizeof(*pbafh2) ){
         goto ExitLoadBMP;
      } // endif

      f2 = pbih2->cbFix > sizeof(*pbih);
      /* as before, we calculate where to position the stream in order to ...*/
      /* read the color table information....................................*/
      ulOffset = ulOffsetTemp;
      ulOffset += (f2) ? sizeof(*pbafh2) + pbih2->cbFix - sizeof(*pbih2):
                         sizeof(*pbafh);
    } break;

   default:
     goto ExitLoadBMP;
  } /* endswitch */
  /* We now position the stream on the color table information...............*/
  rc = fseek(File, ulOffset, SEEK_SET);
  if (!SEEKOK(rc)) goto ExitLoadBMP;

  /* Read the color table....................................................*/
  if (f2) {
    /* For a 2.0 bitmap, all we need to do is read the color table...........*/
    /* The bitmap info structure is just the header + color table............*/
    // If we have 24 bits per pel, there is usually no color table, unless
    // pbih2->cclrUsed or pbih2->cclrImportant are non zero, we should
    // test that !
    if ( pbih2->cBitCount <24 ) {
       ULONG ul = (1 << pbih2->cBitCount) * sizeof(RGB2);
       rc = READFILE(&pbmi2->argbColor[0], 1, ul, File);
       if (rc != ul) goto ExitLoadBMP;
    } // endif
    /* remember the bitmap info we mentioned just above?.....................*/
    pbmi2 = (PBITMAPINFO2)pbih2;
  } else {
    /* This is an old format bitmap. Since the common format is the 2.0......*/
    /* We have to convert all the RGB entries to RGB2........................*/
    ULONG ul, cColors;
    RGB   rgb;
    if (pbih->cBitCount <24)
      cColors = 1 << pbih->cBitCount;
    else
    // If there are 24 bits per pel, the 24 bits are assumed to be a RGB value
      cColors = 0;
    /* Loop over the original table and create the new table, the extra byte.*/
    /* has to be 0...........................................................*/
    for (ul = 0; ul < cColors; ul++) {
      READFILE(&rgb, 1, sizeof(rgb), File);
      pbmi2->argbColor[ul].bRed      = rgb.bRed;
      pbmi2->argbColor[ul].bGreen    = rgb.bGreen;
      pbmi2->argbColor[ul].bBlue     = rgb.bBlue;
      pbmi2->argbColor[ul].fcOptions = 0;
    } /* endfor */

    // we have to convert the old to the new version header
    pbmi2->cbFix = sizeof(*pbih2);
    pbmi2->cBitCount = pbih->cBitCount;
    pbmi2->cPlanes = pbih->cPlanes;
    pbmi2->cy = pbih->cy;
    pbmi2->cx = pbih->cx;
    // set rest to zero
    memset((PCHAR)pbmi2 +16, 0, sizeof(*pbih2)-16);
  } /* endif */

  /* We have the 2.0 bitmap info structure set...............................*/
  /* move to the stream to the start of the bitmap data......................*/
  rc = fseek(File, pbfh2->offBits, SEEK_SET);
  if (!SEEKOK(rc)) goto ExitLoadBMP;

  /* Read the bitmap data, the read size is derived using the magic formula..*/
  /* The bitmap scan line is aligned on a doubleword boundary................*/
  /* The size of the scan line is the number of pels times the bpp...........*/
  /* After aligning it, we divide by 4 to get the number of bytes, and.......*/
  /* multiply by the number of scan lines and the number of pel planes.......*/
  if ( pbmi2->ulCompression ){
     ulDataSize = pbmi2->cbImage;
  } else {
     ulDataSize = (((pbmi2->cBitCount * pbmi2->cx) + 31) / 32) * 4 *
                   pbmi2->cy * pbmi2->cPlanes;
  } /* endif */
  pData = (PBYTE)MyMalloc(ulDataSize);
  if (!pData) goto ExitLoadBMP;
  rc = READFILE(pData, 1, ulDataSize, File);
  if (rc != ulDataSize) goto ExitLoadBMP;

  /* Now, we create the bitmap...............................................*/
  sizel.cx = pbmi2->cx;
  sizel.cy = pbmi2->cy;

  hBmp= GpiCreateBitmap(hPS, (PBITMAPINFOHEADER2)pbmi2, CBM_INIT, pData, pbmi2);

  ExitLoadBMP:
  if (pData) MyFree(pData);
  if (pbafh2) MyFree(pbafh2);
  CLOSEFILE(File);
  WinReleasePS(hPS);
  return(hBmp);
}



//----------------------------------------------------------------------------
// UCMenuSelectColor : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// :pfunction res=&IDF_SELCOL. name='UCMenuSelectColor' text='Add a entry in the color palette'.
// This function add an entry in the color palette
// :syntax name='UCMenuSelectColor' params='Color, hps' return='colorIndex' .
// :fparams.
// :fparam name='Color' type='LONG' io='input' .
// RGB value of the chosen color
// :fparam name='hps' type='HPS' io='input' .
// HPS in which indexed color palette we add an entry
// :freturns.
// :fparam name='colorIndex' type='ULONG' io='return'.
// Index of the added color
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
ULONG _Optlink       UCMenuSelectColor(LONG Color, HPS hps)
{
   LONG  alArray[4];

   // ------------------------------------------------------------------------------------------
   // -- Toolkit 2.1 bug "GpiQueryColorData" in pmgpi.h and "GpiQueryColordata" in os2386.lib !!
   // -- -> prototype added in ucmenus.c
   // ------------------------------------------------------------------------------------------
   GpiQueryColordata(hps, 3L, alArray);
   GpiCreateLogColorTable( hps,
                           0L,
                           LCOLF_CONSECRGB,
                           alArray[QCD_LCT_HIINDEX] + 1,
                           1L,
                           &Color );

   return (alArray[QCD_LCT_HIINDEX]+1);

}

//----------------------------------------------------------------------------
// UCMenuSetBmpBgColor : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// This function is called when the background color of a bitmap needs to be
// changed to match the current background face color of the toolbar.  This
// is done by reading the bitmap color table and changing the entry that
// corresponds to the bitmap background.  The bitmap is then updated with the
// new color table.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuSetBmpBgColor( PUCMITEM pUCMItem, PUCMDATA UCMData, HPS hps )
{

  BITMAPINFOHEADER2 BmpHeader;            // Bitmap header
  PBYTE        pbBits = NULL;             // Ptr to bitmap pixel values
  PBITMAPINFO2 BmpInfo = NULL;            // Bitmap header + color table
  ULONG        BitsLen;                   // Length of bitmap pixel buffer
  ULONG        BmpInfoLen;                // Length of bitmap header + color table
  ULONG        ulMaxPaletteIndex;

  BmpHeader.cbFix = sizeof( BITMAPINFOHEADER2 );
  GpiQueryBitmapInfoHeader( pUCMItem->hBmp, &BmpHeader );

  // We can only background color map standard format bitmaps (2,16,256 color). 
  // With more work we could do 24-bit (true color) bitmaps, but it would be
  // very slow since we would have to walk the bitmap and change every pixel
  // that was in the background color.

  switch (BmpHeader.cBitCount) {
    case 1:
    case 4:
    case 8:
      break;    // continue and process
    default:
      return;   // no can do, just return
  }

  // Number of bytes in bitmap is width x bits/pel x planes x height
  // with rounding up of each line to a 4 byte boundry
  BitsLen = (((BmpHeader.cBitCount * BmpHeader.cx)+31)/32)*4  // one row on 4-byte boundry
             * BmpHeader.cPlanes                           // number of planes
             * BmpHeader.cy;                               // bitmap height

  // Size of BITMAPINFO2 structure we need is basic structure size plus
  // room for bitmap color table.  Color table is either the exact
  // size given in the bitmap header, or large enough to hold
  // the bigest pel index value (which depends on bits/pel). 

  if (BmpHeader.cclrUsed == 0)              // All index values are used
    ulMaxPaletteIndex = 1 << BmpHeader.cBitCount;
  else
    ulMaxPaletteIndex = BmpHeader.cclrUsed; // Only this many used


  BmpInfoLen = sizeof( BITMAPINFO2 ) + (sizeof( RGB2 ) * ulMaxPaletteIndex);

  if (   ( pbBits = (PBYTE)MyMalloc( BitsLen ) )
      && ( BmpInfo = (PBITMAPINFO2)MyMalloc( BmpInfoLen ) ) ) {
     LONG lScanRead;
     HBITMAP  hbmpOld;

     // Must have bitmap in memory device context to change it
     hbmpOld = GpiSetBitmap( UCMData->hpsMem, pUCMItem->hBmp );

     /* Copy header info to new structure with room for color table */
     *((BITMAPINFOHEADER2 *)BmpInfo) = BmpHeader;
     BmpInfo->cbFix = sizeof( BITMAPINFOHEADER2 );

     /* Read bitmap and fill in the color table */
     lScanRead = GpiQueryBitmapBits( UCMData->hpsMem, 0, BmpHeader.cy, pbBits, BmpInfo );

     if ( lScanRead == BmpHeader.cy ) {
        if (UCMData->Style & UCS_CHNGBMPBG) {  // Use app-supplied background color
          int i;
          RGB2 rgbOldBg;

          rgbOldBg.bRed      = (BYTE)( (UCMData->BgBmp & 0x00FF0000L)>>16 );
          rgbOldBg.bGreen    = (BYTE)( (UCMData->BgBmp & 0x0000FF00L)>>8 );
          rgbOldBg.bBlue     = (BYTE)  (UCMData->BgBmp & 0x000000FFL);
          /* Locate all color table entries for the background bitmap color */
          /* and change them to the toolbar background color.               */
          for (i=0;i<ulMaxPaletteIndex ;i++ ) {
             if (  ( BmpInfo->argbColor[i].bRed   == rgbOldBg.bRed   )
                 &&( BmpInfo->argbColor[i].bGreen == rgbOldBg.bGreen )
                 &&( BmpInfo->argbColor[i].bBlue  == rgbOldBg.bBlue  ) ) {
                BmpInfo->argbColor[i].bRed      = (BYTE)( (UCMData->ItemBgColor & 0x00FF0000L)>>16 );
                BmpInfo->argbColor[i].bGreen    = (BYTE)( (UCMData->ItemBgColor & 0x0000FF00L)>>8 );
                BmpInfo->argbColor[i].bBlue     = (BYTE)  (UCMData->ItemBgColor & 0x000000FFL);
                BmpInfo->argbColor[i].fcOptions = 0;
             } // endif
          } // endfor

        } // if UCS_CHNGBMPBG style

        else { // Must be AUTO color mapping style
          ULONG BgColorIndex;

          // Get first pixel value which will point to the color entry for the background
          switch (BmpHeader.cBitCount) {
            case 1:  // Monochrome (1-bit color index, MSB of 1st byte is 1st pixel)
              BgColorIndex = *pbBits >> 7;
              break;
            case 4:  // 16-color (1/2 byte color index, upper nibble is 1st pixel)
              BgColorIndex = *pbBits >> 4;
              break;
            case 8:  // 256-color (1 byte color index)
              BgColorIndex = *pbBits;
              break;
          }
          // Modify the color table with toolbar background color
          BmpInfo->argbColor[BgColorIndex].bRed      = (BYTE)( (UCMData->ItemBgColor & 0x00FF0000L)>>16 );
          BmpInfo->argbColor[BgColorIndex].bGreen    = (BYTE)( (UCMData->ItemBgColor & 0x0000FF00L)>>8 );
          BmpInfo->argbColor[BgColorIndex].bBlue     = (BYTE)  (UCMData->ItemBgColor & 0x000000FFL);
          BmpInfo->argbColor[BgColorIndex].fcOptions = 0;
        } // AUTO style

        /* Update the bitmap with new color table */
        GpiSetBitmapBits( UCMData->hpsMem, 0, lScanRead, pbBits, BmpInfo );

     } // endif

     GpiSetBitmap( UCMData->hpsMem, hbmpOld ); // Deselect from memory device

  } // endif

  if ( pbBits )       { MyFree( pbBits ); }
  if ( BmpInfo ) { MyFree( BmpInfo );  }

  return;
}

//----------------------------------------------------------------------------
// UCMenu3DFrame : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// :pfunction res=&IDF_3DFRAM. name='UCMenu3DFrame' text='Draw a 3D frame'.
// This function draws a 3D frame
// :syntax name='UCMenu3DFrame' params='hps, rcl, hilited' return='-' .
// :fparams.
// :fparam name='hps' type='HPS' io='input' .
// HPS where we draw
// :fparam name='rcl' type='PRECTL' io='input' .
// Upper right exclusive rectangle of the frame
// :fparam name='hilited' type='USHORT' io='input'.
// Type of the frame&colon.
// :dl compact.
// :dt.<>0
// :dd.Hilited item
// :dt.0
// :dd.Non hilited item
// :edl.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenu3DFrame(HPS hps, PRECTL rcl, USHORT hilited)
{
#if 0
   POINTL pt;

   pt.x = rcl->xLeft;
   pt.y = rcl->yBottom ;
   GpiMove(hps, &pt);
   pt.x  = rcl->xRight - 1;
   GpiSetColor(hps, hilited?SYSCLR_BUTTONLIGHT:SYSCLR_BUTTONDARK);
   GpiLine(hps, &pt);
   pt.y  = rcl->yTop - 1;
   GpiLine(hps, &pt);
   pt.x = rcl->xLeft;
   GpiSetColor(hps,  hilited?SYSCLR_BUTTONDARK:SYSCLR_BUTTONLIGHT);
   GpiLine(hps, &pt);
   pt.y = rcl->yBottom;
   GpiLine(hps, &pt);
#endif
   //Simpler, but undocumented PM way to draw 3D borders...
   #define DB_RAISED    0x0400
   #define DB_DEPRESSED 0x0800
   WinDrawBorder( hps, rcl, 1, 1, 0, 0, ( hilited ? DB_DEPRESSED : DB_RAISED ) );
}

//----------------------------------------------------------------------------
// UCMenuMakeTemplate :
//----------------------------------------------------------------------------
// :function res=&IDF_MAKETMP. name='UCMenuMakeTemplate' text='Builds a menu template'.
// This function builds the menu template associated with a specified ucmenu.
// :syntax name='UCMenuMakeTemplate' params='hwndUCMenu, pBufLen' return='pBuffer' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pBufLen' type='PULONG' io='output' .
// Pointer to the ucmenu template buffer length.
// :freturns.
// :fparam name='pBuffer' type='PVOID' io='return'.
// Pointer to the template (NULL if error), has to be freed by the caller with UCMenuFree.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
PVOID APIENTRY  UCMenuMakeTemplate(HWND hwndUCMenu, PULONG pBufLen)
{
   PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwndUCMenu, QWL_UCMDATA );
   if ( UCMData && UCMData->hwndMenu ) {
      HWND hwndMenu = UCMData->hwndMenu;
      ULONG ulLen   = UCMenuTemplateLen( hwndMenu ) + 8;
      PVOID pBuf    = MyMalloc( ulLen ); // 8 is the size of the signature and version number

      if ( pBuf ) {
         *( (PULONG)pBuf ) = UCMTMPLSIG;
         *( (PULONG)( (PBYTE)pBuf + sizeof( ULONG ) ) ) = UCMTMPLVERSION;

         UCMenuMakeTemplate2( hwndMenu, (PVOID)( (PBYTE)pBuf + 8 ), 0 );
      } else {
         ulLen = 0;
      } // endif

      *pBufLen = ulLen;
      return pBuf;
   } else {
      *pBufLen = 0;
      return NULL;
   } // endif
}

//----------------------------------------------------------------------------
// UCMenuTemplateLen :
//----------------------------------------------------------------------------
// :pfunction res=&IDF_TMPLEN. name='UCMenuTemplateLen' text='Calculates the length of a template'.
// This function returns the length needed for the template associated to a ucmenu.
// :syntax name='UCMenuTemplateLen' params='hwndMenu' return='ulLen' .
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :freturns.
// :fparam name='BufLen' type='ULONG' io='return'.
// Length neededfor the template
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
ULONG  _Optlink UCMenuTemplateLen( HWND hwndMenu )
{
  MENUTEMPLATE  Mt;
  PMENUTEMPLATE pMt = &Mt;
  PMTI          pMti;
  MENUITEM      Mi;
  USHORT        NbOfItems = (SHORT)WinSendMsg(hwndMenu, MM_QUERYITEMCOUNT, NULL, NULL);
  USHORT        i, itemID;
  SHORT         sLen = 0;

  pMti = (PMTI)&(pMt->c);

  for (i=0 ; i<NbOfItems ; i++ ) {
    itemID = (USHORT)WinSendMsg(hwndMenu,
                                MM_ITEMIDFROMPOSITION,
                                MPFROMSHORT(i),
                                NULL);
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(itemID, FALSE),
               MPFROMP(&Mi));


    if (Mi.afStyle & MIS_TEXT || Mi.afStyle & MIS_BITMAP) {
      sLen = (SHORT)WinSendMsg(hwndMenu,
                               MM_QUERYITEMTEXTLENGTH,
                               MPFROMSHORT(Mi.id),
                               NULL);
      sLen++;
    } else {
      if (Mi.afStyle & MIS_OWNERDRAW) {
        sLen = 5; // we have the 5 delimiters no matter what
        if (ITEM(&Mi, pszText)) {
          sLen += strlen(ITEM(&Mi, pszText));
        } /* endif */

        if (ITEM(&Mi, pszBmp)) {
          sLen += strlen(ITEM(&Mi, pszBmp));
        } /* endif */

        if (ITEM(&Mi, pszAction)) {
          sLen += strlen((PSZ)ITEM(&Mi, pszAction));
        } /* endif */

        if (ITEM(&Mi, pszParameters)) {
          sLen += strlen((PSZ)ITEM(&Mi, pszParameters));
        } /* endif */

        if (ITEM(&Mi, pszData)) {
          sLen += strlen((PSZ)ITEM(&Mi, pszData));
        } /* endif */

        sLen++;
      } else {
        sLen = 0;
      } /* endif */
    } /* endif */

    pMti = (PMTI)((ULONG)pMti->c + sLen);
    if (Mi.afStyle & MIS_SUBMENU) {
      pMti = (PMTI)( (ULONG)pMti + UCMenuTemplateLen( Mi.hwndSubMenu ) );
    } /* endif */
  } /* endfor */

  return (ULONG)pMti - (ULONG)pMt;
}

//----------------------------------------------------------------------------
// UCMenuMakeTemplate2 :
//----------------------------------------------------------------------------
// :pfunction res=&IDF_MAKETMP2. name='UCMenuMakeTemplate2' text='Builds a menu template'.
// This function builds the menu template associated with a specified menu.
// :syntax name='UCMenuMakeTemplate2' params='hwndMenu, pBuffer' return='pEndBuffer' .
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='pBuffer' type='PVOID' io='input' .
// Pointer to the menu template buffer
// :fparam name='MenuAttr' type='SHORT' io='input'.
// MIA_SUBMENU if processing a submenu, else 0.
// :freturns.
// :fparam name='pEndBuffer' type='PVOID' io='return'.
// Pointer to the end of the template, plus one.
// :efparams.
// :remarks.
// pBuffer has to be allocated before, and freed after this call
// :related.
// :epfunction.
//----------------------------------------------------------------------------
//(MAM) Added MenuAttr parameter to detect recursive submenu processing.
PVOID _Optlink  UCMenuMakeTemplate2(HWND hwndMenu, PVOID pBuf, USHORT MenuAttr)
{
  PMENUTEMPLATE pMt = (PMENUTEMPLATE)pBuf;
  PMTI          pMti;
  MENUITEM      Mi;
  USHORT        NbOfItems = (SHORT)WinSendMsg(hwndMenu, MM_QUERYITEMCOUNT, NULL, NULL);
  USHORT        i, itemID;
  SHORT         sLen = 0, pszLen;
  UCHAR ucDelim = '\t';

  pMt->Version=0;
  pMt->CodePage=0x01B5;
  pMt->Offset=4;
  pMt->Count=NbOfItems;
  pMti = (PMTI)&(pMt->c);

  for (i=0 ; i<NbOfItems ; i++ ) {
    itemID = (USHORT)WinSendMsg(hwndMenu,
                                MM_ITEMIDFROMPOSITION,
                                MPFROMSHORT(i),
                                NULL);
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(itemID, FALSE),
               MPFROMP(&Mi));

    pMti->afStyle     = Mi.afStyle & (USHORT)~MIS_OWNERDRAW;
    if (Mi.afStyle & MIS_OWNERDRAW) { // transform MIS_OWNERDRAW into MIS_TEXT !!
      pMti->afStyle  |= MIS_TEXT;
    } /* endif */

    /* Remove most attributes since app will need to reset them when menu is loaded */
    /* according to (then current) application state.                               */
    pMti->afAttribute = Mi.afAttribute & (USHORT)~MIA_CHECKED;
    pMti->afAttribute = Mi.afAttribute & (USHORT)~MIA_DISABLED;
    pMti->afAttribute = Mi.afAttribute & (USHORT)~MIA_HILITED;

    pMti->idItem      = Mi.id;

    if (Mi.afStyle & MIS_TEXT || Mi.afStyle & MIS_BITMAP) {
      sLen = (SHORT)WinSendMsg(hwndMenu,
                               MM_QUERYITEMTEXTLENGTH,
                               MPFROMSHORT(Mi.id),
                               NULL);
      WinSendMsg(hwndMenu,
                 MM_QUERYITEMTEXT,
                 MPFROM2SHORT(Mi.id, ++sLen),
                 MPFROMP(pMti->c));
    } else {
      if (Mi.afStyle & MIS_OWNERDRAW) {
        sLen = 0;
        pMti->c[0]='\0';

#if 0
        if (ITEM(&Mi, pszText)) {
          sLen = strlen(ITEM(&Mi, pszText));
          memcpy(pMti->c, ITEM(&Mi, pszText), sLen);
        } /* endif */
#endif

        if (ITEM(&Mi, pszText)) {
          pszLen = strlen(ITEM(&Mi, pszText));
          pMti->c[sLen]=ucDelim;
          memcpy(&pMti->c[++sLen], ITEM(&Mi, pszText), pszLen);
          sLen += pszLen;
        } else {
          pMti->c[sLen]=ucDelim;
          sLen++;
        } /* endif */

        if (ITEM(&Mi, pszBmp)) {
          pszLen = strlen(ITEM(&Mi, pszBmp));
          pMti->c[sLen]=ucDelim;
          memcpy(&pMti->c[++sLen], ITEM(&Mi, pszBmp), pszLen);
          sLen += pszLen;
        } else {
          pMti->c[sLen]=ucDelim;
          sLen++;
        } /* endif */

        if (ITEM(&Mi, pszAction)) {
          pszLen = strlen((PSZ)ITEM(&Mi, pszAction));
          pMti->c[sLen]=ucDelim;
          memcpy(&pMti->c[++sLen], ITEM(&Mi, pszAction), pszLen);
          sLen += pszLen;
        } else {
          pMti->c[sLen]=ucDelim;
          sLen++;
        } /* endif */

        if (ITEM(&Mi, pszParameters)) {
          pszLen = strlen((PSZ)ITEM(&Mi, pszParameters));
          pMti->c[sLen]=ucDelim;
          memcpy(&pMti->c[++sLen], ITEM(&Mi, pszParameters), pszLen);
          sLen += pszLen;
        } else {
          pMti->c[sLen]=ucDelim;
          sLen++;
        } /* endif */

        if (ITEM(&Mi, pszData)) {
          pszLen = strlen((PSZ)ITEM(&Mi, pszData));
          pMti->c[sLen]=ucDelim;
          memcpy(&pMti->c[++sLen], ITEM(&Mi, pszData), pszLen);
          sLen += pszLen;
        } else {
          pMti->c[sLen]=ucDelim;
          sLen++;
        } /* endif */

        pMti->c[sLen]='\0';
        sLen++;
      } else {
        pMti->c[0] = '\0';
        sLen       = 0;
      } /* endif */
    } /* endif */

    pMti = (PMTI)((ULONG)pMti->c + sLen);
    if (Mi.afStyle & MIS_SUBMENU) {
      pMti = (PMTI)UCMenuMakeTemplate2(Mi.hwndSubMenu, (PVOID)pMti, MIS_SUBMENU);
    } /* endif */
  } /* endfor */

  pMt->Length = (ULONG)pMti - (ULONG)pMt;
  return (PVOID)pMti;
}
//----------------------------------------------------------------------------
// UCMenuSaveTemplate :
//----------------------------------------------------------------------------
// :function res=&IDF_SAVETMP. name='UCMenuSaveTemplate' text='Saves a menu template'.
// This function builds and saves a ucmenu template.
// :syntax name='UCMenuSaveTemplate' params='hwndUCMenu, pszFileName' return='bRc' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :freturns.
// :fparam name='bRc' type='BOOL' io='return'.
// FALSE if an error occured.
// :efparams.
// :remarks.
// :related.
// UCMenuMakeTemplate
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY  UCMenuSaveTemplate(HWND hwndUCMenu, PSZ pszFileName)
{
  PVOID  pBuffer;
  USHORT size;
  BOOL   bRc = FALSE;
  ULONG  ulBufLen;


  pBuffer = UCMenuMakeTemplate(hwndUCMenu, &ulBufLen);
  if (pBuffer) {
    size = (USHORT)ulBufLen;
    if (size) {
      ULONG ulAction, ulWritten=0;
      HFILE hFile = NULLHANDLE;

      if (DosOpen(pszFileName,
                  &hFile,
                  &ulAction,
                  0,
                  FILE_NORMAL,
                  OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                  OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE|
                  OPEN_FLAGS_SEQUENTIAL | OPEN_FLAGS_NO_CACHE ,
                  0L) == 0 ) {
        DosWrite(hFile, pBuffer, size, &ulWritten);
        DosClose(hFile);
        if (ulWritten == size)
          bRc = TRUE;
      } /* endif */
    } /* endif */
    MyFree(pBuffer);
  } /* endif */

  return (bRc);
}


//----------------------------------------------------------------------------
// UCMenuLoadTemplate :
//----------------------------------------------------------------------------
// :function res=&IDF_LOADTMP. name='UCMenuLoadTemplate' text='Loads a menu template'.
// This function loads a menu template from a file.
// :syntax name='UCMenuLoadTemplate' params='pszFileName, pBufLen' return='pBuffer' .
// :fparams.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :fparam name='pBufLen' type='PULONG' io='output' .
// Pointer to the length of the allocated buffer.
// :freturns.
// :fparam name='pBuffer' type='PVOID' io='input' .
// Pointer to a buffer (NULL if error).
// :hp2.Note&colon.:ehp2. The buffer must be freed by the caller using the UCMenuFree() function:enote.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
PVOID APIENTRY  UCMenuLoadTemplate(PSZ pszFileName, PULONG pBufLen)
{
  PVOID       pBuffer;
  ULONG       ulAction=0, ulRead;
  FILESTATUS3 flstInfo;
  HFILE       hFile= NULLHANDLE;
  APIRET      Error;

  Error = DosOpen(pszFileName,
                  &hFile,
                  &ulAction,
                  0,
                  FILE_NORMAL,
                  OPEN_ACTION_OPEN_IF_EXISTS,
                  OPEN_ACCESS_READONLY | OPEN_SHARE_DENYREADWRITE,
                  0L);
  if (Error) {
    pBuffer = NULL;
  } else {
    if (DosQueryFileInfo(hFile,
                         1,
                         (PBYTE)&flstInfo,
                         sizeof(flstInfo))) {
      DosClose(hFile);
      pBuffer = NULL;
    } else {
      pBuffer = MyMalloc(flstInfo.cbFile);
      if (!pBuffer) {
        DosClose(hFile);
        *pBufLen = 0;
      } else {
        *pBufLen = flstInfo.cbFile;
        DosRead(hFile,
                pBuffer,
                flstInfo.cbFile,
                &ulRead);
        DosClose(hFile);
      } /* endif */
    } /* endif */
  } /* endif */

  return (pBuffer);
}

//----------------------------------------------------------------------------
// UCMenuSaveTemplateIni :
//----------------------------------------------------------------------------
// :function res=&IDF_SAVETMPINI. name='UCMenuSaveTemplateIni' text='Saves a menu template'.
// This function builds and saves a ucmenu template in an ini file.
// :syntax name='UCMenuSaveTemplateIni' params='hwndUCMenu, pszFileName, pszKeyName' return='bRc' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :fparam name='pszKeyName' type='PSZ' io='input' .
// Template name (NULL-terminated string)
// :freturns.
// :fparam name='bRc' type='BOOL' io='return'.
// FALSE if an error occured.
// :efparams.
// :remarks.
// :related.
// UCMenuMakeTemplate
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY  UCMenuSaveTemplateIni(HWND hwndUCMenu, PSZ pszFileName,
                                  PSZ pszKeyName)
{
  PVOID  pBuffer;
  BOOL   bRc = FALSE;
  ULONG  ulBufLen;
  HINI   hIni;
  //HWND   hwndMenu = ((PUCMDATA)WinQueryWindowULong(hwndUCMenu,QWL_UCMDATA))->hwndMenu;

  pBuffer = UCMenuMakeTemplate(hwndUCMenu, &ulBufLen);
  if (pBuffer) {
    if (ulBufLen) {
      hIni = PrfOpenProfile(WinQueryAnchorBlock(HWND_DESKTOP), pszFileName);
      if (hIni) {
         PrfWriteProfileData(hIni, UCAPPNAME, pszKeyName, pBuffer, ulBufLen);
         PrfCloseProfile(hIni);
         bRc = TRUE;
      }
    } /* endif */
    MyFree(pBuffer);
  } /* endif */

  return (bRc);
}

//----------------------------------------------------------------------------
// UCMenuLoadTemplateIni :
//----------------------------------------------------------------------------
// :function res=&IDF_LOADTMPINI. name='UCMenuLoadTemplateIni' text='Loads a menu template'.
// This function loads a menu template from an ini file.
// :syntax name='UCMenuLoadTemplateIni' params='pszFileName, pszKeyName, pBufLen' return='pBuffer' .
// :fparams.
// :fparam name='pszFileName' type='PSZ' io='input' .
// Ini File name (NULL-terminated string)
// :fparam name='pszKeyName' type='PSZ' io='input' .
// Template name (NULL-terminated string)
// :fparam name='pBufLen' type='PULONG' io='output' .
// Pointer to the length of the allocated buffer.
// :freturns.
// :fparam name='pBuffer' type='PVOID' io='input' .
// Pointer to a buffer (NULL if error).
// :hp2.Note&colon.:ehp2. The buffer must be freed by the caller using the UCMenuFree() function:enote.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
PVOID APIENTRY  UCMenuLoadTemplateIni(PSZ pszFileName, PSZ pszKeyName,
                                   PULONG pBufLen)
{
  PVOID       pBuffer=(PVOID)NULL;
  HINI        hIni;
  ULONG       ulSize;

  hIni = PrfOpenProfile(WinQueryAnchorBlock(HWND_DESKTOP), pszFileName);
  if (hIni) {
     PrfQueryProfileSize(hIni, UCAPPNAME, pszKeyName, &ulSize);
     if (ulSize) {
        pBuffer = MyMalloc(ulSize);
     }
     if (pBuffer) {
        PrfQueryProfileData(hIni, UCAPPNAME, pszKeyName, pBuffer, &ulSize);
     }
     PrfCloseProfile(hIni);
  }
  return(pBuffer);
}

//----------------------------------------------------------------------------
// UCMenuSaveStyle :
//----------------------------------------------------------------------------
// :function res=&IDF_SAVESTL. name='UCMenuSaveStyle' text='Saves a menu style'.
// This function saves the informations relative to the style of a ucmenu.
// :syntax name='UCMenuSaveStyle' params='hwndMenu, pszFileName' return='bRC' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :freturns.
// :fparam name='bRC' type='BOOL' io='return'.
// FALSE if an error occured.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY  UCMenuSaveStyle(HWND hwndUCMenu, PSZ pszFileName)
{
  PVOID  pBuffer;
  USHORT size;
  BOOL   bRC = FALSE;
  PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwndUCMenu, QWL_UCMDATA );

  pBuffer = MyMalloc(MAX_TMPSIZE);
  if (pBuffer) {
    PVOID pBufIndex = pBuffer;
    size = 0;
    *((PULONG)pBufIndex)   = UCMData->Style;
    pBufIndex = ((PULONG)pBufIndex)+1;
    size += sizeof( ULONG );
    *((PULONG)pBufIndex) = UCMData->cx;
    pBufIndex = ((PULONG)pBufIndex)+1;
    size += sizeof( ULONG );
    *((PULONG)pBufIndex) = UCMData->cy;
    pBufIndex = ((PULONG)pBufIndex)+1;
    size += sizeof( ULONG );
    *((LONG*)pBufIndex) = UCMData->BgColor;
    pBufIndex = ((LONG*)pBufIndex)+1;
    size += sizeof( LONG );
    *((LONG*)pBufIndex) = UCMData->ItemBgColor;
    pBufIndex = ((LONG*)pBufIndex)+1;
    size += sizeof( LONG );
    if (UCMData->pszFontNameSize) {
       strcpy( pBufIndex, UCMData->pszFontNameSize );
       size += 1 + strlen( UCMData->pszFontNameSize );
    } // endif
    if (size) {
      ULONG ulAction, ulWritten=0;
      HFILE hFile = NULLHANDLE;

      if (DosOpen(pszFileName,
                  &hFile,
                  &ulAction,
                  0,
                  FILE_NORMAL,
                  OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                  OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE|
                  OPEN_FLAGS_SEQUENTIAL | OPEN_FLAGS_NO_CACHE ,
                  0L) == 0 ) {
        DosWrite(hFile, pBuffer, size, &ulWritten);
        DosClose(hFile);
        if (ulWritten == size)
          bRC = TRUE;
      } /* endif */
    } /* endif */
    MyFree(pBuffer);
  } /* endif */
  return (bRC);
}


//----------------------------------------------------------------------------
// UCMenuLoadStyle :
//----------------------------------------------------------------------------
// :function res=&IDF_LOADSTL. name='UCMenuLoadStyle' text='Loads a menu style'.
// This function loads a menu style from a file into a UCMInfo ucmenu
// creation structure.
// :syntax name='UCMenuLoadStyle' params='pszFileName, pUCMInfo' return='bSuccess'.
// :fparams.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :fparam name='pUCMInfo' type='UCMINFO *' io='output' .
// Pointer to the UCMInfo structure in which to load the style
// :freturns.
// :fparam name='bSuccess' type='BOOL' io='return' .
// FALSE if an error occured.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY  UCMenuLoadStyle(PSZ pszFileName, PUCMINFO pUCMInfo)
{
  BOOL        bSuccess;
  PVOID       pBuffer;
  ULONG       ulAction=0, ulRead;
  FILESTATUS3 flstInfo;
  HFILE       hFile= NULLHANDLE;
  APIRET      Error;

  Error = DosOpen(pszFileName,
                  &hFile,
                  &ulAction,
                  0,
                  FILE_NORMAL,
                  OPEN_ACTION_OPEN_IF_EXISTS,
                  OPEN_ACCESS_READONLY | OPEN_SHARE_DENYREADWRITE,
                  0L);
  if (Error) {
    bSuccess = FALSE;
  } else {
    if (DosQueryFileInfo(hFile,
                         1,
                         (PBYTE)&flstInfo,
                         sizeof(flstInfo))) {
      DosClose(hFile);
      bSuccess = FALSE;
    } else {
      pBuffer = MyMalloc(flstInfo.cbFile);
      if (!pBuffer) {
        DosClose(hFile);
        bSuccess = FALSE;
      } else {
        DosRead(hFile,
                pBuffer,
                flstInfo.cbFile,
                &ulRead);
        DosClose(hFile);
        if ( ulRead >= ( 3*sizeof(ULONG) + 2*sizeof(LONG) ) ) {
           PVOID pBufIndex;
           pBufIndex = pBuffer;
           pUCMInfo->Style = *(PULONG)pBufIndex;
           pBufIndex = ((PULONG)pBufIndex)+1;
           pUCMInfo->cx = *(PULONG)pBufIndex;
           pBufIndex = ((PULONG)pBufIndex)+1;
           pUCMInfo->cy = *(PULONG)pBufIndex;
           pBufIndex = ((PULONG)pBufIndex)+1;
           pUCMInfo->BgColor = *(LONG*)pBufIndex;
           pBufIndex = ((LONG*)pBufIndex)+1;
           pUCMInfo->ItemBgColor = *(LONG*)pBufIndex;
           pBufIndex = ((LONG*)pBufIndex)+1;
           if (((PBYTE)pBufIndex-(PBYTE)pBuffer)>ulRead) {
              *((PBYTE)pBuffer+ulRead-1) = 0;
              pUCMInfo->pszFontNameSize = MyStrdup( (PSZ)pBufIndex );
           } else {
              pUCMInfo->pszFontNameSize = 0;
           } // endif
           bSuccess = TRUE;
        } else {
           bSuccess = FALSE;
        } // endif
      MyFree( pBuffer );
      } // endif
    } // endif
  } // endif

  return (bSuccess);
}

//----------------------------------------------------------------------------
// UCMenuSaveStyleIni :
//----------------------------------------------------------------------------
// :function res=&IDF_SAVESTLINI. name='UCMenuSaveStyleIni' text='Saves a menu style'.
// This function saves the informations relative to the style of a ucmenu in an ini file.
// :syntax name='UCMenuSaveStyleIni' params='hwndMenu, pszFileName, pszKeyName' return='bRC' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :fparam name='pszKeyName' type='PSZ' io='input' .
// Style name (NULL-terminated string)
// :freturns.
// :fparam name='bRC' type='BOOL' io='return'.
// FALSE if an error occured.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY  UCMenuSaveStyleIni(HWND hwndUCMenu, PSZ pszFileName,
                               PSZ pszKeyName)
{
  PVOID  pBuffer;
  USHORT size;
  BOOL   bRC = FALSE;
  PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwndUCMenu, QWL_UCMDATA );

  pBuffer = MyMalloc(MAX_TMPSIZE);
  if (pBuffer) {
    PVOID pBufIndex = pBuffer;
    size = 0;
    *((PULONG)pBufIndex)   = UCMData->Style;
    pBufIndex = ((PULONG)pBufIndex)+1;
    size += sizeof( ULONG );
    *((PULONG)pBufIndex) = UCMData->cx;
    pBufIndex = ((PULONG)pBufIndex)+1;
    size += sizeof( ULONG );
    *((PULONG)pBufIndex) = UCMData->cy;
    pBufIndex = ((PULONG)pBufIndex)+1;
    size += sizeof( ULONG );
    *((LONG*)pBufIndex) = UCMData->BgColor;
    pBufIndex = ((LONG*)pBufIndex)+1;
    size += sizeof( LONG );
    *((LONG*)pBufIndex) = UCMData->ItemBgColor;
    pBufIndex = ((LONG*)pBufIndex)+1;
    size += sizeof( LONG );
    if (UCMData->pszFontNameSize) {
       strcpy( pBufIndex, UCMData->pszFontNameSize );
       size += 1 + strlen( UCMData->pszFontNameSize );
    } // endif

    if (size) {
       HINI    hIni;
       hIni = PrfOpenProfile(WinQueryAnchorBlock(HWND_DESKTOP), pszFileName);
       if (hIni) {
          PrfWriteProfileData(hIni, UCAPPNAME, pszKeyName, pBuffer, size);
          PrfCloseProfile(hIni);
       }
    }
    MyFree(pBuffer);
  } /* endif */
  return (bRC);
}


//----------------------------------------------------------------------------
// UCMenuLoadStyleIni :
//----------------------------------------------------------------------------
// :function res=&IDF_LOADSTLINI. name='UCMenuLoadStyleIni' text='Loads a menu style'.
// This function loads a menu style from an ini file into a UCMInfo ucmenu
// creation structure.
// :syntax name='UCMenuLoadStyleIni' params='pszFileName, pszKeyName, pUCMInfo' return='bSuccess'.
// :fparams.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name (NULL-terminated string)
// :fparam name='pszKeyName' type='PSZ' io='input' .
// Style name (NULL-terminated string)
// :fparam name='pUCMInfo' type='UCMINFO *' io='output' .
// Pointer to the UCMInfo structure in which to load the style
// :freturns.
// :fparam name='bSuccess' type='BOOL' io='return' .
// FALSE if an error occured.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY  UCMenuLoadStyleIni(PSZ pszFileName, PSZ pszKeyName,
                                 PUCMINFO pUCMInfo)
{
  BOOL        bSuccess=FALSE;
  PVOID       pBuffer;
  HINI        hIni;
  ULONG       ulSize;

  hIni = PrfOpenProfile(WinQueryAnchorBlock(HWND_DESKTOP), pszFileName);
  if (hIni) {
     PrfQueryProfileSize(hIni, UCAPPNAME, pszKeyName, &ulSize);
     if (ulSize) {
       pBuffer = MyMalloc(ulSize);
       if (pBuffer) {
         PrfQueryProfileData(hIni, UCAPPNAME, pszKeyName, pBuffer, &ulSize);
         if ( ulSize >= ( 3*sizeof(ULONG) + 2*sizeof(LONG) ) ) {
            PVOID pBufIndex;
            pBufIndex = pBuffer;
            pUCMInfo->Style = *(PULONG)pBufIndex;
            pBufIndex = ((PULONG)pBufIndex)+1;
            pUCMInfo->cx = *(PULONG)pBufIndex;
            pBufIndex = ((PULONG)pBufIndex)+1;
            pUCMInfo->cy = *(PULONG)pBufIndex;
            pBufIndex = ((PULONG)pBufIndex)+1;
            pUCMInfo->BgColor = *(LONG*)pBufIndex;
            pBufIndex = ((LONG*)pBufIndex)+1;
            pUCMInfo->ItemBgColor = *(LONG*)pBufIndex;
            pBufIndex = ((LONG*)pBufIndex)+1;
            if (((PBYTE)pBufIndex-(PBYTE)pBuffer)>ulSize) {
               *((PBYTE)pBuffer+ulSize-1) = 0;
               pUCMInfo->pszFontNameSize = MyStrdup( (PSZ)pBufIndex );
            } else {
               pUCMInfo->pszFontNameSize = 0;
            } // endif
            bSuccess = TRUE;
         } // endif
         MyFree( pBuffer );
       } //endif
     } //endif
     PrfCloseProfile(hIni);
  } //endif
  return(bSuccess);

}

//----------------------------------------------------------------------------
// UCMenuLoadMenuData
//----------------------------------------------------------------------------
// :pfunction res=&IDF_LOADMENU. name='UCMenuLoadMenuData' text='Loads the menu data'.
// This function loads the data associated with the OWNERDRAW items of a menu.
// :syntax name='UCMenuLoadMenuData' params='hwndMenu, hModule, UCMData, ulVersion, hwndUCM ' return='-' .
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='UCMData' type='PUCMDATA' io='input'
// Pointer to the UCMDATA structure
// :fparam name='ulVersion' type='ULONG' io='input'
// template version
// :fparam name='hwndUCM' type='HWND' io='input' .
// UCMenu window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing.
// :efparams.
// :remarks.
// This function parses the whole menu (including submenus). It creates ownerdrawn
// items from special text items.
// :p.
// The text field of such items must have the following format &colon.
// "&lbrk.Text&rbrk.#BitmapID&lbrk.#Action&rbrk.&lbrk.#Data&rbrk.".
// :dl compact.
// :dt.:hp2.Text:ehp2.
// :dd.The text displayed in the bitmap
// :dt.:hp2.BitmapID:ehp2.
// :dd.Bitmap identifier or file name
// :dt.:hp2.Action:ehp2.
// :dd.Some text associated with the item , for example the name of a macro.
// :dt.:hp2.Data:ehp2.
// :dd.Information about the action associated with the item , for example the name of a macro.
// :edl.
// :p.
// The style of these items is replaced by MIS_OWNERDRAW. The item handle contains
// a pointer to an :link reftype=hd res=&IDT_ITEMD..UCMITEM data structure:elink.
// :p.
// Any MIS_BREAK style not for a submenu item is removed.
// :hp2.Note&colon.:ehp2. This function is automatically called during the creation of a UCMenu.
// :enote.
// :xamples.
// Definition of the menu in a resource file &colon.
// :xmp.
// BITMAP 2000 BITMAP1.BMP
//  ...
// MENUITEM    "#Item 1#2000#Macro 1",        IDM_MAC1,     MIS_TEXT
// MENUITEM    "#Item 2#bitmap2.bmp#Macro 2", IDM_MAC2,     MIS_TEXT
//  ...
// :exmp.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink  UCMenuLoadMenuData(HWND hwndMenu, PUCMDATA UCMData, ULONG ulVersion, HWND hwndUCM )
{
  MENUITEM mi;
  SHORT    sIndex, sIndexBis, sOtherIndex, ItemID, NewID, NbOfItems, sItemTextLen;
  PSZ      ItemText, ItemText2;
  PSZ      pszBmpHandle=0, pszText=0, pszAction=0, pszParameters=0, pszBmp=0, pszAct = 0;
  PSZ      pszData=0, pszD = 0, pszPar = 0;
  LONG     pszLen;
  UCHAR    ucDelim = '\t';

  WinSetWindowULong( hwndMenu, QWL_USER, (ULONG) UCMData );


  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the Number of menu items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  NbOfItems = (SHORT)WinSendMsg(hwndMenu,
                                MM_QUERYITEMCOUNT,
                                (MPARAM)0,
                                (MPARAM)0);

  for (sIndex=0 ; sIndex<NbOfItems ; sIndex++) {

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item ID and structure ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    ItemID = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(sIndex),
                               (MPARAM)0);

    sOtherIndex = sIndex;
    for ( sIndexBis = sIndex + 1; sIndexBis < NbOfItems; sIndexBis++ ) {
       NewID = (SHORT)WinSendMsg( hwndMenu,
                                  MM_ITEMIDFROMPOSITION,
                                  MPFROMSHORT(sIndexBis),
                                  (MPARAM)0);
       if ( NewID == ItemID ) {
          sOtherIndex = sIndexBis;
       } /* endif */
    } /* endfor */
    if ( sOtherIndex != sIndex ) {
       // Another item has the same ID, so get an unused one
       // We assume here that when 2 items have the same ID,
       // MM_QUERYITEM  amd MM_REMOVEITEM use the one
       // in the first position
       memset( &mi, 0, sizeof( MENUITEM ) );
       WinSendMsg(hwndMenu,
                  MM_QUERYITEM,
                  MPFROM2SHORT(ItemID,FALSE),
                  MPFROMP(&mi));
       NewID = UCMenuGetNewID( hwndMenu, MIT_NONE, UCMData );
       ItemText2 = 0;
       sItemTextLen = (SHORT) WinSendMsg( hwndMenu,
                                          MM_QUERYITEMTEXTLENGTH,
                                          MPFROMSHORT(ItemID ),
                                          (MPARAM)0 );
       if ( sItemTextLen ){
          ItemText2 = MyMalloc( ++sItemTextLen );
          if ( ItemText2 ) {
             WinSendMsg( hwndMenu,
                         MM_QUERYITEMTEXT,
                         MPFROM2SHORT( ItemID, sItemTextLen ),
                         MPFROMP( ItemText2 ) );
          } /* endif */
       } /* endif */
       if ( ItemText2 ) {
          ItemText = ItemText2;
       } else {
          ItemText = "";
       } /* endif */
       WinSendMsg(hwndMenu,
                  MM_REMOVEITEM,
                  MPFROM2SHORT(ItemID,FALSE),
                  (MPARAM)0 );
       mi.id = NewID;
       if ( mi.hItem ){
          ITEM( &mi, usId ) = NewID;
       } /* endif */
       ItemID = NewID;
       WinSendMsg( hwndMenu,
                   MM_INSERTITEM,
                   MPFROMP( &mi ),
                   MPFROMP( ItemText ) );
       if ( ItemText2 ){
          MyFree( ItemText2 );
       } /* endif */
    } /* endif */

    memset( &mi, 0, sizeof( MENUITEM ) );
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(ItemID,FALSE),
               MPFROMP(&mi));

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ If it's a Submenu, do a recursive call with hwndSubMenu ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    if (mi.hwndSubMenu){
       PFNWP pFnwp;
       UCMenuLoadMenuData(mi.hwndSubMenu, UCMData, ulVersion, hwndUCM );
       if ( ( pFnwp =(PFNWP)WinQueryWindowPtr( mi.hwndSubMenu, QWP_PFNWP ) ) != SubmenuWndProc ){
          UCMData->OldSubMenuProc = pFnwp;
          UCMData->OldSubMenuProc = (PFNWP)WinSubclassWindow( mi.hwndSubMenu, SubmenuWndProc );
       } // endif
    }

    // (MAM) same for SPACER and non-SPACER, so moved here to save code.
    // If both MIS_SPACER and MIS_TEXT specified, SPACER is used.

    mi.afStyle |= (USHORT)  MIS_OWNERDRAW ;
    mi.afStyle &= (USHORT) ~MIS_TEXT;
    mi.afStyle &= (USHORT) ~MIS_BREAK;  //(MAM) Don't allow BREAK on any item

    if (mi.afStyle & MIS_SPACER) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ It's a SPACER item                                      ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

       mi.hItem = (LONG)MyMalloc(sizeof(UCMITEM));

       if (mi.hItem) {
          memset( (VOID *) mi.hItem, '\0', sizeof(UCMITEM) );
       } // endif mi.hItem != 0


      WinSendMsg(hwndMenu,
                 MM_SETITEM,
                 MPFROM2SHORT(0,FALSE),
                 MPFROMP(&mi));

    } else {

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Assume it is a MIS_TEXT item                            ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      ItemText2 = 0;
      sItemTextLen = (SHORT) WinSendMsg( hwndMenu,
                                         MM_QUERYITEMTEXTLENGTH,
                                         MPFROMSHORT(ItemID ),
                                         (MPARAM)0 );
      if ( sItemTextLen ){
         ItemText2 = MyMalloc( ++sItemTextLen );
         if ( ItemText2 ) {
            WinSendMsg( hwndMenu,
                        MM_QUERYITEMTEXT,
                        MPFROM2SHORT( ItemID, sItemTextLen ),
                        MPFROMP( ItemText2 ) );
         } /* endif */
      } /* endif */
      if ( ItemText2 ){
         ItemText = ItemText2;
      } else {
         ItemText = "";
      } /* endif */

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ The format is the following : "#Text#Bitmap#Action#Parameters#Data"³
        ³ Text is optional, Bitmap is either a number (bitmap ID) or a       ³
        ³ string (file name), Action, Parameters and Data are string         ³
        ³ The delimiter (here # is given by the first character of the string³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

      if ( ulVersion == UCMTMPLVERSION ){
         ucDelim = ItemText[0];
         pszBmpHandle = strchr(&ItemText[1], ucDelim);
      } else {
         ucDelim = '#';
         pszBmpHandle = strchr(&ItemText[0], ucDelim);
      } // endif


      if (pszBmpHandle) {

        pszAction = strchr(&pszBmpHandle[1], ucDelim);

        if(pszAction) {
          if ( ulVersion == UCMTMPLVERSION ){
              pszParameters   = (PSZ) strchr((PSZ)(pszAction+1), ucDelim);
              if ( pszParameters ){
                 pszData   = (PSZ) strchr((PSZ)(pszParameters+1), ucDelim);
              } // endif
           } else {
              pszParameters = NULL;
              pszData   = (PSZ) strchr((PSZ)(pszAction+1), ucDelim);
           } // endif
        }

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Get the text (if any) ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if ( ulVersion == UCMTMPLVERSION ){
           pszLen = (LONG)pszBmpHandle - (LONG)(&ItemText[1]);
        } else {
           pszLen = (LONG)pszBmpHandle - (LONG)(&ItemText[0]);
        } // endif
        if (pszLen>0) {
          PSZ StrPtr;
          pszText = (PSZ)MyMalloc(pszLen + 1);
          if ( ulVersion == UCMTMPLVERSION ){
             strncpy(pszText, &ItemText[1], pszLen);
          } else {
             strncpy(pszText, &ItemText[0], pszLen);
          } // endif
          pszText[pszLen] = '\0';
          if(StrPtr = strstr(pszText, "~")) {
             ULONG Index = UCMData->AccelTable->cAccel;
             //??? should following be using "Index" instead of "sIndex" which is otherwise unused?
             ULONG cmd = (ULONG) WinSendMsg(hwndMenu, MM_ITEMIDFROMPOSITION, (MPARAM)sIndex, 0L);
             AddAccelItem(UCMData, StrPtr[1], cmd);
          }
        } else {
          pszText = 0;
        } /* endif */
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Replace '#' with '\0' and get the data   ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (pszData) {
          pszData[0] = '\0';
          pszData++;
          pszD = (PSZ)MyMalloc(strlen(pszData)+1);
          strcpy(pszD, pszData);
        } else {
          pszD = NULL;
        } /* endif */

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Replace '#' with '\0' and get the params ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (pszParameters) {
          pszParameters[0] = '\0';
          pszParameters++;
          pszPar = (PSZ)MyMalloc(strlen(pszParameters)+1);
          strcpy(pszPar, pszParameters);
        } else {
          pszPar = NULL;
        } /* endif */

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Replace '#' with '\0' and get the action ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (pszAction) {
          pszAction[0] = '\0';
          pszAction++;
          if ( ulVersion != UCMTMPLVERSION ){
             pszParameters = strchr( pszAction, ' ' );
             if ( pszParameters ) {
                *pszParameters = '\0';
                pszParameters++;
                pszPar = (PSZ)MyMalloc(strlen(pszParameters)+1);
                strcpy(pszPar, pszParameters);
             } // endif
          } // endif
          pszAct = (PSZ)MyMalloc(strlen(pszAction)+1);
          strcpy(pszAct, pszAction);
        } else {
          pszAct = NULL;
        } /* endif */

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Get the Bitmap text (ID or File name) ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (strlen(&pszBmpHandle[1])>0) {
           pszBmp = MyMalloc(strlen(&pszBmpHandle[1])+1);
           strcpy(pszBmp, &pszBmpHandle[1]);
        } else {
           pszBmp = 0;
        } // endif pszBmpHandle<>""
      } else {
         pszBmp = 0;
         pszAct =0;
         pszPar = 0;
         pszD = 0;
         pszText = MyMalloc( strlen(ItemText) + 1);
         strcpy( pszText, ItemText );
      } // endif pszBmpHandle

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³Create and fill the item handle structure ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      mi.hItem = (LONG)MyMalloc(sizeof(UCMITEM));

      if (mi.hItem) {
        memset((PVOID)mi.hItem, 0x00, sizeof(UCMITEM));
      //ITEM(&mi, hBmp)    = 0;
        ITEM(&mi, pszBmp)  = pszBmp;
        ITEM(&mi, pszText) = pszText;
        ITEM(&mi, pszAction) = pszAct;
        ITEM(&mi, pszParameters) = pszPar;
        ITEM(&mi, pszData) = pszD;
        } // endif mi.hItem != 0

      // -- The menu is not subclassed yet so it won't load the bitmap
      UCMenuLoadItemBmp(&mi, UCMData );

      WinSendMsg(hwndMenu,
                 MM_SETITEM,
                 MPFROM2SHORT(0,FALSE),
                 MPFROMP(&mi));
       if ( ItemText2 ){
          MyFree( ItemText2 );
       } // endif
    } // endif MIS_TEXT

  } /* endfor */

}

//----------------------------------------------------------------------------
// UCMenuNotifAll
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NOTIFALL. name='UCMenuNotifAll' text='Sends notifications about each item'.
// This function sends UCN_ADDEDITEM or UCN_DELETEDITEM about all the items in the menu
// :syntax name='UCMenuNotifAll' params='hwndUCMenu, hwndMenu, usNotif ' return='-' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='usNotification' type='USHORT' io='input'
// Notification code, UCN_ADDEDITEM or UCN_DELETEDITEM
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

VOID  _Optlink UCMenuNotifAll(PUCMDATA UCMData, HWND hwndMenu, USHORT usNotif)
{
  MENUITEM mi;
  SHORT    sIndex, ItemID, NbOfItems;


  NbOfItems = (SHORT)WinSendMsg(hwndMenu,
                                MM_QUERYITEMCOUNT,
                                (MPARAM)0,
                                (MPARAM)0);

  for (sIndex=0 ; sIndex<NbOfItems ; sIndex++) {

    ItemID = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(sIndex),
                               (MPARAM)0);


    memset( &mi, 0, sizeof( MENUITEM ) );
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(ItemID,FALSE),
               MPFROMP(&mi));

    if (mi.hwndSubMenu){
       UCMenuNotifAll(UCMData, mi.hwndSubMenu, usNotif );
    } // endif

    WinSendMsg( UCMData->hwndOwner,
                WM_CONTROL,
                MPFROM2SHORT( UCMData->UCMenuID, usNotif ),
                MPFROMSHORT( ItemID ) );

  } /* endfor */

}

//----------------------------------------------------------------------------
// UCMenuCalcItemSize : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CLCITSZ. name='UCMenuCalcItemSize' text='Calculates the scaled size of an item'.
// This function calculates the size of an item, according to the others so that they are even.
// :syntax name='UCMenuCalcItemSize' params='poi, style, hwndUCMenu, pCx, pCy' return='-' .
// :fparams.
// :fparam name='poi' type='POWNERITEM' io='input' .
// Pointer to the OWNERITEM structure of the item
// :fparam name='style' type='USHORT' io='input' .
// Style of the ucmenu
// :fparam name='hwndUCMenu' type='HWND' io='input'.
// Handle of the ucmenu
// :fparam name='pCx' type='PULONG' input='output' .
// Width of the item
// :fparam name='pCy' type='PULONG' input='output' .
// Height of the item
// :freturns.
// :fparam name='-' type='VOID' io='-' .
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

VOID _Optlink  UCMenuCalcItemSize( POWNERITEM poi, USHORT Style, HWND hwndUCMenu, ULONG * pCx, ULONG * pCy)
{
   PUCMITEM pUCMI = (PUCMITEM) poi->hItem;
   ULONG MenuStyle = WinQueryWindowULong(hwndUCMenu, QWL_STYLE);
   PUCMDATA UCMData = (PUCMDATA) WinQueryWindowULong( hwndUCMenu, QWL_UCMDATA );

   UCMenuCalcUnscaledItemSize( pUCMI, Style, hwndUCMenu, pCx, pCy);

   if ( poi->fsState & MIS_SPACER ) {
      *pCx = 8;
      *pCy = 8;
   } // endif

   if (WinQueryWindow(poi->hwnd, QW_OWNER)==hwndUCMenu) {
      // First level ucmenu item
      // Submenu ucmenu items are not scaled, since it makes no sense
      // to scale them according to the items of their parent
      if  (MenuStyle & CMS_VERT) {
         *pCx = UCMData->MaxVerticalWidth;
      } // endif CMS_VERTICAL

      if  (MenuStyle & CMS_HORZ) {
         *pCy = UCMData->MaxHorizontalHeight;
      } // endif CMS_HORIZONTAL

      if  (MenuStyle & CMS_MATRIX) {
         *pCx = UCMData->MaxVerticalWidth;
         *pCy = UCMData->MaxHorizontalHeight;
      } // endif CMS_MATRIX
   } // endif

}

//----------------------------------------------------------------------------
// UCMenuCalcUnscaledItemSize : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CLCUNSCITSZ. name='UCMenuCalcUnscaledItemSize' text='Calculates the unscaled size of an item'.
// This function calculates the size of an item
// :syntax name='UCMenuCalcUnscaledItemSize' params='pUCMI, Style, hwndUCMenu, pCx, pCy' return='-' .
// :fparams.
// :fparam name='pUCMI' type='PUCMITEM' io='input' .
// Pointer to the UCMITEM structure of the ucmenu item
// :fparam name='Style' type='USHORT' io='input' .
// Style of the ucmenu
// :fparam name='hwndUCMenu' type='HWND' io='input'.
// Handle of the ucmenu
// :fparam name='pCx' type='PULONG' input='output' .
// Width of the item
// :fparam name='pCy' type='PULONG' input='output' .
// Height of the item
// :freturns.
// :fparam name='-' type='VOID' io='-' .
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

VOID _Optlink  UCMenuCalcUnscaledItemSize( PUCMITEM pUCMI, USHORT Style, HWND hwndUCMenu,
                                           ULONG * pCx, ULONG * pCy)
{
   PUCMDATA UCMData = (PUCMDATA) WinQueryWindowULong( hwndUCMenu, QWL_UCMDATA );

   if ( Style & UCS_FORCESIZE ) {
      *pCx = UCMData->cx;
      *pCy = UCMData->cy;
   }
   else if ( pUCMI ){
      BITMAPINFOHEADER2 BmpInfo;
    //ULONG MenuStyle = WinQueryWindowULong(hwndUCMenu, QWL_STYLE);

      // By default, size the item to its bitmap
      BmpInfo.cbFix = sizeof(BITMAPINFOHEADER2);
      if (!GpiQueryBitmapInfoHeader( pUCMI->hBmp, &BmpInfo)){
         BmpInfo.cx = 0;
         BmpInfo.cy = 0;
      }
      //(MAM) Add one (all sides) for thicker checkable items.
      *pCx = SUM_ITEM_FRAME_THICK_HORZ + BmpInfo.cx +2;
      *pCy = SUM_ITEM_FRAME_THICK_VERT + BmpInfo.cy +2;
   }

   /* If text is wider, size to text (even in FORCESIZE mode) */

   if (pUCMI) {
      if ( pUCMI->pszText && !(Style & UCS_NOTEXT)) {
         ULONG TextWidth, TextHeight;

         UCMenuCalcTextSize(pUCMI, hwndUCMenu, &TextWidth, &TextHeight );
         TextWidth += SUM_ITEM_FRAME_THICK_HORZ;
         // set width to TextWidth if text larger than bmp
         if ( TextWidth > *pCx ) {
            *pCx = TextWidth;
         }
         // add the height of the text
         *pCy += TextHeight;

      } // endif pszText!=0  && !UCS_NOTEXT
   } //
}

//----------------------------------------------------------------------------
// UCMenuCalcBmpPos : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CLCBMPPOS. name='UCMenuCalcBmpPos' text='Calculates the position of the bitmap in the item'.
// This function calculates the position of the bitmap inside a ucmenu item
// :syntax name='UCMenuCalcBmpPos' params='poi, Style, pDestRect' return='-' .
// :fparams.
// :fparam name='poi' type='POWNERITEM' io='input' .
// Pointer to the OWNERITEM structure of the ucmenu item
// :fparam name='Style' type='USHORT' io='input' .
// Style of the ucmenu
// :fparam name='aptlPoints' type='POINTL[4]' io='output'.
// Destination and source rectangles of the bitmap (upper right exclusive )
// :freturns.
// :fparam name='-' type='VOID' io='-' .
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink  UCMenuCalcBmpPos( POWNERITEM poi, HWND hwndUCMenu, USHORT Style, POINTL aptlPoints[4], PUCMDATA UCMData)
{
   LONG    ItemCxForBmp ;
   LONG    ItemCyForBmp ;
   ULONG   TextWidth    = 0;
   ULONG   TextHeight   = 0;
   PUCMITEM pUCMI = (PUCMITEM) poi->hItem;

   BITMAPINFOHEADER2 BmpInfo;
   POINTL  ImageSize;

   if ( !pUCMI ){
      return;
   } // endif

   /* Get natural bitmap size */

   BmpInfo.cbFix = sizeof(BITMAPINFOHEADER2);
   if (!GpiQueryBitmapInfoHeader( ITEM( poi, hBmp ), &BmpInfo)){
      BmpInfo.cx = 0;
      BmpInfo.cy = 0;
   }

   /* Determine image size to be viewed */

   if (Style & UCS_FORCESIZE) {  // Size of bitmap image is fixed
     ImageSize.x = UCMData->cx;
     ImageSize.y = UCMData->cy;
   }
   else {                        // Use natural bitmap size
     ImageSize.x = BmpInfo.cx;
     ImageSize.y = BmpInfo.cy;
   }

   /* Query the size of the text */

   if ( ITEM( poi, pszText ) && !(Style&UCS_NOTEXT)) {
      UCMenuCalcTextSize( pUCMI, hwndUCMenu, &TextWidth, &TextHeight );
   }

   ItemCxForBmp =  poi->rclItem.xRight - poi->rclItem.xLeft;
   ItemCxForBmp -= SUM_ITEM_FRAME_THICK_HORZ;
   ItemCyForBmp =  poi->rclItem.yTop - poi->rclItem.yBottom;
   ItemCyForBmp -= SUM_ITEM_FRAME_THICK_VERT;

   // We won't have the full item to draw the bmp
   ItemCyForBmp -= TextHeight;

   if ( ItemCxForBmp < 0 ) { ItemCxForBmp = 0; }
   if ( ItemCyForBmp < 0 ) { ItemCyForBmp = 0; }

   aptlPoints[0].x  = poi->rclItem.xLeft;
   aptlPoints[0].x  += ITEM_FRAME_THICK_LEFT; // do not draw over the frame

   /* If image is smaller than available space then center it */
   /* by setting target rectangle points in [0],[1].          */

   if ( ImageSize.x <= ItemCxForBmp ) {
      aptlPoints[0].x += (ItemCxForBmp - ImageSize.x)/2;
      aptlPoints[1].x = aptlPoints[0].x  + ImageSize.x - 1;
   } else {
      aptlPoints[1].x  = poi->rclItem.xRight - ITEM_FRAME_THICK_RIGHT - 1;
   } // endif

   aptlPoints[0].y = poi->rclItem.yBottom;
   aptlPoints[0].y += ITEM_FRAME_THICK_BOTTOM ;
   aptlPoints[0].y+=TextHeight;

   if ( ImageSize.y <= ItemCyForBmp ) {
      aptlPoints[0].y += (ItemCyForBmp - ImageSize.y)/2;
      aptlPoints[1].y = aptlPoints[0].y + ImageSize.y - 1;
   } else {
      aptlPoints[1].y = poi->rclItem.yTop - ITEM_FRAME_THICK_TOP - 1;
   } // endif

   /* Source rectangle is just the original bitmap */

   aptlPoints[2].x = 0;
   aptlPoints[2].y = 0;
   aptlPoints[3].x = BmpInfo.cx;
   aptlPoints[3].y = BmpInfo.cy;

}


//----------------------------------------------------------------------------
// UCMenuCalcTextSize : internal function (no entry in the user's doc)
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CLCTXTSZ. name='UCMenuCalcTextSize' text='Calculates the size of the item text'.
// This function calculates the text size of a ucmenu item, according to its font
// :syntax name='UCMenuCalcTextSize' params='pUCMI, hwndUCMenu, pWidth, pHeight' return='-' .
// :fparams.
// :fparam name='pUCMI' type='PUCMITEM' io='input' .
// Pointer to the UCMITEM structure of the ucmenu item
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// Handle of the ucmenu
// :fparam name='pWidth' type='PULONG' io='output'.
// Width of the text
// :fparam name='pHeight' type='PULONG' io='output'.
// Height of the text
// :freturns.
// :fparam name='-' type='VOID' io='-' .
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink  UCMenuCalcTextSize(PUCMITEM pUCMI, HWND hwndUCMenu, ULONG * pWidth, ULONG * pHeight)
{
   PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong(hwndUCMenu, QWL_UCMDATA);

   if ( !pUCMI ){
      return;
   } // endif

   if (pUCMI->pszText) {
   // POINTL aptl[TXTBOX_COUNT];
      RECTL  Rect;
      HPS hps = WinGetPS(UCMData->hwndMenu);

      //(MAM) Use WinDrawText() to calculate required text size, since this
      // is the API used in the actual drawing.  QueryTextBox() does not always
      // return correct box size when italic fonts are used.
      memset(&Rect, 0x00, sizeof(RECTL));
      Rect.yTop = MAX_INT;
      Rect.xRight = MAX_INT;
      WinDrawText(hps, -1, pUCMI->pszText, &Rect, 0L, 0L, DT_QUERYEXTENT|DT_CENTER|DT_VCENTER|DT_TEXTATTRS|DT_MNEMONIC);
      *pHeight = Rect.yTop - Rect.yBottom;
      *pWidth  = (Rect.xRight - Rect.xLeft) + SUM_TEXT_FRAME_THICK_HORZ;

   // GpiQueryTextBox( hps,
   //                  strlen( pUCMI->pszText ),
   //                  pUCMI->pszText,
   //                  TXTBOX_COUNT,
   //                  aptl );
      WinReleasePS(hps);
   // *pHeight = aptl[TXTBOX_TOPLEFT].y  - aptl[TXTBOX_BOTTOMLEFT].y;
   // *pWidth  = aptl[TXTBOX_TOPRIGHT].x - aptl[TXTBOX_TOPLEFT].x;
   // *pWidth += SUM_TEXT_FRAME_THICK_HORZ;  // we leave some space around the text
   } else {
      *pHeight = 0;
      *pWidth  = 0;
   } // endif
}

//----------------------------------------------------------------------------
// UCMenuFreeMenuData
//----------------------------------------------------------------------------
// :function res=&IDF_FREEMENU. name='UCMenuFreeMenuData' text='Frees the menu data'.
// This function frees the data associated with the OWNERDRAW items of a menu.
// :syntax name='UCMenuFreeMenuData' params='hwndMenu' return='-' .
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing.
// :efparams.
// :remarks.
// This function parses the whole menu (including submenus). It frees the
// data structure associated with every OWNERDRAW item.
// :p.This function requires the owner of the menu to be the ucmenu.
// :hp2.Note&colon.:ehp2. This function is automatically executed when a UCMenu receives a WM_DESTROY message.
// :enote.
// :related.
// :efunction.
//----------------------------------------------------------------------------
VOID APIENTRY  UCMenuFreeMenuData(HWND hwndMenu)
{
  MENUITEM mi;
  SHORT    sIndex, ItemID, NbOfItems;
  PUCMDATA UCMData = (PUCMDATA) WinQueryWindowULong( hwndMenu, QWL_USER );
  HWND     hwndUCM;

  if ( UCMData ) {
     hwndUCM = WinQueryWindow( UCMData->hwndMenu, QW_OWNER );
  } else {
     hwndUCM = WinQueryWindow( hwndMenu, QW_OWNER );
  } /* endif */

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the Number of menu items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  NbOfItems = (SHORT)WinSendMsg(hwndMenu,
                                MM_QUERYITEMCOUNT,
                                (MPARAM)0,
                                (MPARAM)0);

  for (sIndex=0 ; sIndex<NbOfItems ; sIndex++) {

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item handle and structure ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    ItemID = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(sIndex),
                               (MPARAM)0);
    WinSendMsg( WinQueryWindow( hwndUCM, QW_OWNER ),
                WM_CONTROL,
                MPFROM2SHORT( WinQueryWindowUShort( hwndUCM, QWS_ID ), UCN_DELETEDITEM ),
                MPFROMSHORT( ItemID ) );
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(ItemID,FALSE),
               MPFROMP(&mi));

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ If it's a Submenu, do a recursive call with hwndSubMenu ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    if (mi.hwndSubMenu){
       PFNWP pFnwp;
       UCMenuFreeMenuData(mi.hwndSubMenu);
       pFnwp = (PFNWP)WinQueryWindowPtr( mi.hwndSubMenu, QWP_PFNWP );
       if ( ( pFnwp == SubmenuWndProc ) && UCMData && UCMData->OldSubMenuProc ){
          WinSubclassWindow( mi.hwndSubMenu, (PFNWP)UCMData->OldSubMenuProc );
       } // endif
    } // endif

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Free the handle of ownerdrawn items ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    if ((mi.afStyle & MIS_OWNERDRAW) && mi.hItem) {
      if ( ITEM( &mi, pszBmp ) ){
        MyFree( ITEM( &mi, pszBmp ) );
        ITEM( &mi, pszBmp ) = 0;
      }
      if ( ITEM( &mi, pszText ) ){
        MyFree( ITEM( &mi, pszText ) );
        ITEM( &mi, pszText ) = 0;
      }
      if ( ITEM( &mi, pszAction ) ){
        MyFree( ITEM( &mi, pszAction ) );
        ITEM( &mi, pszAction ) = 0;
      }
      if ( ITEM( &mi, pszData ) ){
        MyFree( ITEM( &mi, pszData ) );
        ITEM( &mi, pszData ) = 0;
      }
      if ( ITEM( &mi, pszParameters ) ){
        MyFree( ITEM( &mi, pszParameters ) );
        ITEM( &mi, pszParameters ) = 0;
      }
      if ( ITEM( &mi, hBmp ) ){
        GpiDeleteBitmap( ITEM( &mi, hBmp ) );
        ITEM( &mi, hBmp ) = 0;
      }
      MyFree( (PVOID)mi.hItem );
      mi.hItem = 0;
      WinSendMsg( hwndMenu,
                  MM_SETITEM,
                  MPFROM2SHORT( 0, TRUE ),
                  MPFROMP( &mi ) );
    } /* endif */

  } /* endfor */

}

//----------------------------------------------------------------------------
// CreateUCMenu : Internal function
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CREATUCM. name='CreateUCMenu' text='Creates a User-customizable Menu'.
// This function creates a User-customizable Menu of the specified style in a given rectangle.
// :syntax name='CreateUCMenu' params='hwndUCMenu, hwndParent, hwndOwner, hwndMenu, hModule, MenuID, pRcl, Style, NbOfCols, NbOfRows' return='-'.
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input'.
// Handle of the UCMenu.
// :fparam name='hwndParent' type='HWND' io='input'.
// Handle of the UCMenu's parent window.
// :fparam name='hwndOwner' type='HWND' io='input'.
// Handle of the UCMenu's owner window.
// :fparam name='hwndMenu' type='HWND' io='input'.
// Handle of the menu window associated with the UCMenu.
// :fparam name='MenuID' type='USHORT' io='input'.
// ID of the menu in the resource
// :fparam name='pRcl' type='PRECTL' io='input'.
// UCMenu rectangle.
// p.The height of a horizontal ucmenu is the height of the tallest item
// p.The width of a vertical ucmenu is the width of the widest item
// p.The size of a matrix ucmenu is calculated according to NbOfCols, NbOfRows, the widest and tallest items
// :fparam name='Style' type='USHORT' io='input'.
// :dl compact.
// :dt.:hp2.CMS_VERT:ehp2.
// :dd.Vertical UCMenu
// :dt.:hp2.CMS_HORZ:ehp2.
// :dd.Horizontal UCMenu
// :dt.:hp2.CMS_MATRIX:ehp2.
// :dd.Matrix UCMenu
// :edl.
// :fparam name='NbOfCols' type='USHORT io='input'.
// Number of columns if matrix ucmenu
// :fparam name='NbOfRows' type='USHORT io='input'.
// Number of rows if matrix ucmenu
// :fparam name='ulVersion' type='ULONG io='input'.
// Template version used to build the menu
// :freturns.
// :fparam name='-' type='-' io='-'.
// Nothing.
// :efparams.
// :remarks.
// The UCMenu is the owner of the menu window and therefore receives all the messages.
// However, it forwards the following messages to its owner. They are
// described in PM Reference Guide (Menu Control Notification Messages).
// :dl compact.
// :dt.:hp2.WM_COMMAND:ehp2.
// :dd.:hp2.SHORT2FROMMP(mp1) = UCMenuID, SHORT1FROMMP(mp2) = CMDSRC_UCMENU:ehp2.
// :dt.:hp2.WM_HELP:ehp2.
// :dd.:hp2.SHORT2FROMMP(mp1) = UCMenuID, SHORT1FROMMP(mp2) = CMDSRC_UCMENU:ehp2.
// :dt.:hp2.WM_INITMENU:ehp2.
// :dd.
// :dt.:hp2.WM_MENUEND:ehp2.
// :dd.:hp2.mp2 = hwndUCMenu:ehp2.
// :dt.:hp2.WM_MENUSELECT:ehp2.
// :dd.:hp2.mp2 = hwndUCMenu:ehp2.
// :dt.:hp2.WM_NEXTMENU:ehp2.
// :dd.
// :edl.
// :p.
// The items for which a bitmap can not be found are processed like regular menu items. This
// means that the parameters associated to the previous messages are not changed for them.
// :p.
// The following messages are processed by the UCMenu and not forwarded &colon.
// :dl compact.
// :dt.:hp2.WM_DRAWITEM:ehp2.
// :dd.
// :dt.:hp2.WM_MEASUREITEM:ehp2.
// :dd.
// :edl.
// :p.
// The Menu Control Window Messages (MM_*) sent to the UCMenu are forwarded to
// the menu window. :hp2.MM_QUERYITEMTEXT:ehp2., :hp2.MM_QUERYITEMTEXTLENGTH:ehp2.
// and :hp2.MM_SETITEMTEXT:ehp2., which usually only work for items with a MIS_TEXT style, can
// be used with the MIS_OWNERDRAW items to query and set the text displayed in the bitmap.
// :xamples.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink  CreateUCMenu(HWND hwndUCMenu, HWND hwndParent, HWND hwndOwner,
                           HWND hwndMenu, USHORT MenuID,
                           PRECTL prcl, USHORT Style, USHORT NbOfCols, USHORT NbOfRows, ULONG ulVersion)
{
  LONG      Arrow;
  RECTL     rcl, rclM;
  BOOL      Scrollable;
  PUCMDATA  UCMData;
  ULONG     ScrollStyle;


  UCMData = (PUCMDATA)WinQueryWindowULong(hwndUCMenu, QWL_UCMDATA);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Load the OWNERDRAWN items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  UCMData->AccelTable->cAccel = 0;

  UCMenuLoadMenuData(hwndMenu, UCMData, ulVersion, hwndUCMenu );

  WinSetOwner (hwndMenu, hwndUCMenu);

  UCMenuNotifAll( UCMData, hwndMenu, UCN_ADDEDITEM );

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Autosize : take the size of the biggest item as a reference ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    GetMaxItemSize(UCMData, hwndUCMenu, hwndMenu);

    if (Style & CMS_MATRIX) {
        prcl->yTop  = prcl->yBottom + (UCMData->MaxHorizontalHeight) * NbOfRows;
        prcl->yTop += SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
        prcl->xRight  = prcl->xLeft + (UCMData->MaxVerticalWidth) * NbOfCols;
        prcl->xRight += SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
    } // endif

    if ( Style & CMS_VERT ) {
      prcl->xRight = prcl->xLeft + UCMData->MaxVerticalWidth;
      prcl->xRight += SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
    } // endif

    if ( Style & CMS_HORZ ) {
      prcl->yTop  = prcl->yBottom + UCMData->MaxHorizontalHeight;
      prcl->yTop += SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
    } // endif


  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Size the UC Menu ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  WinSetWindowPos(hwndUCMenu,
                  HWND_TOP,
                  prcl->xLeft,
                  prcl->yBottom,
                  prcl->xRight - prcl->xLeft,
                  prcl->yTop - prcl->yBottom,
                  SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Create Scroll Bar ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  ScrollStyle = SBS_HORZ;
  if ((Style & CMS_VERT) || ((Style & CMS_MATRIX_VERT) == CMS_MATRIX_VERT))
    ScrollStyle = SBS_VERT;
  UCMData->hwndScroll = WinCreateWindow(hwndUCMenu,
                               WC_SCROLLBAR,
                               "",
                               WS_VISIBLE | WS_CLIPCHILDREN | ScrollStyle,
                               0,
                               0,
                               prcl->xRight - prcl->xLeft,
                               prcl->yTop - prcl->yBottom,
                               hwndUCMenu,
                               HWND_TOP,
                               0,
                               NULL,
                               NULL);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Register and create a window to hide the slider ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  WinRegisterClass((HAB)NULLHANDLE, "Hide", (PFNWP)HideWndProc, (ULONG)CS_SIZEREDRAW, 4);

  UCMData->hwndHide = WinCreateWindow(UCMData->hwndScroll,
                             "Hide",
                             "",
                             WS_VISIBLE,
                             0,0,0,0,
                             hwndUCMenu,
                             HWND_TOP,
                             0,
                             (PVOID)WinQueryWindowULong(hwndUCMenu, QWL_UCMDATA),
                             (PVOID)NULL);

  WinSetParent(hwndMenu, UCMData->hwndHide, FALSE);

  switch (Style & 0x7) {

    case CMS_VERT:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Get the menu height to know if we have to hide the buttons too:³
        ³  - Set the width of the menu window and query its height       ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      0,
                      0,
                      UCMData->MaxVerticalWidth,
                      10000,
                      SWP_SIZE);
      WinQueryWindowRect(hwndMenu, &rclM);
      // The height returned is the sum  of all the items heights + 1
      //  ( don't ask me why ... )
      rclM.yTop --;
      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      0,
                      0,
                      rclM.xRight,
                      rclM.yTop,
                      SWP_SIZE);


      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Size the Hide Window ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      Arrow = WinQuerySysValue(HWND_DESKTOP, SV_CYVSCROLLARROW);
      Scrollable = (rclM.yTop > (prcl->yTop - prcl->yBottom - SUM_UCM_FRAME_THICK - SUM_MENU_FRAME_THICK));
      WinSetWindowPos(UCMData->hwndHide,
                      HWND_TOP,
                      UCM_FRAME_THICK,
                      UCM_FRAME_THICK + Arrow * Scrollable,
                      prcl->xRight - prcl->xLeft   - SUM_UCM_FRAME_THICK,
                      prcl->yTop   - prcl->yBottom - SUM_UCM_FRAME_THICK - 2 * Arrow * Scrollable,
                      SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER);

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³Set the scrollbar parameters : slider size and range ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      WinQueryWindowRect(UCMData->hwndHide, &rcl);
      WinSendMsg(UCMData->hwndScroll,
                 SBM_SETSCROLLBAR,
                 MPFROMSHORT(0),
                 MPFROM2SHORT(0, rclM.yTop - (rcl.yTop - rcl.yBottom - SUM_MENU_FRAME_THICK)));
      WinSendMsg(UCMData->hwndScroll,
                 SBM_SETTHUMBSIZE,
                 MPFROM2SHORT(rcl.yTop - rcl.yBottom - SUM_MENU_FRAME_THICK, rclM.yTop),
                 (MPARAM)0);

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Position and show the menu ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      MENU_FRAME_THICK,
                      (rcl.yTop - rcl.yBottom - SUM_MENU_FRAME_THICK) - rclM.yTop  + MENU_FRAME_THICK,
                      0,
                      0,
                      SWP_MOVE | SWP_SHOW);
      break;

    case CMS_HORZ:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Get the menu  width to know if we have to hide the buttons too:³
        ³  - Query all items ...                                         ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      { SHORT sIndex, NbOfItems, ItemID2, MenuWidth=0;
        RECTL rclItem;

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Query the Number of menu items ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        NbOfItems = (SHORT)WinSendMsg(hwndMenu,
                                      MM_QUERYITEMCOUNT,
                                      (MPARAM)0,
                                      (MPARAM)0);

        for (sIndex=0 ; sIndex<NbOfItems ; sIndex++) {
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Query the item rectangle and add the width to MenuWidth ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          ItemID2 = (SHORT)WinSendMsg(hwndMenu,
                                      MM_ITEMIDFROMPOSITION,
                                      MPFROMSHORT(sIndex),
                                      (MPARAM)0);
          WinSendMsg(hwndMenu,
                     MM_QUERYITEMRECT,
                     MPFROM2SHORT(ItemID2,FALSE),
                     MPFROMP(&rclItem));

          MenuWidth += rclItem.xRight - rclItem.xLeft;
        } /* endfor */

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Size the menu window ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSetWindowPos(hwndMenu,
                        HWND_TOP,
                        0,
                        0,
                        MenuWidth,
                        UCMData->MaxHorizontalHeight,
                        SWP_SIZE);
      }

      WinQueryWindowRect(hwndMenu, &rclM);

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Size the Hide Window ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      Arrow = WinQuerySysValue(HWND_DESKTOP, SV_CXHSCROLLARROW);
      Scrollable = (rclM.xRight > (prcl->xRight - prcl->xLeft - SUM_UCM_FRAME_THICK - SUM_MENU_FRAME_THICK));
      WinSetWindowPos(UCMData->hwndHide,
                      HWND_TOP,
                      UCM_FRAME_THICK + Arrow * Scrollable,
                      UCM_FRAME_THICK,
                      prcl->xRight - prcl->xLeft - SUM_UCM_FRAME_THICK - 2 * Arrow * Scrollable,
                      prcl->yTop - prcl->yBottom - SUM_UCM_FRAME_THICK,
                      SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ZORDER);

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³Set the scrollbar parameters : slider size and range ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      WinQueryWindowRect(UCMData->hwndHide, &rcl);
      WinSendMsg(UCMData->hwndScroll,
                 SBM_SETSCROLLBAR,
                 MPFROMSHORT(0),
                 MPFROM2SHORT(0, rclM.xRight - (rcl.xRight - rcl.xLeft - SUM_MENU_FRAME_THICK)));
      WinSendMsg(UCMData->hwndScroll,
                 SBM_SETTHUMBSIZE,
                 MPFROM2SHORT(rcl.xRight - rcl.xLeft - SUM_MENU_FRAME_THICK, rclM.xRight),
                 (MPARAM)0);

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Position and show the menu ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      MENU_FRAME_THICK,
                      MENU_FRAME_THICK,
                      0,
                      0,
                      SWP_MOVE | SWP_SHOW);
      break;

    case CMS_MATRIX:
      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      0,
                      0,
                      prcl->xRight - prcl->xLeft - SUM_MENU_FRAME_THICK - SUM_UCM_FRAME_THICK,
                      10000,
                      SWP_SIZE);
      WinQueryWindowRect(hwndMenu, &rclM);

      WinSetWindowPos(UCMData->hwndHide,
                      HWND_TOP,
                      UCM_FRAME_THICK,
                      UCM_FRAME_THICK,
                      prcl->xRight - prcl->xLeft - SUM_UCM_FRAME_THICK,
                      prcl->yTop - prcl->yBottom - SUM_UCM_FRAME_THICK,
                      SWP_MOVE | SWP_SIZE | SWP_SHOW );

      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      MENU_FRAME_THICK,
                      prcl->yTop - prcl->yBottom - SUM_MENU_FRAME_THICK - SUM_UCM_FRAME_THICK - rclM.yTop + MENU_FRAME_THICK,
                      0,
                      0,
                      SWP_MOVE | SWP_ZORDER | SWP_SHOW);

      break;
  } /* endswitch */
}

//----------------------------------------------------------------------------
// UCMenuSize : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UCMenuSize. name='UCMenuSize' text='Resizes a menu window'.
// This function resizes the menu window of horizontal and vertical UCMenus.
// It is basically used when a user adds, removes or changes a bitmap.
// :syntax name='UCMenuSize' params='hwndMenu, Style' return='rc'.
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input'.
// Window handle of the menu.
// :fparam name='Style' type='LONG' io='input'.
// Style of the menu (CMS_HORZ or CMS_VERT).
// :freturns.
// :fparam name='rc' type='BOOL' io='output'.
// Returns :hp2.TRUE:ehp2. if the menu window is resized.
// :efparams.
// :remarks.
// This function recalculates the width of horizontal menus and the height of
// vertical menus by adding the bitmap sizes.
// :hp2.Note&colon.:ehp2. This function is automatically called by the UCMenu when it receives
// a MM_DELETEITEM, MM_REMOVEITEM, MM_INSERTITEM, MM_SETITEM, MM_SETITEMATTR
// or MM_SETITEMHANDLE message.
// :enote.
// :xamples.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
BOOL _Optlink  UCMenuSize(HWND hwndMenu, USHORT Style)
{
  RECTL rcl;
  SHORT Size=0;
  SHORT NbOfItems, ItemID, sIndex;
  HWND  hwndHide;
  PUCMDATA UCMData ;

  UCMData = (PUCMDATA)WinQueryWindowULong(hwndMenu , QWL_USER);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the Number of menu items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  NbOfItems = (SHORT)WinSendMsg(hwndMenu,
                                MM_QUERYITEMCOUNT,
                                (MPARAM)0,
                                (MPARAM)0);

  for (sIndex=0 ; sIndex<NbOfItems ; sIndex++) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item rectangle and add its size to Size ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    ItemID = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(sIndex),
                               (MPARAM)0);
    WinSendMsg(hwndMenu,
               MM_QUERYITEMRECT,
               MPFROM2SHORT(ItemID,FALSE),
               MPFROMP(&rcl));

    if (Style & CMS_HORZ)
      Size += rcl.xRight - rcl.xLeft;
    else
      Size += rcl.yTop - rcl.yBottom;

  }

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Invalidate the parent ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  hwndHide = WinQueryWindow(hwndMenu, QW_PARENT);
  WinQueryWindowRect(hwndHide, &rcl);
  WinInvalidateRect(hwndHide, &rcl, TRUE);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Size the menu window ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  if (!(Style & CMS_MATRIX))
    WinSetWindowPos(hwndMenu,
                    HWND_TOP,
                    MENU_FRAME_THICK,
                    MENU_FRAME_THICK,
                    (Style & CMS_HORZ ? Size : UCMData->MaxVerticalWidth ),
                    (Style & CMS_VERT ? Size : UCMData->MaxHorizontalHeight),
                    SWP_SIZE);
  else
    WinSetWindowPos(hwndMenu,
                    HWND_TOP,
                    MENU_FRAME_THICK,
                    MENU_FRAME_THICK,
                    UCMData->MaxVerticalWidth    * UCMData->NbOfCols,
                    UCMData->MaxHorizontalHeight * UCMData->NbOfRows,
                    SWP_SIZE);

  return TRUE;
}

//----------------------------------------------------------------------------
// UCMenuCheckScrolling : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CHKSCROL. name='UCMenuCheckScrolling' text='Checks the scrolling status'.
// This function compares the menu size with the UCMenu size and enables or disables
// the scrolling.
// :syntax name='UCMenuCheckScrolling' params='hwndUCMenu' return='rc'.
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input'.
// Window handle of the UCMenu (as returned by CreateUCMenu).
// :freturns.
// :fparam name='rc' type='BOOL' io='output'.
// Returns :hp1.TRUE:ehp1. if the scrolling status changed.
// :efparams.
// :remarks.
// The parameters are reset in two cases &colon.
// :ol compact.
// :li.The menu is larger than the UCMenu and the scrolling disabled
// :li.The menu is shorter than the UCMenu and the scrolling enabled
// :eol.
// :note.This function is called every time the UCMenu receives a WM_SIZE
// message.
// :enote.
// :xamples.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
BOOL _Optlink  UCMenuCheckScrolling(HWND hwndUCMenu)
{
  HWND      hwndScroll = WinQueryWindow(hwndUCMenu, QW_TOP);
  HWND      hwndHide   = WinQueryWindow(hwndScroll, QW_TOP);
  HWND      hwndMenu   = WinQueryWindow(hwndHide,   QW_TOP);
  LONG      Arrow      ;
  ULONG     Style      = WinQueryWindowULong(hwndUCMenu, QWL_STYLE);
  SWP       swpMenu, swpHide, swpScroll;
  PUCMDATA  UCMData ;

  if (!Style)
    return FALSE;

  UCMData = (PUCMDATA)WinQueryWindowULong(hwndMenu , QWL_USER); //c1: Need ptr to our data
 
  WinQueryWindowPos(hwndMenu,   &swpMenu);
  WinQueryWindowPos(hwndHide,   &swpHide);
  WinQueryWindowPos(hwndScroll, &swpScroll);

  if (((Style & CMS_VERT) || ((Style & CMS_MATRIX_VERT) == CMS_MATRIX_VERT)) &&
      swpMenu.cy >  swpScroll.cy - SUM_UCM_FRAME_THICK - SUM_MENU_FRAME_THICK
      ) {
    SHORT     CurrPos;    //@XXXa
    CurrPos = (SHORT)WinSendMsg(hwndScroll, SBM_QUERYPOS, MPVOID, MPVOID);  //@XXXa
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Menu larger than scrollbar. We reset the                         ³
      ³ whole thing : Resize the hiding window, reposition the menu      ³
      ³ window, reset the scrolling parameters                           ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    /* Adjust hide window to uncover scroll bar arrows */
    Arrow         = WinQuerySysValue(HWND_DESKTOP, SV_CYVSCROLLARROW) + UCMData->BmpInset; //c1
    swpHide.y    += Arrow;
    swpHide.cy   -= 2 * Arrow;

    /* Adjust menu to current scroll position */
    swpMenu.y = (swpHide.cy - MENU_FRAME_THICK) - swpMenu.cy + CurrPos;

    // Adjust position of the menu window relative to the scrollbar window.  Position the
    // X coordinate to align the left edge of the menu into the scrollbar.  Leave the Y
    // coordinate where it is, or flush-top align it if it does not extend to the bottom.
 
    swpMenu.x = MENU_FRAME_THICK;
//  if (swpMenu.y + swpMenu.cy < swpHide.y + swpHide.cy - MENU_FRAME_THICK)  // Does not reach top?
//    swpMenu.y = (swpHide.y + swpHide.cy - MENU_FRAME_THICK) - swpMenu.cy;  // Align to top
//  else
      swpMenu.y = min(swpMenu.y, MENU_FRAME_THICK);         // Dont allow to lift off bottom
    WinSetWindowPos(hwndMenu,
                      HWND_TOP, swpMenu.x, swpMenu.y, 0, 0,
                      SWP_MOVE | SWP_SHOW | SWP_ZORDER);

    WinSetWindowPos(hwndHide,
                    HWND_TOP,
                    swpHide.x,
                    swpHide.y,
                    swpHide.cx,
                    swpHide.cy,
                    SWP_MOVE | SWP_SIZE | SWP_SHOW);

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Set the scrolling parameters ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndScroll,
               SBM_SETSCROLLBAR,
               MPFROMSHORT((swpMenu.y+swpMenu.cy)-(swpHide.cy-MENU_FRAME_THICK)),
               MPFROM2SHORT(0, swpMenu.cy - (swpHide.cy-SUM_MENU_FRAME_THICK)));
    WinSendMsg(hwndScroll,
               SBM_SETTHUMBSIZE,
               MPFROM2SHORT(swpHide.cy-SUM_MENU_FRAME_THICK, swpMenu.cy),
               (MPARAM)0);
  
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Window resized : return TRUE  ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    return TRUE;
  } /* endif */

  if (((Style & CMS_VERT) || ((Style & CMS_MATRIX_VERT) == CMS_MATRIX_VERT)) &&
      swpMenu.cy <= swpScroll.cy - SUM_UCM_FRAME_THICK - SUM_MENU_FRAME_THICK
      ) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Menu smaller than scrollbar. We reset the                        ³
      ³ whole thing : Resize the hiding window, reposition the menu      ³
      ³ window, reset the scrolling parameters                           ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

      // Reset menu to left/top flush edge
      WinSetWindowPos(hwndMenu,
                      HWND_TOP,
                      MENU_FRAME_THICK,
                      (swpHide.cy - MENU_FRAME_THICK) - swpMenu.cy,
                      0,
                      0,
                      SWP_MOVE | SWP_SHOW | SWP_ZORDER);


    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Set the scrolling parameters ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndScroll,
               SBM_SETSCROLLBAR,
               MPFROMSHORT(0),
               MPFROM2SHORT(0, swpMenu.cy - (swpHide.cy-SUM_MENU_FRAME_THICK)));
    WinSendMsg(hwndScroll,
               SBM_SETTHUMBSIZE,
               MPFROM2SHORT(swpHide.cy-SUM_MENU_FRAME_THICK, swpMenu.cy),
               (MPARAM)0);

    return TRUE;
  } /* endif */

  if ((Style & CMS_HORZ) &&
      swpMenu.cx >  swpScroll.cx - SUM_UCM_FRAME_THICK - SUM_MENU_FRAME_THICK
      ) {

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Menu larger than scrollbar. We reset the                         ³
      ³ whole thing : Resize the hiding window, reposition the menu      ³
      ³ window, reset the scrolling parameters                           ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Resize Hide : width   -= 2 Arrows ³
      ³ Repos  Hide : xLeft   += Arrow    ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    Arrow       = WinQuerySysValue(HWND_DESKTOP, SV_CXHSCROLLARROW) + UCMData->BmpInset; //c1
    swpHide.x  +=     Arrow;
    swpHide.cx -= 2 * Arrow;

    // Adjust position of the menu window relative to the scrollbar window.  Position the
    // Y coordinate to align the top edge of the menu into the scrollbar.  Leave the X
    // coordinate where it is, or flush-right align it if it does not extend to the edge.

    swpMenu.y = swpScroll.cy - (2*SUM_UCM_FRAME_THICK) - swpMenu.cy + MENU_FRAME_THICK;                         //@P5a
    swpMenu.x = max(swpMenu.x, swpScroll.x + swpScroll.cx - (2*Arrow) - swpMenu.cx - (2*SUM_MENU_FRAME_THICK)); //@P5a
    WinSetWindowPos(hwndMenu,                                                                                   //@P5m
                      HWND_TOP, swpMenu.x, swpMenu.y, 0, 0,                                                     //@P5m
                      SWP_MOVE | SWP_SHOW | SWP_ZORDER);                                                        //@P5m

    WinSetWindowPos(hwndHide,
                    HWND_TOP,
                    swpHide.x,
                    swpHide.y,
                    swpHide.cx,
                    swpHide.cy,
                    SWP_MOVE | SWP_SIZE | SWP_SHOW);

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Set the scrolling parameters ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndScroll,
               SBM_SETSCROLLBAR,
               MPFROMSHORT(swpScroll.x - swpMenu.x),  // Posn may have changed by move of menu above //@P5c
               MPFROM2SHORT(0, swpMenu.cx - (swpHide.cx-SUM_MENU_FRAME_THICK)));
    WinSendMsg(hwndScroll,
               SBM_SETTHUMBSIZE,
               MPFROM2SHORT(swpHide.cx-SUM_MENU_FRAME_THICK, swpMenu.cx),
               (MPARAM)0);

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Window resized : return TRUE  ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    return TRUE;
  } /* endif */

  if ((Style & CMS_HORZ) &&
      swpMenu.cx <= swpScroll.cx - SUM_UCM_FRAME_THICK - SUM_MENU_FRAME_THICK
      ) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Menu smaller than scrollbar. We reset the                        ³
      ³ whole thing : Resize the hiding window, reposition the menu      ³
      ³ window, reset the scrolling parameters                           ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

      // Reset menu to left/top flush edge
      WinSetWindowPos(hwndMenu,                                                                 //@P5a
                      HWND_TOP,                                                                 //@P5a 
                      MENU_FRAME_THICK,                                                         //@P5a 
                      swpScroll.cy - (2*SUM_UCM_FRAME_THICK) - swpMenu.cy + MENU_FRAME_THICK,   //@P5a 
                      0, 0, SWP_MOVE | SWP_SHOW | SWP_ZORDER);                                  //@P5a 

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Set the scrolling parameters ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndScroll,
               SBM_SETSCROLLBAR,
               MPFROMSHORT(0),        // Scroll position is now zero (flush left)
               MPFROM2SHORT(0, swpMenu.cx - (swpHide.cx-SUM_MENU_FRAME_THICK)));
    WinSendMsg(hwndScroll,
               SBM_SETTHUMBSIZE,
               MPFROM2SHORT(swpHide.cx-SUM_MENU_FRAME_THICK, swpMenu.cx),
               (MPARAM)0);

    return TRUE;
  } else {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Matrix, no scrolling³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

      // Reset menu to flush left/top
      WinSetWindowPos(hwndMenu, HWND_TOP,                                                       //@P5a
                      MENU_FRAME_THICK,                                                         //@P5a 
                      (swpHide.cy - MENU_FRAME_THICK) - swpMenu.cy,                             //@P5a
                      0, 0, SWP_MOVE | SWP_SHOW | SWP_ZORDER);                                  //@P5a 

//  WinSendMsg(hwndScroll,
//             SBM_SETSCROLLBAR,
//             MPFROMSHORT(0),
//             MPFROM2SHORT(0,0));
//  WinSendMsg(hwndScroll,
//             SBM_SETTHUMBSIZE,
//             MPFROM2SHORT(swpHide.cx-SUM_MENU_FRAME_THICK, swpMenu.cx),
//             (MPARAM)0);
    return TRUE;
  } /* endif */
}

//----------------------------------------------------------------------------
// UCMenuIdFromCoord :
//----------------------------------------------------------------------------
// :function res=&IDF_IDFROMP. name='UCMenuIdFromCoord' text='Get the ID of a specified menu item' .
// This function returns the id of the menu item that is at a specified position.
// :syntax name='UCMenuIdFromCoord' params='hwndMenu, pptrPos' return='ItemID' .
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='pptrPos' type='PPOINTL' io='input' .
// Position
// :freturns.
// :fparam name='ItemID' type='USHORT' io='return'.
// The item Identifier. 0 if not found.
// :efparams.
// :remarks.
// This function doesn't check the submenus. However, you can identify an item in a submenu
// if you pass the hwnd of the submenu...
// :related.
// :efunction.
//----------------------------------------------------------------------------
USHORT APIENTRY  UCMenuIdFromCoord(HWND hwndMenu, PPOINTL pptrPos)
{
  USHORT    NbOfItems, ItemID, usIndex;
  RECTL    rcl;

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the Number of menu items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  NbOfItems = (USHORT)WinSendMsg(hwndMenu,
                                 MM_QUERYITEMCOUNT,
                                 (MPARAM)0,
                                 (MPARAM)0);

  for (usIndex=0 ; usIndex<NbOfItems ; usIndex++) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item id ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    ItemID = (USHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(usIndex),
                               (MPARAM)0);

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item rectangle³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndMenu,
               MM_QUERYITEMRECT,
               MPFROM2SHORT(ItemID,TRUE),
               MPFROMP(&rcl));

    //(MAM) fixed following to include xRight and yTop pixels
    if (    pptrPos->x >= rcl.xLeft
         && pptrPos->x <= rcl.xRight
         && pptrPos->y >= rcl.yBottom
         && pptrPos->y <= rcl.yTop     ) {
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ We got it ! ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      return ItemID;
     } // endif;
  } // endfor
  return 0;
}

//----------------------------------------------------------------------------
// UCMenuGetActionID
//----------------------------------------------------------------------------
// :function res=&IDF_IDFROMACTION. name='UCMenuGetActionID' text='Get the IDs corresponding to an action' .
// This function returns the ID of the item with a pszAction action, starting at the item sStart.
// :syntax name='UCMenuGetActionID' params='hwndUCM, pszAction, , bSubmenus, sStart ' return='FoundID' .
// :fparams.
// :fparam name='hwndUCM' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pszAction' type='PSZ' io='input' .
// Action string to look for
// :fparam name='bSubmenus' type='BOOL' io='input' .
// Look in submenus or not.
// :fparam name='Start' type='SHORT' io='input' .
// Item ID to start with, MIT_FIRST for the beginning.
// :freturns.
// :fparam name='FoundID' type='SHORT' io='return'.
// Item ID found, or MIT_NONE
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
SHORT APIENTRY UCMenuGetActionID(HWND hwndUCM, PSZ pszAction, BOOL bSubmenus, SHORT sStartID)
{
   SHORT    sFound;
   PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwndUCM, QWL_UCMDATA );

   if ( UCMData ) {
      sFound =  UCMenuGetActionID2( UCMData->hwndMenu, pszAction, bSubmenus, sStartID );
      if ( sFound == -2 ){
         return MIT_NONE;
      } else {
         return sFound;
      } // endif
   } else {
      return MIT_NONE;
   } /* endif */
}


//----------------------------------------------------------------------------
// UCMenuGetActionID2
//----------------------------------------------------------------------------
// :pfunction res=&IDF_IDFROMACTION2. name='UCMenuGetActionID2' text='Get the IDs corresponding to an action'.
// This function returns the ID of the item with a pszAction action, starting at the item sStart.
// :syntax name='UCMenuGetActionID2' params='hwndUCM, pszAction, , bSubmenus, sStart ' return='FoundID' .
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='pszAction' type='PSZ' io='input' .
// Action string to look for
// :fparam name='bSubmenus' type='BOOL' io='input' .
// Look in submenus or not.
// :fparam name='Start' type='SHORT' io='input' .
// Item ID to start with, MIT_FIRST for the beginning.
// :freturns.
// :fparam name='FoundID' type='SHORT' io='return'.
// Item ID found, or MIT_NONE if none, -2 if sStart has been found
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

SHORT _Optlink UCMenuGetActionID2(HWND hwndMenu, PSZ pszAction, BOOL bSubmenus, SHORT sStartID)
{
  USHORT    NbOfItems, ItemID, usIndex;
  BOOL      bStartIDPassed;
  MENUITEM  mi;

  if ( sStartID == MIT_FIRST ){
     bStartIDPassed = TRUE;
  } else {
     bStartIDPassed = FALSE;
  } // endif

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the Number of menu items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  NbOfItems = (USHORT)WinSendMsg(hwndMenu,
                                 MM_QUERYITEMCOUNT,
                                 (MPARAM)0,
                                 (MPARAM)0);

  for (usIndex=0 ; usIndex<NbOfItems ; usIndex++) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item id ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    memset( &mi, '\0', sizeof mi );
    ItemID = (USHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(usIndex),
                               (MPARAM)0);

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(ItemID,FALSE),
               MPFROMP(&mi));
    if ( bStartIDPassed ){
       if ( mi.hItem && ITEM( &mi, pszAction ) ){
          if ( !strcmp( pszAction, ITEM( &mi, pszAction ) ) ){
             return ItemID;
          } // endif
       } // endif
    } // endif

    if ( bSubmenus && mi.hwndSubMenu ){
       SHORT sFoundID =
          UCMenuGetActionID2( mi.hwndSubMenu, pszAction, FALSE, bStartIDPassed?MIT_FIRST:sStartID);
       if ( sFoundID != MIT_NONE  && sFoundID != -2){
          return sFoundID;
       } else if ( sFoundID == -2 ){
          bStartIDPassed = TRUE;
       } // endif
    } // endif

    if ( ItemID == sStartID ){
       bStartIDPassed = TRUE;
    } // endif

  } // endfor

  if ( bStartIDPassed ){
     return -2;
  } else {
     return MIT_NONE;
  } // endif
}

//----------------------------------------------------------------------------
// UCMenuSetActionAttr
//----------------------------------------------------------------------------
// :function res=&IDF_SETACTIONATTR. name='UCMenuSetActionAttr' text='Get the IDs corresponding to an action' .
// This function sets the attributes of the items with the given action.
// :syntax name='UCMenuSetActionAttr' params='hwndUCM, pszAction, usAttrMask, usAttrValue' return='nothing' .
// :fparams.
// :fparam name='hwndUCM' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='pszAction' type='PSZ' io='input' .
// Action string to look for
// :fparam name='usAttrMask' type='USHORT' io='input' .
// Attribute mask to use
// :fparam name='usAttrValue' type='USHORT' io='input' .
// Attribute value to set
// :freturns.
// :fparam name='-' type='VOID' io='return'.
// Nothing
// :efparams.
// :remarks.
// :related.
// MM_SETITEMATTR
// :efunction.
//----------------------------------------------------------------------------
VOID APIENTRY UCMenuSetActionAttr(HWND hwndUCM, PSZ pszAction, USHORT usAttrMask, USHORT usAttrValue )
{
   SHORT sIndex = MIT_FIRST;
   sIndex =  UCMenuGetActionID( hwndUCM, pszAction, TRUE, sIndex );
   while ( sIndex != MIT_NONE ){
      WinSendMsg( hwndUCM, MM_SETITEMATTR, MPFROM2SHORT( sIndex, TRUE ), MPFROM2SHORT( usAttrMask, usAttrValue ) );
      sIndex =  UCMenuGetActionID( hwndUCM, pszAction, TRUE, sIndex );
   } // endwhile
}


//----------------------------------------------------------------------------
// UCMenuContextMenu : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CTXTMENU. name='UCMenuContextMenu' text='Popups the context menu' .
// This function popups the appropriate context menu accroding to the mouse location
// :syntax name='UCMenuContextMenu' params='hwndUCMenu, hwndMenu, FromMouse' return='-' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// UCMenu window handle.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='FromMouse' type='BOOL' io='input' .
// Tells wether the CM was initiated from the mouse or not
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuContextMenu(HWND hwndUCMenu, HWND hwndMenu, BOOL FromMouse)
{ POINTL   ptl;
  MENUITEM mi;
  HWND     PopupHwnd;
  PUCMDATA UCMData    = (PUCMDATA)WinQueryWindowULong(hwndUCMenu, QWL_UCMDATA);


  // --------------------------------------
  // -- First check if context menu allowed
  // --------------------------------------
  if ( UCMData->Style & UCS_NO_CM ) {
     return;
  } // endif

  // -------------------------------------------------------------
  // -- UCMData->hwndCMOrig will be used to send the MM_INSERTITEM
  // -- If we add an item in the menu, send it to hwndUCMenu
  // --  If we add an item in a submenu, send it to the submenu
  // -------------------------------------------------------------
  if (UCMData->hwndMenu==hwndMenu) {
     UCMData->hwndCMOrig = hwndUCMenu;
  } else {
     UCMData->hwndCMOrig = hwndMenu;
  } // endif

  // ----------------------------------------------------------------
  // -- Query the id of the item under the mouse & get menu item info
  // ----------------------------------------------------------------
  if (FromMouse) {
     WinQueryPointerPos(HWND_DESKTOP, &ptl);
     WinMapWindowPoints(HWND_DESKTOP, hwndMenu, &ptl, 1);
     UCMData->ContextID = UCMenuIdFromCoord(hwndMenu, &ptl);
     WinMapWindowPoints(hwndMenu, HWND_DESKTOP, &ptl, 1);
  } else {
     RECTL Rectl;
     ULONG SelectedItem = (ULONG)
              WinSendMsg(hwndMenu, MM_QUERYSELITEMID, 0L, 0L);
     WinSendMsg( hwndMenu, MM_QUERYITEMRECT, (MPARAM)SelectedItem, MPFROMP(&Rectl));
     ptl.x = Rectl.xLeft   + (Rectl.xRight - Rectl.xLeft)/2;
     ptl.y = Rectl.yBottom + (Rectl.yTop - Rectl.yBottom)/2;
     UCMData->ContextID = UCMenuIdFromCoord(hwndMenu, &ptl);
     WinMapWindowPoints(hwndMenu, HWND_DESKTOP, &ptl, 1);
  }
 
  memset(&mi, 0x00, sizeof(MENUITEM));  // set to all zeros if not over an item
  if (UCMData->ContextID != 0)
    WinSendMsg( hwndMenu, MM_QUERYITEM, MPFROM2SHORT( UCMData->ContextID, FALSE ), MPFROMP( &mi ));

  /* See if the application has a context menu for us to use. */
  UCMData->hwndUserCM = (HWND)WinSendMsg(UCMData->hwndOwner, WM_CONTROL,
                              MPFROM2SHORT(UCMData->UCMenuID, UCN_QRYCONTEXTHWND),
                              MPFROMP(&mi));
 
  if (UCMData->hwndUserCM == NULLHANDLE) {  // Use our built-in menu
    #if !defined(UCMUI)
    return;           // No app context menu, and we don't support it
    #else
    PopupHwnd = UCMData->hwndCM;
    // ---------------------------------------------------------------------------
    // -- But if we were  on a MIS_SPACER item we won't be able to edit anyway
    // ---------------------------------------------------------------------------
    if ( mi.afStyle & MIS_SPACER ) {
      WinEnableMenuItem( UCMData->hwndCM, IDM_UCM_EDIT,   FALSE );
    } else {
      WinEnableMenuItem( UCMData->hwndCM, IDM_UCM_EDIT,   TRUE );
    } // endif
    // ---------------------------------------------------------------------------
    // -- But if we were not on an item we won't be able to edit and delete anyway
    // ---------------------------------------------------------------------------
    if ( UCMData->ContextID == 0 ) {
      WinEnableMenuItem( UCMData->hwndCM, IDM_UCM_DELETE, FALSE );
      WinEnableMenuItem( UCMData->hwndCM, IDM_UCM_EDIT,   FALSE );
    } else {
      WinEnableMenuItem( UCMData->hwndCM, IDM_UCM_DELETE, TRUE );
    } // endif
    #endif // UCMUI
  }
  else PopupHwnd = UCMData->hwndUserCM;    // Use application menu

  // Disable bubble help until popup is dismissed (WM_MENUEND message
  // processed in HideWndProc).  Otherwise bubble can overlay
  // and will be corrupted by poup repainting.
  WinSendMsg(UCMData->hwndBubble, MSG_DISABLE_BUBBLE, 0L, 0L);

  // --------------------------------------------------------------
  // -- At last pop up the  context menu.  Messages from this menu
  // -- will be processed by the HideWndProc() procedure.
  // --------------------------------------------------------------
  WinPopupMenu(HWND_DESKTOP,
               WinQueryWindow(UCMData->hwndMenu, QW_PARENT), // Hide window is owner
               PopupHwnd,
               ptl.x,
               ptl.y,
               0,
               PU_MOUSEBUTTON1 | PU_MOUSEBUTTON2 | PU_KEYBOARD |
               PU_HCONSTRAIN | PU_VCONSTRAIN);
} // endif

// (MAM) Added following routine
//----------------------------------------------------------------------------
// UCAdjacentItemBlank : Not for users doc
//----------------------------------------------------------------------------
// This function will take a menu item and see if the adjacent (left/right)
// item has the MIS_SPACER attribute, or if the given item is at the start/end
// of the menu.  A TRUE/FALSE is returned (TRUE if the adjacent item is
// a spacer or there is no adjacent item).  Last parm (LeftRight) is -1 for
// left/above check, +1 for right/below check.  The given ID is assumed to
// exist in the given menu.
//----------------------------------------------------------------------------
 
BOOL _Optlink UCAdjacentItemBlank(HWND MenuHwnd, SHORT ItemID, int LeftRight)
{
  SHORT ItemPos;      /* Position of this item in the menu */
  SHORT AdjItemID;    /* ID of adjacent menu item (if one) */
  MENUITEM MenuItem;  /* Adjacent item data                */

  ItemPos = (SHORT)WinSendMsg(MenuHwnd, MM_ITEMPOSITIONFROMID, MPFROM2SHORT(ItemID, FALSE), 0L);
  AdjItemID = (SHORT)WinSendMsg(MenuHwnd, MM_ITEMIDFROMPOSITION, MPFROMSHORT(ItemPos+LeftRight), 0L);
  if (AdjItemID != MIT_ERROR) {
    /* Get info about adjacent menu item and examine style flags */
    WinSendMsg(MenuHwnd, MM_QUERYITEM, MPFROM2SHORT(AdjItemID, FALSE), MPFROMP(&MenuItem));
    if (!(MIS_SPACER & MenuItem.afStyle))
      return FALSE;   /* There is a non-blank adjacent item */
  }
  return TRUE;        /* No adjacent item, or adjacent item is MIS_SPACER */
}

//----------------------------------------------------------------------------
// UCMenuWndProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UCMWNDPROC. name='UCMenuWndProc' text='UCMenu window procedure'.
// Window procedure of the UCMenu class
// :syntax name='UCMenuWndProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// UCMenu window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :dl compact.
// :dt.:hp2.WM_INITMENU:ehp2.
// :dd.:hp2.A submenu is about to be shown : we subclass it :ehp2.
// :dt.:hp2.WM_MENUEND:ehp2.
// :dd.:hp2.A submenu is about to be destroyed : we un-subclass it :ehp2.
// :dt.:hp2.WM_VSCROLL:ehp2.
// :dd.:hp2.Vertical scrolling event :ehp2.
// :dt.:hp2.WM_HSCROLL:ehp2.
// :dd.:hp2.Horizontal scrolling event :ehp2.
// :dt.:hp2.WM_DRAWITEM:ehp2.
// :dd.:hp2.Draws any OWNERDRAW menu item :ehp2.
// :dt.:hp2.WM_MEASUREITEM:ehp2.
// :dd.:hp2.Returns the height of an OWNERDRAW item :ehp2.
// :edl.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY UCMenuWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  ULONG Style      = WinQueryWindowULong(hwnd, QWL_STYLE);
  PUCMDATA UCMData = (PUCMDATA) WinQueryWindowULong( hwnd, QWL_UCMDATA );

  switch (msg) {
     case WM_TRANSLATEACCEL:
          {
           //??? does this code work?
           //PACCELTABLE AccelTable;
             HWND        hwndMenu = UCMData->hwndMenu;
             PQMSG       QMsg = (PQMSG)mp1;
           //USHORT      VK  = SHORT2FROMMP(mp2);

             if(QMsg->msg == WM_CHAR) {
                USHORT flags = SHORT1FROMMP(QMsg->mp1);
                if(((flags & KC_CHAR)||!(flags & KC_VIRTUALKEY)) && (flags & KC_ALT) && !(flags & KC_PREVDOWN)) {
                   return (MRESULT) TranslateAccel(UCMData, hwndMenu, SHORT1FROMMP(QMsg->mp2), QMsg);
                }
             }
             return (MRESULT)0;
          }
     case WM_UPDATEFRAME:
          {
             if ( ( (ULONG)mp1 == FCF_MENU ) && UCMData->bProcessingPP ){
                // sent by the menu original wndproc after the processing of WM_PRESPARAMCHANGED
                UCMenuUpdateMenu( UCMData->hwndMenu, FALSE );
                UCMData->bProcessingPP = FALSE;
                return (MRESULT) TRUE;
             } else {
                return (MRESULT) FALSE;
             }
          }
     case UCMENU_ADDITEMSTOCM:
          {
            ULONG    i;
            MENUITEM MenuItem;
            ULONG    NbOfAdditionalCMItems = (ULONG)mp1;
            PCMITEMS CMItems = (PCMITEMS)mp2;
            memset(&MenuItem, 0, sizeof(MENUITEM));
            for(i=0; i<NbOfAdditionalCMItems; i++) {
               MenuItem.iPosition = MIT_END;
               MenuItem.id = (CMItems+i)->ID;
               MenuItem.afStyle = MIS_TEXT;
               WinSendMsg(UCMData->hwndCM, MM_INSERTITEM, MPFROMP(&MenuItem),
                          MPFROMP( (CMItems+i)->pszItemText ) );
            }
            return((MRESULT)0);
          }

     case UCMENU_DELETECMITEM:
          {
            ULONG    i;
            ULONG    NbOfItems = (ULONG)mp1;
            PULONG   ItemArray = (PULONG)mp2;
            for(i=0; i<NbOfItems; i++) {
               WinSendMsg(UCMData->hwndCM, MM_DELETEITEM, (MPARAM)ItemArray[i], 0L);
            }
            return (MRESULT)0;
          }
    case WM_PRESPARAMCHANGED:
          {
             UCMenuPresParamChanged(UCMData, hwnd, mp1 );
             return((MRESULT)0);
          }
     case UCMENU_QUERYSIZE:
         {
            if ( UCMData && mp1 && mp2 ){
               if (Style & CMS_MATRIX) {
                  //(MAM) changed to return real size based on actual number of
                  // rows and columns in use.
                  USHORT Count, Rows;
                  Count = (USHORT)WinSendMsg(hwnd, MM_QUERYITEMCOUNT, MPVOID, MPVOID);
                  * (ULONG*)mp1 = min(Count,UCMData->NbOfCols) * UCMData->MaxVerticalWidth    + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
                  Rows = Count / max(1,UCMData->NbOfCols);  // Full rows (don't div by zero!)
                  if ((Rows * UCMData->NbOfCols) < Count)   // Partial row?
                    Rows++;
                  * (ULONG*)mp2 = Rows * UCMData->MaxHorizontalHeight + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
               } // endif
               if ( Style & CMS_VERT ) {
                  * (ULONG*)mp1 = UCMData->MaxVerticalWidth + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
                  * (ULONG*)mp2 = UCMData->SumItemHeights   + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
               } // endif
               if ( Style & CMS_HORZ ) {
                  * (ULONG*)mp1 = UCMData->SumItemWidths       + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
                  * (ULONG*)mp2 = UCMData->MaxHorizontalHeight + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
               } // endif
               return (MRESULT)TRUE;
            } else {
               return (MRESULT)FALSE;
            } // endif
         }

    case UCMENU_QUERYCOLOR:
       {
          if ( UCMData && mp1 && mp2 ) {
             * (LONG*)mp1 = UCMData->BgColor;
             * (LONG*)mp2 = UCMData->ItemBgColor;
             return (MRESULT)TRUE;
          } else {
             return (MRESULT)FALSE;
          } // endif
       }

    case UCMENU_QUERYSTYLE:
       {
          if ( UCMData && mp1) {
             * (ULONG*)mp1 = UCMData->Style;
             return (MRESULT) TRUE;
          } else {
             return (MRESULT) FALSE;
          } // endif
      }

    case UCMENU_SETSTYLE:
       {
          if ( UCMData ) {
             /* If removing bubble-help, destroy bubble window */
             if ((UCMData->hwndBubble != NULLHANDLE) && !((ULONG)mp1 & UCS_BUBBLEHELP)) {
               WinDestroyWindow(UCMData->hwndBubble);
               UCMData->hwndBubble = NULLHANDLE;
            // UCMData->HoverCapture = FALSE;
               UCMData->HoverID = 0;
             }

             /* If adding bubble-help, create bubble window */
             if ((UCMData->hwndBubble == NULLHANDLE) && ((ULONG)mp1 & UCS_BUBBLEHELP))
               UCMenuCreateBubbleWindow(hwnd, UCMData);

             UCMData->Style = (ULONG)mp1;
             UCMData->cx    = SHORT1FROMMP(mp2);
             UCMData->cy    = SHORT2FROMMP(mp2);
             return (MRESULT) TRUE;
          } else {
             return (MRESULT) FALSE;
          } // endif
      }

    case UCMENU_SETBGCOLOR:
       {
          if ( UCMData ) {
             UCMData->BgColor      = (ULONG)mp1;
             UCMData->ItemBgColor  = (ULONG)mp2;
             WinSetPresParam( UCMData->hwndMenu,
                              PP_MENUBACKGROUNDCOLOR,
                              sizeof UCMData->ItemBgColor,
                              &(UCMData->ItemBgColor) );
             return (MRESULT) TRUE;
          } else {
             return (MRESULT) FALSE;
          } // endif
      }
    case UCMENU_SETFONT :
      {
         if ( mp1 && UCMData ){
            if ( WinSetPresParam( UCMData->hwndMenu, PP_FONTNAMESIZE, strlen( mp1 ) + 1, mp1 ) ){
               if ( UCMData->pszFontNameSize ) {
                  MyFree( UCMData->pszFontNameSize );
               } /* endif */
               UCMData->pszFontNameSize = MyMalloc( strlen( mp1 ) + 1 );
               if ( UCMData->pszFontNameSize ){
                  strcpy( UCMData->pszFontNameSize, mp1 );
               } /* endif */
               return (MRESULT)TRUE;
            } else {
               return (MRESULT)FALSE;
            } /* endif */
         } else {
            return (MRESULT)FALSE;
         } /* endif */
      }

    case UCMENU_SETBUBBLETIMERS: // Added V2.04
       {
          UCMData->BubbleDelay = LONGFROMMP(mp1);
          UCMData->BubbleRead  = LONGFROMMP(mp2);
          return 0;
       }
 
    case UCMENU_ACTIVECHG:  // Added V2.04
       {
          if (!(BOOL)SHORT1FROMMP(mp1)) {  // Becoming inactive
            /* When owning app becomes inactive we will close any open */
            /* submenu and deactivate the bubble help, if any.         */
            UCMData->Active = FALSE;
            if (UCMData->usItem != 0) {   // There is an open submenu, close it
               MENUITEM OpenItem;
               if ((BOOL)WinSendMsg(UCMData->hwndMenu,
                          MM_QUERYITEM,
                          MPFROM2SHORT(UCMData->usItem,TRUE),
                          MPFROMP(&OpenItem)))
                 WinSendMsg(OpenItem.hwndSubMenu, MM_ENDMENUMODE, MPFROMSHORT(TRUE), 0L);
            }
            if (UCMData->Style & UCS_BUBBLEHELP) {
          //  if (UCMData->HoverCapture)
          //    WinSetCapture(HWND_DESKTOP, NULLHANDLE);
          //  UCMData->HoverCapture = FALSE;
              UCMData->HoverID = 0;
              WinSendMsg(UCMData->hwndBubble,  // Deactivate bubble if showing
                          MSG_ITEMCHANGE, MPFROM2SHORT(0, TRUE), MPFROMHWND(hwnd));
            }
          }
          else {  // Becoming active
            /* When owning app becomes active, we fake a mouse message if the */
            /* pointer is over toolbar window to reactivate the bubble help.  */
            UCMData->Active = TRUE;
            if (UCMData->Style & UCS_BUBBLEHELP) {
              POINTL MousePos;
              WinQueryPointerPos((HAB)NULLHANDLE, &MousePos);
              WinMapWindowPoints(HWND_DESKTOP,UCMData->hwndMenu,&MousePos, 1);
              WinSendMsg(UCMData->hwndMenu, WM_MOUSEMOVE, MPFROM2SHORT((SHORT)MousePos.x,(SHORT)MousePos.y), MPFROM2SHORT(0,KC_NONE));
            }
          }
       } // end UCMENU_ACTIVECHG
       return 0;

    case UCMENU_UPDATE:
       {
          if ( UCMData ) {
             UCMenuUpdateMenu( UCMData->hwndMenu, TRUE );
             return (MRESULT) TRUE;
          } else {
             return (MRESULT) FALSE;
          } // endif
      }

    case UCMENU_DISABLEUPDATE:
      /* Set update disable status */
      UCMData->DisableUpdate = (BOOL)SHORT1FROMMP(mp1);
      return 0;

    case UCMENU_QUERYFORCEDSIZE:
       {
          if ( UCMData && mp1 && mp2 ) {
             * (ULONG*)mp1 = UCMData->cx;
             * (ULONG*)mp2 = UCMData->cy;
             return (MRESULT)TRUE;
          } else {
             return (MRESULT)FALSE;
          } // endif
      }

    case UCMENU_QUERYFONT:
       {
          if ( UCMData && UCMData->pszFontNameSize && mp1 ) {
             if ( (ULONG)mp2 > strlen( UCMData->pszFontNameSize) ) {
                strcpy( (CHAR *)mp1, UCMData->pszFontNameSize );
                return (MRESULT)TRUE;
             } else {
                return (MRESULT)FALSE;
             } // endif
          } else {
             return (MRESULT)FALSE;
          } // endif
       }

    case UCMENU_QUERYRECT:
       /* Return the bounding rectangle of the specified menu item, */
       /* relative to the UCMenu toolbar window.  mp1(short1) is    */
       /* the item ID, mp2 is ptr to RECTL.  Return TRUE if OK.     */

       /* See if item is on main menu */
       if ((BOOL) WinSendMsg(UCMData->hwndMenu, MM_QUERYITEMRECT, MPFROM2SHORT(SHORT1FROMMP(mp1), FALSE), MPFROMP((PRECTL)PVOIDFROMMP(mp2)))) {
         WinMapWindowPoints(UCMData->hwndMenu, hwnd, (POINTL *)PVOIDFROMMP(mp2), 2);
         return (MRESULT)TRUE;
       }
       /* If a submenu is currently open, try there */
       else if (UCMData->usItem != 0) {
         MENUITEM Item;
         if ((BOOL) WinSendMsg(hwnd, MM_QUERYITEM, MPFROM2SHORT(UCMData->usItem, TRUE), MPFROMP(&Item))) {
            if ((BOOL) WinSendMsg(Item.hwndSubMenu, MM_QUERYITEMRECT, MPFROM2SHORT(SHORT1FROMMP(mp1), FALSE), MPFROMP((PRECTL)PVOIDFROMMP(mp2)))) {
               WinMapWindowPoints(Item.hwndSubMenu, hwnd, (POINTL *)PVOIDFROMMP(mp2), 2);
               return (MRESULT)TRUE;
            }
         }
       }
       return (MRESULT)FALSE; // Not found.
 
    case UCMENU_QUERYUCMINFO:
       {
          if ( UCMData && mp1 ){
             PUCMINFO UCMInfo  = (PUCMINFO)mp1;

             UCMInfo->cb           = sizeof(UCMINFO);
             UCMInfo->hModule      = UCMData->hModBmp;
             UCMInfo->NbOfCols     = UCMData->NbOfCols;
             UCMInfo->NbOfRows     = UCMData->NbOfRows;
             UCMInfo->Style        = UCMData->Style;
             UCMInfo->cx           = UCMData->cx;
             UCMInfo->cy           = UCMData->cy;
             UCMInfo->BgBmp        = UCMData->BgBmp;
             UCMInfo->BgColor      = UCMData->BgColor;
             UCMInfo->ItemBgColor  = UCMData->ItemBgColor;
             UCMInfo->hModUCM      = UCMData->hModUCM;        // added V2.04
             UCMInfo->BubbleDelay  = UCMData->BubbleDelay;    // added V2.04 
             UCMInfo->BubbleRead   = UCMData->BubbleRead;     // added V2.04

             if ( *(UCMData->szBitmapSearchPath) &&
                  (UCMInfo->pszBitmapSearchPath = MyMalloc(strlen( UCMData->szBitmapSearchPath )+1)) ){
                strcpy( UCMInfo->pszBitmapSearchPath, UCMData->szBitmapSearchPath );
             } else {
                UCMInfo->pszBitmapSearchPath = NULL;
             } // endif

             if ( *(UCMData->szDefaultBitmap) &&
                  (UCMInfo->pszDefaultBitmap = MyMalloc(strlen( UCMData->szDefaultBitmap )+1)) ){
                strcpy( UCMInfo->pszDefaultBitmap, UCMData->szDefaultBitmap );
             } else {
                UCMInfo->pszDefaultBitmap = NULL;
             } // endif

             if ( UCMData->pszFontNameSize &&
                  (UCMInfo->pszFontNameSize = MyMalloc(strlen( UCMData->pszFontNameSize )+1)) ){
                strcpy( UCMInfo->pszFontNameSize, UCMData->pszFontNameSize );
             } else {
                UCMInfo->pszFontNameSize = NULL;
             } // endif

             return (MRESULT)TRUE;
          } else {
             return (MRESULT)FALSE;
          } // endif
       }

    case UCMENU_QUERYVERSION:
       {
          return (MRESULT)(ULONG)UCMENUS_VERSION;  // constant defined in ucmenus.h
       }

    case UCMENU_ACTIONSINSERTED:
      //-- This message is posted by the owner to let me know that
      //-- the list of actions was filled. What I have to do is hilite the
      //-- current action in the list or, if it's not in it, add it to the
      //-- list and highlight it.
      #if !defined(UCMUI)
        return 0;
      #else
        if (UCMData->hwndPage2)
          WinPostMsg(UCMData->hwndPage2,
                     UCMENU_ACTIONSINSERTED,
                     (MPARAM)0,
                     (MPARAM)0);
        return 0;
      #endif

    case UCMENU_INSERTACTION:
      #if !defined(UCMUI)
        return 0;
      #else
        WinSendDlgItemMsg(UCMData->hwndPage2,
                          IDC_UCMNBP2FLIST,
                          LM_INSERTITEM,
                          (MPARAM)LIT_END,
                          mp1);
        WinSendDlgItemMsg(UCMData->hwndPage2,
                          IDC_UCMNBP2DLIST,
                          LM_INSERTITEM,
                          (MPARAM)LIT_END,
                          mp2);
        return (MRESULT)0;
      #endif

    case WM_CONTEXTMENU:
      {

       UCMenuContextMenu(hwnd, UCMData->hwndMenu, (ULONG)mp1);
       return (MRESULT) TRUE;
      }

    case WM_CREATE:
      /*---------------------------------------------*/
      /*        Create code                          */
      /*---------------------------------------------*/
     { PCREATESTRUCT CreateParms = (PCREATESTRUCT)mp2;
       PUCMINFO2      UCMInfo     = (PUCMINFO2)mp1;
       RECTL         rcl;
       HPS           hps;
       HDC           hdcMem;


       // Test if the menu handle is valid
       if ( !WinIsWindow( WinQueryAnchorBlock( hwnd ), UCMInfo->hwndMenu ) ) {
          return (MRESULT)FALSE;
       } // endif

       // Allocate memory for UCMenu internal Data
       if(!(UCMData = MyMalloc(sizeof(UCMDATA)))) {
          return((MRESULT)1);
       }

       // Zero out memory
       memset(UCMData, 0, sizeof(UCMDATA));

       UCMData->size = sizeof( UCMDATA );

       WinSetWindowULong(hwnd, QWL_UCMDATA, (ULONG)UCMData);

       /* These are new in UCMDATA for V2.04 */
       UCMData->hwndUCM = hwnd;
       UCMData->hwndOwner = WinQueryWindow(hwnd, QW_OWNER);
       UCMData->UCMenuID = WinQueryWindowUShort(hwnd, QWS_ID);

       // -----------------------------------------------------------------------
       // -- Eventually create a memory device context to manipulate the bitmaps
       // -- We need that if we want to change their background color
       // -----------------------------------------------------------------------
       if (UCMInfo->Style & (UCS_CHNGBMPBG|UCS_CHNGBMPBG_AUTO))   {
         hdcMem = DevOpenDC( WinQueryAnchorBlock( hwnd ),
                             OD_MEMORY,
                             "*",
                             0L,
                             NULL,       // -- compatible with screen device
                             (ULONG)0 );
         if ( hdcMem ) {
            SIZEL sizlPS;

            sizlPS.cx = 0;
            sizlPS.cy = 0;
            UCMData->hpsMem = GpiCreatePS( WinQueryAnchorBlock( hwnd ),
                                           hdcMem,
                                           &sizlPS,
                                           PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC );

         } // endif
       } // endif

       //c1: Added following section to calculate bitmap inset
       // ----------------------------------------------------------------------------
       // Find out how far PM insets the arrow bitmaps inside the scrollbar window.
       // Up to Warp 3.0 it was always one pixel, but with Merlin the arrow bitmaps are
       // drawn 2 pixels inside the window edge.  There is no way to query this 
       // value directly, so instead we find out how big the horizontal arrow bitmap
       // is, and how big the horizontal scroll bar is.  The difference, divided by 2,
       // is the gutter between the window edge and the bitmap.  We now make the
       // assumptions: (1) the vertical and horizontal insets are the same, (2)
       // the insets are symetric (e.g. evenly divided between top and bottom), (3)
       // The insets are the same for the vertical and horizontal scrollbar controls.
       // This value is only calculated once and is used in UCMenuCheckScrolling().
       // -----------------------------------------------------------------------------

       {
         HBITMAP Hbmp;                    // Arrow bitmap handle
         BITMAPINFOHEADER2 BmpInfo;       // Bitmap header structure
       
         Hbmp = WinGetSysBitmap(HWND_DESKTOP, SBMP_SBRGARROW);  // Get horz arrow bitmap
         if (Hbmp != NULLHANDLE) {
           memset(&BmpInfo, 0x00, sizeof(BmpInfo));             // Query header data
           BmpInfo.cbFix = sizeof(BmpInfo);
           GpiQueryBitmapInfoHeader(Hbmp, &BmpInfo);
           // Inset is diff btw scrollbar size and bitmap size, but never negative
           UCMData->BmpInset = max(0L, (LONG)(((WinQuerySysValue(HWND_DESKTOP, SV_CYHSCROLL) - BmpInfo.cy) / 2) - 1));
         }
       }

       // Allocate memory for the accelerator table
       UCMData->AccelTable = (PACCELTABLE)MyMalloc(sizeof(ACCELTABLE)+(100*sizeof(ACCEL)));
       UCMData->AccelTable->codepage = 850;
       UCMData->AccelTable->cAccel   = 0;

       rcl.xLeft   = CreateParms->x;
       rcl.xRight  = CreateParms->x + CreateParms->cx;
       rcl.yTop    = CreateParms->y + CreateParms->cy;
       rcl.yBottom = CreateParms->y;

       if(UCMInfo->pszBitmapSearchPath) {
          strcpy(UCMData->szBitmapSearchPath, UCMInfo->pszBitmapSearchPath);
       }

       if(UCMInfo->pszDefaultBitmap) {
          strcpy(UCMData->szDefaultBitmap, UCMInfo->pszDefaultBitmap);
       }

       UCMData->NbOfRows = UCMInfo->NbOfRows;
       UCMData->NbOfCols = UCMInfo->NbOfCols;
       UCMData->Style    = UCMInfo->Style;
       UCMData->cx       = UCMInfo->cx;
       UCMData->cy       = UCMInfo->cy;
       // -----------------------------------------------------------------------
       // -- We want only solid colors, because the bitmap background can only be
       // -- solid, and we want it to match with everything we paint
       // -----------------------------------------------------------------------
       hps = WinGetPS( UCMInfo->hwndMenu );
       UCMData->BgBmp = UCMInfo->BgBmp;  // Background color in real bitmap can be anything
     //UCMData->BgBmp        = GpiQueryNearestColor( hps, (ULONG)0, UCMInfo->BgBmp );
       UCMData->BgColor      = GpiQueryNearestColor( hps, (ULONG)0, UCMInfo->BgColor );
       UCMData->ItemBgColor  = GpiQueryNearestColor( hps, (ULONG)0, UCMInfo->ItemBgColor );
       WinReleasePS( hps );

       UCMData->hwndMenu = UCMInfo->hwndMenu;

       // -----------------------------------------------------------------------
       // -- The WinSetPresParam causes a WM_UPDATEFRAME to be sent to the owner,
       // -- this will cause trouble if the owner is a WC_FRAME or if it is already
       // -- the ucmenu, -> set the owner temporarily to the desktop object window
       // -----------------------------------------------------------------------
       WinSetOwner (UCMInfo->hwndMenu, HWND_OBJECT);

       // -------------------------------------------------------------------------------------------
       // -- The presparam change has to be done before subclassing the menu, else it fails
       // -- (Here, we want to have PRESPARAMCHANGED processed by the default routines only,
       // -- since everything is not set up yet, especially the UCMData * in QWL_USER or QWL_UCMDATA)
       // -------------------------------------------------------------------------------------------
       if ( ! UCMInfo->pszFontNameSize ){
          UCMInfo->pszFontNameSize = MyMalloc( strlen( UCM_DEFAULTFONT ) + 1 );
          strcpy( UCMInfo->pszFontNameSize, UCM_DEFAULTFONT );
       }
       WinSetPresParam( UCMInfo->hwndMenu, PP_FONTNAMESIZE,
                        strlen(UCMInfo->pszFontNameSize) + 1,
                        UCMInfo->pszFontNameSize);


       if ( UCMData->pszFontNameSize = MyMalloc( strlen( UCMInfo->pszFontNameSize ) + 1 ) ){
          strcpy( UCMData->pszFontNameSize, UCMInfo->pszFontNameSize );
       }

       WinSetPresParam( UCMInfo->hwndMenu, PP_MENUBACKGROUNDCOLOR, sizeof UCMData->ItemBgColor, &(UCMData->ItemBgColor) );

       WinSetOwner (UCMInfo->hwndMenu, hwnd);

       UCMData->OldMenuProc = (PFNWP)WinSubclassWindow(UCMInfo->hwndMenu, (PFNWP)MenuWndProc);

       /* As of UCMenus V2.04, app must supply our module handle if we are  */
       /* in a DLL.  Otherwise we do our best to get it ourselves, but may  */
       /* not work if we are in a DLL loaded by full path name.             */

       UCMData->hModUCM = UCMInfo->hModUCM;
       if (UCMData->hModUCM == NULLHANDLE) {
         //--- Here we have to get the module name to load the resource
         PSZ pszModuleName = "UCMENUS";
         // ----------------------------------------------------------------
         // -- If we can not find ucmenus.dll then we use 0, this will work
         // -- if we are statically linked to an exe
         // ----------------------------------------------------------------
         if ( DosQueryModuleHandle(pszModuleName, &(UCMData->hModUCM)) ){
               UCMData->hModUCM = NULLHANDLE;
         } // endif
       } // endif

       UCMData->hModBmp = UCMInfo->hModule; // Application resources from this module
       UCMData->BubbleDelay = UCMInfo->BubbleDelay;
       UCMData->BubbleRead  = UCMInfo->BubbleRead;

       CreateUCMenu(hwnd,
                    CreateParms->hwndParent,
                    CreateParms->hwndOwner,
                    UCMInfo->hwndMenu,
                    CreateParms->id,
                    &rcl,
                    CreateParms->flStyle,
                    UCMInfo->NbOfCols,
                    UCMInfo->NbOfRows,
                    UCMInfo->ulTmplVersion);


       //-- Load the context menu
       UCMData->hwndCM = WinLoadMenu(HWND_OBJECT,   // was hwnd
                              UCMData->hModUCM,
                              IDD_UCMCTXT);
      WinGetLastError( WinQueryAnchorBlock( hwnd ) );

  // ------------------------------------------------------------
  // -- Set the context menu items according to the UCS_ flags
  // ------------------------------------------------------------
  if ( UCMData->Style & UCS_NO_CM_SEPARATOR ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_SEPARATOR, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_ITEM_CREATE ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_CREATE, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_ITEM_DELETE ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_DELETE, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_ITEM_EDIT ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_EDIT, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_MENU_STYLE ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_STYLE, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_MENU_DEFAULT ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_DEFAULT, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_MENU_IMPORT ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_LOAD, TRUE ), (MPARAM)0 );
  } // endif
  if ( UCMData->Style & UCS_NO_CM_MENU_EXPORT ){
     WinSendMsg( UCMData->hwndCM, MM_DELETEITEM, MPFROM2SHORT( IDM_UCM_SAVEAS, TRUE ), (MPARAM)0 );
  } // endif

  /* Create bubble help window if required by style */
 
  if (UCMData->Style & UCS_BUBBLEHELP)
    UCMenuCreateBubbleWindow(hwnd, UCMData);

  /* Try to determine if our app is currently the active window so */
  /* we can set our initial Active state correctly.  If the        */
  /* parent of the UCMenu is a child of the active window then     */
  /* our app is active.                                            */

  if (WinIsChild(WinQueryWindow(hwnd, QW_PARENT), WinQueryActiveWindow(HWND_DESKTOP)))
    UCMData->Active = TRUE;

  } break;  // end of WM_CREATE

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Menu messages ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    case WM_INITMENU:
      {
         /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
           ³ A submenu is about to be shown : we save the item Identifier of  ³
           ³ the currently open submenu.                                      ³
           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

         UCMData->usItem = (USHORT)mp1;
         WinPostMsg(UCMData->hwndOwner, msg, mp1, mp2);
      }
      break;

    case WM_MENUEND:
      {
         /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
           ³ A submenu is about to end : zero the submenu ID                  ³
           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
         mp2 = MPFROMHWND(hwnd);
         WinPostMsg(UCMData->hwndOwner, msg, mp1, mp2);
         UCMData->usItem = 0;
      }
      break;

    case WM_MEASUREITEM:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ We receive this message the first time an item with the OWNERDRAW      ³
        ³ style is about to be drawn. We have to set the item's height and width ³
        ³ In submenus, we have to decrease xRight by DELTA because of the space  ³
        ³ left by PM for the arrow and check item.  PM docs (2.1) indicate only  ³
        ³ the height is required, but we set both width and height in the item   ³
        ³ rectangle structure and return the height in the message result.       ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      { POWNERITEM        pitem;
        BITMAPINFOHEADER2 BmpInfo;
        SHORT             delta=0;
        ULONG             cx, cy;

        pitem = (POWNERITEM)mp2;
        BmpInfo.cbFix = sizeof(BITMAPINFOHEADER2);
        UCMenuCalcItemSize( pitem, UCMData->Style, hwnd, &cx, &cy );

        if ( WinQueryWindow(pitem->hwnd, QW_OWNER) != hwnd ) {
          // -- This is a submenu item and not a menu item
          HBITMAP hbm;

          hbm = WinGetSysBitmap(HWND_DESKTOP, SBMP_MENUCHECK);
          GpiQueryBitmapInfoHeader(hbm, &BmpInfo);
          delta += BmpInfo.cx;
          GpiDeleteBitmap(hbm);

          hbm = WinGetSysBitmap(HWND_DESKTOP, SBMP_MENUATTACHED);
          GpiQueryBitmapInfoHeader(hbm, &BmpInfo);
          delta += BmpInfo.cx;
          GpiDeleteBitmap(hbm);
        } // endif

        // In the submenus, PM will add some space for the checkmark&arrow : - delta
        //  (We don't want unnecessary space around the non checkable items)
        pitem->rclItem.xLeft   = 0;
        pitem->rclItem.yBottom = 0;
        pitem->rclItem.xRight  = cx  - delta ;
        pitem->rclItem.yTop    = cy  ;

        return MRFROMSHORT((SHORT)cy); // Return height of menu item
      } 

    case WM_DRAWITEM:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ We receive this message when we have to draw an item with ³
        ³ the OWNERDRAW style                                       ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
       {
        POWNERITEM        poi;
        PSZ               pszText;
        POINTL            aptlPoints[4];
        ULONG             TextHeight, TextWidth;
        ULONG             ItemBgColorIndex;
        ULONG             BgColorIndex;
        ULONG flOptions;
        HPS hps;

        poi = (POWNERITEM)mp2;

        /* Presentation space given in owner-draw structure does not */
        /* render larger fonts correctly (not sure why).  So we get  */
        /* our own pres space instead to use for the drawing.        */

        hps = WinGetPS(poi->hwnd);       //@P1a

        ItemBgColorIndex = UCMenuSelectColor( UCMData->ItemBgColor, hps ); //@P1m
        BgColorIndex = UCMenuSelectColor( UCMData->BgColor, hps );         //@P1m

        if (poi->fsState & MIS_SPACER) {
           /*------------- Draw spacer items -----------------------*/

           WinFillRect(hps, &poi->rclItem, BgColorIndex);
           if ( UCMData->Style & UCS_FRAMED ){
              POINTL pt;
              if ( Style & CMS_HORZ ){
                 // (MAM) Don't draw edges adjacent to other MIS_SPACER items
                 if (!UCAdjacentItemBlank(hwnd, poi->idItem, ADJACENT_LEFT)) {
                   pt.x = poi->rclItem.xLeft;
                   pt.y = poi->rclItem.yBottom ;
                   GpiMove( hps, &pt );
                   pt.y  = poi->rclItem.yTop - 1;
                   GpiSetColor( hps, SYSCLR_BUTTONDARK );
                   GpiLine( hps, &pt );
                 }
                 if (!UCAdjacentItemBlank(hwnd, poi->idItem, ADJACENT_RIGHT)) {
                   pt.x = poi->rclItem.xRight - 1;
                   pt.y = poi->rclItem.yBottom;
                   GpiMove( hps, &pt );
                   pt.y  = poi->rclItem.yTop - 1;
                   GpiSetColor( hps, SYSCLR_BUTTONLIGHT );
                   GpiLine( hps, &pt );
                 }
              } else if ( Style & CMS_VERT ){
                 // (MAM) Don't draw edges adjacent to other MIS_SPACER items
                 if (!UCAdjacentItemBlank(hwnd, poi->idItem, ADJACENT_ABOVE)) {
                   pt.x = poi->rclItem.xLeft;
                   pt.y = poi->rclItem.yBottom ;
                   GpiMove( hps, &pt );
                   pt.x  = poi->rclItem.xRight - 1;
                   GpiSetColor( hps, SYSCLR_BUTTONLIGHT );
                   GpiLine( hps, &pt );
                 }
                 if (!UCAdjacentItemBlank(hwnd, poi->idItem, ADJACENT_BELOW)) {
                   pt.x = poi->rclItem.xLeft;
                   pt.y = poi->rclItem.yTop - 1 ;
                   GpiMove( hps, &pt );
                   pt.x  = poi->rclItem.xRight - 1;
                   GpiSetColor( hps, SYSCLR_BUTTONDARK );
                   GpiLine( hps, &pt );
                 }
              } else if (Style & CMS_MATRIX ){
                 UCMenu3DFrame( hps, &poi->rclItem, 1);
              } // endif
           } // endif
           if (poi->fsAttribute != poi->fsAttributeOld) {
              poi->fsAttributeOld = (poi->fsAttribute &= (USHORT)~MIA_HILITED);
           } // endif
           WinReleasePS(hps);
           return (MRESULT)TRUE;
        } // endif

        if ( !poi->hItem ){
           WinReleasePS(hps);
           return (MRESULT)FALSE;
        } // endif

        /*---------------- Non-SPACER item to be drawn ------------------*/

        /* Note we completely redraw the item on all WM_DRAWITEM messages */
        /* even if only a state change.  Our state drawings require       */
        /* repainting to change states.                                   */

        WinFillRect(hps, &poi->rclItem, ItemBgColorIndex);

        /* Draw the bitmap into the drawing rectangle.  For hilight state */
        /* we draw it 1 pixel down and right of the usual position.       */

        UCMenuCalcBmpPos( poi, hwnd, UCMData->Style, aptlPoints, UCMData );

        if (poi->fsAttribute & MIA_HILITED) {
          aptlPoints[0].x++;
          aptlPoints[1].x++;
          aptlPoints[0].y--;
          aptlPoints[1].y--;
        }

        if ( !(UCMData->Style&UCS_SHRINK_BLEND)) {
           flOptions = BBO_IGNORE;
        } else {
           flOptions = UCMData->Style&UCS_SHRINK_OR ? BBO_OR : BBO_AND;
        } // endif

        GpiWCBitBlt( hps,
                     ITEM(poi, hBmp),
                     4,
                     aptlPoints,
                     ROP_SRCCOPY,
                     flOptions );

        /* Now draw the text, also down/right in hilight state */

        UCMenuCalcTextSize( (PUCMITEM) poi->hItem, hwnd, &TextWidth, &TextHeight);

        pszText = ITEM(poi, pszText);
        if (pszText && !(UCMData->Style & UCS_NOTEXT)) {
           RECTL rect;
           GpiSetColor(hps, SYSCLR_MENUTEXT);

           rect.xLeft   = poi->rclItem.xLeft   + ITEM_FRAME_THICK_LEFT;
           rect.xRight  = poi->rclItem.xRight  - ITEM_FRAME_THICK_RIGHT;
           rect.yBottom = poi->rclItem.yBottom + ITEM_FRAME_THICK_BOTTOM;
           rect.yTop    = rect.yBottom + TextHeight;
           if (poi->fsAttribute & MIA_HILITED) {
             rect.xLeft++;   // adjust target of text
             rect.xRight++;
             rect.yBottom--;
             rect.yTop--;
           }
           WinDrawText(hps, -1, pszText, &rect, 0, 0,
                       DT_CENTER | DT_VCENTER | DT_TEXTATTRS | DT_MNEMONIC);
        } // endif

        /* For checked state, draw thick border */

        if (  ( poi->fsAttribute & MIA_CHECKED ) ) {
           // Make it 1 pel thicker than frame to keep visible when HILITED
           WinDrawBorder( hps,
                          &(poi->rclItem),
                          ITEM_FRAME_THICK_LEFT+1,
                          ITEM_FRAME_THICK_TOP+1,
                          CLR_BLACK, CLR_BLACK,
                          DB_PATCOPY);
        } // endif

        /* Draw a frame  around the item or erase any hilight frame if the */
        /* style bits indicate items are not to be framed.                 */

        if (UCMData->Style & UCS_FRAMED)
           UCMenu3DFrame( hps,& poi->rclItem, poi->fsAttribute & MIA_HILITED);
        else {
           if (poi->fsAttribute & MIA_HILITED)  // Always draw depressed hilite frame
             UCMenu3DFrame(hps, &poi->rclItem, TRUE);
           else
             WinDrawBorder( hps,                // Erase any frame
                          &(poi->rclItem),
                          1L, 1L,
                          ItemBgColorIndex, ItemBgColorIndex,
                          DB_PATCOPY);
             }

        /* If item is disabled, shade the area with a half-tone background    */
        /* color pattern.  Note that PM also does this under some conditions, */
        /* but not when we redraw the item due to a state change.  PM does    */
        /* not seem to honor our clearing of the MIA_DISABLED bits (PM bug?)  */
        /* In general we cannot predict when PM will or will not provide the  */
        /* disable half-tone, so we always do it ourselves.                   */

        if (poi->fsAttribute & MIA_DISABLED) {
          POINTL BoxCorner;
          GpiSetPattern(hps, PATSYM_HALFTONE);  // Setup background halftone pattern
          GpiSetColor(hps, ItemBgColorIndex);
          GpiBeginArea(hps, BA_NOBOUNDARY);
          BoxCorner.x = poi->rclItem.xLeft+1;   // Don't halftone the frame
          BoxCorner.y = poi->rclItem.yBottom+1;
          GpiMove(hps, &BoxCorner);
          BoxCorner.x = poi->rclItem.xRight-2;  // Border pixel included, and 1 for frame
          BoxCorner.y = poi->rclItem.yTop-2;
          GpiBox(hps, DRO_OUTLINE, &BoxCorner, 0L, 0L);
          GpiEndArea(hps);
        }
  
         /* Clear all attribute bits since we do all rendering of attributes */
         /* and we don't want PM do modify our drawing.  PM seems to not     */
         /* honor this for MIA_DISABLED (see above).                         */

         poi->fsAttribute    = poi->fsAttribute    & ~(MIA_CHECKED|MIA_HILITED|MIA_FRAMED|MIA_DISABLED);
         poi->fsAttributeOld = poi->fsAttributeOld & ~(MIA_CHECKED|MIA_HILITED|MIA_FRAMED|MIA_DISABLED);

         WinReleasePS(hps);
         return (MRESULT)TRUE; /* TRUE means the item is drawn. */

      } // end of WM_DRAWITEM

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
        default:
          if ( SHORT1FROMMP( mp2 ) == CMDSRC_MENU ){
            MENUITEM mi;
            BOOL bButton2Down=0;
            LONG ButtonState;
   
            WinSendMsg(UCMData->hwndMenu,
                       MM_QUERYITEM,
                       MPFROM2SHORT(SHORT1FROMMP(mp1), TRUE),
                       MPFROMP(&mi));
   
            ButtonState = WinGetPhysKeyState(HWND_DESKTOP, VK_BUTTON2);
            if(ButtonState & 0x8000) {
              bButton2Down = 1;
            }
   
            /* (MAM)Dismiss any open submenu unless this item has MIA_NODISMISS attribute */
            /* since we force all submenus to be globally NODISMISS.                      */
            if ((!(mi.afAttribute & MIA_NODISMISS)) && (!bButton2Down))
              WinSendMsg(UCMData->hwndMenu, MM_ENDMENUMODE, MPFROMSHORT(TRUE), 0L);
   
            if ( !( UCMData->Style & UCS_NODEFAULTACTION ) &&
                 !bButton2Down &&
                 mi.hItem &&
                 ITEM( &mi, pszAction ) &&
                 strstr( ITEM( &mi, pszAction ), UCM_ACTION_EXEC ) == ITEM( &mi, pszAction ) ){
              PSZ pszParams = ITEM( &mi, pszParameters );
              PSZ pszParams2;
              if ( pszParams ){
                 PSZ const pszCmd = "CMD.EXE /K ";
                 TID tid;
                 pszParams += strspn( pszParams, " \t" );
                 pszParams2 = MyMalloc( strlen( pszParams ) + strlen( pszCmd ) + 1 );
                 if ( pszParams2 ) {
                    char * cmdext;
                    char * firstspace;
                    strcpy( pszParams2, pszParams );
                    strupr( pszParams2 );
                    cmdext = strstr( pszParams2, ".CMD" );
                    firstspace = strpbrk( pszParams2, " \t" );
                    if ( cmdext && ( !firstspace || ( firstspace > cmdext ) ) ){
                       strcpy( pszParams2, pszCmd );
                    } else {
                       *pszParams2 = '\0';
                    } // endif
                    strcat( pszParams2, pszParams );
                 } // endif
                 // pszParams2 will be freed by UCMenuExecuteProgram
                 DosCreateThread(&tid, (PFNTHREAD)UCMenuExecuteProgram, (ULONG)pszParams2, 0, 4096) ;
              } // endif
            } else {
              if (!bButton2Down) {
                 UCMITEM ucmi;
    
                 memset( &ucmi, '\0', sizeof( UCMITEM ) );
                 ucmi = *((PUCMITEM)( mi.hItem ) );
                 if ( ITEM( &mi, pszBmp ) ){
                    ucmi.pszBmp = MyStrdup( ITEM( &mi, pszBmp ) );
                 } // endif
                 if ( ITEM( &mi, pszText ) ){
                    ucmi.pszText = MyStrdup( ITEM( &mi, pszText ) );
                 } // endif
                 if ( ITEM( &mi, pszAction ) ){
                    ucmi.pszAction = MyStrdup( ITEM( &mi, pszAction ) );
                 } // endif
                 if ( ITEM( &mi, pszParameters ) ){
                    ucmi.pszParameters = MyStrdup( ITEM( &mi, pszParameters ) );
                 } // endif
                 if ( ITEM( &mi, pszData ) ){
                    ucmi.pszData = MyStrdup( ITEM( &mi, pszData ) );
                 } // endif
    
                 ucmi.usId = (USHORT)mp1;
    
                 WinSendMsg( UCMData->hwndOwner, WM_CONTROL,
                             MPFROM2SHORT(UCMData->UCMenuID, UCN_ITEMSELECTED ),
                             MPFROMP( &ucmi ) );
                 if ( ucmi.pszBmp ){
                    MyFree( ucmi.pszBmp );
                 } // endif
                 if ( ucmi.pszText ){
                    MyFree( ucmi.pszText );
                 } // endif
                 if ( ucmi.pszAction ){
                    MyFree( ucmi.pszAction );
                 } // endif
                 if ( ucmi.pszParameters ){
                    MyFree( ucmi.pszParameters );
                 } // endif
                 if ( ucmi.pszData ){
                    MyFree( ucmi.pszData );
                 } // endif
              } // endif
            } /* endif */
   
          } /* endif */
          break;
      } /* endswitch */
      break;

    case WM_HELP:
      mp1 = MPFROM2SHORT( SHORT1FROMMP(mp1), (USHORT)(UCMData->UCMenuID) );
      mp2 = MPFROM2SHORT( CMDSRC_UCMENU, SHORT2FROMMP(mp2) );
      WinPostMsg(UCMData->hwndOwner, msg, mp1, mp2);
      break;

    case WM_NEXTMENU:
      return WinSendMsg(UCMData->hwndOwner, msg, mp1, mp2);

    case WM_MENUSELECT:
      mp2 = MPFROMHWND(hwnd);
      WinPostMsg(UCMData->hwndOwner, msg, mp1, mp2);
      return (MRESULT)TRUE;

    case MM_INSERTITEM:
    case MM_SETITEM:
       {
          PMENUITEM pMi;
          MRESULT rc;
          USHORT  NotifyMsg;

          if ( msg == MM_INSERTITEM ) {
             pMi = (PMENUITEM)mp1;
          } else {
             pMi = (PMENUITEM)mp2;
          } // endif

          if ( pMi->hwndSubMenu ){

             // -- When we insert a submenu, we have to make sure that the submenu window
             // --  is associated with the right id and UCMData (in case it comes from another
             // --  UCMenu)
             PUCMDATA UCMDataSub = (PUCMDATA)WinQueryWindowULong( pMi->hwndSubMenu, QWL_USER );

             if ( !UCMDataSub || ( UCMDataSub != UCMData ) ){
                PFNWP pFnwp;
                pFnwp = (PFNWP)WinQueryWindowPtr( pMi->hwndSubMenu, QWP_PFNWP );
                if ( pFnwp != SubmenuWndProc ){
                   UCMData->OldSubMenuProc = pFnwp;
                } else if ( UCMDataSub ){
                   UCMData->OldSubMenuProc = UCMDataSub->OldSubMenuProc;
                } // endif
                WinSetWindowULong(  pMi->hwndSubMenu, QWL_USER, (ULONG)UCMData);
                WinSetWindowUShort( pMi->hwndSubMenu, QWS_ID,   pMi->id);
                WinSetOwner( pMi->hwndSubMenu, UCMData->hwndMenu );
                // PRESPARAMCHANGED has to be processed by the original wnd proc
                WinSubclassWindow( pMi->hwndSubMenu, UCMData->OldSubMenuProc );
                WinSetPresParam( pMi->hwndSubMenu, PP_MENUBACKGROUNDCOLOR, sizeof UCMData->ItemBgColor, &(UCMData->ItemBgColor) );
                WinSetPresParam( pMi->hwndSubMenu, PP_FONTNAMESIZE,
                                 strlen( UCMData->pszFontNameSize ) + 1, UCMData->pszFontNameSize );
                WinSubclassWindow( pMi->hwndSubMenu, SubmenuWndProc );
                // The parent is the desktop, so it doesn't change
             } // endif
          } // endif

          if (UCMData->usItem != 0) {   //(MAM) There is an open submenu, close it
             MENUITEM OpenItem;
             if ((BOOL)WinSendMsg(UCMData->hwndMenu,
                        MM_QUERYITEM,
                        MPFROM2SHORT(UCMData->usItem,TRUE),
                        MPFROMP(&OpenItem)))
               WinSendMsg(OpenItem.hwndSubMenu, MM_ENDMENUMODE, MPFROMSHORT(TRUE), 0L);
          }
       
          rc = SEND_TO_MENU;

          UCMenuUpdateMenu( UCMData->hwndMenu, FALSE );

          /* Tell owner of change */
          if ( msg == MM_INSERTITEM )
            NotifyMsg = UCN_ADDEDITEM;
          else
            NotifyMsg = UCN_CHANGEDITEM;
          WinSendMsg( UCMData->hwndOwner,
                      WM_CONTROL,
                      MPFROM2SHORT(UCMData->UCMenuID, NotifyMsg ),
                      MPFROMSHORT(pMi->id));

          return rc;
       }

    //(MAM) Removed fall-through of case from above.

    case MM_DELETEITEM:
    case MM_REMOVEITEM:
    case MM_SETITEMHANDLE:
      { MRESULT rc;
        MENUITEM mi;
        USHORT  NotifyMsg;

        if (UCMData->usItem != 0) {   //(MAM) There is an open submenu, close it
           MENUITEM OpenItem;
           if ((BOOL)WinSendMsg(UCMData->hwndMenu,
                      MM_QUERYITEM,
                      MPFROM2SHORT(UCMData->usItem,TRUE),
                      MPFROMP(&OpenItem)))
             WinSendMsg(OpenItem.hwndSubMenu, MM_ENDMENUMODE, MPFROMSHORT(TRUE), 0L);
        }

        //(MAM) Don't process delete on submenus here -- submenu window proc will do it.
        if (!(BOOL)WinSendMsg(UCMData->hwndMenu, MM_QUERYITEM, MPFROM2SHORT(SHORT1FROMMP(mp1),FALSE), MPFROMP(&mi)))
          return SEND_TO_MENU;
 
        if ( msg == MM_DELETEITEM ) {
           if ( mi.hItem ){
              if ( ITEM( &mi, pszBmp ) ){
                MyFree( ITEM( &mi, pszBmp ) );
              }
              if ( ITEM( &mi, pszText ) ){
                MyFree( ITEM( &mi, pszText ) );
              }
              if ( ITEM( &mi, pszAction ) ){
                MyFree( ITEM( &mi, pszAction ) );
              }
              if ( ITEM( &mi, pszData ) ){
                MyFree( ITEM( &mi, pszData ) );
              }
              if ( ITEM( &mi, pszParameters ) ){
                MyFree( ITEM( &mi, pszParameters ) );
              }
              if ( ITEM( &mi, hBmp ) ){
                GpiDeleteBitmap( ITEM( &mi, hBmp ) );
              }
              MyFree( (PVOID)mi.hItem );
              if ( mi.hwndSubMenu ){
                 UCMenuFreeMenuData( mi.hwndSubMenu );
              } // endif
           } // endif
        } // endif

        rc = SEND_TO_MENU;

        //(MAM) Moved outside above IF so owner is notified of DELETE or REMOVEs
       
        if ((msg==MM_DELETEITEM) || (msg==MM_REMOVEITEM))
          NotifyMsg = UCN_DELETEDITEM;
        else
          NotifyMsg = UCN_CHANGEDITEM;
        WinSendMsg(UCMData->hwndOwner,
                   WM_CONTROL,
                   MPFROM2SHORT(UCMData->UCMenuID, NotifyMsg ),
                   MPFROMSHORT( SHORT1FROMMP( mp1 ) ) );

        UCMenuUpdateMenu( UCMData->hwndMenu, FALSE );

        return rc;
      }

    case MM_SETITEMATTR:
    case MM_ENDMENUMODE:
    case MM_ISITEMVALID:
    case MM_ITEMIDFROMPOSITION:
    case MM_ITEMPOSITIONFROMID:
    case MM_QUERYITEM:
    case MM_QUERYITEMATTR:
    case MM_QUERYITEMCOUNT:
    case MM_QUERYITEMRECT:
    case MM_QUERYSELITEMID:
    case MM_SELECTITEM:
    case WM_QUERYCONVERTPOS:
    case WM_SETWINDOWPARAMS:
    case WM_QUERYWINDOWPARAMS:
      return SEND_TO_MENU;

    case MM_STARTMENUMODE:
      return POST_TO_MENU;

    case MM_QUERYITEMTEXTLENGTH:
      { MENUITEM mi;

        WinSendMsg(UCMData->hwndMenu,
                   MM_QUERYITEM,
                   MPFROM2SHORT((SHORT)mp1, TRUE),
                   MPFROMP(&mi));

        if ( ! ( mi.afStyle & MIS_OWNERDRAW ) ) {
          return SEND_TO_MENU;
        } else {
          if (mi.hItem && ITEM(&mi, pszText))
            return (MPARAM)strlen(ITEM(&mi, pszText));
          else
            return (MPARAM)0;
        } // endif
      }

    case MM_QUERYITEMTEXT:
      { MENUITEM mi;

        if (!SHORT2FROMMP(mp1) || !mp2) {
          return FALSE;
        } // endif
        WinSendMsg(UCMData->hwndMenu,
                   MM_QUERYITEM,
                   MPFROM2SHORT((SHORT)mp1, TRUE),
                   MPFROMP(&mi));

        if ( ! ( mi.afStyle & MIS_OWNERDRAW ) ) {
          return SEND_TO_MENU;
        } else {
          PSZ pszText;

          if (mi.hItem && (pszText = ITEM(&mi, pszText))) {
            strncpy((PSZ)mp2, pszText, SHORT2FROMMP(mp1));
            pszText[SHORT2FROMMP(mp1)]='\0';
            return (MRESULT)strlen(pszText);
          } else {
            return (MRESULT)0;
          } /* endif */
        } /* endif */
      }

    case MM_SETITEMTEXT:
      { MENUITEM mi;

        WinSendMsg(UCMData->hwndMenu,
                   MM_QUERYITEM,
                   MPFROM2SHORT((SHORT)mp1, TRUE),
                   MPFROMP(&mi));

        if ( ! ( mi.afStyle & MIS_OWNERDRAW ) ) {
          return SEND_TO_MENU;
        } else {
          if (mi.hItem) {
            PSZ pszText = ITEM(&mi, pszText);

            if (pszText)
              MyFree(pszText);
            pszText = MyMalloc(strlen((PSZ)mp2)+1);
            strcpy(pszText, (PSZ)mp2);
            ITEM(&mi, pszText) = pszText;
            WinSendMsg( UCMData->hwndOwner,
                    WM_CONTROL,
                    MPFROM2SHORT(UCMData->UCMenuID, UCN_TEXT ),
                    MPFROMSHORT( mi.id ) );
            UCMenuUpdateMenu( UCMData->hwndMenu, TRUE );
            return (MRESULT)TRUE;
          } else {
            return (MRESULT)FALSE;
          } /* endif */
        } /* endif */
      }

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Scrolling messages ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    case WM_VSCROLL:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Vertical Scroll message ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      switch (SHORT2FROMMP(mp2)) {
        case SB_LINEDOWN:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ SB_LINEDOWN : We query the first item height and use it to ³
            ³ scroll the menu up                                         ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          { SWP swp;
            SHORT SliderPos;
            SHORT MaxPos;
            LONG  deltay;

            WinQueryWindowPos(UCMData->hwndHide, &swp );

            deltay = ( swp.cy - SUM_MENU_FRAME_THICK ) / 2;

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Query the scrollbar range and position ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            MaxPos = SHORT2FROMMP(WinSendMsg(UCMData->hwndScroll,
                                             SBM_QUERYRANGE,
                                             (MPARAM)0,
                                             (MPARAM)0));
            SliderPos = (SHORT)WinSendMsg(UCMData->hwndScroll,
                                          SBM_QUERYPOS,
                                          (MPARAM)0,
                                          (MPARAM)0);

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Set the new position : don't scroll beyond the maximum ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            if (SliderPos + deltay > MaxPos) {
              deltay -= SliderPos + deltay - MaxPos;
            } /* endif */

            WinPostMsg(UCMData->hwndScroll,
                       SBM_SETPOS,
                       MPFROMSHORT(SliderPos + deltay),
                       (MPARAM)0);

            WinQueryWindowPos(UCMData->hwndMenu, &swp);
            WinSetWindowPos(UCMData->hwndMenu,
                            HWND_TOP,
                            swp.x,
                            swp.y + deltay,
                            0,
                            0,
                            SWP_MOVE|SWP_SHOW);
          } break;

        case SB_LINEUP:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ SB_LINEUP : We query the first item height and use it to   ³
            ³ scroll the menu down                                       ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          { SWP   swp;
            SHORT SliderPos;
            SHORT MinPos;
            LONG  deltay;

            WinQueryWindowPos( UCMData->hwndHide, &swp );

            deltay = ( swp.cy - SUM_MENU_FRAME_THICK ) / 2;

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Query the scrollbar range and position ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            MinPos = SHORT1FROMMP(WinSendMsg(UCMData->hwndScroll,
                                             SBM_QUERYRANGE,
                                             (MPARAM)0,
                                             (MPARAM)0));
            SliderPos = (SHORT)WinSendMsg(UCMData->hwndScroll,
                                          SBM_QUERYPOS,
                                          (MPARAM)0,
                                          (MPARAM)0);

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Set the new position : don't scroll < the minimum ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            if (SliderPos - deltay < MinPos) {
              deltay -= MinPos - SliderPos + deltay;
            } /* endif */

            WinPostMsg(UCMData->hwndScroll,
                       SBM_SETPOS,
                       MPFROMSHORT(SliderPos - deltay),
                       (MPARAM)0);

            WinQueryWindowPos(UCMData->hwndMenu, &swp);
            WinSetWindowPos(UCMData->hwndMenu,
                            HWND_TOP,
                            swp.x,
                            swp.y - deltay,
                            0,
                            0,
                            SWP_MOVE|SWP_SHOW);
          } break;
      } /* endswitch */
      break;

    case WM_HSCROLL:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Horizontal Scroll message ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      switch (SHORT2FROMMP(mp2)) {
        case SB_LINERIGHT:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ SB_LINERIGHT: We query the first item width and use it to  ³
            ³ scroll the menu to the left                                ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          { SWP swp;
            SHORT SliderPos;
            SHORT MaxPos;
            LONG  deltax;

            WinQueryWindowPos( UCMData->hwndHide, &swp );

            deltax = ( swp.cx - SUM_MENU_FRAME_THICK ) / 2;

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Query the scrollbar range and position ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            MaxPos = SHORT2FROMMP(WinSendMsg(UCMData->hwndScroll,
                                             SBM_QUERYRANGE,
                                             (MPARAM)0,
                                             (MPARAM)0));
            SliderPos = (SHORT)WinSendMsg(UCMData->hwndScroll,
                                          SBM_QUERYPOS,
                                          (MPARAM)0,
                                          (MPARAM)0);

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Set the new position : don't scroll beyond the maximum ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            if (SliderPos + deltax > MaxPos) {
              deltax -= SliderPos + deltax - MaxPos;
            } /* endif */

            WinPostMsg(UCMData->hwndScroll,
                       SBM_SETPOS,
                       MPFROMSHORT(SliderPos + deltax),
                       (MPARAM)0);

            WinQueryWindowPos(UCMData->hwndMenu, &swp);
            WinSetWindowPos(UCMData->hwndMenu,
                            HWND_TOP,
                            swp.x - deltax,
                            swp.y,
                            0,
                            0,
                            SWP_MOVE|SWP_SHOW);
          } break;

        case SB_LINELEFT:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ SB_LINELEFT: We query the first item width  and use it to  ³
            ³ scroll the menu right                                      ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          { SWP   swp;
            SHORT SliderPos;
            SHORT MinPos;
            LONG  deltax;

            WinQueryWindowPos( UCMData->hwndHide, &swp );

            deltax = ( swp.cx - SUM_MENU_FRAME_THICK ) / 2;

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Query the scrollbar range and position ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            MinPos = SHORT1FROMMP(WinSendMsg(UCMData->hwndScroll,
                                             SBM_QUERYRANGE,
                                             (MPARAM)0,
                                             (MPARAM)0));
            SliderPos = (SHORT)WinSendMsg(UCMData->hwndScroll,
                                          SBM_QUERYPOS,
                                          (MPARAM)0,
                                          (MPARAM)0);

            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Set the new position : don't scroll beyond the minimum ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
            if (SliderPos - deltax < MinPos) {
              deltax -= MinPos - SliderPos + deltax;
            } /* endif */

            WinPostMsg(UCMData->hwndScroll,
                       SBM_SETPOS,
                       MPFROMSHORT(SliderPos - deltax),
                       (MPARAM)0);

            WinQueryWindowPos(UCMData->hwndMenu, &swp);
            WinSetWindowPos(UCMData->hwndMenu,
                            HWND_TOP,
                            swp.x + deltax,
                            swp.y,
                            0,
                            0,
                            SWP_MOVE|SWP_SHOW);
          } break;
      } /* endswitch */
      break;

    case WM_ADJUSTWINDOWPOS:
      { PSWP pswp = (PSWP)mp1;

        if (pswp->fl & (SWP_MOVE | SWP_SIZE)) {
          //(MAM) changed this from Post to Send to prevent delayed repainting
          WinSendMsg(hwnd,                                
                     WM_SIZE,
                     (MPARAM)0,
                     MPFROM2SHORT(pswp->cx, pswp->cy));
        } /* endif */

        if (pswp->fl & SWP_ACTIVATE) {
          pswp->fl &= (ULONG)~SWP_ACTIVATE;
          WinSetWindowPos(hwnd,
                          HWND_TOP,
                          0,
                          0,
                          0,
                          0,
                          SWP_ZORDER | SWP_ACTIVATE);
        } /* endif */
      } break;

    case WM_SIZE:
    { //SWP swp;
      LONG  cx = SHORT1FROMMP(mp2);
      LONG  cy = SHORT2FROMMP(mp2);

      if (cx<=0 || cy<=0 || !(UCMData->hwndScroll) || !(UCMData->hwndHide) || !(UCMData->hwndMenu)) break;

//    WinQueryWindowPos(UCMData->hwndMenu, &swp);

      /* Set scroll window over entire area */
      WinSetWindowPos(UCMData->hwndScroll,
                      HWND_TOP,
                      0,
                      0,
                      cx,
                      cy,
                      SWP_MOVE | SWP_SIZE | SWP_ZORDER | SWP_SHOW);

      /* Set hide to cover area, inset by borders */
      WinSetWindowPos(UCMData->hwndHide,
                      HWND_TOP,
                      UCM_FRAME_THICK,
                      UCM_FRAME_THICK,
                      cx - SUM_UCM_FRAME_THICK,
                      cy - SUM_UCM_FRAME_THICK,
                      SWP_SIZE | SWP_MOVE | SWP_ZORDER | SWP_SHOW);

      //7@P5d Moved set of menu window position to UCMenuCheckScrolling()

      UCMenuCheckScrolling(hwnd);
    } break;

    case WM_SHOW:
      // We can get this message after WM_DESTROY has freed our
      // instance data, so check the pointer first!
      if (UCMData != NULL) {
        if (UCMData->hwndScroll)
          WinShowWindow(UCMData->hwndScroll, (BOOL)mp1);
  
        if (UCMData->hwndHide)
          WinShowWindow(UCMData->hwndHide, (BOOL)mp1);
  
        if (UCMData->hwndMenu)
          WinShowWindow(UCMData->hwndMenu, (BOOL)mp1);
      }
      break;

    case WM_DESTROY:
      {

        if (UCMData->usItem != 0) {   //(MAM) There is an open submenu, close it before destory
           MENUITEM OpenItem;
           if ((BOOL)WinSendMsg(UCMData->hwndMenu,
                      MM_QUERYITEM,
                      MPFROM2SHORT(UCMData->usItem,TRUE),
                      MPFROMP(&OpenItem)))
             WinSendMsg(OpenItem.hwndSubMenu, MM_ENDMENUMODE, MPFROMSHORT(TRUE), 0L);
        }

        WinSubclassWindow( UCMData->hwndMenu, (PFNWP)UCMData->OldMenuProc);
        if (UCMData->hwndHelpInstance) {
           WinDestroyHelpInstance( UCMData->hwndHelpInstance );
        } // endif

        UCMenuFreeMenuData( UCMData->hwndMenu );
        //free all UCMenu instance data
        if ( UCMData->pszFontNameSize ) {
           MyFree( UCMData->pszFontNameSize );
        } // endif
        if ( UCMData->hpsMem ) {
           HDC hdcMem;
           hdcMem = GpiQueryDevice( UCMData->hpsMem );
           //(MAM) Destroy PS before closing DC since PM cannot
           //disassociate a micro PS from its DC.
           GpiDestroyPS( UCMData->hpsMem );
           DevCloseDC( hdcMem );
        } // endif
        if ( UCMData->AccelTable ){
           MyFree( UCMData->AccelTable );
        } // endif

        //(MAM) destroy other windows also.  Since Scroll, Hide, and Menu windows are
        // child windows, they will be destroyed by PM after this message is processed.
        // We must explicitly destroy non-child windows:

        if ( UCMData->hwndCM )                   // context menu
          WinDestroyWindow( UCMData->hwndCM );
        if ( UCMData->hwndBubble )
          WinDestroyWindow(UCMData->hwndBubble); // bubble window

        WinSetWindowPtr(hwnd, QWL_UCMDATA, NULL);
        MyFree(UCMData);
        return 0;
      }

    default:
     return (WinDefWindowProc(hwnd, msg, mp1, mp2));

  } // endswitch
  return (MRESULT)FALSE;
}

//----------------------------------------------------------------------------
// HideWndProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_HIDEWNDPROC. name='HideWndProc' text='Hide window procedure'.
// Window procedure of the Hide class, processes WM_PAINT, WM_CONTEXT and WM_COMMAND
// :syntax name='HideWndProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Hide window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY HideWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
PUCMDATA UCMData;

  UCMData = WinQueryWindowPtr(hwnd, 0L);

  switch (msg) {
     case WM_PRESPARAMCHANGED:
          {
             if ( (SHORT)mp1 == PP_BACKGROUNDCOLOR ) {
                ULONG Color, x;
                HPS hps;

                WinQueryPresParam( hwnd,
                                   (SHORT)mp1,
                                   0L, &x,
                                   (ULONG)sizeof Color,
                                   &Color,
                                   QPF_NOINHERIT);
                if ( UCMData && ( x == (SHORT)mp1 ) ){
                   // We don't want a dithered color because we will also use it
                   // to draw lines, and in this case only pure colors are used
                   // -> we will to have exactly the same color all over the ucmenu
                   hps = WinGetPS( hwnd );
                   if ( hps ){
                      UCMData->BgColor = GpiQueryNearestColor( hps, (ULONG)0, (LONG)Color );
                      UCMenuUpdateMenu( UCMData->hwndMenu, FALSE );
                      WinReleasePS( hps );
                      WinSendMsg( UCMData->hwndOwner,
                                  WM_CONTROL,
                                  MPFROM2SHORT(UCMData->UCMenuID, UCN_COLOR ),
                                  MPFROMSHORT( 0 ) );
                   } // endif
                } else {
                   WinRemovePresParam( hwnd, PP_BACKGROUNDCOLOR );
                } // endif
             } else {
                UCMenuPresParamChanged(UCMData, hwnd, mp1 );
             } // endif
             return((MRESULT)0);
          }
//  case WM_MOUSEMOVE:
//     {
//        PUCMDATA  UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
//        if ( UCMData->Style & UCS_PROMPTING ){
//           HWND hwndUCM   = WinQueryWindow( hwnd, QW_OWNER );
//           HWND hwndOwner = WinQueryWindow( hwndUCM, QW_OWNER );
//           WinSendMsg( hwndOwner,
//                       WM_CONTROL,
//                       MPFROM2SHORT( WinQueryWindowUShort( hwndUCM, QWS_ID ), UCN_MOUSEMOVE ),
//                       (MPARAM)0);
//           return (MRESULT)TRUE;
//        } else {
//           return (MRESULT)FALSE;
//        } // endif
//     }

    case WM_CREATE:

         WinSetWindowPtr(hwnd, 0L, (PUCMDATA)mp1);
         return((MRESULT)0);

// case WM_INITMENU:
//    {
//       PUCMDATA UCMData = (PUCMDATA)mp1;
//
//       // ----------------------------------------------------------
//       // -- Received when the context menu is about to be displayed
//       // -- Set the scrollbar as active window so that the contextual
//       // -- help looks in its help subtable (this is the only
//       // -- frame window available with a fixed ID)
//       // ----------------------------------------------------------
//       WinSendMsg( UCMData->hwndHelpInstance,
//                   HM_SET_ACTIVE_WINDOW,
//                   (MPARAM) WinQueryWindow( hwnd, QW_PARENT ),
//                   (MPARAM) WinQueryWindow( hwnd, QW_PARENT ) );
//       return WinDefWindowProc( hwnd, msg, mp1, mp2);
//    }
   case WM_CONTEXTMENU:

      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Show the pop-up menu                                         ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      {

         UCMenuContextMenu(UCMData->hwndUCM,
                           UCMData->hwndMenu,
                           (ULONG)mp1);
         return (MRESULT) TRUE;
      }

    case WM_MENUEND:{
      /* Context menu is terminating... re-enable bubble help window */
      if (UCMData->Style & UCS_BUBBLEHELP)
        WinSendMsg(UCMData->hwndBubble, MSG_ENABLE_BUBBLE, 0L, 0L);
      return 0;
      }

    case WM_COMMAND: {

      /* We only get WM_COMMAND messages here from the toolbar context menu. */
      /* If the context menu is application-supplied, we just pass the       */
      /* message on to the application.  Otherwise, we process options on    */
      /* the built-in toolbar context menu.                                  */
      if (UCMData->hwndUserCM != NULLHANDLE) { // App supplied the context menu

        WinSendMsg(UCMData->hwndOwner,  // To owner (app)
                   WM_CONTROL,
                   MPFROM2SHORT( UCMData->UCMenuID, UCN_CMITEM ) ,
                   MPFROM2SHORT( SHORT1FROMMP( mp1 ), UCMData->ContextID  ) );
        return 0;
      }

      #if !defined(UCMUI)  // We don't support any UI functions
        return 0;
      #else
      switch (SHORT1FROMMP(mp1)) {
        case IDM_UCM_DELETE:
          {
            /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
              ³ Delete the menu item (ContextID = itemID)                    ³
              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

            WinSendMsg(UCMData->hwndCMOrig,
                       MM_DELETEITEM,
                       MPFROM2SHORT(UCMData->ContextID, TRUE),
                       (MPARAM)0);
          }
          return (MRESULT)TRUE;

        case IDM_UCM_CREATE:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Add a new item in the UCMenu : use the settings notebook     ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          {

            UCMData->bItemCreation = TRUE;
            UCMData->hwndTemp = WinQueryWindow(hwnd, QW_OWNER);
            WinDlgBox(HWND_DESKTOP,
                      UCMData->hwndTemp,  //---hwndUCM
                      UCMenuSettingsDlgProc,
                      UCMData->hModUCM,
                      IDD_UCMSETTINGS,
                      (PVOID)UCMData);
            UCMData->hwndTemp = NULLHANDLE;
          }
          return (MRESULT)TRUE;

        case IDM_UCM_EDIT:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Edit an item : call the settings notebook                    ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          {

            UCMData->bItemCreation = FALSE;
            UCMData->hwndTemp = WinQueryWindow(hwnd, QW_OWNER);
            WinDlgBox(HWND_DESKTOP,
                      UCMData->hwndTemp,  //---hwndUCM
                      UCMenuSettingsDlgProc,
                      UCMData->hModUCM,
                      IDD_UCMSETTINGS,
                      (PVOID)UCMData);
            UCMData->hwndTemp = NULLHANDLE;
          }
          return (MRESULT)TRUE;

        case IDM_UCM_DEFAULT:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Get the default template (from the resource)                 ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          UCMenuLoadDefault( UCMData->hwndUCM );
          break;


        case IDM_UCM_LOAD:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Load a template from a file                                  ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          { FILEDLG FileDlg;
            ULONG  ulBufLen;
            UCHAR  szPath[CCHMAXPATH];
            PSZ    pszIndex;


            UCMData->hwndTemp = WinQueryWindow(hwnd, QW_OWNER);
            szPath[CCHMAXPATH-1] = '\0';
            strncpy( szPath, UCMData->szTemplatePath, CCHMAXPATH );
            strncat( szPath, "*.bar", CCHMAXPATH );
            memset(&FileDlg, 0, sizeof(FileDlg));
            FileDlg.cbSize = sizeof(FileDlg);
            FileDlg.fl     = FDS_OPEN_DIALOG | FDS_CENTER;
            FileDlg.szFullFile[CCHMAXPATH-1] = '\0';
            strncpy( FileDlg.szFullFile, szPath, CCHMAXPATH );
            WinFileDlg(HWND_DESKTOP, hwnd, &FileDlg);

            if (FileDlg.lReturn == DID_OK) {
              PVOID pBuffer;
              pBuffer = UCMenuLoadTemplate( FileDlg.szFullFile, &ulBufLen );
              if (pBuffer) {
                UCMenuNew( UCMData->hwndTemp, pBuffer );
                MyFree( pBuffer );
              } /* endif */
              pszIndex = strrchr( FileDlg.szFullFile, '\\' );
              if ( pszIndex ) {
                 *( pszIndex + 1 ) = '\0';
              } /* endif */
              strncpy( UCMData->szTemplatePath, FileDlg.szFullFile, CCHMAXPATH );
            } /* endif */

          } break;


        case IDM_UCM_SAVEAS:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Saves the template to a file                                 ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          { FILEDLG FileDlg;
            UCHAR   szPath[CCHMAXPATH];
            PSZ     pszIndex;

            UCMData->hwndTemp = WinQueryWindow(hwnd, QW_OWNER);
            szPath[CCHMAXPATH-1] = '\0';
            strncpy( szPath, UCMData->szTemplatePath, CCHMAXPATH );
            strncat( szPath, "*.bar", CCHMAXPATH );
            memset(&FileDlg, 0, sizeof(FileDlg));
            FileDlg.cbSize = sizeof(FileDlg);
            FileDlg.fl     = FDS_SAVEAS_DIALOG | FDS_CENTER;
            strncpy( FileDlg.szFullFile, szPath, CCHMAXPATH );
            WinFileDlg(HWND_DESKTOP, hwnd, &FileDlg);

            if (FileDlg.lReturn == DID_OK) {
              UCMenuSaveTemplate(UCMData->hwndTemp, FileDlg.szFullFile);
              pszIndex = strrchr( FileDlg.szFullFile, '\\' );
              if ( pszIndex ) {
                 *( pszIndex + 1 ) = '\0';
              } /* endif */
              strncpy( UCMData->szTemplatePath, FileDlg.szFullFile, CCHMAXPATH );
            } /* endif */
          } break;

        case IDM_UCM_STYLE:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Popup the ucmenu styles dialog                               ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          {
            UCMData->hwndTemp = WinQueryWindow(hwnd, QW_OWNER);

            WinDlgBox(HWND_DESKTOP,
                      UCMData->hwndTemp,
                      UCMenuStyleDlgProc,
                      UCMData->hModUCM,
                      IDD_UCMNSTYLE,
                      (PVOID)UCMData);
            UCMData->hwndTemp = NULLHANDLE;
          }
          return (MRESULT)TRUE;

       default:
            {
           
               UCMData->hwndTemp = UCMData->hwndOwner;
               WinSendMsg(UCMData->hwndOwner,
                          WM_CONTROL,
                          MPFROM2SHORT( UCMData->UCMenuID, UCN_CMITEM ) ,
                          MPFROM2SHORT( SHORT1FROMMP( mp1 ), UCMData->ContextID  ) );
            }
      } // endswitch of WM_COMMAND item ID
      #endif // UCMUI

      break;  // end of WM_COMMAND processing
      }

    case WM_PAINT:
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ We fill the rectangle with the UCMData->BgColor color. ³
        ³ We draw an inside frame                                ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      { HPS hPS;
        RECTL rcl;
        SWP swp;
        ULONG BgColorIndex;

        hPS = WinBeginPaint(hwnd, (HPS)NULL, &rcl);
        BgColorIndex = UCMenuSelectColor( UCMData->BgColor, hPS );
        WinFillRect(hPS, &rcl, BgColorIndex);

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Draw lines around the menu for the 3D effect ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (UCMData->Style & UCS_FRAMED) {
          WinQueryWindowPos( WinQueryWindow( hwnd, QW_TOP ), &swp );
          rcl.xLeft   = swp.x - MENU_FRAME_THICK;
          rcl.yBottom = swp.y - MENU_FRAME_THICK;
          rcl.xRight  = swp.x + swp.cx + MENU_FRAME_THICK;
          rcl.yTop    = swp.y + swp.cy + MENU_FRAME_THICK;
          UCMenu3DFrame( hPS, &rcl, 0 );
        }
        WinEndPaint(hPS);
      } break;

    case DM_DRAGOVER:
      // -------------------------------------------------------------------
      // -- We get this message when the drag icon is moved over our window.
      // -- We must verify whether or not we want to accept the drop.
      // -------------------------------------------------------------------
      return (MRESULT)(UCMenuDragOver(UCMData, hwnd,(PDRAGINFO) mp1));

    case DM_DROP:
      // --------------------------------------------------------
      // -- Some application has just Dropped something on us !!
      // --------------------------------------------------------
      UCMenuDrop(hwnd, (PDRAGINFO)mp1) ;
      return (MRESULT)0;

     default:
       return (WinDefWindowProc(hwnd, msg, mp1, mp2));
  } // endswitch

  return (MRESULT)FALSE;
}

//----------------------------------------------------------------------------
// SubmenuWndProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_SUBMWNDPROC. name='SubmenuWndProc' text='Submenu window procedure'.
// Window procedure of the submenus
// :syntax name='SubmenuWndProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Submenu window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// We process the WM_ADJUSTWINDOWPOS message to position the window on the right
// of the nebu item instead under it for vertical ucmenus
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY SubmenuWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PUCMDATA  UCMData = (PUCMDATA)WinQueryWindowPtr(hwnd, 0L);

   switch (msg) {

//  case WM_BUTTON2DOWN:
//  case WM_BUTTON1DOWN: {
//        /* On any button down, release capture and disable the bubble  */
//        /* help window.  It will be re-enabled when the button is      */
//        /* released (or drag/drop done, in that case).                 */
//
//        if (UCMData->Style & UCS_BUBBLEHELP)
//          WinSendMsg(UCMData->hwndBubble, MSG_DISABLE_BUBBLE, 0L, 0L);
//
//        if (UCMData->HoverCapture) {
//          WinSetCapture(HWND_DESKTOP, NULLHANDLE);
//          UCMData->HoverCapture = FALSE;
//        }
//        
//        if (msg == WM_BUTTON2DOWN)  // Drag/drop does not work if default proc gets this
//          break;                    // ??? should use WinQuerySysValue(...SV_BEGINDRAG...)
//        return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); // Pass this on
//        }
//
//
//  case WM_BUTTON2UP:
//  case WM_BUTTON1UP: {
//        MRESULT rc;
//
//        /* First let normal window proc process the UP message */
//        /* It will POST a WM_COMMAND to our UCMenu window if   */
//        /* the mouse is still on the menu item.                */
//        rc = UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); 
//
//        /* Simulate a mouse-move so that we will recapture the */
//        /* mouse if needed.  Set a flag for the WM_MOUSEMOVE   */
//        /* code to recognize this is a fake movement.          */
//
//        UCMData->HoverMsg = msg;
//        if (UCMData->Style & UCS_BUBBLEHELP)
//          WinSendMsg(UCMData->hwndBubble, MSG_ENABLE_BUBBLE, 0L, 0L);
//
//
//        /* NOTE: This message must be POSTED so it arrives         */
//        /* after WM_COMMAND has been received and UCN_ITEMSELECTED */
//        /* processed by the application.  Otherwise the app could  */
//        /* invoke a dialog in response to UCN_ITEMSELECTED and     */
//        /* cause us to lose mouse capture tracking.                */
//
//        WinPostMsg(hwnd, WM_MOUSEMOVE, mp1, mp2);
//        return rc;
//        }
//     
//  case WM_MOUSEMOVE:
//     {
//        USHORT   usId;      /* ID of menu item under mouse */
//        POINTL   ptl;       /* Mouse position in the window */
//        HWND hwndUCM   = WinQueryWindow( UCMData->hwndMenu, QW_OWNER );
//        HWND hwndOwner = WinQueryWindow( hwndUCM, QW_OWNER );
//        HWND HwndAt;        /* Window at mouse position */
//        BOOL Inside    = TRUE;
//        BOOL ButtonDown= FALSE;
//
//        /* If our app is not the active window, just pass it on */
//        if (!(UCMData->Active))
//          return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 );
//
//        /* See if any mouse button is pressed (and this is not from a BUTTONUP msg above). */
//        if ((WinGetKeyState(HWND_DESKTOP, VK_BUTTON1) & 0x8000) && (UCMData->HoverMsg != WM_BUTTON1UP))
//          ButtonDown = TRUE;
//        if ((WinGetKeyState(HWND_DESKTOP, VK_BUTTON2) & 0x8000) && (UCMData->HoverMsg != WM_BUTTON2UP))
//          ButtonDown = TRUE;
//        UCMData->HoverMsg = WM_NULL;
//
//        ptl.x = (ULONG) SHORT1FROMMP( mp1 );
//        ptl.y = (ULONG) SHORT2FROMMP( mp1 );
//
//        /* Note we must test entire desktop window hierarchy for PM */
//        /* to tell us if the point is over a window which obscures  */
//        /* our own.  If we search only our own window hierarchy, we */
//        /* will detect movements whenever the pointer is inside our */
//        /* window rectangle, even if our window is covered by       */
//        /* some other application.  Searching the desktop hierarchy */
//        /* is bad for performance, but PM gives us no other way to  */
//        /* detect (for sure) when the mouse leaves our menu window. */
//
//        WinMapWindowPoints(hwnd, HWND_DESKTOP, &ptl, 1);
//        HwndAt = WinWindowFromPoint(HWND_DESKTOP, &ptl, TRUE);
//        if (HwndAt != hwnd)
//          Inside = FALSE;
//
//        /* Restore point to my coordinate system */
//        ptl.x = (ULONG) SHORT1FROMMP( mp1 );
//        ptl.y = (ULONG) SHORT2FROMMP( mp1 );
//
//        /* If mouse is over another window (even if within the menu */
//        /* window rectangle), we don't use it.  Coord mapping       */
//        /* routine will be fooled by overlapping windows.           */
//
//        if (!Inside)
//          usId = 0;
//        else
//          usId  = UCMenuIdFromCoord(hwnd, &ptl ); // Where is it?
//
//        if (usId != UCMData->HoverID) {               // Tell owner of any change
//          if (UCMData->Style & UCS_PROMPTING)         // ...if they want to know.
//            WinSendMsg( hwndOwner, WM_CONTROL,
//                        MPFROM2SHORT( WinQueryWindowUShort( hwndUCM, QWS_ID ), UCN_MOUSEMOVE ),
//                        MPFROMSHORT( usId ) );
//          if (UCMData->Style & UCS_BUBBLEHELP) {      // ...if bubble needs to know
//            BOOL Deactivate = TRUE;                   // Bubble should be deactivated
//            if ((HwndAt == UCMData->hwndMenu) ||              // ... unless ptr
//    //          (HwndAt == UCMData->hwndBubble) ||
//    //          (HwndAt == WinQueryWindow(UCMData->hwndMenu, QW_PARENT)) ||  // hide window
//                (WinQueryWindow(HwndAt,QW_OWNER)==UCMData->hwndMenu))  // is over any TB menu
//                Deactivate = FALSE;
//            WinSendMsg(UCMData->hwndBubble,           
//                        MSG_ITEMCHANGE, MPFROM2SHORT(usId, Deactivate), MPFROMHWND(hwnd));
//          }
//        }
//        UCMData->HoverID = usId;                      // Save for next time
//
//        /* We (UCMenus) will capture the mouse if:               */
//        /*  - The mouse is inside the menu window                */
//        /*  - We don't already have it captured                  */
//        /*  - No buttons are pressed                             */
//
//        if ((Inside) && (!UCMData->HoverCapture) && (!ButtonDown)) {
//           WinSetCapture(HWND_DESKTOP, hwnd);
//           UCMData->HoverCapture = TRUE;
//        }
//
//        /* We release capture if:                                */
//        /*  - Mouse is outside the menu window                   */
//        /*  - No buttons down                                    */
//        /*  - We have capture set                                */
//
//        if ((!Inside) && (!ButtonDown) && (UCMData->HoverCapture)) {
//           WinSetCapture(HWND_DESKTOP, NULLHANDLE);    // Stop capture
//           UCMData->HoverCapture = FALSE;              // No longer captured
//           UCMData->HoverID = 0;
//        }
//
//        return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); // Pass this on
//     }
 

    case MM_INSERTITEM:
    case MM_SETITEM:
       {
          PMENUITEM pMi = 0;
          USHORT    NewID, NotifyMsg;
          MRESULT   rc;

          switch (msg) {
          case MM_INSERTITEM:
             pMi = (PMENUITEM)mp1;
             // Check if the id is already used
             NewID = UCMenuGetNewID( UCMData->hwndMenu, pMi->id, UCMData );
             if ( NewID != pMi->id) {
                pMi->id = NewID;
                if ( pMi->hItem ){
                   ITEM( pMi, usId ) = NewID;
                } // endif
             } /* endif */
             break;
          case MM_SETITEM:
             pMi = (PMENUITEM)mp2;
             // The item was already in the menu, so its
             // id should be correct
            break;
          } // endswitch

          //(MAM) Don't allow BREAK on any menu item.
          pMi->afStyle = pMi->afStyle & ~MIS_BREAK;

          if ( pMi && pMi->hItem ){
             // Set the id also in ucmitem
             // --
             ITEM( pMi, usId ) = pMi->id;
             // Load the btimap
             // --
             UCMenuLoadItemBmp(pMi, UCMData );
          } // endif

          rc = UCMData->OldSubMenuProc(hwnd, msg, mp1, mp2);

          // if an item was added, notify application (AFTER the insert is done)
          if (msg==MM_INSERTITEM)
            NotifyMsg = UCN_ADDEDITEM;
          else
            NotifyMsg = UCN_CHANGEDITEM;
          WinSendMsg( UCMData->hwndOwner,
                  WM_CONTROL,
                  MPFROM2SHORT( UCMData->UCMenuID, NotifyMsg ),
                  MPFROMSHORT( pMi->id ) );

          return rc;
       }

    //(MAM) Added DELETE processing here for submenus.  Any MM_DELETEITEM type
    // request received by the main menu for a submenu item will be done here.
    case MM_DELETEITEM:
    case MM_REMOVEITEM:
    case MM_SETITEMHANDLE: {
        MRESULT rc;
        USHORT  NotifyMsg;

        if ( msg == MM_DELETEITEM ){
           MENUITEM mi;

           if ( WinSendMsg(UCMData->hwndMenu, MM_QUERYITEM, mp1, MPFROMP(&mi)) &&
                mi.hItem ){
              if ( ITEM( &mi, pszBmp ) ){
                MyFree( ITEM( &mi, pszBmp ) );
              }
              if ( ITEM( &mi, pszText ) ){
                MyFree( ITEM( &mi, pszText ) );
              }
              if ( ITEM( &mi, pszAction ) ){
                MyFree( ITEM( &mi, pszAction ) );
              }
              if ( ITEM( &mi, pszData ) ){
                MyFree( ITEM( &mi, pszData ) );
              }
              if ( ITEM( &mi, pszParameters ) ){
                MyFree( ITEM( &mi, pszParameters ) );
              }
              if ( ITEM( &mi, hBmp ) ){
                GpiDeleteBitmap( ITEM( &mi, hBmp ) );
              }
              MyFree( (PVOID)mi.hItem );
              if ( mi.hwndSubMenu ){
                 UCMenuFreeMenuData( mi.hwndSubMenu );
              } // endif
           } // endif

        } // endif

        rc = UCMData->OldSubMenuProc(hwnd, msg, mp1, mp2);
     // if ((USHORT)WinSendMsg(hwnd, MM_QUERYITEMCOUNT, MPVOID, MPVOID) == 0) {
     //   /* Just deleted last item of a submenu.  Remove submenu attribute */
     //   /* of the parent menu item.                                       */
     //   //...not implemented yet: define a new mssage, UCMENU_QUERYSUBMENUPARENT
     //   //...which returns the item ID of the parent item of the
     //   //...submenu.  Implement the message by enumerating all the parent items
     //   //...and look for our window handle in the MENUITEM.hwndSubMenu field.
     //   //...When found, remove MIA_SUBMENU attribute, set hwndSubMenu to NULL,
     //   //...and destroy this submenu window.
     // }

        if ((msg==MM_DELETEITEM) || (msg==MM_REMOVEITEM))
          NotifyMsg = UCN_DELETEDITEM;
        else
          NotifyMsg = UCN_CHANGEDITEM;
        WinSendMsg( UCMData->hwndOwner,
                   WM_CONTROL,
                   MPFROM2SHORT( UCMData->UCMenuID, NotifyMsg ),
                   MPFROMSHORT( SHORT1FROMMP( mp1 ) ) );

        return rc;
        }

     case WM_CONTEXTMENU:
        {
         /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
           ³ Show the pop-up menu                                         ³
           ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

           UCMenuContextMenu(UCMData->hwndUCM,
                             hwnd,
                             (ULONG)mp1);
           return (MRESULT) TRUE;
        }
     case WM_SYSCOLORCHANGE:
        // Don't let original menu window proc process this.
        return((MRESULT)0);

     case WM_PRESPARAMCHANGED:
          {
          MRESULT rc;
             UCMenuPresParamChanged( UCMData, hwnd, mp1 );
             rc = UCMData->OldSubMenuProc(hwnd, msg, mp1, mp2);
             /* Need to dismiss submenu or font changes have odd effects */
             WinSendMsg(hwnd, MM_ENDMENUMODE, MPFROMSHORT(TRUE), MPVOID);
             return rc;
          }

     case WM_ADJUSTWINDOWPOS:
       { PSWP pswp;
         ULONG Style       = WinQueryWindowULong(UCMData->hwndUCM, QWL_STYLE);

         pswp = (PSWP)mp1;

         if ( UCMData && ( pswp->fl & SWP_MOVE ) && !WinIsWindowShowing( hwnd ) ) {
           RECTL rect;
           WinSendMsg(UCMData->hwndMenu,
                      MM_QUERYITEMRECT,
                      MPFROM2SHORT(UCMData->usItem,TRUE),
                      MPFROMP(&rect));
           switch (Style & 0x07) {
             case CMS_VERT:
               pswp->y += (rect.yTop   - rect.yBottom);
               pswp->x += (rect.xRight - rect.xLeft);
               break;
             case CMS_MATRIX:
               pswp->x += (rect.xRight - rect.xLeft);
               break;
           } // endswitch
         } // endif

         return (MRESULT)(UCMData->OldSubMenuProc(hwnd, msg, mp1, mp2));
       }

     default:
       {
          return (UCMenuDrgDrpMsg(UCMData, hwnd, msg, mp1, mp2, UCMData->OldSubMenuProc));
       }
   } // endswitch
   return 0;
}

//----------------------------------------------------------------------------
void _Optlink UCMenuCreateBubbleWindow(HWND UCMenuHwnd, UCMDATA *UCMData)
//----------------------------------------------------------------------------
// Create the bubble-help window.
//----------------------------------------------------------------------------
{
  /* Register class with room for 1 pointer */
  WinRegisterClass( (HAB)NULLHANDLE, BUBBLECLASS, (PFNWP)BubbleWndProc, 0L, (ULONG)sizeof(PVOID) );

  /* Create the bubble window  */
  // CS_SAVEBITS makes the bubble disappear faster, but can cause incorrect
  // painting of windows under it if they change while the bubble is up (esp menus)
  UCMData->hwndBubble = WinCreateWindow(HWND_DESKTOP,
                                        BUBBLECLASS,    // Bubble class window
                                        "",
                                  //    WS_SAVEBITS,    // Window style
                                        0L,             // Window style
                                        0,0,0,0,        // Size set by window proc as needed
                                        UCMenuHwnd,     // Owner
                                        HWND_TOP,
                                        0,              // ID is not used
                                        UCMData,        // Pass ptr to global data
                                        NULL);          // No pres params

   if (UCMData->pszFontNameSize[0] != '\0')
     WinSetPresParam( UCMData->hwndBubble, PP_FONTNAMESIZE,  // Make it same font as menu
                      strlen(UCMData->pszFontNameSize) + 1,
                      UCMData->pszFontNameSize);

} 

//----------------------------------------------------------------------------
MRESULT EXPENTRY BubbleWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
//----------------------------------------------------------------------------
// Bubble-help window procedure.
//----------------------------------------------------------------------------
{
#define BUBBLE_MARGIN_TOP        3
#define BUBBLE_MARGIN_BOT        3
#define BUBBLE_MARGIN_LEFT       3
#define BUBBLE_MARGIN_RIGHT      3
typedef struct { /*--- Bubble help window instance data ---*/
   UCMDATA      *UCMData            ;             // Ptr to UCMenu instance data
   char         *Text               ;             // Current bubble text
   USHORT       CurrID              ;             // Menu ID of current item
   HWND         CurrMenu            ;             // Handle of menu or submenu
   BOOL         Disabled            ;             // Bubble is currently disabled
   BOOL         Active              ;             // Bubble window is currently active
   POINTL       OffMenuPos          ;             // Point at which pointer left the toolbar
   BOOL         OffMenuActive       ;             // Was bubble active when pointer left?
   POINTL       StemPoint           ;             // X,Y coordinate of tip of stem (desktop)
   ULONG        TextHeight,TextWidth;             // Dimensions of text including margin
   ULONG        StemHeight,StemWidth;             // Dimensions of stem (not rectangular)
   LONG         XPos, YPos          ;             // X,Y pos of bbl window (desktop)
   BOOL         OnTop               ;             // Bubble is above menu item
   ULONG        DismissTimer        ;             // Handle of autodismiss timer
} BBLDATA, *PBBLDATA;

// "Active" means delay has been satisified already and bubble should
// update as pointer moves from item to item.  It does NOT mean the bubble
// is visible on the screen (e.g. if pointer is over a SPACER item, the
// bubble is still active, but not displayed since there is no help text).
//
// "Disabled" means the bubble window is not to be displayed (because some
// other interaction is in progress on the toolbar, such as a context menu).
// When bubble is disabled it is by definition also in-Active.  When re-enabled
// it will become active again after the normal delay period.

BBLDATA *BblData;   /* Ptr to bubble-instance data.  Not valid until after WM_CREATE */
 
  BblData = (BBLDATA *)WinQueryWindowPtr(hwnd, 0L);

  switch (msg) {
    case WM_CREATE:
      /* Create and initialize bubble-help instance data */
      BblData = MyMalloc(sizeof(BBLDATA));
      memset(BblData, 0x00, sizeof(BBLDATA));

      BblData->UCMData = (UCMDATA *)mp1;  /* MP1 is ptr to UCM instance data */
      WinSetWindowPtr(hwnd, 0L, BblData);
      return 0;

    case WM_DESTROY:
      WinStopTimer((HAB)NULLHANDLE, hwnd, TIMER_BUBBLE); // Cancel any pending update
      /* Free storage we have before quiting */
      if (BblData->Text != NULL)
        MyFree(BblData->Text);
      MyFree(BblData);
      break;
 
    case MSG_DISABLE_BUBBLE:
      /* Disable bubble until MSG_ENABLE_BUBBLE occures. */
      BblData->Disabled = TRUE;
      BblData->Active = FALSE;
      WinStopTimer((HAB)NULLHANDLE, hwnd, TIMER_BUBBLE); // Cancel any pending update
      WinSetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_HIDE);
      return 0;

    case MSG_ENABLE_BUBBLE: {
      USHORT TempID;

      BblData->Disabled = FALSE;
      /* Send fake itemchange message to start delay period */
      TempID = BblData->CurrID;
      BblData->CurrID = 0;  // Force update
      WinSendMsg(hwnd, MSG_ITEMCHANGE, MPFROM2SHORT(TempID,FALSE), MPFROMHWND(BblData->CurrMenu));
      return 0;
      }

    case MSG_ITEMCHANGE: {
      /* mp1 = (SHORT) new item ID               */
      /*       (BOOL) deactivate if ID=0 (T/F)   */
      /* mp2 = (HWND) menu window                */
      POINTL PtrPos;
      HWND   NewHwnd;

      /* Pointer has moved on a menu item.  If item is different */
      /* than last time, schedule bubble window update.          */

      if (SHORT1FROMMP(mp1) == BblData->CurrID)
        return 0;  // Do nothing if no change

      BblData->CurrID = SHORT1FROMMP(mp1);
      BblData->CurrMenu = HWNDFROMMP(mp2);

      /* If item ID is zero, pointer moved off toolbar.  If     */
      /* caller says to deactivate, hide bubble and delay before*/
      /* showing again.  Otherwise keep current active status.  */

      if (BblData->CurrID == 0) {
        WinSetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_HIDE);
        WinStopTimer((HAB)NULLHANDLE, hwnd, TIMER_BUBBLE); // Cancel any pending update
        if ((BOOL)SHORT2FROMMP(mp1))  // Caller says deactivate
          BblData->Active = FALSE;
        return 0;
      }

      /* If we are disabled, no need to schedule update */
      if (BblData->Disabled)
        return 0;

      /* If bubble is already active,  update immediately w/new data */
      /* otherwise delay before showing it.  If delay time is set to */
      /* less than minimum,  fake an immediate timer event (e.g. no  */
      /* delay at all).                                              */

      if (BblData->Active)
        WinSendMsg(hwnd, MSG_UPDATE_BUBBLE, 0L, 0L);
      else {
        if (BblData->UCMData->BubbleDelay < MIN_BUBBLE_DELAY)
          WinSendMsg(hwnd, WM_TIMER, MPFROMSHORT(TIMER_BUBBLE_FAKE), 0L);
        else
          WinStartTimer((HAB)NULLHANDLE, hwnd, TIMER_BUBBLE, BblData->UCMData->BubbleDelay);
      }
 
      return 0;
      }

    case WM_TIMER:
      switch (SHORT1FROMMP(mp1)) {
        case TIMER_BUBBLE: {
          POINTL PtrPos;
          /* Real PM timer event occured.  Stop timer. */
          WinStopTimer((HAB)NULLHANDLE, hwnd, TIMER_BUBBLE);
          /* If pointer has moved off window (but window proc has not noticed yet) */
          /* then do not activate the bubble.                                      */
          WinQueryPointerPos(HWND_DESKTOP, &PtrPos);
          if (WinWindowFromPoint(HWND_DESKTOP, &PtrPos, TRUE) != BblData->CurrMenu)
            return 0;
          /* else fall through next case... */
          }
        case TIMER_BUBBLE_FAKE:
          /* Display bubble help now */
          BblData->Active = TRUE;  // Bubble is now active
          WinSendMsg(hwnd, MSG_UPDATE_BUBBLE, 0L, 0L);
          return 0;
        case TIMER_BBLAUTODISMISS:
          /* Time to remove the bubble help */
          WinSendMsg(hwnd, MSG_ITEMCHANGE, MPFROM2SHORT(0, TRUE), MPFROMHWND(BblData->CurrMenu));
          WinStopTimer((HAB)0, hwnd, BblData->DismissTimer);
          return 0;
      }
      break;


    case MSG_UPDATE_BUBBLE: {
      /* Update the bubble window with current data.  If window */
      /* is not disabled, show it.                              */
      HPS Hps;
      RECTL   TextBox;
      RECTL   itemRect;
      POINTL  BubblePt;
      QBUBBLEDATA QueryData;
      MENUITEM Item;

      if (BblData->CurrID == 0) { // should not happen
        return 0;
      }

      /* Calculate window size needed */

      if (BblData->Text != NULL) // free any previous data
        MyFree(BblData->Text);

      QueryData.BubbleText = NULL;   // Setup for call to application
      QueryData.MenuItem   = &Item;
      if ((BOOL)WinSendMsg(BblData->CurrMenu, MM_QUERYITEM, MPFROM2SHORT(BblData->CurrID,TRUE), MPFROMP(&Item))) {
        WinSendMsg(BblData->UCMData->hwndOwner,
                   WM_CONTROL,
                   MPFROM2SHORT(BblData->UCMData->UCMenuID, UCN_QRYBUBBLEHELP),
                   MPFROMP(&QueryData));
      }

      /* If app gave us a string to use, make a copy and then free application's string */
      if (QueryData.BubbleText != NULL) {
        BblData->Text = MyStrdup(QueryData.BubbleText);
        MyFree(QueryData.BubbleText);
      }
      else
        BblData->Text = NULL;

      /* If there is no text, just hide the bubble window (it will still be 'active') */
      if ((BblData->Text == NULL) || (BblData->Text[0] == '\0')) {
        WinSetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_HIDE);
        return 0;
      }

      /* Calculate window size needed to contain text */

      Hps = WinGetPS(hwnd);    //@P4m
      TextBox.xLeft = 0;
      TextBox.yBottom = 0;
      TextBox.xRight = MAX_INT;
      TextBox.yTop = MAX_INT;
      WinDrawText(Hps, -1, BblData->Text, &TextBox, 0L, 0L, DT_QUERYEXTENT|DT_LEFT|DT_VCENTER);
      WinReleasePS(Hps);       //@P4a

      BblData->TextWidth = BUBBLE_MARGIN_LEFT+BUBBLE_MARGIN_RIGHT+(TextBox.xRight - TextBox.xLeft);
      BblData->TextHeight= BUBBLE_MARGIN_TOP +BUBBLE_MARGIN_BOT  +(TextBox.yTop - TextBox.yBottom);
      BblData->StemHeight= BblData->TextHeight;
      BblData->StemWidth = BblData->StemHeight/2;
      BblData->OnTop     = TRUE;

      /* Minimum bubble width is wide enough for two rounded corners, a stem base     */
      /* and some extra.                                                              */
      BblData->TextWidth = max(BblData->TextWidth, BblData->TextHeight + BblData->TextHeight/2);

      /* Get position of the item in the menu window */
      if (!(BOOL)WinSendMsg(BblData->CurrMenu, MM_QUERYITEMRECT, MPFROM2SHORT(BblData->CurrID, TRUE), MPFROMP(&itemRect))) {
      }

      /* Map to desktop coordinates.  */

      BblData->StemPoint.x = itemRect.xLeft + ((itemRect.xRight-itemRect.xLeft)/2);
      BblData->StemPoint.y = itemRect.yTop;
      WinMapWindowPoints(BblData->CurrMenu, HWND_DESKTOP, &(BblData->StemPoint), 1L);

      /* If bubble is over top of screen, flip to underside of menu item */
      if (BblData->StemPoint.y + BblData->TextHeight + BblData->StemHeight > WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN)) {
        BblData->OnTop = FALSE;   // Put bubble under the menu item
        BblData->StemPoint.y = BblData->StemPoint.y - (itemRect.yTop-itemRect.yBottom);
      }

      /* If tip of stem is off the screen (x-dimension), bring it back */
      BblData->StemPoint.x = min(max(0L, (LONG)BblData->StemPoint.x), WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN));

      /* Try to position bubble window 1/4 MaxHeight to the left  of the stem tip. */
      /* This gives a nice look to the stem and bubble.                            */

      BblData->XPos = min(max(0L,(LONG)(BblData->StemPoint.x-(LONG)(BblData->TextHeight/4))), WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN)-BblData->TextWidth);
      if (BblData->OnTop)
        BblData->YPos = BblData->StemPoint.y;
      else
        BblData->YPos = BblData->StemPoint.y - BblData->TextHeight - BblData->StemHeight;

      /* Size/position the bubble window.  Hide it so background will be */
      /* restored (since we don't repaint our entire window area).       */
      WinSetWindowPos(hwnd, HWND_TOP, BblData->XPos,
                                      BblData->YPos,
                                      BblData->TextWidth,
                                      BblData->TextHeight+BblData->StemHeight,
                                      SWP_MOVE|SWP_SIZE|SWP_HIDE);

      /* Map stem point to bubble window coordinates after move/size */
      WinMapWindowPoints(HWND_DESKTOP, hwnd, &(BblData->StemPoint), 1L);

      /* If we are not disabled, show window and force repaint */
      if (!BblData->Disabled) {
        // We must wait for all WM_PAINT msgs to be processed by other windows run off our
        // message queue, or they may not be updated before our semi-transparent window
        // is displayed, resulting in those windows not appearing to have been updated.
        {QMSG QMsg;
        while(WinPeekMsg((HAB)0, &QMsg, NULLHANDLE, WM_PAINT, WM_PAINT, PM_REMOVE))
          WinDispatchMsg((HAB)0, &QMsg);
        }
        WinSetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_SHOW|SWP_ZORDER);
        WinInvalidateRect(hwnd, NULL, FALSE);
        /* Start timer to autodismiss the bubble, min timeout is 1 second */
        BblData->DismissTimer = WinStartTimer((HAB)0, hwnd, TIMER_BBLAUTODISMISS, max(1000L,BblData->UCMData->BubbleRead));
      }
      return 0;
      }

    case WM_PAINT:
      {
      HPS    Hps;                       /* Presentation Space handle    */
      RECTL  Rect;                      /* Rectangle coordinates        */
      POINTL Pt;                        /* String screen coordinates    */
      POINTL StemPts[3];                /* Points in stem polygon       */
      POLYGON PolyInfo;                 /* Polygon information          */
      SWP    SizePos;                   /* Size/pos of the window       */
      ULONG  Rounding;                  /* Corner rounding factor       */
      LONG   SlantOffset;               /* Offset of tip for slant angle*/
      LONG   SlantDir;                  /* +/-1 slant direction         */

      Hps = WinBeginPaint(hwnd, 0L, &Rect);  /* Get PS to draw */
      WinQueryWindowPos(hwnd, &SizePos);     /* Get window size*/

      /* Draw bubble rectangle with rounded corners */

      Pt.x = 0;                      // Lower left corner
      if (BblData->OnTop)
        Pt.y = BblData->StemHeight;
      else
        Pt.y = 0;
      GpiMove(Hps, &Pt);
      Pt.x = BblData->TextWidth-1;   // Upper right corner
      Pt.y = Pt.y + BblData->TextHeight-1;

      Rounding = BblData->TextHeight/2;
      GpiSetColor(Hps, CLR_YELLOW);
      GpiBox(Hps, DRO_FILL,    &Pt, Rounding, Rounding); // Draw filled rect
      GpiSetColor(Hps, CLR_BLACK);
      GpiBox(Hps, DRO_OUTLINE, &Pt, Rounding, Rounding); // Draw outline

      /* Change slant angle if tip is on right side of bubble */
      SlantOffset = BblData->TextHeight / 2;
      SlantDir    = 1;
      if (BblData->StemPoint.x > BblData->TextWidth/2)
        SlantDir = -1;

      /* Calculate X position of stem verticies */
      /* [0] = left base corner                 */
      /* [1] = tip                              */
      /* [2] = right base corner                */
      
      StemPts[1].x = BblData->StemPoint.x;        // Tip is fixed position
      StemPts[0].x = StemPts[1].x + (SlantOffset * SlantDir);
      StemPts[2].x = StemPts[0].x + (BblData->StemWidth * SlantDir);

      /* Set Y position of stem verticies */
      StemPts[1].y = BblData->StemPoint.y;        // Tip position is fixed
      if (BblData->OnTop)                         // Base above or below tip
        StemPts[0].y = BblData->StemHeight;
      else
        StemPts[0].y = BblData->TextHeight-1;
      StemPts[2].y = StemPts[0].y;

      /* Draw polygon starting at first stem point */
      GpiMove(Hps, &(StemPts[0]));
      PolyInfo.aPointl = StemPts;    // Describe polygon
      PolyInfo.ulPoints = 3;
      GpiSetColor(Hps, CLR_YELLOW);
      GpiPolygons(Hps, 1L, &PolyInfo, 0L, 0L);  // Draw filled stem
      GpiSetColor(Hps, CLR_BLACK);
      GpiMove(Hps, &(StemPts[0]));              // Draw outline
      GpiLine(Hps, &(StemPts[1]));
      GpiLine(Hps, &(StemPts[2]));

      /* Draw the text offset by bottom and left margins and stem size */
 
      Rect.xLeft = BUBBLE_MARGIN_LEFT;
      Rect.xRight = BblData->TextWidth;
      if (BblData->OnTop)
        Rect.yBottom = BUBBLE_MARGIN_BOT+BblData->StemHeight;
      else
        Rect.yBottom = BUBBLE_MARGIN_BOT;
      Rect.yTop = Rect.yBottom + BblData->TextHeight;
      WinDrawText(Hps, -1, BblData->Text, &Rect, 0L, 0L, DT_LEFT|DT_BOTTOM|DT_TEXTATTRS);

      WinEndPaint(Hps);  
      return 0;
      }
  }

  return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

//----------------------------------------------------------------------------
void UCMenuReloadAllBitmaps(HWND hwndMenu, UCMDATA *UCMData)
//----------------------------------------------------------------------------
// Reload all the menu bitmaps calling ourself recursively for submenus.
//----------------------------------------------------------------------------
{
  MENUITEM      Mi;          // PM menu item data
  UCMITEM       *UCMItem;    // UCMenus item data
  USHORT        NbOfItems;   // # of items in this menu
  USHORT        i, itemID;

  NbOfItems = SHORT1FROMMR(WinSendMsg(hwndMenu, MM_QUERYITEMCOUNT, NULL, NULL));

  for (i=0 ; i<NbOfItems ; i++ ) {
    itemID = (USHORT)WinSendMsg(hwndMenu,
                                MM_ITEMIDFROMPOSITION,
                                MPFROMSHORT(i),
                                NULL);
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(itemID, FALSE),
               MPFROMP(&Mi));

    /* If there is valid UCMenu item data, delete current bitmap */
    /* and reload it.                                            */

    UCMItem = (UCMITEM *)Mi.hItem;
    if (UCMItem != NULL) {
      if (UCMItem->hBmp != NULLHANDLE) {
        GpiDeleteBitmap(UCMItem->hBmp);
        UCMItem->hBmp = NULLHANDLE;
      }
      UCMenuLoadItemBmp(&Mi, UCMData);
    }

    /* If this is a submenu item, call again for submenu */

    if (Mi.afStyle & MIS_SUBMENU) 
      UCMenuReloadAllBitmaps(Mi.hwndSubMenu, UCMData);

  } // for each item in menu
}
 
 
//----------------------------------------------------------------------------
// MenuWndProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_MENUWNDPROC. name='MenuWndProc' text='Menu window procedure'.
// Window procedure of the menus
// :syntax name='MenuWndProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Menu window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY MenuWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
PUCMDATA  UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);

   switch (msg) {
     #if defined(MSG_DEBUGMESSAGE)
     case MSG_DEBUGMESSAGE:
       WinMessageBox(HWND_DESKTOP,hwnd,(char *)mp2,(char *)mp1,0,MB_OK|MB_INFORMATION);
       return 0;
     #endif

    case WM_MOUSEMOVE: {
          USHORT   usId;      /* ID of menu item under mouse */
          POINTL   ptl;       /* Mouse position in the window */
 
          /* If our app is not the active window, just pass it on */
          if (!(UCMData->Active))
            return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 );

          /* See what item the mouse is over */
          ptl.x = (ULONG) SHORT1FROMMP( mp1 );
          ptl.y = (ULONG) SHORT2FROMMP( mp1 );
          usId  = UCMenuIdFromCoord(hwnd, &ptl );

          /* If mouse has moved to a different item, send notifications */

          if (usId != UCMData->HoverID) {            
            if (UCMData->Style & UCS_PROMPTING)     // Tell owner if they want to know
              WinSendMsg( UCMData->hwndOwner, WM_CONTROL,
                          MPFROM2SHORT( UCMData->UCMenuID, UCN_MOUSEMOVE ),
                          MPFROMSHORT( usId ) );

            if (UCMData->Style & UCS_BUBBLEHELP)    // Tell bubble if it needs to know
              WinSendMsg(UCMData->hwndBubble,           
                          MSG_ITEMCHANGE, MPFROM2SHORT(usId, FALSE), MPFROMHWND(hwnd));
          }
          UCMData->HoverID = usId;                  // Save for next time

          /* Start/reset timer to check that pointer is still in this window */
          if ((UCMData->Style & UCS_PROMPTING) || (UCMData->Style & UCS_BUBBLEHELP))
            UCMData->MenuPtrTimer = WinStartTimer((HAB)0, hwnd, TIMER_PTRCHECK, PTR_CHECK_DELAY);

          return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); // Pass this on
          }

    case WM_BUTTON2DOWN:
    case WM_BUTTON1DOWN:
          /* On any button down, disable the bubble help window.  It  */
          /* will be re-enabled when the button is released (or       */
          /* drag/drop done, in that case).                           */
  
          if (UCMData->Style & UCS_BUBBLEHELP)
            WinSendMsg(UCMData->hwndBubble, MSG_DISABLE_BUBBLE, 0L, 0L);

          /* Don't pass button 2 to real menu proc since it will attempt to */
          /* select the item.  We also have to return FALSE or drag/drop    */
          /* will not work (no WM_BEGINDRAG will occure).  So for button 2  */
          /* we must do what the default window proc normally does (e.g.    */
          /* activate the frame window).                                    */
          if (msg == WM_BUTTON2DOWN) {
            WinSetActiveWindow(HWND_DESKTOP, hwnd);  // Will activate my frame
            return FALSE;                            // Tell PM we did not process it
          }

          /* For button 1, let normal menu proc handle as usual */
 
          return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); // Pass this on

    case WM_BUTTON2UP:
    case WM_BUTTON1UP: {
          MRESULT rc;
  
          /* First let normal window proc process the UP message */
          /* It will POST a WM_COMMAND to our UCMenu window if   */
          /* the mouse is still on the menu item.                */
          rc = UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); 
  
          /* Simulate a mouse-move so that we will restart the   */
          /* bubble-help window.                                 */
  
          if (UCMData->Style & UCS_BUBBLEHELP)
            WinSendMsg(UCMData->hwndBubble, MSG_ENABLE_BUBBLE, 0L, 0L);
  
          /* NOTE: This message must be POSTED so it arrives         */
          /* after WM_COMMAND has been received and UCN_ITEMSELECTED */
          /* processed by the application.                           */
          //...need to see if ptr is still in the window before doing
          //...this since MOUSEMOVE code assumes ptr is in the window.
  
          WinPostMsg(hwnd, WM_MOUSEMOVE, mp1, mp2);
          return rc;
          }

    case WM_TIMER: {
          POINTL Point;

       // if (SHORT1FROMMP(mp1) == TIMER_SYSCLRCHANGE) {
       //       UCMenuReloadAllBitmaps(WinQueryWindow( hwnd, QW_OWNER ), UCMData);
       //       UCMenuUpdateMenu( hwnd, FALSE );
       //       WinStopTimer((HAB)0, hwnd, TIMER_SYSCLRCHANGE);
       //       return 0;
       //  }
       //  else if (SHORT1FROMMP(mp1) != TIMER_PTRCHECK) // Pass on other timer events
           if (SHORT1FROMMP(mp1) != TIMER_PTRCHECK) // Pass on other timer events
             break;
 
          /* See if the pointer is still in the window.  If not, */
          /* notify the owner and bubble help windows.  Also, if */
          /* application became inactive.                        */
          WinQueryPointerPos(HWND_DESKTOP, &Point);

          if ((WinWindowFromPoint(HWND_DESKTOP, &Point, TRUE) != hwnd) ||
             (!UCMData->Active)) {
            BOOL Disable;

            if (UCMData->Style & UCS_PROMPTING)     // Tell owner if they want to know
              WinSendMsg( UCMData->hwndOwner, WM_CONTROL,
                          MPFROM2SHORT(UCMData->UCMenuID, UCN_MOUSEMOVE ),
                          MPFROMSHORT( 0 ) );
  
            //...should disable bubble only if new window is not part of the
            //...UCMenu control (e.g. not the menu, submenu, or hide window).
            Disable = TRUE;
            if (UCMData->Style & UCS_BUBBLEHELP)    // Tell bubble to disable itself
              WinSendMsg(UCMData->hwndBubble,           
                          MSG_ITEMCHANGE, MPFROM2SHORT(0, Disable), MPFROMHWND(hwnd));
            UCMData->HoverID = 0;                   // Save for next time

            WinStopTimer((HAB)0, hwnd, UCMData->MenuPtrTimer);
          }
          return 0;
          }

//  case WM_BUTTON2DOWN:
//  case WM_BUTTON1DOWN: {
//        /* On any button down, release capture and disable the bubble  */
//        /* help window.  It will be re-enabled when the button is      */
//        /* released (or drag/drop done, in that case).                 */
//
//        if (UCMData->Style & UCS_BUBBLEHELP)
//          WinSendMsg(UCMData->hwndBubble, MSG_DISABLE_BUBBLE, 0L, 0L);
//
//        if (UCMData->HoverCapture) {
//          WinSetCapture(HWND_DESKTOP, NULLHANDLE);
//          UCMData->HoverCapture = FALSE;
//        }
//        
//        if (msg == WM_BUTTON2DOWN)  // Drag/drop does not work if default proc gets this
//          break;                    // ??? should use WinQuerySysValue(...SV_BEGINDRAG...)
//        return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); // Pass this on
//        }
//
//  case WM_BUTTON2UP:
//  case WM_BUTTON1UP: {
//        MRESULT rc;
//
//        /* First let normal window proc process the UP message */
//        /* It will POST a WM_COMMAND to our UCMenu window if   */
//        /* the mouse is still on the menu item.                */
//        rc = UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); 
//
//        /* Simulate a mouse-move so that we will recapture the */
//        /* mouse if needed.  Set a flag for the WM_MOUSEMOVE   */
//        /* code to recognize this is a fake movement.          */
//
//        UCMData->HoverMsg = msg;
//        if (UCMData->Style & UCS_BUBBLEHELP)
//          WinSendMsg(UCMData->hwndBubble, MSG_ENABLE_BUBBLE, 0L, 0L);
//
//        /* NOTE: This message must be POSTED so it arrives         */
//        /* after WM_COMMAND has been received and UCN_ITEMSELECTED */
//        /* processed by the application.  Otherwise the app could  */
//        /* invoke a dialog in response to UCN_ITEMSELECTED and     */
//        /* cause us to lose mouse capture tracking.                */
//
//        WinPostMsg(hwnd, WM_MOUSEMOVE, mp1, mp2);
//        return rc;
//        }
//     
//  case WM_MOUSEMOVE:
//     {
//        USHORT   usId;      /* ID of menu item under mouse */
//        POINTL   ptl;       /* Mouse position in the window */
//        HWND hwndUCM   = WinQueryWindow( hwnd, QW_OWNER );
//        HWND hwndOwner = WinQueryWindow( hwndUCM, QW_OWNER );
//        HWND HwndAt;        /* Window at mouse position */
//        BOOL Inside    = TRUE;
//        BOOL ButtonDown= FALSE;
//
//        /* If our app is not the active window, just pass it on */
//        if (!(UCMData->Active))
//          return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 );
//
//        /* See if any mouse button is pressed (and this is not from a BUTTONUP msg above). */
//        if ((WinGetKeyState(HWND_DESKTOP, VK_BUTTON1) & 0x8000) && (UCMData->HoverMsg != WM_BUTTON1UP))
//          ButtonDown = TRUE;
//        if ((WinGetKeyState(HWND_DESKTOP, VK_BUTTON2) & 0x8000) && (UCMData->HoverMsg != WM_BUTTON2UP))
//          ButtonDown = TRUE;
//        UCMData->HoverMsg = WM_NULL;
//
//        ptl.x = (ULONG) SHORT1FROMMP( mp1 );
//        ptl.y = (ULONG) SHORT2FROMMP( mp1 );
//
//        /* Note we must test entire desktop window hierarchy for PM */
//        /* to tell us if the point is over a window which obscures  */
//        /* our own.  If we search only our own window hierarchy, we */
//        /* will detect movements whenever the pointer is inside our */
//        /* window rectangle, even if our window is covered by       */
//        /* some other application.  Searching the desktop hierarchy */
//        /* is bad for performance, but PM gives us no other way to  */
//        /* detect (for sure) when the mouse leaves our menu window. */
//
//        WinMapWindowPoints(hwnd, HWND_DESKTOP, &ptl, 1);
//        HwndAt = WinWindowFromPoint(HWND_DESKTOP, &ptl, TRUE);
//        if (HwndAt != hwnd)
//          Inside = FALSE;
//
//        /* Restore point to my coordinate system */
//        ptl.x = (ULONG) SHORT1FROMMP( mp1 );
//        ptl.y = (ULONG) SHORT2FROMMP( mp1 );
//
//        /* If mouse is over another window (even if within the menu */
//        /* window rectangle), we don't use it.  Coord mapping       */
//        /* routine will be fooled by overlapping windows.           */
//
//        if (!Inside)
//          usId = 0;
//        else
//          usId  = UCMenuIdFromCoord(hwnd, &ptl ); // Where is it?
//
//        if (usId != UCMData->HoverID) {               // Tell owner of any change
//          if (UCMData->Style & UCS_PROMPTING)         // ...if they want to know.
//            WinSendMsg( hwndOwner, WM_CONTROL,
//                        MPFROM2SHORT( WinQueryWindowUShort( hwndUCM, QWS_ID ), UCN_MOUSEMOVE ),
//                        MPFROMSHORT( usId ) );
//          if (UCMData->Style & UCS_BUBBLEHELP) {      // ...if bubble needs to know
//            BOOL Deactivate = TRUE;                   // Bubble should be deactivated
//            if ((HwndAt == UCMData->hwndMenu) ||              // ... unless ptr
//       //       (HwndAt == UCMData->hwndBubble) ||
//       //       (HwndAt == WinQueryWindow(UCMData->hwndMenu, QW_PARENT)) ||  // hide window
//                (WinQueryWindow(HwndAt,QW_OWNER)==UCMData->hwndMenu))  // is over any TB menu
//                Deactivate = FALSE;
//            WinSendMsg(UCMData->hwndBubble,           
//                        MSG_ITEMCHANGE, MPFROM2SHORT(usId, Deactivate), MPFROMHWND(hwnd));
//          }
//        }
//        UCMData->HoverID = usId;                      // Save for next time
//
//        /* We (UCMenus) will capture the mouse if:               */
//        /*  - The mouse is inside the menu window                */
//        /*  - We don't already have it captured                  */
//        /*  - No buttons are pressed                             */
//
//        if ((Inside) && (!UCMData->HoverCapture) && (!ButtonDown)) {
//           WinSetCapture(HWND_DESKTOP, hwnd);
//           UCMData->HoverCapture = TRUE;
//        }
//
//        /* We release capture if:                                */
//        /*  - Mouse is outside the menu window                   */
//        /*  - No buttons down                                    */
//        /*  - We have capture set                                */
//
//        if ((!Inside) && (!ButtonDown) && (UCMData->HoverCapture)) {
//           WinSetCapture(HWND_DESKTOP, NULLHANDLE);    // Stop capture
//           UCMData->HoverCapture = FALSE;              // No longer captured
//           UCMData->HoverID = 0;
//        }
//
//        return UCMData->OldMenuProc( hwnd, msg, mp1, mp2 ); // Pass this on
//     }

    case MM_INSERTITEM:
    case MM_SETITEM:
       {
          PMENUITEM pMi = 0;
          USHORT    NewID;

          switch (msg) {
          case MM_INSERTITEM:
             pMi = (PMENUITEM)mp1;
             // Check if the id is already used
             NewID = UCMenuGetNewID( UCMData->hwndMenu, pMi->id, UCMData );
             if ( NewID != pMi->id) {
                pMi->id = NewID;
                if ( pMi->hItem ){
                   ITEM( pMi, usId ) = NewID;
                } // endif
             } /* endif */
             break;
          case MM_SETITEM:
             pMi = (PMENUITEM)mp2;
            break;
          } // endswitch

          //(MAM) set MIA_NODISMISS attribute on all submenu placeholder items to
          // prevent dismiss of submenu during drag/drop and context menu operations.
          if (pMi->afStyle & MIS_SUBMENU)
            pMi->afAttribute = pMi->afAttribute | MIA_NODISMISS;

          //(MAM) remove MIS_BREAK from all items
          pMi->afStyle = pMi->afStyle & (USHORT) ~MIS_BREAK;

          if ( pMi && pMi->hItem ){
             // Set the id also in ucmitem
             // --
             ITEM( pMi, usId ) = pMi->id;
             // Load the bitmap
             // --
             UCMenuLoadItemBmp(pMi, UCMData );
          } // endif

          return UCMData->OldMenuProc(hwnd, msg, mp1, mp2);
       }
     case WM_TRANSLATEACCEL:
          {
             PQMSG       QMsg       = (PQMSG)mp1;

             if(QMsg->msg == WM_CHAR) {
                USHORT flags = SHORT1FROMMP(QMsg->mp1);
                USHORT VK = SHORT2FROMMP(QMsg->mp2);

                if((flags & KC_SHIFT) && !(flags & KC_PREVDOWN) && (flags & KC_VIRTUALKEY) && !(flags & KC_LONEKEY)) {
                  if(VK == VK_F10) {
                     WinSendMsg(hwnd, WM_CONTEXTMENU, (MPARAM)0, 0L);
                     return((MRESULT)0);
                  }
                }
                if(!(flags & KC_PREVDOWN) && (flags & KC_VIRTUALKEY) && (VK==VK_F1)) {
                     RECTL Rectl;
                     POINTL ptl;
                     ULONG ContextID;
                     ULONG SelectedItem = (ULONG) WinSendMsg(hwnd, MM_QUERYSELITEMID, 0L, 0L);

                     WinSendMsg(hwnd, MM_QUERYITEMRECT, (MPARAM)SelectedItem, MPFROMP(&Rectl));
                     ptl.x = Rectl.xLeft   + (Rectl.xRight - Rectl.xLeft)/2;
                     ptl.y = Rectl.yBottom + (Rectl.yTop - Rectl.yBottom)/2;
                     ContextID = UCMenuIdFromCoord(hwnd, &ptl);
                     WinSendMsg( UCMData->hwndOwner,
                                 WM_HELP,
                                 MPFROM2SHORT( ContextID, UCMData->UCMenuID),
                                 MPFROM2SHORT( CMDSRC_UCMENU, 0 ) );
                     return((MRESULT)0);
                }

                if(!(flags & KC_PREVDOWN) && (flags & KC_CHAR)) {
                   return (MRESULT) TranslateAccel(UCMData, hwnd, SHORT1FROMMP(QMsg->mp2), QMsg);
                }

                return (UCMenuDrgDrpMsg(UCMData, hwnd, msg, mp1, mp2, UCMData->OldMenuProc));
             }
          } // endcase
          return(MRESULT)0;
    case WM_CONTEXTMENU:
       UCMenuContextMenu(UCMData->hwndUCM,
                         hwnd,
                         (ULONG)mp1);
       return (MRESULT) TRUE;

     case WM_BUTTON2DBLCLK:
       break;

//   case WM_BUTTON2DOWN:
//     // ----------------------------------------------------------------
//     // -- Keep that message here, else drag and drop won't work
//     // -- (this prevent the message from being processed by the default
//     // -- menu window procedure)
//     // ----------------------------------------------------------------
//     break;

     case WM_SYSCOLORCHANGE:
       // Don't let original menu window proc get this since we handle
       // color changes ourself.
       return((MRESULT)0);

     case WM_PRESPARAMCHANGED:
          {
             ULONG x;

             if ((LONG)mp1 == PP_MENUBACKGROUNDCOLOR) {
                // We will also receive 2 messages for the menu bg hilite and menu bg disabled colors
                // We don't need them so we don't process them
                LONG lColor;
                LONG lNearestColor;
                HPS hps;

                WinQueryPresParam( hwnd,
                                   (SHORT)mp1,
                                   0L, &x,
                                   (ULONG)sizeof lColor,
                                   &lColor,
                                   QPF_NOINHERIT );
                if (x == (SHORT)mp1) {
                   hps = WinGetPS( hwnd );
                   lNearestColor = GpiQueryNearestColor( hps, (ULONG)0, (LONG)lColor );
                   WinReleasePS( hps );

                   if ( lColor == lNearestColor ) {
                      // -- Update the color
                      UCMData->ItemBgColor = lColor;

                      // -- When background color changes, must reload all bitmaps
                      // -- to get mapping from original bitmap colors (not current
                      // -- colors).
                      UCMenuReloadAllBitmaps(UCMData->hwndUCM, UCMData);

                      // -- Warn the owner
                      WinSendMsg( UCMData->hwndOwner,
                                  WM_CONTROL,
                                  MPFROM2SHORT( UCMData->UCMenuID, UCN_COLOR ),
                                  MPFROMSHORT( 0 ) );

                      // This will cause a WM_UPDATEFRAME to be sent to the owner (the ucmenu)
                      // If we were processing the 2 following PP_* in the same way, we would have
                      // the ucmenu repainted 3 times (pretty ugly isn't it? :-) )
                      UCMData->bProcessingPP = TRUE;
                      return UCMData->OldMenuProc( hwnd, msg, mp1, mp2);
                   } else {
                      // -----------------------------
                      // -- We want only solid colors
                      // -----------------------------
                      WinSetPresParam( hwnd,
                                       PP_MENUBACKGROUNDCOLOR,
                                       sizeof lNearestColor,
                                       &lNearestColor);
                      return (MRESULT)FALSE;
                   } // endif
                } else {
                   WinRemovePresParam( hwnd, PP_MENUBACKGROUNDCOLOR );
                } // endif
             } else if (LONGFROMMP(mp1) == PP_FONTNAMESIZE) {
                char FontNameSize[MAX_FONTNAMELEN] ;
                WinQueryPresParam( hwnd,
                                   PP_FONTNAMESIZE,
                                   0L, &x,
                                   (ULONG)MAX_FONTNAMELEN,
                                   FontNameSize,
                                   QPF_NOINHERIT );
                if (x == PP_FONTNAMESIZE) {
                   // A font pres parameter was set... update our font info
                   if (UCMData->pszFontNameSize)
                      MyFree(UCMData->pszFontNameSize);
                   if ( UCMData->pszFontNameSize = MyMalloc(strlen(FontNameSize)+1) ) {
                      strcpy(UCMData->pszFontNameSize, FontNameSize );
                      WinSendMsg( UCMData->hwndOwner,
                                  WM_CONTROL,
                                  MPFROM2SHORT( UCMData->UCMenuID, UCN_FONT ),
                                  MPFROMSHORT( 0 ) );
                      /* Tell the bubble-help window about font changes */
                      if (UCMData->Style & UCS_BUBBLEHELP)
                        WinSetPresParam(UCMData->hwndBubble, PP_FONTNAMESIZE, strlen(FontNameSize)+1, FontNameSize);
                   }
                   UCMData->bProcessingPP = TRUE;
                   return UCMData->OldMenuProc( hwnd, msg, mp1, mp2);
                   // This will cause a WM_UPDATEFRAME to be sent to the owner (the ucmenu)
                } else {
                   // The font pres parameter was removed.
                   WinRemovePresParam( hwnd, PP_FONTNAMESIZE );
                   /* Tell the bubble-help window about font changes */
                   if (UCMData->Style & UCS_BUBBLEHELP)
                     WinRemovePresParam( UCMData->hwndBubble, PP_FONTNAMESIZE );
                } // if FONTNAMESIZE param was set

             } else {
                break;
             } // endif
          }
          return UCMData->OldMenuProc( hwnd, msg, mp1, mp2);

     default:
       {
          return (UCMenuDrgDrpMsg(UCMData, hwnd, msg, mp1, mp2, UCMData->OldMenuProc));
       }
   } // endswitch

   return (MRESULT)0;
}

//----------------------------------------------------------------------------
// UCMenuLoadItemBmp
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UCMLOADITEMBMP. name='UCMenuLoadItemBmp' text='Find and load the bitmap of a ucmenu item'.
// If a ucmenu item has no bitmap, find it and load it.
// :syntax name='UCMenuLoadItemBmp' params='pUCMitem, pUCMData' return='nothing' .
// :fparams.
// :fparam name='pUCMItem' type='PUCMITEM' io='input/output' .
// Pointer to a ucmenu item structure.
// :fparam name='pUCMData' type='PUCMDATA' io='input' .
// Pointer to the ucmenu data structure.
// :freturns.
// :fparam name='-' type='VOID' io='return'.
// Nothing.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuLoadItemBmp( MENUITEM *Item, PUCMDATA UCMData )
{
UCMITEM *pUCMI = NULL;

   if (Item)
     pUCMI = (UCMITEM *)Item->hItem;  // Get ptr to UCMITEM from menu item struct

   /* Don't load bitmap if pointers are invalid, there is already */
   /* a bitmap loaded, or this is a SPACER type item.             */

   if ( pUCMI && !pUCMI->hBmp && !(Item->afStyle & MIS_SPACER) ) {
      char  BmpPathStr[MAXPATHL];
      HPS hPS = WinGetPS( UCMData->hwndMenu );
      LONG lID = 0;
      BOOL BinOK;

      if (pUCMI->pszBmp ){
   
        /* A bitmap string was specified.  It may be a resource ID or */
        /* a BMP file name.                                           */
    
        /* Attempt conversion of bitmap string to resource ID */
        lID = UCMString2Int(pUCMI->pszBmp, &BinOK);
    
        if (BinOK) { // Bitmap is a resource ID, so load it from resources
          pUCMI->hBmp = (ULONG)GpiLoadBitmap(hPS,
                                             UCMData->hModBmp,
                                             lID,
                                             0,
                                             0);
          pUCMI->ulFlags &= ~UCMI_BMPFROMFILE;
          pUCMI->ulFlags = (pUCMI->ulFlags & 0x0000FFFFL) | (lID << 16);
        }
        else { // Bitmap is a file name, so load it from file
           UCMenuGetBitmapFullName( UCMData, pUCMI->pszBmp, BmpPathStr );
           pUCMI->hBmp = UCMenuLoadBitmap( BmpPathStr );
           pUCMI->ulFlags |= UCMI_BMPFROMFILE;
           pUCMI->ulFlags = pUCMI->ulFlags & 0x0000FFFFL;
        }
      } // a pszBmp string was specified
      else {
           pUCMI->ulFlags &= ~UCMI_BMPFROMFILE;
           pUCMI->ulFlags = pUCMI->ulFlags & 0x0000FFFFL;
      }

      /* If bitmap could not be loaded, load default as specified in UCMINFO */
   
      if (!pUCMI->hBmp) {
        /* Attempt conversion of bitmap string to resource ID */
        lID = UCMString2Int(UCMData->szDefaultBitmap, &BinOK);
        if (BinOK) { // Bitmap is a resource ID, so load it from resources
          pUCMI->hBmp = (ULONG)GpiLoadBitmap(hPS,
                                             UCMData->hModBmp,
                                             lID,
                                             0,
                                             0);
        }
        else { // Bitmap is a file name, so load it from file
           UCMenuGetBitmapFullName( UCMData, UCMData->szDefaultBitmap, BmpPathStr );
           pUCMI->hBmp = UCMenuLoadBitmap( BmpPathStr );
        }
      }
   
      /* Finally, if still no go, use our own default bitmap resource */
   
      if ( !pUCMI->hBmp )
        pUCMI->hBmp = GpiLoadBitmap( hPS, UCMData->hModUCM, UCMENUID_DEFAULTBMP, 0, 0 );

      // If we are mapping background colors, do the mapping now

      if (UCMData->Style & (UCS_CHNGBMPBG|UCS_CHNGBMPBG_AUTO))
        UCMenuSetBmpBgColor(pUCMI, UCMData, hPS);

      WinReleasePS( hPS );

   } // if data is valid
}

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuSettingsDlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UCMSETTDLGPROC. name='UCMenuSettingsDlgProc' text='UCMenu settings notebook dialog procedure'.
// Dialog procedure of the ucmenu settings notebook
// :syntax name='UCMenuSettingsDlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Notebook window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY  UCMenuSettingsDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg) {
    case WM_CONTROL:
      switch (SHORT2FROMMP(mp1)) {
      case BKN_PAGESELECTED:
         // The last focused window of a page is stored in its QWL_USER
         // The QWL_USER is initialized in the WM_INITDLG of each page
         {
            PAGESELECTNOTIFY notif =  * (PAGESELECTNOTIFY *)mp2;
            HWND hNewPage = (HWND)WinSendMsg( notif.hwndBook,
                                     BKM_QUERYPAGEWINDOWHWND,
                                     MPFROMLONG( notif.ulPageIdNew),
                                     MPFROMLONG(0L));

            if (hNewPage) {
               WinPostMsg( hNewPage, GETTING_FOCUS, 0L, 0L );
            } // endif
         }


         break;
      default:
        break;
      } // endswitch
      break;

    case WM_INITDLG:
      { HWND hwndPage;
        RECTL rcl;
        SWP swp;
        POINTL pt[2];
        HWND hwndNB = WinWindowFromID(hwnd, IDC_UCMNB);
        LONG PageID1, PageID2, PageID0;
        ULONG Color = SYSCLR_WINDOWSTATICTEXT;
        PUCMDATA UCMData = (PUCMDATA)mp2;

//      if ( UCMData->hwndHelpInstance ) {
//         // -------------------------------------------------
//         // -- The contextual help would work without that
//         // -- We do it so that the focus goes back on this
//         // -- dialog after a contextual help invoked from it
//         // -- has been dismissed ( else the focus goes back
//         // -- to the closest winassociated window in the
//         // -- parent and owner chain )
//         // -------------------------------------------------
//         WinAssociateHelpInstance( UCMData->hwndHelpInstance, hwnd );
//      } // endif
        WinSetWindowULong(hwnd, QWL_USER, (ULONG)UCMData);
        UCMData->hwndSettings = hwnd;

        WinSendMsg(hwndNB, BKM_SETNOTEBOOKCOLORS,
                   MPFROMLONG(SYSCLR_DIALOGBACKGROUND),
                   MPFROMLONG(BKA_BACKGROUNDMAJORCOLORINDEX));
        WinSendMsg(hwndNB, BKM_SETNOTEBOOKCOLORS,
                   MPFROMLONG(SYSCLR_DIALOGBACKGROUND),
                   MPFROMLONG(BKA_BACKGROUNDMINORCOLORINDEX));
        WinSendMsg(hwndNB, BKM_SETNOTEBOOKCOLORS,
                   MPFROMLONG(SYSCLR_DIALOGBACKGROUND),
                   MPFROMLONG(BKA_BACKGROUNDPAGECOLORINDEX));
        WinSetPresParam(hwndNB, PP_FOREGROUNDCOLORINDEX, 4 , &Color);
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Insert the pages (2 or 3) in the notebook control            ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (UCMData->bItemCreation) {
          PageID0 = (LONG)WinSendMsg(hwndNB,
                                      BKM_INSERTPAGE,
                                      (MPARAM)0,
                                      MPFROM2SHORT(BKA_MAJOR | BKA_AUTOPAGESIZE, BKA_FIRST));
        } /* endif */
        PageID1 = (LONG) WinSendMsg(hwndNB,
                                    BKM_INSERTPAGE,
                                    (MPARAM)0,
                                    MPFROM2SHORT(BKA_MAJOR | BKA_AUTOPAGESIZE, BKA_LAST));
        PageID2 = (LONG) WinSendMsg(hwndNB,
                                    BKM_INSERTPAGE,
                                    (MPARAM)0,
                                    MPFROM2SHORT(BKA_MAJOR | BKA_AUTOPAGESIZE, BKA_LAST));
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Set the tabs dimensions                                      ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSendMsg(hwndNB,
                   BKM_SETDIMENSIONS,
                   MPFROM2SHORT(90,30),
                   (MPARAM)BKA_MAJORTAB);
        WinSendMsg(hwndNB,
                   BKM_SETDIMENSIONS,
                   MPFROM2SHORT(0,0),
                   (MPARAM)BKA_MINORTAB);
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Get the coord. of the client area                            ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        pt[0].x =   0;  //
        pt[0].y =   0;  // coord of the corners of the nb pages (dialogs)
        pt[1].x = 203;  //  in the rc file -- all are the same size
        pt[1].y = 136;  //

        WinMapDlgPoints( hwndNB, pt, 2, 1 );        // dlg to NB control

        rcl.xLeft    = pt[0].x;
        rcl.yBottom  = pt[0].y;
        rcl.xRight   = pt[1].x;
        rcl.yTop     = pt[1].y;

        // get the size to give to the NB control
        WinSendMsg(hwndNB,
                   BKM_CALCPAGERECT,
                   MPFROMP(&rcl),
                   (MPARAM)FALSE);

        // size the NB control to fit around the pages
        WinSetWindowPos( hwndNB,
                         HWND_TOP,
                         0,
                         0,
                         rcl.xRight-rcl.xLeft,
                         rcl.yTop-rcl.yBottom,
                         SWP_SIZE );

        // Size the dialog window to fit around the NB control
        // (MAM) but account for the OK/Cancel buttons below it.
        WinQueryWindowPos( hwndNB, &swp );
        rcl.xLeft = 0;
        rcl.yBottom = 0;
        rcl.xRight = swp.x + swp.cx;
        rcl.yTop = swp.y + swp.cy;
        // calculate the size of the frame given the size of the client
        // only the size of the rect is considered
        WinCalcFrameRect( hwnd, &rcl, FALSE );
        WinSetWindowPos( hwnd,
                         HWND_TOP,
                         0,
                         0,
                         rcl.xRight-rcl.xLeft,
                         rcl.yTop-rcl.yBottom,
                         SWP_SIZE );

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Load dialogs (0,) 1 and 2                                    ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (UCMData->bItemCreation) {
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ >> PAGE 0 << ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          hwndPage = WinLoadDlg(hwnd,
                                hwnd,
                                UCMenuNBP0DlgProc,
                                UCMData->hModUCM,
                                IDD_UCMNBP0,
                                (PVOID)UCMData);

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Tab text      ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          WinSendMsg(hwndNB,
                     BKM_SETTABTEXT,
                     (MPARAM)PageID0,
                     MPFROMP( nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_POSITION, 0 ) ) );
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Set page hwnd ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
          WinSendMsg(hwndNB,
                     BKM_SETPAGEWINDOWHWND,
                     (MPARAM)PageID0,
                     MPFROMHWND(hwndPage));
        } /* endif */
        WinSetOwner( hwndPage, hwndNB );
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ >> PAGE 1 << ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        hwndPage = WinLoadDlg(hwnd,
                              hwnd,
                              UCMenuNBP1DlgProc,
                              UCMData->hModUCM,
                              IDD_UCMNBP1,
                              (PVOID)UCMData);

        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Tab text      ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSendMsg(hwndNB,
                   BKM_SETTABTEXT,
                   (MPARAM)PageID2,
                    MPFROMP( nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_GENERAL, 0 ) ) );
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Set page hwnd ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSendMsg(hwndNB,
                   BKM_SETPAGEWINDOWHWND,
                   (MPARAM)PageID2,
                   MPFROMHWND(hwndPage));
        WinSetOwner( hwndPage, hwndNB );
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ >> PAGE 2 << ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        hwndPage = WinLoadDlg(hwnd,
                              hwnd,
                              UCMenuNBP2DlgProc,
                              UCMData->hModUCM,
                              IDD_UCMNBP2,
                              (PVOID)UCMData);
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Tab text      ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSendMsg(hwndNB,
                   BKM_SETTABTEXT,
                   (MPARAM)PageID1,
                    MPFROMP( nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_ACTION, 0 ) ) );
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Set page hwnd ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSendMsg(hwndNB,
                   BKM_SETPAGEWINDOWHWND,
                   (MPARAM)PageID1,
                   MPFROMHWND(hwndPage));
        WinSetOwner( hwndPage, hwndNB );
        /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
          ³ Set focus     ³
          ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        if (UCMData->bItemCreation) {
           WinPostMsg( UCMData->hwndPage0, GETTING_FOCUS, 0L, 0L );
        } else {
           WinPostMsg( UCMData->hwndPage2, GETTING_FOCUS, 0L, 0L );
        } // endif

      } break;

    // (MAM) Added processing of OK/CANCEL buttons, simplified exit
    //       processing of notebook pages (all exit processing now
    //       done here instead of in each page dialog proc).
    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
        case DID_CANCEL:
          WinDismissDlg(hwnd, DID_CANCEL);
          return 0;
        case DID_OK:
          {
            PUCMDATA UCMData;
            UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
            if (UCMData->bItemCreation) {
              /* Create item.  Dismiss if no error. */
              if (UCMenuNBP0OK(hwnd))
                WinDismissDlg(hwnd, DID_OK);
              return 0;
            }
            else {
              /* Do "OK" processing, then dismiss */
              UCMenuNBP1OK(UCMData->hwndPage1);
              UCMenuNBP2OK(UCMData->hwndPage2);
              WinDismissDlg(hwnd, DID_OK);  /* We are done */
              return 0;
            } /* endif */
          } /* OK case */

      } /* switch */
      break;

    case WM_CLOSE:
      // (MAM) Close from system menu is now CANCEL function
      WinDismissDlg(hwnd, DID_CANCEL);
      return 0;

    case WM_DESTROY:
     {
     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ Dismiss the dialog and destroy the windows ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
         PUCMDATA UCMData;
         UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);

         if (UCMData->bItemCreation) {
           WinDismissDlg(UCMData->hwndPage0, TRUE);
           WinDestroyWindow(UCMData->hwndPage0);
         } /* endif */
         WinDismissDlg(UCMData->hwndPage1, TRUE);
         WinDismissDlg(UCMData->hwndPage2, TRUE);
         WinDestroyWindow(UCMData->hwndPage1);
         WinDestroyWindow(UCMData->hwndPage2);
      }
      break;

    default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
  } /* endswitch */
  return (MRESULT)0;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP1DlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_PG1DLGPROC. name='UCMenuNBP1DlgProc' text='UCMenu settings notebook page 1 dialog procedure'.
// Dialog procedure of the page 1 of the ucmenu settings notebook
// :syntax name='UCMenuNBP1DlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Notebook page 1 window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY  UCMenuNBP1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg) {
    case WM_INITDLG:
      {
        PUCMDATA UCMData = (PUCMDATA)mp2;

        WinSetWindowULong(hwnd, QWL_USER, (ULONG)UCMData);
        UCMData->hwndPage1 = hwnd;
        UCMenuNBP1Initialize(UCMData, hwnd);
      }
      break;

//  case WM_ACTIVATE:
//    if (SHORT1FROMMP(mp1)) {
//      WinSendMsg(WinQueryHelpInstance(hwnd), HM_SET_ACTIVE_WINDOW,
//                 (MPARAM)hwnd, (MPARAM)hwnd);
//    } else {
//      // clear active help window when this window is deactivated - this is
//      // necessary for message box help, etc. to work properly
//      WinSendMsg(WinQueryHelpInstance(hwnd), HM_SET_ACTIVE_WINDOW,
//                 NULLHANDLE, NULLHANDLE);
//    } /* endif */
//    return WinDefDlgProc( hwnd, msg, mp1, mp2 );

    case GETTING_FOCUS:
       WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd, IDC_UCMNBP1TITLE ) );
     break;

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
        case IDB_UCMNBP1UNDO:
             {
                PUCMDATA UCMData;
                UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
                UCMenuNBP1Initialize(UCMData, hwnd);
                return (MRESULT)0;
             }

        // (MAM) removed OK and CANCEL processing...

        case IDB_UCMNBP1LOAD:
          /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
            ³ Load a bitmap           ³
            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        {  FILEDLG FileDlg;
           PUCMDATA UCMData;
           MENUITEM mi;
           UCHAR    szPath[CCHMAXPATH];
           PSZ      pszIndex;
           UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
           memset(&FileDlg, 0, sizeof(FileDlg));

           if ( ! UCMData->bItemCreation ) {
              WinSendMsg(UCMData->hwndTemp,
                         MM_QUERYITEM,
                         MPFROM2SHORT( UCMData->ContextID, TRUE ),
                         MPFROMP(&mi));
           }

           FileDlg.cbSize     = sizeof(FileDlg);
           FileDlg.fl         = FDS_OPEN_DIALOG | FDS_CENTER;
           FileDlg.pfnDlgProc = BitmapFileDlgProc;
           FileDlg.ulUser     = (ULONG) UCMData;

           if ( ! UCMData->bItemCreation && ITEM( &mi, pszBmp ) ) {
              strcpy((PSZ)(&(FileDlg.szFullFile)), (PSZ)(ITEM(&mi, pszBmp)));
           } else {
              szPath[CCHMAXPATH-1] = '\0';
              strncpy( szPath, UCMData->szBitmapPath, CCHMAXPATH );
              strncat( szPath, "*.bmp", CCHMAXPATH );
              strncpy( FileDlg.szFullFile, szPath, CCHMAXPATH );
           }
           WinFileDlg( HWND_DESKTOP, hwnd, &FileDlg );


           if ( FileDlg.lReturn == DID_OK ) {
              // -- UCMData->hBmpTemp has been updated by the subclassed  filedlgproc
              WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), TRUE );
              UCMenuNBP1UpdateBmp( hwnd, FileDlg.szFullFile );
              pszIndex = strrchr( FileDlg.szFullFile, '\\' );
              if ( pszIndex ) {
                 *( pszIndex + 1 ) = '\0';
              } /* endif */
              strncpy( UCMData->szBitmapPath, FileDlg.szFullFile, CCHMAXPATH );
           } // endif
        }
        break;

        case IDB_UCMNBP1EDIT :
        {
           PSZ pszTxt = MyMalloc( MAXPATHL );
           WinQueryDlgItemText(hwnd, IDC_UCMNBP1FILENAME, (LONG)MAXPATHL, pszTxt);

           UCMenuEditBmpFile( hwnd, pszTxt );

        }
        break;


        case IDB_UCMNBP1PREDEFINED :
        {
           ULONG ulResult;
           PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER );

           if ( !UCMData ) {
              return (MRESULT)FALSE;
           } // endif

           ulResult = WinDlgBox( HWND_DESKTOP,
                                 hwnd,
                                 ResBmpDlgProc,
                                 UCMData->hModUCM,
                                 IDD_RESBMP,
                                 (PVOID)UCMData );
           if ( ulResult && ( ulResult != DID_ERROR ) ){
              HBITMAP hbmp;
              HPS     hPS = WinGetPS( UCMData->hwndMenu );
              hbmp = (ULONG)GpiLoadBitmap( hPS,
                                           UCMData->hModBmp,
                                           UCMData->ulBmpTempId,
                                           0,
                                           0);
              WinReleasePS( hPS );
              if ( hbmp ) {
                 CHAR szBmpId[22];
                 sprintf( szBmpId, "%i", UCMData->ulBmpTempId );
                 UCMData->hBmpTemp = hbmp;
                 UCMData->bBmpTempFromFile = FALSE;
                 WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), FALSE );

                 UCMenuNBP1UpdateBmp( hwnd, szBmpId );
              } // endif
           } // endif
        }
        break;

        case IDB_UCMNBP1NOBMP :
        {
           PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER );

           if ( !UCMData ) {
              return (MRESULT)FALSE;
           } // endif

           UCMData->hBmpTemp = 0;
           UCMData->bBmpTempFromFile = FALSE;
           WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), FALSE );

           UCMenuNBP1UpdateBmp( hwnd, "" );
        }
        break;

        case IDB_UCMNBP1CREATE :
        {
           PUCMDATA UCMData = (PUCMDATA) WinQueryWindowULong( hwnd, QWL_USER );
           WinDlgBox( HWND_DESKTOP,
                      hwnd,
                      UCMenuCreateBmpDlgProc,
                      UCMData->hModUCM,
                      IDD_UCMGETBMPNAME,
                      (PVOID)UCMData );
        }
        break;

      } // endswitch
      break;

    case UCMNBP1_NEWBMP:
    {
       PSZ pszFileName = (PSZ)mp1;
       PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER );

       HBITMAP hBmp = UCMenuLoadBitmap( pszFileName );

       if ( hBmp ) {
          UCMData->hBmpTemp = hBmp;
          UCMData->bBmpTempFromFile = TRUE;
          UCMenuNBP1UpdateBmp( hwnd, pszFileName );
       } // endif
       WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1LOAD ),   TRUE );
       WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1CREATE ), TRUE );
       WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ),   TRUE );
       WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1PREDEFINED ),   TRUE );
    } break;

    case WM_PAINT:
    { MPARAM rc;
      HPS    hPS;
      SWP    swp;
      RECTL  rcl;
      POINTL pt;
      BITMAPINFOHEADER BmpInfo;
      PUCMDATA UCMData;
      UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);

      rc = WinDefDlgProc(hwnd, msg, mp1, mp2);

      if ( UCMData->hBmpTemp ) {
        hPS = WinGetPS( hwnd );
        WinQueryWindowPos( WinWindowFromID( hwnd, IDC_UCMNBP1BITMAP ), &swp );

        GpiQueryBitmapParameters( UCMData->hBmpTemp, &BmpInfo );
        pt.x = (BmpInfo.cx > swp.cx ? swp.x : swp.x + (swp.cx - BmpInfo.cx)/2);
        pt.y = (BmpInfo.cy > swp.cy ? swp.y : swp.y + (swp.cy - BmpInfo.cy)/2);
        rcl.xLeft   = 0;
        rcl.yBottom = 0;
        rcl.xRight  = swp.cx;
        rcl.yTop    = swp.cy;
        WinDrawBitmap( hPS,
                       UCMData->hBmpTemp,
                       &rcl,
                       &pt,
                       0,
                       0,
                       DBM_NORMAL );
        WinReleasePS( hPS );
      } // endif
      return rc;
    }

    case WM_HELP:
      switch (SHORT1FROMMP(mp1)) {
      case IDB_UCMNBP1HELP:
         {
            PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER);

            UCMenuDisplayHelp( UCMData,
                       (USHORT)PANEL_ITEMBMP,
                       (USHORT)UCN_HLP_NB_BMP );

         }
         break;
      default:
         return WinDefDlgProc( hwnd, msg, mp1, mp2 );
      } // endswitch
      break;

    default:
      return WinDefDlgProc( hwnd, msg, mp1, mp2 );

  } // endswitch

  return (MRESULT)0;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP1Initialize : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_INITPG1. name='UCMenuNBP1Initialize' text='Initializes the page 1 of the settings notebook' .
// This function initializes the page 1 of the settings notebook
// :syntax name='UCMenuNBP1Initialize' params='UCMData, hwnd' return='-' .
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input' .
// Pointer to the UCMDATA structure
// :fparam name='hwnd' type='HWND' io='input' .
// Page 1 window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuNBP1Initialize(PUCMDATA UCMData, HWND hwnd)
{
   if (UCMData->bItemCreation) {
     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ Item Creation : blank the fields                             ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
     RECTL rcl;
     SWP   swp;
     HPS   hPS = WinGetPS( hwnd );

     WinSetDlgItemText( hwnd, IDC_UCMNBP1TITLE, "" );

     UCMData->hBmpTemp = 0;
     UCMData->bBmpTempFromFile = FALSE;
     WinQueryWindowPos( WinWindowFromID( hwnd, IDC_UCMNBP1BITMAP ), &swp );
     rcl.xLeft   = swp.x;
     rcl.yBottom = swp.y;
     rcl.xRight  = swp.x + swp.cx;
     rcl.yTop    = swp.y + swp.cy;
     WinFillRect( hPS, &rcl, SYSCLR_DIALOGBACKGROUND );
     WinSetDlgItemText( hwnd, IDC_UCMNBP1FILENAME, 0 );
     WinReleasePS( hPS );

     WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), FALSE );

   } else {
     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ Editing : get the data from the item                         ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
     MENUITEM mi;
     PSZ      pszTxt;
     SWP      swp;
     RECTL    rcl;
     POINTL   pt;
     HPS      hPS = WinGetPS(hwnd);
     HWND     hwndUCM;
     BITMAPINFOHEADER BmpInfo;
     ULONG    ulSize;

     hwndUCM = UCMData->hwndTemp;


     memset(&mi, 0, sizeof(MENUITEM));
     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ Query item                  ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
     WinSendMsg(hwndUCM,
                MM_QUERYITEM,
                MPFROM2SHORT(UCMData->ContextID, TRUE),
                MPFROMP(&mi));

     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ Query item text             ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
       if (mi.hItem && ITEM(&mi, pszText)) {
         ulSize = strlen(ITEM(&mi, pszText));
         pszTxt = MyMalloc(ulSize + 1);
         if (pszTxt) {
           strcpy(pszTxt, ITEM(&mi, pszText));
           WinSetDlgItemText(hwnd, IDC_UCMNBP1TITLE, pszTxt);
           MyFree(pszTxt);
         } else {
           WinSetDlgItemText(hwnd, IDC_UCMNBP1TITLE, "");
         } /* endif */
       } else {
         WinSetDlgItemText(hwnd, IDC_UCMNBP1TITLE, "");
       } /* endif */

     WinQueryWindowPos( WinWindowFromID( hwnd, IDC_UCMNBP1BITMAP ), &swp );

     rcl.xLeft   = swp.x;
     rcl.yBottom = swp.y;
     rcl.xRight  = swp.x + swp.cx;
     rcl.yTop    = swp.y + swp.cy;
     WinFillRect( hPS, &rcl, SYSCLR_DIALOGBACKGROUND );

     WinSetDlgItemText( hwnd, IDC_UCMNBP1FILENAME, "" );

     if ( mi.hItem && ITEM( &mi, hBmp ) ) {
     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ Query item bitmap           ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

       GpiQueryBitmapParameters( UCMData->hBmpTemp = ITEM(&mi, hBmp), &BmpInfo );
       pt.x = ( BmpInfo.cx > swp.cx ? swp.x : swp.x + ( swp.cx - BmpInfo.cx )/2 );
       pt.y = ( BmpInfo.cy > swp.cy ? swp.y : swp.y + ( swp.cy - BmpInfo.cy )/2 );
       rcl.xLeft   = 0;
       rcl.yBottom = 0;
       rcl.xRight  = swp.cx;
       rcl.yTop    = swp.cy;
       WinDrawBitmap( hPS,
                      UCMData->hBmpTemp = ITEM( &mi, hBmp ),
                      &rcl,
                      &pt,
                      0,
                      0,
                      DBM_NORMAL );
        WinSetDlgItemText( hwnd, IDC_UCMNBP1FILENAME, ITEM( &mi, pszBmp ) );
        if ( ITEM( &mi, ulFlags ) & UCMI_BMPFROMFILE ){
           UCMData->bBmpTempFromFile = TRUE;
           WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), TRUE );
        } else {
           UCMData->bBmpTempFromFile = FALSE;
           WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), FALSE );
        } // endif
     } else {
        UCMData->hBmpTemp = 0;
        UCMData->bBmpTempFromFile = FALSE;
        WinEnableWindow( WinWindowFromID( hwnd, IDB_UCMNBP1EDIT ), FALSE );
     } // endif

     WinReleasePS( hPS );


   } // endif
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP2DlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_PG2DLGPROC. name='UCMenuNBP2DlgProc' text='UCMenu settings notebook page 2 dialog procedure'.
// Dialog procedure of the page 2 of the ucmenu settings notebook
// :syntax name='UCMenuNBP2DlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Notebook page 2 window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY  UCMenuNBP2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg) {
    case WM_INITDLG:
      {
        PUCMDATA UCMData = (PUCMDATA)mp2;

        WinSetWindowULong(hwnd, QWL_USER, (ULONG)UCMData);

        UCMData->hwndPage2 = hwnd;
       /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
         ³ Set maximum length of the fields                             ³
         ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
        WinSendDlgItemMsg(hwnd,
                          IDC_UCMNBP2FLIST,
                          EM_SETTEXTLIMIT,
                          MPFROMSHORT(255),
                          (MPARAM)0);
        WinSendDlgItemMsg(hwnd,
                          IDC_UCMNBP2PARAMS,
                          EM_SETTEXTLIMIT,
                          MPFROMSHORT(255),
                          (MPARAM)0);
        UCMenuNBP2Initialize(UCMData, hwnd);
      } break;

//  case WM_ACTIVATE:
//    if (SHORT1FROMMP(mp1)) {
//      WinSendMsg(WinQueryHelpInstance(hwnd), HM_SET_ACTIVE_WINDOW,
//                 (MPARAM)hwnd, (MPARAM)hwnd);
//    } else {
//      // clear active help window when this window is deactivated - this is
//      // necessary for message box help, etc. to work properly
//      WinSendMsg(WinQueryHelpInstance(hwnd), HM_SET_ACTIVE_WINDOW,
//                 NULLHANDLE, NULLHANDLE);
//    } /* endif */
//    return WinDefDlgProc( hwnd, msg, mp1, mp2 );

    case GETTING_FOCUS:
       WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd, IDC_UCMNBP2FLIST ) );
     break;

    case WM_CONTROL:
       {
          switch ( SHORT1FROMMP( mp1 ) ) {
          case IDC_UCMNBP2FLIST:
             switch ( SHORT2FROMMP( mp1 ) ){
             case CBN_LBSELECT:
             {
                SHORT sIndex;
                CHAR pszDesc[MAXDESCLEN];
                sIndex = (USHORT)WinSendMsg( HWNDFROMMP( mp2 ), LM_QUERYSELECTION, MPFROMSHORT( LIT_FIRST ), (MPARAM)0 );
                sIndex = (USHORT)WinSendDlgItemMsg(hwnd,
                                                   IDC_UCMNBP2DLIST,
                                                   LM_QUERYITEMTEXT,
                                                   MPFROM2SHORT( sIndex, MAXDESCLEN ),
                                                   MPFROMP( pszDesc ) );
                WinSetDlgItemText( hwnd, IDC_UCMNBP2DESC, pszDesc );
                return WinDefDlgProc( hwnd, msg, mp1, mp2 );
             }
             default:
               return WinDefDlgProc( hwnd, msg, mp1, mp2 );
               break;
             } // endswitch
          default:
             return WinDefDlgProc( hwnd, msg, mp1, mp2 );
          } // endswitch

       }
     break;

    case UCMENU_ACTIONSINSERTED:
      // -- This message is posted by the owner to let me know that
      // -- the list of actions was filled. What I have to do is hilite the
      // -- current action in the list or, if it's not in it, add it to the
      // -- list and highlight it.
      { MENUITEM mi;
        PSZ      pszTxt, pszParams;
        CHAR     pszDesc[MAXDESCLEN];
        PUCMDATA UCMData;

        WinShowWindow( WinWindowFromID( hwnd, IDC_UCMNBP2LOADING ), FALSE );

        UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);

        memset(&mi, 0, sizeof(MENUITEM));

        if (!(UCMData->bItemCreation)) {
           //-- Query item
           WinSendMsg(UCMData->hwndTemp,
                      MM_QUERYITEM,
                      MPFROM2SHORT(UCMData->ContextID, TRUE),
                      MPFROMP(&mi));
        }

        if (mi.hItem) {
          pszTxt = ITEM(&mi, pszAction);
          pszParams = ITEM(&mi, pszParameters);
          if (pszTxt) {
            SHORT  sIndex;

            if (pszParams) {
              WinSetDlgItemText(hwnd, IDC_UCMNBP2PARAMS, pszParams);
            } else {
              WinSetDlgItemText(hwnd, IDC_UCMNBP2PARAMS, "");
            } /* endif */

            sIndex = (USHORT)WinSendDlgItemMsg(hwnd,
                                               IDC_UCMNBP2FLIST,
                                               LM_SEARCHSTRING,
                                               MPFROM2SHORT(LSS_CASESENSITIVE, LIT_FIRST),
                                               MPFROMP(pszTxt));
            if (sIndex==LIT_NONE || sIndex==LIT_ERROR) {
               //-- Add it to the list
               sIndex = (USHORT) WinSendDlgItemMsg(hwnd,
                                                   IDC_UCMNBP2FLIST,
                                                   LM_INSERTITEM,
                                                   (MPARAM)LIT_END,
                                                   MPFROMP(pszTxt));
               WinSendDlgItemMsg(hwnd,
                                 IDC_UCMNBP2DLIST,
                                 LM_INSERTITEM,
                                 (MPARAM)LIT_END,
                                 MPFROMP(""));
               WinSetDlgItemText(hwnd, IDC_UCMNBP2DESC, "");
            } else {
               WinSendDlgItemMsg(hwnd,
                                 IDC_UCMNBP2DLIST,
                                 LM_QUERYITEMTEXT,
                                 MPFROM2SHORT( sIndex, MAXDESCLEN ),
                                 MPFROMP( pszDesc ) );
               WinSetDlgItemText( hwnd, IDC_UCMNBP2DESC, pszDesc );
            } // endif
            //-- Select it
            WinSendDlgItemMsg(hwnd,
                              IDC_UCMNBP2FLIST,
                              LM_SELECTITEM,
                              MPFROMSHORT(sIndex),
                              MPFROMSHORT(TRUE));
          } else {
            WinSetDlgItemText(hwnd, IDC_UCMNBP2PARAMS, "");
          } /* endif */
        } /* endif */
      } break;

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
        case IDB_UCMNBP2UNDO:
             {
                PUCMDATA UCMData;
                UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
                // -- Empty the functions list because it will be filled again
                WinSendDlgItemMsg(hwnd,
                                  IDC_UCMNBP2FLIST,
                                  LM_DELETEALL,
                                  (MPARAM)0,
                                  (MPARAM)0);
                WinSendDlgItemMsg(hwnd,
                                  IDC_UCMNBP2DLIST,
                                  LM_DELETEALL,
                                  (MPARAM)0,
                                  (MPARAM)0);
                UCMenuNBP2Initialize(UCMData, hwnd);
                return(MRESULT)0;
             }

        // (MAM) removed OK and CANCEL processing...

      } /* endswitch */
      break;

    case WM_HELP:
      switch (SHORT1FROMMP(mp1)) {
      case IDB_UCMNBP2HELP:
         {
            PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER);
            UCMenuDisplayHelp( UCMData,
                       (USHORT)PANEL_ITEMACTION,
                       (USHORT)UCN_HLP_NB_ACTION);
         }
         break;
      default:
        return WinDefDlgProc( hwnd, msg, mp1, mp2 );
        break;
      } // endswitch
      break;

    default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);

  } /* endswitch */
  return (MRESULT)0;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP2Initialize : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_INITPG2. name='UCMenuNBP2Initialize' text='Initializes the page 2 of the settings notebook' .
// This function initializes the page2  of the settings notebook
// :syntax name='UCMenuNBP2Initialize' params='UCMData, hwnd' return='-' .
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input' .
// Pointer to the UCMDATA structure
// :fparam name='hwnd' type='HWND' io='input' .
// Page 2 window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuNBP2Initialize(PUCMDATA UCMData, HWND hwnd)
{

   WinSetDlgItemText(hwnd, IDC_UCMNBP2FLIST, "");
   WinSetDlgItemText(hwnd, IDC_UCMNBP2PARAMS, "");
   WinSetDlgItemText(hwnd, IDC_UCMNBP2DESC, "");
   WinShowWindow( WinWindowFromID( hwnd, IDC_UCMNBP2LOADING ), TRUE );


   /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
     ³ Add an entry in the list of actions : ExecuteProgram.        ³
     ³ It's an internal action.                                     ³
     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
   if ( !( UCMData->Style & UCS_NODEFAULTACTION ) ){
      WinSendDlgItemMsg(hwnd,
                        IDC_UCMNBP2FLIST,
                        LM_INSERTITEM,
                        (MPARAM)LIT_FIRST,
                        MPFROMP(&UCM_ACTION_EXEC));
      //-- Add the corresponding entry in the listbox of description
      //-- This listbox is not displayed, just used to store the descriptions
      WinSendDlgItemMsg(hwnd,
                        IDC_UCMNBP2DLIST,
                        LM_INSERTITEM,
                        (MPARAM)LIT_FIRST,
                        MPFROMP( nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_DESCEXEC, 0 ) ) );
   } // endif

   //-- It's better to change the way we fill the list. Now we post a message to the
   //-- owner to let him know he can fill in the list. Before, it had to be synchronous
   //-- Now, the owner can query its internal list (call an EPM macro) and fill the
   //-- listbox when he's ready
   WinSendMsg( WinQueryWindow(UCMData->hwndTemp, QW_OWNER),
               WM_CONTROL,
               MPFROM2SHORT( WinQueryWindowUShort( UCMData->hwndTemp, QWS_ID ),
                             UCN_QRYACTIONLIST ),
               MPFROMHWND( UCMData->hwndTemp ) );
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP0DlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_PG0DLGPROC. name='UCMenuNBP0DlgProc' text='UCMenu settings notebook page 0 dialog procedure'.
// Dialog procedure of the page 0 of the ucmenu settings notebook
// :syntax name='UCMenuNBP0DlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Notebook page 0 window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY  UCMenuNBP0DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg) {
    case WM_INITDLG:
      {
        PUCMDATA UCMData = (PUCMDATA)mp2;

        WinSetWindowULong(hwnd, QWL_USER, (ULONG)UCMData);
        UCMData->hwndPage0 = hwnd;
        UCMenuNBP0Initialize(UCMData, hwnd);
      }
      break;

//  case WM_ACTIVATE:
//    if (SHORT1FROMMP(mp1)) {
//      WinSendMsg(WinQueryHelpInstance(hwnd), HM_SET_ACTIVE_WINDOW,
//                 (MPARAM)hwnd, (MPARAM)hwnd);
//    } else {
//      // clear active help window when this window is deactivated - this is
//      // necessary for message box help, etc. to work properly
//      WinSendMsg(WinQueryHelpInstance(hwnd), HM_SET_ACTIVE_WINDOW,
//                 NULLHANDLE, NULLHANDLE);
//    } /* endif */
//    return WinDefDlgProc( hwnd, msg, mp1, mp2 );

    case GETTING_FOCUS:
       WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd, IDC_UCMNBP0END ) );
     break;

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
        case IDB_UCMNBP0UNDO:
             {
                PUCMDATA UCMData;
                UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
                UCMenuNBP0Initialize(UCMData, hwnd);
             }
             break;

        // (MAM) removed OK and CANCEL processing

      } /* endswitch */
      break;

    case WM_HELP:
      switch (SHORT1FROMMP(mp1)) {
      case IDB_UCMNBP0HELP:
         {
            PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER);
            UCMenuDisplayHelp( UCMData,
                       (USHORT)PANEL_ITEMPOS,
                       (USHORT) UCN_HLP_NB_CREATE);
         }
         break;
      default:
        return WinDefDlgProc( hwnd, msg, mp1, mp2 );
        break;
      } // endswitch
      break;

    default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);

  } // endswitch
  return (MRESULT)0;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP0Initialize : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_INITPG0. name='UCMenuNBP0Initialize' text='Initializes the page 0 of the settings notebook' .
// This function initializes the page 0 of the settings notebook
// :syntax name='UCMenuNBP0Initialize' params='UCMData, hwnd' return='-' .
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input' .
// Pointer to the UCMDATA structure
// :fparam name='hwnd' type='HWND' io='input' .
// Page 0 window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

VOID  _Optlink UCMenuNBP0Initialize(PUCMDATA UCMData, HWND hwnd)
{
   if (!(UCMData->ContextID)) {
     /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
       ³ No context ID means no item is selected. So the only place   ³
       ³ we can insert the item is the end. We don't need the 2       ³
       ³ buttons : we hide them.                                      ³
       ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
     WinShowWindow(WinWindowFromID(hwnd, IDC_UCMNBP0AFTER), FALSE);
     WinShowWindow(WinWindowFromID(hwnd, IDC_UCMNBP0BEFORE), FALSE);
   } /* endif */
   WinSendMsg(WinWindowFromID(hwnd, IDC_UCMNBP0END), BM_SETCHECK, (MPARAM)1, (MPARAM)0);
   WinSendMsg(WinWindowFromID(hwnd, IDC_UCMNBP0REGULAR), BM_SETCHECK, (MPARAM)1, (MPARAM)0);
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP1OK : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NBPG1OK. name='UCMenuNBP1OK' text='Processes the OK button for the page 1' .
// This function processes the OK button for the page 1 of the settings notebook
// :syntax name='UCMenuNBP1OK' params='hwnd' return='-' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Page 1 window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuNBP1OK(HWND hwnd)
{ MENUITEM mi;
  ULONG ulLen;
  PSZ   pszTitle;
  PUCMDATA UCMData;

  UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the item data  ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  memset(&mi, 0, sizeof(MENUITEM));
  WinSendMsg(UCMData->hwndCMOrig,
             MM_QUERYITEM,
             MPFROM2SHORT(UCMData->ContextID, TRUE),
             MPFROMP(&mi));

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the text       ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  ulLen = WinQueryDlgItemTextLength(hwnd, IDC_UCMNBP1TITLE);
  if (ulLen) {
    pszTitle = MyMalloc(ulLen+1);
    if (pszTitle) {
      WinQueryDlgItemText(hwnd,
                          IDC_UCMNBP1TITLE,
                          ulLen+1,
                          pszTitle);
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ Set the item text    ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      if (mi.hItem) {
         if ( !ITEM(&mi,pszText) || strcmp(ITEM(&mi,pszText),pszTitle) ) {
            WinSendMsg( WinQueryWindow(UCMData->hwndTemp, QW_OWNER),
                    WM_CONTROL,
                    MPFROM2SHORT( WinQueryWindowUShort( UCMData->hwndTemp, QWS_ID ), UCN_TEXT ),
                    MPFROMSHORT( mi.id ) );
         } // endif

        if (ITEM(&mi, pszText)) {
          PSZ OldText = ITEM(&mi, pszText);
          PSZ StrPtr;
          if(StrPtr=strstr(OldText, "~")) {
             RemoveAccelItem(UCMData, StrPtr[1]);
          }
          MyFree(ITEM(&mi, pszText));
        }

        ITEM(&mi, pszText) = pszTitle;
        if(pszTitle && pszTitle[0]){
           PSZ StrPtr;
           if(StrPtr = strstr(pszTitle, "~")) {
              AddAccelItem(UCMData, StrPtr[1], UCMData->ContextID);
           }
        }
      } // endif
      //-- don't free pszTitle !
    } // endif
  } else {
      if (mi.hItem) {
        if (ITEM(&mi, pszText)) {
          PSZ OldText = ITEM(&mi, pszText);
          PSZ StrPtr;
          if(StrPtr=strstr(OldText, "~")) {
             RemoveAccelItem(UCMData, StrPtr[1]);
          }
          MyFree(ITEM(&mi, pszText));
        }
        ITEM(&mi, pszText) = 0;
     } // endif mi.hItem
  } // endif ulLen

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Go for the bitmap now³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Is there a filename set in the dialog ?³
    ³ No means no bitmap is requested        ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  ulLen = WinQueryDlgItemTextLength(hwnd, IDC_UCMNBP1FILENAME);
  if (ulLen) {
    PSZ pszBitmap = MyMalloc(ulLen+1);

    if (pszBitmap) {
      WinQueryDlgItemText(hwnd,
                          IDC_UCMNBP1FILENAME,
                          ulLen+1,
                          pszBitmap);
      if (ITEM(&mi, pszBmp)) {
         MyFree(ITEM(&mi, pszBmp));
      } // endif
      ITEM(&mi, pszBmp) = pszBitmap;
    } // endif

    if (ITEM(&mi,hBmp)!=UCMData->hBmpTemp) {
       WinSendMsg( WinQueryWindow( UCMData->hwndTemp, QW_OWNER ),
                   WM_CONTROL,
                   MPFROM2SHORT( WinQueryWindowUShort( UCMData->hwndTemp, QWS_ID ), UCN_BITMAP ),
                   MPFROMSHORT( mi.id) );
    } // endif

    ITEM(&mi, hBmp)   =  UCMData->hBmpTemp;
    if ( UCMData->bBmpTempFromFile ){
       ITEM( &mi, ulFlags ) |= UCMI_BMPFROMFILE;
    } else {
       ITEM( &mi, ulFlags ) &= ~UCMI_BMPFROMFILE;
    } // endif
  } else {
      if (ITEM(&mi, pszBmp)) {
         MyFree(ITEM(&mi, pszBmp));
      } // endif
      ITEM(&mi, pszBmp) = 0;

    if (ITEM(&mi,hBmp)!=UCMData->hBmpTemp) {
       WinSendMsg( WinQueryWindow( UCMData->hwndTemp, QW_OWNER ),
                   WM_CONTROL,
                   MPFROM2SHORT( WinQueryWindowUShort( UCMData->hwndTemp, QWS_ID ), UCN_BITMAP ),
                   MPFROMSHORT( mi.id) );
    } // endif

    ITEM(&mi, hBmp)   =  0;
    if ( UCMData->bBmpTempFromFile ){
       ITEM( &mi, ulFlags ) |= UCMI_BMPFROMFILE;
    } else {
       ITEM( &mi, ulFlags ) &= ~UCMI_BMPFROMFILE;
    } // endif
  } // endif
  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Set the item back    ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  WinSendMsg(UCMData->hwndCMOrig,
             MM_SETITEM,
             MPFROM2SHORT(0, TRUE),
             MPFROMP(&mi));
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP2OK : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NBPG2OK. name='UCMenuNBP2OK' text='Processes the OK button for the page 2' .
// This function processes the OK button for the page 2 of the settings notebook
// :syntax name='UCMenuNBP2OK' params='hwnd' return='-' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Page 2 window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuNBP2OK(HWND hwnd)
{
  PSZ      pszFunction, pszParams;
  MENUITEM mi;
  ULONG    ulLen1, ulLen2;
  PUCMDATA UCMData;

  UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ We query the function selected by the user and the params    ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  ulLen1 = WinQueryDlgItemTextLength(hwnd, IDC_UCMNBP2FLIST) + 1;
  pszFunction = MyMalloc(ulLen1);
  ulLen2 = WinQueryDlgItemTextLength(hwnd, IDC_UCMNBP2PARAMS) + 1;
  pszParams = MyMalloc(ulLen2);
  if (pszFunction) {
    WinQueryDlgItemText(hwnd,
                        IDC_UCMNBP2FLIST,
                        ulLen1,
                        pszFunction);
    if (pszParams) {
      WinQueryDlgItemText(hwnd,
                          IDC_UCMNBP2PARAMS,
                          ulLen2,
                          pszParams);
    } /* endif */
    memset(&mi, 0, sizeof(MENUITEM));
    //-- Query item
    WinSendMsg(UCMData->hwndCMOrig,
               MM_QUERYITEM,
               MPFROM2SHORT(UCMData->ContextID, TRUE),
               MPFROMP(&mi));

    if ( !ITEM(&mi,pszAction) || strcmp(ITEM(&mi,pszAction),pszFunction) ) {
       WinSendMsg( WinQueryWindow(UCMData->hwndTemp, QW_OWNER),
               WM_CONTROL,
               MPFROM2SHORT( WinQueryWindowUShort( UCMData->hwndTemp, QWS_ID ), UCN_ACTION ),
               MPFROMSHORT( mi.id ) );
    } // endif

    if (ITEM(&mi, pszAction)){
       MyFree (ITEM(&mi, pszAction));
    }
    if (ITEM(&mi, pszParameters)){
       MyFree (ITEM(&mi, pszParameters));
    }

    ITEM(&mi, pszAction) = pszFunction;
    ITEM(&mi, pszParameters) = pszParams;
    WinSendMsg(UCMData->hwndCMOrig,
               MM_SETITEM,
               MPFROM2SHORT(0, TRUE),
               MPFROMP(&mi));
  } // endif
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuStyleDlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_STYLEDLGPROC. name='UCMenuStyleDlgProc' text='Style dialog procedure'.
// Dialog procedure of the style dialog
// :syntax name='UCMenuStyleDlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Style dialog window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY  UCMenuStyleDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg) {
    case WM_INITDLG:
      {
         PUCMDATA UCMData = (PUCMDATA)mp2;

         // Store UCMData in the user field of the dialog
         WinSetWindowULong(hwnd, QWL_USER, (ULONG)UCMData);
         InitializeStyleDlg(UCMData, hwnd);

//       if ( UCMData->hwndHelpInstance ) {
//          // -------------------------------------------------
//          // -- The contextual help would work without that
//          // -- We do it so that the focus goes back on this
//          // -- dialog after a contextual help invoked from it
//          // -- has been dismissed ( else the focus goes back
//          // -- to the closest winassociated window in the
//          // -- parent and owner chain )
//          // -------------------------------------------------
//          WinAssociateHelpInstance( UCMData->hwndHelpInstance, hwnd );
//       } // endif
      }
      break;

    case WM_CONTROL:
       switch (SHORT1FROMMP(mp1)) {
          case IDC_UCMNSTLFORCESIZE:
          {
             USHORT usChkst;

             // This checkbox used to have the opposite effect
             usChkst     = !WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLFORCESIZE);

             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCX),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCY),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCXLABEL),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCYLABEL),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLIGNORE),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLOR),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLAND),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLBOX),
                               usChkst?TRUE:FALSE);

          }
          break;
          case IDC_UCMNSTLBUBBLE:
          {
             USHORT usChkst;

             usChkst     = WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLBUBBLE);

             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLDELAY),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLREAD),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLDELAYLABEL),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLREADLABEL),
                               usChkst?TRUE:FALSE);
             WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLMSECLABEL),
                               usChkst?TRUE:FALSE);

          }
          break;
       }
       break;
    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
        case IDB_UCMNSTLOK:
          UCMenuStyleDlgOK(hwnd);
          WinDismissDlg( hwnd, TRUE );
          return (MRESULT)0;
        case IDB_UCMNSTLCANCEL:
          WinDismissDlg(hwnd, FALSE);
          break;
      } // endswitch
      break;

    case WM_HELP:
      switch (SHORT1FROMMP(mp1)) {
      case IDB_UCMNSTLHELP:
         {
            PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER);
            UCMenuDisplayHelp( UCMData,
                       (USHORT)PANEL_STYLE,
                       (USHORT)UCN_HLP_STYLE );
         }
         break;
      default:
        return WinDefDlgProc( hwnd, msg, mp1, mp2 );
        break;
      } // endswitch

    default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);

  } /* endswitch */
  return (MRESULT)0;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuDisplayHelp : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_DISPLAYHLP. name='UCMenuDisplayHelp' text='Pops up a help panel' .
// This function pops up a style dialog after eventually getting the help instance.
// :syntax name='UCMenuDisplayHelp' params='UCMData, PanelID, CustomID' return='-'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='output.
// Pointer to the UCMDATA structure
// :fparam name='PanelID' type='USHORT' io='input' .
// ID of the panel to pop up.
// :fparam name='CustomID' type='USHORT' io='input' .
// ID ID posted to the owner with UCN_HLP_*  WM_CONTROL notification code in case of custom help.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuDisplayHelp(PUCMDATA UCMData, USHORT usPanelID, USHORT usCustomID )
{

   if ( UCMData->Style & UCS_CUSTOMHLP ){
      WinSendMsg( UCMData->hwndOwner,
                  WM_CONTROL,
                  MPFROM2SHORT( UCMData->UCMenuID, usCustomID ),
                  (MPARAM)0 );
   } else {
      if ( !UCMData->hwndHelpInstance ) {
         HELPINIT      hmiHelpData;

         //-- Initialize the help
         hmiHelpData.cb                       = (ULONG) sizeof(HELPINIT);
         hmiHelpData.ulReturnCode             = 0L;
         hmiHelpData.pszTutorialName          = NULL;

         hmiHelpData.phtHelpTable             = NULL;

         hmiHelpData.hmodAccelActionBarModule = (HMODULE)NULL;
         hmiHelpData.idAccelTable             = 0L;
         hmiHelpData.idActionBar              = 0L;
         hmiHelpData.pszHelpWindowTitle       = nlsgetmessage( WinQueryAnchorBlock( UCMData->hwndMenu ), UCMData->hModUCM, NLS_UCMHLP, 0 );

         hmiHelpData.hmodHelpTableModule      = 0L;

         hmiHelpData.fShowPanelId             = 0L;
         hmiHelpData.pszHelpLibraryName       = "UCMENUS.HLP";

         UCMData->hwndHelpInstance = WinCreateHelpInstance( WinQueryAnchorBlock(UCMData->hwndOwner),
                                                            &hmiHelpData );
      } // endif
      if (UCMData->hwndHelpInstance) {
         WinSendMsg( UCMData->hwndHelpInstance,
                     HM_DISPLAY_HELP,
                     MPFROMSHORT( usPanelID ),
                     MPFROMSHORT( HM_RESOURCEID ));
      } // endif
   } // endif
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// InitializeStyleDlg : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_INITSTYLDLG. name='InitializeStyleDlg' text='Initializes the style dialog' .
// This function initializes the style dialog
// :syntax name='InitializeStyleDlg' params='UCMData, hwnd' return='-'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='output.
// Pointer to the UCMDATA structure
// :fparam name='hwnd' type='HWND' io='input' .
// Style dialog window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink InitializeStyleDlg(PUCMDATA UCMData, HWND hwnd)
{
   RECTL rect;

   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCX),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCY),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCXLABEL),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLCYLABEL),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLIGNORE),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLOR),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLAND),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLBOX),
                     (UCMData->Style&UCS_FORCESIZE)?TRUE:FALSE);

   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLDELAY),
                     (UCMData->Style&UCS_BUBBLEHELP)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLREAD),
                     (UCMData->Style&UCS_BUBBLEHELP)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLREADLABEL),
                     (UCMData->Style&UCS_BUBBLEHELP)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLDELAYLABEL),
                     (UCMData->Style&UCS_BUBBLEHELP)?TRUE:FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_UCMNSTLMSECLABEL),
                     (UCMData->Style&UCS_BUBBLEHELP)?TRUE:FALSE);

   if (UCMData->Style&UCS_FORCESIZE) {
      rect.xLeft = 0;
      rect.xRight = UCMData->cx;
      rect.yBottom = 0;
      rect.yTop = UCMData->cy;
   } else {
      USHORT usItemID;

      if ( !( usItemID = UCMData->ContextID ) ) {
         usItemID = (USHORT)WinSendMsg( UCMData->hwndCMOrig, MM_ITEMIDFROMPOSITION, MPFROMSHORT(1), (MPARAM)0 );
      }  // endif
      if ( !WinSendMsg(UCMData->hwndCMOrig, MM_QUERYITEMRECT, MPFROM2SHORT( usItemID, TRUE ), MPFROMP( &rect ) ) ){
         rect.xLeft = 0;
         rect.xRight = UCMData->cx;
         rect.yBottom = 0;
         rect.yTop = UCMData->cy;
      } // endif
   } // endif

   WinSetDlgItemShort( hwnd, IDC_UCMNSTLCX, (USHORT)(rect.xRight - rect.xLeft), FALSE );
   WinSetDlgItemShort( hwnd, IDC_UCMNSTLCY, (USHORT)(rect.yTop - rect.yBottom), FALSE );

   WinSendDlgItemMsg(hwnd, IDC_UCMNSTLBUBBLE,
              BM_SETCHECK,
              (UCMData->Style&UCS_BUBBLEHELP) ? (MPARAM)1 : (MPARAM)0,
              (MPARAM)0);

   WinSetDlgItemShort(hwnd, IDC_UCMNSTLDELAY, UCMData->BubbleDelay, FALSE);
   WinSetDlgItemShort(hwnd, IDC_UCMNSTLREAD,  UCMData->BubbleRead,  FALSE);

   WinSendDlgItemMsg(hwnd, IDC_UCMNSTLFORCESIZE,
              BM_SETCHECK,
              (UCMData->Style&UCS_FORCESIZE) ? (MPARAM)0 : (MPARAM)1,
              (MPARAM)0);
   WinSendDlgItemMsg(hwnd, IDC_UCMNSTLTEXT,
              BM_SETCHECK,
              (UCMData->Style&UCS_NOTEXT) ? (MPARAM)0 : (MPARAM)1,
              (MPARAM)0);
   WinSendDlgItemMsg(hwnd, IDC_UCMNSTLFRAMED,
              BM_SETCHECK,
              (UCMData->Style&UCS_FRAMED) ? (MPARAM)1 : (MPARAM)0,
              (MPARAM)0);
   WinSendDlgItemMsg(hwnd, IDC_UCMNSTLIGNORE,
              BM_SETCHECK,
              (UCMData->Style&UCS_SHRINK_BLEND) ? (MPARAM)0 : (MPARAM)1,
              (MPARAM)0);
   if ( UCMData->Style&UCS_SHRINK_BLEND ) {
      WinSendDlgItemMsg(hwnd, IDC_UCMNSTLOR,
                 BM_SETCHECK,
                 (UCMData->Style&UCS_SHRINK_OR) ? (MPARAM)1 : (MPARAM)0,
                 (MPARAM)0);
      WinSendDlgItemMsg(hwnd, IDC_UCMNSTLAND,
                 BM_SETCHECK,
                 (UCMData->Style&UCS_SHRINK_OR) ? (MPARAM)0 : (MPARAM)1,
                 (MPARAM)0);
   } // endif
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuStyleDlgOK : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_STYLDLGOK. name='UCMenuStyleDlgOK' text='Processes the OK button for the style dialog' .
// This function processes the OK button for the style dialog
// :syntax name='UCMenuStyleDlgOK' params='hwnd' return='-'.
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Style dialog window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuStyleDlgOK(HWND hwnd)
{
   USHORT usChkst;
   PUCMDATA UCMData;
   ULONG Style;

   UCMData = (PUCMDATA)WinQueryWindowULong(hwnd, QWL_USER);
   Style = UCMData->Style;

   usChkst = !WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLFORCESIZE);
   if (usChkst) {
      SHORT sC;

      Style |= UCS_FORCESIZE;
      WinQueryDlgItemShort( hwnd, IDC_UCMNSTLCX, &sC, FALSE );
      UCMData->cx = (sC>4)?((ULONG) sC):4lu;
      WinQueryDlgItemShort( hwnd, IDC_UCMNSTLCY, &sC, FALSE );
      UCMData->cy = (sC>10)?((ULONG) sC):10lu;
   } else {
      Style &= ~UCS_FORCESIZE;
   } // endif

   usChkst = WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLBUBBLE);
   if (usChkst) {
      SHORT sC;

      Style |= UCS_BUBBLEHELP;
      WinQueryDlgItemShort( hwnd, IDC_UCMNSTLDELAY, &sC, FALSE );
      UCMData->BubbleDelay = (ULONG) sC;
      WinQueryDlgItemShort( hwnd, IDC_UCMNSTLREAD, &sC, FALSE );
      UCMData->BubbleRead = (ULONG) sC;
   } else {
      Style &= ~UCS_BUBBLEHELP;
   } // endif



   usChkst = WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLTEXT);
   if (usChkst) {
      Style &= ~UCS_NOTEXT;
   } else {
      Style |= UCS_NOTEXT;
   } // endif

   usChkst = WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLFRAMED);
   if (usChkst) {
      Style |= UCS_FRAMED;
   } else {
      Style &= ~UCS_FRAMED;
   } // endif

   usChkst = WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLIGNORE);
   if (usChkst) {
      Style &= ~UCS_SHRINK_BLEND;
   } else {
      Style |= UCS_SHRINK_BLEND;
   } // endif

   usChkst = WinQueryButtonCheckstate(hwnd,IDC_UCMNSTLOR);
   if (usChkst) {
      Style |= UCS_SHRINK_OR;
   } else {
      Style &= ~UCS_SHRINK_OR;
   } // endif

   // Send message to update style:
   WinSendMsg(UCMData->hwndUCM, UCMENU_SETSTYLE, MPFROMLONG(Style), 
              MPFROM2SHORT(UCMData->cx, UCMData->cy));

   // Notify owner of change
   WinSendMsg( UCMData->hwndOwner,
               WM_CONTROL,
               MPFROM2SHORT( UCMData->UCMenuID, UCN_STYLE ),
               MPFROMSHORT( 0 ) );
 
   UCMenuUpdateMenu( UCMData->hwndMenu, TRUE );
}
#endif

//----------------------------------------------------------------------------
// UCMenuUpdateMenu : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UPDMENU. name='UCMenuUpdateMenu' text='Updates the display of the ucmenu' .
// This function refreshes the display of the UCMenu according to the latest changes
// :syntax name='UCMenuUpdateMenu' params='hwndMenu' return='-'.
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuUpdateMenu( HWND hwndMenu, BOOL UpdateSubmenus )
{
   MENUITEM mi;
   USHORT ItemID;
   ULONG Item, NumberOfItems;
   SWP    swp;
   PUCMDATA UCMData;
   ULONG OldMaxVerticalWidth;
   ULONG OldMaxHorizontalHeight;
   BOOL    UCMSizeChanged = 0;
   HWND hwndUCM = WinQueryWindow(hwndMenu, QW_OWNER);
   ULONG Style = WinQueryWindowULong(hwndUCM, QWL_STYLE);

   UCMData = (PUCMDATA)WinQueryWindowULong(hwndUCM,QWL_UCMDATA);

   /* If update is disabled by owner, don't do this */
   if (UCMData->DisableUpdate)
     return;

   //(MAM) Submenus must be updated if anything has changed that
   // could change the size of the submenu items (e.g. text on
   // a submenu item, forced size change, various style changes, etc).
   // Normally, PM asks for the size of submenu items only once (the
   // first time they are drawn) and assumes they nver change -- even
   // if the submenu is dismissed and re-started.  To trick PM into
   // resizing the submenu items, we make a no-affect change to the
   // presentation parameters.  When that happens, PM will send us
   // WM_MEASUREITEM messages again, giving us the chance to change the
   // item sizes. 

   if (UpdateSubmenus) {
     if (UCMData->pszFontNameSize != NULL)
       WinSetPresParam( UCMData->hwndMenu,
                      PP_FONTNAMESIZE,
                      strlen(UCMData->pszFontNameSize)+1,
                      UCMData->pszFontNameSize);
     else
       WinSetPresParam( UCMData->hwndMenu,
                      PP_FONTNAMESIZE,
                      strlen(UCM_DEFAULTFONT)+1,
                      UCM_DEFAULTFONT);
   }

   OldMaxHorizontalHeight = UCMData->MaxHorizontalHeight;
   OldMaxVerticalWidth    = UCMData->MaxVerticalWidth;

   NumberOfItems = (ULONG)WinSendMsg( hwndMenu,
                                     MM_QUERYITEMCOUNT, 0L, 0L);
   for(Item=0; Item<NumberOfItems; Item++) {
      ItemID = (USHORT)WinSendMsg(hwndMenu,
                                  MM_ITEMIDFROMPOSITION,
                                  MPFROMSHORT(Item),
                                  (MPARAM)0);

      WinSendMsg(hwndMenu,
                 MM_QUERYITEM,
                 MPFROM2SHORT(ItemID, TRUE),
                 MPFROMP(&mi));

      WinSendMsg(hwndMenu,
                 MM_SETITEM,
                 MPFROM2SHORT(0, TRUE),
                 MPFROMP(&mi));
   }

   GetMaxItemSize(UCMData, hwndUCM, hwndMenu);

   UCMenuSize(hwndMenu, Style);
 
   WinQueryWindowPos(UCMData->hwndUCM, &swp);

   if (Style & CMS_MATRIX) {
     USHORT Count, Rows;
     Count = (USHORT)WinSendMsg(hwndMenu, MM_QUERYITEMCOUNT, MPVOID, MPVOID);
     /* Calculate actual size of matrix menu */
     if ((Style & CMS_MATRIX_HORZ) != CMS_MATRIX_HORZ)
       swp.cx = min(Count,UCMData->NbOfCols) * UCMData->MaxVerticalWidth    + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;

     Rows = Count / max(1,UCMData->NbOfCols);  // Full rows (don't div by zero!)
     if ((Rows * UCMData->NbOfCols) < Count)   // Partial row?
       Rows++;
     if ((Style & CMS_MATRIX_VERT) != CMS_MATRIX_VERT)
       swp.cy = Rows * UCMData->MaxHorizontalHeight + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
     /* This would be theoretical size based on num of rows and cols given by creator */
//   swp.cx = UCMData->MaxVerticalWidth    * UCMData->NbOfCols + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
//   swp.cy = UCMData->MaxHorizontalHeight * UCMData->NbOfRows + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
     if ((UCMData->MaxHorizontalHeight != OldMaxHorizontalHeight) ||
        (UCMData->MaxVerticalWidth != OldMaxVerticalWidth))
       UCMSizeChanged = 1;
    }

   if (Style & CMS_VERT ) {
     swp.cx = UCMData->MaxVerticalWidth + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
     if (UCMData->MaxVerticalWidth != OldMaxVerticalWidth)
       UCMSizeChanged = 1;
   } /* endif */

   if (Style & CMS_HORZ) {
     swp.cy = UCMData->MaxHorizontalHeight + SUM_UCM_FRAME_THICK + SUM_MENU_FRAME_THICK;
     if (UCMData->MaxHorizontalHeight != OldMaxHorizontalHeight)
       UCMSizeChanged = 1;
   } /* endif */

   WinSetWindowPos(UCMData->hwndUCM, HWND_TOP, 0, 0, swp.cx, swp.cy, SWP_SIZE);

   /* Size change notification depends on style of the menu (horz style  */
   /* notifies only if vert dimension changes, vert style notifies only  */
   /* if horz dimension changes, matrix notifies if either change).      */

   if ( UCMSizeChanged ) {
      WinSendMsg( UCMData->hwndOwner,
                  WM_CONTROL,
                  MPFROM2SHORT( UCMData->UCMenuID, UCN_SIZE ),
                  MPFROMSHORT( 0 ) );
   } // endif
 
   UCMenuUnselectAll( hwndMenu );
}


//----------------------------------------------------------------------------
// UCMenuUnselectAll : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UNSELALL. name='UCMenuUnselectAll' text='Unselects all the item of a menu' .
// This function unselects all the items of a menu and closes the open submenus
// :syntax name='UCMenuUnselectAll' params='hwndMenu' return='-'.
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink    UCMenuUnselectAll(HWND hwndMenu)
{
   WinSendMsg( hwndMenu, MM_SELECTITEM, MPFROM2SHORT( MIT_NONE, TRUE ), MPFROM2SHORT( 0, TRUE ));
}

//----------------------------------------------------------------------------
// UCMenuGetNewID : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NEWID. name='UCMenuGetNewID' text='Get an unused menu ID' .
// This function returns an unused menu ID
// :syntax name='UCMenuGetNewID' params='hwndMenu, sID, UCMData' return='ID'.
// :fparams.
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle.
// :fparam name='sID' type='SHORT' io='input' .
// ID used if it doesn't exist already, or MIT_NONE
// :fparam name='UCMData' type='PUCMDATA' io='input' .
// UCMData structure associated to the menu, it may not be yet in the QWL_USER
// :freturns.
// :fparam name='ID' type='USHORT' io='return'.
// Max of the IDs + 1 or min - 1 or 0 if failed
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
USHORT _Optlink UCMenuGetNewID(HWND hwndMenu, SHORT sID, PUCMDATA UCMData)
{
  USHORT   NbOfItems=0, ItemID=0, usIndex=0;
  MENUITEM mi;
  BOOL     bIDFound;

  if ( sID == MIT_NONE ){
     bIDFound = TRUE;
  } else {
     bIDFound = FALSE;
  } // endif

  memset(&mi, 0, sizeof(MENUITEM));

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the Number of menu items ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  NbOfItems = (USHORT)WinSendMsg(hwndMenu,
                                 MM_QUERYITEMCOUNT,
                                 (MPARAM)0,
                                 (MPARAM)0);

  for (usIndex=0 ; usIndex<NbOfItems ; usIndex++) {
    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query the item id ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    ItemID = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(usIndex),
                               (MPARAM)0);
    if ( ItemID == sID ) {
       bIDFound = TRUE;
    } // endif

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Get the max & min ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    if (ItemID>UCMData->MaxID && ItemID<0xFFF0)
      UCMData->MaxID = ItemID;

    if (ItemID<(UCMData->MinID) && ItemID>0) {
      UCMData->MinID = ItemID;
    } /* endif */

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Submenu ?         ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    WinSendMsg(hwndMenu,
               MM_QUERYITEM,
               MPFROM2SHORT(ItemID, FALSE),
               MPFROMP(&mi));

    if (mi.hwndSubMenu) {
      /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
        ³ recursive call    ³
        ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
      USHORT usSubMenuFound = UCMenuGetNewID( mi.hwndSubMenu, sID, UCMData );
      if ( (LONG)usSubMenuFound != (LONG)sID ){
         bIDFound = TRUE;
      } // endif
    } /* endif */
  } /* endfor */

  if ( !bIDFound ) {
     return sID;
  } // endif

  if (UCMData->MaxID < 0xFFF0) {
    ItemID = UCMData->MaxID + 1;
  } else
  if (UCMData->MinID > 1) {
    ItemID = UCMData->MinID - 1;
  } else {
    ItemID = 0;
  } /* endif */
  return (ItemID);
}

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP0OK : Not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NBPG0OK. name='UCMenuNBP0OK' text='Processes the OK button for the page 0' .
// This function processes the OK button for the page 0 of the settings notebook
// :syntax name='UCMenuNBP0OK' params='hwndPage' return='-' .
// :fparams.
// :fparam name='hwndPage' type='HWND' io='input' .
// Page 0 window handle.
// :freturns.
// :fparam name='-' type='BOOL' io='-'.
// True if processed OK.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
BOOL _Optlink UCMenuNBP0OK(HWND hwndPage)
{
  MENUITEM mi, oldmi;
  USHORT   usState = 0;
  PUCMDATA UCMData;

  UCMData = (PUCMDATA)WinQueryWindowULong(hwndPage, QWL_USER);

  memset(&mi, 0, sizeof(MENUITEM));

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the state of the check box                             ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  usState = (USHORT)WinSendDlgItemMsg(UCMData->hwndPage0,
                                      IDC_UCMNBP0STATIC,
                                      BM_QUERYCHECK,
                                      (MPARAM)0,
                                      (MPARAM)0);
  if ( usState ){
     mi.afStyle = MIS_STATIC | MIS_OWNERDRAW;
  } else {
     usState = (USHORT)WinSendDlgItemMsg(UCMData->hwndPage0,
                                         IDC_UCMNBP0REGULAR,
                                         BM_QUERYCHECK,
                                         (MPARAM)0,
                                         (MPARAM)0);
     if ( usState ) {
        mi.afStyle = MIS_OWNERDRAW;
     } else {
        mi.afStyle = ( MIS_SPACER | MIS_OWNERDRAW ) & ~MIS_TEXT;
     } // endif
  } // endif

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the position                                           ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  WinSendMsg(UCMData->hwndTemp,
             MM_QUERYITEM,
             MPFROM2SHORT(UCMData->ContextID, TRUE),
             MPFROMP(&oldmi));

  usState = (USHORT)WinSendDlgItemMsg(UCMData->hwndPage0,
                                      IDC_UCMNBP0END,
                                      BM_QUERYCHECK,
                                      (MPARAM)0,
                                      (MPARAM)0);
  if (usState) {
    mi.iPosition = MIT_END;
  } else {
    usState = (USHORT)WinSendDlgItemMsg(UCMData->hwndPage0,
                                        IDC_UCMNBP0AFTER,
                                        BM_QUERYCHECK,
                                        (MPARAM)0,
                                        (MPARAM)0);
    if (usState) {
      mi.iPosition = oldmi.iPosition + 1;
    } else {
      mi.iPosition = oldmi.iPosition;
    } // endif
  } // endif

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Query the item ID                                            ³
    ³ We actually have to find an unused one.                      ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  UCMData->MaxID = 0;
  UCMData->MinID = 0xFFFF;
  mi.id = UCMenuGetNewID( UCMData->hwndMenu, MIT_NONE, UCMData ) + 1;

  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³Create the item handle structure ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  mi.hItem = (LONG)MyMalloc(sizeof(UCMITEM));
  if (mi.hItem) {
    ULONG ulLen;

    memset((PVOID)mi.hItem, 0, sizeof(UCMITEM));

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Query title text                ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    ulLen = WinQueryDlgItemTextLength(UCMData->hwndPage1, IDC_UCMNBP1TITLE);
    if (ulLen) {
      PSZ pszTitle = MyMalloc(ulLen+1);
      if (pszTitle) {
        PSZ StrPtr;
        WinQueryDlgItemText(UCMData->hwndPage1,
                            IDC_UCMNBP1TITLE,
                            ulLen+1,
                            pszTitle);
        ITEM(&mi, pszText) = pszTitle;
        if(StrPtr = strstr(pszTitle, "~")) {
           if(StrPtr[1]) {
              AddAccelItem(UCMData, StrPtr[1], mi.id);
           }
        }
      } /* endif */
    } /* endif */

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Go for the bitmap               ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/

    //---- Is there a file name specified in the dialog ?
    ulLen = WinQueryDlgItemTextLength(UCMData->hwndPage1, IDC_UCMNBP1FILENAME);
    if (ulLen) {
      PSZ pszBitmap = MyMalloc(ulLen+1);

      if (pszBitmap) {
        WinQueryDlgItemText(UCMData->hwndPage1,
                            IDC_UCMNBP1FILENAME,
                            ulLen+1,
                            pszBitmap);
        ITEM(&mi, pszBmp) = pszBitmap;
      } /* endif */
      ITEM(&mi, hBmp)    = UCMData->hBmpTemp;
      if ( UCMData->bBmpTempFromFile ){
         ITEM( &mi, ulFlags ) |= UCMI_BMPFROMFILE;
      } else {
         ITEM( &mi, ulFlags ) &= ~UCMI_BMPFROMFILE;
      } // endif
    } /* endif */

    /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
      ³ Go for the action               ³
      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
    if ( ! ( mi.afStyle & MIS_SPACER ) ){
      // We don't want any actions associated with spacer items
      PSZ      pszFunction, pszParams;
      ULONG    ulLen1, ulLen2;

      ulLen1 = WinQueryDlgItemTextLength(UCMData->hwndPage2, IDC_UCMNBP2FLIST) + 1;
      ulLen2 = WinQueryDlgItemTextLength(UCMData->hwndPage2, IDC_UCMNBP2PARAMS) + 1;
      pszFunction = MyMalloc(ulLen1);
      pszParams   = MyMalloc(ulLen2);
      if (pszFunction) {
         WinQueryDlgItemText( UCMData->hwndPage2,
                              IDC_UCMNBP2FLIST,
                              ulLen1,
                              pszFunction );
         if (pszParams) {
            WinQueryDlgItemText( UCMData->hwndPage2,
                                 IDC_UCMNBP2PARAMS,
                                 ulLen2,
                                 pszParams );
         } // endif

         ITEM(&mi, pszAction) = pszFunction;
         ITEM(&mi, pszParameters) = pszParams;

      } /* endif */

    } // endif
  } /* endif */


  ITEM(&mi, pszData) = NULL;

  //-- Last check-up before adding item :
  /*ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
    ³ Last check-up before we add the item ³
    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ*/
  if (mi.hItem && ((ITEM(&mi, hBmp) && ITEM(&mi, pszBmp))||ITEM(&mi,pszText)||(mi.afStyle & MIS_SPACER))) {
     WinSendMsg(UCMData->hwndCMOrig,
                MM_INSERTITEM,
                MPFROMP(&mi),
                (MPARAM)0);
    return TRUE;
  } else {
       WinMessageBox(HWND_DESKTOP,
                     HWND_DESKTOP,
                     nlsgetmessage( WinQueryAnchorBlock( hwndPage ), UCMData->hModUCM, NLS_ITEMADDERROR, 0 ),
                     nlsgetmessage( WinQueryAnchorBlock( hwndPage ), UCMData->hModUCM, NLS_ERROR, 1 ),
                     0,
                     MB_OK | MB_ERROR | MB_APPLMODAL);
       return FALSE;
  } /* endif */
}
#endif

//----------------------------------------------------------------------------
// UCMenuExecuteProgram :
//----------------------------------------------------------------------------
// :pfunction res=&IDF_EXECPRGM. name='UCMenuExecuteProgram' text='Executes a program' .
// This function executes the specified .EXE
// :syntax name='UCMenuExecuteProgram' params='pszProgName' return='-' .
// :fparams.
// :fparam name='psz' type='PSZ' io='input' .
// String containing the name of the program, followed by some parameters.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// The program is executed synchronously in the same thread.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _System UCMenuExecuteProgram(PSZ pszName)
{
  PSZ   pszAppli, pszParams;
  ULONG ulLen;

  if (pszName) {
    ulLen = strlen(pszName) + 2;
    pszParams = MyMalloc(ulLen);
    if (pszParams) {
      PSZ psz;
      strcpy(pszParams, pszName);
      MyFree( pszName );
      pszParams[ulLen-1] = '\0';
      psz = strchr(pszParams, ' ');
      if (psz) {
         *psz = '\0';
         pszAppli = MyStrdup(pszParams);
      } else {
         pszAppli = pszParams;
         pszParams = 0;
      } // endif
      if (pszAppli) {
        RESULTCODES res;

        DosExecPgm(NULL,
                   0,
                   EXEC_SYNC,
                   pszParams,
                   NULL,
                   &res,
                   pszAppli);
        MyFree(pszAppli);
      } /* endif */
      MyFree(pszParams);
    } /* endif */
  } /* endif */
}

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuEditBmpFileT2
//----------------------------------------------------------------------------
// :pfunction res=&IDF_EDITBMPFILET2. name='UCMenuEditBmpFileT2' text='Edit a bitmap file' .
// This function starts iconedit with the provided bitmap file name.
// It is started by UCMenuEditBmpFile in a second thread.
// :syntax name='UCMenuEditBmpFileT2' params='pArgs' return='-' .
// :fparams.
// :fparam name='pArgs' type='PVOID' io='input' .
// Points to &colon.
// :dl compact.
// :dt.hwnd
// :dd.HWND, handle of the calling notebook page.
// :dt.pszFileName
// :dd.PSZ, bitmap file name, freed by UCMenuEditBmpFileT2.
// Freed by UCMenuEditBmpFileT2.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// The calling convention must be _System because this function
// is used in a DosCreateThread.
// :related.
// UCMenuEditBmpFile
// :epfunction.
//----------------------------------------------------------------------------
VOID _System UCMenuEditBmpFileT2(PVOID pArgs)
{
   if ( pArgs ) {
      PSZ pszArgs, pszFileName, pszIndex;
      ULONG ulFileNameLength, ulEditorNameLength;
      PSZ pszBmpEditorName = "iconedit.exe";
      HWND hwndNBP1;
      RESULTCODES resultCodes;
      HAB hab;
      HMQ hmq;
      PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwndNBP1, QWL_USER );

      hab = WinInitialize(0);
      hmq = WinCreateMsgQueue( hab, 0 );
      hwndNBP1 = *( (HWND *)pArgs );

      WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1LOAD ),   FALSE );
      WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1CREATE ), FALSE );
      WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1EDIT ),   FALSE );
      WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1PREDEFINED ),   FALSE );

      pszFileName = *( (PSZ*)( (HWND*)pArgs + 1 ) );

      ulEditorNameLength = strlen( pszBmpEditorName );
      ulFileNameLength = strlen( pszFileName );

      pszArgs = MyMalloc( ulEditorNameLength + ulFileNameLength + 3 );
      strcpy( pszArgs, pszBmpEditorName );
      pszIndex = pszArgs + ulEditorNameLength + 1;
      strcpy( pszIndex, pszFileName );
      *( pszIndex + ulFileNameLength + 1 ) = '\0';

      if ( DosExecPgm( NULL, (LONG)0, EXEC_SYNC, pszArgs, NULL, &resultCodes, pszBmpEditorName ) ){
        WinMessageBox( HWND_DESKTOP, hwndNBP1,
                       nlsgetmessage( hab, UCMData->hModUCM, NLS_ERROR, 3 ),
                       nlsgetmessage( hab, UCMData->hModUCM, NLS_NOICESTART, 4 ),
                       0, MB_OK | MB_ICONEXCLAMATION );
      }

      MyFree( pszArgs );
      MyFree( pArgs );

      if (resultCodes.codeTerminate==TC_EXIT) {
         WinSendMsg( hwndNBP1, UCMNBP1_NEWBMP, MPFROMP( pszFileName ), (MPARAM)0 );
      } else {
         WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1LOAD ),   TRUE );
         WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1CREATE ), TRUE );
         WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1EDIT ),   TRUE );
         WinEnableWindow( WinWindowFromID( hwndNBP1, IDB_UCMNBP1PREDEFINED ),   TRUE );
      } // endif

      MyFree( pszFileName );

      WinDestroyMsgQueue( hmq );
      WinTerminate( hab );
   } // endif
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuEditBmpFile
//----------------------------------------------------------------------------
// :pfunction res=&IDF_EDITBMPFILE. name='UCMenuEditBmpFile' text='Edit a bitmap file' .
// This function starts UCMenuEditBmpFileT2 in a second thread.
// :syntax name='UCMenuEditBmpFile' params='hwndNBP1, pszBmpFileName' return='-' .
// :fparams.
// :fparam name='hwndNBP1' type='HWND' io='input' .
// Handle of the calling notebook page.
// :fparam name='pszBmpFileName' type='PSZ' io='input' .
// Name of the bitmap file to edit, freed by UCMenuEditBmpFileT2.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// UCMenuEditBmpFileT2
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuEditBmpFile(HWND hwndNBP1, PSZ pszBmpFileName)
{
   TID tid;
   PVOID pArgs;
   PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwndNBP1, QWL_USER );

   pArgs =  MyMalloc( sizeof( HWND ) + sizeof( PSZ ) );

   if ( pArgs && pszBmpFileName ) {
      *( (HWND *)pArgs ) = hwndNBP1;
      *( (PSZ*)( (HWND *)pArgs + 1 ) ) = pszBmpFileName;
      if ( DosCreateThread( &tid, (PFNTHREAD)UCMenuEditBmpFileT2, (ULONG)pArgs, 0, 8192 ) ){
         WinMessageBox( HWND_DESKTOP, hwndNBP1,
                        nlsgetmessage( WinQueryAnchorBlock( hwndNBP1 ), UCMData->hModUCM, NLS_ERROR, 0 ),
                        nlsgetmessage( WinQueryAnchorBlock( hwndNBP1 ), UCMData->hModUCM, NLS_NOICESTART, 1 ),
                        0, MB_OK | MB_ICONEXCLAMATION );
       } // endif
   } else {
      WinMessageBox( HWND_DESKTOP, hwndNBP1,
                     nlsgetmessage( WinQueryAnchorBlock( hwndNBP1 ), UCMData->hModUCM, NLS_ERROR, 0 ),
                     nlsgetmessage( WinQueryAnchorBlock( hwndNBP1 ), UCMData->hModUCM, NLS_NOBMPFN, 1 ),
                     0, MB_OK | MB_ICONEXCLAMATION );
   } // endif

}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuCreateBmpFile
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CREATEBMPFILE. name='UCMenuCreateBmpFile' text='Create a bitmap file' .
// This function create a 16 color bitmap file given a name and size.
// :syntax name='UCMenuCreateBmpFile' params='pszBmpFileName, cx, cy, bpp' return='bSuccess' .
// :fparams.
// :fparam name='pszBmpFileName' type='PSZ' io='input' .
// Name of the bitmap file to create.
// :fparam name='cx' type='ULONG' io='input' .
// Width in pixels of the bitmap.
// :fparam name='cy' type='ULONG' io='input' .
// Height in pixels of the bitmap.
// :freturns.
// :fparam name='bSuccess' type='BOOL' io='return'.
// True if successful.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
BOOL _Optlink UCMenuCreateBmpFile( PSZ pszBmpFileName, ULONG cx, ULONG cy )
{
  FILEHANDLE              File;
  ULONG                   rc;
  PBITMAPFILEHEADER2      pbfh2  = NULL;
  PBITMAPINFOHEADER2      pbih2  = NULL;
  PBITMAPINFO2            pbmi2  = NULL;
  ULONG                   ulColorTableSize;
  PBYTE                   pData  = NULL;
  ULONG                   ulDataSize;
  BOOL                    bSuccess = FALSE;

  //--- open the file
  File = OPENWRITE( pszBmpFileName );
  if (File == NULLFILE){
     goto ExitLoadBMP;
  } // endif

  /* Write the bitmap info header............................................*/
  ulColorTableSize = 16 * sizeof( RGB2 );
  pbfh2 = ( PBITMAPFILEHEADER2 )MyMalloc( sizeof( *pbfh2 ) + ulColorTableSize );
  if ( !pbfh2 ){
     goto ExitLoadBMP;
  } // endif

  // Fill in the BITMAPFILEHEADER2 structure
  pbfh2->usType  = BFT_BMAP;
  pbfh2->cbSize  = sizeof( *pbfh2 );
  pbfh2->offBits = sizeof( *pbfh2 ) + ulColorTableSize;

  /* We now assign a bunch of pointers to make the code more readable........*/
  pbih2 = &pbfh2->bmp2;
  pbmi2 = (PBITMAPINFO2)pbih2;

  // Fill in the BITMAPFILEINFOHEADER2 structure
  memset(  pbih2, '\0', sizeof( *pbih2 ) );
  pbih2->cbFix = sizeof( *pbih2 );
  pbih2->cx = cx;
  pbih2->cy = cy;
  pbih2->cPlanes = 1;
  pbih2->cBitCount = 4;

  // Now fill in the color table
  pbmi2->argbColor[0].bRed      = 0;
  pbmi2->argbColor[0].bGreen    = 0;
  pbmi2->argbColor[0].bBlue     = 0;
  pbmi2->argbColor[0].fcOptions = 0;
  pbmi2->argbColor[1].bRed      = 0;
  pbmi2->argbColor[1].bGreen    = 0;
  pbmi2->argbColor[1].bBlue     = 0x80;
  pbmi2->argbColor[1].fcOptions = 0;
  pbmi2->argbColor[2].bRed      = 0;
  pbmi2->argbColor[2].bGreen    = 0x80;
  pbmi2->argbColor[2].bBlue     = 0;
  pbmi2->argbColor[2].fcOptions = 0;
  pbmi2->argbColor[3].bRed      = 0;
  pbmi2->argbColor[3].bGreen    = 0x80;
  pbmi2->argbColor[3].bBlue     = 0x80;
  pbmi2->argbColor[3].fcOptions = 0;
  pbmi2->argbColor[4].bRed      = 0x80;
  pbmi2->argbColor[4].bGreen    = 0;
  pbmi2->argbColor[4].bBlue     = 0;
  pbmi2->argbColor[4].fcOptions = 0;
  pbmi2->argbColor[5].bRed      = 0x80;
  pbmi2->argbColor[5].bGreen    = 0;
  pbmi2->argbColor[5].bBlue     = 0x80;
  pbmi2->argbColor[5].fcOptions = 0;
  pbmi2->argbColor[6].bRed      = 0x80;
  pbmi2->argbColor[6].bGreen    = 0x80;
  pbmi2->argbColor[6].bBlue     = 0;
  pbmi2->argbColor[6].fcOptions = 0;
  pbmi2->argbColor[7].bRed      = 0x80;
  pbmi2->argbColor[7].bGreen    = 0x80;
  pbmi2->argbColor[7].bBlue     = 0x80;
  pbmi2->argbColor[7].fcOptions = 0;
  pbmi2->argbColor[8].bRed      = 0xC9;
  pbmi2->argbColor[8].bGreen    = 0xC9;
  pbmi2->argbColor[8].bBlue     = 0xC9;
  pbmi2->argbColor[8].fcOptions = 0;
  pbmi2->argbColor[9].bRed      = 0;
  pbmi2->argbColor[9].bGreen    = 0;
  pbmi2->argbColor[9].bBlue     = 0xFF;
  pbmi2->argbColor[9].fcOptions = 0;
  pbmi2->argbColor[10].bRed      = 0;
  pbmi2->argbColor[10].bGreen    = 0xFF;
  pbmi2->argbColor[10].bBlue     = 0;
  pbmi2->argbColor[10].fcOptions = 0;
  pbmi2->argbColor[11].bRed      = 0;
  pbmi2->argbColor[11].bGreen    = 0xFF;
  pbmi2->argbColor[11].bBlue     = 0xFF;
  pbmi2->argbColor[11].fcOptions = 0;
  pbmi2->argbColor[12].bRed      = 0xFF;
  pbmi2->argbColor[12].bGreen    = 0;
  pbmi2->argbColor[12].bBlue     = 0;
  pbmi2->argbColor[12].fcOptions = 0;
  pbmi2->argbColor[13].bRed      = 0xFF;
  pbmi2->argbColor[13].bGreen    = 0;
  pbmi2->argbColor[13].bBlue     = 0xFF;
  pbmi2->argbColor[13].fcOptions = 0;
  pbmi2->argbColor[14].bRed      = 0xFF;
  pbmi2->argbColor[14].bGreen    = 0xFF;
  pbmi2->argbColor[14].bBlue     = 0;
  pbmi2->argbColor[14].fcOptions = 0;
  pbmi2->argbColor[15].bRed      = 0xFF;
  pbmi2->argbColor[15].bGreen    = 0xFF;
  pbmi2->argbColor[15].bBlue     = 0xFF;

  /* We write a 2.0 image and so we write a bitmap-file header-2 structure...*/
  rc = WRITEFILE( pbfh2, 1, sizeof( *pbfh2 ) + ulColorTableSize, File );
  // ! The prototype of fwrite says that the number should be after the size, but
  // only their product matters, and having the size instead of the number when
  // there is only one item allows better error checking
  if ( rc != ( sizeof( *pbfh2 ) + ulColorTableSize ) ){
     goto ExitLoadBMP;
  } // endif

  /* Read the bitmap data, the read size is derived using the magic formula..*/
  /* The bitmap scan line is aligned on a doubleword boundary................*/
  /* The size of the scan line is the number of pels times the bpp...........*/
  /* After aligning it, we divide by 4 to get the number of bytes, and.......*/
  /* multiply by the number of scan lines and the number of pel planes.......*/
  ulDataSize = ( ( ( 4 * cx ) + 31) / 32) * 4 * cy;
  pData = ( PBYTE )MyMalloc( ulDataSize );
  if ( !pData ){
     goto ExitLoadBMP;
  }
  memset( pData, '\0', ulDataSize );
  rc = WRITEFILE( pData, 1, ulDataSize, File );
  if ( rc != ulDataSize ){
     goto ExitLoadBMP;
  } // endif

  bSuccess = TRUE;

ExitLoadBMP:
  if ( pData ){
     MyFree(pData);
  } // endif
  if ( pbfh2 ){
     MyFree( pbfh2 );
  } // endif
  CLOSEFILE( File );
  return bSuccess;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuNBP1UpdateBmp
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NBP1UPDBMP. name='UCMenuNBP1UpdateBmp' text='Update the display of the bitmap in the notebook' .
// Sets the bitmap of the page 1 of the notebook.
// :syntax name='UCMenuNBP1UpdateBmp' params='hwnd, hBmp, pszFileName' return='-' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Handle of the notebook page 1
// :fparam name='hBmp' type='HBITMAP' io='input' .
// Handle of the bitmap.
// :fparam name='pszFileName' type='PSZ' io='input' .
// File name to display for the bitmap.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuNBP1UpdateBmp(HWND hwnd, PSZ pszFileName)
{
   RECTL  rcl;
   SWP    swp;
   HPS    hPS = WinGetPS( hwnd );

   WinQueryWindowPos( WinWindowFromID( hwnd, IDC_UCMNBP1BITMAP ), &swp );

   rcl.xLeft   = swp.x;
   rcl.yBottom = swp.y;
   rcl.xRight  = swp.x + swp.cx;
   rcl.yTop    = swp.y + swp.cy;
   WinFillRect( hPS, &rcl, SYSCLR_DIALOGBACKGROUND );

   WinReleasePS(hPS);

   WinInvalidateRect( hwnd, &rcl, TRUE );

   WinSetDlgItemText(hwnd,
                     IDC_UCMNBP1FILENAME,
                     pszFileName);

}
#endif

//----------------------------------------------------------------------------
// UCMenuLoadDefault
//----------------------------------------------------------------------------
// :function res=&IDF_UCMLOADDEF. name='UCMenuLoadDefault' text='Loads the default new ucmenu'.
// This function updates the ucmenu with the default template.
// :syntax name='UCMenuLoadDefault' params='hwndUCMenu' return='bSuccess' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// Handle of the ucmenu
// :freturns.
// :fparam name='bSuccess' type='BOOL' io='return'.
// True if successful, FALSE else
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY UCMenuLoadDefault( HWND hwndUCMenu )
{
  MRESULT mr;
  PVOID   pTmplt;
  HMODULE hModule = NULLHANDLE;
  USHORT  MenuID  = 0;
  HWND    hwndNewMenu = NULLHANDLE, hwndOldMenu;
  ULONG   ulVersion = UCMTMPLVERSION;
  PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong(hwndUCMenu, QWL_UCMDATA);

  WinSendMsg( UCMData->hwndOwner,
                              WM_CONTROL,
                              MPFROM2SHORT( UCMData->UCMenuID,
                                            UCN_QRYTEMPLATEMODULE ),
                              MPFROMP(&hModule));
  hwndOldMenu = UCMData->hwndMenu;

  mr = WinSendMsg( UCMData->hwndOwner,
                                   WM_CONTROL,
                                   MPFROM2SHORT( UCMData->UCMenuID,
                                                 UCN_QRYDEFTEMPLATEID ),
                                   MPFROMP( &MenuID ) );
  if ( mr ){
     hwndNewMenu = WinLoadMenu( HWND_OBJECT,
                                hModule,
                                MenuID );
  } else {
     mr = WinSendMsg( UCMData->hwndOwner,
                                      WM_CONTROL,
                                      MPFROM2SHORT( UCMData->UCMenuID,
                                                    UCN_QRYDEFTEMPLATE ),
                                      MPFROMP( &pTmplt ) );

     if ( mr ){
        if ( *( (PULONG)pTmplt ) == UCMTMPLSIG ){
           ulVersion = *( (PULONG)( (PBYTE)pTmplt + 4 ) );
           hwndNewMenu = WinCreateMenu( HWND_OBJECT, (PVOID)((PBYTE)pTmplt + 8 ) );
        } else {
//           ulVersion = 0;
//           hwndNewMenu = WinCreateMenu( HWND_OBJECT, pTmplt );
           return FALSE;
        } // endif
        MyFree( pTmplt );
     } /* endif */
  } /* endif */

  if ( hwndNewMenu ) {
     UCMData->AccelTable->cAccel = 0;
     UCMenuLoadMenuData( hwndNewMenu, UCMData, ulVersion, hwndUCMenu );
     UCMenuReplaceMenu( hwndOldMenu, hwndNewMenu );
  } /* endif */

  return TRUE;
}

//----------------------------------------------------------------------------
// UCMenuNew
//----------------------------------------------------------------------------
// :function res=&IDF_UCMNEW. name='UCMenuNew' text='Loads a new menu in the ucmenu'.
// This function updates the ucmenu with a new template.
// :syntax name='UCMenuNew' params='hwndUCMenu, pTemplate' return='bSuccess' .
// :fparams.
// :fparam name='hwndUCMenu' type='HWND' io='input' .
// Handle of the ucmenu
// :fparam name='pTemplate' type='PVOID' io='input' .
// Template of the new menu.
// :freturns.
// :fparam name='bSuccess' type='BOOL' io='return'.
// True if successful, FALSE else
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
BOOL APIENTRY UCMenuNew( HWND hwndUCMenu, PVOID pTemplate )
{
   HWND  hwndScroll = WinQueryWindow( hwndUCMenu, QW_TOP );
   HWND  hwndHide   = WinQueryWindow( hwndScroll, QW_TOP );
   PUCMDATA UCMData = (PUCMDATA) WinQueryWindowULong( hwndUCMenu, QWL_UCMDATA );
   HWND  hwndNewMenu;
   ULONG ulVersion;

   // (MAM) fixed test of unititialized variable

   if ( UCMData && UCMData->hwndMenu ) {
      HWND hwndOldMenu = UCMData->hwndMenu;
      UCMData->AccelTable->cAccel = 0;

      // Load new-style template (with signature).   Remove comments to
      // accomodate older (no sig) templates, but then we cannot detect
      // attempts to load non-UCMenu template files.

      if ( *( (PULONG)pTemplate ) == UCMTMPLSIG ){
         ulVersion = *( (PULONG)( (PBYTE)pTemplate + 4 ) );
         hwndNewMenu = WinCreateMenu( hwndHide, (PVOID)((PBYTE)pTemplate + 8 ) );
      } else {
//         ulVersion = 0;
//         hwndNewMenu = WinCreateMenu( hwndHide, pTemplate );
         return FALSE;
      } // endif

      UCMenuLoadMenuData( hwndNewMenu, UCMData, ulVersion, hwndUCMenu );

      UCMenuReplaceMenu( hwndOldMenu, hwndNewMenu );

      return TRUE;
   } else {
      return FALSE;
   } // endif
}

//----------------------------------------------------------------------------
// UCMenuReplaceMenu : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_REPMENU. name='UCMenuReplaceMenu' text='Loads a new menu in the ucmenu'.
// This function replaces the menu of a ucmenu with a new one.
// :syntax name='UCMenuReplaceMenu' params='hwndOldMenu, hwndNewMenu' return='-' .
// :fparams.
// :fparam name='hwndOldMenu' type='HWND' io='input' .
// Handle of the old menu
// :fparam name='hwndNewMenu' type='HWND' io='input' .
// Handle of the new menu
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// Used when we load templates
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuReplaceMenu(HWND hwndOldMenu, HWND hwndNewMenu)
{
  HWND hwndOwner   = WinQueryWindow(hwndOldMenu , QW_OWNER);
  HWND hwndParent  = WinQueryWindow(hwndOldMenu , QW_PARENT);


  if (hwndOldMenu && hwndNewMenu) {
    PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong(hwndOldMenu, QWL_USER);

    UCMenuFreeMenuData(hwndOldMenu);
    WinDestroyWindow(hwndOldMenu);

    UCMData->hwndMenu = hwndNewMenu;

    WinSetOwner(hwndNewMenu, hwndOwner);
    WinSetParent(hwndNewMenu, hwndParent, TRUE);

    // The presparam change has to be done before subclassing the menu, else it fails
    // (Here, we want to have PRESPARAMCHANGED processed by the default routines only,
    //  since everything is not set up yet)
    WinSetPresParam( hwndNewMenu, PP_FONTNAMESIZE,
                     strlen( UCMData->pszFontNameSize ) + 1,
                     UCMData->pszFontNameSize );
    WinSetPresParam( hwndNewMenu, PP_MENUBACKGROUNDCOLOR, sizeof UCMData->ItemBgColor, &(UCMData->ItemBgColor) );

    UCMData->OldMenuProc = (PFNWP)WinQueryWindowPtr(hwndNewMenu, QWP_PFNWP);
    UCMData->OldMenuProc = (PFNWP)WinSubclassWindow(hwndNewMenu, (PFNWP)MenuWndProc);

    UCMenuNotifAll( UCMData, hwndNewMenu, UCN_ADDEDITEM );

    UCMenuUpdateMenu(hwndNewMenu, FALSE);

  } // endif
}

//----------------------------------------------------------------------------
// UCMenuInitDrag : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_INITDRAG. name='UCMenuInitDrag' text='Performs initializations at the start of a drag'.
// This function does some initializations at the beginning of a drag.
// :syntax name='UCMenuInitDrag' params='hwnd' return='initOK'.
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Handle of the window from which the drag occurs ( it should be a menu )
// :fparam name='x' type='SHORT' io='input' .
// X coordinate of the pointer at the beginning of the drag.
// :fparam name='y' type='SHORT' io='input' .
// Y coordinate of the pointer at the beginning of the drag.
// :freturns.
// :fparam name='initOK' type='BOOL' io='return'.
// The initialization went OK
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

BOOL _Optlink UCMenuInitDrag(HWND hwnd, SHORT x, SHORT y)
{
  DRAGITEM                 DragItem;
  DRAGIMAGE                DragImage;
  DRAGINFO                *pDragInfo;
  POINTL                   ptl;
  MENUITEM                 mItem;
  HBITMAP                  hBitmap;
  PID                      pid;
  TID                      tid;
  PUCMDATA                 UCMData;
  BOOL                     bFileBitmap = FALSE;
  // (MAM) Added flag to delete newly loaded bitmap after drag
  BOOL                     DeleteBitmap = FALSE;  
  QMSG                     QMsg;

  UCMData = (PUCMDATA) WinQueryWindowULong(hwnd , QWL_USER);

  // ------------------------------------------
  // -- First check if drag and drop is allowed
  // ------------------------------------------
  if ( UCMData->Style & UCS_NO_DM) {
     return FALSE;
  } // endif

  WinQueryWindowProcess( hwnd, &pid, &tid );

  ptl.x = x;
  ptl.y = y;
  UCMData->ContextID = UCMenuIdFromCoord(hwnd, &ptl);
  if ( ! UCMData->ContextID ) {
     return FALSE;
  } // endif
  memset(&mItem, 0, sizeof(MENUITEM));
  WinSendMsg(hwnd, MM_QUERYITEM, MPFROM2SHORT(UCMData->ContextID, FALSE), MPFROMP(&mItem)); 

  if (mItem.hItem && ITEM(&mItem, hBmp)) {
//  PSZ pszFileExt;
    BOOL BinOK;
    hBitmap = ITEM(&mItem, hBmp);
    // ------------------------------------------------------
    // -- pszBmp can be a bitmap ID or a file name.  If it
    // -- converts to binary without error we set bFileBitmap
    // -- to TRUE.
    // ------------------------------------------------------
    if (ITEM(&mItem, pszBmp)) {  // There is a bitmap string...
       UCMString2Int(ITEM(&mItem, pszBmp), &BinOK);
       if ((!BinOK) && !(UCMData->Style & UCS_NO_DM_RENDER_TO_BMP))
         bFileBitmap = TRUE;    // Not a number, must be a filename
    }
//...old method, non-NLS...
//  pszFileExt = strrchr( ITEM( &mItem, pszBmp ), '.' );
//
//  if ( !(UCMData->Style & UCS_NO_DM_RENDER_TO_BMP)
//    && pszFileExt
//    && strlen(pszFileExt)>3
//    && toupper(pszFileExt[1])=='B'
//    && toupper(pszFileExt[2])=='M'
//    && toupper(pszFileExt[3])=='P' ) {
//     bFileBitmap = TRUE;
//  } // endif
  } else {
    // fix 03/07/95 (MAM)
    // Cannot use DrgGetPS()/DrgReleasePS() during WM_BEGINDRAG processing.
    // We must get our own PS to load the bitmap.
    HPS hps;
    HDC hdc;
    SIZEL PSSize={0,0};
    DEVOPENSTRUC DevOS={NULL, "DISPLAY", NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    /* Create memory device context to load bitmap */
    hdc = DevOpenDC((HAB)NULLHANDLE, OD_MEMORY, "*", 5L, (PDEVOPENDATA)&DevOS, NULLHANDLE);
    hps = GpiCreatePS((HAB)NULLHANDLE, hdc, &PSSize, GPIA_ASSOC | PU_PELS | GPIT_MICRO);
    if (mItem.afStyle & MIS_SPACER) /* Give spacer items a different look */
      hBitmap = GpiLoadBitmap( hps, UCMData->hModUCM, UCMENUID_SPACERBMP,  0, 0 );
    else
      hBitmap = GpiLoadBitmap( hps, UCMData->hModUCM, UCMENUID_DEFAULTBMP, 0, 0 );

    GpiDestroyPS(hps);
    DevCloseDC(hdc);
    DeleteBitmap = TRUE;  /* Delete this bitmap afer drag is done */
  } // endif

  // ---------------------------------------------------------------------
  // -- If we are dragging an open nodismiss submenu, we close it before
  // -- Else it would cause problems when it is dropped on another ucmenu
  // -- where UCMData->oldSubMenuProc is not yet set
  // ---------------------------------------------------------------------
  if ( WinSendMsg( hwnd,
                   MM_QUERYITEMATTR,
                   MPFROM2SHORT( mItem.id, FALSE ),
                   MPFROMSHORT( MIA_HILITED ) ) ){
     WinSendMsg( hwnd,
                 MM_SETITEMATTR,
                 MPFROM2SHORT( mItem.id, FALSE ),
                 MPFROM2SHORT( MIA_HILITED, FALSE ) );
     if (mItem.hwndSubMenu) {
        UCMenuUnselectAll( UCMData->hwndMenu );
     } // endif
  } // endif

  pDragInfo = DrgAllocDraginfo(1);
  if (pDragInfo == NULL) {
    return 0;
  }

  // -------------------------------------------------------------------------------------
  // -- DC_REMOVEABLEMEDIA prevents the desktop from doing a move by default
  // -- Else, whenever an item with a bitmap file is mistakenly dropped on the desktop,
  // -- the file is moved into the desktop directory and the ucmenu can not find it again
  // -------------------------------------------------------------------------------------
  DragItem.fsControl         = DC_REMOVEABLEMEDIA;

  DragItem.ulItemID          = UCMData->ContextID;

  // ------------------------------------------------------------------------------
  // -- We can either render as a bitmap file or as a ucmenu item
  // -- We will fill them only if it can be rendered as a bitmap file
  // -- In case   a ucmenu item rendering is wanted, a DM_RENDER will be necessary
  // ------------------------------------------------------------------------------
  DragItem.hstrContainerName = 0;
  DragItem.hstrSourceName    = 0;

  DragItem.hwndItem          = hwnd;                 // -- hwnd of the source window (ie menu or submenu)
  DragItem.hstrTargetName    = 0;
  DragItem.fsSupportedOps    = DO_COPYABLE | DO_MOVEABLE;
  if ( bFileBitmap ) {
     PSZ   pszNameOnly;
     PSZ   pszFullNameCopy;

     // -------------------------------------------------------------------------------------
     // -- If the item can be rendered  as a bitmap file, we set it up so that its true type
     // -- and native RMF are those of an actual BMP file -> the order in the following
     // -- strings is important. Else, some applications, eg iconedit, won't accept it.
     // -------------------------------------------------------------------------------------
     DragItem.hstrType = DrgAddStrHandle( DRT_BITMAP "," DRT_UCMITEM ","  DRT_TEXT "," DRT_UNKNOWN );
     if (UCMData->Style&UCS_NO_DM_DISCARD) {
        DragItem.hstrRMF  = DrgAddStrHandle("<DRM_OS2FILE, DRF_TEXT>,<DRM_UCMITEM, DRF_UNKNOWN>");
     } else {
        DragItem.hstrRMF  = DrgAddStrHandle("<DRM_OS2FILE, DRF_TEXT>,(DRM_UCMITEM, DRM_DISCARD)X(DRF_UNKNOWN)");
     } // endif

     pszFullNameCopy = MyStrdup( ITEM( &mItem, pszBmp ) );
     pszNameOnly = strrchr( pszFullNameCopy, '\\' );
     pszNameOnly++;
     DragItem.hstrSourceName    = DrgAddStrHandle( pszNameOnly );
     * pszNameOnly = '\0';
     DragItem.hstrContainerName = DrgAddStrHandle( pszFullNameCopy );
  } else {
     DragItem.hstrType = DrgAddStrHandle(DRT_UCMITEM ", " DRT_UNKNOWN);
     if (UCMData->Style&UCS_NO_DM_DISCARD) {
        DragItem.hstrRMF  = DrgAddStrHandle("<DRM_UCMITEM, DRF_UNKNOWN>");
     } else {
        DragItem.hstrRMF  = DrgAddStrHandle("(DRM_UCMITEM, DRM_DISCARD)X(DRF_UNKNOWN)");
     } // endif
  } // endif

  DragImage.cb               = sizeof(DRAGIMAGE);
  DragImage.hImage           = hBitmap;
  DragImage.fl               = DRG_BITMAP;
  DragImage.cxOffset         = 0;
  DragImage.cyOffset         = 0;

  //(MAM) Allow submenus to be source of drag operations, just like main menus
  pDragInfo->hwndSource      = hwnd;
//pDragInfo->hwndSource      = UCMData->hwndMenu;   // -- always the handle of the menu, never of the submenu
  DrgSetDragitem(pDragInfo, &DragItem, sizeof(DRAGITEM), 0);

  /* Dispatch any waiting messages */
  while (WinPeekMsg((HAB)NULLHANDLE, &QMsg, NULLHANDLE, 0, 0, PM_REMOVE)) {
    WinDispatchMsg((HAB)NULLHANDLE, &QMsg);
  }

  DrgDrag(hwnd,
          pDragInfo,
          &DragImage,
          1,
          VK_BUTTON2,
          DRAGDEBUG);

  // (MAM) Delete bitmap we loaded just for dragging
  if (DeleteBitmap)
    GpiDeleteBitmap(hBitmap);

  DrgAccessDraginfo          (pDragInfo);
  DrgDeleteDraginfoStrHandles(pDragInfo);
  DrgFreeDraginfo            (pDragInfo);

  return TRUE;
}

//----------------------------------------------------------------------------
// UCMenuDrgDrpMsg : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_DRGDRPMSG. name='UCMenuDrgDrpMsg' text='Processes the drag&drop messages'.
// This function processes the drag & drop messages  for the menu & ucmenu window procedures
// :syntax name='UCMenuDrgDrpMsg' params='hwnd, msg, mp1, mp2, WindowProc ' return='rc'.
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Handle of the window where the message occurs
// :fparam name='msg' type='ULONG' io='input' .
// Message given to the window proc
// :fparam name='mp1' type='MPARAM' io='input' .
// First parameter of the message given to the window proc
// :fparam name='mp2' type='MPARAM' io='input' .
// Second parameter of the message given to the window proc
// :fparam name='WindowProc' type='PFNWP' io='input' .
// Window porcedure to call if we do not process the message.
// :freturns.
// :fparam name='rc' type='MRESULT' io='return'.
// Return code for a PM message
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------

MRESULT _Optlink UCMenuDrgDrpMsg(PUCMDATA UCMData, HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2, PFNWP WindowProc)
{
  switch (msg) {
     #if defined(MSG_DEBUGMESSAGE)
     case MSG_DEBUGMESSAGE:
       WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,(char *)mp1,"Debug message:",0,MB_OK);
       return 0;
     #endif

     case WM_BEGINDRAG: {
       MRESULT rc;
       POINTL  CurrMousePos;

       rc = (MRESULT) UCMenuInitDrag( hwnd, SHORT1FROMMP(mp1), SHORT2FROMMP(mp1) );
       /* Re-enable bubble help when drag is done.  It was disabled when */
       /* the BUTTONxDOWN that started the drag occured.                 */
       if (UCMData->Style & UCS_BUBBLEHELP) {
         /* We lose track of the mouse position during drag/drop, so we  */
         /* send a fake mousemove message to regain tracking.            */
         WinQueryPointerPos(HWND_DESKTOP, &CurrMousePos);
         WinMapWindowPoints(HWND_DESKTOP, hwnd, &CurrMousePos, 1);
         WinSendMsg(hwnd, WM_MOUSEMOVE, MPFROM2SHORT(CurrMousePos.x, CurrMousePos.y), MPFROM2SHORT(1, KC_NONE));
         /* If button 2 was not release (e.g. drag was termianted by  */
         /* ESC key, PF1 or some other way), recapture mouse so we    */
         /* will see the BUTTON2UP message and re-enable bubble help  */
         /* at that time.  If drag ended normally (button 2 is up)    */
         /* then we can just re-enable the bubble-help now.           */
//...OK? if (WinGetKeyState(HWND_DESKTOP, VK_BUTTON2) & 0x8000) {
//         WinSetCapture(HWND_DESKTOP, hwnd);
//         UCMData->HoverCapture = TRUE;
//       }
//       else {
           WinSendMsg(UCMData->hwndBubble, MSG_ENABLE_BUBBLE, 0L, 0L);
//       }
       }
       return rc;
       }

     case DM_ENDCONVERSATION:
       // -- All our "conversation resources" are released before returning
       // -- from DM_RENDER so we do nothing here.
       return (MRESULT)0;

     case DM_RENDERPREPARE:
       // -- Since we don't set DC_PREPARE in the DRAGITEM structures from the
       // -- dragged items, this message should never be received
       // -- In case this would happen, should we DrgFreeDragTransfer
       // --  the DRAGTRANSFER structure?
       return (MRESULT)FALSE;

     case DM_RENDER:
       { PDRAGTRANSFER  pdxfer;
         MENUITEM     * pMiTransfer;
         UCMITEM      * pUCMTransfer;
         UCHAR          pszRMF[30];      // -- "<DRM_UCMITEM,DRF_UNKNOWN>" must fit in
         BOOL           bSuccess = TRUE;

         pdxfer = (PDRAGTRANSFER)mp1;

         DrgQueryStrName(pdxfer->hstrSelectedRMF, sizeof(pszRMF), pszRMF);
         if ( strstr( pszRMF, "<DRM_UCMITEM,DRF_UNKNOWN>" ) )
         {
            CHAR pszItemPtr[20];
  
            // ---------------------------------------------------------------
            // -- ulTargetInfo contains the address of the shared memory
            // --  if source and target are in different processes and 0 else
            // ---------------------------------------------------------------
            if (pdxfer->ulTargetInfo) {
               DosSubSetMem ( (PVOID)(pdxfer->ulTargetInfo), 0, 4000 );
               DosSubAllocMem( (PVOID)(pdxfer->ulTargetInfo),(PVOID)&pMiTransfer, sizeof(MENUITEM) );
            } else {
               pMiTransfer = MyMalloc( sizeof(MENUITEM) );
            } // endif
  
            memset( pMiTransfer, 0, sizeof(MENUITEM) );
            WinSendMsg(hwnd,
                       MM_QUERYITEM,
                       MPFROM2SHORT((SHORT)(pdxfer->pditem->ulItemID), TRUE),
                       MPFROMP(pMiTransfer));
            if (pMiTransfer->hItem && pdxfer->ulTargetInfo) {
               // --------------------------------------------------------------------
               // -- pMiTransfer->hItem is a pointer to a UCMItem structure which is
               // -- allocated in our process, so we have to copy it in shared mem too
               // --------------------------------------------------------------------
               UCMITEM * pUCMItem;
  
               pUCMItem = (UCMITEM*)(pMiTransfer->hItem);
               DosSubAllocMem( (PVOID)(pdxfer->ulTargetInfo),(PPVOID)&(pMiTransfer->hItem), sizeof(UCMITEM) );
  
               ITEM(pMiTransfer, hBmp   ) = pUCMItem->hBmp;
               ITEM(pMiTransfer, pszBmp ) = SubMemStrdup( (PVOID)(pdxfer->ulTargetInfo), pUCMItem->pszBmp );
               ITEM(pMiTransfer, pszText) = SubMemStrdup( (PVOID)(pdxfer->ulTargetInfo), pUCMItem->pszText );
               ITEM(pMiTransfer, pszAction) = SubMemStrdup( (PVOID)(pdxfer->ulTargetInfo), pUCMItem->pszAction );
               ITEM(pMiTransfer, pszParameters ) = SubMemStrdup( (PVOID)(pdxfer->ulTargetInfo), pUCMItem->pszParameters );
               ITEM(pMiTransfer, pszData) = SubMemStrdup( (PVOID)(pdxfer->ulTargetInfo), pUCMItem->pszData );
            } // endif
  
            sprintf( pszItemPtr, "%u", pMiTransfer );
            pdxfer->pditem->hstrSourceName = DrgAddStrHandle( pszItemPtr );
  
         } else if ( strstr( pszRMF, "<DRM_OS2FILE,DRF_TEXT>" ) ){
            // ---------------------------------------------------
            // -- A bmp file rendering is requested
            // -- We tell the target to do it by itself!
            // -- (we supplied all the necessary informations)
            // ---------------------------------------------------
            pdxfer->fsReply = DMFL_NATIVERENDER;
            bSuccess = FALSE;
         } else {
            // ------------------------------------
            // -- We don't know how to render that
            // ------------------------------------
            bSuccess = FALSE;
         } // endif RMF checking
  
         if (pdxfer->ulTargetInfo){
            DosSubUnsetMem((PVOID)(pdxfer->ulTargetInfo));
            DosFreeMem((PVOID)(pdxfer->ulTargetInfo));
         } // endif
  
         // ---------------------------------------------------------------------
         // -- Free the drag transfer structure
         // ---------------------------------------------------------------------
         DrgDeleteStrHandle( pdxfer->hstrSelectedRMF );
         DrgFreeDragtransfer( pdxfer );
 
         return (MRESULT)bSuccess;
       }

     case DM_DISCARDOBJECT:
     // ------------------------------------------------------------------
     // -- Discard a menu item (dragged to the shredder for instance)
     // -- We return DRR_SOURCE, which means we handle the delete action
     // ------------------------------------------------------------------
       {
         WinSendMsg(WinQueryWindow(hwnd, QW_OWNER),
                    MM_DELETEITEM,
                    MPFROM2SHORT(UCMData->ContextID, TRUE),
                    (MPARAM)0);
       }
       return (MRESULT)DRR_SOURCE;

     case DM_DRAGOVER:
      // --------------------------------------------------------------------
      // -- We get this message when the drag icon is moved over our window.
      // -- We draw an emphasis frame around the item
      // -- We must verify whether or not we want to accept the drop.
      // --------------------------------------------------------------------
      {
         RECTL    rcl;
         POINTL   ptl;
         USHORT   targetID;
         BOOL     fSuccess, fSuccess2;
         MENUITEM mi;

         ptl.x = SHORT1FROMMP( mp2 );
         ptl.y = SHORT2FROMMP( mp2 );
         WinMapWindowPoints( HWND_DESKTOP, hwnd, &ptl, 1);
         targetID = UCMenuIdFromCoord(hwnd, &ptl);

         if (UCMData->TargetID != targetID) {
            HPS hps  = DrgGetPS( hwnd );

            // Remove the frame of the quitted item
            fSuccess  = (BOOL) WinSendMsg( hwnd,
                                           MM_QUERYITEMRECT,
                                           MPFROM2SHORT( UCMData->TargetID, TRUE ),
                                           MPFROMP( &rcl ));
            fSuccess2 = (BOOL) WinSendMsg( hwnd,
                                           MM_QUERYITEM,
                                           MPFROM2SHORT( UCMData->TargetID, TRUE ),
                                           MPFROMP( &mi ) );
            if ( fSuccess && fSuccess2 ){
               ULONG ColorIndex;

               if (WinIsMenuItemChecked(hwnd,UCMData->TargetID)) {
                  ColorIndex = CLR_BLACK;
               } else if ( mi.afStyle & MIS_SPACER ){
                  ColorIndex = UCMenuSelectColor( UCMData->BgColor, hps );
               } else {
                  ColorIndex = UCMenuSelectColor( UCMData->ItemBgColor, hps );
               } // endif

               rcl.xLeft   += 1;
               rcl.yBottom += 1;
               rcl.yTop    -= 1;
               rcl.xRight  -= 1;

               WinDrawBorder( hps, &rcl, 1, 1, ColorIndex, 0, DB_PATCOPY);
            } // endif

            // -- Draw a frame around the entered item
            fSuccess = (BOOL) WinSendMsg( hwnd,
                                          MM_QUERYITEMRECT,
                                          MPFROM2SHORT( targetID, TRUE ),
                                          MPFROMP( &rcl ));
            if (fSuccess) {
               rcl.xLeft   += 1;
               rcl.yBottom += 1;
               rcl.yTop    -= 1;
               rcl.xRight  -= 1;

               WinDrawBorder( hps, &rcl, 1, 1, CLR_BLACK, 0, DB_PATCOPY);
            } // endif

            UCMData->TargetID = targetID;

            DrgReleasePS( hps );

         } // endif UCMData->TargetID != targetID


         return (MRESULT)(UCMenuDragOver(UCMData, hwnd,(PDRAGINFO) mp1));

      }


    case DM_DRAGLEAVE:
      // -------------------------------------------------------------
      // -- We get this message when the drag icon leaves our window.
      // -- If any clean up is needed, this is the place.
      // -------------------------------------------------------------
      {

         UCMenuRemoveDropEmphasis( UCMData, hwnd );

         return (MRESULT)0;
      }

    #if defined(UCMUI)
    case DM_DROPHELP:
      // ---------------------------------------------------------------------
      // -- Help for Drag Drop.  This message is POSTED to use if the user
      // -- pressed F1 during a drag operation.  Note that the WM_BEGINDRAG
      // -- processing has already completed since this is posted, not sent.
      // ---------------------------------------------------------------------
      {

         UCMenuDisplayHelp( UCMData,
                            (USHORT)PANEL_DM,
                            (USHORT)UCN_HLP_DM );
         return (MRESULT)0;
      }
    #endif

    case DM_DROP:
      // ---------------------------------------------------------------------
      // -- Some application has just Dropped something on us !!
      // ---------------------------------------------------------------------
      UCMenuDrop(hwnd, (PDRAGINFO)mp1) ;
      return (MRESULT)0;

    case DM_RENDERCOMPLETE:
      // ----------------------------------------------------------------------------------
      // -- Some application has just Dropped something on us, but it was
      // -- an incomplete drop specification.  So we asked for a rendering with DM_RENDER.
      // -- However, in all the cases we process the rendering we need is done when we
      // -- get the reply from DM_RENDER, so we do nothing here.
      // -- We would do something eg if the source had to copy a file for us and was
      // -- doing it asynchronously, but we just need the names and location of bmp files,
      // -- which are given in the DM_RENDER reply.
      // ----------------------------------------------------------------------------------
      return (MRESULT)0;

    default:
      return WindowProc(hwnd, msg, mp1, mp2);

   } // endswitch
}

//----------------------------------------------------------------------------
// UCMenuRemoveDropEmphasis : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_RMVEMPH. name='UCMenuRemoveDropEmphasis'
//   text='Called to remove the current drop emphasis'.
// This function is called to remove the emphasis frame drawn around the item being
//  currently dragged over.
// :syntax name='UCMenuRemoveDropEmphasis' params='UCMData, hwnd' return='-'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input' .
// Pointer to the structure associated to the ucmenu.
// :fparam name='hwnd' type='HWND' io='input' .
// Handle of the droppee window.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuRemoveDropEmphasis( PUCMDATA UCMData, HWND hwnd )
{
   RECTL    rcl;
   BOOL     fSuccess, fSuccess2;
   MENUITEM mi;

   fSuccess  = (BOOL) WinSendMsg( hwnd,
                                  MM_QUERYITEMRECT,
                                  MPFROM2SHORT( UCMData->TargetID, TRUE ),
                                  MPFROMP( &rcl ) );
   fSuccess2 = (BOOL) WinSendMsg( hwnd,
                                  MM_QUERYITEM,
                                  MPFROM2SHORT( UCMData->TargetID, TRUE ),
                                  MPFROMP( &mi ) );

   if ( fSuccess && fSuccess2 ){
      ULONG ColorIndex;
      HPS hps   = DrgGetPS( hwnd );

      if (WinIsMenuItemChecked(hwnd,UCMData->TargetID)) {
         ColorIndex = CLR_BLACK;
      } else if ( mi.afStyle & MIS_SPACER ){
         ColorIndex = UCMenuSelectColor( UCMData->BgColor, hps );
      } else {
         ColorIndex = UCMenuSelectColor( UCMData->ItemBgColor, hps );
      } // endif

      rcl.xLeft   += 1;
      rcl.yBottom += 1;
      rcl.yTop    -= 1;
      rcl.xRight  -= 1;

      WinDrawBorder( hps, &rcl, 1, 1, ColorIndex, 0, DB_PATCOPY);
      DrgReleasePS( hps );
   } // endif
   UCMData->TargetID = 0;
}

//----------------------------------------------------------------------------
// UCMenuDragOver : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_DRGOVER. name='UCMenuDragOver' text='Called when a ucmenu is dragged over'.
// This function is called whenever something is being dragged over a ucmenu.
// :syntax name='UCMenuDragOver' params='hwnd, pDragInfo' return='rc'.
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Handle of the droppee window (menu, submenu or hide).
// :fparam name='pDragInfo' type='PDRAGINFO' io='input' .
// Pointer to the draginfo structure
// :freturns.
// :fparam name='rc' type='MRESULT' io='return'.
// Return code for a PM DM_DRAGOVER message
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT _Optlink UCMenuDragOver(PUCMDATA UCMData, HWND hwnd, PDRAGINFO pDraginfo)
{
 USHORT        usOperation, usIndicator;
 PDRAGITEM     pditem;
 ULONG         ulStyle = UCMData->Style;
 PUCMDATA      UCMDataSource;
 ULONG         ulStyleSource = 0;
 BOOL          bSameProcess;
 BOOL          IsUCMenu = FALSE;    // Source of drag is a UCMenu control
 PID           pidSource, pid;
 TID           tid;

 // -------------------------------------------------------------------------
 // -- In case we refuse, we answer only DOR_NODROP, not DOR_NEVERDROP or
 // -- DOR_NODROPOP, because it would prevent DM_DRAGOVER from being sent to
 // -- the menu, and we need it all the time in order to draw the drop
 // -- emphasis on the items (the items are not actual windows).
 // -------------------------------------------------------------------------

 // ------------------------------------------
 // -- First check if drag and drop is allowed
 // ------------------------------------------
 if ( UCMData->Style & UCS_NO_DM ) {
    return MPFROM2SHORT( DOR_NODROP, 0 );
 } // endif

 /* ---------------------------------------------------------------------- */
 /* Get access to the DRAGINFO structure.                                  */
 /* ---------------------------------------------------------------------- */
 DrgAccessDraginfo (pDraginfo);
 pditem = DrgQueryDragitemPtr (pDraginfo, 0);

 WinQueryWindowProcess( hwnd, &pid, &tid );
 WinQueryWindowProcess( pDraginfo->hwndSource, &pidSource, &tid );

 //(MAM) fixed terrible assumption that if drag was from another window in
 //      the same process, it must be a drag from another UCMenu.  Caused
 //      trap/hang if application has its own drag/drop implementation in
 //      addition to a UCMenu.

 bSameProcess = ( pid == pidSource );
 if ( bSameProcess ){
    HWND Owner;
    char Class[20] = "";

    // Check class name of source window... get UCMData of source only
    // if it is really a UCMenu window.  Check by looking at owner
    // of source window (menu or submenu).

    Owner = WinQueryWindow(pDraginfo->hwndSource, QW_OWNER);
    WinQueryClassName(Owner, sizeof(Class), Class);
    if (!strcmp(Class, UCMCLASS))
      IsUCMenu = TRUE;
    else {
      Owner = WinQueryWindow(Owner, QW_OWNER);
      WinQueryClassName(Owner, sizeof(Class), Class);
      if (!strcmp(Class, UCMCLASS))
        IsUCMenu = TRUE;
    }
 
    if (IsUCMenu) {
      UCMDataSource = (PUCMDATA) WinQueryWindowULong( pDraginfo->hwndSource, QWL_USER);
      ulStyleSource = UCMDataSource->Style;
    }
 } /* endif */

 /* ---------------------------------------------------------------------- */
 /* Determine if a drop can be accepted                                    */
 /* ---------------------------------------------------------------------- */
 usIndicator = DOR_DROP;
 if ( WinGetKeyState( HWND_DESKTOP, VK_ALT ) & 0x8000 ){
    pDraginfo->usOperation = DO_UNKNOWN;
 } // endif
 usOperation = pDraginfo->usOperation;
 switch (pDraginfo->usOperation) {
   case DO_COPY:
     usOperation = DO_COPY;
     break;
   case DO_MOVE:
     usOperation = DO_MOVE;
     break;
   case DO_DEFAULT:
     {
        if ( !bSameProcess ) {
           usOperation = DO_COPY;
        } else if (  DrgVerifyRMF (pditem, "DRM_UCMITEM",  "DRF_UNKNOWN") ){
           // At this point we are sure that the process is the same for
           // source and target so it makes sense to compare the PUCMDATA
           // pointers to know whether we are in the same ucmenu or not
           if ( ( ulStyleSource & UCS_NO_DM_M_TO_OTHER ) && ( UCMData != UCMDataSource ) ) {
              usOperation = DO_COPY;
           } else {
              usOperation = DO_MOVE;
           } /* endif */
        } else if( DrgVerifyRMF(pditem, "DRM_OS2FILE", "DRF_TEXT") )  {
           usOperation = DO_COPY;
        } // endif
     }
     break;
   case DO_UNKNOWN:
      {

         usIndicator = DOR_NODROP;

         if ( !( UCMData->Style & UCS_NO_DM_ALT ) ){
            POINTL ptlPos;
            USHORT usItemid;
            ptlPos.x = pDraginfo->xDrop;
            ptlPos.y=  pDraginfo->yDrop;
            WinMapWindowPoints(HWND_DESKTOP, UCMData->hwndMenu, &ptlPos, 1);
            usItemid = UCMenuIdFromCoord( UCMData->hwndMenu, &ptlPos );
            if ( usItemid ){
               MENUITEM mi;
               memset( &mi, '\0', sizeof mi );
               if ( WinSendMsg( UCMData->hwndMenu,
                                MM_QUERYITEM,
                                MPFROM2SHORT( usItemid, FALSE ),
                               MPFROMP( &mi ) )
                    && !( mi.afStyle & MIS_SPACER ) ){
                  // We only accept alt drops over non spacer or non static items
                  // We also don't want alt drop over the hide window (in this case usItemid will be 0)
                  usIndicator = DOR_DROP;
                  usOperation = DO_COPY; // We will get a DO_UNKNOWN anyway in DM_DROP !!
               } // endif
            } // endif
         } // endif
      }
      break;
  default:
     usIndicator = DOR_NODROP;
     usOperation = 0;
 } // endswitch

 // --------------------------------------------------------------------------------
 // -- In order to support the drop, the source must support  a rendering
 // --  mechanims of <DRM_UCMENU,DRF_UNKNOWN> or <DRM_OS2FILE,DRF_UNKNOWN>
 // --  We also check the UCS_ flags  to know if the requested operation is allowed
 // --------------------------------------------------------------------------------
 if ( DrgVerifyRMF (pditem, "DRM_UCMITEM",  "DRF_UNKNOWN") ){
    //(MAM) source may be a submenu of this UCM, need OR conditition
    BOOL bSameUCM = (UCMData->hwndMenu==pDraginfo->hwndSource)||
                    (UCMData->hwndMenu==WinQueryWindow(pDraginfo->hwndSource, QW_OWNER));
    BOOL bMove    = (usOperation == DO_MOVE); // else it is a copy


    if ( bSameUCM && ( !bMove && ulStyle&UCS_NO_DM_C_INSIDE
                     || bMove && ulStyle&UCS_NO_DM_M_INSIDE )
     || !bSameUCM && ( !bMove && ( ulStyle&UCS_NO_DM_C_FROM_OTHER || ulStyleSource&UCS_NO_DM_C_TO_OTHER )
                     || bMove && ( ulStyle&UCS_NO_DM_M_FROM_OTHER || ulStyleSource&UCS_NO_DM_M_TO_OTHER ) ) ) {
       usIndicator = DOR_NODROP;
    } // endif
 } else if (  DrgVerifyRMF( pditem, "DRM_OS2FILE", "DRF_TEXT" )
           && DrgVerifyType( pditem, DRT_BITMAP ) )  {
    if ( UCMData->Style&UCS_NO_DM_RENDER_FROM_BMP ) {
       usIndicator = DOR_NODROP;
    } // endif
 } else {
    usIndicator = DOR_NODROP;
 } // endif


 DrgFreeDraginfo (pDraginfo);

 return (MRFROM2SHORT(usIndicator, usOperation));
}

//--------------------------------------------------------------------------//
//------------------------------- DROP CODE --------------------------------//
//--------------------------------------------------------------------------//
//----------------------------------------------------------------------------
// UCMenuDrop : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_DROP. name='UCMenuDrop' text='Called when something is dropped on a ucmenu'.
// This function is called whenever something is dropped on a ucmenu.
// :syntax name='UCMenuDrop' params='hwnd, pDragInfo' return='-'.
// :fparams.
// :fparam name='hwnd' type='HWND' io='input'.
// Handle of the window receiving the drop.
// :fparam name='pDragInfo' type='PDRAGINFO' io='input' .
// Pointer to the draginfo structure
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink UCMenuDrop(HWND hwnd, PDRAGINFO pDraginfo)
{
   PDRAGITEM     pditem;
   TID           tid;
   PID           pidSource, pidTarget;
   BOOL          bAlt;
   PUCMDATA      UCMData = (PUCMDATA) WinQueryWindowULong( hwnd, QWL_USER );


   // ----------------------------------------------------------------------------
   // -- If we are on any window other than a submenu, pretend we are on the menu
   // ----------------------------------------------------------------------------
   if (WinQueryWindow( hwnd, QW_OWNER ) != UCMData->hwndMenu) {
      hwnd = UCMData->hwndMenu;
   } // endif


   UCMenuRemoveDropEmphasis( UCMData, hwnd);

 
   DrgAccessDraginfo (pDraginfo);
  
   // ----------------------------------------------------------------------------
   // -- Set up a flag to know whether ALT was pressed or not
   // ----------------------------------------------------------------------------
   if ( WinGetKeyState( HWND_DESKTOP, VK_ALT ) & 0x8000 ){
      // !! If alt was pressed before beginning the drag, usOperation will be DO_MOVE !!
      pDraginfo->usOperation = DO_UNKNOWN;
      bAlt = TRUE;
   } else {
      bAlt = FALSE;
   } // endif
  
   if (!WinQueryWindowProcess( hwnd, &pidTarget, &tid )) {
      pidTarget = 0;
   } // endif
  
   if (!WinQueryWindowProcess( pDraginfo->hwndSource, &pidSource, &tid )) {
      pidSource = 0;
   } // endif
  
   pditem = DrgQueryDragitemPtr (pDraginfo, 0);
   if ( pditem ) {
     /* ---------------------------------------------------------------------- */
     /* Let's render                                                           */
     /* ---------------------------------------------------------------------- */
     /* We assume only one object is being dragged                             */
     /* ---------------------------------------------------------------------- */
     PDRAGTRANSFER   pDxfer;
     PVOID           pSharedMem;
     BOOL            bFullItemDropped;
     BOOL            bRenderSuccess = TRUE;
  
     // -- We ask the source to render
     pDxfer = DrgAllocDragtransfer(1);
     pDxfer->cb               = sizeof(DRAGTRANSFER);
     pDxfer->hwndClient       = hwnd;
     pDxfer->pditem           = pditem;
     pDxfer->hstrRenderToName = 0;
     pDxfer->usOperation      = pDraginfo->usOperation;
     pDxfer->fsReply          = 0;
     pDxfer->ulTargetInfo     = 0;
  
     if (DrgVerifyRMF( pditem, "DRM_UCMITEM", "DRF_UNKNOWN" )){
        // ------------------------------------------------------------------------
        // -- We want a full ucmenu item
        // ------------------------------------------------------------------------
        pDxfer->hstrSelectedRMF  = DrgAddStrHandle("<DRM_UCMITEM,DRF_UNKNOWN>");
        // ------------------------------------------------------------------------
        // -- In case the source is in another process, allocate some shared mem
        // ------------------------------------------------------------------------
        if (pidSource!=pidTarget) {
           // ------------------------------------------------------------------------
           // -- We will store in that mem the MENUITEM and UCMITEM structures
           // -- associated to an item, so one page (4K) should be enough
           // -- (We will use DosSubAllocMem, which has a granularity of 8 bytes and not 4096)
           // ------------------------------------------------------------------------
           DosAllocSharedMem( &pSharedMem, 0, 4000, PAG_READ | PAG_WRITE |  PAG_COMMIT | OBJ_GIVEABLE );
           DosSubSetMem( pSharedMem, DOSSUB_INIT, 4000 );
           DosGiveSharedMem( pSharedMem, pidSource, PAG_READ | PAG_WRITE );
           pDxfer->ulTargetInfo = (ULONG)pSharedMem;
        } // endif
        bFullItemDropped = TRUE;
     } else {
        // ------------------------------------------------------------------------
        // -- We are sure that this RMF is supported because of the DM_DRAGOVER processing
        // -- We will make a new ucmenu item using this bitmap
        // ------------------------------------------------------------------------
        pDxfer->hstrSelectedRMF = DrgAddStrHandle("<DRM_OS2FILE,DRF_TEXT>");
        bFullItemDropped = FALSE;
     } // endif
  
     // ------------------------------------------------------------------------
     // -- If it is a ucmenu item, we always ask the rendering
     // --   (because we render differently if the processes are not the same)
     // -- If it is a bmp file, we ask the rendering only if the filename is not provided.
     // ------------------------------------------------------------------------
     if ( bFullItemDropped || !pditem->hstrSourceName ) {
        bRenderSuccess = (BOOL)DrgSendTransferMsg( pDraginfo->hwndSource,
                                                   DM_RENDER,
                                                   (MPARAM)pDxfer,
                                                   (MPARAM)0 );
     } else {
        // ----------------------------------------------------------------
        // -- Bmp file whose name is provided : we can render by ourselves.
        // ----------------------------------------------------------------
        DrgDeleteStrHandle( pDxfer->hstrSelectedRMF );
     } // endif
  
     /* We must always free the drag xfer structure.  Target of DM_RENDER */
     /* must also free it because DrgSendTransferMsg() does a DosGive()   */
     /* to the target process but not DosFree().                          */
     DrgFreeDragtransfer( pDxfer );
  
     if ( bRenderSuccess ) {
        MENUITEM * pMiNew;
        HWND       hwndDest;
        POINTL     ptlPos;
        USHORT     usItemid;    // ID of the target item
        SHORT      sIndex;      // Index used to insert the item
        PSZ        pszRenderInfo;
        ULONG      ul;
  
        // -------------------------------------------------------
        // -- Decide which window will handle the item insertion
        // -------------------------------------------------------
        if ( WinQueryWindow( hwnd, QW_OWNER ) != UCMData->hwndMenu ){
           // -- If we are not on a submenu, the ucmenu will do the insertion
           hwndDest = WinQueryWindow( hwnd, QW_OWNER );
        } else {
           // -- If we are on a submenu, it can handle the insert by itself
           hwndDest = hwnd;
        } // endif
  
  
        // ----------------------------------------------------------------------------
        // -- Get the rendered information
        // ----------------------------------------------------------------------------
        ul = DrgQueryStrNameLen(pditem->hstrSourceName) + 1;
        pszRenderInfo = (PSZ)MyMalloc(ul);
        DrgQueryStrName(pditem->hstrSourceName,    // string handle
                        ul,                        // Nb of bytes
                        pszRenderInfo);            // buffer
  
        // ----------------------------------------------------------------------------
        // -- Use the rendered info to fill in the MENUITEM
        // ----------------------------------------------------------------------------
        {
           pMiNew = MyMalloc( sizeof(MENUITEM) );
           memset(pMiNew, 0, sizeof(MENUITEM));
           if ( bFullItemDropped ) {
  
              MENUITEM * pMiTransfered = 0;
  
              sscanf(pszRenderInfo, "%u", &pMiTransfered);
              pMiNew->iPosition   = pMiTransfered->iPosition;
              pMiNew->afStyle     = pMiTransfered->afStyle;
              pMiNew->afAttribute = pMiTransfered->afAttribute;
              pMiNew->id          = pMiTransfered->id;
              pMiNew->hwndSubMenu = pMiTransfered->hwndSubMenu;
              if ( pMiTransfered->hItem ){
                 pMiNew->hItem = (ULONG)MyMalloc(sizeof(UCMITEM));
                 memset((PVOID)pMiNew->hItem, 0, sizeof(UCMITEM));
                 ITEM(pMiNew, hBmp)    = ITEM(pMiTransfered, hBmp);
                 ITEM(pMiNew, pszBmp)  = MyStrdup( ITEM(pMiTransfered, pszBmp) );
                 ITEM(pMiNew, pszText) = MyStrdup( ITEM(pMiTransfered, pszText) );
                 ITEM(pMiNew, pszAction) = MyStrdup( ITEM(pMiTransfered, pszAction) );
                 ITEM(pMiNew, pszParameters) = MyStrdup( ITEM(pMiTransfered, pszParameters) );
                 ITEM(pMiNew, pszData) = MyStrdup( ITEM(pMiTransfered, pszData) );
              }
              if (pidSource==pidTarget) {
                 // -- Same process -> the transfered item has been allocated with MyMalloc
                 // -- Else, it is in shared mem, the whole shared mem bank will be freed
                 // --  at the end of UCMenuDrop
                 MyFree( pMiTransfered );
              } // endif
           } else {
              // -- We have here a bitmap file name
              ULONG ul2;
  
              pMiNew->hItem = (ULONG)MyMalloc(sizeof(UCMITEM));
              memset((PVOID)pMiNew->hItem, 0, sizeof(UCMITEM));
  
              ul2 = DrgQueryStrNameLen(pditem->hstrContainerName)+1;
              ((UCMITEM*)pMiNew->hItem)->pszBmp = MyMalloc(ul+ul2);
              DrgQueryStrName( pditem->hstrContainerName, ul2, ITEM(pMiNew,pszBmp));
              strcat( ITEM(pMiNew,pszBmp), pszRenderInfo );
              pMiNew->afStyle = MIS_OWNERDRAW;
           } // endif
        }
  
        // ----------------------------------------------------------------------------
        // -- Force the reloading of the bitmap if necessary
        // ----------------------------------------------------------------------------
        if ( pMiNew->hItem &&
            ( pidSource!=pidTarget || pDraginfo->usOperation==DO_COPY || pDraginfo->usOperation==DO_UNKNOWN ) ) {
           // ----------------------------------
           // -- Release the bitmap if necessary
           // ----------------------------------
           if ( ITEM(pMiNew,hBmp) &&
                (pidSource!=pidTarget) &&
                (pDraginfo->usOperation==DO_MOVE) ){
              GpiDeleteBitmap( ITEM(pMiNew,hBmp) );
           } // endif
           ITEM(pMiNew,hBmp) = 0;
        } // endif
  
        // -----------------------------------------------------------------------------
        // -- (MAM) remove any MIS_BREAK
        // -----------------------------------------------------------------------------
        pMiNew->afStyle &= (USHORT) ~MIS_BREAK;
  
        // ----------------------------------------------------------------------------
        // -- Query where the item has to be dropped (index in the menu)
        // ----------------------------------------------------------------------------
        ptlPos.x = pDraginfo->xDrop;
        ptlPos.y=  pDraginfo->yDrop;
        WinMapWindowPoints(HWND_DESKTOP, hwnd, &ptlPos, 1);
        usItemid = UCMenuIdFromCoord(hwnd, &ptlPos);
        if (usItemid) {
           RECTL    rect;
           if ( bAlt && ( hwnd == UCMData->hwndMenu ) ){
              MENUITEM mi;
              WinSendMsg( hwnd,
                          MM_QUERYITEM,
                          MPFROM2SHORT( usItemid, FALSE ), 
                          MPFROMP( &mi ) );
  
              if ( !( mi.afStyle & MIS_SUBMENU ) ){
              
                 mi.afStyle |= MIS_SUBMENU;
                 mi.hwndSubMenu = WinCreateWindow( HWND_OBJECT,
                                                   WC_MENU,
                                                   "",
                                                   0, // WS_*
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   UCMData->hwndMenu,
                                                   HWND_BOTTOM,
                                                   usItemid,
                                                   0,
                                                   0 );
                WinSendMsg( WinQueryWindow( UCMData->hwndMenu, QW_OWNER ),  // ucmenu window
                            MM_SETITEM,
                            MPFROM2SHORT( usItemid, FALSE ), 
                            MPFROMP( &mi ) );
              } // endif
  
              hwndDest = hwnd = mi.hwndSubMenu;
           } // endif
  
           sIndex = (SHORT)WinSendMsg( hwnd,
                                       MM_ITEMPOSITIONFROMID,
                                       MPFROM2SHORT(usItemid, FALSE), 
                                       (MPARAM)0 );
           // -------------------------------------------------------------------------------------
           // -- If it is an item of a vertical ucmenu or of a submenu of an horizontal ucmenu, we
           // --  put the dropped item before if it is dropped over the top half and after else.
           // -- If it is an item of an horizontal ucmenu or of a submenu of a vertical ucmenu, we
           // --  put the dropped item before if it is dropped over the left half and after else.
           // -- A matrix ucmenu is here processed in the same way as an horizontal one.
           // -------------------------------------------------------------------------------------
           if ( WinSendMsg( hwnd, MM_QUERYITEMRECT, MPFROM2SHORT( usItemid, FALSE ), MPFROMP( &rect ) ) ) { 
              HWND hwndUCMDest = WinQueryWindow( hwnd, QW_OWNER );
              ULONG Style      = WinQueryWindowULong( hwndUCMDest, QWL_STYLE );
              if (   ( (Style & CMS_VERT) && (hwnd == UCMData->hwndMenu))  ||
                     (!(Style & CMS_VERT) && (hwnd != UCMData->hwndMenu)) ) {
                       if ( ptlPos.y < (rect.yTop+rect.yBottom)/2)
                         sIndex++;
              } else {
                 if ( ptlPos.x > (rect.xRight+rect.xLeft)/2) 
                   sIndex++;
              } // endif Style...
           } // endif WinSendMsg
  
        } else {
           sIndex = MIT_LAST;
        } // endif
  
        if (sIndex==MIT_LAST || sIndex==MIT_NONE) {
          // -------------------------------------------------------
          // -- Query item count : item insert after all the others
          // -------------------------------------------------------
          sIndex = (SHORT)WinSendMsg(hwnd,
                                     MM_QUERYITEMCOUNT,
                                     (MPARAM)0,
                                     (MPARAM)0);
        } // endif
  
        // -----------------------------------------------------------------------
        // -- Before dropping, we unselect all the items of the dest menu
        // -- because the open submenu of a nodismiss submenu item do not follow
        // -- it when this item is moved
        // -----------------------------------------------------------------------
        UCMenuUnselectAll( UCMData->hwndMenu );
  
        switch (pDraginfo->usOperation) {
          case DO_UNKNOWN:
             // This is for the Alt dropping
          case DO_COPY:
            {
               // --------------------------------------------------------------------------------
               // -- If dropped item was a submenu placeholder, turn it into a regular item.
               // --------------------------------------------------------------------------------
               pMiNew->afStyle     &= (USHORT)~MIS_SUBMENU;
               //(MAM) also remove NODISMISS attribute
               pMiNew->afAttribute &= (USHORT)~MIA_NODISMISS;
               pMiNew->hwndSubMenu  = NULLHANDLE;
               pMiNew->iPosition    = sIndex;
               pMiNew->id           = UCMenuGetNewID( UCMData->hwndMenu, MIT_NONE, UCMData );
  
               WinSendMsg(hwndDest,
                          MM_INSERTITEM,
                          MPFROMP(pMiNew),
                          (MPARAM)0);
  
            }
            break;
  
          case DO_MOVE:
            { SHORT sSourcePos    = pMiNew->iPosition;
              USHORT SourceMenuID = pMiNew->id;
  
              if ( ( pMiNew->hwndSubMenu && ( hwnd != UCMData->hwndMenu ) )
                   || pidSource!=pidTarget ){
                 // --------------------------------------------------------------------------
                 // -- Only one submenu level is supported
                 // -- If we move an item with a submenu into another one, we remove its submenu
                 // -- We don't move the submenus from other apps because it's too complicated...
                 // --------------------------------------------------------------------------
                 UCMenuFreeMenuData( pMiNew->hwndSubMenu );
                 WinDestroyWindow( pMiNew->hwndSubMenu );
                 pMiNew->afStyle    &= (USHORT)~MIS_SUBMENU; // turn into a normal item if submenu holder
                 pMiNew->afAttribute&= (USHORT)~MIA_NODISMISS;
                 pMiNew->hwndSubMenu = 0;
              } // endif
  
              if ( pditem->hwndItem == hwnd ) {
                // --------------------------------------------------------------------------
                // -- Same destination : the item interferes with its index
                // --------------------------------------------------------------------------
                if (sSourcePos<sIndex) {
                  pMiNew->iPosition = sIndex - 1;
                } else {
                  pMiNew->iPosition = sIndex;
                } // endif
              } else {
                // --------------------------------------------------------------------------
                // -- Different UCMenus : we need a new ID !
                // --------------------------------------------------------------------------
                pMiNew->id        = UCMenuGetNewID( UCMData->hwndMenu, MIT_NONE, UCMData );
                pMiNew->iPosition = sIndex;
              } // endif
  
              if ( bFullItemDropped ) {
                 // --------------------------------------------------------------------------
                 // -- The dropped object was coming from a ucmenu
                 // --------------------------------------------------------------------------
                 if ( pidSource == pidTarget) {
                    MENUITEM mi;
                    WinSendMsg( pDraginfo->hwndSource,
                                MM_QUERYITEM,
                             // (MAM) source may have been a submenu item, so we need
                             //       to search submenus also.
                             // MPFROM2SHORT( SourceMenuID, FALSE ),
                                MPFROM2SHORT( SourceMenuID, TRUE  ),
                                MPFROMP( &mi ) );
                    if ( mi.hItem ) {
                       if ( ITEM( &mi, pszBmp ) ){    MyFree( ITEM( &mi, pszBmp ) ); }
                       if ( ITEM( &mi, pszText ) ){   MyFree( ITEM( &mi, pszText ) ); }
                       if ( ITEM( &mi, pszAction ) ){ MyFree( ITEM( &mi, pszAction ) ); }
                       if ( ITEM( &mi, pszParameters ) ){ MyFree( ITEM( &mi, pszParameters ) ); }
                       if ( ITEM( &mi, pszData ) ){   MyFree( ITEM( &mi, pszData ) ); }
                    } // endif
                    WinSendMsg(WinQueryWindow(pDraginfo->hwndSource, QW_OWNER),
                               MM_REMOVEITEM,
                            // (MAM) Source item may have been a submenu, so we
                            //       need TRUE here to delete submenu source items.  This
                            //       is safe since all UCMenu item IDs should be unique.
                            // MPFROM2SHORT(SourceMenuID, FALSE),
                               MPFROM2SHORT(SourceMenuID, TRUE),
                               (MPARAM)0);
                 } else {
                    WinSendMsg(WinQueryWindow(pDraginfo->hwndSource, QW_OWNER),
                               MM_DELETEITEM,
                            // (MAM) Source item may have been a submenu, so we
                            //       need TRUE here to delete submenu source items.  This
                            //       is safe since all UCMenu item IDs should be unique.
                            // MPFROM2SHORT(SourceMenuID, FALSE),
                               MPFROM2SHORT(SourceMenuID, TRUE),
                               (MPARAM)0);
                 } // endif
              }
  
              WinSendMsg(hwndDest,
                         MM_INSERTITEM,
                         MPFROMP( pMiNew ),
                         (MPARAM)0 );
            } break;
          default:
            //-- invalid operation
            break;
        } // endswitch
        // ----------------------------------------------------------------------------------------
        // -- We can now free pMiNew, it was either allocated by us or by the source using MyMalloc
        // ----------------------------------------------------------------------------------------
        MyFree( pMiNew );
     } // endif render successful
  
  
     // ----------------------------------------------------------------------------------------
     // -- Now let's notify the source that it can release the resources it allocated for the rendering.
     // ----------------------------------------------------------------------------------------
     DrgSendTransferMsg( pDraginfo->hwndSource,
                         DM_ENDCONVERSATION,
                         (MPARAM)pditem->ulItemID,
                         (MPARAM)DMFL_TARGETSUCCESSFUL);
  
  
     // ---------------------------------------------------------------------------------------
     // -- If we did allocate shared memory, free it
     // ---------------------------------------------------------------------------------------
     if ( bFullItemDropped && pidSource!=pidTarget ) {
        DosSubUnsetMem( pSharedMem );
        DosFreeMem( pSharedMem );
     } // endif
  
   } // endif  pditem
  
   // ---------------------------------------------------------------------------------------
   // -- free the resource:
   // ---------------------------------------------------------------------------------------
   DrgDeleteDraginfoStrHandles (pDraginfo);
   DrgFreeDraginfo (pDraginfo);
}

//----------------------------------------------------------------------------
// UCMenuPresParamChanged : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_PPCHG. name='UCMenuPresParamChanged' text='Processes the presentation parameter changes'.
// This function is called within the WM_PRESPARAMCHANGED processing.
// :syntax name='UCMenuPresParamChanged' params='hwndUCM, hwnd, mp1' return='-'.
// :fparams.
// :fparam name='hwndUCM' type='HWND' io='input'.
// Handle of the ucmenu
// :fparam name='hwnd' type='HWND' io='input'.
// Handle of the window which received WM_PRESPARAMCHANGED
// :p.It can be any of the windows part of a UCMenu.
// :fparam name='mp1' type='MPARAM' io='input' .
// First parameter of the WM_PRESPARAMCHANGED message
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink UCMenuPresParamChanged(PUCMDATA UCMData, HWND hwnd, MPARAM mp1)
{
   ULONG x;
 
   if ( (SHORT)mp1 == PP_BACKGROUNDCOLOR ) {
      ULONG Color;

      WinQueryPresParam( hwnd,
                         (SHORT)mp1,
                         0L, &x,
                         (ULONG)sizeof Color,
                         &Color,
                         QPF_NOINHERIT);
      if (x == (SHORT)mp1) {
         // We tell the menu to change its color
         // It will change UCMData->ItemBgColor and have everything redrawn
         WinSetPresParam( UCMData->hwndMenu,
                          PP_MENUBACKGROUNDCOLOR,
                          sizeof Color,
                          &Color);
      } else {
         WinRemovePresParam( hwnd, PP_BACKGROUNDCOLOR );
      } // endif
   } else if ( (SHORT)mp1 == PP_FONTNAMESIZE ) {
      CHAR FontNameSize[100];

      WinQueryPresParam( hwnd,
                         (SHORT)mp1,
                         0L, &x,
                         100L,
                         FontNameSize,
                         QPF_NOINHERIT );
      if (x == (SHORT)mp1) {
         // We remove this presparam from the window, because when the context
         // menu pops up, it uses the PP__FONTNAMESIZE font of its owner and we want
         // it to always use the default menu font. (its owner is the Hide window)
         WinRemovePresParam( hwnd, PP_FONTNAMESIZE );
         // We tell the menu to change its fonts
         // It will change UCMData->pszFontNameSize and have everything redrawn
         WinSetPresParam( UCMData->hwndMenu,
                          PP_FONTNAMESIZE,
                          strlen(FontNameSize)+1,
                          FontNameSize);
         // Tell bubble window about font changes
         if (UCMData->Style & UCS_BUBBLEHELP)
           WinSetPresParam( UCMData->hwndBubble,
                            PP_FONTNAMESIZE,
                            strlen(FontNameSize)+1,
                            FontNameSize);
      } else {
         WinRemovePresParam( hwnd, PP_FONTNAMESIZE );
      } // endif

   } // endif
}

//----------------------------------------------------------------------------
// UCMenuGetExePath : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_GETEXEPATH. name='UCMenuGetExePath' text='Finds the path of the program which called the dll'.
// This function returns the path of the exe file which called the ucmenu dll
// :syntax name='UCMenuGetExePath' params='-' return='pszPath'.
// :fparams.
// :freturns.
// :fparam name='pszPath' type='PSZ' io='return'.
// String containing the path
// :efparams.
// :remarks.
// :related.
// :epfunction.
//---------------------------------------------------------------------------
PSZ _Optlink UCMenuGetExePath(VOID)
{
  PTIB  ptib;
  PPIB  ppib = 0;
  ULONG rc;
  PSZ   psz = 0;
  rc = DosGetInfoBlocks(&ptib, &ppib);
  if (!rc) {
    CHAR sz[CCHMAXPATH];
    strcpy(sz, ppib->pib_pchcmd);
    strupr( sz );
    psz = strstr(sz, ".EXE");
    while (psz && (psz >= sz) && (*psz != '\\')) psz --;
    if (psz) {
      *psz = '\0';
      psz = MyStrdup(sz);
    } // endif
  } // endif
  return psz;
}

//----------------------------------------------------------------------------
// UCMenuGetBitmapPath : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_BMPPATH. name='UCMenuGetBitmapPath' text='Finds the path of the given bitmap file'.
// This function finds the access path of a given file.
// :syntax name='UCMenuGetBitmapPath' params='UCMData, pszBmp, pszPathName' return='success'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input'.
// Pointer to the UCMData structure
// :fparam name='pszBmp' type='PSZ' io='input'.
// String of the searched filename, which can also include a path and a drive
// :fparam name='pszPathName' type='MPARAM' io='output' .
// Full name of path found or "", must already be allocated to MAXPATHL characters
// :freturns.
// :fparam name='success' type='USHORT' io='return'.
// O if successful
// :efparams.
// :remarks.
// We look for the file (including any given path ) in the current directory, then we keep only the filename
// and look for it in the dir of the exe file, and in the path of the UCMData->pszBitmapSearchPath
// environment variables.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
USHORT _Optlink UCMenuGetBitmapPath( PUCMDATA UCMData, PSZ pszBmp, PSZ pszPathName )
{
   PSZ   BitmapFile;
   UCHAR BitmapFileName[MAXPATHL];
   PSZ   Path;
   BOOL  FirstToken;
   UCHAR szBitmapSearchPath[MAXPATHL];
   ULONG DriveNumber, LogicalDriveMap;
   ULONG DirPathLen = MAXPATHL;
   BYTE DirPath[MAXPATHL];
   APIRET rc;

   // Query the current path
   // --
   rc =  DosQueryCurrentDisk( &DriveNumber, &LogicalDriveMap );
   rc += DosQueryCurrentDir( DriveNumber, DirPath, &DirPathLen );

   // Put in BitmapFileName the full access name of the given bitmap name in
   // the current drive and directory
   // --
   if ( pszBmp[1] == ':' && pszBmp[2] == '\\' ) {
      // The given filename includes the dir and path
      // --
      BitmapFileName[0] = '\0';
   } else  {
      // Add the default drive at the beginning
      // --
      BitmapFileName[0] = 'A' + DriveNumber - 1;
      BitmapFileName[1] = ':';
      BitmapFileName[2] = '\0';
      if ( pszBmp[0] != '\\' ) {
         // Add "\", current directory, and "\" before pszBmp;
         // --
         strcat( BitmapFileName, "\\" );
         strcat( BitmapFileName, DirPath );
         strcat( BitmapFileName, "\\" );
      }
   } // endif
   strcat( BitmapFileName, pszBmp );

   // Now BitmapFileName contains the full access name of the bitmap
   // We copy the directory part of it in DirPath
   // --
   BitmapFile = strrchr( BitmapFileName, '\\' );
   BitmapFile[0] = '\0';
   strcpy( DirPath, BitmapFileName );
   if ( ( DirPath[1] == ':' ) && ( DirPath[2] == '\0' ) ){
      // Drive only, we have to add \ else it will look
      // in the current directory of this drive
      // --
      strcat( DirPath, "\\" );
   } // endif

   // Now we make BitmapFile point to the filename only
   // We use pszBmp instead of BitmapFileName because  BitmapFileName
   // will be used after and have its content changed
   // --
   if ( BitmapFile = strrchr( pszBmp, '\\' ) ) {
      BitmapFile++;
   } else {
      BitmapFile = pszBmp;
   }


   // Try loading the bitmap from the current path with the given prefixing path
   // --
   if ( ! DosSearchPath( 0, DirPath, BitmapFile, BitmapFileName, MAXPATHL) ) {
      strcpy( pszPathName, DirPath );
      return 0;
   } // endif

   // Try loading the bitmap file from the exe directory
   // --
   {
      PSZ ExePath = UCMenuGetExePath();
      if ( ! DosSearchPath( 0, ExePath, BitmapFile, BitmapFileName, MAXPATHL) ) {
         strcpy( pszPathName, ExePath );
         MyFree( ExePath );
         return 0;
      } // endif
      MyFree( ExePath );
   }

   // If search Paths were specified search them
   // --
   if ( UCMData->szBitmapSearchPath[0] ) {
      strcpy( szBitmapSearchPath, UCMData->szBitmapSearchPath );
      FirstToken = 1;
      while( Path = strtok( FirstToken?szBitmapSearchPath:0, " " ) ) {
         if ( ! DosSearchPath( 2, Path, BitmapFile, BitmapFileName, MAXPATHL ) ) {
            Path = strrchr( BitmapFileName, '\\' );
            Path[0] = '\0';
            strcpy( pszPathName, BitmapFileName );
            return 0;
         } // endif
         FirstToken = 0;
      } // endwhile
   } // endif

   pszPathName[0] = '\0';
   return 1;
}

//----------------------------------------------------------------------------
// UCMenuGetBitmapFullName : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_BMPFULLNAME. name='UCMenuGetBitmapFullName' text='Finds the full access name of the given bitmap file'.
// This functions looks for the given file or the default one in  all the suitable directories and returns its full access name
// :syntax name='UCMenuGetBitmapFullName' params='UCMData, pszBmp, pszPathName' return='success'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input'.
// Pointer to the UCMData structure
// :fparam name='pszBmp' type='PSZ' io='input'.
// String of the searched filename, which can also include a path and a drive
// :fparam name='pszFullName' type='MPARAM' io='output' .
// Full name including the path found or "", must already be allocated to MAXPATHL characters
// :freturns.
// :fparam name='success' type='USHORT' io='return'.
// O if successful
// :efparams.
// :remarks.
// We look for the file (including any given path ) in the current directory, then we keep only the filename
// and look for it in the dir of the exe file, and in the path of the UCMData->pszBitmapSearchPath
// environment variables.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
USHORT _Optlink UCMenuGetBitmapFullName( PUCMDATA UCMData, PSZ pszBmp, PSZ pszFullName )
{
   USHORT rc;
   PSZ    BitmapFile;

   rc = UCMenuGetBitmapPath( UCMData, pszBmp, pszFullName );

   // Strip any path prefixing the bitmap file name
   // --
   if ( ! ( BitmapFile = strrchr( pszBmp, '\\' ) ) ) {
      BitmapFile = pszBmp;
   } else {
      BitmapFile++;
   }

   if ( ! rc ) {
      ULONG ulLen = strlen( pszFullName );
      if ( pszFullName[ulLen-1] != '\\' ){
         strcat( pszFullName, "\\" );
      } // endif
      strcat( pszFullName, BitmapFile );
      return 0;
   } // endif

//... default bitmap may be a resource ID or file name, this
//... no longer works
//
// if ( *( UCMData->szDefaultBitmap ) ) {
//    rc = UCMenuGetBitmapPath( UCMData, UCMData->szDefaultBitmap, pszFullName );
//
//    // Strip any path prefixing the bitmap file name
//    // --
//    if ( ! ( BitmapFile = strrchr( UCMData->szDefaultBitmap, '\\' ) ) ) {
//       BitmapFile = UCMData->szDefaultBitmap;
//    } else {
//       BitmapFile++;
//    }
//
//    if ( ! rc ) {
//       ULONG ulLen = strlen( pszFullName );
//       if ( pszFullName[ulLen-1] != '\\' ){
//          strcat( pszFullName, "\\" );
//       } // endif
//       strcat( pszFullName, BitmapFile );
//       return 0;
//    } // endif
// } // endif pszDefaultBitmap

   pszFullName[0] = '\0';
   return 1;
}

//----------------------------------------------------------------------------
// GetMaxItemSize : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_MAXITSZ. name='GetMaxItemSize' text='Finds the size of the biggest item and updates UCMData'.
// This functions looks for the given file or the default one in  all the suitable directories and returns its full access name
// :syntax name='GetMaxItemSize' params='UCMData, hwndUCMenu, hwndMenu' return='-'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input'.
// Pointer to the UCMData structure
// :fparam name='hwndUCMenu' type='HWND' io='input'.
// UCMenu window handle
// :fparam name='hwndMenu' type='HWND' io='input' .
// Menu window handle
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink GetMaxItemSize(PUCMDATA UCMData, HWND hwndUCMenu, HWND hwndMenu)
{
   ULONG NumberOfItems = 0;
   ULONG Item;
   ULONG cx, cy;
   USHORT ItemID;
   MENUITEM mi;
   ULONG MaxHorizontalHeight, MaxVerticalWidth;
   ULONG SumItemWidths  = 0;
   ULONG SumItemHeights = 0;

   // Do not put anything but the actual new values in UCMData
   MaxVerticalWidth = MaxHorizontalHeight = 0;

   NumberOfItems = (ULONG)WinSendMsg(hwndMenu,
                                     MM_QUERYITEMCOUNT, 0L, 0L);

   if (NumberOfItems == 0) {
     cx = WinQuerySysValue(HWND_DESKTOP, SV_CYMENU); // Set empty toolbar to PM menu height
     UCMData->MaxHorizontalHeight = cx;
     UCMData->MaxVerticalWidth    = cx;
     UCMData->SumItemWidths  = cx;
     UCMData->SumItemHeights = cx;
     return;
   }

   for(Item=0; Item<NumberOfItems; Item++) {
      ItemID = (USHORT)WinSendMsg(hwndMenu,
                                  MM_ITEMIDFROMPOSITION,
                                  MPFROMSHORT(Item),
                                  (MPARAM)0);
      WinSendMsg(hwndMenu,
                 MM_QUERYITEM,
                 MPFROM2SHORT(ItemID,FALSE),
                 MPFROMP(&mi));

      if (mi.hItem) {
         UCMenuCalcUnscaledItemSize( (PUCMITEM)mi.hItem, UCMData->Style, hwndUCMenu, &cx, &cy );
         SumItemWidths  += cx;
         SumItemHeights += cy;
      } else {
         cx = cy = 0;
      } // endif

      if ( cx > MaxVerticalWidth) {
         MaxVerticalWidth = cx;
      } /* endif */

      if ( cy > MaxHorizontalHeight) {
         MaxHorizontalHeight = cy;
      } /* endif */

   }

   UCMData->MaxHorizontalHeight = MaxHorizontalHeight;
   UCMData->MaxVerticalWidth    = MaxVerticalWidth;
   UCMData->SumItemWidths  = SumItemWidths;
   UCMData->SumItemHeights = SumItemHeights;

}


//----------------------------------------------------------------------------
// TranslateAccel : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_TRNACC. name='TranslateAccel' text='Translates an accelerator'.
// This functions translates an accelerator
// :syntax name='TranslateAccel' params='UCMData, hwndMenu, Key, QMsg' return='success'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input'.
// Pointer to the UCMData structure
// :fparam name='hwndMenu' type='HWND' io='input'.
// Menu window handle
// :fparam name='Key' type='USHORT' io='input' .
// :fparam name='QMsg' type='PQMSG' io='output'.
// :freturns.
// :fparam name='success' type='BOOL' io='return'.
// 0 if failure.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
BOOL _Optlink TranslateAccel(PUCMDATA UCMData, HWND HwndMenu, USHORT Key, PQMSG QMsg)
{
    ULONG NbOfItems = UCMData->AccelTable->cAccel;
    ULONG i;
    for(i=0; i<NbOfItems; i++) {
    //??? Accelerator keys don't work, and need to remove use of toupper()
    //ctype
    //   if(toupper(Key) == toupper(UCMData->AccelTable->aaccel[i].key)) {
    //      QMsg->hwnd = HwndMenu;
    //      QMsg->msg  = MM_SELECTITEM;
    //      QMsg->mp1  = (MPARAM)UCMData->AccelTable->aaccel[i].cmd;
    //      QMsg->mp2  = MPFROM2SHORT(0, 1);
    //      return 1;
    //   }
    }
    return 0;
}

//----------------------------------------------------------------------------
// AddAccelItem : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_ADDACC. name='AddAccelItem' text='Adds an accelerator item'.
// This functions adds an accelerator
// :syntax name='AddAccelItem' params='UCMData, Key, id' return='-'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input'.
// Pointer to the UCMData structure
// :fparam name='Key' type='USHORT' io='input' .
// :fparam name='id' type='ULONG' io='input'.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID  _Optlink AddAccelItem(PUCMDATA UCMData, USHORT Key, ULONG id)
{
   ULONG Item = UCMData->AccelTable->cAccel;
   ULONG i;

   for(i=0; i<Item; i++) {
      if(UCMData->AccelTable->aaccel[i].key == Key) {
         UCMData->AccelTable->aaccel[i].cmd = id;
         return;
      }
   }

   UCMData->AccelTable->aaccel[Item].key = Key;
   UCMData->AccelTable->aaccel[Item].fs = AF_CHAR+AF_ALT;
   UCMData->AccelTable->aaccel[Item].cmd = id;
   (UCMData->AccelTable->cAccel)++;
}

//----------------------------------------------------------------------------
// RemoveAccelItem : not for the user's doc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_REMACC. name='RemoveAccelItem' text='Removes an accelerator item'.
// This functions removes an accelerator from the table in UCMData
// :syntax name='RemoveAccelItem' params='UCMData, Key' return='-'.
// :fparams.
// :fparam name='UCMData' type='PUCMDATA' io='input'.
// Pointer to the UCMData structure
// :fparam name='Key' type='USHORT' io='input' .
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// :efparams.
// :remarks.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _Optlink RemoveAccelItem(PUCMDATA UCMData, USHORT Key)
{

  ULONG i;
  for(i=0; i<UCMData->AccelTable->cAccel; i++) {
    if(Key == UCMData->AccelTable->aaccel[i].key) {
       break;
    }
  }

  if(i == UCMData->AccelTable->cAccel) {
     return;
  }

  if(i == (UCMData->AccelTable->cAccel-1)) {
     (UCMData->AccelTable->cAccel)--;
  }

  while(i < UCMData->AccelTable->cAccel) {
     memcpy(&(UCMData->AccelTable->aaccel[i]), &(UCMData->AccelTable->aaccel[i+1]), sizeof(ACCEL));
     i++;
  }

 (UCMData->AccelTable->cAccel)--;
}

#if defined(UCMUI)
//----------------------------------------------------------------------------
// BitmapFileDlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_BMPFILEDLGPROC. name='BitmapFileDlgProc' text='Subclassed file window procedure'.
// Checks that the given filename is a bitmap and loads it before dismissing the file dialog
// :syntax name='BitmapFileDlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// File dialog window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
MRESULT EXPENTRY  BitmapFileDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   switch (msg) {
   case FDM_VALIDATE:
      {
          HBITMAP  hBmp;
          PFILEDLG FileDlg = (PFILEDLG) WinQueryWindowULong( hwnd, QWL_USER );
          PUCMDATA UCMData = (PUCMDATA) FileDlg->ulUser;

          if ( hBmp = UCMenuLoadBitmap( FileDlg->szFullFile ) ) {
             UCMData->hBmpTemp = hBmp;
             UCMData->bBmpTempFromFile = TRUE;
             return (MRESULT)TRUE;
          } else {
             WinMessageBox( HWND_DESKTOP, hwnd,
                            nlsgetmessage ( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_BADBMPFN, 0 ),
                            nlsgetmessage ( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_LOADBMP, 1 ),
                            0, MB_OK | MB_ERROR);
             WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd, DID_FILENAME_ED ) );
             return (MRESULT)FALSE;
          } // endif
      }
   default:
     return WinDefFileDlgProc( hwnd, msg, mp1, mp2 );

   } // endswitch
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuCreateBmpDlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_CREATEBMPDLGPROC. name='UCMEnuCreateBmpDlgProc' text='Bitmap creation dialog procedure'.
// Let the user enter a file name and start iconedit to create this bitmap.
// :syntax name='UCMenuCreateBmpDlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// File dialog window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
MRESULT EXPENTRY  UCMenuCreateBmpDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER );
   switch (msg) {
      case WM_INITDLG:
      {
        WinSetWindowULong( hwnd, QWL_USER, (ULONG)mp2 );
        WinSetDlgItemShort( hwnd, IDC_UCMBMPCX, ((PUCMDATA)mp2)->cx, FALSE );
        WinSetDlgItemShort( hwnd, IDC_UCMBMPCY, ((PUCMDATA)mp2)->cy, FALSE );
      }
      break;
      case WM_COMMAND:
      {
         switch (SHORT1FROMMP(mp1)) {
            case IDB_UCMBMPOK:
            {
               UCHAR pszText[MAXPATHL];
               PSZ pszFullName = MyMalloc( MAXPATHL ); // Will be freed by UCMenuEditBmpFile

               if ( pszFullName ) {
                  SHORT cx, cy;
                  *pszText = '\0';
                  *pszFullName = '\0';
                  WinQueryDlgItemText( hwnd, IDC_UCMBMPNAME, (LONG)MAXPATHL, pszText );
                  WinQueryDlgItemShort( hwnd, IDC_UCMBMPCX, &cx, FALSE );
                  WinQueryDlgItemShort( hwnd, IDC_UCMBMPCY, &cy, FALSE );
                  UCMenuGetBitmapFullName( UCMData, pszText, pszFullName );
                  // We do that just to check whether the file already exists or not
                  if ( *pszFullName!='\0' ){
                     if ( WinMessageBox( HWND_DESKTOP, hwnd,
                                         nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_OVERWRITE, 0 ),
                                         nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_OVERWRITETITLE, 1 ),
                                         0, MB_YESNO ) != MBID_YES ){
                        MyFree( pszFullName );
                        return (MRESULT)TRUE;
                     } // endif
                  } // endif
                  UCMenuCreateBmpFile( pszText, cx, cy );
                  UCMenuGetBitmapFullName( UCMData, pszText, pszFullName );
                  UCMenuEditBmpFile( UCMData->hwndPage1, pszFullName );
               } // endif
            }
            // Fall through
            case IDB_UCMBMPCANCEL:
               WinDismissDlg( hwnd, TRUE );
               break;
            default:
               return WinDefDlgProc( hwnd, msg, mp1, mp2 );
         }
      }  break;

      default:
         return WinDefDlgProc( hwnd, msg, mp1, mp2 );

   } // endswitch

   return (MRESULT) FALSE;
}
#endif

#if defined(UCMUI)
//----------------------------------------------------------------------------
// ResBmpDlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_RESBMPDLGPROC. name='ResBmpDlgProc' text='Resource bitmap selection dialog procedure'.
// Let the user pick a bitmap among those available in the resource.
// :syntax name='ResBmpDlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Dialog window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
MRESULT EXPENTRY  ResBmpDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PUCMDATA UCMData = WinQueryWindowPtr( hwnd, 0 );
   switch (msg) {
      case WM_INITDLG:
      {
         UCMINFO  UCMInfo;
         HWND     hwndUCM;
         HWND     hOwner;
         PULONG   pId     = 0;
         ULONG    ulNbId  = 0;

         UCMData = (PUCMDATA)mp2;
         WinSetWindowPtr( hwnd, 0, UCMData );

         hwndUCM = WinQueryWindow( UCMData->hwndMenu, QW_OWNER );
         hOwner  = WinQueryWindow( hwndUCM, QW_OWNER );

         ulNbId = (ULONG)WinSendMsg( hOwner,
                              WM_CONTROL,
                              MPFROM2SHORT( WinQueryWindowUShort( hwndUCM, QWS_ID ), UCN_QRYRESBMP  ),
                              MPFROMP( &pId )  );
         if ( ulNbId && pId ){
            HWND     hwndUCM, hwndMenu;
            memset( &UCMInfo, 0, sizeof(UCMINFO) );
            UCMInfo.cb       = sizeof( UCMINFO );
            UCMInfo.hModule  = UCMData->hModBmp;
            UCMInfo.Style    = UCS_FRAMED | UCS_NOTEXT | UCS_NO_DM | UCS_NO_CM;
            if ( UCMData->Style & UCS_CHNGBMPBG ) {
               UCMInfo.Style |= UCS_CHNGBMPBG;
            } // endif
            if ( UCMData->Style & UCS_FORCESIZE ) {
               UCMInfo.Style |= UCS_FORCESIZE;
               UCMInfo.cx = UCMData->cx;
               UCMInfo.cy = UCMData->cy;
            } // endif
            UCMInfo.BgBmp       = UCMData->BgBmp;
            UCMInfo.BgColor     = UCMData->BgColor;
            UCMInfo.ItemBgColor = UCMData->ItemBgColor;

            hwndMenu = WinCreateWindow( HWND_OBJECT,
                                        WC_MENU,
                                        "",
                                        MS_ACTIONBAR,
                                        0,
                                        0,
                                        0,
                                        0,
                                        HWND_OBJECT,
                                        HWND_BOTTOM,
                                        7, // magic number ...
                                        0,
                                        0 );
            hwndUCM = UCMenuCreateFromHMenu(
                                          WinQueryAnchorBlock( hwnd ),
                                          hwnd,
                                          hwnd,
                                          CMS_HORZ,
                                          0,
                                          0,
                                          0,
                                          0,
                                          HWND_TOP,
                                          7,          // magic number ...
                                          hwndMenu,
                                          (PVOID)&UCMInfo );

            {
               PVOID pArgs;

               pArgs = MyMalloc( sizeof( HWND ) + sizeof( PULONG ) + sizeof( ULONG ) + sizeof( HWND ) );

               if ( pArgs ){
                  *( (HWND*)pArgs ) = hwnd;
                  *( (PULONG*)( (PBYTE)pArgs + sizeof( HWND ) ) ) = pId;
                  *( (PULONG)( (PBYTE)pArgs + sizeof( HWND ) + sizeof( PULONG ) ) ) = ulNbId;
                  *( (PHWND)( (PBYTE)pArgs + sizeof( HWND ) + sizeof( PULONG ) + sizeof( ULONG ) ) ) = hwndMenu;

                  WinSetDlgItemText( hwnd, IDC_RESBMPTEXT, nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_BMPLOADING, 0 ) );

                  DosCreateThread( &( UCMData->tid ), (PFNTHREAD)UCMenuLoadResBmp, (ULONG)pArgs, 0, 8192 );
               } // endif
            }
         } else {
            WinSetDlgItemText( hwnd, IDC_RESBMPTEXT, nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_NOBMPRES, 0 ) );
         } // endif
      }
      break;
      case WM_CONTROL:
      {
         switch ( SHORT1FROMMP( mp1 ) ){
         case 7: // ID of the ucmenu ...
            switch ( SHORT2FROMMP( mp1 ) ){
            case UCN_ITEMSELECTED:
               {
                  PUCMITEM pucmi = (PUCMITEM)mp2;
                  if ( pucmi ) {
                     sscanf( pucmi->pszBmp, "%i", &( UCMData->ulBmpTempId ) );
                  } else {
                     UCMData->ulBmpTempId = 0;
                  } // endif
                  WinDismissDlg( hwnd, (USHORT)1 );
                  return (MRESULT)TRUE;
               }
               break;
            default :
               return (MRESULT)0;

            } // endswitch
            break;
         default:
            return WinDefDlgProc( hwnd, msg, mp1, mp2 );

         } // endswitch
      }
      break;
      case WM_CLOSE:
         if ( DosWaitThread( &( UCMData->tid ), DCWW_NOWAIT ) != ERROR_THREAD_NOT_TERMINATED ){
            // Don't close unless the threaded loading ended, else trouble!
            return WinDefDlgProc( hwnd, msg, mp1, mp2 );
         } /* endif */;
         break;
      case WM_COMMAND:
      {

         switch ( SHORT1FROMMP( mp1 ) ) {
            case DID_CANCEL:
            case IDB_RESBMPCANCEL:
               if ( DosWaitThread( &( UCMData->tid ), DCWW_NOWAIT ) != ERROR_THREAD_NOT_TERMINATED ){
                  // Don't dismiss unless the threaded loading ended, else trouble!
                  WinDismissDlg( hwnd, 0 );
               } /* endif */;
               break;
            default:
               return WinDefDlgProc( hwnd, msg, mp1, mp2 );
         }
      }  break;

      default:
         return WinDefDlgProc( hwnd, msg, mp1, mp2 );
         break;
   } // endswitch

   return (MRESULT) FALSE;
}
#endif


#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMDlgProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_UCMDLGPROC. name='UCMDlgProc' text='Buffet toolbar selection dialog procedure'.
// Let the user pick items from the buffet toolbar
// :syntax name='ResBmpDlgProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Dialog window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
MRESULT EXPENTRY UCMDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
   PUCMDLGINFO pUCMDlgInfo = (PUCMDLGINFO)WinQueryWindowULong( hwnd, QWL_USER );

   if ( !pUCMDlgInfo && ( msg != WM_INITDLG ) ) {
     return( WinDefDlgProc( hwnd, msg, mp1, mp2 ) );
   } /* endif */

   switch ( msg ) {
   case WM_INITDLG:
     {
       PVOID    pCurUCMTemplate;
       ULONG    ulBufLen;
       SWP      swpBuffetDesc, swpCurrentDesc, swpText, swp;
       HWND     hwndBuffet, hwndCurrent, hwndTmp;
       UCMINFO  UCMInfo;
       HAB      hab = WinQueryAnchorBlock( hwnd );

       pUCMDlgInfo = (PUCMDLGINFO)mp2;
       if ( !pUCMDlgInfo ) {
         return (MRESULT)FALSE;
       } /* endif */

       WinSetWindowULong( hwnd, QWL_USER, (ULONG)pUCMDlgInfo );

       // Query the desc positions
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENTDESC ), &swpCurrentDesc );
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFETDESC ),  &swpBuffetDesc  );
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_TEXT ),  &swpText  );
       WinQueryWindowPos( hwnd, &swp );

       // Query the current toolbar
       pCurUCMTemplate = UCMenuMakeTemplate( pUCMDlgInfo->hwndUCMenu, &ulBufLen );

       // Query Its UCMINFO structure
       memset( &UCMInfo, '\0', sizeof UCMInfo );
       WinSendMsg( pUCMDlgInfo->hwndUCMenu, UCMENU_QUERYUCMINFO, MPFROMP( & UCMInfo ), (MPARAM)0 );

       WinCheckButton( hwnd, IDD_UCMDLG_TEXT, ( UCMInfo.Style & UCS_NOTEXT )? FALSE : TRUE );

       UCMInfo.cb     =  sizeof( UCMINFO );
       UCMInfo.Style &= UCS_FORCESIZE             |
                        UCS_FRAMED                |
                        UCS_NOTEXT                |
                        UCS_SHRINK_BLEND          |
                        UCS_SHRINK_OR             |
                        UCS_CHNGBMPBG             |
                        UCS_NO_CM_SEPARATOR       |
                        UCS_NO_CM_MENU_STYLE      |
                        UCS_NO_CM_MENU_IMPORT     |
                        UCS_NO_CM_MENU_EXPORT     |
                        UCS_NO_CM_MENU_DEFAULT    |
                        UCS_NO_CM_ITEM_EDIT       |
                        UCS_NO_CM_ITEM_CREATE     |
                        UCS_NO_CM_ITEM_DELETE     |
                        UCS_NO_CM                 |
                        UCS_NODEFAULTACTION;

       // Create its copy
       hwndCurrent = UCMenuCreateFromTemplate(
                                 hab,
                                 hwnd,
                                 hwnd,
                                 CMS_HORZ,
                                 0,
                                 0,
                                 swp.cx - swpCurrentDesc.x -14,
                                 0,
                                 HWND_TOP,
                                 IDD_UCMDLG_CURRENT,  // ID of the ucmenu, could be different from the menu id
                                 pCurUCMTemplate,     // module of the menu resource
                                 (PVOID)&UCMInfo,
                                 &hwndTmp );
       if ( pCurUCMTemplate ) {
         MyFree( pCurUCMTemplate );
       } /* endif */

       // Create the buffet toolbar
       UCMInfo.Style &= UCS_FORCESIZE |
                        UCS_FRAMED |
                        UCS_NOTEXT |
                        UCS_SHRINK_BLEND |
                        UCS_SHRINK_OR |
                        UCS_CHNGBMPBG;
       UCMInfo.Style |=  UCS_NO_CM | UCS_NOITEMSMODIF;
       UCMInfo.Style &= ~UCS_NO_DM_C_TO_OTHER;
       if ( pUCMDlgInfo->bFromTemplate ){
          hwndBuffet = UCMenuCreateFromTemplate(
                                    hab,
                                    hwnd,
                                    hwnd,
                                    CMS_HORZ,
                                    0,
                                    0,
                                    swp.cx - swpBuffetDesc.x -14,
                                    0,
                                    HWND_TOP,
                                    IDD_UCMDLG_BUFFET,  // ID of the ucmenu, could be different from the menu id
                                    pUCMDlgInfo->pTemplate,
                                    (PVOID)&UCMInfo,
                                    &hwndTmp );
       } else {
          hwndBuffet = UCMenuCreateFromResource(
                                    hab,
                                    hwnd,
                                    hwnd,
                                    CMS_HORZ,
                                    0,
                                    0,
                                    swp.cx - swpBuffetDesc.x -14,
                                    0,
                                    HWND_TOP,
                                    IDD_UCMDLG_BUFFET,  // ID of the ucmenu, could be different from the menu id
                                    pUCMDlgInfo->hmodBuffetMenu,
                                    pUCMDlgInfo->ulBuffetMenuID,
                                    (PVOID)&UCMInfo,
                                    &hwndTmp );
       } // endif

       // Subclass the icon to destroy items dropped over it
       WinSetWindowULong( WinWindowFromID( hwnd, IDD_UCMDLG_SHREDDER ), QWL_USER, (ULONG)pUCMDlgInfo );
       pUCMDlgInfo->OldShredderWndProc = WinSubclassWindow( WinWindowFromID( hwnd, IDD_UCMDLG_SHREDDER ), ShredderWndProc );

       WinSendMsg( hwnd, WM_SIZE, (MPARAM)0, (MPARAM)0 );

       // Ask for the list of actions and descriptions
       WinSendMsg( WinQueryWindow( pUCMDlgInfo->hwndUCMenu, QW_OWNER ),
                   WM_CONTROL,
                   MPFROM2SHORT( WinQueryWindowUShort( pUCMDlgInfo->hwndUCMenu, QWS_ID ), UCN_QRYACTIONLIST ),
                   MPFROMP( hwnd ) );


       // Cleanup
       if ( UCMInfo.pszBitmapSearchPath ) {
         MyFree( UCMInfo.pszBitmapSearchPath );
       } /* endif */
       if ( UCMInfo.pszDefaultBitmap ) {
         MyFree( UCMInfo.pszDefaultBitmap );
       } /* endif */
       if ( UCMInfo.pszFontNameSize ) {
         MyFree( UCMInfo.pszFontNameSize );
       } /* endif */

       return (MRESULT)FALSE;
     }

   case UCMENU_INSERTACTION:
      {
         WinSendDlgItemMsg( hwnd,
                            IDD_UCMDLG_ACTIONS,
                            LM_INSERTITEM,
                            (MPARAM)LIT_END,
                            mp1 );
         WinSendDlgItemMsg( hwnd,
                            IDD_UCMDLG_DESCR,
                            LM_INSERTITEM,
                            (MPARAM)LIT_END,
                            mp2 );
         return (MRESULT)0;
      }

   case WM_CONTROL:
     if ( ( SHORT1FROMMP( mp1 ) == IDD_UCMDLG_CURRENT || SHORT1FROMMP( mp1 ) == IDD_UCMDLG_BUFFET ) &&
          ( SHORT2FROMMP( mp1 ) == UCN_ITEMSELECTED ) ){
        PUCMITEM pucmi = (PUCMITEM)mp2;
        SHORT  sIndex;
        PSZ    pszTxt;
        CHAR   pszDesc[MAXDESCLEN];

        if ( pucmi && pucmi->pszAction ){
           pszTxt = pucmi->pszAction;
        } else {
           return (MRESULT)FALSE;
        } /* endif */
        sIndex = (USHORT)WinSendDlgItemMsg( hwnd,
                                            IDD_UCMDLG_ACTIONS,
                                            LM_SEARCHSTRING,
                                            MPFROM2SHORT( LSS_CASESENSITIVE, LIT_FIRST ),
                                            MPFROMP( pszTxt ) );
        if ( sIndex != LIT_NONE && sIndex != LIT_ERROR ){
           WinSendDlgItemMsg( hwnd,
                              IDD_UCMDLG_DESCR,
                              LM_QUERYITEMTEXT,
                              MPFROM2SHORT( sIndex, MAXDESCLEN ),
                              MPFROMP( pszDesc ) );
           WinMessageBox( HWND_DESKTOP, hwnd,
                          pszDesc,
                          nlsgetmessage( WinQueryAnchorBlock( hwnd ),
                                         pUCMDlgInfo->UCMData->hModUCM,
                                         NLS_ITEMDESCR, 0 ),
                          0, MB_CANCEL | MB_INFORMATION | MB_APPLMODAL | MB_MOVEABLE );
        } // endif
        return (MRESULT)FALSE;
     } /* endif */
     switch ( SHORT1FROMMP( mp1 ) ) {
     case IDD_UCMDLG_TEXT:
        switch ( SHORT2FROMMP( mp1 ) ){
        case BN_CLICKED:
          {
            ULONG  ulStyle1, ulStyle2, ulCx1, ulCy1, ulCx2, ulCy2;
            USHORT usText;
            WinSendMsg( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFET ),
                        UCMENU_QUERYSTYLE,
                        MPFROMP( &ulStyle1 ),
                        (MPARAM)0 );
            WinSendMsg( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT ),
                        UCMENU_QUERYSTYLE,
                        MPFROMP( &ulStyle2 ),
                        (MPARAM)0 );
            WinSendMsg( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFET ),
                        UCMENU_QUERYFORCEDSIZE,
                        MPFROMP( &ulCx1 ),
                        MPFROMP( &ulCy1 ) );
            WinSendMsg( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT ),
                        UCMENU_QUERYFORCEDSIZE,
                        MPFROMP( &ulCx2 ),
                        MPFROMP( &ulCy2 ) );
            usText = WinQueryButtonCheckstate( hwnd, IDD_UCMDLG_TEXT );
            if ( usText ) {
               ulStyle1 &= ~UCS_NOTEXT;
               ulStyle2 &= ~UCS_NOTEXT;
            } else {
               ulStyle1 |= UCS_NOTEXT;
               ulStyle2 |= UCS_NOTEXT;
            } /* endif */
            WinPostMsg( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFET ),
                        UCMENU_SETSTYLE,
                        (MPARAM)ulStyle1,
                        MPFROM2SHORT( (USHORT)ulCx1, (USHORT)ulCy1 ) );
            WinPostMsg( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT ),
                        UCMENU_SETSTYLE,
                        (MPARAM)ulStyle2,
                        MPFROM2SHORT( (USHORT)ulCx2, (USHORT)ulCy2 ) );
            WinPostMsg( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFET ),
                        UCMENU_UPDATE,
                        (MPARAM)0,
                        (MPARAM)0 );
            WinPostMsg( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT ),
                        UCMENU_UPDATE,
                        (MPARAM)0,
                        (MPARAM)0 );

          }
          break;
        default:
          break;
        } /* endswitch */

     case IDD_UCMDLG_CURRENT:
        switch ( SHORT2FROMMP( mp1 ) ){
        case UCN_SIZE:
           WinSendMsg( hwnd, WM_SIZE, (MPARAM)0, (MPARAM)0 );
           break;
        case UCN_QRYDEFTEMPLATEID:
        case UCN_QRYTEMPLATEMODULE:
        case UCN_QRYDEFTEMPLATE:
        case UCN_QRYACTIONLIST:
        case UCN_QRYRESBMP:
           mp1 = MPFROM2SHORT( WinQueryWindowUShort( pUCMDlgInfo->hwndUCMenu, QWS_ID ), SHORT2FROMMP( mp1 ) );
           return WinSendMsg( WinQueryWindow( pUCMDlgInfo->hwndUCMenu, QW_OWNER ),
                              msg, mp1, mp2 );

        default:
          break;
        } /* endswitch */

     default:
       break;
     } /* endswitch */

  case WM_COMMAND:
     switch ( (USHORT)mp1 ) {
     case IDD_UCMDLG_OK:
       { PVOID  pNewTemplate;
         ULONG  ulLen;
         pNewTemplate =
           UCMenuMakeTemplate( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT ), &ulLen );
         UCMenuNew( pUCMDlgInfo->hwndUCMenu, pNewTemplate );
         MyFree( pNewTemplate );
         WinDismissDlg( hwnd, 1 );

         // process the text checkmark
#if 0
         WinSendMsg( pUCMDlgInfo->hwndUCMenu,
                     UCMENU_QUERYSTYLE,
                     MPFROMP( &ulStyle ),
                     (MPARAM)0 );
         WinSendMsg( pUCMDlgInfo->hwndUCMenu,
                     UCMENU_QUERYFORCEDSIZE,
                     MPFROMP( &ulCx ),
                     MPFROMP( &ulCy ) );
         usText = WinQueryButtonCheckstate( hwnd, IDD_UCMDLG_TEXT );
         if ( usText ) {
            elQtyle &= ~UCS_NOTEXT;
         } else {
            ulStyle |= UCS_NOTEXT;
         } /* endif */
         WinPostMsg( pUCMDlgInfo->hwndUCMenu,
                    UCMENU_SETSTYLE,
                     (MPARAM) ulStyle,
                     MPFROM2SHORT( (USHORT)ulCx, (USHORT)ulCy ) );
         WinPostMsg( pUCMDlgInfo->hwndUCMenu,
                     UCMENU_UPDATE,
                     (MPARAM)0,
                     (MPARAM)0 );
#endif
       }
       break;
     case DID_CANCEL:
     case IDD_UCMDLG_CANCEL:
       WinDismissDlg( hwnd, 0 );
       break;
     case IDD_UCMDLG_DEFAULT:
       UCMenuLoadDefault( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT ) );
       break;
    case IDD_UCMDLG_HELP:
       UCMenuDisplayHelp( pUCMDlgInfo->UCMData,
                          (USHORT)PANEL_BUFFET,
                          (USHORT)UCN_HLP_BUFFET );
       break;
     default:
       break;
     } /* endswitch */
     break;
  case WM_SIZE:
     {
       SWP   swpCurrentDesc, swpBuffetDesc, swpText, swp;
       HWND  hwndCurrent, hwndBuffet;
       ULONG ulCxBuf, ulCyBuf, ulCxCur, ulCyCur;

       hwndCurrent = WinWindowFromID( hwnd, IDD_UCMDLG_CURRENT );
       hwndBuffet  = WinWindowFromID( hwnd, IDD_UCMDLG_BUFFET );

       // Query the desc positions
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENTDESC ), &swpCurrentDesc );
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFETDESC ),  &swpBuffetDesc  );
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_TEXT ),  &swpText  );
       WinQueryWindowPos( hwnd, &swp );

       // query its height, set its position and show it
       WinSendMsg( hwndCurrent, UCMENU_QUERYSIZE, MPFROMP(&ulCxCur), MPFROMP(&ulCyCur) );
       WinSetWindowPos( hwndCurrent,
                        HWND_TOP,
                        swpCurrentDesc.x + 6,
                        swpText.y + swpText.cy + 10,
                        0,
                        0,
                        SWP_MOVE | SWP_SHOW );
       WinSetWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENTDESC ),
                        HWND_TOP,
                        swpCurrentDesc.x,
                        swpText.y + swpText.cy + ulCyCur + 15,
                        0,
                        0,
                        SWP_MOVE | SWP_SHOW );
       WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_CURRENTDESC ), &swpCurrentDesc );

       // query its height, set its position and show it
       WinSendMsg( hwndBuffet, UCMENU_QUERYSIZE, MPFROMP(&ulCxBuf), MPFROMP(&ulCyBuf) );
       WinSetWindowPos( hwndBuffet,
                        HWND_TOP,
                        swpBuffetDesc.x + 6,
                        swpCurrentDesc.y + swpCurrentDesc.cy + 10,
                        0,
                        0,
                        SWP_MOVE | SWP_SHOW );
       WinSetWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_BUFFETDESC ),
                        HWND_TOP,
                        swpBuffetDesc.x,
                        swpCurrentDesc.y + swpCurrentDesc.cy + ulCyBuf + 15,
                        0,
                        0,
                        SWP_MOVE | SWP_SHOW );
       WinSetWindowPos( hwnd,
                        HWND_TOP,
                        0,
                        0,
                        swp.cx,
                        swpCurrentDesc.y + swpCurrentDesc.cy + ulCyBuf + swpBuffetDesc.cy + 20
                         + WinQuerySysValue( HWND_DESKTOP, SV_CYTITLEBAR ) + WinQuerySysValue( HWND_DESKTOP, SV_CYDLGFRAME ),
                        SWP_SIZE | SWP_SHOW );
        return (MRESULT)0;
     }
     break;
//case WM_PAINT:
//   {
//      RECTL rcl;
//      SWP   swp;
//      HPS   hps;
//
//      WinDefDlgProc( hwnd, msg, mp1, mp2 );
//
//      WinQueryWindowPos( WinWindowFromID( hwnd, IDD_UCMDLG_SHREDDER ), &swp );
//      rcl.xLeft   = swp.x - 10;
//      rcl.xRight  = swp.x + swp.cx + 10;
//      rcl.yBottom = swp.y - 10;
//      rcl.yTop    = swp.y + swp.cy + 10;
//      hps = WinGetPS( hwnd );
//      UCMenu3DFrame( hps, &rcl, TRUE );
//      WinDrawBorder( hps, &rcl, 1, 1, CLR_BLACK, 0, DB_PATCOPY );
//      WinReleasePS( hps );
//   }
//   break;
  default:
      return( WinDefDlgProc( hwnd, msg, mp1, mp2 ) );
      break;
   } /* endswitch */
   return (MRESULT)FALSE;

}
#endif


#if defined(UCMUI)
//----------------------------------------------------------------------------
// ShredderWndProc
//----------------------------------------------------------------------------
// :pfunction res=&IDF_SHRDDRWNDPROC. name='ShredderWndProc' text='Subclassed wnd proc for the shredder icon'.
// This wndproc processes the drop of ucmenu items over the buffet dialog shredder.
// :syntax name='ShredderWndProc' params='hwnd, msg, mp1, mp2' return='mresult' .
// :fparams.
// :fparam name='hwnd' type='HWND' io='input' .
// Window handle
// :fparam name='msg' type='ULONG' io='input' .
// Message
// :fparam name='mp1' type='MPARAM' io='input'.
// First parameter
// :fparam name='mp2' type='MPARAM' io='input'.
// Second parameter
// :freturns.
// :fparam name='mresult' type='MRESULT' io='return'.
// Return code of a PM message.
// :efparams.
// :remarks.
// :epfunction.
MRESULT EXPENTRY ShredderWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
   PUCMDLGINFO pUCMDlgInfo = (PUCMDLGINFO)WinQueryWindowULong( hwnd, QWL_USER );

   if ( !pUCMDlgInfo ) {
     return( WinDefWindowProc( hwnd, msg, mp1, mp2 ) );
   } /* endif */

   switch ( msg ){
   case DM_DRAGLEAVE:
      {
         RECTL rcl;
         HPS hps = DrgGetPS( hwnd );
         WinQueryWindowRect( hwnd, &rcl );
//       rcl.xLeft   -=  5;
//       rcl.xRight  +=  5;
//       rcl.yBottom -=  5;
//       rcl.yTop    +=  5;
         WinDrawBorder( hps, &rcl, 1, 1, CLR_PALEGRAY, 0, DB_PATCOPY);
         DrgReleasePS( hps );
      }
      break;
   case DM_DRAGOVER:
      {
       PDRAGINFO  pDraginfo = (PDRAGINFO)mp1;
       USHORT     usOperation, usIndicator;
       PDRAGITEM  pditem;
       RECTL rcl;
       HPS hps = DrgGetPS( hwnd );

       WinQueryWindowRect( hwnd, &rcl );
//     rcl.xLeft   -=  5;
//     rcl.xRight  +=  5;
//     rcl.yBottom -=  5;
//     rcl.yTop    +=  5;
       WinDrawBorder( hps, &rcl, 1, 1, CLR_BLACK, 0, DB_PATCOPY);
       DrgReleasePS( hps );

       /* ---------------------------------------------------------------------- */
       /* Get access to the DRAGINFO structure.                                  */
       /* ---------------------------------------------------------------------- */
       DrgAccessDraginfo( pDraginfo );
       pditem = DrgQueryDragitemPtr( pDraginfo, 0 );

       if ( WinQueryWindowUShort( WinQueryWindow( pDraginfo->hwndSource, QW_OWNER ), QWS_ID )
            != IDD_UCMDLG_CURRENT ) {
          usIndicator = DOR_NEVERDROP;
          DrgFreeDraginfo (pDraginfo);
          return (MRFROM2SHORT(usIndicator, usOperation));
       } /* endif */

       /* ---------------------------------------------------------------------- */
       /* Determine if a drop can be accepted                                    */
       /* ---------------------------------------------------------------------- */
       usIndicator = DOR_DROP;
       usOperation = pDraginfo->usOperation;
       switch (pDraginfo->usOperation) {
         case DO_COPY:
           usIndicator = DOR_NODROPOP;
           break;
         case DO_MOVE:
           usOperation = DO_MOVE;
           break;
         case DO_DEFAULT:
           usOperation = DO_MOVE;
           break;
         case DO_UNKNOWN:
            usIndicator = DOR_NODROPOP;
            break;
        default:
           usIndicator = DOR_NODROP;
           usOperation = 0;
       } // endswitch

       if ( !DrgVerifyRMF( pditem, "DRM_UCMITEM",  "DRF_UNKNOWN" ) ){
          usIndicator = DOR_NEVERDROP;
       } // endif


       DrgFreeDraginfo( pDraginfo );

       return MRFROM2SHORT( usIndicator, usOperation );
      }
      break;
   case DM_DROP:
      {
         PDRAGINFO pDraginfo = (PDRAGINFO)mp1;
         PDRAGITEM pditem;
         RECTL rcl;
         HPS hps = DrgGetPS( hwnd );
         WinQueryWindowRect( hwnd, &rcl );
//       rcl.xLeft   -=  5;
//       rcl.xRight  +=  5;
//       rcl.yBottom -=  5;
//       rcl.yTop    +=  5;
         WinDrawBorder( hps, &rcl, 1, 1, CLR_PALEGRAY, 0, DB_PATCOPY);
         DrgReleasePS( hps );

         DrgAccessDraginfo( pDraginfo );

         pditem = DrgQueryDragitemPtr( pDraginfo, 0 );

         if ( pditem ){
              switch ( pDraginfo->usOperation ){
                case DO_MOVE:
                   WinSendMsg( WinQueryWindow( pDraginfo->hwndSource, QW_OWNER ),
                               MM_DELETEITEM,
                               MPFROM2SHORT( (USHORT)(pditem->ulItemID), TRUE ),
                               (MPARAM)0 );
                   break;
                default:
                  //-- invalid operation
                  break;
              } // endswitch
         } // endif  pditem

         // ----------------------------------------------------------------------
         // -- free the resource:
         // ----------------------------------------------------------------------
         DrgDeleteDraginfoStrHandles( pDraginfo );
         DrgFreeDraginfo( pDraginfo );
      }
      break;
   default:
      return pUCMDlgInfo->OldShredderWndProc( hwnd, msg, mp1, mp2 );
      break;
   } // endif
   return (MRESULT)0;
}
#endif

//----------------------------------------------------------------------------
// UCMenuResourceBuffetDlg
//----------------------------------------------------------------------------
// :function res=&IDF_RESBUFFETDLG. name='UCMenuResourceBuffetDlg' text='Toolbar customization dialog'.
// This dialog let the user pick items from a buffet toolbar coming from a resource..
// :syntax name='UCMenuResourceBuffetDlg' params='hParent, hUCMenu, ulBuffetID, hmodBuffet' return='-' .
// :fparams.
// :fparam name='hParent' type='HWND' io='input' .
// Parent of the dialog.
// :fparam name='hUCMenu' type='HWND' io='input' .
// Handle of the ucmenu to modify.
// :fparam name='ulBuffetID' type='ULONG' io='input' .
// ID of the buffet menu.
// :fparam name='hmodBuffet' type='HMODULE' io='input' .
// Module where the buffet menu is.
// :freturns.
// :fparam name='ulResult' type='ULONG' io='return'.
// result of WinDglBox
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------

ULONG APIENTRY UCMenuResourceBuffetDlg( HWND hParent, HWND hUCMenu, ULONG ulBuffetID, HMODULE hmodBuffet)
{
   #if defined(UCMUI)  // Only build this code if we support a user interface
   UCMDLGINFO UCMDlgInfo;
   ULONG      ulResult = 0;
   PUCMDATA   UCMData = (PUCMDATA)WinQueryWindowULong( hUCMenu, QWL_UCMDATA );

   if ( UCMData ){
      memset( &UCMDlgInfo, '\0', sizeof( UCMDLGINFO ) );

      UCMDlgInfo.ulSize         = sizeof( UCMDLGINFO );
      UCMDlgInfo.hwndUCMenu     = hUCMenu;
      UCMDlgInfo.UCMData        = UCMData;
      UCMDlgInfo.ulBuffetMenuID = ulBuffetID;
      UCMDlgInfo.hmodBuffetMenu = hmodBuffet;
      UCMDlgInfo.bFromTemplate  = FALSE;
      ulResult = WinDlgBox( hParent,
                  WinQueryWindow( hUCMenu, QW_OWNER ),
                  UCMDlgProc,
                  UCMData->hModUCM,
                  IDD_UCMDLG,
                  (PVOID)&UCMDlgInfo );
   } /* endif */
   return ulResult;
   #endif
   return DID_CANCEL;  // Return dummy value
}

#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuTemplateBuffetDlg
//----------------------------------------------------------------------------
// :function res=&IDF_TMPLBUFFETDLG. name='UCMenuTemplateBuffetDlg' text='Toolbar customization dialog'.
// This dialog let the user pick items from a buffet toolbar coming from a template..
// :syntax name='UCMenuTemplateBuffetDlg' params='hParent, hUCMenu, pTemplate' return='-' .
// :fparams.
// :fparam name='hParent' type='HWND' io='input' .
// Parent of the dialog.
// :fparam name='hUCMenu' type='HWND' io='input' .
// Handle of the ucmenu to modify.
// :fparam name='pTemplate' type='PVOID' io='input' .
// Template of the buffet menu
// :freturns.
// :fparam name='ulResult' type='ULONG' io='return'.
// result of WinDglBox
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------

ULONG APIENTRY UCMenuTemplateBuffetDlg( HWND hParent, HWND hUCMenu, PVOID pTemplate )
{
   #if defined(UCMUI)  // Only build this code if we support a user interface
   UCMDLGINFO UCMDlgInfo;
   HWND       hBuffet;
   ULONG      ulResult = 0;
   PUCMDATA UCMData = (PUCMDATA)WinQueryWindowULong( hUCMenu, QWL_UCMDATA );

   if ( UCMData ){
      memset( &UCMDlgInfo, '\0', sizeof( UCMDLGINFO ) );

      UCMDlgInfo.ulSize         = sizeof( UCMDLGINFO );
      UCMDlgInfo.hwndUCMenu     = hUCMenu;
      UCMDlgInfo.hwndBuffet     = hBuffet;
      UCMDlgInfo.UCMData        = UCMData;
      UCMDlgInfo.pTemplate      = pTemplate;
      UCMDlgInfo.bFromTemplate  = TRUE;
      ulResult = WinDlgBox( hParent,
        WinQueryWindow( hUCMenu, QW_OWNER ),
        UCMDlgProc,
        UCMData->hModUCM,
        IDD_UCMDLG,
        (PVOID)&UCMDlgInfo );
   } /* endif */
   return ulResult;
   #endif
   return DID_CANCEL;  // Return dummy value
}
#endif // UCMUI

//----------------------------------------------------------------------------
// UCMenuGetVersion
//----------------------------------------------------------------------------
// :function res=&IDF_GETVER. name='UCMenuGetVersion' text='Get the version of the toolbar'.
// This function returns the version of the ucmenus code.
// :syntax name='UCMenuGetVersion' params='-' return='ulVersion' .
// :fparams.
// :freturns.
// :fparam name='ulVersion' type='ULONG' io='return'.
// version of the ucmenus.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------

ULONG APIENTRY UCMenuGetVersion()
{
   return (ULONG) UCMENUS_VERSION;

}


#if defined(UCMUI)
//----------------------------------------------------------------------------
// UCMenuLoadResBmp
//----------------------------------------------------------------------------
// :pfunction res=&IDF_LOADRESBMP. name='UCMenuLoadResBmp' text='Load the built-in bitmaps'.
// This function loads the built-in bitmap in the resource bitmaps dialog toolbar
// It is started by ResBmpDlgProc in a second thread.
// :syntax name='UCMenuLoadResBmp' params='pArgs' return='-' .
// :fparams.
// :fparam name='pArgs' type='PVOID' io='input' .
// Points to &colon.
// :dl compact.
// :dt.hwnd
// :dd.HWND, handle of the calling dialog.
// :dt.pID
// :dd.PULONG, points to the bitmap ids, freed by UCMenuLoadResBmp
// :dt.ulNb
// :dd.ULONG, number of  bitmap ids.
// :dt.hwndMenu
// :dd.HWND, handle of the toolbar menu
// Freed by UCMenuLoadResBmp
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing
// :efparams.
// :remarks.
// The calling convention must be _System because this function
// is used in a DosCreateThread.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
VOID _System UCMenuLoadResBmp( PVOID pArgs )
{
   if ( pArgs ){
      int      i;
      ULONG    ulNbId, ulH, ulW;
      PULONG   pId;
      MENUITEM mi;
      HWND     hwnd, hwndText, hwndButton, hwndUCM, hwndMenu;
      PUCMDATA UCMData;
      HAB      hab;
      HMQ      hmq;
      SWP      swp, swp2;

      hab = WinInitialize(0);
     hmq = WinCreateMsgQueue( hab, 0 );

      // Get hwnd
      hwnd = *( (HWND*)pArgs );
      // Get pId
      pId = *( (PULONG*)( (PBYTE)pArgs + sizeof( HWND ) ) );
      // Get ulNbId;
      ulNbId = *( (PULONG)( (PBYTE)pArgs + sizeof( HWND ) + sizeof( PULONG ) ) );
      // Get hwndMenu
      hwndMenu = *( (PHWND)( (PBYTE)pArgs + sizeof( HWND ) + sizeof( PULONG ) + sizeof( ULONG ) ) );

      UCMData = (PUCMDATA)WinQueryWindowULong( hwnd, QWL_USER );

      hwndUCM  = WinWindowFromID( hwnd, 7 ); // 7 is the magic bitmaps ucmenu ID

      for ( i = 0; i < ulNbId; i++ ){
         memset( &mi, '\0', sizeof mi );
         mi.iPosition = MIT_END;
         mi.afStyle   = MIS_OWNERDRAW;
         mi.id = UCMenuGetNewID( hwndMenu, MIT_NONE, (PUCMDATA)WinQueryWindowULong( hwndMenu, QWL_USER ) ) + 1;
         mi.hItem = (LONG)MyMalloc( sizeof( UCMITEM ) );
         if ( mi.hItem ){
            CHAR szId[22];
            sprintf( szId, "%i", pId[i] );
            memset( (PVOID)mi.hItem, 0, sizeof( UCMITEM ) );
            ITEM( &mi, pszBmp ) = MyMalloc( strlen( szId ) + 1 );
            strcpy( ITEM( &mi, pszBmp ), szId );
            WinSendMsg( hwndUCM, MM_INSERTITEM, MPFROMP( &mi ), MPFROMP( "" ) );
         } // endif
      } // endfor
      MyFree( pId );

      // query ucmenu size
      WinSendMsg( hwndUCM, UCMENU_QUERYSIZE, MPFROMP( &ulW ), MPFROMP( &ulH ) );

      // query dialog size
      WinQueryWindowPos( hwnd, &swp );
      hwndText   = WinWindowFromID( hwnd, IDC_RESBMPTEXT );
      hwndButton = WinWindowFromID( hwnd, IDB_RESBMPCANCEL );
      WinQueryWindowPos( hwndButton, &swp2 );

      // size window
      WinSetWindowPos( hwnd, HWND_TOP, 0, 0, swp.cx, ulH + swp2.y + swp2.cy + 50,  SWP_SIZE );

      // position static text
      WinSetWindowPos( hwndText, HWND_TOP,
                       5, swp2.y, swp2.x - 10, swp2.cy, SWP_MOVE | SWP_SHOW | SWP_SIZE );

      // position, size and show ucm
      WinSetWindowPos( hwndUCM, HWND_TOP, 10, swp2.y + swp2.cy + 10, swp.cx - 20, ulH, SWP_MOVE | SWP_SHOW | SWP_SIZE );

      // show window
      WinSetWindowPos( hwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOW  );

      // Set text
      WinSetDlgItemText( hwnd, IDC_RESBMPTEXT, nlsgetmessage( WinQueryAnchorBlock( hwnd ), UCMData->hModUCM, NLS_BMPLOADED, 0 ) );

      MyFree( pArgs );

      WinDestroyMsgQueue( hmq );
      WinTerminate( hab );
   } // endif pArgs
}
#endif // UCMUI

//----------------------------------------------------------------------------
// SubMemStrdup
//----------------------------------------------------------------------------
// :pfunction res=&IDF_SUBMEMSTRDUP. name='SubMemStrdup' text='strdup in a memory pool'.
// Does a strdup in a memory pool.
// :syntax name='SubMemStrdup' params='pSubMem, pszSource' return='pszTarget' .
// :fparams.
// :fparam name='pSubMem' type='PVOID' io='input' .
// Pointer to the memory pool.
// :fparam name='pszSource' type='PSZ' io='input' .
// String to be duplicated.
// :freturns.
// :fparam name='pszTarget' type='PSZ' io='return'.
// Duplicated string or 0 if failure.
// :efparams.
// :remarks.
// :epfunction.
//----------------------------------------------------------------------------
PSZ   _Optlink SubMemStrdup(PVOID pSubMem, PSZ pszSource)
{
   if (pszSource) {
      ULONG ul=0;
      PSZ pszDest=0;
      ul = strlen(pszSource);
      if ( !DosSubAllocMem( pSubMem, (PVOID)&pszDest, ul+1 ) ){
         strcpy(pszDest,pszSource);
         return pszDest;
      } // endif
   } // endif
   return NULL;
}


//----------------------------------------------------------------------------
// UCMenuAlloc
//----------------------------------------------------------------------------
// :function res=&IDF_UCMALLOC. name='UCMenuAlloc' text='Malloc used by the ucmenus'.
// External entry point to the allocation routine used by the ucmenus.
// :syntax name='UCMenuAlloc' params='size' return='PVOID' .
// :fparams.
// :fparam name='size' type='size_t' io='input' .
// Size to allocate.
// :freturns.
// :fparam name='pMem' type='PVOID' io='return'.
// Pointer to the allocated memory or 0 if failure.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------
PVOID APIENTRY UCMenuAlloc(size_t size)
{
   return MyMalloc( size );
}

//----------------------------------------------------------------------------
// UCMenuStrdup
//----------------------------------------------------------------------------
PSZ  APIENTRY UCMenuStrdup(const char *Src)
{
 
   return MyStrdup(Src);
}


//----------------------------------------------------------------------------
// UCMenuItemFree
//----------------------------------------------------------------------------
// Complement to UCMenuItemDup() function
//----------------------------------------------------------------------------
VOID APIENTRY UCMenuItemFree(UCMITEM *Source)
{
  if (Source != NULL) {
    /* Free strings */
    if (Source->pszBmp != NULL)
      MyFree(Source->pszBmp);
    if (Source->pszText != NULL)
      MyFree(Source->pszText);
    if (Source->pszAction != NULL)
      MyFree(Source->pszAction);
    if (Source->pszParameters != NULL)
      MyFree(Source->pszParameters);
    if (Source->pszData != NULL)
      MyFree(Source->pszData);

    /* Free structure */
    MyFree(Source);
  }
}

//----------------------------------------------------------------------------
// UCMenuItemDup
//----------------------------------------------------------------------------
UCMITEM * APIENTRY UCMenuItemDup(UCMITEM *Source)
{
UCMITEM *NewItem;
 
  NewItem=MyMalloc(sizeof(UCMITEM));
  if (NewItem != NULL) {
    memset(NewItem, 0x00, sizeof(UCMITEM));
    /* Dup strings */
    if (Source->pszBmp != NULL)
      NewItem->pszBmp = MyStrdup(Source->pszBmp);
    if (Source->pszText != NULL)
      NewItem->pszText = MyStrdup(Source->pszText);
    if (Source->pszAction != NULL)
      NewItem->pszAction = MyStrdup(Source->pszAction);
    if (Source->pszParameters != NULL)
      NewItem->pszParameters = MyStrdup(Source->pszParameters);
    if (Source->pszData != NULL)
      NewItem->pszData = MyStrdup(Source->pszData);

    /* Copy selected parts of the structure.  We do not */
    /* copy hBmp.                                       */
    NewItem->usId    = Source->usId;
    NewItem->ulFlags = Source->ulFlags;
  }

  return NewItem;
}

//----------------------------------------------------------------------------
// UCMenuFree
//----------------------------------------------------------------------------
// :function res=&IDF_UCMFREE. name='UCMenuFree' text='Free used by the ucmenus'.
// External entry point to the freeing routine used by the ucmenus.
// :syntax name='UCMenuFree' params='pMem' return='-' .
// :fparams.
// :fparam name='pMem' type='PVOID' io='input' .
// Pointer to free.
// :freturns.
// :fparam name='-' type='VOID' io='-'.
// Nothing.
// :efparams.
// :remarks.
// :related.
// :efunction.
//----------------------------------------------------------------------------

VOID  APIENTRY UCMenuFree(VOID * p)
{
   MyFree( p );
}



#ifdef UCMENUS_DEBUG

   #ifdef MYMALLOC_RIGHT_BOUNDARY

      #define MYPAGESIZE 4096lu

      VOID *   MyMalloc(size_t size)
      {
         // --------------------------------------------------------------
         // -- In case size+sizeof(ULONG) is on a page boundary, this code
         // -- will allocate one unnecessary supplemental page...
         // --------------------------------------------------------------

         PVOID p;
         ULONG ulSizeAllocated;

         ulSizeAllocated = (size+sizeof(ULONG)) - (size+sizeof(ULONG))%MYPAGESIZE + MYPAGESIZE;

         if (  DosAllocMem( &p, ulSizeAllocated, PAG_COMMIT | PAG_READ | PAG_WRITE) ) {
            return 0;
         }
         p =  ( PVOID ) ( ((PBYTE)p) + ulSizeAllocated  - size );
         *( ((PULONG)p)-1 ) = (ULONG)size;
         return p;
      }

      VOID  MyFree(VOID * p)
      {
         if (p) {
            ULONG ulSizeAllocated;
            ULONG ulSize = *( (PULONG)(p) -1 );

            ulSizeAllocated = (ulSize+sizeof(ULONG)) - (ulSize+sizeof(ULONG))%MYPAGESIZE + MYPAGESIZE;
            DosFreeMem( (PVOID) ( ((PBYTE)p) - ulSizeAllocated + ulSize ) );
         } // endif
      }
  #else
      VOID *   MyMalloc(size_t size)
      {
         PVOID p;

         if (DosAllocMem( &p, (ULONG) ( size ), PAG_COMMIT | PAG_READ | PAG_WRITE)) {
            return 0;
         }
         return p;
      }


      VOID  MyFree(VOID * p)
      {
         if (p) {DosFreeMem( (PVOID) ( p ));}
      }
  #endif // MY_MALLOC_RIGHT_BOUNDARY

   char * MyStrdup( const char * string)
   {
      if (string) {
         ULONG ul=0;
         char * stringDest = 0;
         ul = strlen(string);
         stringDest = MyMalloc(ul+1);
         if (stringDest) {
            strcpy(stringDest,string);
            return stringDest;
         } // endif
      } // endif
      return NULL;
   }
#else
   char * MyStrdup( const char * string)
   {
      if (string) {
         return strdup( string );
      } // endif
      return NULL;
   }

#endif // ifdef UCMENUS_DEBUG

//----------------------------------------------------------------------------
// nlsgetmessage
//----------------------------------------------------------------------------
// :pfunction res=&IDF_NLSGETMSG. name='nlsgetmessage' text='get a string from the string table'.
// Returns a string from the string table in a static buffer.
// :syntax name='nlsgetmessage' params='Hab, HModule, msg, buffnum' return='buffer' .
// :fparams.
// :fparam name='Hab' type='HAB' io='input' .
// Anchor block of the application.
// :fparam name='HModule' type='HMODULE' io='input' .
// Handle of the module where the string table is.
// :fparam name='msg' type='SHORT' io='input' .
// ID of the message to retrieve.
// :fparam name='buffnum' type='SHORT' io='input'.
//  Number of the buffer to use. (0-3)
// :freturns.
// :fparam name='buffer' type='PSZ' io='return'.
//  Pointer to the static buffer where the string is.
// :efparams.
// :remarks.
// Currently the indexes 0-2 are used for thread 1 and 3 for thread 2.
// :related.
// :epfunction.
//----------------------------------------------------------------------------
#define NLSSTRINGLEN   256
#define MAXNLSBUF 6
PSZ _Optlink nlsgetmessage(HAB Hab, HMODULE HModule, SHORT msg, SHORT buffnum )
{
   static UCHAR buffer[MAXNLSBUF][NLSSTRINGLEN];

   WinLoadString( Hab,
                  HModule,
                  msg,
                  NLSSTRINGLEN,
                  buffer[buffnum] );

   return buffer[buffnum];
}

/****************************************************************************/
LONG  _Optlink UCMString2Int(char *lpString, BOOL *lpTranslated)
/****************************************************************************/
/* Translate a string to binary value.  String may contain leading and      */
/* trailing blanks and optional minus sign.  An error occures if string     */
/* contains any non-numeric character other than leading/trailing blanks.   */
/* If an error occures, zero is returned and lpTranslated is set to FALSE   */
/* if supplied.  (If lpTranslated is a NULL pointer, zero is returned and   */
/* caller cannot know if an error occured).                                 */
/*                                                                          */
/****************************************************************************/
{
  char  *Buff = lpString;
  int    i    = 0;
  int    sign = 1;
  LONG   lReturn = 0L;

  /*-------------------------------------------------------------------------*/
  /*  check the buffer pointer                                               */
  /*-------------------------------------------------------------------------*/
  if (!lpString)                                
  {                                             
    if ( lpTranslated ) *lpTranslated = FALSE;  
    return 0L;
  }

  /*-------------------------------------------------------------------------*/
  /*  striping any extra spaces.                                             */
  /*-------------------------------------------------------------------------*/
  while ( Buff[i] == ' ' ) i++;
  if ( Buff[i] == '\0' )
  {
    if ( lpTranslated ) *lpTranslated = FALSE;
    return 0L;
  }

  /*-------------------------------------------------------------------------*/
  /*  check sign flag.                                                       */
  /*-------------------------------------------------------------------------*/
  if ( Buff[i] == '-' )
  {
    sign = -1;
    i++;
  }

  /*-------------------------------------------------------------------------*/
  /*  walk the number calculating as we go                                   */
  /*-------------------------------------------------------------------------*/
  while ( Buff[i]>='0' && Buff[i]<='9')
  {
    lReturn = (lReturn*10) + ((int)Buff[i] - (int)'0');
    i++;
  }
  while ( Buff[i] == ' ' ) i++;  // Ignore trailing blanks
  if ( Buff[i] != '\0' )         // Error if any more chars in string
  {
    if ( lpTranslated ) *lpTranslated = FALSE;
    return 0L;
  }

  /*-------------------------------------------------------------------------*/
  /*  return results                                                         */
  /*-------------------------------------------------------------------------*/

  if ( lpTranslated ) *lpTranslated = TRUE;
  return (sign * lReturn);
}

