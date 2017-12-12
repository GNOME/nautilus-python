# This example contributed by Robert Knight - bobby.knight@gmail.com

# This creates a menu item that says "Open File With"
# and then, the two programs are options to open the file with.  In this particular example
# the names of the program are 'code' for Visual Studio code  and 'gedit'.
# to use leafpad instead of code, replace the word code with 'leafpad' on line 12.

from gi.repository import Nautilus, GObject
from urllib import unquote

PROGRAM_NAME = 'code'
PROGRAM_NAME2 = 'gedit'

class ExampleMenuProvider(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        pass

    def launch_gedit(self, menu, files):
        # Do whatever you want to do with the files selected
        if len(files) == 0:
            return
        # Strip the URI format to plain file names
        file_name = [unquote(item.get_uri()[7:]) for item in files]
        argv = [PROGRAM_NAME2] + file_name
        GObject.spawn_async(argv, flags=GObject.SPAWN_SEARCH_PATH)

    def launch_code(self, menu, files):
        # Do whatever you want to do with the files selected
        if len(files) == 0:
            return
        # Strip the URI format to plain file names
        file_name = [unquote(item.get_uri()[7:]) for item in files]
        argv = [PROGRAM_NAME] + file_name
        GObject.spawn_async(argv, flags=GObject.SPAWN_SEARCH_PATH)


    def get_file_items(self, window, files):

        #  Appears as top level item         --------------------- 
        top_menuitem = Nautilus.MenuItem(name='ExampleMenuProvider::Main', 
                                         label='Open File With: ', 
                                         tip='',
                                         icon='')

        #  Submenu items when a file is selected -----------------
        submenu = Nautilus.Menu()
        top_menuitem.set_submenu(submenu)

        sub_menuitem = Nautilus.MenuItem(name='ExampleMenuProvider::Code', 
                                         label='Code', 
                                         tip='',
                                         icon='')
        submenu.append_item(sub_menuitem)

        sub_menuitem.connect('activate', self.launch_code, files)

        sub_menuitem2 = Nautilus.MenuItem(name='ExampleMenuProvider::Gedit', 
                                         label='Gedit', 
                                         tip='',
                                         icon='')
        submenu.append_item(sub_menuitem2)
        sub_menuitem2.connect('activate', self.launch_gedit, files)


        return top_menuitem,
