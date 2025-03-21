# proParalela
A project for a parallel programming class, structured to help students learn and experiment with parallel computing concepts. It includes simple examples, tasks, and projects written in C and C++.  Project Structure

## Depencies
```bash
sudo apt update ; sudo apt install g++ gdb;

sudo apt-get install openmpi-bin libopenmpi-dev ; sudo apt-get install mpich libmpich-dev;

sudo apt install openmpi-bin libopenmpi-dev;

find /usr -name "mpicxx";
```

## tasks.json
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++ build active file",
            "command": "/usr/bin/mpicxx",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-fopenmp",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
        
    ],
    "version": "2.0.0"
}
```

## c_cpp_properties.json
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/lib/x86_64-linux-gnu/openmpi/include",
                "/usr/include"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/mpicc",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```