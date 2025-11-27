# N-Queens Solver

Web UI in `web/` and C++ solver in `src/`.

Quick start

- Web UI: open `web/index.html` in a browser (no build required).
- Or serve the `web/` folder locally:

```powershell
cd "D:\Nqueen Solver Project\web"
python -m http.server 8000
Start-Process http://localhost:8000
```

- Native C++ solver (optional):

```powershell
cd "D:\Nqueen Solver Project"
mkdir build -ErrorAction SilentlyContinue
g++ -g src\solver.cpp -o build\solver.exe
.\build\solver.exe 8 1
```

Notes

- If you see linker errors when compiling on Windows, try building in the MSYS2 `mingw64` shell or use WSL/Visual Studio toolchain.
- The web UI is fully client-side (HTML/CSS/JS) and requires only a browser.
