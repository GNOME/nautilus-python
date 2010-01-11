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
    def update_file_info(self, file):
        """
        @param file   selected file
        @type  file   list of nautilus.FileInfo

        This is used to update data for file, use the set_data method,
        and use together with the other extensions
        """

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
        pass

    def get_name(self):
        pass

    def get_uri(self):
        pass

    def get_parent_uri(self):
        pass

    def get_uri_scheme(self):
        pass

    def get_mime_type(self):
        pass
    
    def is_mime_type(self, mime_type):
        pass

    def is_directory(self):
        pass

    def add_emblem(self, emblem):
        pass
    
    def get_string_attribute(self, attribute_name):
        pass

    def add_string_attribute(self, attribute_name, value):
        pass

    def invalidate_extension_info(self):
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
    
    
