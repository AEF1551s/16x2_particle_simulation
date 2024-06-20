
# Description

Particle simulation on 16x2 char display.
# In development..
  

## Prerequisites

- CMake

-  arm-none-eabi toolchain

-  OpenOCD

  

### Installing prerequisites

#### Ubuntu/Linux

##### CMake

Install build tools and libraries that CMake depends on:  
`$ sudo apt-get install build-essential libssl-dev`
Go to the temp directory:  
`$ cd /tmp`
Then, enter the following command to download the source code:  
`$ wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz`
Once the tar.gz file is downloaded, enter the following command to extract it:  
`$ tar -zxvf cmake-3.20.0.tar.gz`
Then move to the extracted folder as follows:  
`$ cd cmake-3.20.0`
Finally, run the following commands to compile and install CMake:  
`./bootstrap`
Then  build:  
`$ make`  
And install:  
`$ sudo make install`
##### arm-none-eabi toolchain
To install run:
`$ sudo apt-get install gcc-arm-none-eabi`

##### OpenOCD
Clone OpenOCD repository:
`$ sudo git clone https://github.com/openocd-org/openocd`
Run bootsrap:  
`$ ./bootstrap`
Run configure:  
`$ ./configure --prefix=/usr/local/ --enable-ftdi --enable-stlink --enable-jlink`
Build:  
`$ make`
Install:
`$ sudo make install`

- OpenOCD requires additional dependecies:

`build-essentials`
`libtool`
`libusb-1.0-0`
`libusb-1.0-0-dev`
`gdb-multiarch`
`libjaylink-dev`

To install run:
`$ sudo apt-get install [dependecies]`

#### Other OS

See official installation and user guides

  

## Build
Go to project directory and create build folder:
`$ mkdir build`
Generate Makefiles, example is given with *Unix Makefiles*:
`$ cmake -G "Unix Makefiles" -B ./build`
Then build project without flashing option:
`$ cmake -D FLASH=OFF build`
Run make in /build to compile:
`$ make`
  

## Flashing
Flashing is done using OpenOCD. To flash you must specify `-D FLASH=ON` when building the project.
The openocd command is excecuted as post-build command.
To change the interface and target configuration, see CMakeLists.txt `openocd_flags`.
  
 Build project with flashing option:
`$ cmake -D FLASH=ON build`
Run make in /build to compile and flash:
`$ make`

## Debugging
In this project debugging is done using OpenOCD and with VSCode extensions, for easier visual debugging: 
`Cortex-Debug`

To see register contents, access serial output and read memory use extensions such as: 
`MemoryView`
`Peripheral Viewer`
`Serial Monitor`
  
  For this to work inside VSCode the *launch* **OpenOCD configuration** and *settings* **cortex-debug** paths must be set.
For additional debug features, setup VSCode as per **extension setup guides**.
## Reason for porting existing library
...  

## Encountered problems and solutions
...  
