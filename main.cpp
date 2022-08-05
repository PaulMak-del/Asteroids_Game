/*-------------*//*-------------
// TODO
// - Создать базовый объект для игровых объектов?
//
///===ОСНОВА ИГРЫ
// - Добавить HP кораблю и возможность получить урон
/////////////////
///===МЕНЮ
// - Создать начальное меню
// --- кнопка "Начать игру"
// --- кнопка "Списки лидеров" (После гибели корабля нужно вписать имя, 
                                чтобы запомнить счёт)
// --- кнопка "Выйти из игры"
// - Создать возможность ставить игру на паузу
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
// - Стоит ли заменять счётчик на std::chrono? (для интервалов стрельбы)
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