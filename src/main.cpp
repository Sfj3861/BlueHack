#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

namespace {
    constexpr char kButtonID[] = "bluehack-open-button";

    void showBlueHackInfo() {
        FLAlertLayer::create(
            "BlueHack 0.1.0",
            "BlueHack is loaded. This is the initial UI shell; feature modules will be added and tested in later milestones.",
            "OK"
        )->show();
    }
}

$modify(BlueHackMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Add the button only when the standard bottom menu exists.
        auto bottomMenu = this->getChildByID("bottom-menu");
        if (!bottomMenu || bottomMenu->getChildByID(kButtonID)) return true;

        auto label = CCLabelBMFont::create("BH", "bigFont.fnt");
        if (!label) {
            log::warn("BlueHack: could not create the menu label");
            return true;
        }

        auto button = CCMenuItemSpriteExtra::create(
            label, this, menu_selector(BlueHackMenuLayer::onBlueHackPressed)
        );
        if (!button) {
            log::warn("BlueHack: could not create the menu button");
            return true;
        }

        button->setID(kButtonID);
        bottomMenu->addChild(button);
        bottomMenu->updateLayout();
        return true;
    }

    void onBlueHackPressed(CCObject*) { showBlueHackInfo(); }
};

$on_mod(Loaded) {
    log::info("BlueHack {} loaded", BLUEHACK_VERSION);
}
