#include <iostream>
#include <random>
#include <iomanip>

/* Mathe-Vortrag | Wahrscheinlichkeitsrechnung - Pseudozahlengeneratoren | Lucas Barusic | Q2*/

class LinearCongruenceGenerator {

private:

	int number_size; //Anzahl an Zufallszahlen
	long int modulus;
	long int factor;
	long int increment;
	long int seed[100000]; //Startwert an seed[0] und Zufallszahlen mit seed[i > 2]

public:

	int calculate_result(int i) {
	
		seed[i] = (factor * seed[i - 1] + increment) % modulus; //Rechne die Zufallszahl aus
		return seed[i];
		
	}
	void setStandard() {
		modulus = 100;
		factor = 21;
		increment = 31;
		seed[0] = 35; //Setze Startwert
	}
	void setModulus(int input) {
		modulus = input; //Setze Modul auf Eingabewert
	}
	void setFactor(int input) {
		factor = input; //Setze Faktor auf Eingabewert
	}
	void setIncrement(int input) {
		increment = input;//Setze Inkrement auf Eingabewert
	}
	void setSeed(int input) { 
		seed[0] = input; //Setze Startwert
	}
	
	int getModulus() { 
		return modulus; //Gib das Modul an
	}
	int getFactor() { 
		return factor; //Gib den Faktor an
	}
	int getIncrement() {
		return increment; //Gib den Inkrement an
	}
	int getSeed() {
		return seed[0]; //Gib den Startwert an
	}

};

class MersenneTwisterGenerator {

private:

	std::random_device random_device; //Greift auf udev/random auf Linux oder auf die Microsoft CryptoApi auf Windows zurück
	std::mt19937 mtg{ random_device() }; //Der Mersenne Twister Generator

	int numbers[6] = {0,0,0,0,0,0}; //Für den Beweis des Gesetzes der großen Zahlen, als Speichermöglichkeit der absoluten Häufigkeiten
	int count = 50000;
	int temp;

public:

	int dice() { //Wuerfel
		std::uniform_int_distribution<int> numbers(0, 5); //Würfelzahlen 0-5, weil Array bei 0 startet
		return numbers(mtg); //Ausgabe des 
	}
	
	void lawoflargenumbers() {
		
		for (int i = 0; i < 50000; i++) {

			temp = dice();
			std::cout << temp;
			numbers[temp]++;
			
		}
		std::cout << "\n\nInsgesamte Wuerfelversuche: " << count << " Versuche" << std::endl;

		for (int i = 0; i < 6; i++) {
			std::cout << "\nAbsolute Haeufigkeit von " << i << ": " << numbers[i] << std::endl;
			std::cout << std::setprecision(13);
			double relative = (double)numbers[i] / count;
			std::cout << "\nRelative Haeufigkeit von " << i << ": " << relative << std::endl;
		}
	}

};


int main() {

	LinearCongruenceGenerator* lcg = new LinearCongruenceGenerator(); //Objekt von der Klasse LinearCongruenceGenerator, mit Zeiger wegen Speicher
	MersenneTwisterGenerator* mtg = new MersenneTwisterGenerator(); //Objekt von der Klasse MersenneTwisterGenerator, mit Zeiger wegen Speicher
	int input = NULL;

	std::cout << "\n\nWillkommen zu dem Programm zum Vortrag zu Wahrscheinlichkeitsrechnung - Vortrag Mathematik Q2-GK2 - Lucas Barusic\n\n"
		<< "1. Linearer Kongruenzgenerator: Standardwerte\n"
		<< "2. Linearer Kongruenzgenerator: Eigene Werte\n"
	    << "3. Mersenne Twister Engine: Wuerfel\n"
		<< "4. Mersenne Twister Engine: Beweis vom Gesetz der grossen Zahlen" << std::endl;

	std::cout << "Deine Eingabe: ";
	std::cin >> input;

	if (input == 1) {

		lcg->setStandard();
		
		std::cout << "Deine Zufallszahlen: ";

		for (int i = 1; i < 100; i++) {
			std::cout << lcg->calculate_result(i) << " ";
		}

		delete lcg;
		delete mtg;
		main();
	

	}
	else if (input == 2) {

		std::cout << "Gib Modulus an: ";
		std::cin >> input;
		lcg->setModulus(input);

		std::cout << "Gib Faktor an: ";
		std::cin >> input;
		lcg->setFactor(input);

		std::cout << "Gib Inkrement an: ";
		std::cin >> input;
		lcg->setIncrement(input);
	
		std::cout << "Gib Seed an: ";
		std::cin >> input;
		lcg->setSeed(input);

		std::cout << "Deine Zufallszahlen: ";

		for (int i = 1; i < 100; i++) {
			std::cout << lcg->calculate_result(i) << " ";
		}
		

	}
	else if (input == 3) {

		for (int i = 1; i < 100; i++) {
	    	std::cout << mtg->dice() << " ";
		}

	}
	else if (input == 4) {

		mtg->lawoflargenumbers();

	}
	else {
		std::cout << "ERROR: INVALID INPUT" << std::endl;
	}

	std::cout << "\n";
	delete lcg;
	delete mtg;
	main();
}

