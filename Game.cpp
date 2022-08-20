#include <iostream>
#include "Game.h"
#include <fstream>

#define DEBUG

void saveScore(sf::String player, int currentScore);
void replaceLine(std::string fileName, std::string oldStr, std::string newStr);

Game::Game(unsigned int width, unsigned int height) 
    : _window(sf::VideoMode({ width, height}), "Asteroids!")
{
    _window.setKeyRepeatEnabled(false);
    state = MENU;

    //Menu initialisation
    menuInit(); // Здусь загружается Font, поэтому всегда должна вызываться первой

    //Game initialisation
    //gameInit();    //Запускается каждый раз при запуске игры из меню 

    //Pause initialisation
    pauseInit();

    //GameOver initialisation
    gameOverInit();
}

Game::~Game() {
	//Asteroid stuff
    for (int i = 0; i < ast.size(); ++i) {
        delete ast[i];
    }
}

void Game::game_run()
{
    std::cout << "GAME_RUNING\n";

    while (_window.isOpen()) {
        switch (state) {
        case MENU:
            menuProcessEvents();
            menuUpdate();
            menuRender();
            break;
        case GAME_RUNING:
            gameProcessEvents();
            gameUpdate();
            gameRender();
            break;
        case GAME_OVER:
            gameOverProcessEvents();
            gameOverUpdate();
            gameRender(); // Состояние паузы учитывается внутри этой функции
            //gameOverRender();
            break;
        case PAUSE:
            pauseProcessEvents();
            pauseUpdate();
            gameRender(); // Состояние паузы учитывается внутри этой функции
            //pauseRender();
            break;
        default:
            std::cout << "INCORRECT STATE\n";
        }
    }
}

//=====================MENU==============================
void Game::menuProcessEvents() {
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            _window.close();
            state = GAME_OVER;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                _window.close();
            }
            if (event.key.code == sf::Keyboard::Enter) {
                //Выход из меню и переход в состояние игры
                state = GAME_RUNING;
                gameInit();
            }
        }
    }
}

void Game::menuUpdate()
{
}

void Game::menuRender() {
    _window.clear();
    _window.draw(_menuHelpText);
    _window.draw(_menuText);
    _window.display();
}
//========================================================

//=========================PAUSE==========================
void Game::pauseProcessEvents() {
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            _window.close();
            state = GAME_OVER;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                state = GAME_RUNING;
            }

            if (event.key.code == sf::Keyboard::Backspace) {
                state = MENU;
            }
        }
    }


}

void Game::pauseUpdate() {

}

void Game::pauseRender() {
    gameRender();
}
//========================================================

//=======================GAMEOVER=========================
void Game::gameOverProcessEvents() {
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                saveScore(_playerInput, _score);
                state = MENU;
            }
            if (event.key.code == sf::Keyboard::Enter) {
                saveScore(_playerInput, _score);
                state = GAME_RUNING;
                gameInit();
            }
        }

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {
                if (!_playerInput.isEmpty()) {
                    _playerInput.erase(_playerInput.getSize() - 1);
                }
            }
            else if (_playerInput.getSize() > 20) {
                std::cout << "Too much characters\n";
            }
            else {
                _playerInput += event.text.unicode;
            }
            _playerText.setString("Enter your name: " + _playerInput);
        }
    }
}

void Game::gameOverUpdate() {
    _gameOverFinalScore.setString("Your score: " + std::to_string(_score));
    _gameOverFinalScore.setOrigin(sf::Vector2f(_gameOverFinalScore.getGlobalBounds().width / 2,
                                         _gameOverFinalScore.getGlobalBounds().height / 2));

    _playerText.setOrigin(sf::Vector2f(_playerText.getGlobalBounds().width / 2,
                                       _playerText.getGlobalBounds().height / 2));
}

void Game::gameOverRender() {
    gameRender();
}
//===========================================================

//========================GAME===============================
void Game::gameProcessEvents() {
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            _window.close();
            state = GAME_OVER;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            state = PAUSE;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //Движение корабля
        ship.setForceDirection(ship.getDirection());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { //Создание снаряда
        ship.addBullet();
    }
}

