from pathlib import Path
import io

def write_ns_prologue(f, ns):
    f.write(''.join((f'namespace {v} ' + '{\n') for v in ns))
    
def write_ns_epilogue(f, ns):
    f.write(''.join(('}; // namespace ' + v + '\n') for v in ns))

def ns_from_path(path : Path):
    ns = ["notsa", "script"]

    for p in reversed(path.parents):
        pn = p.name.lower()
        if pn:
            ns.append(pn)

    if path.is_file():
        ns.append(path.stem.lower())

    return ns

def process_hpp_to_cpp():
    for file in Path("Commands/").rglob("*.hpp"):
        ns = ns_from_path(file)
        
        with file.open("r+", encoding='utf-8') as f:
            f.seek(0)

            all_other : list[str] = []
            registers : list[str] = []
            all_other.extend(('#include <StdInc.h>\n', ))
            for line in  f.readlines()[1:]: # Skip `#pragma once` at the beginning
                if line.startswith("REGISTER_COMMAND_HANDLER"):
                    registers.append('    ' + line)
                else:
                    all_other.append(line)

            f.truncate(0) # Clear file
            f.seek(0)
            f.write(''.join(all_other))

            # Write registering
            #write_ns_prologue(f, ns)
            f.write("\n")
            f.write(f"void {'::'.join(ns)}::RegisterHandlers() {{\n")
            f.write(''.join(registers))
            f.write("}\n")
            #write_ns_epilogue(f, ns)
        file.rename(file.with_suffix(".cpp")) # Rename .hpp to .cpp
        
        # Write new header file
        #with file.with_suffix(".hpp").open("w", encoding='utf-8') as f: # Create new .hpp and add this to it
        #    write_ns_prologue(f, ns)
        #    f.write("void RegisterHandlers();\n")
        #    write_ns_epilogue(f, ns)
def write_commands_hpp():
    for dir_name in ("Commands", "Commands/CLEO", "Commands/CLEO/Extensions"):
        curr_dir_path = Path("./" + dir_name)
        with (curr_dir_path / "Commands.hpp").open("w") as f:
            ns = ns_from_path(curr_dir_path)

            f.write("#pragma once\n\n")

            write_ns_prologue(f, ns)
            for file in curr_dir_path.glob("*.cpp"):
                f.write(f'namespace {file.stem.lower()} {{ void RegisterHandlers(); }};\n')    
            write_ns_epilogue(f, ns)

process_hpp_to_cpp()
write_commands_hpp()
