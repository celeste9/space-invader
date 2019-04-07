#include "Fonctions.h"
#include "Vaisseau.h"
#include "Laser.h"
#include "Scores.h"
#include "Jauges.h"
#include "Martien.h"
#include "Plutonien.h"
#include <iostream>
#include <windows.h>
#include <MMSystem.h>
#include <fstream>
#include <string>
#include "UIKit.h"

//ASTUCE
Vaisseau sauveur;
int nouvellePositionLaser;
Laser missile;
char action;
char tir;
bool game_over = false;
int devant;
Scores point;
Jauges vieVaisseau;


Martien martien1(143, 50); //LE TYPE DE MARTIEN ET SA VALEUR
Martien martien2(143, 50); //LE TYPE DE MARTIEN ET SA VALEUR
Martien martien3(143, 50); //LE TYPE DE MARTIEN ET SA VALEUR
Martien martien4(143, 50); //LE TYPE DE MARTIEN ET SA VALEUR
Martien martien5(143, 50); //LE TYPE DE MARTIEN ET SA VALEUR
Martien martien6(143, 50); //LE TYPE DE MARTIEN ET SA VALEUR
////////////////////////////////////////////////////////////////////////
Plutonien plutonien1(232, 100); //LE TYPE DE PLUTONIEN ET SA VALEUR
Plutonien plutonien2(232, 100); //LE TYPE DE PLUTONIEN ET SA VALEUR
Plutonien plutonien3(232, 100); //LE TYPE DE PLUTONIEN ET SA VALEUR
Plutonien plutonien4(232, 100); //LE TYPE DE PLUTONIEN ET SA VALEUR
Plutonien plutonien5(232, 100); //LE TYPE DE PLUTONIEN ET SA VALEUR

void afficherScore() {
	UIKit::gotoXY(80, 5); UIKit::color(0x0004); std::cout << "SCORE : " << point.getScore();  //AFFICHER LE SCORE
}

void afficherPv() {
	UIKit::gotoXY(80, 40); UIKit::color(0x0002); std::cout << "PV : " << vieVaisseau.getPv() << " /500";  //AFFICHER LE SCORE
}


void terrain() {
	system("CLS");
	// ON DEFINI LE CADRE DU TERRAIN
	for (int i = 1; i < 75; i++) {  //barre de haut 75
		UIKit::gotoXY(i, 1); UIKit::color(7); std::cout << char(205); //COULEUR = BLANCHE
		Sleep(10);
	}

	for (int i = 1; i < 75; i++) {  //barre de bas de 75 
		UIKit::gotoXY(i, 44); UIKit::color(7); std::cout << char(205);
		Sleep(10);
	}

	for (int i = 1; i < 45; i++) {  //barre de gauche de 45 
		UIKit::gotoXY(1, i); UIKit::color(7); std::cout << char(186);
		Sleep(10);
	}

	for (int i = 1; i < 45; i++) {  //barre de droite de 45 
		UIKit::gotoXY(74, i); UIKit::color(7); std::cout << char(186);
		Sleep(10);
	}

	UIKit::gotoXY(1, 1); UIKit::color(7); std::cout << char(201);   //COIN HAUT GAUCHE
	UIKit::gotoXY(74, 1); UIKit::color(7); std::cout << char(187); //COIN HAUT DROITE
	UIKit::gotoXY(1, 44); UIKit::color(7); std::cout << char(200); //COIN BAS GAUCHE
	UIKit::gotoXY(74, 44); UIKit::color(7); std::cout << char(188); //COIN BAS DROITE

	afficherScore();
	afficherPv();

}

void mouvementVaisseau() {
	action = 'z'; //POUR QUE LA BOUCLE SOIT VALIDE PEUT IMPORTE SI ON ENTRE APRES GAUCHE OU DROITE

	if (GetAsyncKeyState(0x4B)) {  //ENTREE DE K (DEPLACEMENT VERS LA GAUCHE)
		char New = 'k';
		UIKit::color(1); sauveur.modifierPosition(New);  //COULEUR = BLUE
	}

	if (GetAsyncKeyState(0x4C)) {  //ENTREE DE L (DEPLACEMENT VERS LA DROITE)
		char New = 'l';
		UIKit::color(1); sauveur.modifierPosition(New);  //COULEUR = BLUE
	}


}


