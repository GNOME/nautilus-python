import os
from gi.repository import Nautilus, GObject
# https://github.com/GNOME/nautilus-python/blob/master/examples/submenu.py

class ExampleMenuProvider(GObject.GObject, Nautilus.MenuProvider):
    # Nautilus crashes if a plugin doesn't implement the __init__ method.
    # See Bug #374958

    def __init__(self):
        pass

    def get_file_items(self, window, file):

        top_menuitem = Nautilus.MenuItem(name='ExampleMenuProvider::Foo',
                                         label='Foo',
                                         tip='',
                                         icon='')

        submenu = Nautilus.Menu()
        top_menuitem.set_submenu(submenu)

        sub_menuitem = Nautilus.MenuItem(name='ExampleMenuProvider::Bar',
                                         label='Bar',
                                         tip='',
                                         icon='')
        submenu.append_item(sub_menuitem)

        return top_menuitem,

    def get_background_items(self, window, file):
        submenu = Nautilus.Menu()
        submenu.append_item(
        Nautilus.MenuItem('ExampleMenuProvider::Bar', 'Bar', '', ''))

        menuitem = Nautilus.MenuItem('ExampleMenuProvider::Foo', 'Foo', '', '')
        menuitem.set_submenu(submenu)

        return menuitem,
