/************************************************************************/
/* Program name: SAMP2.C                                                */
/*                                                                      */
/* OS/2 Developer Magazine, Issue:  Jan '95                             */
/* Author:  Mark McMillan, IBM Corp.                                    */
/*                                                                      */
/* Description: UCMenu sample #2                                        */
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

/*************************************************************************
   Notes for sample #2:

   Unlike sample #1, this is a full UCMenu toolbar implementation.  The
   'application' contains a standard PM text menu and two toolbars (one
   for commands, one for a color palette).  All WM_CONTROL messages
   from the toolbars are implemented, except for help-relate messages.
   All the toolbar states and styles are saved in an INI file when the
   applications is closed and reloaded when the application starts.

   This sample models a drawing program, but no real drawing code is
   implemented.  The purpose of this sample is just to show how the
   toolbars and menus work.  When a toolbar item is selected the command
   is just echoed into a MLE on the user interface.

   This program consists of just a single dialog -- there is no main
   window explictly created (see the main() function).  This is for
   simplicity of coding.  See sample #1 for details of using a toolbar
   on a standard window.

   This sample allows the user to drag menu items from one toolbar to
   another (e.g. from the palette menu to the command menu and from
   the command menu to the palette).  This may not make sense in a
   real application.  Allowing this has some implications for how
   to handle toggle checkable items.  The same menu item (e.g.
   action) can appear on one, both, or neither of the toolbar menus.
   It can also appear in multiple places on the same toolbar.  The
   code here will handle all these cases and keep the check state
   consistent and correct wherever the checkable items appear.

   This sample has only two toolbars instead of the four shown in
   sample #1.  This is to reduce the size of this sample, but
   conceptually this code can be easily extended for more toolbars.

   --Enjoy!

*************************************************************************/


#define  INCL_BASE
#define  INCL_WIN
#define  INCL_DOS
#define  INCL_WINSTDSPIN

#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 

#include "DIALOG.H"
#include "samp2.h"
#include "UCMenus.h"     /* UCMenu prototypes and definitions           */
#include "UCMUtils.h"    /* Utility function prototypes and definitions */

/* Global Data */
HAB      Hab;                   /* PM anchor block */

/* Structure to easily save/restore menu information in INI file */
typedef struct {
                 ULONG CmdStyle;      /* Command menu style bits */
                 ULONG CmdCx;         /* Forced size (x) */
                 ULONG CmdCy;         /* Forced size (y) */
                 ULONG CmdBgColor;    /* Toolbar background */
                 ULONG CmdItemBgColor;/* Item background */
                 char  CmdFont[32];   /* Font name */
                 ULONG CmdSize;       /* Size of menu template */
                 ULONG CmdBblDelay;   /* Bubble delay time */
                 ULONG CmdBblRead;    /* Bubble read  time */

                 ULONG ClrStyle;      /* Color menu style bits */
                 ULONG ClrCx;         /* Forced size (x) */
                 ULONG ClrCy;         /* Forced size (y) */
                 ULONG ClrBgColor;    /* Toolbar background */
                 ULONG ClrItemBgColor;/* Item background */
                 char  ClrFont[32];   /* Font name */
                 ULONG ClrSize;       /* Size of menu template */
                 ULONG ClrBblDelay;   /* Bubble read  time */
                 ULONG ClrBblRead;    /* Bubble read  time */
               } IniDataStruct;

/* Structure to describe each menu item supported by this application.  Some of */
/* the data here (e.g. action strings) are duplicated in the .RC file.  Only    */
/* selectable items are listed here (e.g. not submenu placeholders).            */

typedef struct {
                 USHORT CommandID;   /* Unique ID for each menu item */
                 BOOL   Checkable;   /* Is this item checkable */
                 USHORT CheckStatus; /* Zero (not checked) or MIA_CHECKED */
                 PSZ    Action;      /* Unique 'action' string */
                 PSZ    Desc;        /* Description for this item (used in status bar and customization dlgs) */
               } AppItemStruct;

/* Create static table of all supported menu items.  End of list indicated by ID=0.*/
/* We use this list to map action string to IDs when the user selects an action    */
/* on a UC menu.  It is also used to track the check status of checkable items (we */
/* cannot depend on the menu to keep track since the item can be deleted from the  */
/* menu by the user).                                                              */

