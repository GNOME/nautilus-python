import gtk
import nautilus

class ColumnExtension(nautilus.ColumnProvider):
    def __init__(self):
        pass
    
    def get_columns(self):
        return nautilus.Column("NautilusPython::python_column",
                               "python_data",
                               "Python Data",
                               "Information from the Python test component"),

class MenuExtension(nautilus.MenuProvider):
    def __init__(self):
        pass
    
    def menu_activate_cb(self, menu, window, files):
        if files:
            msg = ', '.join([file.get_name() for file in files])
        else:
            msg = 'nothing!'
            
        g = gtk.MessageDialog(parent=window,
                              message_format="You selected " + msg,
                              buttons=gtk.BUTTONS_OK)
        def timeout_cb():
            print 'timeout'
            return True
        
        def response_cb(*args):
            print args

        source_id = gtk.timeout_add(100, timeout_cb)
        g.run()
        gtk.timeout_remove(source_id)
        g.destroy()
        
    def menu_background_activate_cb(self, menu, files):
        print 'You clicked on the background'

    def menu_toolbar_activate_cb(self, menu, files):
        print 'You clicked in the toolbar'

    def get_file_items(self, window, files):
        item = nautilus.MenuItem('NautilusPython::file_item',
                                 'Python!',
                                 'Python File MenuItem')
        item.connect('activate', self.menu_activate_cb, window, files)
        return item,

    def get_background_items(self, window, file):
        item = nautilus.MenuItem('NautilusPython::background_item',
                                 'Python!',
                                 'Python Background MenuItem')
        item.connect('activate', self.menu_background_activate_cb, file)
        return item,

    def get_toolbar_items(self, window, file):
        item = nautilus.MenuItem('NautilusPython::toolbar_item',
                                 'Python!',
                                 'Python Toolbar MenuItem')
        item.connect('activate', self.menu_toolbar_activate_cb, file)
        return item,

class PropertyExtension(nautilus.PropertyPageProvider):
    def __init__(self):
        pass
    
    def get_property_pages(self, files):
        d = [file.get_data('python') for file in files]
            
        label = gtk.Label('Python 2')
        label.show()
        page = gtk.Label('Python property page: %r' % d)
        page.show()
        
        return nautilus.PropertyPage("NautilusPython::property_page",
                                     label, page),

class InfoExtension(nautilus.InfoProvider):
    def __init__(self):
        pass

    def update_file_info(self, file):
        file.set_data('python', 2j)
