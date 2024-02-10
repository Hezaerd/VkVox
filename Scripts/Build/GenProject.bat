@echo off
pushd %~dp0\..\..\
setlocal

echo "Root dir : %CD%"

call Vendor\Premake\Bin\premake5.exe vs2022


pause
popd