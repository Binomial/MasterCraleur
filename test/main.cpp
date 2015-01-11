#include <QApplication>
#include "header/view/mafenetre.h"

int main(int argc, char *argv[]) {
    Player *player = new Player();
    char interface;

    std::cout << "INTERFACE GRAPHIQUE ? (y/n) " << std::endl;
    std::cin>>interface;
    if (interface == 'y') {
        QApplication app(argc, argv);

        MaFenetre *fenetre = new MaFenetre(*player);
        fenetre->show();
        return app.exec();
    } else {
        int step = 0;
        while (step < 5) {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "#Tour de jeu numéro " << step << std::endl;
            std::cout << std::endl;
            player->plays(step); //step pour debug, normalement c'est la methode choisie
            step++;
        }
        return 0;
    }


}
