#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
//#include "Static.h"
//#include "Texture.h"
//#include "ButtonSettings.h"
//#include "ControllerSetiings.h"
//#include "Button.h"
//#include "Menu.h"
//#include "HomeMenu.h"

enum class EventType {
    ButtonClick,
    MenuClick,
    None,
    ExitButton_c,
    SinglePlayerBtn_c,
    MuteButton_c
};

class ButtonsSettings {
public:

    ButtonsSettings() = delete;
    void operator=(const ButtonsSettings&) = delete;
    static SDL_Point getStartBtnSize();
    static SDL_Point getRegularBtnSize();

private:

    static SDL_Point startBtnSize; // holds the size of start button
    static SDL_Point regularBtnSize; // holds the size of regular button
};

SDL_Point ButtonsSettings::startBtnSize = { 200, 200 };
SDL_Point ButtonsSettings::regularBtnSize = { 70, 70 };

//=============================================================================
SDL_Point ButtonsSettings::getStartBtnSize() {
    return startBtnSize;
}

//=============================================================================
SDL_Point ButtonsSettings::getRegularBtnSize() {
    return regularBtnSize;
}

class ControllerSettings {
private:
    static SDL_Point windowSize;
    static std::string windowTitle;
public:
    // public functions
    ControllerSettings() = delete;
    void operator = (const ControllerSettings&) = delete;
    static SDL_Point getWindowSize() {
        return windowSize;
    }
    static std::string getWindowTitle() {
        return windowTitle;
    }

};

SDL_Point ControllerSettings::windowSize = { 800, 600 };
std::string ControllerSettings::windowTitle = "Gold Miner vjp";

//SDL_Point getWindowSize() {
//
//}

//std::string getWindowTitle() {
//
//}

class Button {
protected:
    SDL_Rect rect;
public:
    Button(SDL_Point pos, SDL_Point size) {
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;
    }
    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
    void hover(const SDL_Point& point, SDL_Renderer* renderer) {
        if (SDL_PointInRect(&point, &rect)) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    virtual const EventType& click(const SDL_Point& point) const = 0;


};

class MuteButton : public Button {
public:
    MuteButton(SDL_Point pos, SDL_Point size) : Button(pos, size) {}
    const EventType& click(const SDL_Point& point) const override {
        return EventType::MuteButton_c;
    }
};

class ExitButton : public Button {
public:
    ExitButton(SDL_Point pos, SDL_Point size) : Button(pos, size) {}
    const EventType& click(const SDL_Point& point) const override {
        return EventType::ExitButton_c;
    }
};

class SinglePlayerBtn : public Button {
public:
    SinglePlayerBtn(SDL_Point pos, SDL_Point size) : Button(pos, size) {}
    const EventType& click(const SDL_Point& point) const override {
        return EventType::SinglePlayerBtn_c;
    }
};

class Menu {
protected:
    SDL_Rect background;
    std::vector<Button*> buttons;

public:
    Menu() {}
    Menu(const SDL_Point& windowSize) {
        background.w = windowSize.x;
        background.h = windowSize.y;
    }

    virtual void draw(SDL_Renderer* renderer) = 0;

