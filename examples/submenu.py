from gi.repository import Nautilus, GObject

class ExampleMenuProvider(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        pass
        
    def get_file_items(self, window, files):
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
        submenu.append_item(Nautilus.MenuItem(name='ExampleMenuProvider::Bar2', 
                                         label='Bar2', 
                                         tip='',
                                         icon=''))

        menuitem = Nautilus.MenuItem(name='ExampleMenuProvider::Foo2', 
                                         label='Foo2', 
                                         tip='',
                                         icon='')
        menuitem.set_submenu(submenu)

        return menuitem,

