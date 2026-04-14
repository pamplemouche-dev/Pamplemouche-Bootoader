@echo off
set FILENAME=BOOTX64
set CLANG_PATH="C:\Program Files\LLVM\bin\clang.exe"

%CLANG_PATH% -target x86_64-unknown-windows -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I../include -c ../src/main.c -o main.o

%CLANG_PATH% -target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -o ../EFI/BOOT/%FILENAME%.EFI main.o

echo Compilation terminee. Fichier genere dans EFI/BOOT/%FILENAME%.EFI
pause
