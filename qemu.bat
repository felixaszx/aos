start qemu-system-x86_64.exe -S -s --machine q35 --cpu max -m 4G --smp 8 -bios x86_64-OVMF.fd  --cdrom build/image.iso -monitor stdio
