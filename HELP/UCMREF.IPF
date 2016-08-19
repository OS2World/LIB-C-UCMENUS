.***************************************************************************
.* UCMenus toolkit online reference.
.*
.* NOTE: The IPFC pre-processor utility (IPFCPREP) is required to
.* process this document.
.***************************************************************************
.***************************************************************************
.***************************************************************************
.*                        DISCLAIMER OF WARRANTIES.                        *
.***************************************************************************
.***************************************************************************
.*                                                                         *
.*  Copyright (C) 1995 IBM Corporation                                     *
.*                                                                         *
.*      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        *
.*      sample code created by IBM Corporation. This sample code is not    *
.*      part of any standard or IBM product and is provided to you solely  *
.*      for  the purpose of assisting you in the development of your       *
.*      applications.  The code is provided "AS IS", without               *
.*      warranty of any kind.  IBM shall not be liable for any damages     *
.*      arising out of your use of the sample code, even if they have been *
.*      advised of the possibility of such damages.                        *
.***************************************************************************
:userdoc.
.********* Useful IPFC macros *********
.dm UCMINFO on
:link reftype=hd res=101.UCMINFO:elink.
.dm off
.dm UCMITEM on
:link reftype=hd res=102.UCMITEM:elink.
.dm off
.dm CMITEMS on
:link reftype=hd res=103.CMITEMS:elink.
.dm off
.dm WM_CONTROL on
:link reftype=hd res=500.WM_CONTROL:elink.
.dm off
.dm QBUBBLEDATA on
:link reftype=hd res=104.QBUBBLEDATA:elink.
.dm off

.dm UCMenuItemFree on
:link reftype=hd res=236.UCMenuItemFree:elink.
.dm off
.dm UCMenuItemDup on
:link reftype=hd res=235.UCMenuItemDup:elink.
.dm off
.dm UCMenuFree on 
:link reftype=hd res=234.UCMenuFree:elink.
.dm off
.dm UCMenuStrdup on
:link reftype=hd res=233.UCMenuStrdup:elink.
.dm off
.dm UCMenuAlloc on
:link reftype=hd res=232.UCMenuAlloc:elink.
.dm off
.dm UCMenuGetVersion on
:link reftype=hd res=231.UCMenuGetVersion:elink.
.dm off
.dm UCMenuTemplateBuffetDlg on
:link reftype=hd res=230.UCMenuTemplateBuffetDlg:elink.
.dm off
.dm UCMenuResourceBuffetDlg on
:link reftype=hd res=219.UCMenuResourceBuffetDlg:elink.
.dm off
.dm UCMenuNew on
:link reftype=hd res=218.UCMenuNew:elink.
.dm off
.dm UCMenuLoadDefault on
:link reftype=hd res=217.UCMenuLoadDefault:elink.
.dm off
.dm UCMenuSetActionAttr on
:link reftype=hd res=216.UCMenuSetActionAttr:elink.
.dm off
.dm UCMenuGetActionID on
:link reftype=hd res=215.UCMenuGetActionID:elink.
.dm off
.dm UCMenuIdFromCoord on
:link reftype=hd res=214.UCMenuIdFromCoord:elink.
.dm off
.dm UCMenuFreeMenuData on
:link reftype=hd res=213.UCMenuFreeMenuData:elink.
.dm off
.dm UCMenuLoadStyleIni on
:link reftype=hd res=212.UCMenuLoadStyleIni:elink.
.dm off
.dm UCMenuSaveStyleIni on
:link reftype=hd res=211.UCMenuSaveStyleIni:elink.
.dm off
.dm UCMenuLoadStyle on
:link reftype=hd res=210.UCMenuLoadStyle:elink.
.dm off
.dm UCMenuSaveStyle on
:link reftype=hd res=209.UCMenuSaveStyle:elink.
.dm off
.dm UCMenuLoadTemplateIni on
:link reftype=hd res=208.UCMenuLoadTemplateIni:elink.
.dm off
.dm UCMenuSaveTemplateIni on
:link reftype=hd res=207.UCMenuSaveTemplateIni:elink.
.dm off
.dm UCMenuLoadTemplate on
:link reftype=hd res=206.UCMenuLoadTemplate:elink.
.dm off
.dm UCMenuSaveTemplate on
:link reftype=hd res=205.UCMenuSaveTemplate:elink.
.dm off
.dm UCMenuMakeTemplate on
:link reftype=hd res=204.UCMenuMakeTemplate:elink.
.dm off
.dm UCMenuLoadBitmap on
:link reftype=hd res=203.UCMenuLoadBitmap:elink.
.dm off
.dm UCMenuCreateFromTemplate on
:link reftype=hd res=202.UCMenuCreateFromTemplate:elink.
.dm off
.dm UCMenuCreateFromHMenu on
:link reftype=hd res=201.UCMenuCreateFromHMenu:elink.
.dm off
.dm UCMenuCreateFromResource on
:link reftype=hd res=200.UCMenuCreateFromResource:elink.
.dm off


.dm UCMENU_INSERTACTION on
:link reftype=hd res=664.UCMENU_INSERTACTION:elink.
.dm off
.dm UCMENU_ACTIONSINSERTED on
:link reftype=hd res=663.UCMENU_ACTIONSINSERTED:elink.
.dm off
.dm UCMENU_SETFONT on
:link reftype=hd res=662.UCMENU_SETFONT:elink.
.dm off
.dm UCMENU_SETBGCOLOR on
:link reftype=hd res=661.UCMENU_SETBGCOLOR:elink.
.dm off
.dm UCMENU_UPDATE on
:link reftype=hd res=660.UCMENU_UPDATE:elink.
.dm off
.dm UCMENU_QUERYUCMINFO on
:link reftype=hd res=659.UCMENU_QUERYUCMINFO:elink.
.dm off
.dm UCMENU_SETSTYLE on
:link reftype=hd res=658.UCMENU_SETSTYLE:elink.
.dm off
.dm UCMENU_QUERYVERSION on
:link reftype=hd res=657.UCMENU_QUERYVERSION:elink.
.dm off
.dm UCMENU_DELETECMITEM on
:link reftype=hd res=656.UCMENU_DELETECMITEM:elink.
.dm off
.dm UCMENU_ADDITEMSTOCM on
:link reftype=hd res=655.UCMENU_ADDITEMSTOCM:elink.
.dm off
.dm UCMENU_QUERYFORCEDSIZE on
:link reftype=hd res=654.UCMENU_QUERYFORCEDSIZE:elink.
.dm off
.dm UCMENU_QUERYSTYLE on
:link reftype=hd res=653.UCMENU_QUERYSTYLE:elink.
.dm off
.dm UCMENU_QUERYFONT on
:link reftype=hd res=652.UCMENU_QUERYFONT:elink.
.dm off
.dm UCMENU_QUERYCOLOR on
:link reftype=hd res=651.UCMENU_QUERYCOLOR:elink.
.dm off
.dm UCMENU_QUERYSIZE on
:link reftype=hd res=650.UCMENU_QUERYSIZE:elink.
.dm off
.dm UCMENU_SETBUBBLETIMERS on
:link reftype=hd res=665.UCMENU_SETBUBBLETIMERS:elink.
.dm off
.dm UCMENU_ACTIVECHG on
:link reftype=hd res=666.UCMENU_ACTIVECHG:elink.
.dm off
.dm UCMENU_DISABLEUPDATE on
:link reftype=hd res=667.UCMENU_DISABLEUPDATE:elink.
.dm off



.dm UCN_HLP_BUFFET on
:link reftype=hd res=622.UCN_HLP_BUFFET:elink.
.dm off
.dm UCN_HLP_DM on
:link reftype=hd res=621.UCN_HLP_DM:elink.
.dm off
.dm UCN_HLP_STYLE on
:link reftype=hd res=620.UCN_HLP_STYLE:elink.
.dm off
.dm UCN_HLP_NB_ACTION on
:link reftype=hd res=619.UCN_HLP_NB_ACTION:elink.
.dm off
.dm UCN_HLP_NB_CREATE on
:link reftype=hd res=618.UCN_HLP_NB_CREATE:elink.
.dm off
.dm UCN_HLP_NB_BMP on
:link reftype=hd res=617.UCN_HLP_NB_BMP:elink.
.dm off
.dm UCN_MOUSEMOVE on
:link reftype=hd res=616.UCN_MOUSEMOVE:elink.
.dm off
.dm UCN_CMITEM on
:link reftype=hd res=615.UCN_CMITEM:elink.
.dm off
.dm UCN_ACTION on
:link reftype=hd res=614.UCN_ACTION:elink.
.dm off
.dm UCN_QRYRESBMP on
:link reftype=hd res=613.UCN_QRYRESBMP:elink.
.dm off
.dm UCN_TEXT on
:link reftype=hd res=612.UCN_TEXT:elink.
.dm off
.dm UCN_BITMAP on
:link reftype=hd res=611.UCN_BITMAP:elink.
.dm off
.dm UCN_DELETEDITEM on
:link reftype=hd res=610.UCN_DELETEDITEM:elink.
.dm off
.dm UCN_ADDEDITEM on
:link reftype=hd res=609.UCN_ADDEDITEM:elink.
.dm off
.dm UCN_COLOR on
:link reftype=hd res=608.UCN_COLOR:elink.
.dm off
.dm UCN_FONT on
:link reftype=hd res=607.UCN_FONT:elink.
.dm off
.dm UCN_STYLE on
:link reftype=hd res=606.UCN_STYLE:elink.
.dm off
.dm UCN_SIZE on
:link reftype=hd res=605.UCN_SIZE:elink.
.dm off
.dm UCN_QRYACTIONLIST on
:link reftype=hd res=604.UCN_QRYACTIONLIST:elink.
.dm off
.dm UCN_QRYDEFTEMPLATE on
:link reftype=hd res=603.UCN_QRYDEFTEMPLATE:elink.
.dm off
.dm UCN_QRYDEFTEMPLATEID on
:link reftype=hd res=602.UCN_QRYDEFTEMPLATEID:elink.
.dm off
.dm UCN_QRYTEMPLATEMODULE on
:link reftype=hd res=601.UCN_QRYTEMPLATEMODULE:elink.
.dm off
.dm UCN_ITEMSELECTED on
:link reftype=hd res=600.UCN_ITEMSELECTED:elink.
.dm off
.dm UCN_CHANGEDITEM on
:link reftype=hd res=625.UCN_CHANGEDITEM:elink.
.dm off
.dm UCN_QRYBUBBLEHELP on
:link reftype=hd res=623.UCN_QRYBUBBLEHELP:elink.
.dm off
.dm UCN_QRYCONTEXTHWND on
:link reftype=hd res=624.UCN_QRYCONTEXTHWND:elink.
.dm off
.dm makeall on
:link reftype=hd res=9000.Building Executable Files:elink.
.dm off
.***************************************
:title.User Customizable Menus
.***************************************
.imd ucmlocal.h
:h1. Introduction
This document is the programmer's reference for the User Customizable Menu
(UCMenu) PM control.  For more information on programming with this
control, see :hp1.OS/2 Developer Magazine:ehp1., Jan/Feb 1995, page 50.
:artwork align=center name='ALLUCM.BMP'.
:p.
:hp7.Acknowledgments:ehp7.
.br
This control was originally conceived at the IBM Yorktown Research
laboratory by Gennaro Cuomo and Juerg VonKaenel for use in EPM (the
OS/2 enhanced system editor) with
subsequent development
contributions from Guillaume Le Stum, John Ponzo, Alan Warren and Alex
Bertrand.  Mark McMillan of IBM Research Triangle Park developed the
sample code, frame control utility functions, and initiated
improvements in the architecture.
:p.
:hp7.Description:ehp7.
.br
The :hp3.User Customizable Menu:ehp3. is a very powerful, new user interface
component, designed to overcome the problems with current menu and toolbar
designs.
It allows the user to define the ordering of menu items and
visual representation (artwork and text) of menu items. New items, like
"macro assignments" can be added dynamically. A user customizable menu can
be saved in its present state for later use.
The UCMenu changes itself into a
"scrolling" mode when the number of selectable items exceeds the
allotted window size.
:p.
Aside from the good graphical presentation, the most significant
features of this control are the easy :hp1.user customization:ehp1. methods it
provides (thus its name, UCMenus).  Customizing a UCMenu is made easy
for the user by extensive use of direct manipulation techniques.  For
example, to delete an item from the toolbar the user can drag the item
to the system shredder.  Reordering the items is as easy as dragging
the item to a new position and dropping it.  Many direct manipulation
functions are provided by the control.
:p.
There are two basic customization methods for which UCMenus
provides direct support:
:ol.
:li.:hp1.Free Form Customization&colon.:ehp1.  Using this method,
the user can alter any aspect of any menu item, including the
bitmap (graphical presentation), the application function
associated with the item, etc.  An OS/2 notebook control provides
easy customization of all aspects of the menu items.  This is
the default method if not overridden by the application.
:li.:hp1.Buffet Style Customization&colon.:ehp1.  Using this
method, the application provides a fixed set ("buffet") of
supported menu items.  The user can only select from the
buffet and cannot modify the application functions associated
with the menu items.  They cannot specify alternate or
custom bitmaps for the graphical presentation.  This is the
easiest form of customization method for novice users or for
applications with a fixed set of toolbar items.
:eol.
:p.
All customization is encapsulated in the UCMenu control itself.  The
control and the application cooperate via messages to provide
application specific information during customization.  Using the
built-in customization methods the user can:
:ul.
:li.Modify styles related to visual effects.
:li.Add and delete items and submenu items.
:li.Replace bitmaps with .BMP files or application supplied bitmaps.
:li.Edit the text under the bitmap.
:li.Associate application functions with menu items (the
application supplying the list of valid functions).
:li.Move/copy menu items within a menu or between menus.
:li.Restore the entire menu to an application-defined default state.
:eul.
:p.
The application can restrict what customization functions are allowed
through the use of style flags.
:h1.Programming Concepts
:p.
There are several key concepts which need to be understood to make
effective use of UCMenu controls in an application program.  As its
name implies, the basic paradigm of a UCMenu control is that of a
normal PM text menu; the control contains selectable items, submenus,
separators, item attributes, etc.  (The current implementation is
limited to a single level of submenus.)  The
developers view of this control is also similar to that of a PM menu
control.  This similarity is by design and allows anyone familiar with
PM menus to grasp the terminology, concepts, and messages involved
with UCMenu controls.  It is important to recognize that there are
some key differences, many of which we will cover in this article.
:p.
The UCMenu control uses many of the same menu-related messages and
data structures as its PM menu counterpart.
For example, a MM_QUERYITEM message can
be sent to the UCMenu window to obtain a MENUITEM structure which
describes a particular item in the menu.  The application will
receive all the standard PM menu notification messages except
WM_DRAWITEM and WM_MEASUREITEM which are used internally by the
UCMenu, and WM_COMMAND which is replaced with a :WM_CONTROL. message.
:p.
Because of its added visual and interactive complexity, the standard
PM menu structures and messages are not sufficient to implement a
customizable graphical menu bar.  Thus, UCMenus add another layer of
messages and data structures on top of the PM menu architecture.  It
is important to understand the new concepts that UCMenus brings to
the existing menu architecture and how the PM menu architecture has
been extended to accommodate them.  The following sections
describe some of these extensions.
.*******************************************************************************
:h2.UCMenu Action Strings
One of the most important new concepts that UCMenus brings to a menu is
that of :hp1.actions:ehp1..  An :hp1.action:ehp1. is a textual description of the
function assigned to a particular menu item.  It is an arbitrary string
defined by the application and seen by the user when customizing a
UCMenu.
For example, a text editor might define action strings like:
:xmp.
  "Copy to Clipboard"
  "Paste from Clipboard"
  "Left Justify"
  "Select Fonts"
  ...etc...