    void hover(const SDL_Point& point, SDL_Renderer* renderer) {
        for (auto& btn : buttons) {
            btn->hover(point, renderer);
        }
    }
    const EventType click(const SDL_Point& point) const {
        for (auto& btn : buttons) {
            EventType type = btn->click(point);
            if (type != EventType::None)
                return type;
        }
        return EventType::None;
    }
};

const int NUM_OF_TEXTURES = 32;

enum texturesNames {
    COMP_MINING_TN, COMP_THROW_TN, DIAMOND_ROCK_TN, EXIT_BUTTON_TN
    , GOLDEN_ROCK_TN, HOME_BUTTON_TN, HOME_MENU_TN, LEVEL_BACKGROUND_TN,
    MUTE_BUTTON_TN, CONTINUE_BUTTON_TN, PLAYER_MINING_TN, PLAYER_THROW_TN, REGULAR_ROCK_TN,
    RESUME_BUTTON_TN, SURPRISE_BAG_TN, UNMUTE_BUTTON_TN,
    PAUSE_MENU_TN, SUMMARY_MENU_TN, HOOK_TN, PAUSE_BUTTON_TN, DYNAMITE_TN, CLOCK_TN, LEVEL_INDICATOR_TN,
    COIN_TN, HALF_HOOK_TN, EXPLOSION_TN, FROZEN_PLAYER_TN, FROZEN_COMP_TN, BARREL_TN, SINGLE_PLAYER_TN, MULTI_PLAYER_TN,
    GAME_OVER_BACK_TN
};

const std::vector<std::string> texturesImages = { "Images/CompMining.png",
                                                 "Images/CompThrow.png",
                                                 "Images/DiamondRock.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/ExitButton.png",
                                                 "Images/GoldenRock.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/HomeButton.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/HomeMenu.png",
                                                 "Images/LevelBackground.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/MuteButton.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/ContinueButton.png",
                                                 "Images/PlayerMining.png",
                                                 "Images/PlayerThrow.png",
                                                 "Images/RegularRock.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/ResumeButton.png",
                                                 "Images/SurpriseBag.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/UnmuteButton.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/PauseMenu.png",
                                                 "Images/SummaryMenu.png",
                                                 "Images/Hook.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/PauseButton.png",
                                                 "Images/Dynamite.png" ,
                                                 "Images/Clock.png" ,
                                                 "Images/LevelIndicator.png",
                                                 "Images/Coin.png",
                                                 "Images/HalfHook.png",
                                                 "Images/Explosion.png",
                                                 "Images/FrozenPlayer.png",
                                                 "Images/FrozenComp.png",
                                                 "Images/Barrel.png",
                                                 "D:/SDL_vjp/SDL_vjp/Images/SinglePlayer.png" ,
                                                 "Images/MultiPlayer.png",
                                                 "Images/GameOverBack.png" };


class LTexture {
protected:
    SDL_Renderer* renderer;
    SDL_Texture* m_textures = nullptr;

    int mWidth = 0;
    int mHeight = 0;
public:
    LTexture(SDL_Renderer* rend) : renderer(rend) {}
    SDL_Texture* loadFromFile(std::string path);
    void free();
    LTexture() {};
    LTexture(std::string path);
    void render(int x, int y);
    SDL_Texture* getTexture();
}texture[NUM_OF_TEXTURES];

SDL_Texture* LTexture::loadFromFile(std::string path) {
    free();
    //SDL_Window* window = SDL_CreateWindow(ControllerSettings::windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    m_textures = newTexture;
    SDL_QueryTexture(newTexture, nullptr, nullptr, &mWidth, &mHeight);
    return m_textures;
}

void LTexture::free() {

    if (m_textures != NULL)
    {
        SDL_DestroyTexture(m_textures);
        m_textures = NULL;
        mWidth = 0;
        mHeight = 0;
    }


}

//LTexture::LTexture(std::string path) {
//    for (int i = 0; i < NUM_OF_TEXTURES; ++i) {
//        m_textures = loadFromFile(path.c_str());
//        SDL_SetTextureBlendMode(m_textures, SDL_BLENDMODE_BLEND);
//    }
//
//
//}

void LTexture::render(int x, int y)
{

    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy(renderer, m_textures, NULL, &renderQuad);


}

class HomeMenu : public Menu {
public:
    HomeMenu() {}
    HomeMenu(const SDL_Point& windowSize) {
        background.w = windowSize.x;
        background.h = windowSize.y;
        //background.setTexture(Textures::instance().getTexture(HOME_MENU_TN));
        SDL_Texture* menu = texture[HOME_MENU_TN].loadFromFile(texturesImages[HOME_MENU_TN].c_str());
        // init buttons
        SDL_Point startBtnPos = { 50, static_cast<int>((windowSize.y / 8.0) * 2.50) };
        SDL_Point btnPos = { windowSize.x - ButtonsSettings::getRegularBtnSize().x - 20 , 20 };
        /*Button* startButton = new Button(startBtnPos);
        Button* singlePlayerButton = new Button(btnPos);*/
        SinglePlayerBtn SinglePlayerBtn(startBtnPos, btnPos);

        buttons.push_back(&SinglePlayerBtn);
        startBtnPos.x += ButtonsSettings::getStartBtnSize().x + 30;
        startBtnPos.y += 50;
        //Button MultiPlayerBtn(startBtnPos, btnPos);
        //buttons.push_back(std::make_unique<MultiPlayerBtn>(startBtnPos, ButtonsSettings::getStartBtnSize()));
        ExitButton ExitButton(btnPos, ButtonsSettings::getRegularBtnSize());
        buttons.push_back(&ExitButton);
        btnPos.x -= ButtonsSettings::getRegularBtnSize().x + 10;
        MuteButton MuteButton(btnPos, ButtonsSettings::getRegularBtnSize());
        buttons.push_back(&MuteButton);
    }

