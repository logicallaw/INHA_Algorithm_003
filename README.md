# INHA_Algorithm_003

## Build and Run Instructions

0. Set Google Test Library Path
   ```bash
   {
      "configurations": [
         {
            "name": "Mac",
            "includePath": [
                  "${workspaceFolder}/**",
                  "/opt/homebrew/Cellar/googletest/1.16.0/include"
                  ],
            "defines": [],
            "macFrameworkPath": [
                  "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks"
            ],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-arm64"
         }
      ],
      "version": 4
   } 
   ```

1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

2. Compile your source code:
   ```bash
   cmake ..
   ```

3. Run make:
   ```bash
   make
   ```

4. Execute the program:
    ```bash
    ./INHA_Algorithm_003
    ```

5. Etc./ shortcut command:
   ```
   cmake .. && make && ./INHA_Algorithm_003
   ```