# BlueHack roadmap

## 0.1.0 — load and UI smoke test
- [x] Add Geode metadata and CMake project.
- [x] Add a minimal main-menu entry point.
- [ ] Compile against the selected Geode SDK.
- [ ] Confirm the button appears on target Android.
- [ ] Confirm no crash on main-menu open/close.

## 0.2.0 — actual menu shell
- [ ] Mobile-friendly panel with categories.
- [ ] Reusable toggle, slider, and action-row controls.
- [ ] Search/filter and favorites foundations.
- [ ] Settings persistence with validation.
- [ ] Close button, back handling, safe-area and orientation checks.

## 0.3.0 — low-risk utilities
- [ ] FPS/status display with throttled updates.
- [ ] Player state labels.
- [ ] Configurable visual preferences.
- [ ] Module registry and lifecycle tests.

## 0.4.0 — practice and visual tools
- [ ] StartPos/segment utilities after target-version API review.
- [ ] Hitbox visualizer with world/screen coordinate tests.
- [ ] Trajectory preview with explicit camera/world transforms.
- [ ] Input-state diagnostics; do not claim frame-perfect capture before tests verify it.

## 0.5.0 — stability pass
- [ ] Test menu transitions, death/restart, editor and platformer.
- [ ] Check memory lifetime, duplicate hooks, and repeated enable/disable.
- [ ] Profile on a representative Android device.
- [ ] Verify compatibility with common Geode dependencies.

## 1.0.0 — stable release
- [ ] All advertised features pass tests.
- [ ] Android package builds reproducibly.
- [ ] Document known limitations and compatibility.
- [ ] Provide release notes and source/license notices.
