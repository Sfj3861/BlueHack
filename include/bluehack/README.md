# Source layout

This directory is reserved for stable internal interfaces shared by BlueHack modules. Keep public headers small and avoid exposing Geode internals unless needed.

Planned headers:
- core/Feature.hpp: feature lifecycle contract.
- core/FeatureRegistry.hpp: registration and lookup.
- core/Config.hpp: validated configuration access.
- ui/BlueHackPopup.hpp: mobile-friendly menu panel.
