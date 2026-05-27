# BayoHook
A trainer for the Steam version of Bayonetta made using [Dear ImGui](https://github.com/ocornut/imgui), [minhook](https://github.com/TsudaKageyu/minhook), [DX9 BaseHook](https://github.com/rdbo/DX9-BaseHook) and [dmc4_hook](https://github.com/muhopensores/dmc4_hook).

This dll will give you access to training, gameplay, and quality of life options without ever needing to open anything alongside your exe.

Builds are intended for use on the Steam version of the game and will crash on other versions.

Please back up your save before using this hook. Savedata can be found in `C:\Program Files (x86)\Steam\userdata\[steamid]\460790\remote`.

## Installation

* Download the latest dll [here](https://github.com/SSSiyan/BayoHook/releases)
  * If you have issues with your antivirus removing the file, please follow [these instructions](https://github.com/SSSiyan/BayoHook/wiki#virus-protection)

* Place dinput8.dll in the Bayonetta root folder, next to your exe. By default this is `C:\Program Files (x86)\Steam\steamapps\common\Bayonetta\`

* Run the game. Hit Delete on your keyboard to open the menu to change options.

## Instructions
For help regarding usage of the trainer, check our [wiki.](https://github.com/SSSiyan/BayoHook/wiki)

## Speedrun edition builds

The solution includes `DebugSpeedrun|x86` and `ReleaseSpeedrun|x86` configurations. These define `SPEEDRUN_BUILD` at compile time, so contributors can build the speedrun edition without editing `src/gamehook.hpp`.

Use `ReleaseSpeedrun|x86` for a candidate DLL and keep the output filename as `dinput8.dll` when placing it beside `Bayonetta.exe`.

The speedrun edition keeps the speedrun-specific UI path, including the proof badge overlay and non-gameplay quality-of-life settings exposed by `SPEEDRUN_BUILD`. It does not by itself certify leaderboard legality or prove high-refresh/delta-time behavior; those still need in-game Windows validation by runners and maintainers.
