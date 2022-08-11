from gi.repository import Nautilus, Gtk, GObject


class LocationProviderExample(GObject.GObject, Nautilus.LocationWidgetProvider):
    def __init__(self):
        pass

    def get_widget(self, uri, window):
        entry = Gtk.Entry()
        entry.set_text(uri)
        entry.show()
        return entry
