//
// Created by 王新宇 on 2023/7/6.
//

#include "GamePlayer.h"
#include "Game.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

/**
*控制台按键所代表的数字
*“↑”：72
*“↓”：80
*“←”：75
*“→”：77
*/

void PerformPlayer(gameT& game){
    int preKey;

    if(_kbhit()){

        preKey = _getch(); // 在正常的指令读入前，老是有个0读入，怪事
        preKey = _getch();

        cout << preKey << endl;
        switch (preKey) {
            case 72:
                game.velocity.row = -1;
                game.velocity.col = 0;
                break;
            case 80:
                game.velocity.row = 1;
                game.velocity.col = 0;
                break;
            case 75:
                game.velocity.row = 0;
                game.velocity.col = -1;
                break;
            case 77:
                game.velocity.row = 0;
                game.velocity.col = 1;
                break;
            /* 没有按键则方向不变 */
            default:
                preKey = preKey;
        }

    }
}