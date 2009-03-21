import nautilus

class ExampleMenuProvider(nautilus.MenuProvider):
    
    # Nautilus crashes if a plugin doesn't implement the __init__ method.
    # See Bug #374958
    def __init__(self):
        pass
        
    def get_file_items(self, window, files):
        top_menuitem = nautilus.MenuItem('ExampleMenuProvider::Foo', 'Foo', '')

        submenu = nautilus.Menu()
        top_menuitem.set_submenu(submenu)

        sub_menuitem = nautilus.MenuItem('ExampleMenuProvider::Bar', 'Bar', '')
        submenu.append_item(sub_menuitem)

        return top_menuitem,

    def get_background_items(self, window, file):
        submenu = nautilus.Menu()
        submenu.append_item(nautilus.MenuItem('ExampleMenuProvider::Bar', 'Bar', ''))

        menuitem = nautilus.MenuItem('ExampleMenuProvider::Foo', 'Foo', '')
        menuitem.set_submenu(submenu)

        return menuitem,

