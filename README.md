# Little OS

## References

[Little OS Book](https://littleosbook.github.io/)  
[OS Dev Wiki](https://wiki.osdev.org/Bare_Bones)

### Frame buffer references

[VGA Text Mode](https://en.wikipedia.org/wiki/VGA_text_mode)

## Known issues

I started basing this example off of the code in the Little OS Book. Some of the Little OS Book code is buggy, though I think I've fixed bugs pointed out by others in this implementation. I've used OS Dev Wiki bare bones section to sanity check the code and ideas.

The build system is CMake (minimum version specified in the root directory). I wanted to use CMake instead of GNU Makefiles as specified in Little OS Book because I think CMake leads to better management of library hierarchy and is better supported by C++ specific tools I want to use (clang suite, eventually). There is a custom target to run the OS in a Bochs VM, but it assumes setup for generating the ISO image that is not checked in. The documentation is in the Little OS Book.