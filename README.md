# Easily embed existing filesystem in C/C++ applications

Search for files in current or specified path and creates a C Include file with array of follow struct:

```
struct stFile {
  const char *name;             // Name of file
  const char *mime;             // Mime Type
  int size;                     // Size
  const unsigned char *data;    // file content
 };
```

All found files are stored at array `const volatile stFile __attribute__ ((section (".rodata"))) fsFiles[];` in **out.h**.
Just include **out.h** in your application and search for they in `fsFiles[i].name`. Found it, the content and size are in `fsFiles[i].size` and `fsFiles[i].data`.

The number of files found is set in `#define FS_FILES	X`


## Usage:
```
./fs2ch [Input PATH - Optional] [Output filename - Optional]
```
```
./fs2ch 
```

**fs2ch** searches for files in current directory and creates **out.h** if run without  arguments

## Install
Just do `make` 

## Dependencies
`Boost Filesystem`

## Test
Folder **test-example** have test and example how to use **fsFiles[]**. It 
will embed files from **input** folder and recreate it to folder 
**output** and run diff. If diff return none the files are equal.
To run the test enter in `test-example` and do `make`

### Uses
I created it for a embedded system with FreeRTOS + Mongoose Web Server. 

I'm embedding Angular.js, Fonts, Images and HTML files in the Flash of my ARM Cortex M3 board. 

