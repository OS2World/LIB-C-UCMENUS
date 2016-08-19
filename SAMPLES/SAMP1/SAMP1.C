/************************************************************************/
/* Program name: SAMP1.C                                                */
/*                                                                      */
/* OS/2 Developer Magazine, Issue:  Jan '95                             */
/* Author:  Mark McMillan, IBM Corp.                                    */
/*                                                                      */
/* Description: UCMenu sample #1                                        */
/*                                                                      */
/* Program Requirements:  OS/2 2.x                                      */
/*                        IBM C Set/2 (or other OS/2 compiler)          */
/*                        OS/2 Toolkit                                  */
/*                                                                      */
/* Copyright (c)International Business Machines Corp. 1994              */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/************************************************************************/
/*                      DISCLAIMER OF WARRANTIES.                       */
/************************************************************************/
/************************************************************************/
/*     The following [enclosed] code is source code created by the      */
/*     author(s).  This source code is provided to you solely           */
/*     for the purpose of assisting you in the development of your      */
/*     applications.  The code is provided "AS IS", without             */
/*     warranty of any kind.  The author(s) shall not be liable         */
/*     for any damages arising out of your use of the source code,      */
/*     even if they have been advised of the possibility of such        */
/*     damages.  It is provided purely for instructional and            */
/*     illustrative purposes.                                           */
/************************************************************************/
/************************************************************************/
 
/*----------------------------------------------------------------------------
Notes for sample #1:

This sample shows the visual appearence of several UC menus in a standard
frame with all the frame controls used (e.g. menu bar, vertical and
horizontal scroll bars, etc).  There is no functionality in this sample, its
only purpose is to show how UC menus can be made into frame controls on any
edge of a standard frame window.  It also shows how UC menus are created from
resource file templates and given various attributes and styles.  This is not
a full UC menus implementation -- not all the WM_CONTROL messages from the
menu are processed (and thus some fields of the menu customization dialogs
will be blank).  See sample #2 for a full implementation.
----------------------------------------------------------------------------*/

#define  INCL_BASE
#define  INCL_WIN
#define  INCL_GPI
#define  INCL_DOS
#define  INCL_WINSTDSPIN
#define  INCL_GPIBITMAPS

#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "samp1.h"
#include "UCMenus.h"
#include "UCMUtils.h"

#define APP_CLASS "UCMSamp"
#define APP_TITLE "UC Menus Sample #1"
#define ERRBOX(Owner,Title,Msg) WinMessageBox(HWND_DESKTOP,Owner,Msg,Title,0,MB_OK|MB_ERROR)
#define MSGBOX(Owner,Title,Msg) WinMessageBox(HWND_DESKTOP,Owner,Msg,Title,0,MB_OK|MB_INFORMATION) /*! <Main> <Defines> 6 */

/* Global data */
HWND CommandBar, ToolBar, ColorBar, DiskBar;   /* UC menu window handles */
HWND FrameHwnd,  ClientHwnd;          /* Application window handles */
HWND ActionMenu;                      /* Std PM text menu handle    */
HAB  Hab;                             /* Application PM anchor block */
HMQ  Hmq;                             /* Application msg queue handle */

/* Prototypes */
MRESULT EXPENTRY ClientWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );

