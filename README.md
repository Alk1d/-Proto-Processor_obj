# Prototype of .obj file format processor
Qt/C++ console application for university field studies. Due to Qt+MSVC build, some limitations occur during development: 
1. Standard Qt application output doesn't support user input, need to use terminal.
2. Standard streams don't work, workaround with QDebug and QTextStream.
3. Absolute file path is needed in [entering file path.](https://github.com/Alk1d/-Proto-Processor_obj/blob/main/main.cpp#L92)
## Output example
![image_2024-06-26_105333099](https://github.com/Alk1d/-Proto-Processor_obj/assets/108924851/76499217-7238-491c-8c99-aa00f3585feb)
