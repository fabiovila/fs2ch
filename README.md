# Easily embed existing filesystem in C/C++ applications

Recursively search for files in current or specified path and creates a C Include file with array of follow struct:

```
struct {
  const char *name;             // Name of file
  const char *mime;             // Mime Type
  int size;                     // Size
  const unsigned char *data;    // file content
 };
```

This struct is defined as `const volatile stFile __attribute__ ((section (".rodata"))) fsFiles[];`

You get the number of files found ( and the fsFiles size ) from `#define FS_FILES	X`

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

