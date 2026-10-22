#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

namespace {
    constexpr char kButtonID[] = "bluehack-open-button";
    constexpr float kSpeedhackScale = 1.5f;
    class BlueHackOverlay;
    static BlueHackOverlay* g_overlay = nullptr;

    bool isFrameGuardAvailable() {
        auto* mod = Loader::get()->getLoadedMod("sfj3861.frame-guard");
        return mod && mod->isEnabled();
    }

    bool toggleFrameGuardSetting(char const* key) {
        if (auto* mod = Loader::get()->getLoadedMod("sfj3861.frame-guard"); mod && mod->isEnabled()) {
            bool value = !mod->getSettingValue<bool>(key);
            mod->setSettingValue<bool>(key, value);
            log::info("BlueHack: Frame-Guard setting '{}' set to {}", key, value);
            return value;
        }
        FLAlertLayer::create(
            "Frame-Guard not found",
            "Install and enable a compatible Frame-Guard version to control this feature from BlueHack.",
            "OK"
        )->show();
        return false;
    }

    void applySpeedhack(bool enabled) {
        // Only alter the game clock while an actual level is active; never slow the menus.
        if (!PlayLayer::get()) return;
        if (auto* director = CCDirector::sharedDirector()) {
            if (auto* scheduler = director->getScheduler()) {
                scheduler->setTimeScale(enabled ? kSpeedhackScale : 1.f);
            }
        }
    }
}

class BlueHackOverlay final : public CCLayerColor {
public:
    static BlueHackOverlay* create() {
        auto* ret = new BlueHackOverlay();
        if (ret && ret->initWithColor({ 9, 14, 28, 238 }) && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() {
        auto win = CCDirector::sharedDirector()->getWinSize();
        this->setContentSize(win);
        this->setTouchEnabled(true);

        auto* title = CCLabelBMFont::create("BLUEHACK", "bigFont.fnt");
        if (title) {
            title->setScale(0.8f);
            title->setPosition({ win.width / 2.f, win.height - 42.f });
            this->addChild(title);
        }
        auto* subtitle = CCLabelBMFont::create("ANDROID  |  GEODE 5.11.2", "goldFont.fnt");
        if (subtitle) {
            subtitle->setScale(0.38f);
            subtitle->setPosition({ win.width / 2.f, win.height - 68.f });
            this->addChild(subtitle);
        }

        m_menu = CCMenu::create();
        if (!m_menu) return false;
        m_menu->setPosition({ 0.f, 0.f });
        this->addChild(m_menu);

        addButton("Speedhack  x1.5", ccp(win.width / 2.f, win.height - 120.f), menu_selector(BlueHackOverlay::onSpeedhack));
        addButton("Noclip", ccp(win.width / 2.f, win.height - 164.f), menu_selector(BlueHackOverlay::onNoclip));
        addButton("Frame-Guard: Hitboxes", ccp(win.width / 2.f, win.height - 208.f), menu_selector(BlueHackOverlay::onHitboxes));
        addButton("Frame-Guard: Trajectory", ccp(win.width / 2.f, win.height - 252.f), menu_selector(BlueHackOverlay::onTrajectory));
        addButton("Frame-Guard: Player bounds", ccp(win.width / 2.f, win.height - 296.f), menu_selector(BlueHackOverlay::onPlayerBounds));
        addButton("Close", ccp(win.width / 2.f, 42.f), menu_selector(BlueHackOverlay::onClose));

        auto* status = CCLabelBMFont::create(
            isFrameGuardAvailable() ? "Frame-Guard detected" : "Frame-Guard not detected",
            "bigFont.fnt"
        );
        if (status) {
            status->setScale(0.34f);
            status->setPosition({ win.width / 2.f, 17.f });
            this->addChild(status);
        }
        return true;
    }

    void onClose(CCObject*) {
        if (this->getParent()) this->removeFromParentAndCleanup(true);
        if (g_overlay == this) g_overlay = nullptr;
    }

    void onSpeedhack(CCObject*) {
        bool enabled = !Mod::get()->getSettingValue<bool>("speedhack-enabled");
        Mod::get()->setSettingValue<bool>("speedhack-enabled", enabled);
        applySpeedhack(enabled);
        notifyToggle("Speedhack", enabled);
    }

    void onNoclip(CCObject*) {
        bool enabled = !Mod::get()->getSettingValue<bool>("noclip-enabled");
        Mod::get()->setSettingValue<bool>("noclip-enabled", enabled);
        notifyToggle("Noclip", enabled);
    }

    void onHitboxes(CCObject*) {
        bool enabled = toggleFrameGuardSetting("show-hitboxes");
        Mod::get()->setSettingValue<bool>("hitboxes-enabled", enabled);
        notifyToggle("Hitboxes", enabled);
    }

    void onTrajectory(CCObject*) {
        bool enabled = toggleFrameGuardSetting("show-trajectory");
        Mod::get()->setSettingValue<bool>("trajectory-enabled", enabled);
        notifyToggle("Trajectory", enabled);
    }

    void onPlayerBounds(CCObject*) {
        bool enabled = toggleFrameGuardSetting("show-player-bounds");
        Mod::get()->setSettingValue<bool>("player-bounds-enabled", enabled);
        notifyToggle("Player bounds", enabled);
    }

private:
    void addButton(char const* title, CCPoint position, cocos2d::SEL_MenuHandler callback) {
        auto* label = CCLabelBMFont::create(title, "bigFont.fnt");
        if (!label) return;
        label->setScale(0.46f);
        auto* item = CCMenuItemLabel::create(label, this, callback);
        if (!item) return;
        item->setPosition(position);
        m_menu->addChild(item);
    }

    void notifyToggle(char const* feature, bool enabled) {
        log::info("BlueHack: {} {}", feature, enabled ? "enabled" : "disabled");
    }

    CCMenu* m_menu = nullptr;
};

namespace {
    void openBlueHack(CCNode* parent) {
        if (!parent) return;
        if (g_overlay && g_overlay->getParent()) {
            g_overlay->removeFromParentAndCleanup(true);
            g_overlay = nullptr;
            return;
        }
        g_overlay = BlueHackOverlay::create();
        if (g_overlay) parent->addChild(g_overlay, 9999);
    }
}

$modify(BlueHackMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        auto* bottomMenu = this->getChildByID("bottom-menu");
        if (!bottomMenu || bottomMenu->getChildByID(kButtonID)) return true;

        auto* label = CCLabelBMFont::create("BH", "bigFont.fnt");
        if (!label) return true;
        auto* button = CCMenuItemSpriteExtra::create(
            label, this, menu_selector(BlueHackMenuLayer::onBlueHackPressed)
        );
        if (!button) return true;
        button->setID(kButtonID);
        bottomMenu->addChild(button);
        bottomMenu->updateLayout();
        return true;
    }

    void onBlueHackPressed(CCObject*) {
        openBlueHack(CCDirector::sharedDirector()->getRunningScene());
    }
};

$modify(BlueHackPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        if (Mod::get()->getSettingValue<bool>("speedhack-enabled")) applySpeedhack(true);
        return true;
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("noclip-enabled")) return;
        PlayLayer::destroyPlayer(player, object);
    }

    void onExit() {
        applySpeedhack(false);
        Mod::get()->setSettingValue<bool>("speedhack-enabled", false);
        if (g_overlay && g_overlay->getParent()) {
            g_overlay->removeFromParentAndCleanup(true);
        }
        g_overlay = nullptr;
        PlayLayer::onExit();
    }
};

