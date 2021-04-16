#include "Vue.h"
#include <QApplication>
#include <qwidget.h>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QColor>
#include <QPalette>
#include <QGridLayout>

Bouton::Bouton(QChar& piece, QWidget* parent, int x, int y) : QPushButton(piece, parent) {
	x_ = x;
	y_ = y;
}

VueEchiquier::VueEchiquier(QWidget* parent, Echiquier& echiquier) : echiquier_(echiquier),  QMainWindow(parent) {
	
	auto widget = new QWidget(this);
	auto layout = new QVBoxLayout(widget);
	auto vue = new QGridLayout();

	layout->addLayout(vue);
	vue->setVerticalSpacing(0);
	vue->setHorizontalSpacing(0);

	for (int ligne = 0; ligne < nLignes; ligne++) {
		for (int colonne = 0; colonne < nColonnes; colonne++)
		{
			Bouton* bouton;
			QChar pieceVue;
			if (echiquier_.getPiece(colonne, ligne))
			{
				Piece* piece = echiquier_.getPiece(colonne, ligne);
				bool couleur = piece->getCouleur();
				if (dynamic_cast<Roi*>(piece)) {
					couleur ? pieceVue = QChar(0x265A) : pieceVue = QChar(0x2654);
				}
				else if (dynamic_cast<Tour*>(piece)) {
					couleur ? pieceVue = QChar(0x265C) : pieceVue = QChar(0x2656);
				}
				else if (dynamic_cast<Cavalier*>(piece)) {
					couleur ? pieceVue = QChar(0x265E) : pieceVue = QChar(0x2658);
				}
			}
			bouton = new Bouton(pieceVue, this, colonne, ligne);

			QFont font = VueEchiquier::font();
			font.setPointSize(45);
			bouton->setFont(font);
			vue->addWidget(bouton, nColonnes - 1 - colonne, ligne);
			QSize taille = QSize(100, 100);
			bouton->setFixedSize(taille);

			QColor couleur;
			(ligne % 2) == (colonne % 2) ? couleur = QColor(200,200,229) : couleur = QColor(255,255,255);

			QPalette couleurVue = palette();
			couleurVue.setColor(QPalette::Button, couleur);
			bouton->setAutoFillBackground(true);
			bouton->setFlat(true);
			bouton->setPalette(couleurVue);

			QObject::connect(bouton, &QPushButton::clicked, this, &VueEchiquier::appuye);
		}
	}
	setCentralWidget(widget);
	setWindowTitle("Jeu d'Echec");
}