cmd_/home/hds/github/kernel-module/temp/hello/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/hds/github/kernel-module/temp/hello/hello.ko /home/hds/github/kernel-module/temp/hello/hello.o /home/hds/github/kernel-module/temp/hello/hello.mod.o;  true