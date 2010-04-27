class ColumnProvider:
    def get_columns(self):
        """
        @returns columns to show
        @rtype   a sequence of nautilus.Column
        """

class MenuProvider:
    def get_file_items(self, window, files):
        """
        @param window the window it was sent from
        @type  window gtk.Window
        @param files  selected files
        @type  files  list of nautilus.FileInfo
        @returns      menu items to show
        @rtype        a sequence of nautilus.MenuItems
        """

    def get_background_items(self, window, file):
        """
        @param window the window it was sent from
        @type  window gtk.Window
        @param file   file that was clicked on
        @type  file   nautilus.FileInfo
        @returns      menu items to show
        @rtype        a sequence of nautilus.MenuItems
        """

    def get_toolbar_items(self, window, file):
        """
        @param window the window it was sent from
        @type  window gtk.Window
        @param file   file that was clicked on
        @type  file   nautilus.FileInfo
        @returns      menu items to show
        @rtype        a sequence of nautilus.MenuItems
        """

class PropertyPageProvider:
    def get_property_pages(self, files):
        """
        @param files  selected files
        @type  files  list of nautilus.FileInfo
        @returns      property pages to show
        @rtype        a sequence of nautilus.PropertyPage

        Creates a property page for files
        """
        
class InfoProvider:
    def update_file_info(self, file, info):
        """
        @param file   selected file
        @type  file   list of nautilus.FileInfo

        @param info   data that needs to be passed back in a 
                        self.update_complete_invoke(info) call
        @type  info   dict

        @returns      None, nautilus.OPERATION_COMPLETE, 
                        nautilus.OPERATION_FAILED, or 
                        nautilus.OPERATION_IN_PROGRESS

        This is used to update data for file, use the set_data method,
        and use together with the other extensions.
        
        In order to use this method asynchronously, you must return the 
        nautilus.OPERATION_IN_PROGRESS enum.  Then, when the operation has
        completed, call the self.update_complete_invoke method, passing the info variable
        as a parameter.
        """

    def update_complete_invoke(self, info):
        """
        @param  info    unique data for each update_file_info call
        @type   info    dict
        """

class Menu:
    def append(self, menu_item):
        """
        @type   menu_item   nautilus.MenuItem
        """
        pass
        
    def get_items(self):
        """
        @rtype  list of nautilus.MenuItem
        """
        pass

class MenuItem:
    """
    Properties:
      name (string)        - the identifier for the menu item
      label (string)       - the user-visible label of the menu item
      tip (string)         - the tooltip of the menu item 
      icon (string)        - the name of the icon to display in the menu item
      sensitive (boolean)  - whether the menu item is sensitive or not
      priority (boolean)   - used for toolbar items, whether to show priority

    Signals:
      activate (button)
    """
    
    def __init__(self, name, label, tip, icon=None):
        pass
    
    def activate(self):
        pass

    def set_submenu(self, menu):
        """
        @type   menu    nautilus.Menu
        """
        pass
    
class Column:
    """
    Properties:
      name (string)        - the identifier for the column
      attribute (string)   - the file attribute to be displayed in the 
                              column
      label (string)       - the user-visible label for the column
      description (string) - a user-visible description of the column
      xalign (float)       - x-alignment of the column 
    """
    
    def __init__(self, name, attribute, label, description):
        pass

class FileInfo:
    def is_gone(self):
        """
        @rtype   boolean
        """
        pass

    def get_file_type(self):
        """
        @rtype   gio FileType enum
        """
        pass

    def get_location(self):
        """
        @rtype   gio.File
        """
        pass

    def get_name(self):
        """
        @rtype   string
        """
        pass

    def get_uri(self):
        """
        @rtype   string
        """
        pass

    def get_activation_uri(self):
        """
        @rtype   string
        """
        pass

    def get_parent_location(self):
        """
        @rtype   gio.File
        """
        pass

    def get_parent_uri(self):
        """
        @rtype   string
        """
        pass

    def get_mount(self):
        """
        @rtype   gio.Mount
        """
        pass

    def get_uri_scheme(self):
        """
        @rtype   string
        """
        pass

    def get_mime_type(self):
        """
        @rtype   string
        """
        pass
    
    def is_mime_type(self, mime_type):
        """
        @type   mime_type   string
        @rtype  boolean
        """
        pass

    def is_directory(self):
        """
        @rtype   boolean
        """
        pass
    
    def can_write(self):
        """
        @rtype   boolean
        """
        pass

    def add_emblem(self, emblem):
        """
        @rtype   void
        """
        pass
    
    def get_string_attribute(self, attribute_name):
        """
        @rtype   string
        """
        pass

    def add_string_attribute(self, attribute_name, value):
        """
        @rtype   void
        """
        pass

    def invalidate_extension_info(self):
        """
        @rtype   void
        """
        pass
    
class PropertyPage:
    """
    Properties:
      name (string)        - the identifier for the property page
      label (widget)       - the user-visible label of the property page
      page (widget)        - the property page to display
    """

    def __init__(self, name, label, page):
        pass
    
    
