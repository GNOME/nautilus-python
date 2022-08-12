from gi.repository import Nautilus, GObject


class TestExtension(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        super().__init__()
        print("Initialized test extension")

    def menu_activate_cb(self, menu, file):
        print("menu_activate_cb", file)

    def get_file_items(self, window, files):
        if len(files) != 1:
            return

        file = files[0]

        item = Nautilus.MenuItem(
            name="SimpleMenuExtension::Show_File_Name",
            label="Showing %s" % file.get_name(),
            tip="Showing %s" % file.get_name(),
        )
        item.connect("activate", self.menu_activate_cb, file)

        return [item]

    # Even though we're not using background items, Nautilus will generate
    # a warning if the method isn't present
    def get_background_items(self, window, file):
        return None
