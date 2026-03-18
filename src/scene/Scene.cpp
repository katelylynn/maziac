//
// Created by kate on 2026-02-25.
//

#include "../scene/Scene.h"

#include "../manager/AssetManager.h"
#include "Game.h"

Scene::Scene(SceneType sceneType, const char *sceneName, const char *mapPath, int windowWidth, int windowHeight)
: name(sceneName), type(sceneType) {
    if (sceneType == SceneType::MainMenu)
        initMainMenu(windowWidth, windowHeight);
    else
        initGameplay(mapPath, windowWidth, windowHeight);
}

void Scene::initMainMenu(int windowWidth, int windowHeight) {
    // CAMERA ENTITY
    auto &cam = world.createEntity();
    cam.addComponent<Camera>();

    // MENU ENTITY
    auto &menu(world.createEntity());
    auto menuTransform = menu.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);

    SDL_Texture *texture = TextureManager::load("../asset/menu.png");
    SDL_FRect menuSrc {0, 0, (float) windowWidth, (float) windowHeight};
    SDL_FRect menuDest {menuTransform.position.x, menuTransform.position.y, menuSrc.w, menuSrc.h};
    menu.addComponent<Sprite>(texture, menuSrc, menuDest);

    auto& settingsOverlay = createSettingsOverlay(windowWidth, windowHeight);
    createCogButton(windowWidth, windowHeight, settingsOverlay);
}

void Scene::initGameplay(const char* mapPath, int windowWidth, int windowHeight) {
    // load map
    world.getMap().load(mapPath, TextureManager::load("../asset/spritesheet.png"));

    // add entities

    // COLLIDERS
    // create an entity for each collider on the map
    for (auto &collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);

        auto& c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        // just to have a visual of the colliders
        SDL_Texture* texture = TextureManager::load("../asset/spritesheet.png");
        SDL_FRect colliderSrc { 0, 32, 32, 32 };
        SDL_FRect colliderDest { c.rect.x, c.rect.y, c.rect.w, c.rect.h };
        e.addComponent<Sprite>(texture, colliderSrc, colliderDest);
    }

    // CAMERA
    auto& camera = world.createEntity();
    SDL_FRect cameraView{};
    cameraView.w = windowWidth; // window width
    cameraView.h = windowHeight; // window height
    camera.addComponent<Camera>(cameraView, world.getMap().width * 32.0f, world.getMap().height * 32.0f);

    // ITEMS
    // must be spawned before player, or it registers a single collision on start
    for (auto &collider : world.getMap().itemColliders) {
        auto& item = world.createEntity();
        item.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);

        auto& c = item.addComponent<Collider>("item");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = 32;
        c.rect.h = 32;

        SDL_Texture* texture = TextureManager::load("../asset/coin.png");
        SDL_FRect itemSrc { 0, 0, 32, 32 };
        SDL_FRect itemDest { c.rect.x, c.rect.y, 32, 32 };
        item.addComponent<Sprite>(texture, itemSrc, itemDest);
    }

    // PLAYER
    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0, 0), 240.0f);
    player.addComponent<Animation>();

    Animation animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture* playerTexture = TextureManager::load("../asset/animations/diver_anim.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
    SDL_FRect playerDest { playerTransform.position.x, playerTransform.position.y, 64, 64 };
    player.addComponent<Sprite>(playerTexture, playerSrc, playerDest);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDest.w;
    playerCollider.rect.h = playerDest.h;

    player.addComponent<PlayerTag>();

    player.addComponent<Health>(Game::gameState.playerHealth);

    //TIMED SPAWNER
    auto& spawner(world.createEntity());
    Transform spawnerTransform = spawner.addComponent<Transform>(Vector2D(windowWidth / 2.0f, windowHeight - 5.0f), 0.0f, 1.0f);
    spawner.addComponent<TimedSpawner>(2.0f, [this, spawnerTransform] {
        // create our projectile (bird in this case)
        auto& entity(world.createDeferredEntity());
        entity.addComponent<Transform>(Vector2D(spawnerTransform.position.x, spawnerTransform.position.y), 0.0f, 1.0f);
        entity.addComponent<Velocity>(Vector2D(0, -1), 100.0f); // upwards at a speed of 100

        Animation animation = AssetManager::getAnimation("enemy");
        entity.addComponent<Animation>(animation);

        SDL_Texture* texture = TextureManager::load("../asset/animations/bird_anim.png");
        SDL_FRect src { 0, 0, 0, 32 };
        SDL_FRect dest { spawnerTransform.position.x, spawnerTransform.position.y, 32, 32 };
        entity.addComponent<Sprite>(texture, src, dest);

        Collider collider = entity.addComponent<Collider>("projectile");
        collider.rect.w = dest.w;
        collider.rect.h = dest.h;

        entity.addComponent<ProjectileTag>();
    });

    // add scene state
    auto &state(world.createEntity());
    state.addComponent<SceneState>();
}

