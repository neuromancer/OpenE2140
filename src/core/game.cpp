//
// Created by Ion Agorria on 1/11/18
//
#include "core/common.h"
#include "assets/assetmanager.h"
#include "graphics/palette.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "gui/eventhandler.h"
#include "simulation/simulation.h"
#include "core/luavm.h"
#include "game.h"
#include "utils.h"

Game::Game() {
    log = Log::get("Game");
}

Game::~Game() {
    close();
    log->debug("Destroyed");
}

void Game::close() {
    log->debug("Closing");
    if (eventHandler) {
        eventHandler.reset();
    }
    if (renderer) {
        renderer.reset();
    }
    windows.clear();
    mainWindow = nullptr;
    if (luaVM) {
        luaVM.reset();
    }
    if (assetManager) {
        assetManager.reset();
    }
}

std::unique_ptr<Palette> extra;
bool Game::run() {
    log->debug("Running");

    std::shared_ptr<Game> this_ptr = shared_from_this();

    // Initialize Lua
    luaVM = LuaVM::create();

    //Initialize event handler
    eventHandler = std::make_unique<EventHandler>(this_ptr);

    //Initialize window
    std::unique_ptr<Window> window = std::make_unique<Window>(DEFAULT_RESOLUTION_WIDTH, DEFAULT_RESOLUTION_HEIGHT, GAME_TITLE);
    std::string error = window->getError();
    if (!error.empty()) {
        log->error("Error initializing window\n{0}", error);
        return false;
    }
    mainWindow = window.get();
    windows.emplace(window->getID(), std::move(window));

    // Initialize renderer
    renderer = std::make_unique<Renderer>();
    error = renderer->getError();
    if (!error.empty()) {
        log->error("Error initializing renderer\n{0}", error);
        return false;
    }

    //Initialize asset manager
    assetManager = std::make_unique<AssetManager>(this_ptr);
    assetManager->loadAssets();
    error = assetManager->getError();
    if (!error.empty()) {
        log->error("Error initializing asset manager\n{0}", error);
        return false;
    }

    //Show main window
    mainWindow->show();

    //TODO remove
    extra = std::make_unique<Palette>(10, true);
    test(0);

    //Main loop
    log->debug("Starting loop");
    while (!eventHandler->isClosing()) {
        loop();
    }

    //Close myself
    close();

    return true;
}

std::shared_ptr<Image> image;
int v = 90;
double t;
void Game::loop() {
    //Clear
    mainWindow->clear();

    //Poll input
    eventHandler->poll();

    //Update simulation

    //Draw the simulation

    //Draw/update UI
    renderer->changeCamera(0, 0);
    //TODO remove this
    t += 0.05;
    if (image) {
        ColorRGBA color = {(byte) (std::round(std::sin(t) * 0x7f) + 0x7f), 0,
                          (byte) (std::round(std::cos(t) * 0x7f) + 0x7f), 128};
        for (unsigned int i = 0; i < extra->length(); ++i) {
            extra->setColor(i, color);
        }
        extra->updateTexture();
        for (float j = 0; j <= 100; j += 1) {
            for (float i = 0; i <= 100; i += 1) {
                renderer->draw(j * 10, i * 10, 15, 15, std::sin(t / 2) * 1.3, *image, extra.get());
            }
        }
    }
    renderer->flush();

    //Update window
    mainWindow->swap();
}

void Game::test(int i) {
    if (0 < i) {
        v++;
    } else if (i < 0) {
        v--;
    }
    std::string path = v < 0 ? "MIX/SPRT0/"+std::to_string(std::abs(v) - 1) : "MIX/SPRU0/"+std::to_string(v);
    log->debug(path);
    image = assetManager->getImage(path);
    if (image) log->debug("Current: {0} {1}", v, image->toString());
}

Window* Game::getMainWindow() {
    return mainWindow;
}

Window* Game::getWindow(unsigned int id) {
    return Utils::getPointerFromUnorderedMap(windows, id);
}

Renderer* Game::getRenderer() {
    return renderer.get();
}

Simulation* Game::getSimulation() {
    return simulation.get();
}

AssetManager* Game::getAssetManager() {
    return assetManager.get();
}