void Game::gameUpdate() 
{
    ship.update(_window);

    for (auto el : ast) {
        el->update(_window);
    }

    ship.bulletUpdate(_window);

    //ПРОВЕРКА КОЛЛИЗИЙ
    //Проверка коллизий между снарядами и астероидами
    for (int i = 0; i < ship.bullets.size(); ++i) {
        for (int j = 0; j < ast.size() && i < ship.bullets.size(); ++j) {
            if (ast[j]->getGlobalBounds().findIntersection(ship.bullets[i]->getGlobalBounds())) {
                delete ship.bullets[i];
                ship.bullets.erase(ship.bullets.begin() + i);
                if (i > 0) {
                    i--;
                }

                if (ast[j]->getSize() == LARGE) {
                    ast.push_back(astManager.create(MEDIUM));
                    ast.back()->setPosition(ast[j]->getPosition());
                    ast.push_back(astManager.create(MEDIUM));
                    ast.back()->setPosition(ast[j]->getPosition());
                    //Score up
                    _score += 1;
                    _scoreLeftBeforeSpawn += 1;
                }
                else if (ast[j]->getSize() == MEDIUM) {
                    ast.push_back(astManager.create(SMALL));
                    ast.back()->setPosition(ast[j]->getPosition());
                    ast.push_back(astManager.create(SMALL));
                    ast.back()->setPosition(ast[j]->getPosition());
                    //Score up
                    _score += 2;
                    _scoreLeftBeforeSpawn += 2;
                }
                else {
                    //Score up
                    _score += 3;
                    _scoreLeftBeforeSpawn += 3;

                }

                //Score update 
                _scoreText.setString("SCORE: " + std::to_string(_score));
                if (_scoreLeftBeforeSpawn > SCORE_THRESHOLD) {
                    ast.push_back(astManager.create(LARGE));
                    _scoreLeftBeforeSpawn -= SCORE_THRESHOLD;
                }

                delete ast[j];
                ast.erase(ast.begin() + j);
                j--;
                
            }
        }
    }

    //Проверка коллизий между кораблём и астероидами
    for (int i = 0; i < ast.size(); ++i) {
        if (ship.getGlobalBounds().findIntersection(ast[i]->getGlobalBounds())) {
            std::cout << "true ";
            if (ship.getLastDamageTime() > 100) {
                ship.damage();
                if (ship.getHP() <= 0) {
                    state = GAME_OVER;
                }
            }
        }
    }
}

void Game::gameRender() {
    _window.clear();

    for (auto bullet : ship.bullets) {
        _window.draw(bullet->bul);
    }

    _window.draw(ship);

    for (int i = 0; i < ast.size(); ++i) {
        _window.draw(*ast[i]);
    }

    for (int i = 0; i < ship.getHP(); ++i) {
        _window.draw(hpBar[i]);
    }

    _window.draw(_scoreText);

    if (state == PAUSE) {
        _window.draw(_background);
        _window.draw(_pauseText);
        _window.draw(_pauseHelpText);
    }
    if (state == GAME_OVER) {
        _window.draw(_background);
        _window.draw(_gameOverText);
        _window.draw(_gameOverFinalScore);
        _window.draw(_playerText);
        _window.draw(_gameOverHelpText);
    }
    _window.display();
}
//===========================================================

void Game::menuInit() {
    if (!_font.loadFromFile("font.ttf")) {
        throw 12;
    }

    //Score text
    _scoreText.setFont(_font);
    _scoreText.setString("SCORE: 0");
    _scoreText.setFillColor(sf::Color::White);
    _scoreText.setCharacterSize(30);
    _scoreText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.7f), 0.f));

    _menuText.setFont(_font);
    _menuText.setString("MENU");
    _menuText.setFillColor(sf::Color::White);
    _menuText.setCharacterSize(50);
    _menuText.setOrigin(sf::Vector2f(_menuText.getGlobalBounds().width / 2,
                                           _menuText.getGlobalBounds().height / 2));
    _menuText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.2f)));

    _menuHelpText.setFont(_font);
    _menuHelpText.setString("\"Enter\" to start \n\"ESC\" to exit");
    _menuHelpText.setFillColor(sf::Color::White);
    _menuHelpText.setCharacterSize(30);
    _menuHelpText.setOrigin(sf::Vector2f(_menuHelpText.getGlobalBounds().width / 2,
                                       _menuHelpText.getGlobalBounds().height / 2));
    _menuHelpText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.3f)));
}

void Game::gameInit() {
    //Window
    _window.setVerticalSyncEnabled(true);

	//Ship stuff
    ship.init(_window);

	//HP Bar
    for (int i = 0; i < ship.getHP(); ++i) {
        hpBar.push_back(sf::RectangleShape());
        hpBar[i].setSize(sf::Vector2f(60.f, 25.f));
        hpBar[i].setFillColor(sf::Color::White);
        hpBar[i].setPosition(sf::Vector2f(20.f + i * 63.f, 20.f));
    }

    //Score
    _score = 0;
    _scoreLeftBeforeSpawn = 0;

	//Asteroid stuff
    for (auto el : ast) {
        delete el;
    }
    ast.clear();
    ast.push_back(astManager.create(LARGE));

    int wsx = _window.getSize().x;
    int wsy = _window.getSize().y;
    ast[0]->setPosition(sf::Vector2f(wsx * 0.125f, wsy * 0.125f));
}

