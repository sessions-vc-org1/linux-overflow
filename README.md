## Requirements
- Docker
- VSCode

## Running
Download the Dev containers Extension. Set the Veracode Extension to run on a workspace in your `Open user Settings (JSON).
- After connecting to the Dev Container on VSCode using `Dev Containers: Open folder in Container`, you can download the Veracode extension and run the program normally. You have to reinstall the SCA IDE agent for this container.

## Working inside a container
VSCode has a good explanation of how this works, I recommend reading it [here](https://code.visualstudio.com/docs/devcontainers/containers#_quick-start-open-an-existing-folder-in-a-container).

## Running the project
`make`

This should build the .o (object) files. These are then linked into the `linux_app` executable.

## Python bindings (pybind11)
Build the C++ executable and Python extension module:

`make`

This produces:
- `linux_app`
- `paymentlib<python-extension-suffix>` (for example, `paymentlib.cpython-310-x86_64-linux-gnu.so`)

### End-to-end flow
1. `make` compiles native sources and also builds the pybind11 extension module from `python_bindings.cpp`.
2. The generated module is named `paymentlib` + Python extension suffix (from `python3-config --extension-suffix`).
3. `python3 demo_paymentlib.py` imports `paymentlib` and calls the exposed C++ method.

### How Python finds `paymentlib`
Python includes the current working directory in `sys.path` as an import location.
Because the built file `paymentlib*.so` is created in the project root, running:

`python3 demo_paymentlib.py`

from the same directory allows `import paymentlib` to resolve automatically.
If you run the script from another directory, either:
- run it from the project root, or
- set `PYTHONPATH` to include this project directory.

Run the Python demo that uses the C++ module:

`python3 demo_paymentlib.py`

## Reviewing results
the value from this is in `CWE-121: Stack-based Buffer Overflow`. You can see the number of bites allocated to variables that are copied iwth strcpy, and this is something no other vendor does.


