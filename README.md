# G-Mem (for Mac)

Program used to read the memory contents of an external process in MacOS,
specifically the [RC4](https://en.wikipedia.org/wiki/RC4) cipher used by Habbo to encrypt server-client communication. 
This program is used by [G-Earth](https://github.com/sirjonasxx/G-Earth) application to inject/intercept packets in Habbo. 

This program is a hard fork of [G-Mem](https://github.com/sirjonasxx/G-Mem).
## Install

### Dependencies
The software only depends on one library for logging [spdlog](https://github.com/gabime/spdlog).
This can be installed using various package managers (see repository for more example), 
here's how to install it with brew:
```shell
brew install spdlog
```

### Building
In order to build an executable from the source code, perform the following steps:
1. Create a directory to save the executable to:
```shell
mkdir build
```
2. Enter the build directory
```shell
cd build
```
3. Build using CMake
```shell
cmake ..
```
4. Create executable
```shell
make
```
This should generate an executable file at `build/g_mem_mac`.

### System Integrity Protection (SIP)
Modern machines running MacOS have a security feature that shields of the memory of processes from other processes. 
Depending on your machine you may have to [disable SIP](https://developer.apple.com/documentation/security/disabling_and_enabling_system_integrity_protection).
Especially for M1 macs it is required to disable SIP. 

### Patch Entitlements
In order to access the memory contents of the Habbo process,
we need to enable some custom flags for the application.

This can be done by running [patch_entitlements.sh](patch_entitlements.sh)
with as argument the path to the Habbo AIR app.

You can run the script as follows:
```shell
sudo sh patch_entitlements.sh "/Users/YOURNAME/Library/Application Support/Habbo Launcher/downloads/air/37/Habbo.app"
```
* Replace `YOURNAME` with your username.

## Usage

The build program is ran by G-Earth and attempts to retrieve the memory contents 
of a running Habbo process. The results, if obtained successfully, are printed to the console,
which is then read by the G-Earth process.

The `build/g_mem_mac` executable generated in the building step can be renamed to `G-Mem` and replace the existing `G-Mem` executable in the latest G-Earth release. 

### Logs
Logs are written to the following directory:
`/Users/YOURNAME/.g_mem/logs`
Please make sure to include your logs if experiencing an issue. 
