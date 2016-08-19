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

Description:
------------
The User Customizable Menu (UCMenu) is a very powerful "toolbar" custom
PM control.  It allows the user to define the ordering of menu items and
visual representation (artwork and text) of menu items.   Most
customization functions are encapsulated inside the control itself,
greatly reducing the application code needed to support a customizable
toolbar.  Extensive use is made of direct manipulation for a smooth
integration with the OS/2 Workplace Shell.  For example, to reorder
items on the toolbar, the user can just drag/drop items into new
positions.  Dragging a toolbar item to the shredder will delete it.  A
context menu gives quick access to other customization functions.

This package contains the complete UCMenu custom PM control including
all source code.  It also includes several working sample programs that
demonstrate the appearence and operation of the toolbar.  Also
included is a programmers toolkit reference in OS/2 VIEW format.

This control was described in an artical in OS/2 Developer magazine,
Jan/Feb 1995, page 50.

Version Notice:
---------------
This is Version 2.12 of UCMenus and completely replaces earlier versions
which have been made available through various means.  Version 2.12
is source-level compatible with with 2.0 but not binary compatible.

NOTE: Unlike prior versions of the toolkit, compiled .OBJ and .DLL files
are no longer included.  You should build your own copy of the executable
files using your own compiler.  See the online reference for instructions
on building the OBJ and DLL files.

Installing the UCMenus Toolkit:
-------------------------------
To install this toolkit, run the UCMINST.CMD program from an OS/2
command line.  Supply the name of a directory for installation when
prompted.  All the toolkit files and samples will be placed into
the specified directory.

The toolkit directory structure created will be as follows (assuming
the main toolkit directory is \UCMENUS):

   \UCMENUS          -- Main directory, misc files like READ.ME
      \INCLUDE       -- Header files (.H) to be #included in application
      \LIB           -- Linkable object and resource files
      \HELP          -- Online UCMENU documentation in VIEW (.INF) format
      \SOURCE        -- Source for UCMenus and UCMenu utilties routines
      \SAMPLES       -- Common files (bitmaps, etc) for all samples
         \SAMP1      -- Sample #1, demo of different types of menus
         \SAMP2      -- Sample #2, full menu implementation
         \SAMP3      -- Sample #3, 'buffet' menu customization method


Notes on the Samples:
---------------------

The samples contain everything needed to build the executables including
make files, resource files, etc.  To keep the package size down, the
intermediate code files (.OBJ and .RES) have been deleted, but the .EXE
files are there so you can run the samples without compiling them.  To
compile a sample, just run the OS/2 command "nmake /a all", assuming you
have installed the IBM VisualAge compiler and OS/2 toolkit.

Note that the samples all use static linking of the UCMENUS custom control
code.  To reduce the size of your application .EXE file, you can use dynamic
linking and use the UCMENUS.DLL built in the LIB subdirectory.  When you
use dynamic linking, you must name the UCMENUS.LIB file in the link
command to import the DLL entry points.  Comments in the sample make files
show how to do dynamic linking.

Documentation:
--------------

The HELP directory contains a complete programmers toolkit reference for
the UCMenu control in OS/2 VIEW (.INF) file format.

Questions?:
-----------
This code has no comitted level of support.  However, informal support on
a time-available basis will be made available on Compuserve, OS2DF1
forum, PM programming section.  TALKLINK members can also receive informal
support on the OS2PMPGM CFORUM.
