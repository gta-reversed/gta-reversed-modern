from tkinter import filedialog as tkFileDialog
from pathlib import Path
import zipfile
import ctypes
import sys
import re
import os

def main():
    if ctypes.windll.shell32.IsUserAnAdmin():
        modern()
    else:
        print('Allow the launch as an administrator!')
        ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, " ".join(sys.argv), None, 1)

def modern():
    git_repo_root = Path.cwd()
    if git_repo_root.parts[-1] == 'contrib':
        git_repo_root = git_repo_root.parent
    
    gta_root = tkFileDialog.askdirectory(title='Select GTA:SA install directory', mustexist=False)
    gta_root_dir = Path(gta_root)
    if not gta_root or git_repo_root == gta_root_dir:
        print("The project directory cannot be an assembly. Press Enter...")
        return modern()

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
    for filename in ('gta_reversed.pdb', 'gta_reversed.asi'):
        dst = gta_scripts_dir / filename
        dst.unlink(missing_ok=True) # Delete symlink if it already exists
        # This fails [WinError 1314] if the script isn't run with admin rights [softlinks require it]
        # To run as admin just open an admin cmd, and type `python ./install.py` in the repo root dir
        os.symlink(config_bin_dir / filename, dst)

    setting_file = git_repo_root / 'build' / 'gta_reversed.vcxproj.user'
    if os.path.exists(setting_file):
        with open(setting_file) as file:
            content = file.read()
        
        content = re.sub(r'<LocalDebuggerCommand>(.*?)</LocalDebuggerCommand>', f'<LocalDebuggerCommand>{gta_root_dir.as_posix() + "/gta_sa.exe"}</LocalDebuggerCommand>', content)
        content = re.sub(r'<LocalDebuggerWorkingDirectory>(.*?)</LocalDebuggerWorkingDirectory>', f'<LocalDebuggerWorkingDirectory>{gta_root_dir.as_posix()}</LocalDebuggerWorkingDirectory>', content)
        with open(setting_file, 'w') as file:
            file.write(content)
        print("The debugging settings have been changed. It's better to re-enter the project")
    input('Done! Press Enter...')

if __name__ == "__main__":
    main()
