<!-- omit in toc -->
# Raspberry Pi Pico W5100S Azure IoT SDK Examples

RP2040 W5100 network examples - Azure cloud functions, Azure IoT SDK, Azure IoT device client, ...

- [1. 🎯 Azure-IoT-SDK](#1--azure-iot-sdk)
  - [1.1. 3rd party SDKs](#11-3rd-party-sdks)
- [2. 🎓 Getting started](#2--getting-started)
  - [2.1. 📚 Download SDK library](#21--download-sdk-library)
    - [2.1.1. Download azure-iot-sdk-c library](#211-download-azure-iot-sdk-c-library)
    - [2.1.2. Download mbedtls library](#212-download-mbedtls-library)
    - [2.1.3. Building mbedtls library](#213-building-mbedtls-library)
  - [2.2. 🗂 Build a sample](#22--build-a-sample)
    - [2.2.1. Make "port" directory for Azure IoT SDK, mbedtls](#221-make-port-directory-for-azure-iot-sdk-mbedtls)
    - [2.2.2. Modify CMakeLists.txt](#222-modify-cmakeliststxt)
    - [2.2.3. Set your board network information and select application](#223-set-your-board-network-information-and-select-application)
    - [2.2.4. Set the key information](#224-set-the-key-information)
  - [2.3. ⏳ Build project](#23--build-project)
    - [2.3.1. Build command](#231-build-command)
    - [2.3.2. Example command log](#232-example-command-log)
  - [2.4. 📝 Sample application results](#24--sample-application-results)
    - [2.4.1. 📬 "iothub_ll_telemetry_sample" application result](#241--iothub_ll_telemetry_sample-application-result)
    - [2.4.2. 📩 "iothub_ll_c2d_sample" application result](#242--iothub_ll_c2d_sample-application-result)
    - [2.4.3. 🔐 "iothub_ll_client_x509_sample" application result](#243--iothub_ll_client_x509_sample-application-result)
    - [2.4.4. 🚢 "prov_dev_client_ll_sample" application result](#244--prov_dev_client_ll_sample-application-result)

------



# 1. 🎯 Azure-IoT-SDK

App|Description
---|---
[Azure IoT SDK example](examples) | Basic Azure cloud functions with Azure IoT SDK. (NonOS + WIZnet W5100S)



## 1.1. 3rd party SDKs

- [Azure IoT C SDKs and Libraries](https://github.com/Azure/azure-iot-sdk-c)
- [Mbed TLS](https://github.com/ARMmbed/mbedtls)
- [WIZnet ioLibrary](https://github.com/Wiznet/ioLibrary_Driver)
  - for CMake users => https://github.com/Wiznet/RP2040-HAT-C/blob/main/libraries/CMakeLists.txt



# 2. 🎓 Getting started

See [Getting Started with the Raspberry Pi Pico](https://rptl.io/pico-get-started) and the README in the [pico-sdk](https://github.com/raspberrypi/pico-sdk) for information
on getting up and running.



## 2.1. 📚 Download SDK library



### 2.1.1. Download azure-iot-sdk-c library

This repo get the local copy version for this project.

If you need, you can get this version from releae section in the git repo
- LTS_07_2021_Ref01 : https://github.com/Azure/azure-iot-sdk-c/releases/tag/LTS_07_2021_Ref01

- 📑 For details, Please read [_0_install_Azure_IoT_SDK.md](_0_install_Azure_IoT_SDK.md)



### 2.1.2. Download mbedtls library

This repo get the local copy version for this project.

If you need, you can get this version from release section in their git repo
- Mbed TLS 3.0.0 - https://github.com/ARMmbed/mbedtls/releases/tag/v3.0.0



## 2.2. 🗂 Build a sample



### 2.2.1. Make "port" directory for Azure IoT SDK, mbedtls

For Pico W5100S platform, we need to make port codes, please check out the [Microsoft Azure SDK porting guide document](https://github.com/Azure/azure-c-shared-utility/blob/master/devdoc/porting_guide.md).

From upper porting guide, the repo has a example `RP2040-HAT-AZURE-C\port\azure-iot-sdk-c` directory for this sample applications.



### 2.2.2. Modify CMakeLists.txt

In the following [`RP2040-HAT-AZURE-C/CMakeLists.txt`](CMakeLists.txt) file, find the line similar to this and replace it as your environment:

```bash
# Set the project root directory if it's not already defined, as may happen if
# the tests folder is included directly by a parent project, without including
# the top level CMakeLists.txt.
if(NOT DEFINED AZURE_SDK_DIR)
    set(AZURE_SDK_DIR ${CMAKE_SOURCE_DIR}/libraries/azure-iot-sdk-c)
    message(STATUS "AZURE_SDK_DIR = ${AZURE_SDK_DIR}")
endif()

if(NOT DEFINED WIZNET_DIR)
    set(WIZNET_DIR ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver)
    message(STATUS "WIZNET_DIR = ${WIZNET_DIR}")
endif()

if(NOT DEFINED MBEDTLS_LIB_DIR)
    set(MBEDTLS_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/mbedtls)
    message(STATUS "MBEDTLS_LIB_DIR = ${MBEDTLS_LIB_DIR}")
endif()

if(NOT DEFINED PORT_DIR)
    set(PORT_DIR ${CMAKE_SOURCE_DIR}/port)
    message(STATUS "PORT_DIR = ${PORT_DIR}")
endif()
```



### 2.2.3. Set your board network information and select application

In the following [`RP2040-HAT-AZURE-C/examples/main.c`](examples/main.c) source file, find the line similar to this and replace it as you want:

```C
(...)

// The application you wish to use should be uncommented
//
#define APP_TELEMETRY
//#define APP_C2D
//#define APP_CLI_X509
//#define APP_PROV_X509

// The application you wish to use DHCP mode should be uncommented
#define _DHCP
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
#ifdef _DHCP
        .dhcp = NETINFO_DHCP // DHCP enable/disable
#else
        // this example uses static IP
        .dhcp = NETINFO_STATIC
#endif
};
```



### 2.2.4. Set the key information

Edit the [`RP2040-HAT-AZURE-C/examples/sample_certs.c`](examples/sample_certs.c) entering the proper connection string and key value from the Azure Portal:

```C
/* Paste in the your iothub connection string  */
const char pico_az_connectionString[] = "[device connection string]";

const char pico_az_x509connectionString[] = "[device connection string]";

const char pico_az_x509certificate[] =
"-----BEGIN CERTIFICATE-----""\n"
"-----END CERTIFICATE-----";

const char pico_az_x509privatekey[] =
"-----BEGIN PRIVATE KEY-----""\n"
"-----END PRIVATE KEY-----";

const char pico_az_id_scope[] = "[ID Scope]";

const char pico_az_COMMON_NAME[] = "[custom-hsm-device]";

const char pico_az_CERTIFICATE[] =
"-----BEGIN CERTIFICATE-----""\n"
"-----END CERTIFICATE-----";

const char pico_az_PRIVATE_KEY[] =
"-----BEGIN PRIVATE KEY-----""\n"
"-----END PRIVATE KEY-----";
```



## 2.3. ⏳ Build project



### 2.3.1. Build command

Run the following CMake commands from the root of the repository:

```
mkdir build
cd build

# As your environment, select
  cmake .. -G "MSYS Makefiles" ## on MSYS2 (MinGW64) + Windows 10 Platform
# or
  cmake .. -G "Visual Studio 15 2017" ## For Visual Studio 2017
# or
  cmake .. -G "Visual Studio 16 2019" -A Win32
# or
  cmake ..

cd examples
make
```

Then, copy generated "main.uf2" file into your RP-Pico board. Done!!



### 2.3.2. Example command log

> on MSYS2 (MinGW64) + Windows 10 Platform

```
(PWD) RP2040-HAT-AZURE-C/build
$ cd ..

(PWD) RP2040-HAT-AZURE-C
$ rm -rf build

(PWD) RP2040-HAT-AZURE-C
$ mkdir build

(PWD) RP2040-HAT-AZURE-C
$ cd build

(PWD) RP2040-HAT-AZURE-C/build
$ cmake .. -G "MSYS Makefiles"
-- PICO_SDK_PATH = D:/RP2040/RP2040-HAT-AZURE-C/libraries/pico-sdk
-- Found Git: C:/msys64/usr/bin/git.exe (found version "2.34.1")
RP2040-HAT-AZURE-C patch utils found
Submodule 'libraries/azure-iot-sdk-c' (https://github.com/Azure/azure-iot-sdk-c) registered for path 'libraries/azure-iot-sdk-c'
Submodule 'libraries/ioLibrary_Driver' (https://github.com/Wiznet/ioLibrary_Driver) registered for path 'libraries/ioLibrary_Driver'
Submodule 'libraries/mbedtls' (https://github.com/ARMmbed/mbedtls) registered for path 'libraries/mbedtls'
Submodule 'libraries/pico-extras' (https://github.com/raspberrypi/pico-extras.git) registered for path 'libraries/pico-extras'
Submodule 'libraries/pico-sdk' (https://github.com/raspberrypi/pico-sdk.git) registered for path 'libraries/pico-sdk'
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/ioLibrary_Driver'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/mbedtls'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/pico-extras'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/pico-sdk'...
Submodule path 'libraries/azure-iot-sdk-c': checked out '808a5595f98853a5f2eae2c67dd9b3608a2338ea'
Submodule path 'libraries/ioLibrary_Driver': checked out 'e285249784ce6c09b869502bb6715337b45278e3'
Submodule path 'libraries/mbedtls': checked out '8df2f8e7b9c7bb9390ac74bb7bace27edca81a2b'
Submodule path 'libraries/pico-extras': checked out '77eae2836638baf2f61b321eb61125da99bb4445'
Submodule path 'libraries/pico-sdk': checked out 'bfcbefafc5d2a210551a4d9d80b4303d4ae0adf7'
Submodule 'azure-c-shared-utility' (https://github.com/Azure/azure-c-shared-utility.git) registered for path 'c-utility'
Submodule 'deps/azure-c-testrunnerswitcher' (https://github.com/Azure/azure-c-testrunnerswitcher.git) registered for path 'deps/azure-c-testrunnerswitcher'
Submodule 'deps/azure-ctest' (https://github.com/Azure/azure-ctest.git) registered for path 'deps/azure-ctest'
Submodule 'deps/azure-macro-utils-c' (https://github.com/Azure/azure-macro-utils-c.git) registered for path 'deps/azure-macro-utils-c'
Submodule 'deps/parson' (https://github.com/kgabis/parson.git) registered for path 'deps/parson'
Submodule 'deps/uhttp' (https://github.com/Azure/azure-uhttp-c.git) registered for path 'deps/uhttp'
Submodule 'deps/umock-c' (https://github.com/Azure/umock-c.git) registered for path 'deps/umock-c'
Submodule 'provisioning_client/deps/RIoT' (https://github.com/Microsoft/RIoT.git) registered for path 'provisioning_client/deps/RIoT'
Submodule 'provisioning_client/deps/utpm' (https://github.com/Azure/azure-utpm-c.git) registered for path 'provisioning_client/deps/utpm'
Submodule 'azure-uamqp-c' (https://github.com/Azure/azure-uamqp-c.git) registered for path 'uamqp'
Submodule 'azure-umqtt-c' (https://github.com/Azure/azure-umqtt-c.git) registered for path 'umqtt'
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/c-utility'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/deps/azure-c-testrunnerswitcher'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/deps/azure-ctest'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/deps/azure-macro-utils-c'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/deps/parson'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/deps/uhttp'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/deps/umock-c'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/provisioning_client/deps/RIoT'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/provisioning_client/deps/utpm'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/uamqp'...
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c/umqtt'...
Submodule path 'c-utility': checked out '73a2039cc0de5ececf5755ebe731a6b5b98f85da'
Submodule path 'deps/azure-c-testrunnerswitcher': checked out '8734bd6c53c88dd6c0cea8e87d70b9964726484a'
Submodule path 'deps/azure-ctest': checked out '4aa84c45236ecda21983fb682f542f17d0b21e19'
Submodule path 'deps/azure-macro-utils-c': checked out '5926caf4e42e98e730e6d03395788205649a3ada'
Submodule path 'deps/parson': checked out '8beeb5ea4da5eedff8d3221307ef04855804a920'
Submodule path 'deps/uhttp': checked out 'db8ac9c1353fe05cf6917e8ec8bcb866bf4a6f11'
Submodule path 'deps/umock-c': checked out '504193e65d1c2f6eb50c15357167600a296df7ff'
Submodule path 'provisioning_client/deps/RIoT': checked out 'e878185a8fb433902bee185b6f3a8c66aa232bff'
Submodule path 'provisioning_client/deps/utpm': checked out '1d0642281086669c6239f9bc1b085463044d69d6'
Submodule path 'uamqp': checked out 'b75cdb7e1736a388fe3e9fc2a99493aa1db6f43f'
Submodule path 'umqtt': checked out '12cb55ee5a926a124f22ad737c7cec35f6af7165'
Submodule 'tinyusb' (https://github.com/hathach/tinyusb.git) registered for path 'lib/tinyusb'
Cloning into '/d/RP2040/RP2040-HAT-AZURE-C/libraries/pico-sdk/lib/tinyusb'...
Submodule path 'lib/tinyusb': checked out 'd49938d0f5052bce70e55c652b657c0a6a7e84fe'
submodules ioLibrary_Driver initialised
Running patch D:/RP2040/RP2040-HAT-AZURE-C/patches/01_iolibrary_driver_ethernet_chip.patch
Running patch D:/RP2040/RP2040-HAT-AZURE-C/patches/02_iolibrary_driver_ftp_client.patch
Running patch D:/RP2040/RP2040-HAT-AZURE-C/patches/03_iolibrary_driver_sntp.patch
PICO_SDK_PATH is D:/RP2040/RP2040-HAT-AZURE-C/libraries/pico-sdk
Defaulting PICO_PLATFORM to rp2040 since not specified.
Defaulting PICO platform compiler to pico_arm_gcc since not specified.
-- Defaulting build type to 'Release' since not specified.
PICO compiler is pico_arm_gcc
-- RP2040-HAT-AZURE-C SDK version is 1.0.0
-- The C compiler identification is GNU 10.1.0
-- The CXX compiler identification is GNU 10.1.0
-- The ASM compiler identification is GNU
-- Found assembler: C:/msys64/mingw64/bin/arm-none-eabi-gcc.exe
Defaulting PICO target board to pico since not specified.
Using board configuration from D:/RP2040/RP2040-HAT-AZURE-C/libraries/pico-sdk/src/boards/include/boards/pico.h
-- Found Python3: C:/Program Files/Python39/python.exe (found version "3.9.6") found components: Interpreter
TinyUSB available at D:/RP2040/RP2040-HAT-AZURE-C/libraries/pico-sdk/lib/tinyusb/src/portable/raspberrypi/rp2040; adding USB support.
-- AZURE_SDK_DIR = D:/RP2040/RP2040-HAT-AZURE-C/libraries/azure-iot-sdk-c
-- WIZNET_DIR = D:/RP2040/RP2040-HAT-AZURE-C/libraries/ioLibrary_Driver
-- MBEDTLS_LIB_DIR = D:/RP2040/RP2040-HAT-AZURE-C/libraries/mbedtls
-- PORT_DIR = D:/RP2040/RP2040-HAT-AZURE-C/port
-- Performing Test C_COMPILER_SUPPORTS_WFORMAT_SIGNEDNESS
-- Performing Test C_COMPILER_SUPPORTS_WFORMAT_SIGNEDNESS - Failed
-- Configuring done
-- Generating done
-- Build files have been written to: D:/RP2040/RP2040-HAT-AZURE-C/build

(PWD) RP2040-HAT-AZURE-C/build
$ cd examples/

(PWD) RP2040-HAT-AZURE-C/build/examples
$ make
[  0%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/adapters/socketio_mbed.c.obj
[  0%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/adapters/httpapi_compact.c.obj
[  0%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/certs/certs.c.obj
[  0%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/pal/tlsio_options.c.obj
[  0%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/xlogging.c.obj
[  0%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/singlylinkedlist.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/buffer.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/consolelogger.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/constbuffer.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/constmap.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/crt_abstractions.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/doublylinkedlist.c.obj
[  1%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/gballoc.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/gb_stdio.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/gb_time.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/hmac.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/hmacsha256.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/httpapiex.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/httpapiexsas.c.obj
[  2%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/httpheaders.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/map.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/optionhandler.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/sastoken.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/sha1.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/sha224.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/sha384-512.c.obj
[  3%] Building C object libraries/CMakeFiles/AZURE_SDK_FILES.dir/azure-iot-sdk-c/c-utility/src/strings.c.obj

(...)

[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/serializer/src/schema.c.obj
[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/serializer/src/schemalib.c.obj
[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/serializer/src/schemaserializer.c.obj
[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/iothub_client/src/iothub.c.obj
[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/c-utility/src/http_proxy_io.c.obj
[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/c-utility/src/azure_base32.c.obj
[ 97%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/prov_device_client.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/prov_transport_mqtt_client.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/prov_transport_mqtt_common.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/prov_security_factory.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/prov_device_ll_client.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/iothub_security_factory.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/iothub_auth_client.c.obj
[ 98%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/src/prov_auth_client.c.obj
[100%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/adapters/hsm_client_data.c.obj
[100%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/deps/utpm/src/tpm_codec.c.obj
[100%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/deps/utpm/src/Marshal.c.obj
[100%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/deps/utpm/src/tpm_comm_emulator.c.obj
[100%] Building C object examples/CMakeFiles/main.dir/__/libraries/azure-iot-sdk-c/provisioning_client/deps/utpm/src/Memory.c.obj
[100%] Linking CXX executable main.elf
[100%] Built target main

(PWD) RP2040-HAT-AZURE-C/build/examples
$ cp main.uf2 /f/
```



## 2.4. 📝 Sample application results



### 2.4.1. 📬 "iothub_ll_telemetry_sample" application result

📑 [Let's see this doc for iothub_ll_telemetry_sample application](_1_APP_TELEMETRY_manual.md)



### 2.4.2. 📩 "iothub_ll_c2d_sample" application result

📑 [Let's see this doc for iothub_ll_c2d_sample application](_2_APP_C2D_manual.md)



### 2.4.3. 🔐 "iothub_ll_client_x509_sample" application result

📑 [Let's see this doc for iothub_ll_client_x509_sample application](_3_APP_CLIENT_X509_manual.md)



### 2.4.4. 🚢 "prov_dev_client_ll_sample" application result

📑 [Let's see this doc for prov_dev_client_ll_sample application](_4_APP_PROV_X509_manual.md)