    void draw(SDL_Renderer* renderer) {
        SDL_Texture* m = texture[HOME_MENU_TN].loadFromFile(texturesImages[HOME_MENU_TN].c_str());
        SDL_RenderCopy(renderer, m, nullptr, nullptr);
        //background.draw(renderer);

        for (auto& btn : buttons)
        {
            btn->draw(renderer);
        }
    }

    //virtual void draw(SDL_Renderer* renderer) override;
};

class Controller {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    HomeMenu homeMenu;
    //GameController gameController;
    void draw() {
        if (renderer == nullptr) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        
        SDL_RenderClear(renderer);

        homeMenu.draw(renderer);

        SDL_RenderPresent(renderer);
        //SDL_DestroyRenderer(renderer);
    }
    void handleEvents(bool isRunning) {
        SDL_Event event;

        while (isRunning) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        clickHandle({ event.button.x, event.button.y });
                    break;
                case SDL_MOUSEMOTION:
                    homeMenu.hover({ event.motion.x, event.motion.y }, renderer);
                    break;
                }
            }
        }

    }
    void clickHandle(const SDL_Point& point) {
        const EventType type = homeMenu.click(point);// get the type of button from the home menu

        if (type != EventType::None) {
            switch (type) {
            case EventType::ExitButton_c:
                SDL_DestroyWindow(window);
                return;
            case EventType::SinglePlayerBtn_c:
                //                if (!gameController.playGame(window, true))// play single player
                //                    SDL_DestroyWindow(window);
                std::cout << 5;
                return;
                //case EventType::MultiPlayerBtn:
                //    // Xử lý khi MultiPlayerBtn được click
                //    break;
            case EventType::MuteButton_c:
                if (Mix_PausedMusic() == 1) {
                    Mix_ResumeMusic();
                }
                else
                {
                    Mix_PauseMusic();
                }

                return;
            }
        }
    }

public:
    Controller() {
        window = SDL_CreateWindow(ControllerSettings::getWindowTitle().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ControllerSettings::getWindowSize().x, ControllerSettings::getWindowSize().y, SDL_WINDOW_SHOWN);
        homeMenu = ControllerSettings::getWindowSize();
        //        gameController = ControllerSettings::getWindowSize();
    }

    bool isWindowOpen(SDL_Window* window) {
        if (window == nullptr) return false;
        Uint32 flags = SDL_GetWindowFlags(window);
        return (flags & SDL_WINDOW_SHOWN);
    }
    void run() {
        bool isRunning = isWindowOpen(window);
        while (isRunning)
        {
            draw();
            handleEvents(isRunning);
        }
    }

};


int main(int argc, char* args[]) {
    Controller controller;
    controller.run();
    return 0;
}
