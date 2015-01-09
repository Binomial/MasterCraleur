#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

#include "../../header/model/Player.h"

class MaFenetre : public QWidget {
    Q_OBJECT

public:
    MaFenetre();

public slots:
    void loadGame();
    void getLetters();
    void possibilitiesDawg();

private:
    QGridLayout *layout;
    QHBoxLayout *layoutPrinc;
    QVBoxLayout *layoutV;
    QPushButton *m_bouton1;
    QPushButton *m_bouton2;
    QPushButton *m_bouton3;
    QPushButton *m_bouton4;

    QHBoxLayout *layoutRack;

    QGridLayout *grid;

    QLabel *rack, *possibilities, *points;
    Player player;

};

#endif
