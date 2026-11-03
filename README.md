# STM32 UART Interpolation

## Requirements

Before running this project, prepare the following hardware and software:

### Hardware
- STM32F103C8T6 (Blue Pill)
- CH340 or USB-to-TTL converter for initial firmware flashing
- USB Type-C data cable
- Computer with a USB port

### Software
- CMake
- Make
- ARM GCC toolchain (if required by your CMake configuration)

## Hardware Setup

1. Prepare the STM32F103C8T6 board.
2. Connect the STM32 to a CH340 or USB-to-TTL converter.
3. Flash the firmware to the STM32 board.
4. After flashing is complete, disconnect the CH340 or USB-to-TTL converter if it is no longer needed.
5. Connect the STM32 board to your computer using a USB Type-C data cable through the USB Type-C port on the board.

## Project Structure

The project uses the following source files:

- `main.cpp` – Main program entry point.
- `serial.cpp` and `serial.h` – Serial communication implementation.
- `interpolation.cpp` and `interpolation.h` – Interpolation implementation.
- `CMakeLists.txt` – Build configuration.

## Build Instructions

Open a terminal in the project directory and run:

```bash
cmake -S . -B build
```

Then compile the project:

```bash
cmake --build build
```

## Running the Program

After building successfully, run the generated executable from the build directory.

```bash
cd build
```

Run the executable:

```bash
./your_executable_name
```

Replace `your_executable_name` with the executable name defined in your `CMakeLists.txt`.

## Input Instructions

1. Run the program.
2. Enter three different numerical values.
3. Press `Enter` after entering the numbers as requested by the program.
4. The STM32 will process the input using the interpolation implementation.

**Note:** Make sure the USB Type-C cable supports data transfer, not just charging.