/******************************************************************************/
int main(int argc,char **argv, char **envp)
/******************************************************************************/
/* The main routine just does basic PM initialization and creates a standard  */
/* frame window.  All the work is done in the client window procedure below.  */
/******************************************************************************/
{
QMSG    Qmsg;           /* PM Q message for dispatching */
ULONG   FrameStyles;    /* Main frame window style flags */

   /* Initialize PM and get message queue */
   /* NOTE! Need extra large queue when using UC menu controls */

   Hab = WinInitialize(0L);
   Hmq = WinCreateMsgQueue(Hab, 50);

   MSGBOX(HWND_DESKTOP,"UC Menus Sample #1 (Standard PM Window) - Notes:",
    "This sample is only intended to show the visual effects of various "
    "menu style and placement options.  It is not fully functional (in "
    "particular, some fields of the menu customization dialogs will appear "
    "blank, checkable items are not toggled, and changes to the menus "
    "are not saved).\n\nItems can be drag/dropped to rearrange menus or to move/copy "
    "items between menus.\n\nDisk menu (on right edge) is UCS_STATIC "
    "style and cannot be modified."
    "\n\nSee Sample #2 for a complete menu implementation.");

   /* Create main application window */
   WinRegisterClass(Hab, APP_CLASS, (PFNWP)ClientWindowProc, CS_SIZEREDRAW, sizeof(PVOID));
   FrameStyles = FCF_TITLEBAR | FCF_SYSMENU | FCF_MENU | FCF_MINMAX | 
                 FCF_VERTSCROLL | FCF_HORZSCROLL | FCF_SIZEBORDER |
                 FCF_ICON | FCF_AUTOICON | FCF_TASKLIST;
   FrameHwnd = WinCreateStdWindow(HWND_DESKTOP, 0L, &FrameStyles,
                 APP_CLASS, APP_TITLE, 0L, NULLHANDLE, ID_FRAME_RESOURCE, &ClientHwnd);

   /* Get and dispatch messages until application terminates */

   while (WinGetMsg(Hab, &Qmsg, NULLHANDLE, 0L, 0L ))
      WinDispatchMsg(Hab, &Qmsg);
 
   /* Cleanup */
   WinDestroyWindow(FrameHwnd);
   WinDestroyMsgQueue(Hmq);
   WinTerminate(Hab);
   return 0;
}

