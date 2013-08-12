call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat"

devenv %1 /Clean "RELEASE|Win32"
devenv %1 /Rebuild "RELEASE|Win32"

