#include <QApplication>
#include "header/view/mafenetre.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MaFenetre *fenetre = new MaFenetre(*(new Player()));
    fenetre->show();
    return app.exec();

}
