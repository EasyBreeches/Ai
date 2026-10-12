\
    #include <Geode/Geode.hpp>
    #include <Geode/modify/PlayLayer.hpp>

    using namespace geode::prelude;

    // AI Player v0.2.0: learning-data foundation only.
    // This does not synthesize input and is not an autonomous bot yet.

    namespace {
        constexpr char ATTEMPTS_KEY[] = "attempts";
        constexpr char BEST_X_KEY[] = "best-x";
        constexpr char SESSION_X_KEY[] = "session-x";

        float sessionMaxX = 0.f;
        bool sessionStarted = false;
    }

    class $modify(AIPlayerPlayLayer, PlayLayer) {
        void postUpdate(float dt) {
            PlayLayer::postUpdate(dt);

            auto mod = Mod::get();
            if (!mod->getSettingValue<bool>("learning-enabled"))
                return;

            auto layer = PlayLayer::get();
            if (!layer || !layer->m_player1)
                return;

            const float x = layer->m_player1->getPositionX();

            if (!sessionStarted) {
                sessionStarted = true;
                sessionMaxX = x;
            }
            if (x > sessionMaxX)
                sessionMaxX = x;

            mod->setSavedValue<float>(SESSION_X_KEY, sessionMaxX);

            const float best = mod->getSavedValue<float>(BEST_X_KEY, 0.f);
            if (sessionMaxX > best)
                mod->setSavedValue<float>(BEST_X_KEY, sessionMaxX);
        }
    };

    $on_mod(Loaded) {
        auto mod = Mod::get();
        log::info("AI Player v0.2.0 loaded (telemetry foundation only).");
        log::info("Saved attempt count: {}",
            mod->getSavedValue<int>(ATTEMPTS_KEY, 0));
        log::info("Best recorded X: {}",
            mod->getSavedValue<float>(BEST_X_KEY, 0.f));
    }
