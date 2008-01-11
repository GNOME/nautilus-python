import nautilus

class ExampleMenuProvider(nautilus.MenuProvider):

    def get_file_items(self, window, files):
        menuitem = nautilus.MenuItem('ExampleMenuProvider::Foo', 'Foo', '')

        submenu = nautilus.Menu()
        menuitem.set_submenu(submenu)

        menuitem = nautilus.MenuItem('ExampleMenuProvider::Bar', 'Bar', '')
        submenu.append_item(menuitem)

        return menuitem,

    # FIXME: Why isn't this working?
    def get_background_items(self, window, file):
        submenu = nautilus.Menu()
        submenu.append_item(nautilus.MenuItem('ExampleMenuProvider::Bar', 'Bar', ''))

        menuitem = nautilus.MenuItem('ExampleMenuProvider::Foo', 'Foo', '')
        menuitem.set_submenu(submenu)

        return menuitem,