AppItemStruct ItemList[] = {
   /* Item ID              Checkable?  CheckStatus  UCMenu Action String    Description                                 */
   /*--------------------  ----------  -----------  ----------------------  --------------------------------------------*/
   {ID_ACTION_NEW        ,   FALSE,       0,        "Cmd: New"             ,"Start new drawing and discard current file." },
   {ID_ACTION_OPEN       ,   FALSE,       0,        "Cmd: Open"            ,"Open existing drawing file."                 },
   {ID_ACTION_SAVE       ,   FALSE,       0,        "Cmd: Save"            ,"Save drawing to a file."                     },
   {ID_ACTION_CLOSE      ,   FALSE,       0,        "Cmd: Close"           ,"Exit application."                           },
   {ID_ACTION_COPY       ,   FALSE,       0,        "Cmd: Copy"            ,"Copy selected objects to clipboard."         },
   {ID_ACTION_CUT        ,   FALSE,       0,        "Cmd: Cut"             ,"Move selected objects to clipboard."         },
   {ID_ACTION_PASTE      ,   FALSE,       0,        "Cmd: Paste"           ,"Paste objects from clipboard."               },
   {ID_ACTION_UNDO       ,   FALSE,       0,        "Cmd: Undo"            ,"Undo last 'Paste' command."                  },
   {ID_ACTION_LINK       ,   FALSE,       0,        "Cmd: Link"            ,"Link object from another application."       },
   {ID_ACTION_SELECTALL  ,   FALSE,       0,        "Cmd: Select All"      ,"Select all objects in current drawing."      },
   {ID_ACTION_DESELECTALL,   FALSE,       0,        "Cmd: Deselect All"    ,"Unselect all selected objects."              },
   {ID_ACTION_ZOOMIN     ,   FALSE,       0,        "Cmd: Zoom In"         ,"Zoom in around current cursor position."     },
   {ID_ACTION_ZOOMOUT    ,   FALSE,       0,        "Cmd: Zoom Out"        ,"Zoom out from current cursor position."      },
   {ID_ACTION_STYLES     ,   FALSE,       0,        "Styles Submenu"       ,"Style Options (submenu)."                    },
   {ID_ACTION_BOLD       ,   TRUE,        0,        "Style: Bold"          ,"Make text bold."                             },
   {ID_ACTION_ITALIC     ,   TRUE,        0,        "Style: Italic"        ,"Make text italic."                           },
   {ID_ACTION_UNDERLINE  ,   TRUE,        0,        "Style: Underline"     ,"Make text underlined."                       },
   {ID_ACTION_TOOLSLCT   ,   FALSE,       0,        "Tool: Selection"      ,"Tool to select existing objects."            },
   {ID_ACTION_TOOLDRAW   ,   FALSE,       0,        "Tool: Draw"           ,"Freehand drawing tool."                      },
   {ID_ACTION_TOOLBRSH   ,   FALSE,       0,        "Tool: Brush"          ,"Freehand drawing with wide line."            },
   {ID_ACTION_TOOLERAS   ,   FALSE,       0,        "Tool: Eraser"         ,"Erase portions of objects, freehand."        },
   {ID_ACTION_TOOLSPRY   ,   FALSE,       0,        "Tool: Spraycan"       ,"Spray large areas of drawing, freehand."     },
   {ID_ACTION_TOOLFILL   ,   FALSE,       0,        "Tool: Fill"           ,"Fill an object with color or patterns."      },
   {ID_ACTION_TOOLLINE   ,   FALSE,       0,        "Tool: Line"           ,"Draw a straight lines."                      },
   {ID_ACTION_TOOLARC    ,   FALSE,       0,        "Tool: Arc"            ,"Draw arcs."                                  },
   {ID_ACTION_TOOLRECT   ,   FALSE,       0,        "Tool: Rectangle"      ,"Draw rectangles."                            },
   {ID_ACTION_TOOLCIRC   ,   FALSE,       0,        "Tool: Circle"         ,"Draw circles and ovals."                     },
   {ID_ACTION_TOOLTEXT   ,   FALSE,       0,        "Tool: Text"           ,"Place text on the drawing."                  },
   {ID_ACTION_TOOLLSEG   ,   FALSE,       0,        "Tool: Segmented Line" ,"Draw multiple straight-line segments."       },
   {ID_ACTION_TOOLCURV   ,   FALSE,       0,        "Tool: Curve"          ,"Draw arbitrary curves."                      },
   {ID_ACTION_TOOLSHP    ,   FALSE,       0,        "Tool: Shape"          ,"Draw closed shapes with straigt lines."      },
   {ID_ACTION_PALETTE    ,   FALSE,       0,        "Color Palette"        ,"Alter currently selected color."             },
   {ID_ACTION_BLACK      ,   TRUE,        0,        "Color: Black"         ,"Select this color for drawing and filling."  },
   {ID_ACTION_DGRAY      ,   TRUE,        0,        "Color: Dark gray"     ,"Select this color for drawing and filling."  },
   {ID_ACTION_PGRAY      ,   TRUE,        0,        "Color: Pale gray"     ,"Select this color for drawing and filling."  },
   {ID_ACTION_PPINK      ,   TRUE,        0,        "Color: Pale pink"     ,"Select this color for drawing and filling."  },
   {ID_ACTION_DBLUE      ,   TRUE,        0,        "Color: Dark blue"     ,"Select this color for drawing and filling."  },
   {ID_ACTION_BLUE       ,   TRUE,        0,        "Color: Blue"          ,"Select this color for drawing and filling."  },
   {ID_ACTION_MBLUE      ,   TRUE,        0,        "Color: Medium blue"   ,"Select this color for drawing and filling."  },
   {ID_ACTION_DCYAN      ,   TRUE,        0,        "Color: Dark cyan"     ,"Select this color for drawing and filling."  },
   {ID_ACTION_CYAN       ,   TRUE,        0,        "Color: Cyan"          ,"Select this color for drawing and filling."  },
   {ID_ACTION_DGREEN     ,   TRUE,        0,        "Color: Dark green"    ,"Select this color for drawing and filling."  },
   {ID_ACTION_MGREEN     ,   TRUE,        0,        "Color: Medium green"  ,"Select this color for drawing and filling."  },
   {ID_ACTION_GREEN      ,   TRUE,        0,        "Color: Green"         ,"Select this color for drawing and filling."  },
   {ID_ACTION_DRED       ,   TRUE,        0,        "Color: Dark red"      ,"Select this color for drawing and filling."  },
   {ID_ACTION_MRED       ,   TRUE,        0,        "Color: Medium red"    ,"Select this color for drawing and filling."  },
   {ID_ACTION_RED        ,   TRUE,        0,        "Color: Red"           ,"Select this color for drawing and filling."  },
   {ID_ACTION_ORANGE     ,   TRUE,        0,        "Color: Orange"        ,"Select this color for drawing and filling."  },
   {ID_ACTION_DPINK      ,   TRUE,        0,        "Color: Dark pink"     ,"Select this color for drawing and filling."  },
   {ID_ACTION_PINK       ,   TRUE,        0,        "Color: Pink"          ,"Select this color for drawing and filling."  },
   {ID_ACTION_BROWN      ,   TRUE,        0,        "Color: Brown"         ,"Select this color for drawing and filling."  },
   {ID_ACTION_YELLOW     ,   TRUE,        0,        "Color: Yellow"        ,"Select this color for drawing and filling."  },
   {ID_ACTION_WHITE      ,   TRUE,        0,        "Color: White"         ,"Select this color for drawing and filling."  },
   {ID_ACTION_FONTS      ,   FALSE,       0,        "Cmd: Fonts"           ,"Select font for text tool."                  },
   {ID_ACTION_GRID       ,   FALSE,       0,        "Cmd: Grid"            ,"Place grid over drawing area."               },
   {ID_ACTION_RULER      ,   FALSE,       0,        "Cmd: Ruler"           ,"Place ruler over drawing area."              },
   {ID_ACTION_MAG        ,   FALSE,       0,        "Cmd: Magnify"         ,"Magnify area immediatly around cursor."      },
   {ID_ACTION_DISKA      ,   FALSE,       0,        "Cmd: Disk A"          ,"Select disk A."                              },
   {ID_ACTION_DISKB      ,   FALSE,       0,        "Cmd: Disk B"          ,"Select disk B."                              },
   {ID_ACTION_DISKC      ,   FALSE,       0,        "Cmd: Disk C"          ,"Select disk C."                              },
   {ID_ACTION_DISKD      ,   FALSE,       0,        "Cmd: Disk D"          ,"Select disk D."                              },
   {ID_ACTION_HELP       ,   FALSE,       0,        "Cmd: Help"            ,"Show help."                                  },
   {ID_ACTION_VIEWCMD    ,    TRUE,   MIA_CHECKED,  "Show/Hide Command Bar","Toggle top command toolbar on/off."          },
   {ID_ACTION_VIEWCOLOR  ,    TRUE,   MIA_CHECKED,  "Show/Hide Color Bar"  ,"Toggle bottom color toolbar on/off."         },
   {0, FALSE, 0, "", ""}}; /* End of list */

