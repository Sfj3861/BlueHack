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
- Confirm every command remains usable by touch without a keyboard.

## Keyboard shortcut checks
- Test key-down, key-up, held-key repeat, and rapid repeated taps.
- Confirm one key-down produces exactly one toggle.
- Confirm rebinding persists after restarting the game.
- Confirm defaults do not conflict with Geometry Dash, Geode, or common Android/system shortcuts.
- Test with and without a physical keyboard.
- Test focus loss, menu changes, death/restart, level completion, editor entry, and return to menu.
- Confirm unavailable commands and absent integrations are safely ignored.

## Frame-Guard integration checks
- Test with Frame-Guard installed, disabled, absent, and an incompatible SDK build.
- Verify the bridge never assumes private globals or copies Frame-Guard code.
- Verify trajectory/hitbox controls affect only intended settings and UI stays synchronized.
- Confirm Frame-Guard works independently if BlueHack is removed.
- Label diagnostic visuals as approximate.

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
