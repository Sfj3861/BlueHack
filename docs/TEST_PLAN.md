# BlueHack test plan

## Build checks
- Configure CMake with the intended Geode SDK.
- Build the Android target without errors.
- Verify generated package metadata and mod ID.
- Do not report success unless compiler and packager complete successfully.

## Load/UI checks
- Launch Geometry Dash 2.2081 with Geode enabled.
- Confirm BlueHack appears in the mod list without a load error.
- Open the main menu repeatedly and confirm only one BlueHack button is created.
- Tap the button and confirm the info popup opens and closes.
- Navigate away from and back to the main menu; confirm no stale nodes or crashes.

## Regression checks for every future feature
- Toggle on/off repeatedly (at least 50 cycles).
- Restart a level, die, complete a level, return to the menu, and enter the editor.
- Confirm disabling a feature removes its own visual nodes and hooks.
- Test small screens, safe areas, and touch targets.
- Verify camera movement does not cause world-space visualizers to stick to the screen.
- Record FPS and memory before/after enabling visual features.
- Verify invalid or missing config values fall back safely.

## Release acceptance
- No known crash in tested flows.
- No duplicated UI nodes or hooks.
- Each visible control has a real implementation and observable effect.
- Documentation identifies experimental or unsupported features.
- Attach exact build artifact and test environment details to the release.