:exmp.
When a user creates a new UCMenu item or modifies an existing item,
they will select from a list of actions supplied by the application.
:p.
For a UCMenu control, the menu item IDs are arbitrary and can change during
execution of the program.  An application cannot know ahead of time
what the item IDs are going to be for any particular menu item.
When a user adds a new menu item
to an existing UCMenu toolbar the UCMenu control supplies all the
user interface necessary for the user to choose a bitmap, text, and an
application-specific action for the new item.  When the new item is
added to the menu, the UCMenu control will choose an arbitrary item ID
which is unique throughout the menu and all submenus.  Likewise, items
can be moved and copied between UCMenu toolbars.  The resulting (new)
menu items are assigned arbitrary IDs that do not conflict with any
existing items.
:p.
Therefore, an application cannot depend on using
item IDs to determine what function was selected on a UCMenu toobar.
Instead, the application must use the :hp1.action string:ehp1. associated with the menu
item to determine what function has been selected.  A UCMenu control
will send a :WM_CONTROL. message with a notification code of
:UCN_ITEMSELECTED. when an item is selected.  The application will not
receive a WM_COMMAND message from a UCMenu control.
:p.
The application must associate the action string of the selected menu
item with an application function.  The toolkit sample program
(SAMP1.C) uses a table which maps action strings to fixed ID values.
The action of the selected item is looked up in the table and then a
simple switch can be used to select the correct application function.
The ID values chosen for the table purposefully match the fixed
item IDs used in the applications standard PM menu bar (the application
has both UCMenu toolbars and a standard PM menu bar).  Thus, the same
switch can be used to process WM_COMMAND messages from the PM menu and
:WM_CONTROL. messages from the UCMenus.  This reduces code size and keeps
application specific function from being duplicated.
.******************************************************************************
:h2.Data Structures
:p.
There are two primary data structures related to UCMenu controls.
Associated with each UCMenu window is a set of data which describes
various aspects of the overall toolbar appearance and behavior.  This
includes information such as style flags, menu colors and text font.
This is the :UCMINFO. structure.
It is filled in by
the application and used during creation of a UCMenu control.
:p.
Associated with each item of the menu are two linked data structures.
The first is the
standard PM MENUITEM structure.  That structure contains an 'item
handle' which is generally reserved for application use.  A UCMenu
uses the item handle to point to a :UCMITEM. structure which provides
UCMenu specific item information.  In effect, the MENUITEM structure
is extended for UCMenu specific data. It should be noted that
any of the string pointers in the :UCMITEM. structure can be null.
:p.
These data structures are used extensively in the processing of
messages to and from the UCMenu control.
:p.
.************************************************************************
:h2.Checkable Menu Items
The fact that a UCMenu can be extensively customized by the user has
some important implications for applications with 'checkable' style
menu items.  Like a PM menu, any item in a UCMenu can be checked
simply by setting the MIA_CHECKED attribute for that item.  A menu
item should be checkable if the action associated with it represents
the toggling of some application state. A checked menu item is
indicated in a UCMenu by drawing a thick border around it.
:p.
When a UCMenu item is created by the user the MIA_CHECKED attribute is
not set.  Thus, if the action selected by the user for the new item is
a toggle function, the application should update the current state of
the item with the current state of the application.
:p.
Likewise, when a menu item is modified and assigned a new action, the
current attributes are not changed.  If the new action is a toggle
function, the item attribute must be updated to reflect the current
application state.  If the action is not a toggle function, the
MIA_CHECKED attribute should be cleared since the previous action may
have been checked.
:p.
The UCMenu control will send a :WM_CONTROL. message with a notification
code of :UCN_ADDEDITEM. or :UCN_ACTION. when a new item is added or an
action is changed.  When these messages are received, the application
must examine the new action and set or clear the MIA_CHECKED
attribute.
:p.
When the application is notified of a selection on a checkable UCMenu
item, the application must toggle the check state.  In a standard PM
menu it is sufficient to toggle the state of just the menu item
selected.  Since a UCMenu may have the same (toggle) action on
different items in the same menu, the check state of :hp1.all:ehp1. items with
the toggle action must be updated.
This function has been
incorporated into the UCMenu API set with the function
:UCMenuSetActionAttr..  This API will set the attributes of all
items in the UCMenu with the specified action string.  If the
application has multiple UCMenu toolbars, all must be updated since the
action may exist in any of them.
:p.
:h2.Customization Messages
Easy customization of the toolbar is one of the most useful and
powerful features of this control.  It gives the user complete
flexibility to add and delete menu items, rearrange the order, create
submenus, and move and copy items between toolbars.  Encapsulation of
these functions into the UCMenu control means that there is very little
application code required to support customization.
:p.
Although most of the customization function is encapsulated in the
control itself, there are several messages to which the application
must respond for customization to work properly.  The UCMenu control
will send :WM_CONTROL. messages to its owner when it needs certain types
of information.  Depending on what type of customization the
application allows (free-form or 'buffet' style), some of
these message may not be generated.
The :WM_CONTROL. notification codes for customization are as follows:
:ul.
:li.:UCN_QRYDEFTEMPLATEID.&colon.  This is sent when the user selects the :hp1.Load
default:ehp1. context menu item to restore the entire UCMenu to its
default configuration.  The application responds by supplying the
resource ID of the menu template to be loaded.
:li.
:UCN_QRYTEMPLATEMODULE.&colon.  This is also sent when the :hp1.Load default:ehp1.
context menu item is selected.  The application must supply the
handle of the module in which the :UCN_QRYDEFTEMPLATEID. resource is to be
found.
:li.
:UCN_QRYRESBMP.&colon.  This message is sent when the user wants to display a
list of application-supplied bitmaps from which to choose.  The
application must allocate and construct an array of bitmap resource
IDs.
This message is generated by the free-form customization method.
:li.
:UCN_QRYACTIONLIST.&colon.  This message is sent when the user has requested
a list of actions from which to choose.  The application responds by
sending a series of :UCMENU_INSERTACTION. messages, each with a pointer
to an action string and descriptive help text.  After the last action
has been inserted, the application must send :UCMENU_ACTIONSINSERTED.
to indicate the list is complete.
This message is generated by the free-form customization method.
:li.
UCN_HLP_*&colon. This is a set of messages sent when the UCS_CUSTOMHLP
menu style is used and the user requests help on a customization
dialog.  By default the UCMenu control will supply the needed help
text.
:eul.
:p.
The handling of all these messages is demonstrated in the SAMP3.C
sample program in the toolkit.
.**********************************************************************************
:h2.Control of Customization
The highly flexible customization built-in to the UCMenu control may
not be desirable for all applications or situations.  For example, the
ability to move items from one menu to another within an application
may not make semantic sense.  An application with multiple windows
performing different functions may not want to allow the user to drag
items from the toolbar in one window to the toolbar in another.  The
result might be 'actions' which make no sense in the context of the
window.  The application may also want to provide its own
customization methods to replace or supplement those of UCMenus.
:p.
By default, all the direct manipulations and all
the context menu options are allowed.  No buffet dialog
is displayed unless explicitly called using the UCMenuXXXXBuffetDlg() APIs.
Various
style flags (UCS_*) can be used by the application to control which
direct manipulation and context menu functions are supported for that
instance of the menu.  At the extreme, the application can set a style
of UCS_STATIC to prevent any customization at all.  This style will
disable all direct manipulation functions and the context menu.  Other
style flags allow selective disabling of specific customization
functions, such as disabling drag/drop between menus (but allowing it
within a menu), disabling drops to the system shredder, removing the
'Edit item...'  context menu option, etc.
:p.
An application can also supply its own customization functions via the
UCMenu context menu.  By sending the control a :UCMENU_ADDITEMSTOCM.
message the application can add its own options to the context menu.
The UCMenu control will send a :WM_CONTROL. message with a
notify code of :UCN_CMITEM. when such an option is selected.  A sample
of adding an application customization function to the context menu is
shown in the SAMP3.C toolkit sample.
.******************************************************************************
:h1.Version Notice
The following sections describe the recent changes to the UCMenus toolkit.
.br
:h2.Version 2.12
Version 2.12 is
binary-compatible with applications written for Version 2.1 and later.
Version 2.12 contains the following major changes from Version 2.11:
:ul.
:li.Compiled binary files (.OBJ and .DLL) are no longer supplied as part of
the toolkit package.  You must build the binary files using your compiler
and toolkit installation (see :makeall.).  This prevents
linking errors when using the toolkit with different levels of compilers
and OS/2 toolkits.
:li.This version contains only some minor fixes from Version 2.11:
:ul.
:li.Fix obscured 3D button border on scroll button when running on OS/2 Merlin.
:li.Change to send owner UCN_DELETED notification after delete of the item is complete.
:eul.
:eul.
.*******************
:h2.Version 2.11
Version 2.11 is
:hp1.not:ehp1. binary-compatible with applications written for Version 1
or Version 2.0.  This version is :hp1.source:ehp1. compatible with Version 2.0.
:hp1.The size of some data structures were changed in this version so applications
must be recompiled.:ehp1.
:p.
Version 2.11 contains the following major changes from Version 2.1:
:ul.
:li.Two new styles, CMS_MATRIX_VERT and CMS_MATRIX_HORZ allow matrix
style menus be scrollable in the vertical or horizontal direction.  SAMP1 of
the toolkit uses this style for the tool palette menu.
:li.The frame is now activated when a button is pressed on a UCMenu
control.  This prevents UCMenu context menus from appearing in
a non-active frame.
:li.Fixed memory leaks.
:li.Improved scrolling such that UCMenus does not always return to a
scroll position of zero when items are inserted, deleted, or modified.
:eul.
:p.
Version 2.1 contains the following major changes from Version 2.0:
:ul.
:li.Improved :UCN_MOUSEMOVE. message generation.
:li.Added support for bubble-help (cartoon-like bubble with extended description text).
:li.Added following APIs:
:ul compact.
:li.:UCMenuStrdup.
:li.:UCMenuItemDup.
:li.:UCMenuItemFree.
:eul.
:li.Added support for application-supplied context menu.
:li.Added compile-time UCMUI define statement.  Removing this statement
produces a UCMenus control with no user-interface (customization) code.
:li.Submenus are now dismissed when the application window becomes inactive (application
must send new :UCMENU_ACTIVECHG. messages).
:li.Changed item sizing algorithms such that item text is never truncated even for
UCS_FORCESIZE style menus.  Item width is always set to larger of the bitmap width and
the text width.
:li.Added :UCMENU_DISABLEUPDATE. message to improve performance during large number
of item insert/delete/modify.
:li.The :hp1.pszDefaultBitmap:ehp1. field of the UCMINFO structure can now be a resource
ID (in string form) or a filename.
:li.Changed UCMENUS.RCH to UCMLOCAL.H since some build systems require header to have .H extension.
:li.Fixed bug that caused application to hang if application had its own drag/drop functions
in addition to the toolbar.
:li.Improved handing of bitmap background colors:
:ul compact.
:li.New style UCS_CHNGBMPBG_AUTO will use the lower leftmost pixel of the bitmap to determine the
background color (the :hp1.BmpBg:ehp1. field of UCMINFO is ignored).  This allows different
bitmaps of the toolbar to have different transparent colors.
:li.Improved algorithms to not assume 256-color bitmaps (less memory, faster execution).
:li.Improved algorithms such that background colors are mapped only when the bitmap
is first loaded (instead of every time the toolbar is painted).
:li.All bitmaps are reloaded (and color mapped) when the background color is changed.
This prevents valid colors in the bitmap from getting set to the background when
several color changes are made in sequence.
:li.Removed lCurBmpBgColor from UCMITEM structure since it is no longer needed.
:eul.
:li.Fixed stray-pixel problems when a partially-obscured button is pressed.
:li.Many minor bug fixes and code changes to improve performance (in particular, store
often-used window handles in UCMDATA to avoid lots of WinQueryWindow() calls).
:eul.
.*----------------------------------------------------------------------------
:h1 res=9000.Building Executable Files
There are two ways to build an application using the UCMenus toolbar control:
:ol.
:li.:hp1.Static Linking:ehp1.  The UCMenus source code is compiled to an
object file (.OBJ) which is then linked with the application code.  In this
scenario the UCMenus code becomes part of the application executable.  The
application code itself may be an EXE file or a DLL.  Note that you must
also bind the UCMenus resources to your application EXE file.
:li.:hp1.Dynamic Linking:ehp1.  The UCMenus source code is compiled and
linked into a standalone DLL which is shipped with the application.  The
application can call entry points in the DLL either by explicitly loading
the DLL with :hp2.DosLoadModule():ehp2. and :hp2.DosQueryProcAddress():ehp2.,
or the DLL entry points can be named in the IMPORT section of the application
module definiton file (.DEF).
:eol.
:p.
The sample make files supplied in the \SAMPLES subdirectories show how to
build an application for static or dynamic linking, and how to bind the
UCMenus resource files with the application.
:p.
The advantage of static linking is simplicity; the UCMenu functions are simply
called by your application just like any other application functions.  There
are no DLLs to ship as part of the application.  The advantage of dynamic
linking is that the application executable size is reduced, and the application
can be structured such that the UCMenus code is never loaded if it is not
needed.  This can improve application performance and reduce memory
requirements.
:p.
In either case, you must pre-construct either the .OBJ file to be linked
with your application, or the .DLL file to be shipped with it.  These files
are built from the source code supplied as part of the toolkit.  They are not
part of the toolkit itself since you may have a different level of the compiler,
linker, or OS/2 toolkit which could make the UCMenus executable code
incompatible with your application.  By having you build the UCMenus binary
files it is insured the same compiler and toolkits are used for the UCMenus
code and the application code.
:p.
To build the UCMenus binary object files, you must have either the IBM
C/Set or VisualAge C++ compiler installed.  The SOURCE\MAKEFILE make file is
by default setup for the VisualAge compiler.  If you are using C/Set or
some other compiler you will need to modify the make file.
:p.
Use the following steps to build the UCMenus binary object files from
and OS/2 command window:
:ol.
:li.Change to the \SOURCE subdirectory of the UCMenus toolkit.
:li.Execute the command "nmake /a all".
:eol.
:p.
This will build several files:
:xmp.
 \SOURCE\UCMENUS.MAP     Linker map file
 \SOURCE\UCMENUS.SYM     Symbol file
 \LIB\UCMSTAT.OBJ        Object code for static linking
 \LIB\UCMENUS.DLL        Dynamic code for dynamic linking
 \LIB\UCMENUS.LIB        Import library for dynamic linking
 \LIB\UCMENUS.RES        Full GUI resource file
 \LIB\UCMINRES.RES       Minimal (no-GUI) resource file
