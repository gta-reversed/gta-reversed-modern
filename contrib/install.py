import tkinter as tk
import subprocess
from tkinter import filedialog as tkFileDialog
from pathlib import Path
import zipfile

def mk_symlink(link : Path, target : Path):
    subprocess.run(
        ['mklink', str(link), str(target)], 
        check=True
    )

def main():
    while True:
        gta_root_dir = Path(tkFileDialog.askdirectory(
            parent=tk.Tk(),
            initialdir=Path.cwd(),
            title='Select GTA:SA install directory'
        ))
        if gta_root_dir.exists():
            break
    gta_scripts_dir = gta_root_dir / 'scripts'
    
    # Unpack zip into gta dir
    print("Unpacking `plugins.zip` into GTA:SA root directory...")
    with zipfile.ZipFile('plugins.zip') as plugins_zip:
        plugins_zip.extractall(gta_root_dir)
    
    # Create symlinks
    config_name = print("Choose configuration to link (debug/release, default: debug): ") or 'debug'
    print(f"Creating the symlinks for `{config_name}` configuration...")
    config_bin_dir = Path.cwd().parent / 'bin' / Path(config_name)
    print(f'{config_bin_dir=!r}')
    mk_symlink(config_bin_dir / 'gta_reversed.asi', gta_scripts_dir / 'gta_reversed.asi')
    mk_symlink(config_bin_dir / 'gta_reversed.pdb', gta_scripts_dir / 'gta_reversed.pdb')

if __name__ == "__main__":
    if Path.cwd().name != 'contrib':
        print('This file should be ran from inside the `contrib` folder!')
        input("Press any key to continue...")
    else:
        main()
