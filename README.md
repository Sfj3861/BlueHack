# BlueHack

An original, modular Geometry Dash utility menu built for Geode.

## Current target
- Platform: Android
- Geometry Dash: 2.2081
- Language: C++20
- Build: CMake + Geode SDK

## Status
The feature/bluehack-0.1-foundation branch contains the initial project structure and a minimal main-menu button that opens an informational popup. This is a development scaffold, not yet a tested or installable .geode release.

## Build prerequisites
- A Geode SDK compatible with Geometry Dash 2.2081
- CMake 3.21 or newer
- Android NDK/toolchain supported by the selected SDK
- GEODE_SDK environment variable pointing to the SDK checkout

Configure and build using the workflow documented by the chosen Geode SDK. The metadata currently declares Geode 5.7.1; confirm exact SDK compatibility before building or publishing.

## Project docs
- docs/TECHNICAL_SPEC.md — architecture and reuse policy
- docs/ROADMAP.md — planned milestones
- docs/TEST_PLAN.md — acceptance tests

## Reference projects
BlueHack studies public feature descriptions and UI patterns from QOLMod, Eclipse Menu and GD Mega Overlay, but does not copy their source files. QOLMod's current license explicitly requires permission before code reuse. Eclipse Menu is EPL-2.0 and GD Mega Overlay is GPL-3.0, so any future reuse will require a separate license review.
