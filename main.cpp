/*-------------*//*-------------
// TODO
// - Заменить указатели на умные указатели
// - Прочитать про friend функции (может сделать Ship и Bullet друзьями?:)
// - Заменить счётчик на std::chrono (для интервалов стрельбы и получения урона)
// - Модифицировать управление пользовательским вводом (нужно однократное срабатывание)
//
///===ОСНОВА ИГРЫ
// 
/////////////////
///===МЕНЮ
// - Добавить списки лидеров
// - Улучшить стартовое меню (добавить задний фон)
////////////
///===СЧЁТ
//
////////////
///===МУЗЫКА
//
////////////
///===УРОВНИ
//
////////////
///===КОРРЕКТИРОВКИ
// - Более плавное перемещение с одного края поля на другой
// - Cтоит ли корректировать скорость астероидов?
// - Заменить rand() на функцию из C++11
////////////
*/

#include <iostream>
#include "Game.h"

#define DEBUG

int main()
{
    unsigned int width = 800;
    unsigned int height = 800;

    Game* game = new Game(width, height);

    while (game->isRuning()) { 
        switch (game->state) {
        case MENU:
            game->menu();
            break;
        case GAME_RUNING:
            game->game_run();
            break;
        case GAME_OVER:
            break;
        case PAUSE:
            break;
        case RESTART:
            game->restart();
            game->state = GAME_RUNING; 
            break;
        default:
            std::cout << "INCORRECT STATE\n";
        }
    }

    delete game;

    return 0;
}