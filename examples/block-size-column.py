import os
from urllib.parse import unquote
from gi.repository import GObject, Nautilus
from typing import List


class ColumnExtension(GObject.GObject, Nautilus.ColumnProvider, Nautilus.InfoProvider):
    def get_columns(self) -> List[Nautilus.Column]:
        column = Nautilus.Column(
            name="NautilusPython::block_size_column",
            attribute="block_size",
            label="Block size",
            description="Get the block size",
        )

        return [
            column,
        ]

    def update_file_info(self, file: Nautilus.FileInfo) -> None:
        if file.get_uri_scheme() != "file":
            return

        filename = unquote(file.get_uri()[7:])

        file.add_string_attribute("block_size", str(os.stat(filename).st_blksize))
