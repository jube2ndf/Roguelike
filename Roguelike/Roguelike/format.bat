@echo off

echo Formatting source files...

for /R %%f in (*.cpp *.c *.hpp *.h) do (
    clang-format -i "%%f"
    echo %%f
)

echo.
echo Done.
pause