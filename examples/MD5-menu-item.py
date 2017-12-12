# This example is contributed Robert Knight - bobby.knight@gmail.com

from gi.repository import Nautilus, GObject
import hashlib
import urllib

class Md5MenuDisplay(GObject.GObject, Nautilus.MenuProvider):
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
        md5sum = hashlib.md5()
        with open(filename,'rb') as f:
            for chunk in iter(lambda: f.read(8192), ''):
                md5sum.update(chunk)
        f.close()
        string = md5sum.hexdigest()
        item = Nautilus.MenuItem(name="Md5MenuDisplay::Show_File_Name",
                                 label="MD5: %s" % string,
                                 tip="MD5: %s" % string)
        item.connect('activate', self.menu_activate_cb, file)
        
        return [item]
