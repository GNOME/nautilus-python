import hashlib
import urllib

import gtk
import nautilus

class MD5SumPropertyPage(nautilus.PropertyPageProvider):
    def __init__(self):
        pass
    
    def get_property_pages(self, files):
        if len(files) != 1:
            return
        
        file = files[0]
        if file.get_uri_scheme() != 'file':
            return

        if file.is_directory():
            return

        filename = urllib.unquote(file.get_uri()[7:])

        self.property_label = gtk.Label('MD5Sum')
        self.property_label.show()

        self.hbox = gtk.HBox(0, False)
        self.hbox.show()

        label = gtk.Label('MD5Sum:')
        label.show()
        self.hbox.pack_start(label)

        self.value_label = gtk.Label()
        self.hbox.pack_start(self.value_label)

        md5sum = hashlib.md5()
        with open(filename,'rb') as f: 
            for chunk in iter(lambda: f.read(8192), ''): 
                md5sum.update(chunk)
        f.close()       

        self.value_label.set_text(md5sum.hexdigest())
        self.value_label.show()
        
        return nautilus.PropertyPage("NautilusPython::md5_sum",
                                     self.property_label, self.hbox),
