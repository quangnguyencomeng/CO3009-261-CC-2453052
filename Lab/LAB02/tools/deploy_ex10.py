"""Deploy a compiled HEX to the supplied Proteus project, keeping backups.

Proteus stores a length-prefixed property string in ROOT.CDB and ROOT.DSN.
Preserve the original byte length/record offsets by replacing the old PROGRAM
property with a shorter relative path followed by whitespace (blank lines).
All other ZIP members and binary bytes remain unchanged.
"""
from datetime import datetime
from hashlib import sha256
from pathlib import Path
import re
import shutil
import struct
import zipfile

ROOT = Path(__file__).resolve().parents[1]
BUILT = ROOT / "Debug" / "LAB02.hex"
PROJECT = Path(r"C:\Users\Acer\Downloads\Exercise9-10.pdsprj")
DEST_HEX = PROJECT.with_name("lab2.2.hex")


def check_hex(path):
    base = 0
    image = {}
    eof = False
    for line in path.read_text(encoding="ascii").splitlines():
        assert line.startswith(":"), "Invalid Intel HEX record"
        record = bytes.fromhex(line[1:])
        assert len(record) == record[0] + 5 and sum(record) % 256 == 0
        address = int.from_bytes(record[1:3], "big")
        kind, data = record[3], record[4:-1]
        if kind == 4:
            base = int.from_bytes(data, "big") << 16
        elif kind == 0:
            for offset, value in enumerate(data):
                absolute = base + address + offset
                assert 0x08000000 <= absolute < 0x08008000
                assert absolute not in image
                image[absolute] = value
        elif kind == 1:
            eof = True
    assert eof and image
    vector = bytes(image[0x08000000 + i] for i in range(8))
    sp, reset = struct.unpack("<II", vector)
    assert 0x20000000 < sp <= 0x20002800
    assert reset & 1 and (reset & ~1) in image
    print(f"HEX validated: {len(image)} flash bytes; reset vector {reset:#x}")


def patched_member(name, original):
    if name not in ("ROOT.CDB", "ROOT.DSN"):
        return original
    matches = [m for m in re.finditer(rb"\{PROGRAM=[^}]+\}", original)
               if not m.group().startswith(b'{PROGRAM="')]
    assert len(matches) == 1, f"Unexpected PROGRAM count in {name}"
    match = matches[0]
    target = b"{PROGRAM=lab2.2.hex}"
    old = match.group()
    assert old.lower().endswith(b"lab2.2.hex}")
    assert len(target) <= len(old)
    # Confirm this is the first property in the expected length-prefixed record.
    count = struct.unpack_from("<I", original, match.start() - 4)[0]
    assert len(old) <= count <= 4096
    assert match.start() + count <= len(original)
    replacement = target + b"\n" * (len(old) - len(target))
    result = original[:match.start()] + replacement + original[match.end():]
    assert len(result) == len(original)
    print(f"{name}: PROGRAM -> lab2.2.hex (binary record length preserved)")
    return result


def main():
    check_hex(BUILT)
    stamp = datetime.now().strftime("%Y%m%d-%H%M%S-%f")
    with zipfile.ZipFile(PROJECT) as archive:
        assert archive.testzip() is None
        members = [(info, archive.read(info)) for info in archive.infolist()]
        comment = archive.comment
    modified = [(info, patched_member(info.filename, data)) for info, data in members]
    temp_project = PROJECT.with_name(f"Exercise9-10.ex10-{stamp}.tmp")
    with zipfile.ZipFile(temp_project, "w") as archive:
        archive.comment = comment
        for info, data in modified:
            archive.writestr(info, data)
    with zipfile.ZipFile(temp_project) as archive:
        assert archive.testzip() is None
        for info, data in modified:
            assert archive.read(info.filename) == data
    for path in (PROJECT, DEST_HEX):
        backup = path.with_name(path.name + f".before-ex10-{stamp}.bak")
        shutil.copy2(path, backup)
        print(f"Backup: {backup}")
    shutil.copy2(BUILT, DEST_HEX)
    temp_project.replace(PROJECT)
    assert sha256(BUILT.read_bytes()).digest() == sha256(DEST_HEX.read_bytes()).digest()
    check_hex(DEST_HEX)
    print(f"Updated: {PROJECT}")
    print(f"Updated: {DEST_HEX}")


if __name__ == "__main__":
    main()