$on_mod(Loaded) {
    log::info("BlueHack {} loaded on the current Geode SDK.", BLUEHACK_VERSION);
    KeybindSettingPressedEventV3(Mod::get(), "toggle-menu").listen([](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) return;
        auto* scene = CCDirector::sharedDirector()->getRunningScene();
        if (!scene) return;
        if (g_overlay && g_overlay->getParent()) {
            g_overlay->removeFromParentAndCleanup(true);
            g_overlay = nullptr;
        } else {
            openBlueHack(scene);
        }
    });
    KeybindSettingPressedEventV3(Mod::get(), "toggle-speedhack").listen([](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) return;
        bool enabled = !Mod::get()->getSettingValue<bool>("speedhack-enabled");
        Mod::get()->setSettingValue<bool>("speedhack-enabled", enabled);
        applySpeedhack(enabled);
    });
    KeybindSettingPressedEventV3(Mod::get(), "toggle-noclip").listen([](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) return;
        Mod::get()->setSettingValue<bool>("noclip-enabled", !Mod::get()->getSettingValue<bool>("noclip-enabled"));
    });
    KeybindSettingPressedEventV3(Mod::get(), "toggle-trajectory").listen([](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) return;
        Mod::get()->setSettingValue<bool>("trajectory-enabled", toggleFrameGuardSetting("show-trajectory"));
    });
    KeybindSettingPressedEventV3(Mod::get(), "toggle-hitboxes").listen([](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) return;
        Mod::get()->setSettingValue<bool>("hitboxes-enabled", toggleFrameGuardSetting("show-hitboxes"));
    });
    KeybindSettingPressedEventV3(Mod::get(), "toggle-player-bounds").listen([](Keybind const&, bool down, bool repeat, double) {
        if (!down || repeat) return;
        Mod::get()->setSettingValue<bool>("player-bounds-enabled", toggleFrameGuardSetting("show-player-bounds"));
    });
}
