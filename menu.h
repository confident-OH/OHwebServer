#pragma once
void Menu(int opt, int web_status) {
    system("cls");
    printf("/***********************************************************************************************************************************************/\n");
    printf("                                                                                                                                      \n");
    printf("       OOOOOOOOO    HHHHHHHHH     HHHHHHHHH  SSSSSSSSSSSSSSS\n");
    printf("     OO:::::::::OO  H:::::::H     H:::::::HSS:::::::::::::::S\n");
    printf("   OO:::::::::::::OOH:::::::H     H:::::::S:::::SSSSSS::::::S\n");
    printf("  O:::::::OOO:::::::HH::::::H     H::::::HS:::::S     SSSSSSS\n");
    printf("  O::::::O   O::::::O H:::::H     H:::::H S:::::S               eeeeeeeeeeee vvvvvvv           vvvvvvveeeeeeeeeeee   rrrrr   rrrrrrrrr   \n");
    printf("  O:::::O     O:::::O H:::::H     H:::::H S:::::S             ee::::::::::::eev:::::v         v:::::ee::::::::::::ee r::::rrr:::::::::r\n");
    printf("  O:::::O     O:::::O H::::::HHHHH::::::H  S::::SSSS         e::::::eeeee:::::ev:::::v       v:::::e::::::eeeee:::::er:::::::::::::::::r \n");
    printf("  O:::::O     O:::::O H:::::::::::::::::H   SS::::::SSSSS   e::::::e     e:::::ev:::::v     v:::::e::::::e     e:::::rr::::::rrrrr::::::r\n");
    printf("  O:::::O     O:::::O H:::::::::::::::::H     SSS::::::::SS e:::::::eeeee::::::e v:::::v   v:::::ve:::::::eeeee::::::er:::::r     r:::::r\n");
    printf("  O:::::O     O:::::O H::::::HHHHH::::::H        SSSSSS::::Se:::::::::::::::::e   v:::::v v:::::v e:::::::::::::::::e r:::::r     rrrrrrr\n");
    printf("  O:::::O     O:::::O H:::::H     H:::::H             S:::::e::::::eeeeeeeeeee     v:::::v:::::v  e::::::eeeeeeeeeee  r:::::r\n");
    printf("  O::::::O   O::::::O H:::::H     H:::::H             S:::::e:::::::e               v:::::::::v   e:::::::e           r:::::r \n");
    printf("  O:::::::OOO:::::::HH::::::H     H::::::HSSSSSSS     S:::::e::::::::e               v:::::::v    e::::::::e          r:::::r\n");
    printf("   OO:::::::::::::OOH:::::::H     H:::::::S::::::SSSSSS:::::Se::::::::eeeeeeee        v:::::v      e::::::::eeeeeeee  r:::::r\n");
    printf("     OO:::::::::OO  H:::::::H     H:::::::S:::::::::::::::SS  ee:::::::::::::e         v:::v        ee:::::::::::::e  r:::::r\n");
    printf("       OOOOOOOOO    HHHHHHHHH     HHHHHHHHHSSSSSSSSSSSSSSS      eeeeeeeeeeeeee          vvv           eeeeeeeeeeeeee  rrrrrrr \n");
    printf("\n");
    printf("/***********************************************************************************************************************************************/\n\n\n\n");
    printf("欢迎来到OHSever！\n\n");
    if (web_status == 1) {
        printf("Sever状态: 已打开\n\n\n");
    }
    else {
        printf("Sever状态: 未打开\n\n\n");
    }
    printf("/***********************************************************************************************************************************************/\n");
    if (opt == 0) {
        printf("\033[1;31;44m         功能一：打开服务器\033[0m\n");
    }
    else {
        printf("         功能一：打开服务器\n");
    }
    if (opt == 1) {
        printf("\033[1;31;44m         功能二：关闭服务器\033[0m\n");
    }
    else {
        printf("         功能二：关闭服务器\n");
    }
    if (opt == 2) {
        printf("\033[1;31;44m         功能三：退出程序\033[0m\n\n");
    }
    else {
        printf("         功能三：退出程序\n\n");
    }
    printf("输入s/w可以上下移动图标，回车键进入对应功能\n");
    printf("您的输入：");
}

