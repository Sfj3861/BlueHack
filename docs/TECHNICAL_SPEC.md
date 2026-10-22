# BlueHack — initial technical specification

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

## Planned module boundaries
- ui/: menu shell, categories, controls, search and mobile layout.
- core/: feature registry, lifecycle and configuration validation.
- features/visual/: hitbox and trajectory visualizers, only after coordinate-space tests.
- features/practice/: StartPos and segment helpers.
- features/diagnostics/: FPS/status readouts and input-state diagnostics.
- platform/android/: touch placement and layout adaptations.
- tests/: host-side tests for pure logic and validation.

## Initial scope
The first commit provides a load hook and a minimal entry button on the main menu. It is a UI smoke-test shell, not a finished menu and not a compiled .geode package. Modules must not be advertised as implemented until they pass acceptance tests.

## Reference projects and reuse policy
- QOLMod (TheSillyDoggo/GeodeMenu) is useful for studying feature categories and Android interaction patterns. Its current LICENSE explicitly says not to use its code without permission, so BlueHack does not copy its implementation.
- Eclipse Menu Modification is under EPL-2.0. Reuse would require preserving license obligations and tracking modified files; the initial code is independently written.
- GD Mega Overlay is GPL-3.0 and targets an older Geometry Dash version. Any future code reuse needs a GPL compliance review; the current implementation does not copy its code.
- The Mega Hack package is used only for verifiable metadata/resources/observed behaviour, not as decompiled source.

## Compatibility gate
Before publishing, verify the exact Geode SDK and Android toolchain against Geometry Dash 2.2081. A metadata declaration is not proof of binary compatibility.
