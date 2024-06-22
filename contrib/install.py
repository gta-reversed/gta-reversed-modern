import os
from tkinter import filedialog as tkFileDialog
from pathlib import Path
import zipfile
import ctypes
import sys

def main():
    if ctypes.windll.shell32.IsUserAnAdmin():
        modern()
    else:
        print('Allow the launch as an administrator!')
        ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, " ".join(sys.argv), None, 1)

def set_env_var(name, value):
    os.system(f"powershell [Environment]::SetEnvironmentVariable('{name}', '{value}', [EnvironmentVariableTarget]::User)")

def modern():
    git_repo_root = Path.cwd()
    if git_repo_root.parts[-1] == 'contrib':
        git_repo_root = git_repo_root.parent

    gta_sa_file = Path(tkFileDialog.askopenfilename(
        title='Select the executable file from the GTA:SA installation directory',
        filetypes=[("GTA:SA", ".exe")]
    ))
    gta_root_dir = gta_sa_file.parent.resolve()
    if gta_root_dir.is_relative_to(git_repo_root):
        print("GTA root directory can't be relative to this project's git root path")
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
        os.symlink(config_bin_dir / filename, dst)

    print("The Env variables are changing. If you had a project open, reopen it.")
    set_env_var('GTA_SA_EXE', gta_sa_file.as_posix())
    set_env_var('GTA_SA_DIR', gta_root_dir.as_posix())
    input('Done! Press Enter...')

if __name__ == "__main__":
    main()
