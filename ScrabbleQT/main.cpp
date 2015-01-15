#include <QApplication>
#include "header/view/mafenetre.h"
#include "header/view/Console.h"

/*Pour toi jérémy !*/
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
        Console *console = new Console();
        console->startGame(*player);

        return 0;
    }


}