CMITEMS CMItem = {ID_DEFAULTSTYLE, "Reset Style"}; /* Our own context menu item */

static HWND CommandBar, ColorBar;      /* UC menu window handles */
static HWND TextBar;                   /* Std PM text menu bar   */
static int  ColorIndex;                /* Index of curr color    */

SWCNTRL Tasklist = {NULLHANDLE, NULLHANDLE, NULLHANDLE, 0, 0,
                    SWL_VISIBLE, SWL_JUMPABLE, "UCMenus Sample"};

#define BASIC_STYLES   UCS_CHNGBMPBG_AUTO |    /* Alter bitmap bkgnd colors to match toolbar */\
                       UCS_PROMPTING |         /* Tell me about mouse moves on toolbar */      \
                       UCS_NODEFAULTACTION|    /* I will supply all action strings */          \
                       UCS_NO_CM_MENU_IMPORT | /* No 'import' option on context menu */        \
                       UCS_NO_CM_MENU_EXPORT | /* No 'export' option on context menu */        \
                       UCS_CUSTOMHLP           /* We will provide all help */

#define MSG_PROCESS_COMMAND (WM_USER+1)  /* Internally used message */
#define APP_NAME "UCMSamp"               /* App key in INI file */
#define INI_NAME "UCMSAMP.INI"           /* INI file name */

#define STRSAME(str1,str2) (!strcmpi(str1,str2))
/* Extract a UC menu data item from basic PM menu item structure */
#define UCMITEMDATA(UCitem, UCdata) (((UCMITEM *)(UCitem.hItem))->UCdata)

/* Prototypes */
MRESULT EXPENTRY MAINDLG_Proc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT ProcessUCMenuControlMsg(HWND hwnd, MPARAM mp1, MPARAM mp2);
int FindActionInItemList(PSZ Action);

/* General Dialog Helper Macros */
#define MSGBOX(Owner,Title,Msg)  WinMessageBox(HWND_DESKTOP,Owner,Msg,Title,0,MB_OK|MB_INFORMATION)
#define ERRBOX(Owner,Title,Msg)  WinMessageBox(HWND_DESKTOP,Owner,Msg,Title,0,MB_OK|MB_ERROR)
#define WARNBOX(Owner,Title,Msg) WinMessageBox(HWND_DESKTOP,Owner,Msg,Title,0,MB_OKCANCEL|MB_WARNING)
#define SETTEXT(ID,Buff)         WinSetWindowText(WinWindowFromID(hwnd,ID),Buff)

