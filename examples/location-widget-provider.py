import nautilus
import gtk

class LocationProviderExample(nautilus.LocationWidgetProvider):
    def __init__(self):
        pass
    
    def get_widget(self, uri, window):
        entry = gtk.Entry()
        entry.set_text(uri)
        entry.show()
        return entry