//FONCTION DE DEMARRAGE
void demarrerPartie() {
	
	game_over = false;	//CHAQUE FOIS QU'ON RELANCERA UNE PARTIE GAME_OVER SERA A FALSE.
	point.setScore(-(point.getScore()));		//CHAQUE FOIS QU'ON RELANCERA UNE PARTIE LE POINT SERA REMIS A 0.
	int niveau;
	int choix;
	char commandeTapez = 'z';
	nouvellePositionLaser = 0;
	devant = 38;
	int departMissilePlutonien = 15;
	int departMissileMartien = 8;

	system("CLS");
	Sleep(1500);
	ifstream fichier("Debug/readme.txt", ios::in);
	if (fichier) {  // si l'ouverture a fonctionné
		string ligne;
		while (getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			UIKit::color(7); cout << ligne << endl;  // on l'affiche  COULEUR = BLANCHE
		}
		fichier.close();
	}
	PlaySound(TEXT("Debug/Intro.wav"), NULL, SND_SYNC);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "                                     APPUYEZ <ENTRER> POUR CONTINUER ";
	system("pause>nul");
	if (GetAsyncKeyState(VK_RETURN)) {
		system("CLS");
	}
	do {
		UIKit::gotoXY(10, 10); std::cout << "Choisissez votre niveau (1 - 2 - 3) : ";
		std::cin >> niveau;
		system("CLS");
	} while (niveau < 1 || niveau > 3);

	system("CLS");
	terrain();

	if (niveau == 1) {

		//ON PLACE LES MARTIENS
		martien1.coord.setPositionX(10);
		martien1.coord.setPositionY(7);
		UIKit::color(7); martien1.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////////
		martien2.coord.setPositionX(20);
		martien2.coord.setPositionY(7);
		UIKit::color(7); martien2.putExtraTerrestre();

		/*******************************************************************************************************************************************************/

		//ON PLACE LES PLUTONIENS      
		plutonien1.coord.setPositionX(15);
		plutonien1.coord.setPositionY(14);
		UIKit::color(7); plutonien1.putExtraTerrestre();

		Sleep(500);
		UIKit::gotoXY(20, 40); UIKit::color(1); std::cout << char(18);   //ON AFICHE LA POSITION DE DEPART DU VAISSEAU


		int cpt = 0;
		int cptLaserVaisseau = 0;


		do {

			//TIRS
			for (int a = 1; a < 65; a++) {
				if (UIKit::getCharXY(a, 7) == char(143) && cpt == 0) {
					UIKit::gotoXY(a, departMissileMartien); std::cout << '/' << std::endl;
				}
				if (UIKit::getCharXY(a, 14) == char(232) && cpt == 0) {
					UIKit::gotoXY(a, departMissilePlutonien); std::cout << '/' << std::endl;
				}
			}
			for (int a = 1; a < 65; a++) {
				if (UIKit::getCharXY(a, departMissileMartien) == '/') {
					Sleep(35);
					UIKit::gotoXY(a, departMissileMartien); std::cout << ' ' << std::endl;
					UIKit::gotoXY(a, departMissileMartien + 1); std::cout << '/' << std::endl;
				}
				if (UIKit::getCharXY(a, departMissilePlutonien) == '/') {
					Sleep(35);
					UIKit::gotoXY(a, departMissilePlutonien); std::cout << ' ' << std::endl;
					UIKit::gotoXY(a, departMissilePlutonien + 1); std::cout << '/' << std::endl;
				}
			}
			cpt++;
			departMissileMartien++;
			departMissilePlutonien++;
			if (departMissileMartien > 40) {
				departMissileMartien = 8;
				cpt = 0;
			}
			if (departMissilePlutonien > 40) {
				departMissilePlutonien = 15;
				cpt = 0;
			}


			if (vieVaisseau.getPv() <= 0) {		//SI PARMIS LES DEGATS PRIS LA VIE DU VAISSEAU EST 0 LA PARTIE SE TERMINE
				game_over = true;
				PlaySound(TEXT("Debug/Die.wav"), NULL, SND_SYNC);
			}


			if (GetAsyncKeyState(0x4B) || GetAsyncKeyState(0x4C)) {  //TOUCHES K OU L TAPEZ
				mouvementVaisseau();
			}
			else if (GetAsyncKeyState(0x56)) {  //TOUCHE V TAPEZ
				PlaySound(TEXT("Debug/shoot.wav"), NULL, SND_SYNC);
				for (int i = 2; i < 74; i++) {
					char tevoila;
					tevoila = UIKit::getCharXY(i, 40);   //CHERCHE EN SE BASANT SUR LA LIGNE 40 OU SE DEPLACE LE VAISEAU (Y = 40)
					if (tevoila == char(18)) {
						nouvellePositionLaser = i;             //VA INTERPRETER LA CORDONNEE Y COMME X ET LE LASER SE PLACERA EXACTEMENT OU SE TROUVE LE VAISSEAU
					}
				}
				if (cptLaserVaisseau == 0) {
					UIKit::gotoXY(nouvellePositionLaser, 39); UIKit::color(4); std::cout << char(15);    //LA POSITION X D'OU PART LE LASER  COULEUR = ROUGE
				}
				for (int u = 39; u > 2; u--) {

					if (UIKit::getCharXY(nouvellePositionLaser, u - 1) == char(143)) {
						point.setScore(100);													//POINT POUR LES MARTIENS
						afficherScore();
					}
					if (UIKit::getCharXY(nouvellePositionLaser, u - 1) == char(232)) {
						point.setScore(50);												//POINT POUR LES PLUTONIENS
						afficherScore();
					}

					if (UIKit::getCharXY(nouvellePositionLaser, u) == char(15)) {
						Sleep(20);	//DELAIS DE TEMPS DE DEPLACEMENT DU LASER (PLUS LE DELAIS EST GRAND MOINS LE LASER EST RAPIDE
						UIKit::gotoXY(nouvellePositionLaser, u); std::cout << " ";
						Sleep(20);	//DELAIS DE TEMPS DE DEPLACEMENT DU LASER (PLUS LE DELAIS EST GRAND MOINS LE LASER EST RAPIDE
						UIKit::gotoXY(nouvellePositionLaser, u - 1); UIKit::color(4); std::cout << char(15);
					}
				}
			}

			if (point.getScore() == 250) {
						//SI LE SCORE TOTAL EST ATTEINT PARTIE GAGNEE
				UIKit::gotoXY(20, 25); std::cout << "!!!! YOU WIN !!!! ";
				PlaySound(TEXT("Debug/Win.wav"), NULL, SND_SYNC);
				game_over = true;
			}

			for (int i = 2; i < 70; i++) {			//SI LE MISSILLE ENNEMI SE TROUVE DEVANT LE VAISSEAU ALORS IL PREND DES DEGATS
				if (UIKit::getCharXY(i, 40) == char(18) && UIKit::getCharXY(i, 39) == '/') {
					vieVaisseau.reduirePv(50);     //SERT A REDUIRE LES POINTS DE VIE DU VAISSEAU
					afficherPv();
				}
			}

			for (int i = 2; i < 65; i++) {
				if (UIKit::getCharXY(i, 41) == '/') {		//ON CHERCHE OU SONT LES LASERS EGARES DES ENNEMIS
					UIKit::gotoXY(i, 41); std::cout << ' ' << std::endl;   //PUIS ON LES EFFACES
				}
			}

			for (int i = 2; i < 65; i++) {
				if (UIKit::getCharXY(i, 2) == char(15)) {		//ON CHERCHE OU SONT LES LASERS EGARES DU VAISSEAU VERS LE HAUT
					UIKit::gotoXY(i, 2); std::cout << ' ' << std::endl;   //PUIS ON LES EFFACES
				}
			}


		} while (!game_over); //TANTQUE GAME_OVER EST DIFFERENT DE TRUE(FALSE) ALORS ON CONTINU LA PARTIE

	} //FIN DE NIVEAU

	if (niveau == 2) {

		//ON PLACE LES MARTIENS
		martien1.coord.setPositionX(10);
		martien1.coord.setPositionY(7);
		UIKit::color(7); martien1.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////////
		martien3.coord.setPositionX(20);
		martien3.coord.setPositionY(7);
		UIKit::color(7); martien3.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////
		martien5.coord.setPositionX(30);
		martien5.coord.setPositionY(7);
		UIKit::color(7); martien5.putExtraTerrestre();

		/*******************************************************************************************************************************************************/

		//ON PLACE LES PLUTONIENS 
		plutonien2.coord.setPositionX(15);
		plutonien2.coord.setPositionY(14);
		UIKit::color(7); plutonien2.putExtraTerrestre();
		////////////////////////////////////////////////////////////////////
		plutonien4.coord.setPositionX(25);
		plutonien4.coord.setPositionY(14);
		UIKit::color(7); plutonien4.putExtraTerrestre();
		////////////////////////////////////////////////////////////////////
		plutonien5.coord.setPositionX(35);
		plutonien5.coord.setPositionY(14);
		UIKit::color(7); plutonien5.putExtraTerrestre();

		Sleep(500);
		UIKit::gotoXY(20, 40); UIKit::color(1); std::cout << char(18);   //ON AFICHE LA POSITION DE DEPART DU VAISSEAU


		int cpt = 0;
		int cptLaserVaisseau = 0;


		do {

			//TIRS
			for (int a = 1; a < 65; a++) {
				if (UIKit::getCharXY(a, 7) == char(143) && cpt == 0) {
					UIKit::gotoXY(a, departMissileMartien); std::cout << '/' << std::endl;
				}
				if (UIKit::getCharXY(a, 14) == char(232) && cpt == 0) {
					UIKit::gotoXY(a, departMissilePlutonien); std::cout << '/' << std::endl;
				}
			}
			for (int a = 1; a < 65; a++) {
				if (UIKit::getCharXY(a, departMissileMartien) == '/') {
					Sleep(12);
					UIKit::gotoXY(a, departMissileMartien); std::cout << ' ' << std::endl;
					UIKit::gotoXY(a, departMissileMartien + 1); std::cout << '/' << std::endl;
				}
				if (UIKit::getCharXY(a, departMissilePlutonien) == '/') {
					Sleep(12);
					UIKit::gotoXY(a, departMissilePlutonien); std::cout << ' ' << std::endl;
					UIKit::gotoXY(a, departMissilePlutonien + 1); std::cout << '/' << std::endl;
				}
			}

			cpt++;
			departMissileMartien++;
			departMissilePlutonien++;
			if (departMissileMartien > 40) {
				departMissileMartien = 8;
				cpt = 0;
			}
			if (departMissilePlutonien > 40) {
				departMissilePlutonien = 15;
				cpt = 0;
			}


			if (vieVaisseau.getPv() <= 0) {		//SI PARMIS LES DEGATS PRIS LA VIE DU VAISSEAU EST 0 LA PARTIE SE TERMINE
				game_over = true;
				PlaySound(TEXT("Debug/Die.wav"), NULL, SND_SYNC);
			}


			if (GetAsyncKeyState(0x4B) || GetAsyncKeyState(0x4C)) {  //TOUCHES K OU L TAPEZ
				mouvementVaisseau();
			}
			else if (GetAsyncKeyState(0x56)) {  //TOUCHE V TAPEZ
				PlaySound(TEXT("Debug/shoot.wav"), NULL, SND_SYNC);
				for (int i = 2; i < 74; i++) {
					char tevoila;
					tevoila = UIKit::getCharXY(i, 40);   //CHERCHE EN SE BASANT SUR LA LIGNE 40 OU SE DEPLACE LE VAISEAU (Y = 40)
					if (tevoila == char(18)) {
						nouvellePositionLaser = i;             //VA INTERPRETER LA CORDONNEE Y COMME X ET LE LASER SE PLACERA EXACTEMENT OU SE TROUVE LE VAISSEAU
					}
				}
				if (cptLaserVaisseau == 0) {
					UIKit::gotoXY(nouvellePositionLaser, 39); UIKit::color(4); std::cout << char(15);    //LA POSITION X D'OU PART LE LASER  COULEUR = ROUGE
				}
				for (int u = 39; u > 2; u--) {

					if (UIKit::getCharXY(nouvellePositionLaser, u - 1) == char(143)) {
						point.setScore(100);													//POINT POUR LES MARTIENS
						afficherScore();
					}
					if (UIKit::getCharXY(nouvellePositionLaser, u - 1) == char(232)) {
						point.setScore(50);												//POINT POUR LES PLUTONIENS
						afficherScore();
					}

					if (UIKit::getCharXY(nouvellePositionLaser, u) == char(15)) {
						Sleep(20);	//DELAIS DE TEMPS DE DEPLACEMENT DU LASER (PLUS LE DELAIS EST GRAND MOINS LE LASER EST RAPIDE
						UIKit::gotoXY(nouvellePositionLaser, u); std::cout << " ";
						Sleep(20);	//DELAIS DE TEMPS DE DEPLACEMENT DU LASER (PLUS LE DELAIS EST GRAND MOINS LE LASER EST RAPIDE
						UIKit::gotoXY(nouvellePositionLaser, u - 1); UIKit::color(4); std::cout << char(15);
					}
				}
			}

			if (point.getScore() == 450) {
						//SI LE SCORE TOTAL EST ATTEINT PARTIE GAGNEE
				PlaySound(TEXT("Debug/Win.wav"), NULL, SND_SYNC);
				UIKit::gotoXY(20, 25); std::cout << "!!!! YOU WIN !!!! ";
				Sleep(5800);
				game_over = true;
			}

			for (int i = 2; i < 70; i++) {			//SI LE MISSILLE ENNEMI SE TROUVE DEVANT LE VAISSEAU ALORS IL PREND DES DEGATS
				if (UIKit::getCharXY(i, 40) == char(18) && UIKit::getCharXY(i, 39) == '/') {
					vieVaisseau.reduirePv(50);     //SERT A REDUIRE LES POINTS DE VIE DU VAISSEAU
					afficherPv();
				}
			}

			for (int i = 2; i < 65; i++) {
				if (UIKit::getCharXY(i, 41) == '/') {		//ON CHERCHE OU SONT LES LASERS EGARES DES ENNEMIS
					UIKit::gotoXY(i, 41); std::cout << ' ' << std::endl;   //PUIS ON LES EFFACES
				}
			}

			for (int i = 2; i < 65; i++) {
				if (UIKit::getCharXY(i, 2) == char(15)) {		//ON CHERCHE OU SONT LES LASERS EGARES DU VAISSEAU VERS LE HAUT
					UIKit::gotoXY(i, 2); std::cout << ' ' << std::endl;   //PUIS ON LES EFFACES
				}
			}


		} while (!game_over); //TANTQUE GAME_OVER EST DIFFERENT DE TRUE(FALSE) ALORS ON CONTINU LA PARTIE

	} //FIN DE NIVEAU

	if (niveau == 3) {

		//ON PLACE LES MARTIENS
		martien1.coord.setPositionX(10);
		martien1.coord.setPositionY(7);
		UIKit::color(7); martien1.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////////
		martien2.coord.setPositionX(20);
		martien2.coord.setPositionY(7);
		UIKit::color(7); martien2.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////
		martien3.coord.setPositionX(30);
		martien3.coord.setPositionY(7);
		UIKit::color(7); martien3.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////
		martien4.coord.setPositionX(40);
		martien4.coord.setPositionY(7);
		UIKit::color(7); martien4.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////
		martien5.coord.setPositionX(50);                                                 //y = 7 x = 10;20;30;40;50;60
		martien5.coord.setPositionY(7);
		UIKit::color(7); martien5.putExtraTerrestre();
		/////////////////////////////////////////////////////////////////////
		martien6.coord.setPositionX(60);                                                 //y = 7 x = 10;20;30;40;50;60
		martien6.coord.setPositionY(7);
		UIKit::color(7); martien6.putExtraTerrestre();

		/*******************************************************************************************************************************************************/

		//ON PLACE LES PLUTONIENS      //y = 14 x = 15;25;35;45;55
		plutonien1.coord.setPositionX(15);
		plutonien1.coord.setPositionY(14);
		UIKit::color(7); plutonien1.putExtraTerrestre();
		////////////////////////////////////////////////////////////////////
		plutonien2.coord.setPositionX(25);
		plutonien2.coord.setPositionY(14);
		UIKit::color(7); plutonien2.putExtraTerrestre();
		////////////////////////////////////////////////////////////////////
		plutonien3.coord.setPositionX(35);
		plutonien3.coord.setPositionY(14);
		UIKit::color(7); plutonien3.putExtraTerrestre();
		////////////////////////////////////////////////////////////////////
		plutonien4.coord.setPositionX(45);
		plutonien4.coord.setPositionY(14);
		UIKit::color(7); plutonien4.putExtraTerrestre();
		////////////////////////////////////////////////////////////////////
		plutonien5.coord.setPositionX(55);
		plutonien5.coord.setPositionY(14);
		UIKit::color(7); plutonien5.putExtraTerrestre();

		Sleep(500);
		UIKit::gotoXY(20, 40); UIKit::color(1); std::cout << char(18);   //ON AFICHE LA POSITION DE DEPART DU VAISSEAU


		int cpt = 0;
		int cptLaserVaisseau = 0;


		do {

			//TIRS
			for (int a = 1; a < 65; a++) {
				if (UIKit::getCharXY(a, 7) == char(143) && cpt == 0) {
					UIKit::gotoXY(a, departMissileMartien); std::cout << '/' << std::endl;
				}
				if (UIKit::getCharXY(a, 14) == char(232) && cpt == 0) {
					UIKit::gotoXY(a, departMissilePlutonien); std::cout << '/' << std::endl;
				}
			}
			for (int a = 1; a < 65; a++) {
				if (UIKit::getCharXY(a, departMissileMartien) == '/') {
					Sleep(5);
					UIKit::gotoXY(a, departMissileMartien); std::cout << ' ' << std::endl;
					UIKit::gotoXY(a, departMissileMartien + 1); std::cout << '/' << std::endl;
				}
				if (UIKit::getCharXY(a, departMissilePlutonien) == '/') {
					Sleep(5);
					UIKit::gotoXY(a, departMissilePlutonien); std::cout << ' ' << std::endl;
					UIKit::gotoXY(a, departMissilePlutonien + 1); std::cout << '/' << std::endl;
				}
			}

			cpt++;
			departMissileMartien++;
			departMissilePlutonien++;
			if (departMissileMartien > 40) {
				departMissileMartien = 8;
				cpt = 0;
			}
			if (departMissilePlutonien > 40) {
				departMissilePlutonien = 15;
				cpt = 0;
			}


			if (vieVaisseau.getPv() <= 0) {		//SI PARMIS LES DEGATS PRIS LA VIE DU VAISSEAU EST 0 LA PARTIE SE TERMINE
				game_over = true;
				PlaySound(TEXT("Debug/Die.wav"), NULL, SND_SYNC);
			}


			if (GetAsyncKeyState(0x4B) || GetAsyncKeyState(0x4C)) {  //TOUCHES K OU L TAPEZ
				mouvementVaisseau();
			}
			else if (GetAsyncKeyState(0x56)) {  //TOUCHE V TAPEZ
				PlaySound(TEXT("Debug/shoot.wav"), NULL, SND_SYNC);
				for (int i = 2; i < 74; i++) {
					char tevoila;
					tevoila = UIKit::getCharXY(i, 40);   //CHERCHE EN SE BASANT SUR LA LIGNE 40 OU SE DEPLACE LE VAISEAU (Y = 40)
					if (tevoila == char(18)) {
						nouvellePositionLaser = i;             //VA INTERPRETER LA CORDONNEE Y COMME X ET LE LASER SE PLACERA EXACTEMENT OU SE TROUVE LE VAISSEAU
					}
				}
				if (cptLaserVaisseau == 0) {
					UIKit::gotoXY(nouvellePositionLaser, 39); UIKit::color(4); std::cout << char(15);    //LA POSITION X D'OU PART LE LASER  COULEUR = ROUGE
				}
				for (int u = 39; u > 2; u--) {

					if (UIKit::getCharXY(nouvellePositionLaser, u - 1) == char(143)) {
						point.setScore(100);													//POINT POUR LES MARTIENS
						afficherScore();
					}
					if (UIKit::getCharXY(nouvellePositionLaser, u - 1) == char(232)) {
						point.setScore(50);												//POINT POUR LES PLUTONIENS
						afficherScore();
					}

					if (UIKit::getCharXY(nouvellePositionLaser, u) == char(15)) {
						Sleep(20);	//DELAIS DE TEMPS DE DEPLACEMENT DU LASER (PLUS LE DELAIS EST GRAND MOINS LE LASER EST RAPIDE
						UIKit::gotoXY(nouvellePositionLaser, u); std::cout << " ";
						Sleep(20);	//DELAIS DE TEMPS DE DEPLACEMENT DU LASER (PLUS LE DELAIS EST GRAND MOINS LE LASER EST RAPIDE
						UIKit::gotoXY(nouvellePositionLaser, u - 1); UIKit::color(4); std::cout << char(15);
					}
				}
			}

			if (point.getScore() == 850) {
							//SI LE SCORE TOTAL EST ATTEINT PARTIE GAGNEE
				PlaySound(TEXT("Debug/Win.wav"), NULL, SND_SYNC);
				UIKit::gotoXY(20, 25); std::cout << "!!!! YOU WIN !!!! ";
				Sleep(5800);
				game_over = true;
			}

			for (int i = 2; i < 70; i++) {			//SI LE MISSILLE ENNEMI SE TROUVE DEVANT LE VAISSEAU ALORS IL PREND DES DEGATS
				if (UIKit::getCharXY(i, 40) == char(18) && UIKit::getCharXY(i, 39) == '/') {
					vieVaisseau.setPv(50);     //SERT A REDUIRE LES POINTS DE VIE DU VAISSEAU
					afficherPv();
				}
			}

			for (int i = 2; i < 65; i++) {
				if (UIKit::getCharXY(i, 41) == '/') {		//ON CHERCHE OU SONT LES LASERS EGARES DES ENNEMIS
					UIKit::gotoXY(i, 41); std::cout << ' ' << std::endl;   //PUIS ON LES EFFACES
				}
			}

			for (int i = 2; i < 65; i++) {
				if (UIKit::getCharXY(i, 2) == char(15)) {		//ON CHERCHE OU SONT LES LASERS EGARES DU VAISSEAU VERS LE HAUT
					UIKit::gotoXY(i, 2); std::cout << ' ' << std::endl;   //PUIS ON LES EFFACES
				}
			}


		} while (!game_over); //TANTQUE GAME_OVER EST DIFFERENT DE TRUE(FALSE) ALORS ON CONTINU LA PARTIE

	} //FIN DE NIVEAU

	UIKit::gotoXY(10, 30); std::cout << "VOULEZ-VOUS FAIRE UNE AUTRE PARTIE (1-OUI / 0-NON) ? : ";
	keybd_event(27,0,0,0);
	keybd_event(27, 0, KEYEVENTF_KEYUP, 0);
	std::cin >> choix;
	if (choix == 1) {
		vieVaisseau.setPv(500);//CHAQUE FOIS QU'ON RELANCERA UNE PARTIE LA VIE DU VAISEAU SERA REMISE A 500.
		demarrerPartie();
	}
	else if (choix == 0) {
		UIKit::gotoXY(20, 25); std::cout << "!!!! GAME OVER !!!! ";
		PlaySound(TEXT("Debug/game_over.wav"), NULL, SND_SYNC);
		system("CLS");
		//system("start /MIN Credit.wav ");
		//Sleep(1500);
		UIKit::gotoXY(25, 25); UIKit::color(4); std::cout << "                  MERCI D'AVOIR JOUER A BIENTOT !!!";
		PlaySound(TEXT("Debug/Credit.wav"), NULL, SND_SYNC);
		system("CLS");
		ifstream fichier("Debug/Credit.txt", ios::in);
		if (fichier) {  // si l'ouverture a fonctionné
			string ligne;
			while (getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
			{
				UIKit::color(4); cout << ligne << endl;  // on l'affiche  COULEUR = ROUGE
				Sleep(1000);
			}
			fichier.close();
		}
		Sleep(200);
		exit(0);
	}

}