/******************************************************************************/
MRESULT EXPENTRY ClientWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
/******************************************************************************/
/* This is the client window procedure.  During creation it will create the   */
/* UC menus and place them as frame controls.  The client window will be      */
/* filled with a bitmap, just for interest.                                   */
/******************************************************************************/
{
static HPS     HpsBitmap;
static HBITMAP Bitmap;

UCMINFO UCMInit;        /* UC menu initialization data */
HWND    DummyHwnd;      /* Text menu handle (unused) */
RECTL   Rect;           /* Rectangle for placement calculations */
BITMAPINFOHEADER2 BitmapInfo;  /* Header info for bitmap */

  switch (msg) {

    case WM_CREATE:
      /* Need these even before WinCreatStdWindow() completes */
      ClientHwnd = hwnd;
      FrameHwnd  = WinQueryWindow(hwnd, QW_PARENT);
      ActionMenu = WinWindowFromID(FrameHwnd, FID_MENU);

      /* NOTE: To really do this well, the loading of the toolbar menus */
      /* should really be done with another thread to keep from tying   */
      /* up PM while all the bitmaps and such are loaded.               */

      /* Create graphic toolbars for edges of frame */
    
      memset(&UCMInit, 0x00, sizeof(UCMINFO));    /* Setup initialization data */
      UCMInit.cb = sizeof(UCMINFO);
      UCMInit.hModule = NULLHANDLE;         /* All resources are bound to EXE */
      UCMInit.BgBmp   = 0x00CCCCCC;         /* Light grey is bkgnd color in bitmaps */
      UCMInit.BgColor = 0x00B0B0B0;         /* Darker grey is toolbar background */
      UCMInit.ItemBgColor = WinQuerySysColor(HWND_DESKTOP,SYSCLR_MENU,0L); /* Items are menu color */
      UCMInit.BubbleDelay = 0L;             /* Instant bubble help */
      UCMInit.BubbleRead = 3500L;           /* 3.5 seconds to autodismiss bubble help */
    
      UCMInit.Style   = UCS_FRAMED |        /* Use 3D effects */
                        UCS_CHNGBMPBG_AUTO |/* Auto-detect bitmap background color */
                        UCS_NODEFAULTACTION|/* Don't put 'exec pgm' on list of actions */
                        UCS_CUSTOMHLP |     /* We will provide all help */
                        UCS_BUBBLEHELP;     /* Enable bubble help */
      CommandBar = UCMenuCreateFromResource(Hab,
                    FrameHwnd,              /* Frame is parent of its controls */
                    ClientHwnd,             /* Client will get messages */
                    CMS_HORZ | WS_VISIBLE,  /* Horizontal orientation */
                    0,0,0,0,                /* Size/position will be done by frame */
                    HWND_TOP,               /* Put on top of siblings */
                    ID_COMMANDBAR,          /* ID new menu will have */
                    NULLHANDLE,             /* Resources come from EXE */
                    ID_COMMANDBAR,          /* ID of menu template in resource file */
                    &UCMInit,               /* Initialization data structure */
                    &DummyHwnd);            /* Returned text menu handle (not used) */
    
      UCMInit.Style   = UCS_NOTEXT |        /* No text under bitmaps */
                        UCS_CHNGBMPBG_AUTO |/* Auto-detect bitmap background color */
                        UCS_CUSTOMHLP ;     /* We will provide all help */
      UCMInit.ItemBgColor = 0x00B0B0B0;     /* Blend color dots into background */
      ColorBar   = UCMenuCreateFromResource(Hab,
                    FrameHwnd,              /* Frame is parent of its controls */
                    ClientHwnd,             /* Client will get messages */
                    CMS_HORZ,               /* Horizontal orientation */
                    0,0,0,0,                /* Size/position will be done by frame */
                    HWND_TOP,               /* Put on top of siblings */
                    ID_COLORBAR,            /* ID new menu will have */
                    NULLHANDLE,             /* Resources come from EXE */
                    ID_COLORBAR,            /* ID of menu template in resource file */
                    &UCMInit,               /* Initialization data structure */
                    &DummyHwnd);            /* Returned text menu handle (not used) */

      UCMInit.ItemBgColor = WinQuerySysColor(HWND_DESKTOP,SYSCLR_MENU,0L); /* Items are menu color */
      UCMInit.Style   = UCS_FRAMED |        /* No text under bitmaps */
                        UCS_CHNGBMPBG_AUTO |/* Auto-detect bitmap background color */
                        UCS_STATIC |        /* Allow no customizing of the menu */
                        UCS_CUSTOMHLP ;     /* We will provide all help */
      DiskBar    = UCMenuCreateFromResource(Hab,
                    FrameHwnd,              /* Frame is parent of its controls */
                    ClientHwnd,             /* Client will get messages */
                    CMS_VERT,               /* Vertical orientation */
                    0,0,0,0,                /* Size/position will be done by frame */
                    HWND_TOP,               /* Put on top of siblings */
                    ID_DISKBAR,             /* ID new menu will have */
                    NULLHANDLE,             /* Resources come from EXE */
                    ID_DISKBAR,             /* ID of menu template in resource file */
                    &UCMInit,               /* Initialization data structure */
                    &DummyHwnd);            /* Returned text menu handle (not used) */
    
      UCMInit.Style   = UCS_FRAMED |        /* Use 3D effects */
                        UCS_NOTEXT |        /* No text under bitmaps */
                        UCS_CHNGBMPBG_AUTO |/* Auto-detect bitmap background color */
                        UCS_NODEFAULTACTION|/* Don't put 'exec pgm' on list of actions */
                        UCS_CUSTOMHLP ;     /* We will provide all help */
      UCMInit.NbOfCols=2;
      UCMInit.NbOfRows=30; /* max */
      ToolBar    = UCMenuCreateFromResource(Hab,
                    FrameHwnd,              /* Frame is parent of its controls */
                    ClientHwnd,             /* Client will get messages */
                    CMS_MATRIX_VERT,        /* Vertical matrix menu */
                    0,0,0,0,                /* Size/position will be done by frame */
                    HWND_TOP,               /* Put on top of siblings */
                    ID_TOOLBAR,             /* ID new menu will have */
                    NULLHANDLE,             /* Resources come from EXE */
                    ID_TOOLBAR,             /* ID of menu template in resource file */
                    &UCMInit,               /* Initialization data structure */
                    &DummyHwnd);            /* Returned text menu handle (not used) */
    
      /* Now make them frame controls so we will not have to worry about */
      /* size or position of the menus as the window is sized.           */
    
      UCMUtilsAddToFrame(FrameHwnd, CommandBar, UCMUTILS_PLACE_TOP);
      UCMUtilsAddToFrame(FrameHwnd, ToolBar,    UCMUTILS_PLACE_LEFT);
      UCMUtilsAddToFrame(FrameHwnd, ColorBar,   UCMUTILS_PLACE_BOTTOM);
      UCMUtilsAddToFrame(FrameHwnd, DiskBar,    UCMUTILS_PLACE_RIGHT);

      /* Update View-> submenu to indicate all toolbars are showing */
      WinSendMsg(ActionMenu, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_VIEWCMD, TRUE),   MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(ActionMenu, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_VIEWTOOL, TRUE),  MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(ActionMenu, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_VIEWCOLOR, TRUE), MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(ActionMenu, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_VIEWDISK, TRUE),  MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));

      /* Hardwire checkstate of some menu items, just for show */
      WinSendMsg(ActionMenu, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_ITALIC, TRUE),  MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(ActionMenu, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_CYAN,   TRUE),  MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      UCMenuSetActionAttr(CommandBar, "Style: Italic", MIA_CHECKED, MIA_CHECKED);
      UCMenuSetActionAttr(ColorBar,   "Color: Cyan",   MIA_CHECKED, MIA_CHECKED);

      /* Load bitmap for later display in the client area */
      HpsBitmap = WinGetPS(hwnd);
      Bitmap = GpiLoadBitmap(HpsBitmap, NULLHANDLE, ID_GALORE_BITMAP, 0L, 0L);

      /* Size frame such that client is natural size of bitmap */
      BitmapInfo.cbFix = sizeof(BITMAPINFOHEADER2);
      GpiQueryBitmapInfoHeader(Bitmap, &BitmapInfo);
      Rect.yBottom = 0;
      Rect.xLeft   = 0;
      Rect.yTop    = BitmapInfo.cy;
      Rect.xRight  = BitmapInfo.cx;
      WinSendMsg(FrameHwnd, WM_CALCFRAMERECT, MPFROMP(&Rect), MPFROMSHORT(FALSE));
      Rect.xRight  = Rect.xRight - Rect.xLeft;    /* Calculate CX */
      Rect.yTop    = Rect.yTop   - Rect.yBottom;  /* Calculate CY */
      Rect.xLeft = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN)/2 - Rect.xRight/2;
      Rect.yBottom=WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN)/2 - Rect.yTop/2;

      WinSetWindowPos(FrameHwnd, HWND_TOP, 
                      Rect.xLeft, Rect.yBottom,
                      Rect.xRight,Rect.yTop,
                      SWP_ACTIVATE | SWP_SHOW | SWP_ZORDER | SWP_SIZE | SWP_MOVE);
      return (MRESULT) FALSE;

    case WM_ACTIVATE:
      /* Tell toolbars we are getting/losing focus */
      WinSendMsg(CommandBar, UCMENU_ACTIVECHG, mp1, MPVOID);
      WinSendMsg(ColorBar,   UCMENU_ACTIVECHG, mp1, MPVOID);
      WinSendMsg(ToolBar,    UCMENU_ACTIVECHG, mp1, MPVOID);
      WinSendMsg(DiskBar,    UCMENU_ACTIVECHG, mp1, MPVOID);
      break;

    case WM_CONTROL:
      switch (SHORT1FROMMP(mp1)) {   /* ID of windows sending msg */
        case ID_TOOLBAR:
        case ID_DISKBAR:
        case ID_COMMANDBAR:
        case ID_COLORBAR:            /* Any of the UC menus */
          switch (SHORT2FROMMP(mp1)) {
            case UCN_QRYBUBBLEHELP:{ /* CommandBar needs bubble help text */
               /* Toolbar needs to know what bubble help text to display. */
               /* We keep bubble help in the pszData field of the UCMITEM */
               /* structure, passed to us via mp2.  Note we must return   */
               /* a COPY which UCMenus will free when it is done with it. */
               QBUBBLEDATA *BubbleInfo;
               BubbleInfo = (QBUBBLEDATA *)mp2;

               if (UCMFIELD(BubbleInfo->MenuItem, pszData) != NULL)
                 BubbleInfo->BubbleText = UCMenuStrdup(UCMFIELD(BubbleInfo->MenuItem, pszData));
               return 0;
               }
 
            case UCN_QRYDEFTEMPLATEID:
              /* User wants to reload default menu config.  Tell UC menus */
              /* what menu resource to load and replace current menu.     */
              /* This is the ID we originally loaded, which is the same   */
              /* as the ID of the UC menu window itself.                  */
              *(USHORT *)mp2 = SHORT1FROMMP(mp1);
              return (MRESULT)TRUE;
            case UCN_QRYTEMPLATEMODULE:
              /* Need to tell UCMenu where to module to load resources    */
              /* from.  Return NULLHANDLE for EXE-bound resources.        */
              *(HMODULE *)mp2 = NULLHANDLE;
              return (MRESULT)TRUE;
           }
      }
      break;

    case WM_COMMAND: {
      /* Process messages from normal PM text bar */
      USHORT Attr, MenuPlace;
      HWND   MenuHwnd;
      /* Toggle visibility of the four tool menus */
      switch (SHORT1FROMMP(mp1)){
        case ID_ACTION_VIEWCMD:
        case ID_ACTION_VIEWTOOL:
        case ID_ACTION_VIEWCOLOR:
        case ID_ACTION_VIEWDISK:
          Attr = (SHORT)WinSendMsg(ActionMenu, MM_QUERYITEMATTR,
                            MPFROM2SHORT(SHORT1FROMMP(mp1),TRUE),
                            MPFROMSHORT(MIA_CHECKED));
          Attr = Attr ^ MIA_CHECKED;
          WinSendMsg(ActionMenu, MM_SETITEMATTR,
                            MPFROM2SHORT(SHORT1FROMMP(mp1),TRUE),
                            MPFROM2SHORT(MIA_CHECKED, Attr));
          switch (SHORT1FROMMP(mp1)){
            case ID_ACTION_VIEWCMD:
              MenuHwnd = CommandBar;
              MenuPlace= UCMUTILS_PLACE_TOP;
              break;
            case ID_ACTION_VIEWTOOL:
              MenuHwnd = ToolBar;
              MenuPlace= UCMUTILS_PLACE_LEFT;
              break;
            case ID_ACTION_VIEWCOLOR:
              MenuHwnd = ColorBar;
              MenuPlace= UCMUTILS_PLACE_BOTTOM;
              break;
            case ID_ACTION_VIEWDISK:
              MenuHwnd = DiskBar;
              MenuPlace= UCMUTILS_PLACE_RIGHT;
              break;
          }
          if (Attr & MIA_CHECKED)  /* Add or remove menu from frame */
            UCMUtilsAddToFrame(FrameHwnd, MenuHwnd, MenuPlace);
            else UCMUtilsRemoveFromFrame(FrameHwnd, MenuHwnd);
      }
      }
      return 0;

    case WM_DESTROY:
      /* Release resources */
      GpiDeleteBitmap(Bitmap);
      WinReleasePS(HpsBitmap);
      break;

    case WM_PAINT: {
        /* Draw bitmap previously loaded into whole client window.  Note  */
        /* that since the menu bars are frame controls, we do not have to */
        /* account for them in the size of the client window (e.g. they   */
        /* are outside the client window).                                */
        SWP swp;
        RECTL rc;
        HPS Hps;

        Hps = WinBeginPaint(hwnd, NULLHANDLE, (PRECTL)NULL);
        /* Get size of client window and draw bitmap into it */
        WinQueryWindowPos(hwnd, &swp);
        rc.xLeft   = 0;
        rc.yBottom = 0;
        rc.xRight  = swp.cx;
        rc.yTop    = swp.cy;
        WinDrawBitmap(Hps, Bitmap, NULL, (POINTL *)&rc, 0L, 0L,
                      DBM_STRETCH | DBM_IMAGEATTRS);
        WinEndPaint(Hps);
      }
      return 0;
