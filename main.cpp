/*-------------*//*-------------
// TODO
// - ������� ������� ������ ��� ������� ��������?
//
///===������ ����
// - �������� HP ������� � ����������� �������� ����
/////////////////
///===����
// - ������� ��������� ����
// --- ������ "������ ����"
// --- ������ "������ �������" (����� ������ ������� ����� ������� ���, 
                                ����� ��������� ����)
// --- ������ "����� �� ����"
// - ������� ����������� ������� ���� �� �����
////////////
///===�ר�
//
////////////
///===������
//
////////////
///===������
//
////////////
///===�������������
// - ����� �� �������� ������� �� std::chrono? (��� ���������� ��������)
// - ����� ������� ����������� � ������ ���� ���� �� ������
// - C���� �� �������������� �������� ����������?
// - �������� rand() �� ������� �� C++11
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