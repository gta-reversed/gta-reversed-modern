import tkinter as tk
import os
import subprocess
from tkinter import filedialog as tkFileDialog
from pathlib import Path
import zipfile

def main():
    git_repo_root = Path.cwd()

    gta_root_dir = Path(tkFileDialog.askdirectory(
        title='Select GTA:SA install directory'
    ))
    gta_scripts_dir = gta_root_dir / 'scripts'
    
    # Unpack zip into gta dir
    print("Unpacking `plugins.zip` into GTA:SA root directory...")
    with zipfile.ZipFile(git_repo_root / 'contrib' / 'plugins.zip') as plugins_zip:
        plugins_zip.extractall(gta_root_dir)
    
    # Create symlinks
    config_name = input("Choose configuration to link (debug/release, default: debug): ") or 'debug'
    print(f"Creating the symlinks for `{config_name}` configuration...")
    config_bin_dir = git_repo_root / 'bin' / Path(config_name)
    print(f'{config_bin_dir=}')
    for filename in ('gta_reversed.pdb', 'gta_reversed.asi',):
        dst = gta_scripts_dir / filename
        dst.unlink(missing_ok=True) # Delete symlink if it already exists
        # This fails [WinError 1314] if the script isn't run with admin rights [softlinks require it]
        # To run as admin just open an admin cmd, and type `python ./install.py` in the repo root dir
        os.symlink(config_bin_dir / filename, dst)

    print('Done!')

if __name__ == "__main__":
    main()
