Import("env")
import re, pathlib

root = pathlib.Path(env["PROJECT_DIR"])
for path in (root / "lib").rglob("HvUtils.h"):
    original = path.read_text()
    text = re.sub(r"#define hv_malloc\(_n\) .*", "#define hv_malloc(_n) hv_psram_malloc(_n)", original)
    text = re.sub(r"#define hv_realloc\(a, b\) .*", "#define hv_realloc(a, b) hv_psram_realloc(a, b)", text)
    if '#include "heavy_psram.h"' not in text:
        text = '#include "heavy_psram.h"\n' + text
    if text != original:
        path.write_text(text)
        print("Patched", path)