Entity& Scene::createSettingsOverlay(int windowWidth, int windowHeight) {
    auto& overlay(world.createEntity());

    SDL_Texture* overlayTexture = TextureManager::load("../asset/ui/settings.jpg");
    SDL_FRect overlaySrc { 0, 0, windowWidth*0.85f, windowHeight*0.85f };
    SDL_FRect overlayDest {
        (float) windowWidth/2 - overlaySrc.w/2,
        (float) windowHeight/2 - overlaySrc.h/2,
        overlaySrc.w, overlaySrc.h
    };
    overlay.addComponent<Transform>(Vector2D(overlayDest.x, overlayDest.y), 0.0f, 1.0f);
    overlay.addComponent<Sprite>(overlayTexture, overlaySrc, overlayDest, RenderLayer::UI, false);

    createSettingsUIComponents(overlay);

    return overlay;
}

Entity& Scene::createCogButton(int windowWidth, int windowHeight, Entity& overlay) {
    auto& cog(world.createEntity());
    auto& cogTransform = cog.addComponent<Transform>(
        // bottom right corner
        Vector2D((float) windowWidth - 50, (float) windowHeight - 50), 0.0f, 1.0f
    );

    SDL_Texture *cogTexture = TextureManager::load("../asset/ui/cog.png");
    SDL_FRect cogSrc { 0, 0, 32, 32 };
    SDL_FRect cogDest { cogTransform.position.x, cogTransform.position.y, cogSrc.w, cogSrc.h };
    cog.addComponent<Sprite>(cogTexture, cogSrc, cogDest, RenderLayer::UI);
    cog.addComponent<Collider>("ui", cogDest);

    auto& clickable = cog.addComponent<Clickable>();
    clickable.onPressed = [&cogTransform] {
        cogTransform.scale = 0.5f;
    };
    // this gives access to toggle visibility function
    clickable.onReleased = [this, &cogTransform, &overlay] {
        cogTransform.scale = 1.0f;
        toggleSettingsOverlayVisibility(overlay);
    };
    clickable.onCancel = [&cogTransform] {
        cogTransform.scale = 1.0f;
    };

    return cog;
}

void Scene::createSettingsUIComponents(Entity& overlay) {
    if (!overlay.hasComponent<Children>()) {
        overlay.addComponent<Children>();
    }

    auto& overlayTransform = overlay.getComponent<Transform>();
    auto& overlaySprite = overlay.getComponent<Sprite>();

    float baseX = overlayTransform.position.x;
    float baseY = overlayTransform.position.y;

    // CLOSE BUTTON
    auto& closeButton = world.createEntity();
    auto& closeTransform = closeButton.addComponent<Transform>(
        // top right corner
        Vector2D(baseX + overlaySprite.dest.w - 40, baseY + 10), 0.0f, 1.0f
    );
    SDL_Texture *closeTexture = TextureManager::load("../asset/ui/close.png");
    SDL_FRect closeSrc{0, 0, 32, 32 };
    SDL_FRect closeDest { closeTransform.position.x, closeTransform.position.y, closeSrc.w, closeSrc.h };
    closeButton.addComponent<Sprite>(closeTexture, closeSrc, closeDest, RenderLayer::UI, false);
    closeButton.addComponent<Collider>("ui", closeDest);

    auto& clickable = closeButton.addComponent<Clickable>();
    clickable.onPressed = [&closeTransform] {
        closeTransform.scale = 0.5f;
    };
    clickable.onReleased = [this, &overlay, &closeTransform] {
        closeTransform.scale = 1.0f;
        toggleSettingsOverlayVisibility(overlay);
    };
    clickable.onCancel = [&closeTransform] {
        closeTransform.scale = 1.0f;
    };

    // sets the overlay as its parent
    closeButton.addComponent<Parent>(&overlay);

    // sets the close button as the overlay's child
    auto& parentChildren = overlay.getComponent<Children>();
    parentChildren.children.push_back(&closeButton);
}

void Scene::toggleSettingsOverlayVisibility(Entity& overlay) {
    auto& sprite = overlay.getComponent<Sprite>();
    bool newVisibility = !sprite.visible;
    sprite.visible = newVisibility;

    if (overlay.hasComponent<Children>()) {
        auto& children = overlay.getComponent<Children>();

        for (auto& child : children.children) {
            if (child && child->hasComponent<Sprite>())
                child->getComponent<Sprite>().visible = newVisibility;

            if (child && child->hasComponent<Collider>())
                child->getComponent<Collider>().enabled = newVisibility;
        }
    }
}