void Game::pauseInit() {
    _pauseText.setFont(_font);
    _pauseText.setString("PAUSE");
    _pauseText.setFillColor(sf::Color::White);
    _pauseText.setCharacterSize(50);
    _pauseText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.03f),
                                          static_cast<float>(_window.getSize().y * 0.8f)));

    _pauseHelpText.setFont(_font);
    _pauseHelpText.setString("\"ESC\" to continue\n\"Backspace\" to exit");
    _pauseHelpText.setFillColor(sf::Color::White);
    _pauseHelpText.setCharacterSize(30);
    _pauseHelpText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.03f),
                                          static_cast<float>(_window.getSize().y * 0.9f)));

    float x = static_cast<float>(_window.getSize().x);
    float y = static_cast<float>(_window.getSize().y);
    _background = sf::RectangleShape(sf::Vector2f(x, y));
    _background.setFillColor(sf::Color(0, 0, 0, 170));
}

void Game::gameOverInit() {
    _playerText.setFont(_font);
    _playerText.setString("Enter your name: ");
    _playerText.setFillColor(sf::Color::White);
    _playerText.setCharacterSize(30);
    _playerText.setOrigin(sf::Vector2f(_playerText.getGlobalBounds().width / 2,
                                       _playerText.getGlobalBounds().height / 2));
    _playerText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.4f)));

    _gameOverFinalScore.setFont(_font);
    _gameOverFinalScore.setString("Your score: " + std::to_string(_score));
    _gameOverFinalScore.setFillColor(sf::Color::White);
    _gameOverFinalScore.setCharacterSize(50);
    _gameOverFinalScore.setOrigin(sf::Vector2f(_gameOverFinalScore.getGlobalBounds().width / 2,
                                         _gameOverFinalScore.getGlobalBounds().height / 2));
    _gameOverFinalScore.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.3f)));

    _gameOverText.setFont(_font);
    _gameOverText.setString("GAME OVER");
    _gameOverText.setFillColor(sf::Color::White);
    _gameOverText.setCharacterSize(70);
    _gameOverText.setOrigin(sf::Vector2f(_gameOverText.getGlobalBounds().width / 2,
                                         _gameOverText.getGlobalBounds().height / 2));
    _gameOverText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.2f)));

    _gameOverHelpText.setFont(_font);
    _gameOverHelpText.setString("\"ESC\" to exit\n\"ENTER\" to restart");
    _gameOverHelpText.setFillColor(sf::Color::White);
    _gameOverHelpText.setCharacterSize(30);
    _gameOverHelpText.setOrigin(sf::Vector2f(_gameOverHelpText.getGlobalBounds().width / 2,
                                             _gameOverHelpText.getGlobalBounds().height / 2));
    _gameOverHelpText.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.5f)));
}

void saveScore(sf::String player, int currentScore) {
    std::cout << "player: " << player.toAnsiString() << " score: " << currentScore << "\n";
    if (player == "") {
        return;
    }
    std::string line;
    std::ifstream fin("userScore.txt", std::ios::in);
    if (!fin.is_open()) {
        std::cout << "File is not open\n";
    }

    while (getline(fin, line)) {
        //Найти игрока с нужным именем
        sf::String name = line.substr(0, line.find(' '));
        //std::cout << name.toAnsiString() << '\n';
        if (name == player) {
            int userScore = std::stoi(line.substr(line.find(' ')));
            if (userScore < currentScore) {
                //Заменить счёт игрока
                std::string newString = name + ' ' + std::to_string(currentScore) + '\n';
                replaceLine("userScore.txt", line, newString);
            }
            fin.close();
            return;
        }
    }
    fin.close();

    std::ofstream fout;
    fout.open("userScore.txt", std::ios::out | std::ios::app);
    if (!fout.is_open()) {
        std::cout << "File is not open\n";
    }

    std::string user = player + ' ' + std::to_string(currentScore);
    fout << user;
    fout.close();
}

void replaceLine(std::string fileName, std::string oldStr, std::string newStr) {
    std::ifstream fin(fileName);
    std::vector<std::string> buf;
    std::string line;
    bool isFind = false;
    if (!fin.is_open()) {
        std::cout << "File is not open\n";
    }
    while (getline(fin, line)) {
        if (line == oldStr) {
            buf.push_back(newStr);
            isFind = true;
        }
        else {
            buf.push_back(line + '\n');
        }
    }
    fin.close();

    if (isFind) {
        std::ofstream fout(fileName);
        while (!buf.empty()) {
            fout << buf.back();
            buf.pop_back();
        }
        fout.close();
    }
}
