/*-------------*//*-------------
// TODO:
// - Своя математика? (для векторов и матриц)
//
///===ОСНОВА ИГРЫ
// - Добавить физику (масса, инерция)
// - Добавить астероиды
// --- Астероиды должны ломаться (Смотри Game.ccp | 84)
// --- Поместить астероиды в структуру данных, которая позволяет быстро добавлять, удалять, 
//     и получать объекты (связный список? А большой ли прирост скорости будет по сравнению с вектором?)
// - Добавить "Бесконечное" поле
// --- Сделай красиво, а? (https://www.cyberforum.ru/unity/thread2282258.html)
// - Добавить стрельбу
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
            game->state = GAME_RUNING;
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