:exmp.
.*----------------------------------------------------------------------------
:h1.Limitations and Known Problems
:ul.
:li.A bug in OS/2 Warp 3.0 can cause random bitmap corruption to occure during drag/drop
operations.  Usually seen as the toolbar changing size unexpectedly and one or
more toolbar bitmaps being corrupted.  Bug was reported to OS/2 development
as APAR PJ17913.  This APAR is reported to be fixed in Warp fixpack #7.  This problem
does not occure in OS/2 Version 2.X.
:li.A bug in PM prevents support of MIS_BREAK on submenus (MM_QUERYITEMRECT
can return wrong coordinates when an owner-draw submenu has MIS_BREAK style
items).  Any MIS_BREAK style flags are removed when the UCMenu is created.
:li.Bubble help is not implemented for submenus.
:eul.
.*----------------------------------------------------------------------------
:h1.Direct Manipulations
UCMenus support the following direct manipulation functions:
:ul.
:li.
Move menu items: drag and drop menu items from one position to another.
New position will be insertion point nearest the mouse cursor when
the item is dropped.  MIS_SPACER items can also be moved.  Items
may be moved from one toobar to another.
:li.
Copy menu items: drag and drop menu items with the CTRL key
pressed.   Items may be copied from one toolbar to another.
:li.
Copy to submenu: drag menu item with ALT key pressed and drop on
another menu item.  If the target
item is not a submenu it will be changed to be one.  The dropped item
is inserted after the last item already in the submenu.
Submenu items can be copied from one toolbar to another.
:li.
Delete menu items: drag menu item to system shredder.
:li.
Create new items: drag .BMP file type from desktop or drives folder
onto a toolbar.  A new item with the supplied bitmap will be
created.  The item will not have any text or action associated with it
until provided with the context menu 'Edit item' option.
:li.
Render bitmap to file: a menu item which has file-supplied bitmap (the
bitmap specification is a file name, not an application resource) can
be dragged to the OS/2 desktop or a folder to create a .BMP file.
The bitmap can also be dropped on the OS/2 Icon Editor desktop object
to open and edit the source bitmap file.
:li.
Change colors: a color can be dragged from the system color palette
onto the toolbar background or the item background.  All items will
have the same background color.
:li.
Change font: a font can be dragged from the system font palette onto the
toolbar.  The dropped font will be used for the text under the
bitmaps.
:eul.
:p.
Items can also be created, deleted and edited with the context menu
which may be displayed by positioning the cursor on a menu item and
pressing the right mouse button (if the 'Edit' context menu
item is enabled by the application).
.*-------------------------------------------------------------------------
:h1.Submenus
UCMenus supports graphical submenus in a similar fashion to normal PM
submenus.  Visually, a submenu is a vertical UCMenu which is invoked
by selecting from a primary UCMenu item (the submenu 'placeholder'):
:artwork align=center name='SUCM.BMP'.
:p.
Only one level of submenu is supported.  A submenu cannot contain
multiple columns (e.g. the MIS_BREAK style flag is ignored).  A
submenu can be customized like the main menu by drag/drop reordering
of items, adding items by dropping from other menu or submenus,
using the context menu to insert, delete, or modify items, etc.
:p.
Submenus inheret style settings from the parent (main) menu,
including background colors, fonts for text, etc.
:p.
:hp1.Limitations&colon.:ehp1.
:ul.
:li.A submenu cannot use the MIS_BREAK style to have multiple columns
of selectable items.
:li.An attribute of MIA_NODISMISS on a submenu placeholder is ignored.  To
prevent a submenu from being dismissed when an item is selected, the
item itself must have the MIA_NODISMISS attribute.  Submenu items without
this attribute will cause the submenu to be dismissed when the item
is selected.
:eul.
.*-------------------------------------------------------------------------
:h1.Styles
The visual appearance of a UCMenu can be
modified through the use of 'style' flags.
UCMenu toolbars can have a vertical, horizontal, or matrix layout:
:ul compact.
:li.
:hp1.CMS_HORZ:ehp1.  The traditional horizontal menu bar style. If the
number of items do not fit, scrolling indicators are shown. This is contrary
to the style of menu bars which would wrap.
:fig.
:artwork name='HUCM.BMP'.
:figcap.Horizontal arrangement
:efig.
:p.
:li.
:hp1.CMS_VERT:ehp1.  Display as a vertical column.  This is a very useful
arrangement to display a small set of tools to the left or right of a
window.
:fig.
:artwork name='VUCM.BMP'.
:figcap.Vertical arrangement
:efig.
:p.
:li.
:hp1.CMS_MATRIX:ehp1.  A matrix arrangement, as it is typically used for tool palettes.  The
matrix may free-form (application defines height and width), or it may have an
orientation in which case it becomes scrollable in that direction (CMS_MATRIX_HORZ, or
CMS_MATRIX_VERT).
:fig.
:artwork name='MUCM.BMP'.
:figcap.Matrix arrangement.
:efig.
:eul.
:p.
The
bitmap items can be drawn with or without 3D frames, text underneath,
and with a fixed or automatic sizing.  Individual items can be
highlighted with a 'checkmark' attribute and are drawn with thick dark
borders.  Background colors of the menu items and empty toolbar spaces
can also be controlled.  When required by window size, scrollbar
controls will automatically appear at each end of the toolbar.
:p.
A UCMenu can have a number of different styles that can be set on creation in
the :UCMINFO. structure and changed dynamically through the context menu&colon.
:parml compact break=all.
:pt.:hp2.UCS_NOTEXT:ehp2.
:pd.The text associated with the item is not displayed on the screen.
:pt.:hp2.UCS_FRAMED:ehp2.
:pd.When this is set, a frame is drawn around each item so that it looks like a 3-D
button.
:pt.:hp2.UCS_FORCESIZE:ehp2.
:pd.The size of all items can be forced to a certain rectangle. If this is set, the size
has to be specified in the :UCMINFO. structure (UCMInfo.cx and UCMInfo.cx)
:pt.:hp2.UCS_SHRINK_BLEND:ehp2.
:pd.When set, either BBO_OR or BBO_AND is used to shrink the bitmaps, else BBO_IGNORE is used
:pt.:hp2.UCS_SHRINK_OR:ehp2.
:pd.Used when BBO_IGNORE not selected. If set BBO_OR is used, else BBO_AND
:pt.:hp2.UCS_NO_DM_ALT:ehp2.
:pd.No drag and drop copy to a submenu when doing an Alt-drop over the UCMenu
:pt.:hp2.UCS_NO_DM_M_TO_OTHER:ehp2.
:pd.No drag and drop move to another UCMenu
:pt.:hp2.UCS_NO_DM_M_FROM_OTHER:ehp2.
:pd.No drag and drop move from another UCMenu
:pt.:hp2.UCS_NO_DM_M_INSIDE:ehp2.
:pd.No drag and drop move inside this UCMenu
:pt.:hp2.UCS_NO_DM_C_TO_OTHER:ehp2.
:pd.No drag and drop copy to another UCMenu
:pt.:hp2.UCS_NO_DM_C_FROM_OTHER:ehp2.
:pd.No drag and drop copy from another UCMenu
:pt.:hp2.UCS_NO_DM_C_INSIDE:ehp2.
:pd.No drag and drop copy inside this UCMenu
:pt.:hp2.UCS_NO_DM_DISCARD:ehp2.
:pd.No drag and drop to the shredder
:pt.:hp2.UCS_NO_DM_RENDER_TO_BMP:ehp2.
:pd.No drag and drop rendering as a BMP file
:pt.:hp2.UCS_NO_DM_RENDER_FROM_BMP:ehp2.
:pd.No drag and drop from a BMP file
:pt.:hp2.UCS_NO_DM:ehp2.
:pd.No direct manipulation at all
:pt.:hp2.UCS_NO_CM_MENU_STYLE:ehp2.
:pd.No "change style" in the context menu
:pt.:hp2.UCS_NO_CM_MENU_IMPORT:ehp2.
:pd.No "import" in the context menu
:pt.:hp2.UCS_NO_CM_MENU_EXPORT:ehp2.
:pd.No "export" in the context menu
:pt.:hp2.UCS_NO_CM_MENU_DEFAULT:ehp2.
:pd.No "load default" in the context menu
:pt.:hp2.UCS_NO_CM_ITEM_EDIT:ehp2.
:pd.No "edit item" in the context menu
:pt.:hp2.UCS_NO_CM_ITEM_CREATE:ehp2.
:pd.No "create item" in the context menu
:pt.:hp2.UCS_NO_CM_ITEM_DELETE:ehp2.
:pd.No "delete item" in the context menu
:pt.:hp2.UCS_NO_CM_SEPARATOR:ehp2.
:pd.No "delete item" in the context menu
:pt.:hp2.UCS_NO_CM:ehp2.
:pd.No context menu
:pt.:hp2.UCS_CHNGBMPBG:ehp2.
:pd.When this style is used the background color of the bitmaps is
mapped to the background color of the toolbar.  The background color
of the bitmaps is defined as
the :hp1.BgBmp:ehp1. color in the :UCMINFO. structure.  All pixels
in all bitmaps which match that color will be changed to the toolbar
background color.  This style should not be used with UCS_CHNGBMPBG_AUTO.
:pt.:hp2.UCS_CHNGBMPBG_AUTO:ehp2.
:pd.When this style is used the background color of the bitmaps is
mapped to the background color of the toolbar.  The background color of
the bitmaps is defined as the color of the pixel in the lower leftmost corner
of the bitmap.  All pixels of that same color in the bitmap are changed
to the toolbar background color.  The :hp1.BgBmp:ehp1. field of the :UCMINFO. structure
is ignored.  This style should not be used with UCS_CHNGBMPBG. 
:pt.:hp2.UCS_CUSTOMHLP:ehp2.
:pd.The help is provided by the user.
:pt.:hp2.UCS_PROMPTING:ehp2.
:pd.:UCN_MOUSEMOVE. notifications are sent to the owner.
:pt.:hp2.UCS_NODEFAULTACTION:ehp2.
:pd.The list of actions does not include executeprogram by default.
:pt.:hp2.UCS_BUBBLEHELP:ehp2.
:pd.Enables the display of cartoon-style bubble help.  When the pointer
hovers on a single menu item for a defined period of time (:hp1.BubbleDelay:ehp1. in
:UCMINFO.) the toolbar will query the application for the help text to
be displayed in the bubble window (:UCN_QRYBUBBLEHELP.).  If the application
supplies help text, it will be displayed in a cartoon-like window near the
menu item.  The bubble window is removed when the pointer leaves the
toolbar, or when the :hp1.BubbleRead:ehp1. time period expires, whichever
occures first.  The application :hp2.must:ehp2. send :UCMENU_ACTIVECHG. messages
for the bubble window to work properly.
:eparml.
:p.The UCM text font and background color can be set on creation, through the :UCMINFO.
structure. The default font is Helv 8. Note that the color corresponds to the RGB index
and can look different on different types of displays and adapters. You should use the index returned by
WinQuerySysColor().
:xmp.