/*----------------------------------------------------------------------------*/
MRESULT EXPENTRY MAINDLG_Proc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
{
static  HPOINTER DlgIcon;   /* Dialog icon */

/* Dynamic dialog data */
UCMINFO UCMInit;            /* Graphic toolbar setup data */
HWND    DummyHwnd;          /* Dummy menu window (unused) */
SWP     MySize;             /* Size of this dialog        */
char    Msg[150];
int     i;

VOID   *CmdTemplate, *ClrTemplate;        /* UC menu templates for INI save/restore */
IniDataStruct IniData;                    /* Data to save/restore in INI file */
HINI   IniHandle;                         /* Handle of INI file */
ULONG  ULValue;                           /* Other INI ULONG values saved/restored */
BOOL   ProfileFound;                      /* Existing INI file */

  switch (msg) {

    case WM_INITDLG:
      /* Because our main window is a dialog, there are some things we */
      /* have to do manually: load the PM text menu bar, set an icon   */
      /* for the minimized state, and put ourselves in the task list.  */

      /* Load and position standard PM text menu bar */
      /* and grow dialog window to fit it in.        */
      WinQueryWindowPos(hwnd, &MySize);
      WinSetWindowPos(hwnd, HWND_TOP, 0,0,
                      MySize.cx, MySize.cy+WinQuerySysValue(HWND_DESKTOP,SV_CYMENU),
                      SWP_SIZE);
      TextBar = WinLoadMenu(hwnd, NULLHANDLE, ID_FRAME_RESOURCE);
      WinSendMsg(hwnd, WM_UPDATEFRAME, MPFROMLONG(FCF_MENU), 0L);

      /* Load icon and make it the default dialog icon */
      DlgIcon = WinLoadPointer (HWND_DESKTOP, NULLHANDLE, ID_FRAME_RESOURCE);
      WinDefDlgProc (hwnd, WM_SETICON, (MPARAM)DlgIcon, (MPARAM)0);

      /* Put myself in the task list */
      Tasklist.hwnd = hwnd;
      WinAddSwitchEntry(&Tasklist);

      /* If we have saved a previous UC menu configuration in the .INI  */
      /* file, restore its contents and style information.              */
      
      ProfileFound = FALSE;
      IniHandle = PrfOpenProfile(Hab, INI_NAME);
      if (IniHandle != NULLHANDLE) {
        /* If one value is here, they all should be */
        ULValue = sizeof(IniDataStruct);
        if (PrfQueryProfileData(IniHandle, APP_NAME, "IniData", &IniData, &ULValue)) {
          CmdTemplate = malloc(IniData.CmdSize);
          ClrTemplate = malloc(IniData.ClrSize);
          PrfQueryProfileData(IniHandle, APP_NAME, "CmdTemplate", CmdTemplate, &(IniData.CmdSize));
          PrfQueryProfileData(IniHandle, APP_NAME, "ClrTemplate", ClrTemplate, &(IniData.ClrSize));
          ProfileFound = TRUE;
        }
        PrfCloseProfile(IniHandle);
      }

      /* NOTE: To really do this well, the loading of the toolbar menus */
      /* should really be done with another thread to keep from tying   */
      /* up PM while all the bitmaps and resources are loaded.          */

      /* First, set all the basic values into the UCMINFO structure */
    
      memset(&UCMInit, 0x00, sizeof(UCMINFO));    /* Setup initialization data */
      UCMInit.cb = sizeof(UCMINFO);
      UCMInit.hModule = NULLHANDLE;         /* All resources are bound to EXE */
      UCMInit.BgBmp   = 0x00CCCCCC;         /* Light grey is bkgnd color in bitmaps */
      UCMInit.BgColor = 0x00B0B0B0;         /* Darker grey is toolbar background */
      UCMInit.ItemBgColor = WinQuerySysColor(HWND_DESKTOP,SYSCLR_MENU,0L); /* Items are menu color */
      UCMInit.BubbleDelay = 1000L;          /* 1 second hover delay */
      UCMInit.BubbleRead = 3000L;           /* 3 second read time */

      /* If we loaded a previously saved set of UC menus from the INI file, */
      /* use them to create the menus.  Otherwise, use the starter set of   */
      /* menus in the resource file which is bound to this .EXE.            */

      if (ProfileFound) { /*------- Create menus from existing templates --------*/
        /* Command menu */
        UCMInit.Style = IniData.CmdStyle;   /* Restore menu style */
        UCMInit.cx    = IniData.CmdCx;      /* Restore forced size (if any) */
        UCMInit.cy    = IniData.CmdCy;      /* Restore forced size (if any) */
        UCMInit.BgColor         = IniData.CmdBgColor;      /* Restore color */
        UCMInit.ItemBgColor     = IniData.CmdItemBgColor;  /* Restore color */ 
        UCMInit.pszFontNameSize = IniData.CmdFont;         /* Restore font  */
        UCMInit.BubbleDelay     = IniData.CmdBblDelay;
        UCMInit.BubbleRead      = IniData.CmdBblRead;
        CommandBar = UCMenuCreateFromTemplate(Hab,
                    hwnd,                   /* Dialog (frame) is parent */
                    hwnd,                   /* Dialog is also owner to get msgs */
                    CMS_HORZ,               /* Horizontal orientation */
                    0,0,0,0,                /* Size/position will be done by frame */
                    HWND_TOP,               /* Put on top of siblings */
                    ID_COMMANDBAR,          /* ID new menu will have */
                    CmdTemplate,            /* Ptr to incore template */
                    &UCMInit,               /* Initialization data structure */
                    &DummyHwnd);            /* Returned text menu handle (not used) */
        free(CmdTemplate);
        /* Color menu */
        UCMInit.Style = IniData.ClrStyle;   /* Restore menu style */
        UCMInit.cx    = IniData.ClrCx;      /* Restore forced size (if any) */
        UCMInit.cy    = IniData.ClrCy;      /* Restore forced size (if any) */
        UCMInit.BgColor         = IniData.ClrBgColor;      /* Restore color */
        UCMInit.ItemBgColor     = IniData.ClrItemBgColor;  /* Restore color */
        UCMInit.pszFontNameSize = IniData.ClrFont;         /* Restore font  */
        UCMInit.BubbleDelay     = IniData.ClrBblDelay;
        UCMInit.BubbleRead      = IniData.ClrBblRead;
        ColorBar = UCMenuCreateFromTemplate(Hab,
                    hwnd,                   /* Dialog (frame) is parent */
                    hwnd,                   /* Dialog is also owner to get msgs */
                    CMS_HORZ,               /* Horizontal orientation */
                    0,0,0,0,                /* Size/position will be done by frame */
                    HWND_TOP,               /* Put on top of siblings */
                    ID_COLORBAR,            /* ID new menu will have */
                    ClrTemplate,            /* Ptr to incore template */
                    &UCMInit,               /* Initialization data structure */
                    &DummyHwnd);            /* Returned text menu handle (not used) */
        free(ClrTemplate);
      }
      else { /*------- Create menus from resource file templates --------*/
        /* Command menu */
        UCMInit.Style   = UCS_FRAMED |        /* Use 3D effects */
                          BASIC_STYLES;       /* Plus my other basic styles */
        CommandBar = UCMenuCreateFromResource(Hab,
                      hwnd,                   /* Dialog (frame) is parent */
                      hwnd,                   /* Dialog is also owner to get msgs */
                      CMS_HORZ,               /* Horizontal orientation */
                      0,0,0,0,                /* Size/position will be done by frame */
                      HWND_TOP,               /* Put on top of siblings */
                      ID_COMMANDBAR,          /* ID new menu will have */
                      NULLHANDLE,             /* Resources come from EXE */
                      ID_COMMANDBAR,          /* ID of menu template in resource file */
                      &UCMInit,               /* Initialization data structure */
                      &DummyHwnd);            /* Returned text menu handle (not used) */
        /* Color menu */
        UCMInit.Style   = UCS_NOTEXT |        /* No text under bitmaps */
                          BASIC_STYLES;       /* Plus my other basic styles */
        UCMInit.ItemBgColor = 0x00B0B0B0;     /* Match face and background of color buttons */
        ColorBar   = UCMenuCreateFromResource(Hab,
                      hwnd,                   /* Dialog (frame) is parent */
                      hwnd,                   /* Dialog is also owner to get msgs */
                      CMS_HORZ,               /* Horizontal orientation */
                      0,0,0,0,                /* Size/position will be done by frame */
                      HWND_TOP,               /* Put on top of siblings */
                      ID_COLORBAR,            /* ID new menu will have */
                      NULLHANDLE,             /* Resources come from EXE */
                      ID_COLORBAR,            /* ID of menu template in resource file */
                      &UCMInit,               /* Initialization data structure */
                      &DummyHwnd);            /* Returned text menu handle (not used) */
      } /* if profile found */

      /* Add my own option to the UCMenu context menus.                  */
      WinSendMsg(CommandBar, UCMENU_ADDITEMSTOCM, MPFROMLONG(1L), MPFROMP(&CMItem));
      WinSendMsg(ColorBar  , UCMENU_ADDITEMSTOCM, MPFROMLONG(1L), MPFROMP(&CMItem));
    
      /* Now make them frame controls so we will not have to worry about */
      /* size or position of the menus as the window is sized.  The      */
      /* UCMUtils() will also take care of moving the dialog controls.   */

      UCMUtilsAddToFrame(hwnd, CommandBar, UCMUTILS_PLACE_TOP);
      UCMUtilsAddToFrame(hwnd, ColorBar,   UCMUTILS_PLACE_BOTTOM);

      WinSendMsg(TextBar, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_VIEWCMD, TRUE),   MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(TextBar, MM_SETITEMATTR, MPFROM2SHORT(ID_ACTION_VIEWCOLOR, TRUE), MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));

      /* Preselect default color by sending myself a WM_COMMAND */
      WinSendMsg(hwnd, WM_COMMAND, MPFROMSHORT(ID_ACTION_BLUE), MPFROM2SHORT(CMDSRC_MENU,FALSE));

      return (MRESULT)FALSE;  /* End of WM_INITDLG */

    case WM_SAVEAPPLICATION: {
      /* We need to save the current menu configurations in the  application */
      /* .INI file.  We need to save the current menu structure (e.g. the    */
      /* list of items, bitmaps, text, etc), and the current menu style      */
      /* such as text/notext, forced sizing, etc.  The menu structure can be */
      /* saved by creating an in-core template of the menu, and the style    */
      /* information is queried from the UC menu control.                    */

      /* A complete application should save more... such as the current      */
      /* window size/position/state, on/off status of toolbars, etc.         */

      /* Create incore template representations of the menus */
      CmdTemplate = UCMenuMakeTemplate(CommandBar, &(IniData.CmdSize));
      ClrTemplate = UCMenuMakeTemplate(ColorBar,   &(IniData.ClrSize));
      /* Open INI file and save templates */
      IniHandle = PrfOpenProfile(Hab, INI_NAME);
      if (IniHandle != NULLHANDLE) {
        PrfWriteProfileData(IniHandle, APP_NAME, "CmdTemplate", CmdTemplate, IniData.CmdSize);
        PrfWriteProfileData(IniHandle, APP_NAME, "ClrTemplate", ClrTemplate, IniData.ClrSize);
        /* We must also save the style bits, size, colors, fonts */

        WinSendMsg(CommandBar, UCMENU_QUERYUCMINFO, MPFROMP(&UCMInit), 0L);
        IniData.CmdStyle       = UCMInit.Style;
        IniData.CmdCx          = UCMInit.cx;
        IniData.CmdCy          = UCMInit.cy;
        IniData.CmdBgColor     = UCMInit.BgColor;
        IniData.CmdItemBgColor = UCMInit.ItemBgColor;
        IniData.CmdBblDelay    = UCMInit.BubbleDelay;
        IniData.CmdBblRead     = UCMInit.BubbleRead;
        if (UCMInit.pszFontNameSize != NULL)
          strcpy(IniData.CmdFont, UCMInit.pszFontNameSize);
          else (IniData.CmdFont)[0] = '\0';
        UCMUtilsFreeUCMInfoStrings(&UCMInit);

        WinSendMsg(ColorBar, UCMENU_QUERYUCMINFO, MPFROMP(&UCMInit), 0L);
        IniData.ClrStyle       = UCMInit.Style;
        IniData.ClrCx          = UCMInit.cx;
        IniData.ClrCy          = UCMInit.cy;
        IniData.ClrBgColor     = UCMInit.BgColor;
        IniData.ClrItemBgColor = UCMInit.ItemBgColor;
        IniData.ClrBblDelay    = UCMInit.BubbleDelay;
        IniData.ClrBblRead     = UCMInit.BubbleRead;
        if (UCMInit.pszFontNameSize != NULL)
          strcpy(IniData.ClrFont, UCMInit.pszFontNameSize);
          else (IniData.ClrFont)[0] = '\0';
        UCMUtilsFreeUCMInfoStrings(&UCMInit);

        PrfWriteProfileData(IniHandle, APP_NAME, "IniData", &IniData, sizeof(IniDataStruct));
        PrfCloseProfile(IniHandle);
      }
      UCMenuFree(CmdTemplate);
      UCMenuFree(ClrTemplate);
      break;
      }

    case WM_ACTIVATE:
      /* Tell toolbars we are getting/losing focus */
      WinSendMsg(CommandBar, UCMENU_ACTIVECHG, mp1, MPVOID);
      WinSendMsg(ColorBar,   UCMENU_ACTIVECHG, mp1, MPVOID);
      break;

    case WM_CONTROL:
      switch (SHORT1FROMMP(mp1)) {  /* ID of window sending msg */
        case ID_COMMANDBAR:
        case ID_COLORBAR:
          /* To help keep the source code neat, we put all the WM_CONTROL */
          /* processing for the UCMenus in a seperate routine.  There are */
          /* a number of notification codes we must respond to.           */
          return ProcessUCMenuControlMsg(hwnd, mp1, mp2);
      //case ID_XXX: ... any other dialog control WM_CONTROLs processed here...
      }
      break;


    case WM_NEXTMENU:
      /* When user arrows off the end of a menu, PM wants to know which menu */
      /* should the selection cursor move to.  The default dialog proc would */
      /* normally manage movement between the system menu and action bar,    */
      /* but if we want the UC menus to participate in the menu ring, we must*/
      /* handle this message.  PM hangs can also occure if we don't return   */
      /* some valid menu handle.                                             */

      /* Handling this message is complicated by the fact that we must       */
      /* return not the UCMenu window handle, but the underlaying real PM    */
      /* text menu that UCMenu uses internally.  This would normally expose  */
      /* the internals of the UCMenu control to the application... so the    */
      /* handling of this message is encapsulated in the UCMUtils() routines.*/

      /* We pass a variable length list of menu window IDs in the order we   */
      /* want them in the selection ring.  E.g. as the user arrows-right the */
      /* selection will move through this list of menus from left to right   */
      /* (with wraparound).  If any menu in the list is not visible it will  */
      /* be skipped and selection will to the next menu.  The list MUST be   */
      /* terminated with an ID of zero.                                      */

      /* Boy, this is a lot of comments for one line of code... :-)          */

      return UCMUtilsGetNextMenu(hwnd,                     /* Parent of all  */
        HWNDFROMMP(mp1),                                   /* Current menu   */
        SHORT1FROMMP(mp2),                                 /* Direction      */
        FID_SYSMENU, FID_MENU, ID_COMMANDBAR, ID_COLORBAR, /* Ordered list   */
        0);                                                /* List terminator*/

    case WM_COMMAND: 
      /* Process selects on the normal PM text menu */
      if (SHORT1FROMMP(mp2) == CMDSRC_MENU) {
        /* Lookup the command in the item list */
        for (i=0; ItemList[i].CommandID != 0; i++) {
          if (ItemList[i].CommandID == SHORT1FROMMP(mp1)) {
            /* Just send ourselves a message to process the command index */
            WinSendMsg(hwnd, MSG_PROCESS_COMMAND, MPFROMSHORT(i), 0L);
            break;
          }
        } /* for */
        return 0;
      } /* if a text menu */

      /* Process all WM_COMMAND msgs from dlg controls */
      switch (SHORT1FROMMP(mp1)) {
        case DID_OK:
          /* This occures when user presses EXIT button or CLOSE on the         */
          /* system menu.  Because our main window is a dialog, we must prevent */
          /* WinDismissDlg() from being called or focus is not returned to      */
          /* the correct window.  So instead we save our application state      */
          /* and destory our dialog window (which terminates the dialog         */
          /* without calling WinDismissDlg()).                                  */
          WinSendMsg(hwnd, WM_SAVEAPPLICATION, 0L, 0L);
          WinDestroyWindow(hwnd);
          return 0;
        case DID_CANCEL:
          /* This will occure if ESC key is pressed on dialog.  Since our */
          /* dialog is the main window, we will ignore it.                */
          return 0;
        case PB_HELP:
          MSGBOX(hwnd,"Not implemented yet.","");
          return 0;
      }
      break;  /* End of WM_COMMAND */

    case MSG_PROCESS_COMMAND: {
      USHORT CmdIndex;
      USHORT Attr;
      /* A menu command needs to be processed, either from a toolbar  */
      /* or the normal PM text menu.  The index of the command in the */
      /* ItemList[] array is in mp1.  This is where a lot of          */
      /* application specific code would go if this were a real       */
      /* drawing program.                                             */
      CmdIndex = SHORT1FROMMP(mp1);

      /* First, see if this command is a checkable type.  If so, we   */
      /* must toggle the check status and update all occurances of    */
      /* this item on all menus (text menus and UC menus).            */

      if (ItemList[CmdIndex].Checkable) {
        /* If this is a color action, we want a radio-button like     */
        /* behaviour where one and only one is checked at a time.     */
        if ((ItemList[CmdIndex].CommandID>=ID_ACTION_BLACK) && 
            (ItemList[CmdIndex].CommandID<=ID_ACTION_WHITE)) {
          ItemList[CmdIndex].CheckStatus = MIA_CHECKED;
          if (CmdIndex != ColorIndex) {  /* New color selected, uncheck old color */
            WinSendMsg(TextBar, MM_SETITEMATTR,
                       MPFROM2SHORT(ItemList[ColorIndex].CommandID, TRUE),
                       MPFROM2SHORT(MIA_CHECKED, ~MIA_CHECKED));
            UCMenuSetActionAttr(CommandBar, ItemList[ColorIndex].Action,
                                MIA_CHECKED, ~MIA_CHECKED);
            UCMenuSetActionAttr(ColorBar, ItemList[ColorIndex].Action,
                                MIA_CHECKED, ~MIA_CHECKED);
            ItemList[ColorIndex].CheckStatus = 0;
            ColorIndex = CmdIndex;  /* Save new color index */
            SETTEXT(COLOR, ItemList[ColorIndex].Action);
          }
        }
        else { /* For non-color checkable items, toggle check state */
          ItemList[CmdIndex].CheckStatus = ItemList[CmdIndex].CheckStatus ^ MIA_CHECKED;
        }
        /* Now update checkmarks on all menus */
        WinSendMsg(TextBar, MM_SETITEMATTR,
                   MPFROM2SHORT(ItemList[CmdIndex].CommandID, TRUE),
                   MPFROM2SHORT(MIA_CHECKED, ItemList[CmdIndex].CheckStatus));
        /* Update UC menus.  Use API call to update attributes of all */
        /* items in the menu that have this action on them (may be >1)*/
        UCMenuSetActionAttr(CommandBar, ItemList[CmdIndex].Action,
                            MIA_CHECKED, ItemList[CmdIndex].CheckStatus);
        UCMenuSetActionAttr(ColorBar, ItemList[CmdIndex].Action,
                            MIA_CHECKED, ItemList[CmdIndex].CheckStatus);
      } /* Item is checkable */

      /* Now process the selected command.  If this were a real drawing */
      /* program, we would insert code here to implement the various    */
      /* functions on the menus.  It might look something like:         */

      switch (ItemList[CmdIndex].CommandID) {
        case ID_ACTION_SAVE: /* Save drawing...*/
          break;
        case ID_ACTION_NEW:  /* Start new drawing...*/
          break;
        case ID_ACTION_OPEN: /* Open a drawing from disk file */
          break;
        case ID_ACTION_VIEWCMD: /* Toggle command menu on/off (check state already changed) */
          if (ItemList[CmdIndex].CheckStatus & MIA_CHECKED)
            UCMUtilsAddToFrame(hwnd, CommandBar, UCMUTILS_PLACE_TOP);
            else UCMUtilsRemoveFromFrame(hwnd, CommandBar);
          break;
        case ID_ACTION_VIEWCOLOR: /* Toggle color menu on/off (check state already changed) */ 
          if (ItemList[CmdIndex].CheckStatus & MIA_CHECKED)
            UCMUtilsAddToFrame(hwnd, ColorBar, UCMUTILS_PLACE_BOTTOM);
            else UCMUtilsRemoveFromFrame(hwnd, ColorBar);
          break;
        /* ...etc  <<<=== More application-specific cases here...*/
      }

      /* To save code in this example, we just write the command to the */
      /* MLE on the dialog.                                             */

      sprintf(Msg,"Item Selected: '%s'\n", ItemList[CmdIndex].Action);
      WinSendMsg(WinWindowFromID(hwnd,CMDLIST), MLM_INSERT, MPFROMP(Msg), 0L);
      return 0;
      } /* end of MSG_PROCESS_COMMAND */

    case WM_PAINT: {
      SWP Pos, DlgPos;
      HPS Hps;
      RECTL Rect;

      /* First let dialog do normal painting */
      WinDefDlgProc(hwnd, msg, mp1, mp2);

      /* Paint recessed frame around the status line */
      Hps = WinGetPS(hwnd);
      WinQueryWindowPos(WinWindowFromID(hwnd, DYNINFO), &Pos);
      WinQueryWindowPos(hwnd, &DlgPos);
      Rect.xLeft = WinQuerySysValue(HWND_DESKTOP, SV_CXDLGFRAME);
      Rect.xRight= DlgPos.cx - Rect.xLeft;
      Rect.yBottom = Pos.y - 1;
      Rect.yTop    = Pos.y + Pos.cy + 1;
      #define DB_RAISED    0x0400  // Undocumented borders
      #define DB_DEPRESSED 0x0800
      WinDrawBorder(Hps, &Rect, 1, 1, 0, 0, DB_DEPRESSED);
      WinReleasePS(Hps);
      return 0;
      }


    case WM_ADJUSTWINDOWPOS:
      /* This message occures when the dialog is about to be minimized,     */
      /* maximized, restored, etc.  When a dialog is minimized, any         */
      /* dialog controls in the lower left corner will overlay the icon.    */
      /* So when we minimize we hide these controls, otherwise we make them */
      /* visible.  Note that UCMenu controls do this themselves so we don't */
      /* have to worry about them.                                          */

      if (((PSWP)mp1)->fl & SWP_MINIMIZE)
        WinShowWindow(WinWindowFromID(hwnd, DID_OK), FALSE);
      else if (((PSWP)mp1)->fl & SWP_RESTORE)
        WinShowWindow(WinWindowFromID(hwnd, DID_OK), TRUE);

      break;  /* Let PM handle the message normally */


  } /* End of (msg) switch */
                                                                                                  
  return WinDefDlgProc(hwnd, msg, mp1, mp2);
                                                                                                  
} /* End dialog procedure */

