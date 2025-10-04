from gi.repository import Nautilus, GObject, Gio
from typing import List

SUPPORTED_FORMATS = "image/jpeg", "image/png"
BACKGROUND_SCHEMA = "org.gnome.desktop.background"
BACKGROUND_KEY = "picture-uri"


class BackgroundImageExtension(GObject.GObject, Nautilus.MenuProvider):
    def __init__(self):
        super().__init__()
        self.bgsettings = Gio.Settings.new(BACKGROUND_SCHEMA)

    def menu_activate_cb(
        self,
        menu: Nautilus.MenuItem,
        file: Nautilus.FileInfo,
    ) -> None:
        if file.is_gone():
            return

        self.bgsettings[BACKGROUND_KEY] = file.get_uri()

    def get_file_items(
        self,
        files: List[Nautilus.FileInfo],
    ) -> List[Nautilus.MenuItem]:
        if len(files) != 1:
            return []

        file = files[0]

        # We're only going to put ourselves on images context menus
        if not file.get_mime_type() in SUPPORTED_FORMATS:
            return []

        # Gnome can only handle file:
        # In the future we might want to copy the file locally
        if file.get_uri_scheme() != "file":
            return []

        item = Nautilus.MenuItem(
            name="Nautilus::set_background_image",
            label="Use as background image",
        )
        item.connect("activate", self.menu_activate_cb, file)

        return [
            item,
        ]

    # Current versions of Nautilus will throw a warning if get_background_items
    # isn't present
    def get_background_items(
        self,
        current_folder: Nautilus.FileInfo,
    ) -> List[Nautilus.MenuItem]:
        return []
