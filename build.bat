@echo off
setlocal

REM
cd /d "%~dp0"

REM
set "PATH=C:\msys64\mingw64\bin;C:\msys64\usr\bin;%PATH%"

REM
if not exist bin mkdir bin

echo Building...

g++ -std=c++17 -g -Wall -Wno-unknown-pragmas ^
  src/*.cpp ^
  -o bin/main.exe ^
  -IC:/of/libs/openFrameworks ^
  -IC:/of/libs/openFrameworks/app ^
  -IC:/of/libs/openFrameworks/gl ^
  -IC:/of/libs/openFrameworks/graphics ^
  -IC:/of/libs/openFrameworks/math ^
  -IC:/of/libs/openFrameworks/utils ^
  -IC:/of/libs/openFrameworks/types ^
  -IC:/of/libs/openFrameworks/events ^
  -IC:/of/libs/openFrameworks/communication ^
  -IC:/of/libs/openFrameworks/3d ^
  -IC:/of/libs/openFrameworks/sound ^
  -IC:/of/libs/openFrameworks/video ^
  -IC:/of/libs/tess2/include ^
  -IC:/of/libs/glm/include ^
  -IC:/of/libs/utf8/include ^
  -IC:/of/libs/json/include ^
  -IC:/of/libs/pugixml/include ^
  -IC:/of/libs/uriparser/include ^
  -IC:/of/libs/rtAudio/include ^
  -IC:/of/libs/glfw/include ^
  -IC:/of/libs/FreeImage/include ^
  -IC:/of/libs/curl/include ^
  -IC:/of/libs/openssl/include ^
  -IC:/of/libs/cairo/include/cairo ^
  -IC:/of/libs/kiss/include ^
  -IC:/of/libs/kiss/include/include ^
  -IC:/msys64/mingw64/include/freetype2 ^
  -IC:/msys64/mingw64/include/cairo ^
  -IC:/msys64/mingw64/include/glib-2.0 ^
  -IC:/msys64/mingw64/lib/glib-2.0/include ^
  -LC:/of/libs/openFrameworksCompiled/lib/msys2 ^
  -LC:/of/libs/tess2/lib/msys2 ^
  -LC:/of/libs/kiss/lib/msys2 ^
  -lopenFrameworks ^
  -lkiss ^
  -ltess2 ^
  -lglfw3 ^
  -lglew32 ^
  -lfreeimage ^
  -lfreetype ^
  -lcairo ^
  -lcurl ^
  -luriparser ^
  -lpugixml ^
  -lssl ^
  -lcrypto ^
  -lz ^
  -lrtaudio ^
  -lopenal ^
  -lsndfile ^
  -lmpg123 ^
  -lassimp ^
  -lopengl32 ^
  -lglu32 ^
  -lgdi32 ^
  -lmsimg32 ^
  -ldsound ^
  -lwinmm ^
  -ldxguid ^
  -lstrmiids ^
  -luuid ^
  -lole32 ^
  -loleaut32 ^
  -lsetupapi ^
  -lwsock32 ^
  -lws2_32 ^
  -liphlpapi ^
  -lcomdlg32

if errorlevel 1 (
    echo.
    echo Build FAILED.
    exit /b 1
)

echo.
echo Build succeeded: bin\main.exe
endlocal