#define UCM_DEFAULTCOLOR     0x00C9C9C9L   // -- light grey on 8514
#define UCM_DEFAULTFONT      "8.Helv"

:exmp.
.*-------------------------------------------------------------------------
:h1.Creating a UCMenu Control
Conceptually, creating a UCMenu control is the same as creating a PM
menu control.  The menu structure and items are defined in textual
form in a resource file (.RC) using MENU, MENUITEM, and SUBMENU
statements.  The resource file is compiled with the resource compiler
into binary resource format and appended to the application executable
(or a DLL).  The application calls an API to read the binary resource
and create the visual PM windows and underlaying data structures.
Finally, the window is placed and sized on a parent window.
.*-------------
:h2.Resource Files
The textual resource file (.RC) specifies the complete structure of
the menu and the contents of the menu items.  However, the MENUITEM
resource statement does not have the syntactic flexibility to allow
complete specification of all the data associated with a UCMenu item.
Therefore, the text field of the MENUITEM statement is interpreted to
contain four extra fields of information not found on standard PM menu
items:  the bitmap specification, action string, parameter string, and
a data string.  Each of these fields is separated by a single
character defined as the first character of the string.  A typical
resource file for a UCMenu might be:
:xmp.
BITMAP 6  "new.bmp"
BITMAP 1  "open.bmp"
BITMAP 2  "save.bmp"
BITMAP 62 "styles.bmp"
BITMAP 63 "bold.bmp"
BITMAP 64 "italic.bmp"
BITMAP 8  "help.bmp"

/* Text strings are interpreted as:                           */
/*                                                            */
/* "<c>Text<c>BitmapID<c>ActionStr<c>ParamStr<c>DataStr"      */
/*                                                            */
/*   where <c> is any character that does not appear in       */
/*   the strings.                                             */
/*                                                            */
/* Item style MIS_SPACER produces a gap in the menu bar.      */

MENU ID_COMMANDBAR LOADONCALL MOVEABLE DISCARDABLE
BEGIN
  MENUITEM "/New/6/New",              1,  MIS_TEXT
  MENUITEM "/Open/1/Open File",       2,  MIS_TEXT
  MENUITEM "/Save/2/Save File",       3,  MIS_TEXT
  MENUITEM "",                        4,  MIS_SPACER
  SUBMENU  "/Styles/62/Styles Submenu",     5, MIS_TEXT
  BEGIN
    /* Use a different delim here so we can use "/" in the strings */
    MENUITEM "!Bold!63!Bold/Style",         6, MIS_TEXT ³ MIS_CHECKABLE
    MENUITEM "!Italic!64!Italic/Style",     7, MIS_TEXT ³ MIS_CHECKABLE
  END
  MENUITEM "",                        8,  MIS_SPACER
  MENUITEM "/Help/8/Show Help",       9,  MIS_TEXT
