# anga - Another Generic AutoClicker

**anga** is a basic auto-clicker program written in C. It allows you to automate mouse clicks with customizable delay settings and offers a command mode for on-the-fly adjustments.

## Features

- **Start/Stop Clicking**: Toggle the auto-clicker on and off using hotkeys.
- **Command Mode**: Adjust settings like click delay directly from the console.
- **Exit**: Cleanly exit the program using a hotkey.

## Hotkeys

- **F7**: Start clicking
- **F8**: Stop clicking
- **F9**: Exit the auto-clicker
- **F10**: Enter command mode

## Command Mode

Enter command mode by pressing **F10**. The following commands are available:

- **delay**: Set the click delay (in milliseconds)
- **start**: Start the auto-clicker
- **end**: Stop the auto-clicker
- **help**: Display help information
- **exit**: Exit command mode

## Usage

1. Compile the program using a C compiler like `gcc` or any other. Make sure to link the `gdi32` library, like this: `gcc -o whateveryouwant.exe auto.c -lgdi32`
2. Run the compiled program.
3. Use the hotkeys and command mode to control the auto-clicker.

## Up and coming
- [X] Toggle Click Type (Left/Right Clicks)
- [X] Hold Down Feature
- [X] Precompiled EXE Files For Releases*

If you would like for me to implement other features, please lmk.

*I will mostly update the repo as i work on it than make new releases, so for latest src of anga, build yourself

## Credits

- **anga**: Another Generic AutoClicker created by dLL44.
