from gi.repository import Nautilus, GObject
from typing import List


class TestExtension(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        super().__init__()
        print("Initialized test extension")

    def menu_activate_cb(
        self,
        menu: Nautilus.MenuItem,
        file: Nautilus.FileInfo,
    ) -> None:
        print("menu_activate_cb", file)

    def get_file_items(
        self,
        files: List[Nautilus.FileInfo],
    ) -> List[Nautilus.MenuItem]:
        if len(files) != 1:
            return []

        file = files[0]

        item = Nautilus.MenuItem(
            name="SimpleMenuExtension::Show_File_Name",
            label="Showing %s" % file.get_name(),
        )
        item.connect("activate", self.menu_activate_cb, file)

        return [
            item,
        ]

    # Even though we're not using background items, Nautilus will generate
    # a warning if the method isn't present
    def get_background_items(
        self,
        current_folder: Nautilus.FileInfo,
    ) -> List[Nautilus.MenuItem]:
        return []