END
:exmp.
The format for the text field is the following&colon.
"&lbrk.#Text&rbrk.#BitmapID&lbrk.#Action&rbrk.&lbrk.#Parameters&rbrk.&lbrk.#Data&rbrk.".
The first character of the string (here #) is used as a delimiter and can be any
character that does not appear in the string itself.
:parml compact break=all.
:pt.:hp2.Text:ehp2.
:pd.The text displayed in or under the bitmap
:pt.:hp2.BitmapID:ehp2.
:pd.Bitmap identifier or file name
:pt.:hp2.Action:ehp2.
:pd.Information about the action associated with the item , for example the name of a macro.
:pt.:hp2.Parameters:ehp2.
:pd.Parameters associated to the action.
:pt.:hp2.Data:ehp2.
:pd.Some text associated with the item , for example the parameters of a macro.
:eparml.
Some notes on UCMenu resource files:
:ul.
:li.
The menu item IDs specified in the resource file are arbitrary.
Sequential numbering is used to help keep menu items unique but is
not necessary.
:li.
A new menu item style MIS_SPACER is defined for UCMenus.  It produces
a blank space in the menu to separate menu items into groups.
:li.
The 'Data' field is not seen by the user and is for application use.
Note that new items created by customization will have no 'data'
value.
:li.
The bitmap items have to be declared with the MIS_TEXT style even
though they will (from a PM viewpoint) be OWNERDRAW items.
:li.
The MIS_BREAK style is not effective for the first level UCMenu items, but it
works for the submenu items.
:li.
Only one level of submenus is supported.
:eul.
.*-------------------
:h2.Completing the UCMINFO Structure
To complete the process of creating a UCMenu, the application must
construct a :UCMINFO. data structure and fill in all the
relevant fields.  The RGB values of the structure are used for color
mapping the bitmap background pixels.  UCMenus supplies a means for
bitmap background pixels to be automatically mapped to the current
UCMenu background color.  The BgBmp value of :UCMINFO. tells UCMenus what
background color was used in the design of the bitmaps.  That color
will be replaced with the ItemBgColor before the bitmaps are displayed
wherever that color appears in the bitmap.  The ItemBgColor should be
set to the SYSCLR_MENU color returned by WinQuerySysColor().  A
different color may be specified in the BgColor field.  This will be
the color used wherever there are no items on the toolbar.
:p.
Once the :UCMINFO. structure is filled in, the function
:UCMenuCreateFromTemplate. or :UCMenuCreateFromResource. is called.
The template version is used if the application has manually loaded a
previously saved UCMenu template.  The resource version will create a
UCMenu from a menu template in the applications resources.
The creation functions return two window handles.  The function result is
the window handle of interest for the application, the other may be
ignored.
:p.
:h2.Placement and Sizing of a UCMenu
Toolbars are generally placed along one edge of the application window
frame.  Toolbars may be attached to the top, bottom, left or right edge
of the window.  The toolkit sample SAMP1.C shows toolbars on all four edges of the frame.
:p.
It is possible to simply place and size the toolbar into the client
window of a standard PM window.  However, this simple approach
introduces a lot of complexity when the application must properly scale
and paint the client window.  If the frame window is a dialog, proper
size and placement is even more complex since the application does not
paint, and there is no separate client window.
:p.
The proper solution to toolbar placement is to make the toolbar a
frame control.
Making a window into a frame control requires a thorough knowledge of
how PM frame windows and message protocols work.  Adding a frame
control to a dialog window is even more complex since it may require
the movement of all the dialog controls.  All the function necessary to
make UCMenu windows into frame controls is supplied in a set of utility
routines in the toolkit.  These routines are not a formal part of the
UCMenu control, but allow an application to easily place UCMenu
controls along any edge of a frame or dialog window.  By using these
utilities an application can be completely removed from any sizing or
positioning considerations for the toolbars.
:p.
The frame control utilities consist of two functions, one to add a
UCMenu to a frame or dialog window, the other to remove it.
The utilities support up to four toolbars per
frame or dialog window (one each at the top, bottom, left, and right
edges).  By calling the add/remove frame control utilities, a toolbar
can be toggled on and off.
:p.
The UCMUtils() functions encapsulate all the complexity of frame
control management freeing the application from that task.  With just
a simple function call, the toolbar can be positioned in the frame and
will maintain its proper position as the frame is sized and moved.
Source code for the utilities is provided in the toolkit.
.***************************************************************************
:h1.A Dynamic Status Bar
A dynamic status bar can be implemented by the application to
automatically show a description of each menu item as the mouse pointer
is moved on the toolbar.  To help the application implement this
feature, a UCMenu with the UCS_PROMPTING style will send :WM_CONTROL.
messages with a notify code of :UCN_MOUSEMOVE. when the pointer moves on
the menu bar.  The message supplies the menu item ID of the item under
the mouse pointer.  Using this item ID, the application can obtain
the item data structures and determine the action string associated
with that item.  The action string string may be displayed directly, or
it may be used to lookup a more complete description for display to the
user.  The SAMP3.C sample program uses the lookup method to display a
longer description of the menu items action.
.***************************************************************************
:h1.Saving/Restoring UCMenus
The UCMenus API provides several function to aid the application in
saving and restoring the customized state of UCMenu toolbars.  The
function :UCMenuMakeTemplate. will create a binary in-storage
representation of the complete UCMenu item structure.  The binary
image will include all text, bitmaps, action strings, and arrangements
of menu items.  The corresponding APIs, :UCMenuCreateFromTemplate.
and :UCMenuNew., create and replace UCMenu controls from an in-storage
binary template.  It should be noted that these binary templates
are in a special format used by UCMenus.  UCMenu templates are not
usable as standard PM menu templates.
:p.
The SAMP3.C toolkit sample
shows the processing of WM_SAVEAPPLICATION.
The UCMenu style,
colors, and font, as well as the binary templates, are stored in the
application .INI file.  During initialization, the styles, colors,
font and templates are read from the .INI file and are used to recreate
the customized toolbars.
.*********************************************************************************************
:h1.Data Structures Reference
This section contains a list of all the structures used by a UCMenus application.
.*-------------------------------------------------------------------------
:h2 res=102.UCMITEM (UCMenu Item Structure)
This structure is used to store data related to a UCMenus menu item, such
as its bitmap handle, identifier, text and an action strings.  For each menu
item, this structure is accessed from the :hp1.hItem:ehp1. component of the
standard PM :hp1.MENUITEM:ehp1. structure (which can be obtained with
the MM_QUERYITEM message).
:p.
:xmp.
typedef struct {
   LONG    hBmp;            // Bitmap handle
   PSZ     pszBmp;          // Bitmap Identifier or file name
   PSZ     pszText;         // Bitmap Text
   PSZ     pszAction;       // Action : for instance the name of a macro
   PSZ     pszParameters;   // Parameters for the action
   PSZ     pszData;         // Data associated to the item, not visible for the user
   USHORT  usId;            // Id of the item
   LONG    lCurBmpBgRGB;    // Current background color set for the bmp (if any)
   ULONG   ulFlags;
} UCMITEM, *PUCMITEM;

#define ITEM(a,b) ((PUCMITEM)((a)->hItem))->b
:exmp.
ulFlags can include &colon.
:dl compact.
:dt.:hp2.UCMI_BMPFROMFILE:ehp2.
:dd.Set if the bitmap comes from a file, not set if it comes from the resources.
:edl.
.*----------------------------------------------------------------------------
:h2 res=103.CMITEMS (Context Menu items)
This structure is used to add items to the UCMenu's context menu.
It contains the identifier and text of the item.
:p.
:xmp.
typedef struct {
   ULONG ID;
   PSZ   pszItemText;
} CMITEMS,  *PCMITEMS;
:exmp.
.*----------------------------------------------------------------------------
:h2 res=101.UCMINFO (UCMenu Initialization Structure)
This structure is used to create a UCMenu. It must be passed to
the UCMCreateXXXX() APIs when creating a UCMenu.
:p.If a matrix UCMenu is created with a null width, NbOfCols must contain the
number of menu items per line. If it's created with a null height, NbOfRows
must contain the number of items per column.
:xmp.
typedef struct {
   ULONG  cb;                   // size of this structure
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
   LONG    ItemBgColor;         // RGB color of the UCMenu items background
   PSZ     pszFontNameSize;     // String describing the font of the UCMenu (such as used
} UCMINFO, *PUCMINFO;           //  in WinSetPresParam), if NULL, UCM_DEFAULTFONT is used
:exmp.
.*----------------------------------------------------------------------------
:h2 res=104.QBUBBLEDATA (Query Bubble Data)
This structure is passed to the application by the
:UCN_QRYBUBBLEHELP. message.
:p.
:xmp.
   typedef struct { 
      MENUITEM     *MenuItem   ;  // Item information supplied by UCMenus
      char         *BubbleText ;  // Bubble text supplied by application (freed by UCMenus)
   } QBUBBLEDATA, *PQBUBBLEDATA;
:exmp.
.*---------------------------------------------------------------------------
.* IPFCPREP macros used for message reference entries
.*---------------------------------------------------------------------------
.dm message on.
:h2 res=&res..&name.
.**** to build links: .dm &name. on :link reftype=hd res=&res..&name.:elink.
.dm off
.*----------------
.dm params on
:parml.
.dm off
.*----------------
.dm param1 on
:pt.:hp6.Param1:ehp6.
.br
:parml.
.dm off
.*----------------
.dm param2 on
:eparml.
:pt.:hp6.Param2:ehp6.
.br
:parml.
.dm off
.*----------------
.dm item on
:pt.:hp2.&name.:ehp2. :hp1.(&type.):ehp1.
:pd.
.dm off
.*----------------
.dm returns on
:eparml.
:pt.:hp6.Returns:ehp6.&rbl.
.br
:parml.
.dm off
.*----------------
.dm eparams on
:eparml.
:eparml.
.dm off
.*----------------
.dm sample on
:p.
:h3.:hp5.Example:ehp5.
.br
:xmp.
:font facename='System Monospaced' size=12x10.
.dm off
.*----------------
.dm esample on
:font facename=default size=0x0.
:exmp.
.dm off
.*----------------
.dm remarks on
:p.
:h3.:hp5.Remarks:ehp5.
.br
.dm off
.*----------------
.dm related on
:p.
:h3.:hp5.Related:ehp5.
.br
.dm off
.*----------------
.dm defproc on
:p.
:h3.:hp5.Default Processing:ehp5.
.br
.dm off
.*----------------
.dm emessage on
.dm off
.*----------------
.*-----------------------------------------------------------------------------------------------
:h1 res=500 toc=12.WM_CONTROL Message Reference
.*-----------------------------------------------------------------------------------------------
This section describes all the WM_CONTROL messages generated by a UCMenu control and
sent to the control owner.
.*-----------------------------------------------------------------------------------------------
:message res=600 name='UCN_ITEMSELECTED' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
a UCMenu menu item is selected by the user.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_ITEMSELECTED
:param2.
:item name='pUCMitem' type='UCMITEM *'.
Pointer to the UCMenu item structure for the selected item.
:returns.
Nothing
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*-----------------------------------------------------------------------------------------------
:message res=601 name='UCN_QRYTEMPLATEMODULE' .
This WM_CONTROL notification is sent by the UCMenu to its owner when the default template is loaded
("Load default option" in the popup context menu). The owner has to return the module
handle where we can look for the default template.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYTEMPLATEMODULE
:param2.
:item name='pHModule' type='HMODULE *'.
Pointer to the module to be filled by the owner.
:returns.
:item name='Processed' type='BOOL'.
TRUE if processed, FALSE else.
:eparams.
:remarks.
:defproc.
:related.
:UCN_QRYDEFTEMPLATEID.
:emessage.
.*---------------------------------------------------------------------------
:message res=602 name='UCN_QRYDEFTEMPLATEID' .
This WM_CONTROL notification is sent by the UCMenu to its owner when the default template is loaded
("Load default option" in the popup context menu). The owner has to return the ID
of the menu in the resource.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYDEFTEMPLATEID
:param2.
:item name='pID' type='PUSHORT'.
Pointer to the ID to be filled by the owner.
:returns.
:item name='Processed' type='BOOL'.
TRUE if processed, FALSE else.
:eparams.
:remarks.
:defproc.
:related.
:UCN_QRYTEMPLATEMODULE.
:emessage.
.*---------------------------------------------------------------------------
:message res=603 name='UCN_QRYDEFTEMPLATE' .
This WM_CONTROL notification is sent by the UCMenu to its owner when the default template has to be loaded
("Load default option" in the popup context menu). The owner has to return a pointer to the
template of the default toolbar, allocated with UCMenuAlloc.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYDEFTEMPLATE
:param2.
:item name='ppTemplate' type='PVOID*'.
Pointer to the pointer to the template.
:returns.
:item name='Processed' type='BOOL'.
TRUE if processed, FALSE else.
:eparams.
:remarks.
If processed, the template has to be allocated with UCMenuAlloc().
The UCMenus will free it with UCMenuFree().
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=604 name='UCN_QRYACTIONLIST' .
This WM_CONTROL notification is sentthe UCMenu to its owner when the settings dialog for the
action is popped up so that he can fill in the list of actions.
The owner has to send :UCMENU_INSERTACTION. messages and to post back a :UCMENU_ACTIONSINSERTED.
when it is done.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYACTIONSLIST
:param2.
:item name='hwndUCMenu' type='HWND'.
Handle of the UCMenu.
:returns.
nothing
:eparams.
:remarks.
:defproc.
:related.
:UCMENU_INSERTACTION.
:emessage.
.*---------------------------------------------------------------------------
:message res=605 name='UCN_SIZE' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
its size has changed.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_SIZE
:param2.
:item name='param2' type='ULONG'.
reserved
:returns.
Nothing
:eparams.
:remarks.
After receiving this message, further information can be obtained by using the UCMENU_QUERY* messages.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=606 name='UCN_STYLE' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
its style has changed.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_STYLE
:param2.
:item name='param2' type='ULONG'.
reserved
:returns.
Nothing
:eparams.
:remarks.
After receiving this message, further information can be obtained by using the UCMENU_QUERY* messages.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=607 name='UCN_FONT' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
its font has changed (eg when a font has been dropped from the palette over the UCMenu ).
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_FONT
:param2.
:item name='param2' type='ULONG'.
reserved
:returns.
Nothing
:eparams.
:remarks.
After receiving this message, further information can be obtained by using the UCMENU_QUERY* messages.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=608 name='UCN_COLOR' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
its color has changed (eg when a color has been dropped from the palette over the UCMenu ).
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_COLOR
:param2.
:item name='param2' type='ULONG'.
reserved
:returns.
Nothing
:eparams.
:remarks.
After receiving this message, further information can be obtained by using the UCMENU_QUERY* messages.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=609 name='UCN_ADDEDITEM' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
an item has been added.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_ADDEDITEM
:param2.
:item name='ItemID' type='USHORT'.
ID of the added item.
:returns.
Nothing
:eparams.
:remarks.
After receiving this message, further information can be obtained by using the UCMENU_QUERY* messages.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=610 name='UCN_DELETEDITEM' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
an item has been deleted.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_DELETEDITEM
:param2.
:item name='ItemID' type='USHORT'.
ID of the added item.
:returns.
Nothing
:eparams.
:remarks.
After receiving this message, further information can be obtained by using the UCMENU_QUERY* messages.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=611 name='UCN_BITMAP' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
the bitmap of an item has been changed.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_BITMAP
:param2.
:item name='ItemID' type='USHORT'.
ID of the changed item.
:returns.
Nothing
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=612 name='UCN_TEXT' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
the text of an item has been changed.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_TEXT
:param2.
:item name='ItemID' type='USHORT'.
ID of the changed item.
:returns.
Nothing
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=613 name='UCN_QRYRESBMP' .
This WM_CONTROL notification message is sent by the UCMenu to its owner when the list of bmp id is needed.
("Predefined..." on the "general" notebook page )
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYRESBMP
:param2.
:item name='pArrayId' type='PULONG *'.
The owner has to return in this pointer an array of the bitmap IDs, allocated with UCMenuAlloc.
:returns.
:item name='nbItems' type='ULONG'.
The number of elements in the returned array or zero.
:eparams.
:remarks.
The array will be freed by the UCMenu.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=614 name='UCN_ACTION' .
This WM_CONTROL notification is sent by the UCMenu to its owner when
the action of an item has been changed.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_ACTION
:param2.
:item name='ItemID' type='USHORT'.
ID of the changed item.
:returns.
Nothing
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=615 name='UCN_CMITEM' .
This WM_CONTROL notification is sent to the owner of the UCMenu when the context menu receives
a WM_COMMAND message for one of the items added with :UCMENU_ADDITEMSTOCM..
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_CMITEM
:param2.
:item name='CMItemID' type='USHORT'.
ID of the context menu item selected.
:item name='ItemID' type='USHORT'.
ID of item over which the context menu was popped up.
:eparams.
:remarks.
The owner should process this message by executing the function associated
to the item he added.
:defproc.
No default processing
:related.
See :CMITEMS. type.
See :UCMENU_ADDITEMSTOCM.
See :UCMENU_DELETECMITEM.
:emessage.
.*---------------------------------------------------------------------------
:message res=616 name='UCN_MOUSEMOVE' .
This WM_CONTROL notification code is sent by the UCMenu to its owner when the mouse is moved over
its menu or submenu.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_MOUSEMOVE
:param2.
:item name='ItemID' type='USHORT'.
ID of the item over which the pointer is
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
:emessage.
.*----------------------------------------------------------------------------
:message res=617 name='UCN_HLP_NB_BMP' .
This WM_CONTROL notification is sent by the UCMenu to its owner when custom help is required
for the general page of the notebook.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_HLP_NB_BMP
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
UCS_CUSTOMHLP
:emessage.
.*----------------------------------------------------------------------------
:message res=618 name='UCN_HLP_NB_CREATE' .
This WM_CONTROL notification is sent by the UCMenu to its owner when custom help is required
for the create page of the notebook.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_HLP_NB_CREATE
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
UCS_CUSTOMHLP
:emessage.
.*----------------------------------------------------------------------------
:message res=619 name='UCN_HLP_NB_ACTION' .
This WM_CONTROL notification is sent by the UCMenu to its owner when custom help is required
for the action page of the notebook.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_HLP_NB_ACTION
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
UCS_CUSTOMHLP
:emessage.
.*----------------------------------------------------------------------------
:message res=620 name='UCN_HLP_STYLE' .
This WM_CONTROL notification is sent by the UCMenu to its owner when custom help is required
for the style dialog.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_HLP_NB_STYLE
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
UCS_CUSTOMHLP
:emessage.
.*----------------------------------------------------------------------------
:message res=621 name='UCN_HLP_DM' .
This WM_CONTROL notification is sent by the UCMenu to its owner when custom help is required
for the drag and drop.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_HLP_NB_DM
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
UCS_CUSTOMHLP
:emessage.
.*----------------------------------------------------------------------------
:message res=622 name='UCN_HLP_BUFFET' .
This WM_CONTROL notification is sent by the UCMenu to its owner when custom help is required
for the buffet toolbar dialog.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_HLP_NB_BUFFET
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
Nothing.
:eparams.
:remarks.
:defproc.
No default processing
:related.
UCS_CUSTOMHLP
:emessage.
.*----------------------------------------------------------------------------
:message res=623 name='UCN_QRYBUBBLEHELP'.
This WM_CONTROL notification is sent by the UCMenu to its owner to obtain
the bubble-help text associated with a particular menu item.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYBUBBLEHELP
:param2.
:item name='QueryData' type='QBUBBLEDATA *'.
Pointer to :QBUBBLEDATA. structure.  The :hp1.MenuItem:ehp1. field will contain
a pointer to the MENUITEM structure.  
:returns.
Nothing.
:eparams.
:remarks.
The application should fill in the :hp1.BubbleText:ehp1. pointer of the
:QBUBBLEDATA. structure.  :hp2.Note: This text string will be freed by
UCMenus so it must be a dynamically allocated string.:ehp2.
:p.
If the :hp1.BubbleText:ehp1. field is NULL then no bubble help window will be displayed.
:defproc.
No default processing
:related.
:emessage.
.*----------------------------------------------------------------------------
:message res=624 name='UCN_QRYCONTEXTHWND'.
This WM_CONTROL notification is sent by the UCMenu to its owner to obtain
the handle of an application-supplied context menu.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_QRYCONTEXTHWND
:param2.
:item name='MenuItem' type='MENUITEM *'.
Pointer to MENUITEM structure describing the item on which the context menu
was requested.  This structure will contain all binary zero values if
the pointer was not over a menu item when the context menu was requested.
:returns.
Nothing.
:eparams.
:remarks.
The application can ignore this message if the UCMenus built-in context menu is to
be used.  Otherwise it should supply the handle of a context menu to be
displayed.  Selections on the context menu will generate :UCN_CMITEM. messages.
:defproc.
No default processing
:related.
:emessage.
.*----------------------------------------------------------------------------
:message res=625 name='UCN_CHANGEDITEM'.
This WM_CONTROL notification is sent by the UCMenu to its owner
when a menu item has been changed and it is not possible to determine
which parts of the item were modified.
:params.
:param1.
:item name='UCMenuID' type='USHORT'.
ID of the UCMenu
:item name='NotifCode' type='USHORT'.
UCN_CHANGEDITEM
:param2.
:item name='ItemID' type='USHORT'.
ID of the menu item that changed.
:returns.
Nothing.
:eparams.
:remarks.
In general the application will get notification messages for specific changes
to menu items such as :UCN_ACTION..  However, when the MM_SETITEM message is used
to update a menu item it is not possible to determine exactly what components of
the item were changed and this message is generated.
Idefproc.
No default processing
:related.
:emessage.
.*-----------------------------------------------------------------------------------------------
:h1 toc=12.UCMenu Message Reference
.*-----------------------------------------------------------------------------------------------
This section describes all the messages an application can send to a UCMenu control
to set and query various options.
.*---------------------------------------------------------------------------
:message res=650 name='UCMENU_QUERYSIZE' .
This message is sent to the UCMenu to query the size it needs to be be fully displayed.
:params.
:param1.
:item name='pCx' type='PULONG'.
Pointer to a ULONG in which the width will be put.
:param2.
:item name='pCy' type='PULONG'.
Pointer to a ULONG in which the height will be put.
:returns.
:item name='Success' type='BOOL'.
:dl compact.
:dt.:hp2.TRUE:ehp2.
:dd.Query successful
:dt.:hp2.FALSE:ehp2.
:dd.Query Unsuccessful
:edl.
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=651 name='UCMENU_QUERYCOLOR' .
This message is sent to the UCMenu to query its color.
:params.
:param1.
:item name='pRGBColor' type='LONG *'.
Pointer to a LONG in which the RGB value of the UCMenu background color will be put.
:param2.
:item name='pItemRGBColor' type='LONG *'.
Pointer to a LONG in which the RGB value of the UCMenu items background color will be put.
:returns.
:item name='Success' type='BOOL'.
:dl compact.
:dt.:hp2.TRUE:ehp2.
:dd.Query successful
:dt.:hp2.FALSE:ehp2.
:dd.Query Unsuccessful
:edl.
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=652 name='UCMENU_QUERYFONT' .
This message is sent to the UCMenu to query its font.
:params.
:param1.
:item name='pszFontNameSize' type='PSZ'.
String in which the font  name and size will be put, allocated by the sender.
:p.The string returned has the format used in WinSetPresParam.
:param2.
:item name='Size' type='ULONG'.
Size of the string allocated by the sender
:returns.
:item name='Success' type='BOOL'.
:dl compact.
:dt.:hp2.TRUE:ehp2.
:dd.Query successful
:dt.:hp2.FALSE:ehp2.
:dd.Query Unsuccessful
:edl.
:eparams.
:remarks.
:defproc.
:related.
WinSetPresParam, WinQueryPresParam.
:emessage.
.*---------------------------------------------------------------------------
:message res=653 name='UCMENU_QUERYSTYLE' .
This message is sent to the UCMenu to query its style.
:params.
:param1.
:item name='pStyle' type='PULONG'.
Pointer to a ULONG in which the style will be put.
:p.The style is a combination of the UCS_* values.
:returns.
:item name='Success' type='BOOL'.
:dl compact.
:dt.:hp2.TRUE:ehp2.
:dd.Query successful
:dt.:hp2.FALSE:ehp2.
:dd.Query Unsuccessful
:edl.
:param2.
:item name='param2' type='ULONG'.
reserved
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=654 name='UCMENU_QUERYFORCEDSIZE' .
This message is sent to the UCMenu to query the value of its forced size
:params.
:param1.
:item name='pCx' type='PULONG'.
Pointer to a ULONG in which the width will be put.
:param2.
:item name='pCy' type='PULONG'.
Pointer to a ULONG in which the height will be put.
:returns.
:item name='Success' type='BOOL'.
:dl compact.
:dt.:hp2.TRUE:ehp2.
:dd.Query successful
:dt.:hp2.FALSE:ehp2.
:dd.Query Unsuccessful
:edl.
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=655 name='UCMENU_ADDITEMSTOCM' .
This user message can be sent to the UCMenu to add items to its context menu
:params.
:param1.
:item name='NbOfItems' type='ULONG'.
Number of items to add
:param2.
:item name='pCMItems' type='PCMITEMS'.
Pointer to a :CMITEMS. structure. It contains an ID and pszText for each item
added
:returns.
nothing
:item name='' type=''.
:eparams.
:remarks.
This message should be sent, since the caller has to free pszItemText in
the :CMITEMS. structure.
:defproc.
No default processing
:related.
See :CMITEMS. type.
See :UCMENU_DELETECMITEM.
:emessage.
.*---------------------------------------------------------------------------
:message res=656 name='UCMENU_DELETECMITEM' .
This user message can be sent to the UCMenu to delete items from its context menu
:params.
:param1.
:item name='NbOfItems' type='ULONG'.
Number of items to delete.
:param2.
:item name='pItemId' type='PULONG'.
Array of items ids.
:returns.
nothing
:eparams.
:remarks.
By default, the context menu has the following items &colon.
:dl compact.
:dt.:hp2.Edit&period.&period.&period.:ehp2.
:dd.IDM_UCM_EDIT
:dt.:hp2.Create&period.&period.&period.:ehp2.
:dd.IDM_UCM_CREATE
:dt.:hp2.Delete:ehp2.
:dd.IDM_UCM_DELETE
:dt.:hp2.Separator line:ehp2.
:dd.IDM_UCM_SEPARATOR
:dt.:hp2.Style&period.&period.&period.:ehp2.
:dd.IDM_UCM_STYLE
:dt.:hp2.Load Default:ehp2.
:dd.IDM_UCM_DEFAULT
:dt.:hp2.Import&period.&period.&period.:ehp2.
:dd.IDM_UCM_LOAD
:dt.:hp2.Export&period.&period.&period.:ehp2.
:dd.IDM_UCM_SAVEAS
:edl.
:defproc.
No default processing
:related.
See :CMITEMS. type
See :UCMENU_ADDITEMSTOCM.
See :UCN_CMITEM.
:emessage.
.*---------------------------------------------------------------------------
:message res=657 name='UCMENU_QUERYVERSION' .
This user message is sent to the UCMenu to query the version of the UCMenus dll
:params.
:param1.
:item name='param1' type='ULONG'.
Reserved
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
:item name='version' type='ULONG'.
Version number of the dll, eg 2 for 0.02 and 100 for 1.00.
:eparams.
:remarks.
:defproc.
No default processing
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=658 name='UCMENU_SETSTYLE' .
This message is sent to the UCMenu to set the style flags and the associated width
and height values.
:params.
:param1.
:item name='StyleFlags' type='ULONG'.
Combination of UCS_* flags.
:param2.
:item name='cx' type='USHORT'.
The width of the items if UCS_FORCESIZE is set.
:item name='cy' type='USHORT'.
The height of the items if UCS_FORCESIZE is set.
:returns.
:item name='Success' type='BOOL'.
TRUE if successful, FALSE else.
:eparams.
:remarks.
A :UCMENU_UPDATE. message must be issued in order to reflect the changes.
:defproc.
:related.
:UCMENU_UPDATE.
:emessage.
.*---------------------------------------------------------------------------
:message res=659 name='UCMENU_QUERYUCMINFO' .
This message is sent to the UCMenu to retrieve the :UCMINFO. structure
:params.
:param1.
:item name='pUCMInfo' type='PUCMINFO'.
Pointer to the :UCMINFO. structure to fill.
:param2.
:item name='param2' type='ULONG'.
reserved.
:returns.
:item name='Success' type='BOOL'.
TRUE if successful, FALSE else.
:eparams.
:remarks.
If the PSZ fields are not null, they have been allocated by
the UCMenu and have to be freed with UCMenuFree by the sender.
:defproc.
No default processing
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=660 name='UCMENU_UPDATE' .
This message is sent to the UCMenu to display the changes made.
:params.
:param1.
:item name='param1' type='ULONG'.
reserved.
:param2.
:item name='param2' type='ULONG'.
reserved.
:returns.
:item name='Success' type='BOOL'.
TRUE if successful, FALSE else.
:eparams.
:remarks.
:defproc.
No default processing
:related.
:UCMENU_SETSTYLE.
:UCMENU_SETBGCOLOR.
:emessage.
.*---------------------------------------------------------------------------
:message res=661 name='UCMENU_SETBGCOLOR' .
This message is sent to the UCMenu to set the UCMenu background color
:params.
:param1.
:item name='BgColor' type='ULONG'.
The RGB color which will be used for the UCMenu background.
:param2.
:item name='ItemBgColor' type='ULONG'.
The RGB color which will be used for the items background.
:returns.
:item name='Success' type='BOOL'.
TRUE if successful, FALSE else.
:eparams.
:remarks.
:defproc.
No default processing
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=662 name='UCMENU_SETFONT' .
This message is sent to the UCMenu to set the UCMenu font.
:params.
:param1.
:item name='FontNameSize' type='PSZ'.
Font name, such as used in WinSetPresParam.
:param2.
:item name='-' type='ULONG'.
Reserved.
:returns.
:item name='Success' type='BOOL'.
TRUE if successful, FALSE else.
:eparams.
:remarks.
:defproc.
No default processing
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=663 name='UCMENU_ACTIONSINSERTED' .
This message is posted to the UCMenu by its owner when it has filled
the list of actions
:params.
:param1.
:item name='param1' type='ULONG'.
Reserved.
:param2.
:item name='param2' type='ULONG'.
Reserved
:returns.
nothing
:eparams.
:remarks.
:defproc.
:related.
:UCMENU_INSERTACTION.
:emessage.
.*---------------------------------------------------------------------------
:message res=664 name='UCMENU_INSERTACTION' .
This message is sent to the UCMenu by its owner after it received :UCN_QRYACTIONLIST..
:params.
:param1.
:item name='Action' type='PSZ'.
String including the name of the action eventually followed by parameters.
:param2.
:item name='Description' type='PSZ'.
A description of the action.
:returns.
nothing
:eparams.
:remarks.
This message has to be sent, not posted to the UCMenus control.
:defproc.
:related.
:UCN_QRYACTIONLIST.
:emessage.
.*---------------------------------------------------------------------------
:message res=665 name='UCMENU_SETBUBBLETIMERS'.
This message is sent to the UCMenu by its owner to set the time delays
associated with the bubble-help feature (UCS_BUBBLEHELP style).
:params.
:param1.
:item name='HoverDelay' type='ULONG'.
Number of msec pointer must hover over the same menu item before
the bubble help is displayed.  Maximum of 65000 msec (65 seconds).
:param2.
:item name='ReadTime' type='ULONG'.
Number of msec bubble help will be visible while pointer remains
over the same menu item.  Bubble help is removed when the
pointer leaves the UCMenu toolbar if this time has not
expired yet.  Maximum of 65000 msec (65 seconds).
:returns.
nothing
:eparams.
:remarks.
:defproc.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=666 name='UCMENU_ACTIVECHG'.
This message is sent to the UCMenu by its owner
whenever the frame window in which the menu exists becomes active
or inactive.
:params.
:param1.
:item name='Activated' type='BOOL'.
TRUE if the window is being activated, FALSE if being deactivated.
:param2.
Reserved.
:returns.
Nothing
:eparams.
:remarks.
The owner must send this message whenever the window frame in which the
toolbar exists becomes active or inactive.
:sample.
  // Owner must notify toolbar on active status changes:

  case WM_ACTIVATE:
    /* Tell toolbar we are becoming active or inactive */
    WinSendMsg(ToolHwnd, UCMENU_ACTIVECHG, mp1, MPVOID);
    break;
:esample.
:related.
:emessage.
.*---------------------------------------------------------------------------
:message res=667 name='UCMENU_DISABLEUPDATE'.
This message is sent to the UCMenu by its owner
to disable updates to the toolbar window while items are inserted,
deleted, or modified.
:params.
:param1.
:item name='Disable' type='BOOL'.
TRUE if updates are to be disabled, FALSE if they are to be shown.
:param2.
Reserved.
:returns.
Nothing
:eparams.
:remarks.
This message can be used to improve performance when more than one
menu item will be inserted, deleted, or modified.  The menu will
not be visually updated when :hp1.Disable:ehp1. is TRUE.  Updates
will be shown when :hp1.Disable:ehp1. is FALSE.
:p.
Note that a :UCMENU_UPDATE. message :hp2.must:ehp2. be sent after
the menu is disabled and then enabled to insure proper update
if the window.
:related.
:emessage.
.*---------------------------------------------------------------------------
.* API Reference
.*---------------------------------------------------------------------------
:h1.Programming Interfaces (API)
This section describes each of the callable UCMenu programming interfaces.
.*---------------------------------------------------------------------------
.* IPFCPREP macros used for message reference entries
.*---------------------------------------------------------------------------
.dm function on
:h2 res=&res..&name.
.**** to produce link tags: .dm &name. on :link reftype=hd res=&res..&name.:elink.
.dm off
.*----------------
.dm syntax on
:p.
:hp7.Syntax&colon.:ehp7.
.br
:lines.
:font facename='System Monospaced' size=12x10.
:hp4.&return. &name.(&params.):ehp4.
:font facename=default size=0x0.
:elines.
.dm off
.*----------------
.dm fparams on
:font facename='System Monospaced' size=12x10.
:table cols='15 10 10 50' rules=both frame=box.
:row.
:c.:hp1.Name:ehp1.
:c.:hp1.Type:ehp1.
:c.:hp1.In/Out:ehp1.
:c.:hp1.Description:ehp1.
.dm off
.*----------------
.dm fparam on
:row.
:c.&name.
:c.&type.
:c.&io.
:c.
.dm off
.*----------------
.dm freturns on
:etable.
:font facename=default size=0x0.
:hp1.Returns:ehp1.
:font facename='System Monospaced' size=12x10.
:table cols='15 10 10 50' rules=both frame=box.
.dm off
.*----------------
.dm efparams on
:etable.
:font facename=default size=0x0.
.dm off
.*----------------
.dm efunction on
.dm off
.*----------------
.*--------------------------------------------------------------------------
.*-------------------------------------------------------------------------
:function res=200 name='UCMenuCreateFromResource' text='Create a UCMenu from a resource menu'.
This function creates a UCMenu using a menu template stored in the resources.
:syntax name='UCMenuCreateFromResource' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID hmodResource usMenuID pUCMInfo phTextMenu' return='hUCMenu' .
:fparams.
:fparam name='hab' type='HAB' io='input' .
Handle of the anchor-block.
:fparam name='hParent' type='HWND' io='input' .
Handle of the parent window
:fparam name='hOwner' type='HWND' io='input' .
Handle of the owner window
:fparam name='flStyle' type='ULONG' io='input' .
Style flags of the UCMenu window, combination of WS_ flags and CMS_VERT, CMS_HORZ, CMS_MATRIX, CMS_MATRIX_VERT, CMS_MATRIX_HORZ
:fparam name='x' type='ULONG' io='input'.
x coordinate of UCMenu window position
:fparam name='y' type='ULONG' io='input'.
y coordinate of UCMenu window position
:fparam name='cx' type='ULONG' io='input'.
width of the UCMenu window, ignored if vertical or matrix UCMenu
:fparam name='cy' type='ULONG' io='input'.
height of the UCMenu window, ignored if horizontal or matrix UCMenu
:fparam name='hInsertBehind' type='ULONG' io='input'.
Sibling window behind which the UCMenu is placed, can also be HWND_TOP or HWND_BOTTOM.
:fparam name='ulID' type='ULONG' io='input'.
ID given to the UCMenu.
:fparam name='hmodResource' type='HMODULE' io='input'.
Handle of the module where the menu resource is to be found.
:fparam name='usMenuID' type='USHORT' io='input'.
ID of the resource menu used as a template to create the UCMenu.
:fparam name='pUCMInfo' type='PUCMINFO' io='input'.
Pointer to the :UCMINFO. UCMenu creation structure
:fparam name='phTextMenu' type='PHWND' io='output'.
Handle of the menu loaded from the resource.
It should normally not be used.
:freturns.
:fparam name='hUCMenu' type='PSZ' io='return'.
Handle of the UCMenu or NULLHANDLE if the creation failed.
:efparams.
:remarks.
:related.
:UCMINFO. data structure
.*-------------------------------------------------------------------------
:function res=201 name='UCMenuCreateFromHMenu' text='Create a UCMenu from a menu handle'.
This function creates a UCMenu using an already loaded or created PM text menu.
:syntax name='UCMenuCreateFromHMenu' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID  hMenu pUCMInfo' return='hUCMenu'.
:fparams.
:fparam name='hab' type='HAB' io='input' .
Handle of the anchor-block.
:fparam name='hParent' type='HWND' io='input' .
Handle of the parent window
:fparam name='hOwner' type='HWND' io='input' .
Handle of the owner window
:fparam name='flStyle' type='ULONG' io='input' .
Style flags of the UCMenu window, combination of WS_ flags and CMS_VERT, CMS_HORZ, CMS_MATRIX, CMS_MATRIX_VERT, CMS_MATRIX_HORZ
:fparam name='x' type='ULONG' io='input'.
x coordinate of UCMenu window position
:fparam name='y' type='ULONG' io='input'.
y coordinate of UCMenu window position
:fparam name='cx' type='ULONG' io='input'.
width of the UCMenu window, ignored if vertical or matrix UCMenu
:fparam name='cy' type='ULONG' io='input'.
height of the UCMenu window, ignored if horizontal or matrix UCMenu
:fparam name='hInsertBehind' type='ULONG' io='input'.
Sibling window behind which the UCMenu is placed, can also be HWND_TOP or HWND_BOTTOM.
:fparam name='ulID' type='ULONG' io='input'.
ID given to the UCMenu.
:fparam name='hMenu' type='HWND' io='input'.
Handle of the PM menu used as a template to create the UCMenu
:fparam name='pUCMInfo' type='PUCMINFO' io='input'.
Pointer to the :UCMINFO. UCMenu creation structure
:freturns.
:fparam name='hUCMenu' type='PSZ' io='return'.
Handle of the UCMenu or zero if the creation failed.
:efparams.
:remarks.
Note that the passed menu handle is the handle of a standard PM
menu, not a UCMenu.  This function can be used to create an empty UCMenu
by first creating an empty PM menu as shown in the example below.
:sample.
 // Create empty UCMenu from an empty PM menu

 PMMenu = WinCreateWindow(hwnd,   // parent
               WC_MENU,           // PM menu class
                "",               // no window text
                MS_ACTIONBAR,     // window style
                0,0,0,0,          // UCMenu will set size
                hwnd,             // owner
                HWND_TOP,         // top of siblings
                0,                // ID of the control
                NULL,             // No ctl data -> empty menu
                NULL);            // No pres parms
 UCMenu = UCMenuCreateFromHMenu(hab,
                hwnd,             // parent
                hwnd,             // owner to get msgs
                CMS_HORZ,         // Orientation (CMS_* flags)
                0,0,0,0,          // Sizing will be done by UCMenu
                HWND_TOP,         // Put on top of siblings
                ID_COPYMENU,      // ID new menu will have
                PMMenu,           // Handle of menu to use for template
                &amp.UCMInfo);        // Initialization data structure
:esample.
:related.
:UCMINFO. data structure
.*-------------------------------------------------------------------------
:function res=202 name='UCMenuCreateFromTemplate' text='Create a UCMenu from a menu template'.
This function creates a UCMenu using an already loaded UCMenu template
previously created by the :UCMenuMakeTemplate. function.
:syntax name='UCMenuCreateFromTemplate' params='hab hParent hOwner ulStyle x y cx cy hInsertBehind ulID pMenuTemplate pUCMInfo phTextMenu' return='hUCMenu' .
:fparams.
:fparam name='hab' type='HAB' io='input' .
Handle of the anchor-block.
:fparam name='hParent' type='HWND' io='input' .
Handle of the parent window
:fparam name='hOwner' type='HWND' io='input' .
Handle of the owner window
:fparam name='flStyle' type='ULONG' io='input' .
Style flags of the UCMenu window, combination of WS_ flags and CMS_VERT, CMS_HORZ, CMS_MATRIX, CMS_MATRIX_VERT, CMS_MATRIX_HORZ
:fparam name='x' type='ULONG' io='input'.
x coordinate of UCMenu window position
:fparam name='y' type='ULONG' io='input'.
y coordinate of UCMenu window position
:fparam name='cx' type='ULONG' io='input'.
width of the UCMenu window, ignored if vertical or matrix UCMenu
:fparam name='cy' type='ULONG' io='input'.
height of the UCMenu window, ignored if horizontal or matrix UCMenu
:fparam name='hInsertBehind' type='ULONG' io='input'.
Sibling window behind which the UCMenu is placed, can also be HWND_TOP or HWND_BOTTOM.
:fparam name='ulID' type='ULONG' io='input'.
ID given to the UCMenu.
:fparam name='pmtMenuTemplate' type='PVOID' io='input'.
Pointer to the menu template in binary format
:fparam name='pUCMInfo' type='PUCMINFO' io='input'.
Pointer to the :UCMINFO. UCMenu creation structure
:fparam name='phTextMenu' type='PHWND' io='output'.
Handle of the menu loaded from the resource.
It should normally not be used.
:freturns.
:fparam name='hUCMenu' type='PSZ' io='return'.
Handle of the UCMenu or NULLHANDLE if the creation failed.
:efparams.
:remarks.
Note that the template is a :hp1.UCMenu:ehp1. template which is not
the same as a PM menu template.  The templated passed in much have
been created by a UCMenu template-creation function such as :UCMenuMakeTemplate..
:related.
:UCMINFO. data structure
:UCMenuMakeTemplate.
:UCMenuSaveTemplate.
:UCMenuLoadTemplate.
:UCMenuSaveTemplateIni.
:UCMenuLoadTemplateIni.
.*-------------------------------------------------------------------------
:function res=203 name='UCMenuLoadBitmap' text='Loads a bitmap'.
This function loads a bitmap from a file and returns its handle.
:syntax name='UCMenuLoadBitmap' params='pszFileName' return='hBitmap' .
:fparams.
:fparam name='pszFileName' type='PSZ' io='input' .
Name of the file to load.
:freturns.
:fparam name='hBitmap' type='LONG' io='return'.
Bit-map handle (0 if error)
:efparams.
:remarks.
If the bitmap file contains multiple resolutions, the bitmap the most appropriate to the
current display will be chosen.
:related.
.*-------------------------------------------------------------------------
:function res=204 name='UCMenuMakeTemplate' text='Builds a menu template'.
This function builds the UCMenu menu template associated with a specified UCMenu.
Note that a UCMenu menu template
is a binary data structure whose internal format is known and
understood only by UCMenus.  UCMenus templates should not be used to create
standard PM menus, and PM menu templates cannot be used to create a UCMenu.
:syntax name='UCMenuMakeTemplate' params='hwndUCMenu, pBufLen' return='pBuffer' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pBufLen' type='PULONG' io='output' .
Pointer to the UCMenu template buffer length.
:freturns.
:fparam name='pBuffer' type='PVOID' io='return'.
Pointer to the template (NULL if error), has to be freed by the caller with UCMenuFree.
:efparams.
:remarks.
:related.
:UCMenuCreateFromTemplate.
:UCMenuSaveTemplate.
:UCMenuLoadTemplate.
:UCMenuSaveTemplateIni.
:UCMenuLoadTemplateIni.
.*-------------------------------------------------------------------------
:function res=205 name='UCMenuSaveTemplate' text='Saves a menu template'.
This function builds and saves a UCMenu menu template.
Note that a UCMenu menu template
is a binary data structure whose internal format is known and
understood only by UCMenus.  UCMenus templates should not be used to create
standard PM menus, and PM menu templates cannot be used to create a UCMenu.
:syntax name='UCMenuSaveTemplate' params='hwndUCMenu, pszFileName' return='bRc' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:freturns.
:fparam name='bRc' type='BOOL' io='return'.
FALSE if an error occurred.
:efparams.
:remarks.
:related.
:UCMenuCreateFromTemplate.
:UCMenuMakeTemplate.
:UCMenuLoadTemplate.
:UCMenuSaveTemplateIni.
:UCMenuLoadTemplateIni.
.*-------------------------------------------------------------------------
:function res=206 name='UCMenuLoadTemplate' text='Loads a menu template'.
This function loads a UCMenu menu template from a file.
Note that a UCMenu menu template
is a binary data structure whose internal format is known and
understood only by UCMenus.  UCMenus templates should not be used to create
standard PM menus, and PM menu templates cannot be used to create a UCMenu.
:syntax name='UCMenuLoadTemplate' params='pszFileName, pBufLen' return='pBuffer' .
:fparams.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:fparam name='pBufLen' type='PULONG' io='output' .
Pointer to the length of the allocated buffer.
:freturns.
:fparam name='pBuffer' type='PVOID' io='input' .
Pointer to a buffer (NULL if error).
:hp2.Note&colon.:ehp2. The buffer must be freed by the caller using the UCMenuFree() function.
:efparams.
:remarks.
:related.
:UCMenuCreateFromTemplate.
:UCMenuMakeTemplate.
:UCMenuSaveTemplate.
:UCMenuSaveTemplateIni.
:UCMenuLoadTemplateIni.
.*-------------------------------------------------------------------------
:function res=207 name='UCMenuSaveTemplateIni' text='Saves a menu template'.
This function builds and saves a UCMenu menu template in an ini file.
Note that a UCMenu menu template
is a binary data structure whose internal format is known and
understood only by UCMenus.  UCMenus templates should not be used to create
standard PM menus, and PM menu templates cannot be used to create a UCMenu.
:syntax name='UCMenuSaveTemplateIni' params='hwndUCMenu, pszFileName, pszKeyName' return='bRc' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:fparam name='pszKeyName' type='PSZ' io='input' .
Template name (NULL-terminated string)
:freturns.
:fparam name='bRc' type='BOOL' io='return'.
FALSE if an error occurred.
:efparams.
:remarks.
:related.
:UCMenuCreateFromTemplate.
:UCMenuMakeTemplate.
:UCMenuSaveTemplate.
:UCMenuLoadTemplate.
:UCMenuLoadTemplateIni.
.*-------------------------------------------------------------------------
:function res=208 name='UCMenuLoadTemplateIni' text='Loads a menu template'.
This function loads a UCMenu menu template from an ini file.
Note that a UCMenu menu template
is a binary data structure whose internal format is known and
understood only by UCMenus.  UCMenus templates should not be used to create
standard PM menus, and PM menu templates cannot be used to create a UCMenu.
:syntax name='UCMenuLoadTemplateIni' params='pszFileName, pszKeyName, pBufLen' return='pBuffer' .
:fparams.
:fparam name='pszFileName' type='PSZ' io='input' .
Ini File name (NULL-terminated string)
:fparam name='pszKeyName' type='PSZ' io='input' .
Template name (NULL-terminated string)
:fparam name='pBufLen' type='PULONG' io='output' .
Pointer to the length of the allocated buffer.
:freturns.
:fparam name='pBuffer' type='PVOID' io='input' .
Pointer to a buffer (NULL if error).
:hp2.Note&colon.:ehp2. The buffer must be freed by the caller using the UCMenuFree() function.
:efparams.
:remarks.
:related.
:UCMenuCreateFromTemplate.
:UCMenuMakeTemplate.
:UCMenuSaveTemplate.
:UCMenuLoadTemplate.
:UCMenuSaveTemplateIni.
.*-------------------------------------------------------------------------
:function res=209 name='UCMenuSaveStyle' text='Saves a menu style'.
This function saves various UCMenu style-related information to a file.
:syntax name='UCMenuSaveStyle' params='hwndMenu, pszFileName' return='bRC' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:freturns.
:fparam name='bRC' type='BOOL' io='return'.
FALSE if an error occurred.
:efparams.
:remarks.
The following items are saved in the file:
:ul compact.
:li.Style flags
:li.Current size (cx, cy)
:li.Background color
:li.Button face background color
:li.Font name and size
:eul.
:related.
:UCMenuLoadStyle.
:UCMenuLoadStyleIni.
:UCMenuSaveStyleIni.
.*-------------------------------------------------------------------------
:function res=210 name='UCMenuLoadStyle' text='Loads a menu style'.
This function loads a menu style from a file into a :UCMINFO. UCMenu
creation structure.
:syntax name='UCMenuLoadStyle' params='pszFileName, pUCMInfo' return='bSuccess'.
:fparams.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:fparam name='pUCMInfo' type='UCMINFO *' io='output' .
Pointer to the :UCMINFO. structure in which to load the style
:freturns.
:fparam name='bSuccess' type='BOOL' io='return' .
FALSE if an error occurred.
:efparams.
:remarks.
:related.
:UCMenuSaveStyle.
:UCMenuLoadStyleIni.
:UCMenuSaveStyleIni.
.*-------------------------------------------------------------------------
:function res=211 name='UCMenuSaveStyleIni' text='Saves a menu style'.
This function saves the information relative to the style of a UCMenu in an ini file.
:syntax name='UCMenuSaveStyleIni' params='hwndMenu, pszFileName, pszKeyName' return='bRC' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:fparam name='pszKeyName' type='PSZ' io='input' .
Style name (NULL-terminated string)
:freturns.
:fparam name='bRC' type='BOOL' io='return'.
FALSE if an error occurred.
:efparams.
:remarks.
The following items are saved:
:ul compact.
:li.Style flags
:li.Current size (cx, cy)
:li.Background color
:li.Button face background color
:li.Font name and size
:eul.
:related.
:UCMenuLoadStyle.
:UCMenuSaveStyle.
:UCMenuLoadStyleIni.
.*-------------------------------------------------------------------------
:function res=212 name='UCMenuLoadStyleIni' text='Loads a menu style'.
This function loads a menu style from an ini file into a UCMInfo UCMenu
creation structure.
:syntax name='UCMenuLoadStyleIni' params='pszFileName, pszKeyName, pUCMInfo' return='bSuccess'.
:fparams.
:fparam name='pszFileName' type='PSZ' io='input' .
File name (NULL-terminated string)
:fparam name='pszKeyName' type='PSZ' io='input' .
Style name (NULL-terminated string)
:fparam name='pUCMInfo' type='UCMINFO *' io='output' .
Pointer to the UCMInfo structure in which to load the style
:freturns.
:fparam name='bSuccess' type='BOOL' io='return' .
FALSE if an error occurred.
:efparams.
:remarks.
:related.
:UCMenuLoadStyle.
:UCMenuSaveStyle.
:UCMenuSaveStyleIni.
.*-------------------------------------------------------------------------
:function res=213 name='UCMenuFreeMenuData' text='Frees the menu data'.
This function frees the data associated with the OWNERDRAW items of a menu.
:syntax name='UCMenuFreeMenuData' params='hwndMenu' return='-' .
:fparams.
:fparam name='hwndMenu' type='HWND' io='input' .
Menu window handle.
:freturns.
:fparam name='-' type='VOID' io='-'.
Nothing.
:efparams.
:remarks.
This function parses the whole menu (including submenus). It frees the
data structure associated with every OWNERDRAW item.
:p.This function requires the owner of the menu to be the UCMenu.
:hp2.Note&colon.:ehp2. This function is automatically executed when a UCMenu receives a WM_DESTROY message.
:related.
.*-------------------------------------------------------------------------
:function res=214 name='UCMenuIdFromCoord' text='Get the ID of a specified menu item' .
This function returns the id of the menu item that is at a specified position.
:syntax name='UCMenuIdFromCoord' params='hwndMenu, pptrPos' return='ItemID' .
:fparams.
:fparam name='hwndMenu' type='HWND' io='input' .
Menu window handle.
:fparam name='pptrPos' type='PPOINTL' io='input' .
Position
:freturns.
:fparam name='ItemID' type='USHORT' io='return'.
The item Identifier. 0 if not found.
:efparams.
:remarks.
This function doesn't check the submenus. However, you can identify an item in a submenu
if you pass the hwnd of the submenu.
:related.
.*-------------------------------------------------------------------------
:function res=215 name='UCMenuGetActionID' text='Get the IDs corresponding to an action' .
This function returns the ID of the item with a pszAction action, starting at the item sStart.
:syntax name='UCMenuGetActionID' params='hwndUCM, pszAction, , bSubmenus, sStart ' return='FoundID' .
:fparams.
:fparam name='hwndUCM' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pszAction' type='PSZ' io='input' .
Action string to look for
:fparam name='bSubmenus' type='BOOL' io='input' .
Look in submenus or not.
:fparam name='Start' type='SHORT' io='input' .
Item ID to start with, MIT_FIRST for the beginning.
:freturns.
:fparam name='FoundID' type='SHORT' io='return'.
Item ID found, or MIT_NONE
:efparams.
:remarks.
Note that more than one item in the menu may have the same action string.  This function
can be used to enumerate all the items in the menu with a particular action string.
:related.
.*-------------------------------------------------------------------------
:function res=216 name='UCMenuSetActionAttr' text='Get the IDs corresponding to an action' .
This function sets the attributes of the items with the given action string.
:syntax name='UCMenuSetActionAttr' params='hwndUCM, pszAction, usAttrMask, usAttrValue' return='void' .
:fparams.
:fparam name='hwndUCM' type='HWND' io='input' .
UCMenu window handle.
:fparam name='pszAction' type='PSZ' io='input' .
Action string to look for
:fparam name='usAttrMask' type='USHORT' io='input' .
Attribute mask to use
:fparam name='usAttrValue' type='USHORT' io='input' .
Attribute value to set
:freturns.
:fparam name='-' type='VOID' io='return'.
Nothing
:efparams.
:remarks.
A UCMenu may have more than one item with the same action string.  This function
will set the given attribte on all items in the menu with the given action string.
:related.
.*-------------------------------------------------------------------------
:function res=217 name='UCMenuLoadDefault' text='Loads the default new UCMenu'.
This function updates the UCMenu with the default template.
:syntax name='UCMenuLoadDefault' params='hwndUCMenu' return='bSuccess' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
Handle of the UCMenu
:freturns.
:fparam name='bSuccess' type='BOOL' io='return'.
True if successful, FALSE else
:efparams.
:remarks.
This call will cause the UCMenu to send a :UCN_QRYDEFTEMPLATE. or :UCN_QRYDEFTEMPLATEID.
message to the owner to get the default template to be loaded.
:related.
.*-------------------------------------------------------------------------
:function res=218 name='UCMenuNew' text='Loads a new menu in the UCMenu'.
This function updates the UCMenu with a new template.  Note that the template
is a UCMenus template created with one of the UCMenu template functions (such
as :UCMenuMakeTemplate.).  A PM menu template may not be used.
:syntax name='UCMenuNew' params='hwndUCMenu, pTemplate' return='bSuccess' .
:fparams.
:fparam name='hwndUCMenu' type='HWND' io='input' .
Handle of the UCMenu
:fparam name='pTemplate' type='PVOID' io='input' .
Template of the new menu.
:freturns.
:fparam name='bSuccess' type='BOOL' io='return'.
True if successful, FALSE else
:efparams.
:remarks.
:related.
.*-------------------------------------------------------------------------
:function res=219 name='UCMenuResourceBuffetDlg' text='Toolbar customization dialog'.
This dialog let the user pick items from a buffet toolbar coming from a resource.
:syntax name='UCMenuResourceBuffetDlg' params='hParent, hUCMenu, ulBuffetID, hmodBuffet' return='-' .
:fparams.
:fparam name='hParent' type='HWND' io='input' .
Parent of the dialog.
:fparam name='hUCMenu' type='HWND' io='input' .
Handle of the UCMenu to modify.
:fparam name='ulBuffetID' type='ULONG' io='input' .
ID of the buffet menu.
:fparam name='hmodBuffet' type='HMODULE' io='input' .
Module where the buffet menu is.
:freturns.
:fparam name='ulResult' type='ULONG' io='return'.
result of WinDglBox
:efparams.
:remarks.
:p.
The purpose of this call is to allow easy drag-and-drop customization of a
UCMenu.  A dialog will be displayed which contains two UCMenus (the buffet menu
and the menu to be customized).  The user can drag items from the buffet and
add them to the menu, and they can drag items from the menu to a shredder icon
to delete them.
:p.
The application supplies (via the :hp1.ulBuffetID:ehp1. menu) the list of
menu items the user can choose from.  The user cannot change the bitmaps or
action strings of the menu items, nor can they add new items not supplied by
the application.
:p.
When the user selects the :hp1.OK:ehp1. button on the buffet dialog, the UCMenu
represented by :hp1.hUCMenu:ehp1. is updated.  If the user cancels, the menu
is not affected.  When a menu is updated via the buffet dialog, all the current
items of the menu will be deleted, followed by insertion of the new items.
Applications which monitor the insert and delete of menu items should be
prepared to handle this mass-delete and mass-insert which occurs when the menu is
updated via the buffet dialog.
:related.
.*-------------------------------------------------------------------------
:function res=230 name='UCMenuTemplateBuffetDlg' text='Toolbar customization dialog'.
This dialog let the user pick items from a buffet toolbar coming from a template.  Note
that this template is a UCMenus template created by one of the UCMenu template
functions.  It is not a PM menu template.
:syntax name='UCMenuTemplateBuffetDlg' params='hParent, hUCMenu, pTemplate' return='-' .
:fparams.
:fparam name='hParent' type='HWND' io='input' .
Parent of the dialog.
:fparam name='hUCMenu' type='HWND' io='input' .
Handle of the UCMenu to modify.
:fparam name='pTemplate' type='PVOID' io='input' .
Template of the buffet menu
:freturns.
:fparam name='ulResult' type='ULONG' io='return'.
result of WinDglBox
:efparams.
:remarks.
:related.
.*-------------------------------------------------------------------------
:function res=231 name='UCMenuGetVersion' text='Get the version of the toolbar'.
This function returns the version of the UCMenus code.
:syntax name='UCMenuGetVersion' params='-' return='ulVersion' .
:fparams.
:freturns.
:fparam name='ulVersion' type='ULONG' io='return'.
version of the UCMenus.
:efparams.
:remarks.
:related.
.*-------------------------------------------------------------------------
:function res=232 name='UCMenuAlloc' text='Malloc used by UCMenus'.
External entry point to the allocation routine used by the UCMenus.
:syntax name='UCMenuAlloc' params='size' return='PVOID' .
:fparams.
:fparam name='size' type='size_t' io='input' .
Size to allocate.
:freturns.
:fparam name='pMem' type='PVOID' io='return'.
Pointer to the allocated memory or 0 if failure.
:efparams.
:remarks.
Strings and structures which may passed to UCMenus should use the
UCMenu memory allocation functions.
:related.
:UCMenuFree.
:UCMenuStrdup.
.*-------------------------------------------------------------------------
:function res=233 name='UCMenuStrdup' text='Duplication string used by UCMenus'.
Allocates and copies string using UCMenu memory allocation.
:syntax name='UCMenuStrdup' params='string' return='PSZ'.
:fparams.
:fparam name='string' type='PSZ' io='input' .
String to be copied.
:freturns.
:fparam name='copy' type='PSZ' io='return'.
Pointer to the copied string or 0 if failure.
:efparams.
:remarks.
Strings and structures which may passed to UCMenus should use the
UCMenu memory allocation functions.
:related.
:UCMenuFree.
:UCMenuAlloc.
.*-------------------------------------------------------------------------
:function res=234 name='UCMenuFree' text='Free used by the UCMenus'.
External entry point to the freeing routine used by the UCMenus.
:syntax name='UCMenuFree' params='pMem' return='-' .
:fparams.
:fparam name='pMem' type='PVOID' io='input' .
Pointer to free.
:freturns.
:fparam name='-' type='VOID' io='-'.
Nothing.
:efparams.
:remarks.
:related.
:UCMenuAlloc.
:UCMenuStrdup.
.*-------------------------------------------------------------------------
:function res=235 name='UCMenuItemDup' text='Duplicate UCMITEM structure and strings'.
Allocate storage for, and copy a :UCMITEM. structure including the strings it contains.
Any of the string pointers may be NULL.
:syntax name='UCMenuItemDup' params='UCMItem' return='UCMITEM *'.
:fparams.
:fparam name='UCMItem' type='UCMITEM *' io='input' .
Pointer to :UCMITEM. structure which is to be duplicated.
:freturns.
:fparam name='NewItem' type='UCMITEM *' io='returns'.
Returns a pointer to the new :UCMITEM. structure.  The structure will be filled with
strings duplicated from the original :UCMITEM. structure.
:efparams.
:remarks.
Note that the structure as well as the string pointes are duplicated by this function.
:related.
:UCMenuAlloc.
:UCMenuStrdup.
.*-------------------------------------------------------------------------
:function res=236 name='UCMenuItemFree' text='Free UCMITEM strings and storage'.
Free all strings in a :UCMITEM. structure and then free the storage for the structure itself.
Any of the string pointers may be NULL.
:syntax name='UCMenuItemFree' params='UCMItem' return='void'.
:fparams.
:fparam name='UCMItem' type='UCMITEM *' io='input' .
Pointer to :UCMITEM. structure which contains pointers to strings to be freed.
:freturns.
:fparam name='-' type='VOID' io='-'.
Nothing.
:efparams.
:remarks.
Note that the structure as well as the string pointes are freed by this function.
:related.
:UCMenuAlloc.
:UCMenuStrdup.
:euserdoc.
