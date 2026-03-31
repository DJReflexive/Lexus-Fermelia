# A simple script to rename files without an extension to .png in a specified directory.
#
# Not a complex script, but a script that I use often enough to having it here.

import os
from pathlib import Path


directory_path = r"C:\Users\lexus\directory\path\here"


p = Path(directory_path)
for entry in p.iterdir():
    print(entry.name, end='')

    # Check if file name has extension
    if not entry.suffix:
        new_name = entry.with_suffix('.png')
        os.rename(entry, new_name)
        
        print(f" -> Renamed to: {new_name.name}")

