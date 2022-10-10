# bin_conver_lecroy

Repository for the conversion of .trc files, a Lecroy proprietary binary file created by this brand's oscilloscopes.

A working scripts in C++ is present. A test file is present the */data*.

Two functions, on the file named *full_functions_to_read_txt_and_trc.cpp*, are presented as an example to be integrated in a a bigger project. These trim the name of the input file, check the extension, and write the values to two vectors (time and amplitude).
Note: This works only for .txt and .trc files create by Lecroy branded oscilloscopes. Other sources might require some changes.

## Installation

A working ROOT and C++ installations are required.

### Python Version

For the python version please check this repository: https://github.com/yetifrisstlama/readTrc

## Usage

Unix/MacOS

```bash
c++ -O3 convert_Trc.cpp -o oscilloscope_binary_conv.out `root-config --glibs --cflags`
./oscilloscope_binary_conv.out  
```

## Contributing

Pull requests are welcome, as well as verbal comments & tips.