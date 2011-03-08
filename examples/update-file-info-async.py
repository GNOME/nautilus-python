import gobject
from gi.repository import Nautilus

class UpdateFileInfoAsync(gobject.GObject, Nautilus.InfoProvider):
    def __init__(self):
        pass
    
    def update_file_info_full(self, provider, handle, closure, file):
        print "update_file_info_full"
        print handle
        gobject.timeout_add_seconds(3, self.update_cb, provider, handle, closure)
        return Nautilus.OperationResult.IN_PROGRESS
        
    def update_cb(self, provider, handle, closure):
        print "update_cb"
        Nautilus.info_provider_update_complete_invoke(self.hello, provider, handle, Nautilus.OperationResult.FAILED)
        
    def hello(self):
        print "HELLO"
