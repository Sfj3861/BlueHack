# BlueHack roadmap

## 0.1.0 — load and UI smoke test
- [x] Add Geode metadata and CMake project.
- [x] Add a minimal main-menu entry point.
- [ ] Compile against the selected Geode SDK.
- [ ] Confirm the button appears on target Android.
- [ ] Confirm no crash on main-menu open/close.

## 0.2.0 — actual menu shell and command/keybind foundation
- [ ] Mobile-friendly panel with categories.
- [ ] Reusable toggle, slider, action-row, and keybind-row controls.
- [ ] Search/filter and favorites foundations.
- [ ] Settings persistence with validation.
- [ ] Close button, back handling, safe-area and orientation checks.
- [ ] Central command registry with stable IDs, availability checks, and execute/toggle actions.
- [ ] Configurable keyboard shortcuts through Geode keybind settings; keyboard remains optional on Android.
- [ ] Toggle commands react once on key-down and ignore key-repeat.
- [ ] Detect/document shortcut conflicts rather than silently sharing bindings.

## 0.3.0 — low-risk utilities
- [ ] FPS/status display with throttled updates.
- [ ] Player state labels.
- [ ] Configurable visual preferences.
- [ ] Module registry and lifecycle tests.
- [ ] Keybind dispatch tests: key-down/up, repeats, focus changes, and scene changes.

## 0.4.0 — practice and visual tools
- [ ] StartPos/segment utilities after target-version API review.
- [ ] Hitbox visualizer with world/screen coordinate tests.
- [ ] Trajectory preview with explicit camera/world transforms.
- [ ] Input-state diagnostics; do not claim frame-perfect capture before tests verify it.
- [ ] Show Trajectory command with a configurable shortcut, initially unbound until conflict testing.
- [ ] Optional Frame-Guard integration with capability/version checks.

## 0.5.0 — gameplay toggles and stability pass
- [ ] Speedhack and noclip as separate modules; shortcuts remain unavailable until each feature is implemented and tested.
- [ ] Clearly mark gameplay-modifying commands as practice/testing features.
- [ ] Test menu transitions, death/restart, editor and platformer.
- [ ] Check memory lifetime, duplicate hooks, and repeated enable/disable.
- [ ] Profile on a representative Android device.
- [ ] Verify compatibility with common Geode dependencies and Frame-Guard SDK requirements.

## 1.0.0 — stable release
- [ ] All advertised features pass tests.
- [ ] Android package builds reproducibly.
- [ ] Document known limitations and compatibility.
- [ ] Provide release notes and source/license notices.
