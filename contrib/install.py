import os
from tkinter import filedialog as tkFileDialog
from pathlib import Path
import zipfile
import ctypes
import sys

def set_env_var(name, value):
    os.system(f"powershell [Environment]::SetEnvironmentVariable('{name}', '{value}', [EnvironmentVariableTarget]::User)")

def main():
    if not ctypes.windll.shell32.IsUserAnAdmin():
        print('Allow the launch as an administrator!')
        return ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, " ".join(sys.argv), None, 1)

    git_repo_root = Path.cwd()
    if git_repo_root.parts[-1] == 'contrib':
        git_repo_root = git_repo_root.parent

    initialdir = os.environ['GTA_SA_DIR'] if 'GTA_SA_DIR' in os.environ else ''
    select = tkFileDialog.askopenfilename(
        title='Select the executable file from the GTA:SA installation directory',
        filetypes=[("GTA:SA", ".exe")], initialdir=initialdir
    )
    if not select:
        return input('You have not selected a file, we are leaving. Press Enter...')

    gta_sa_file = Path(select)
    gta_root_dir = gta_sa_file.parent.resolve()

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
        dst = gta_root_dir / 'scripts' / filename
        dst.unlink(missing_ok=True) # Delete symlink if it already exists
        # This fails [WinError 1314] if the script isn't run with admin rights [softlinks require it]
        os.symlink(config_bin_dir / filename, dst)

    print("The Env variables are changing... If VS is open with the Modern solution, restart VS")
    set_env_var('GTA_SA_EXE', gta_sa_file)
    set_env_var('GTA_SA_DIR', gta_root_dir)
    input('Done! Press Enter...')

if __name__ == "__main__":
    main()
