#include "appli.h"

String parametre = "id:";
String sms_regie = "nom : Salle judo, id:5, portA:3, portB:4";


//Converti un entier en string
//Complète avec des 0 avant le nombre dans le string
String Int2String(int nombre, uint16_t decimal)
{
	if (nombre<10)
		return "0" + String(nombre);
	return String(nombre);
}

//Retourne le nombre de digits d'un entier
int GetDigit(int nombre)
{
	int digit = 0;
	do{
		nombre = nombre/10;
		digit++;
	}
	while (nombre);
	return digit;
}

/*
String CInstant::GetValeur( const String& reponse_serv, const String& balise) 
{
    String valeur;
    int posDebut = reponse_serv.indexOf(balise);
    if (posDebut != -1) {
        // Trouvé la balise, avancer jusqu'au début de la valeur
        posDebut += balise.length();
        // Chercher la fin de la valeur
        int posFin = reponse_serv.indexOf("\n", posDebut);
        if (posFin != -1) {
            // Extraire la valeur entre posDebut et posFin
            valeur = reponse_serv.substring(posDebut, posFin);
        }
    }
    return valeur;
}
*/

//Récupère la valeur d'un paramètre de la réponse serveur
String GetValeur(String& reponse, String parametre) 
{
	// Recherche de la position du paramètre dans la chaîne
	int posDebut = reponse.indexOf(parametre);
	// Le paramètre n'a pas été trouvé
	if (posDebut == -1) return "";

	// Avancer la position de début pour pointer juste après le mot-clef
	posDebut += parametre.length();

	// Recherche de la position du prochain retour à la ligne à partir de la position de début
	int posFin = reponse.indexOf('\n', posDebut);

	// Si le retour à la ligne n'a pas été trouvé, la fin est la fin de la chaîne
	if (posFin == -1) posFin = reponse.length();
 
	// Extrait la sous-chaîne entre posDebut et posFin
	String valeur = reponse.substring(posDebut, posFin);

	// Supprime les espaces inutiles 
	//en début et en fin de valeur
	valeur.trim();

	// Retourne la valeur trouvée
	return valeur;
	
  Serial.print("Valeur trouvée : ");
  Serial.println(valeur);
}

String GetStringLongueurFixe(String texte, int longueurfixe) 
{
    // Longueur du texte
    int longtxt = texte.length();
	//int longrestante = textefixe - longueurfixe;
	String textefixe = "";
	
    // Boucler pour ajouter les espaces à la fin du texte
    for (int i = 0; i < longueurfixe; i++) 
	{
        if (i < longtxt)
			textefixe += texte[i];
		else
			textefixe += ".";
    }

    // Retourner le texte de longueur fixe
    return textefixe;
}