from gi.repository import Nautilus, GObject


class UpdateFileInfoAsync(GObject.GObject, Nautilus.InfoProvider):
    def __init__(self):
        super().__init__()
        self.timers = []
        pass

    def update_file_info_full(self, provider, handle, closure, file):
        print("update_file_info_full")
        self.timers.append(
            GObject.timeout_add_seconds(3, self.update_cb, provider, handle, closure)
        )
        return Nautilus.OperationResult.IN_PROGRESS

    def update_cb(self, provider, handle, closure):
        print("update_cb")
        Nautilus.info_provider_update_complete_invoke(
            closure,
            provider,
            handle,
            Nautilus.OperationResult.FAILED,
        )

    def cancel_update(self, provider, handle):
        print("cancel_update")
        for t in self.timers:
            GObject.source_remove(t)
        self.timers = []
