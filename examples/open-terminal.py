# This example is contributed by Martin Enlund
import os
import urllib.parse

import gi
gi.require_version('GConf', '2.0')
from gi.repository import Nautilus, GObject, GConf


class OpenTerminalExtension(Nautilus.MenuProvider, GObject.GObject):
    def __init__(self):
        self.client = GConf.Client.get_default()
        
    def _open_terminal(self, file):
        filename = urllib.parse.unquote(file.get_uri()[7:])

        os.chdir(filename)
        os.system('gnome-terminal')
        
    def menu_activate_cb(self, menu, file):
        self._open_terminal(file)
        
    def menu_background_activate_cb(self, menu, file): 
        self._open_terminal(file)
       
    def get_file_items(self, window, files):
        if len(files) != 1:
            return
        
        file = files[0]
        if not file.is_directory() or file.get_uri_scheme() != 'file':
            return
       
        item = Nautilus.MenuItem(name='NautilusPython::openterminal_file_item',
                                 label='Open Terminal' ,
                                 tip='Open Terminal In %s' % file.get_name())
        item.connect('activate', self.menu_activate_cb, file)
        return item,

    def get_background_items(self, window, file):
        item = Nautilus.MenuItem(name='NautilusPython::openterminal_file_item2',
                                 label='Open Terminal' ,
                                 tip='Open Terminal In %s' % file.get_name())
        item.connect('activate', self.menu_background_activate_cb, file)
        return item,