/*----------------------------------------------------------------------------*/
MRESULT ProcessUCMenuControlMsg(HWND hwnd, MPARAM mp1, MPARAM mp2)
/*----------------------------------------------------------------------------*/
/* This routine processes all WM_CONTROL messages from all UCMenu toolbar     */
/* controls.  The return value will be the message result.                    */
/*----------------------------------------------------------------------------*/
{
USHORT   MenuID;        /* Window ID of UCMenu           */
UCMITEM  *UCItem;       /* Ptr to UCMenu item data       */
MENUITEM ItemData;      /* Std PM menu item data         */
int      CmdIndex;      /* Index into ActionList[] array */
char     Msg[100];      /* Message formatting buffer     */
int      i;

  MenuID = SHORT1FROMMP(mp1);  /* ID of UCMenu sending this message */

  switch (SHORT2FROMMP(mp1)) { /* Process each notification code */

  case UCN_ITEMSELECTED: /* User made a selection on a toolbar */

    UCItem = (UCMITEM *)mp2;
    if (UCItem->pszAction != NULL) { /* Make sure there is an action string */

      /* See if we recognize this action.  If so, send ourselves */
      /* a message to process the command index.                 */

      CmdIndex = FindActionInItemList(UCItem->pszAction);
      if (CmdIndex >= 0) 
        WinSendMsg(hwnd, MSG_PROCESS_COMMAND, MPFROMSHORT(CmdIndex), 0L);
    }
    return 0;

  case UCN_CMITEM: {
    /* One of the items we added to the UCMenu context menu was selected. */
    ULONG MenuColor, ItemColor;

    switch (SHORT1FROMMP(mp2)) {  /* What item was selected on context menu? */
      case ID_DEFAULTSTYLE:
        /* Reset style flags to default values */
        if (MenuID == ID_COMMANDBAR)
          WinSendMsg(CommandBar, UCMENU_SETSTYLE,
           MPFROMLONG(UCS_FRAMED|BASIC_STYLES),
           MPFROM2SHORT(0,0));
        else
          WinSendMsg(ColorBar, UCMENU_SETSTYLE,
           MPFROMLONG(UCS_NOTEXT|BASIC_STYLES),
           MPFROM2SHORT(0,0));
        /* Reset colors and fonts */
        MenuColor = 0x00B0B0B0;         /* Darker grey is toolbar background */
        ItemColor = WinQuerySysColor(HWND_DESKTOP,SYSCLR_MENU,0L); /* Items are menu color */
        WinSendMsg(WinWindowFromID(hwnd, MenuID), UCMENU_SETBGCOLOR,
                   MPFROMLONG(MenuColor), MPFROMLONG(ItemColor));
        WinSendMsg(WinWindowFromID(hwnd, MenuID), UCMENU_SETFONT,
                   MPFROMP("8.Helv"), 0L);
        WinSendMsg(WinWindowFromID(hwnd, MenuID), UCMENU_SETBUBBLETIMERS,
                   MPFROMLONG(1000L), MPFROMLONG(3000L));
        /* Tell UCMenu to update with new styles */
        WinSendMsg(WinWindowFromID(hwnd, MenuID), UCMENU_UPDATE, 0L, 0L);
        break;
    } /* switch on item ID */
    return 0;
    }

  case UCN_QRYDEFTEMPLATEID:
    /* User has asked to reload the default menu for one of the toolbars. */
    /* Tell the UC menu control the resource ID of the menu template,     */
    /* which is the same as the UCMenu window ID set during UCMenu create.*/
    *(USHORT *)mp2 = MenuID;
    return (MRESULT)TRUE;

  case UCN_QRYTEMPLATEMODULE:
    /* Menu needs to know module handle from which to load resources. */
    *(HMODULE *)mp2 = NULLHANDLE;      /* Resources are bound to EXE. */
    return (MRESULT)TRUE;

  case UCN_QRYACTIONLIST:
    /* User is customizing a menu item and we need to supply a list of all */
    /* the valid actions the user can put on the item.  We do this by      */
    /* sending the control UCMENU_INSERTACTION messages and then a         */
    /* UCMENU_ACTIONLIST when we are done.                                 */
    for (i=0; ItemList[i].CommandID != 0; i++)
      WinSendMsg(HWNDFROMMP(mp2), UCMENU_INSERTACTION,
                 MPFROMP(ItemList[i].Action),
                 MPFROMP(ItemList[i].Desc));
    /* Tell control we are done */
    WinSendMsg(HWNDFROMMP(mp2), UCMENU_ACTIONSINSERTED, 0L, 0L);
    return 0;

  case UCN_QRYRESBMP: {
    ULONG **BmpList, ResSize, ResID;
    /* The user is customizing a menu item and has asked for a list of all  */
    /* the built-in bitmaps.  We must supply an array of resource IDs, each */
    /* of which is a BITMAP resource in the .RC file.  To make this easy,   */
    /* we have choosen to make all the bitmap resource IDs sequentially     */
    /* numbered so we can generate the array algorithmicly.  If a specific  */
    /* ID in the sequence does not exist, we don't put it into the array.   */
    BmpList = PVOIDFROMMP(mp2);
    *BmpList = UCMenuAlloc(sizeof(ULONG) * (MAX_BMPID-MIN_BMPID+1));
    i = 0;
    for (ResID=MIN_BMPID; ResID<=MAX_BMPID; ResID++ ) {
      if (DosQueryResourceSize(NULLHANDLE, RT_BITMAP, ResID, &ResSize) == 0) {
        (*BmpList)[i] = ResID;
        i++;
      }
    } /* endfor */
    return MRFROMSHORT(i);      /* Tell how many valid entries in the array */
    }

  case UCN_HLP_NB_BMP:
  case UCN_HLP_NB_CREATE:
  case UCN_HLP_NB_ACTION:
  case UCN_HLP_STYLE:
  case UCN_HLP_DM:
    /* User has requested help on a customization dialog.  We only get this */
    /* message if we have the UCS_CUSTOMHLP style on the UCMenu.            */
    MSGBOX(hwnd, "Sorry...","Help not implemented yet.");
    return 0;

  case UCN_QRYBUBBLEHELP:{
     /* Toolbar needs to know what bubble help text to display. */
     /* We keep bubble help in the pszData field of the UCMITEM */
     /* structure, passed to us via mp2.  Note we must return   */
     /* a COPY which UCMenus will free when it is done with it. */
     QBUBBLEDATA *BubbleInfo;
     int        Index;

     BubbleInfo = (QBUBBLEDATA *)mp2;

     if (UCMFIELD(BubbleInfo->MenuItem, pszAction) != NULL) {
       Index = FindActionInItemList(UCMFIELD(BubbleInfo->MenuItem, pszAction));
       if (Index >= 0)
         BubbleInfo->BubbleText = UCMenuStrdup(ItemList[Index].Desc);
     }
     return 0;
     }

  case UCN_MOUSEMOVE: {
    /* The mouse has moved on a toolbar.  As of V2.1 of UCMenus we get only */
    /* one message when the mouse enters an item and one when it leaves the */
    /* toolbar (there is a small delay before we get the notice that the    */
    /* mouse pointer has left the toolbar).  Note that we only get          */
    /* this message if we have the UCS_PROMPTING style on the UCMenu.       */
    /* When the mouse moves over a toolbar, we will update status text with */
    /* description of item under the pointer.                               */
    POINTL MousePt;
    USHORT MouseItem;
    int    MouseIndex;

    MouseItem = SHORT1FROMMP(mp2);
    if (MouseItem == 0)       /* Mouse moved off menu or not on an item */
      SETTEXT(DYNINFO, "");   /* Blank the dynamic info line */
    else {

      /* Lookup help text in our command table.                                 */
      /* Query the item to get the MENUITEM -> UCMENU item data.  Note we could */
      /* use some macros from the UCMenu toolkit header to simplify access to   */
      /* the UCMITEM fields, but for this sample we will show the explicit      */
      /* means used to access the data structures.                              */

      if (WinSendMsg(WinWindowFromID(hwnd, MenuID), MM_QUERYITEM,
                    MPFROM2SHORT(MouseItem, TRUE), MPFROMP(&ItemData))) {
        if (((UCMITEM *)(ItemData.hItem))!= NULLHANDLE) { /* Make sure there is a UCMITEM structure */
          if (((UCMITEM *)(ItemData.hItem))->pszAction  != NULL) { /* Make sure there is an action string */
            /* See if we recognize this action */
            MouseIndex = FindActionInItemList(((UCMITEM *)(ItemData.hItem))->pszAction);
            if (MouseIndex >= 0)
              SETTEXT(DYNINFO, ItemList[MouseIndex].Desc); /* Update status line */
            else
              SETTEXT(DYNINFO, "??? Unknown toolbar item ???");
          }
        }
      }
    } // search lookup table

    return 0;
    }

  case UCN_ADDEDITEM:    /* A new item was added to a UCMenu */
  case UCN_ACTION:       /* Action of an existing item was changed */
      /* If an item is added or it's Action is modified, we must check it:        */
      /*  - Is the 'Action' valid?  UC menus allows the user to type in arbitrary */
      /*    action strings.                                                       */
      /*  - Is the selected action a checkable item?  If so, we must set the      */
      /*    check state to our current state for that action.                     */

      if (!WinSendMsg(WinWindowFromID(hwnd, MenuID), MM_QUERYITEM,
                      MPFROM2SHORT(SHORT1FROMMP(mp2), TRUE), MPFROMP(&ItemData)))
        return 0;
      if (((UCMITEM *)(ItemData.hItem))== NULLHANDLE)  /* Make sure there is a UCMITEM structure */
        return 0;
      if (((UCMITEM *)(ItemData.hItem))->pszAction  == NULL) /* Make sure there is an action string */
        return 0;

      /* Locate the action in our list of valid application actions */
      i = FindActionInItemList(((UCMITEM *)(ItemData.hItem))->pszAction);

      if (i>=0) {
        /* If this action is supposed to be checkable, set current check state */
        /* else clear any check mark currently on it.                          */
        if (ItemList[i].Checkable)
          WinSendMsg(WinWindowFromID(hwnd, MenuID), MM_SETITEMATTR,
                     MPFROM2SHORT(SHORT1FROMMP(mp2), TRUE),
                     MPFROM2SHORT(MIA_CHECKED,ItemList[i].CheckStatus));
          else WinSendMsg(WinWindowFromID(hwnd, MenuID), MM_SETITEMATTR,
                     MPFROM2SHORT(SHORT1FROMMP(mp2), TRUE),
                     MPFROM2SHORT(MIA_CHECKED,~MIA_CHECKED));
      } /* if found in list */
      else {
        /* Action specified by user for this menu item is not supported. */
        /* We could notify the user and delete the menu item, or not even*/
        /* tell the user until the item is selected.  For this sample we */
        /* choose to give the user a warning and continue.               */
        sprintf(Msg, "The toolbar item has been assigned an unrecognized action '%s'.\n\n"\
                     "This item will be ignored when selected.",
                     ((UCMITEM *)(ItemData.hItem))->pszAction);
        ERRBOX(hwnd, "Toolbar Update Warning:", Msg);
      }
      return 0;
 
  } /* switch on notification code */

  return 0;  /* Did not process notifcation */

}

