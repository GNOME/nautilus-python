from gi.repository import Nautilus, GObject
from typing import List


class ExampleMenuProvider(GObject.GObject, Nautilus.MenuProvider):
    def get_file_items(
        self,
        files: List[Nautilus.FileInfo],
    ) -> List[Nautilus.MenuItem]:
        top_menuitem = Nautilus.MenuItem(
            name="ExampleMenuProvider::Foo",
            label="Foo",
        )

        submenu = Nautilus.Menu()
        top_menuitem.set_submenu(submenu)

        sub_menuitem = Nautilus.MenuItem(
            name="ExampleMenuProvider::Bar",
            label="Bar",
        )
        submenu.append_item(sub_menuitem)

        return [
            top_menuitem,
        ]

    def get_background_items(
        self,
        current_folder: Nautilus.FileInfo,
    ) -> List[Nautilus.MenuItem]:
        submenu = Nautilus.Menu()
        submenu.append_item(
            Nautilus.MenuItem(
                name="ExampleMenuProvider::Bar2",
                label="Bar2",
            )
        )

        menuitem = Nautilus.MenuItem(
            name="ExampleMenuProvider::Foo2",
            label="Foo2",
        )
        menuitem.set_submenu(submenu)

        return [
            menuitem,
        ]
