@echo off

if not exist ".build\windows" (
  mkdir ".build\windows"
)

cl ^
  /Fo:.build\windows\practice1.obj ^
  /Fe:.build\windows\practice1.exe ^
  main.c

if %errorlevel% == 0 (
  .build\windows\practice1.exe
)
