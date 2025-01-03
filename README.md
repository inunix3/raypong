# raypong #
A clone of the ping pong game. Uses [raylib](https://www.raylib.com/) for graphics and audio, and
[raygui](https://github.com/raysan5/raygui) for UI.

![Video demonstration](https://github.com/user-attachments/assets/1d8d9859-7cee-4f96-ac31-a8e6fb93ac28)

Written just for fun.

## Building ##
You can build simply by creating `build` directory, going to it and calling cmake (e.g. `cmake ..`).

Optionally, you can install by typing `sudo cmake --install .`.

All assets such as sounds and images are copied into the binary file, so raypong is a single executable.

## Usage ##
Just type `./raypong` (or `raypong` if you have installed it)!

## Controls ##
| Key      | Action                     |
|----------|----------------------------|
| `Escape` | Exit to the main menu      |
| `P`      | Pause                      |
| `W`      | Move the left paddle up    |
| `S`      | Move the left paddle down  |
| `↑`      | Move the right paddle up   |
| `↓`      | Move the right paddle down |

## Contribution ##
If you have found a problem or have a suggestion, feel free to open an issue or send a pull request.
I'd appreciate it.

## License ##
The raypong project is licensed under the [MIT license](LICENSE.md).