#if defined(ALTERNATE_PAINT)
    case WM_PAINT: {
        /* Draw box around edge and X through center of  window.    Note  */
        /* that since the menu bars are frame controls, we do not have to */
        /* account for them in the size of the client window (e.g. they   */
        /* are outside the client window).                                */
        HPS hPS;
        POINTL Point;
        SWP    ClientPos;

        hPS = WinBeginPaint(hwnd, (HPS)NULL, (PRECTL)0);
        GpiErase( hPS );
        GpiSetColor(hPS, CLR_GREEN);
        Point.x = 0;
        Point.y = 0;
        GpiSetCurrentPosition(hPS, &Point);
        WinQueryWindowPos(hwnd, &ClientPos);
        Point.x = max(1, ClientPos.cx-2);
        Point.y = max(1, ClientPos.cy-2);
        GpiBox(hPS, DRO_OUTLINE, &Point, 0L, 0L);
        GpiLine(hPS, &Point);
        Point.x = 0;             /* Point to upper-left corner */
        GpiSetCurrentPosition(hPS, &Point);
        Point.y = 0;
        Point.x = ClientPos.cx;  /* Lower right */
        GpiLine(hPS, &Point);

        WinEndPaint( hPS );
      }
      return 0;
#endif /* ALTERNATE_PAINT */
 
  } /* msg switch */
  return  WinDefWindowProc(hwnd, msg, mp1, mp2 );
}
 