/*----------------------------------------------------------------------------*/
int FindActionInItemList(PSZ Action)
/*----------------------------------------------------------------------------*/
/* Look through the list of all the 'actions' this application supports and   */
/* return the index into the ItemList array of the matching entry.  If the    */
/* specified action is not supported, return -1.                              */
/*----------------------------------------------------------------------------*/
{
int i;
  if (Action == NULL)  /* Check for nonexistant action string */
    return -1;

  for (i=0; ItemList[i].CommandID != 0; i++) {
    if (STRSAME(ItemList[i].Action, Action)) /* We found the action in the list */
      return i;
  } /* for each item in list */

  return -1;  /* Did not find the action in the list */
}
/*----------------------------------------------------------------------------*/
int main(int argc,char **argv, char **envp)
/*----------------------------------------------------------------------------*/
/*  Main routine just runs a dialog box (no main window).                     */
/*----------------------------------------------------------------------------*/
{                                                                                                 
HMQ MyQ;

  /* Initialize PM window environment, get a message queue. */
  /* NOTE: We need an extra large queue for UC menus.       */

  Hab = WinInitialize(0L);
  MyQ = WinCreateMsgQueue(Hab, 50);

  WinDlgBox(HWND_DESKTOP, HWND_DESKTOP, (PFNWP)
            MAINDLG_Proc,
            NULLHANDLE,
            MAINDLG,
            NULL);

  /* Cleanup when dialog terminates */

  WinDestroyMsgQueue(MyQ);
  WinTerminate(Hab);
  return 0;
}
