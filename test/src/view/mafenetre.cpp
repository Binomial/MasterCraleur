#include "../../header/view/mafenetre.h"

void MaFenetre::loadGame() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Game board"), "/home/jeremy/Documents", tr("Game board (*.gb *.txt)"));
    QString texte;
    QFile fichier(fileName);
    int ligne = 0, colonne = 0;
    if (fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream flux(&fichier);
        while (!flux.atEnd()) {
            QString temp = flux.readLine();
            texte = temp;
            while (colonne < temp.size() && colonne < 16) {
                if (temp.at(colonne) != ' ') {
                    QLayoutItem* item = layout-> itemAtPosition(ligne, colonne);
                    QWidget* widget = item->widget();
                    QPushButton* mPB = qobject_cast<QPushButton*>(widget);
                    mPB->setText(temp.at(colonne));
                    mPB->setStyleSheet("background-color: #eddeb9;color:black;font-weight : bold;");
                }
                colonne++;
            }
            colonne = 0;
            ligne++;
        }
        fichier.close();
    }
}

void MaFenetre::getLetters() {
    std::cout << "Je possede " << player.getNbLetters() << std::endl; // BUG
    int nbLetters = 7 - player.getNbLetters();
    std::cout << "Je veux " << nbLetters << " lettres" << std::endl;
    if (nbLetters > 0) {
        player.takeLetters(nbLetters);
        for (int i = 0; i < 7; i++) {
            QLabel *letter = new QLabel("");
            letter->setFixedWidth(40);
            letter->setFixedHeight(40);
            letter->setStyleSheet("background-color: #eddeb9; color : black; font-weight : bold;");
            letter->setAlignment(Qt::AlignCenter);
            letter->setText(letter->text() + player.getLettersFromRack()[i]);
            layoutRack->addWidget(letter);
        }
        ///rack->setText(rack->text() + " " + player.getLettersFromRack().c_str());
    }
}

/* Printf all the possibilities for 0-> DAWG 1*/
void MaFenetre::possibilitiesDawg() {
    if (player.getNbLetters() == 7) {
        possibilities->setText("Best word : ");
        possibilities->setText(possibilities->text() + "On verra plus tard");
    } else {
        QMessageBox msgBox;
        msgBox.setText("Please get your letters before this operation");
        msgBox.exec();
    }
}

MaFenetre::MaFenetre(Player p) : QWidget() {
    player = p;

    setFixedSize(1120, 810);
    this->setStyleSheet("background-color: #75b475;");
    // Menu
    m_bouton1 = new QPushButton("Import", this);
    m_bouton1->setCursor(Qt::PointingHandCursor);
    m_bouton1->setStyleSheet("background-color : white;");
    QObject::connect(m_bouton1, SIGNAL(clicked()), this, SLOT(loadGame()));

    m_bouton2 = new QPushButton("Get letters", this);
    m_bouton2->setCursor(Qt::PointingHandCursor);
    m_bouton2->setStyleSheet("background-color : white;");
    QObject::connect(m_bouton2, SIGNAL(clicked()), this, SLOT(getLetters()));

    m_bouton3 = new QPushButton("Calculate possibilities", this);
    m_bouton3->setCursor(Qt::PointingHandCursor);
    m_bouton3->setStyleSheet("background-color : white;");
    QObject::connect(m_bouton3, SIGNAL(clicked()), this, SLOT(possibilitiesDawg()));

    m_bouton4 = new QPushButton("Put word", this);
    m_bouton4->setCursor(Qt::PointingHandCursor);
    m_bouton4->setStyleSheet("background-color : white;");

    possibilities = new QLabel("Best Word");
    possibilities->setStyleSheet("color : black;");
    points = new QLabel("Points : 0");

    points->setStyleSheet("color : white;");

    layoutRack = new QHBoxLayout();
    layoutRack->setSpacing(1);


    layoutV = new QVBoxLayout;
    layoutV->addWidget(m_bouton1);
    layoutV->addWidget(m_bouton2);
    layoutV->addWidget(m_bouton3);
    layoutV->addWidget(m_bouton4);
    layoutV->addLayout(layoutRack);
    layoutV->addWidget(possibilities);
    layoutV->addWidget(points);


    layout = new QGridLayout;
    layout->setSpacing(5);
    //Vertical
    for (int i = 0; i < 15; i++) {
        //Horizontal
        for (int j = 0; j < 15; j++) {
            QPushButton *bouton = new QPushButton("", this);
            bouton->setFixedSize(50, 50);
            bouton->setDisabled(true);
            bouton->setStyleSheet("background-color: #00a900;");

            if (i == j || i == 14 - j)
                bouton->setStyleSheet("background-color: pink;");

            if ((i == 0 && j == 3) || (i == 0 && j == 11) || (i == 3 && j == 0) || (i == 2 && j == 6) || (i == 2 && j == 8) || (i == 3 && j == 7) || (i == 3 && j == 14) || (i == 6 && j == 2) || (i == 6 && j == 6) || (i == 6 && j == 8) || (i == 6 && j == 12) || (i == 7 && j == 3) || (i == 7 && j == 11)
                    || (i == 8 && j == 2) || (i == 8 && j == 6) || (i == 8 && j == 8) || (i == 8 && j == 12)
                    || (i == 14 && j == 3) || (i == 14 && j == 11) || (i == 11 && j == 0) || (i == 12 && j == 6) || (i == 12 && j == 8) || (i == 11 && j == 7) || (i == 11 && j == 14) || (i == 8 && j == 2) || (i == 8 && j == 6) || (i == 8 && j == 8) || (i == 8 && j == 12))
                bouton->setStyleSheet("background-color: #1fb1ee;");

            if ((i == 1 && (j == 5 || j == 9)) || (i == 5 && (j == 1 || j == 5 || j == 9 || j == 13)) || (i == 9 && (j == 1 || j == 5 || j == 9 || j == 13)) || (i == 13 && (j == 5 || j == 9)))
                bouton->setStyleSheet("background-color: blue");

            // Word*3
            if (i % 7 == 0 && j % 7 == 0)
                bouton->setStyleSheet("background-color: red;");

            // Start Case
            if (i == 7 && j == 7)
                bouton->setStyleSheet("background-image: url(dep.png);");
            layout->addWidget(bouton, i, j);

        }
    }

    layoutPrinc = new QHBoxLayout;
    layoutPrinc->setSpacing(20);
    layoutPrinc->addLayout(layoutV);
    layoutPrinc->addLayout(layout);

    this->setLayout(layoutPrinc);
}
