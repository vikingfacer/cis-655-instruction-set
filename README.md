# cis-655-instruction-set
cis-655-group-project

# build me
Requirements: cmake & build-generator (make, nmake, ninja, etc...)
_all instructions assume commands are ran in the root of the directory_

make a directory for the build
```
mkdir build
```

configure the build (vanilla)
```
cmake -S . -B build
```

configure the build (ninja flavored)
```
cmake -S . -B build -G Ninja
```

build the build
```
cd build
<build command: make, nmake, etc..>
```

build the build ninja style
```
ninja -C build
```

# run me
navigate to into build directory
```
cd build
```
run the emulator
```
./emulator/emulator
```
run the parser
```
./parser/parser
```





