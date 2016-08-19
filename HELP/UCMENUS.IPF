.*
:userdoc.
:docprof.
:title.UCMenus help
.*
:h1 res=3230.Style dialog
:p.You can check the following items to change the general style of the UCMenu &colon.
:parml compact break=all.
:pt.:hp2.Show the text:ehp2.
:pd.Display the text.
:pt.:hp2.Frame the items:ehp2.
:pd.Draw a 3D frame around each item.
:pt.:hp2.Force the size:ehp2.
:pd.Use the :hp2.Width:ehp2. and :hp2.Height:ehp2. fields to specify the size in pixels
you want to give to each item.
.br
If the item is smaller, it is centered.
.br
If the item is bigger, the bitmap is shrunk.
.br
There are three shrink modes &colon.
:parml compact break=all.
:pt.:hp2.Ignore:ehp2.
:pd.Ignore the lost lines and columns, works best for bitmaps with lots of colors.
:pt.:hp2.And:ehp2.
:pd.Works best for bitmaps with dark drawings on light backgrounds.
:pt.:hp2.Or:ehp2.
:pd.Works best for bitmaps with light drawings on dark backgrounds.
:eparml.
:eparml.
.*
:h1 res=3231.Item edition notebook
:p.This notebook is displayed when you select :hp2.Create item:ehp2. or
:hp2.Edit item:ehp2. from the context menu. You can display one of the
following pages &colon.
:ul compact.
:li.:link reftype=hd res=3232.Position:elink.
:li.:link reftype=hd res=3233.General:elink.
:li.:link reftype=hd res=3234.Action:elink.
:eul.
.*
:h1 res=3232.Item position
:p.You can create an item at the :hp2.End:ehp2. of the UCMenu, :hp2.Before:ehp2.
or :hp2.After:ehp2. the current item.
:note.If you did not display the context menu over an item, you can just chose :hp2.End:ehp2.
:p.If you select the :hp2.Non selectable item:ehp2. button, the created item will not be selectable
and will just be used as a decoration.
:p.If you select the :hp2.Spacer:ehp2. button, the created item will be an item without text, bitmap or
frame, which can be used as a separator.
.*
:h1 res=3233.General
:p.This page allows to chose the text and the bitmap of an item. An item must have at
least one of the two.
:parml compact break=all.
:pt.:hp2.Title:ehp2.
:pd.Text to be written in the item if the :hp2.Show text:ehp2. style is chosen.
.br
An accelerator key can be defined by putting a "~" in front of the chosen character.
The character will be displayed underscored on the item and pressing on its key while
the focus is on the UCMenu will select the item.
:pt.:hp2.Built-in...:ehp2.
:pd.Display a dialog to chose a new bitmap among the set of built-in bitmaps.
:pt.:hp2.Load...:ehp2.
:pd.Display a file dialog to chose a new bitmap.
:pt.:hp2.Edit...:ehp2.
:pd.If the icon comes from a file, start iconedit to edit it.
:pt.:hp2.Create...:ehp2.
:pd.Start iconedit to create a new bitmap.
:eparml.
:p.Under the bitmap frame is displayed its filename, or its id if it
comes from the resources.
.*
:h1 res=3234.Item action
:p.The chosen :hp2.Function:ehp2. will be executed  with the associated
:hp2.Parameters:ehp2. when the item is selected.
:p.You can chose the function in a list&colon.
:ul compact.
:li.The :hp2.ExecuteProgram:ehp2. function starts the program given in the :hp2.Parameters:ehp2.
field in another thread.
:li.The other functions supplied depends on the application using the UCMenu.
:eul.
.*
:h1 res=3235.Drag and drop features
:hp2.You can use drag and drop to copy or move items between ucmenus.:ehp2.
:p.The default operation is move, you can also do a copy if you press the :hp2.Control:ehp2. key while dropping.
:p.It is possible to do drag and drop between ucmenus from different applications.
:p.The submenus attached to an item are not kept if you do a copy, or if you do a drag and drop
between different applications.
:p.If you press the :hp2.Alt:ehp2. key while dropping over an item ,
the operation will be a copy to the submenu of this item. If it had no submenu, one will be created.
:p.A frame is drawn around the destination item.
:p.On an horizontal or matrix ucmenu, the dropped item can go either to the left or to the right
of the destination item, depending on the drop zone.
:p.On a vertical ucmenu, it goes to the top or to the bottom of the destination
:p.You can drop on the part of the UCMenu where there are no items, the dropped item will be added at the end.
:p.:hp2.An item can be rendered as a bitmap file.:ehp2.
:p.If its bitmap comes from a file and not from the application, an item can be
dropped for example on iconedit to edit its bitmap.
:p.:hp2.If a bitmap file is dropped, a new item using this bitmap is created.:ehp2.
:p.:hp2.An item can also be dropped on the shredder to be deleted.:ehp2.
:p.:hp2.Fonts and colors can be dragged and dropped from the system palettes to change the appearance of the ucmenu.:ehp2.
.*
:h1 res=3236.Context Menu
:p.You can select an action which will affect either one item or the whole toolbar.
.*
:h1 res=3237.Edit item...
:p.Display a notebook to select the bitmap, text and action associated to the item.
.*
:h1 res=3238.Create item...
:p.Display a notebook to select the bitmap, text, action and position
:p. of the new item.
.*
:h1 res=3239.Delete.
:p.Deletes the item on which the context menu was popped up.
.*
:h1 res=3240.Change style...
:p.Display a dialog to modify the appearance of the tool bar.
.*
:h1 res=3241.Load default.
:p.Switch back to the original tool bar.
.*
:h1 res=3242.Import...
:p.Restore a tool bar from a file.
.*
:h1 res=3243.Export...
:p.Save a tool bar to a file.
.*
:h1 res=3244.Toolbar buffet dialog.
:p.The top toolbar is the buffet, it contains all the built-in items.
:p.The bottom toolbar represents the toolbar you want to modify.
:p.You can drag items &colon.
:ul compact.
:li.From the buffet to the bottom toolbar to add them.
:li.Inside the bottom toolbar to change their ordering.
:li.From the bottom toolbar to the shredder icon to remove them.
:eul.
:p.You can click on an item to pop up a message box with its description.
:p.You can also click on the right mouse button over a bottom toolbar item
to display the context menu and do more advanced modifications.
:p.
.*
:euserdoc.



