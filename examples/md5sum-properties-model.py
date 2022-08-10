import hashlib

from urllib.parse import unquote
from gi.repository import Nautilus, Gio, GObject
from typing import List


class MD5SumPropertiesModel(GObject.GObject, Nautilus.PropertiesModelProvider):
    def get_models(
        self,
        files: List[Nautilus.FileInfo],
    ) -> List[Nautilus.PropertiesModel]:
        if len(files) != 1:
            return []

        file = files[0]
        if file.get_uri_scheme() != "file":
            return []

        if file.is_directory():
            return []

        filename = unquote(file.get_uri()[7:]).encode("utf-8")

        section_model = Gio.ListStore.new(item_type=Nautilus.PropertiesItem)

        section_model.append(
            Nautilus.PropertiesItem(
                name="MD5 sum of the filename",
                value=hashlib.md5(filename).hexdigest(),
            )
        )

        return [
            Nautilus.PropertiesModel(
                title="MD5Sum",
                model=section_model,
            ),
        ]
