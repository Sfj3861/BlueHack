# BlueHack — technical specification

## Target
- Initial platform: Android
- Geometry Dash target: 2.2081
- Loader/API: Geode SDK compatible with the target build. Metadata currently declares 5.7.1; verify against the installed SDK before release.
- Language: C++20
- Build system: CMake + Geode SDK
- Mod ID: sfj3861.bluehack

## Architecture principles
1. Keep UI, feature logic, and game integration separate.
2. Register each feature with a stable ID, category, default state, and lifecycle.
3. Make feature activation idempotent; toggling twice must not duplicate hooks or nodes.
4. Unregister hooks and remove owned nodes when a feature is disabled or the scene ends.
5. Persist only validated configuration values and provide safe defaults.
6. Avoid per-frame allocations; cache reusable visual objects and throttle non-critical labels.
7. Explicitly distinguish world coordinates from screen coordinates and account for camera transforms.
8. Keep diagnostic/visual modules separate from gameplay-modifying modules.
9. Clearly disclose features that may affect gameplay or level records.
10. Keyboard shortcuts are optional bindings, not the only way to operate a feature; every command remains reachable from touch UI.
11. A shortcut dispatches a registered command ID, never a pointer to a temporary UI node.
12. Toggle commands act only on key-down and ignore repeated key-down events; scene/focus changes must not leave a feature stuck.
13. Avoid common game/system keys by default; allow rebinding and surface conflicts.

## Planned module boundaries
- ui/: menu shell, categories, controls, search and mobile layout.
- core/: feature registry, lifecycle, command registry, keybind dispatch and configuration validation.
- features/visual/: hitbox and trajectory visualizers, only after coordinate-space tests.
- features/practice/: StartPos and segment helpers.
- features/diagnostics/: FPS/status readouts and input-state diagnostics.
- features/gameplay/: speedhack and noclip, independently gated and tested.
- integrations/frame_guard/: optional bridge to Frame-Guard capabilities.
- platform/android/: touch placement, keyboard availability and layout adaptations.
- tests/: host-side tests for pure logic, command routing and validation.

## Keyboard shortcut behavior
- Use editable Geode keybind settings and retain a touch equivalent for every command.
- Candidate commands: open/close BlueHack, toggle speedhack, toggle noclip, toggle trajectory, and toggle Frame-Guard diagnostics.
- Do not ship shortcuts for features that are not implemented.
- Key-down toggles once; key-up does not toggle; key-repeat is ignored.
- Commands are ignored if their feature or optional integration is unavailable.
- A physical keyboard may be used on Android, but touch remains primary and keyboard behavior needs device testing.

## Frame-Guard integration contract
Frame-Guard is a separate Geode mod (sfj3861.frame-guard), targeting Geometry Dash Android 2.2081 and declaring Geode SDK 5.11.2. BlueHack currently declares SDK 5.7.1, so direct binary/API compatibility is not established.

1. Detect whether Frame-Guard is installed and enabled before exposing controls.
2. Prefer a small documented public API or shared command interface; do not access anonymous-namespace globals or assume private setting IDs are a stable API.
3. If no public API exists, use only documented Geode settings/events after verifying supported API and version compatibility.
4. If Frame-Guard is absent, disabled, or incompatible, disable bridge commands without affecting BlueHack.
5. Do not copy Frame-Guard implementation files into BlueHack. Keep both projects and their release pipelines separate.
6. Hitboxes and trajectory remain approximate diagnostics, not authoritative collision prediction.

## Initial scope
The current branch provides a load hook and a minimal main-menu entry point. It is not a finished menu or a compiled .geode package. Modules must not be advertised as implemented until they pass acceptance tests.

## Reference projects and reuse policy
- QOLMod (TheSillyDoggo/GeodeMenu) is useful for studying feature categories and Android interaction patterns. Its current LICENSE says not to use its code without permission, so BlueHack does not copy its implementation.
- Eclipse Menu Modification is under EPL-2.0; reuse requires preserving license obligations and tracking modified files.
- GD Mega Overlay is GPL-3.0 and targets an older Geometry Dash version; any future code reuse needs a GPL compliance review.
- Frame-Guard is a separate MIT-licensed project; integration should use a narrow interface or documented settings, not copied source.
- The Mega Hack package is used only for verifiable metadata/resources/observed behaviour, not as decompiled source.

## Compatibility gate
Before publishing, verify the exact Geode SDK and Android toolchain against Geometry Dash 2.2081. Metadata is not proof of binary compatibility. Resolve the SDK mismatch with Frame-Guard before relying on cross-mod integration.
