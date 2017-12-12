# This example is contributed Robert Knight 

from gi.repository import Nautilus, GObject
import hashlib
import urllib

class Sha1MenuDisplay(GObject.GObject, Nautilus.MenuProvider):
    """ This places an MD5 sum in the context menu in Nautilus.
    To use it, nautilus-python is required.  This script then goes in
    ~/.local/share/nautilus-python/extensions and should work after a restart
    of Nautilus
    """
    def __init__(self):
        pass

    def menu_activate_cb(self, menu, file):
        print "menu_activate_cb",file

    def get_file_items(self, window, files):
        if len(files) != 1:
            return

        file = files[0]
        filename = urllib.unquote(file.get_uri()[7:])
        sha1sum = hashlib.sha1()
        with open(filename,'rb') as f:
            for chunk in iter(lambda: f.read(8192), ''):
                sha1sum.update(chunk)
        f.close()
        string = sha1sum.hexdigest()
        item = Nautilus.MenuItem(name="Sha1MenuDisplay::Show_File_Name",
                                 label="SHA-1: %s" % string,
                                 tip="SHA-1: %s" % string)
        item.connect('activate', self.menu_activate_cb, file)
        
        return [item]
