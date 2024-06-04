#include "appli.h"
// Constructeur par défaut
CAcces::CAcces() 
{
}

CPeriode CAcces::GetPeriodeServeur(String& reponse_serveur)
{
  CPeriode periode_reserv;
  String debut = GetValeur(reponse_serveur, "debut:");

  uint16_t jour = debut.substring(0, 2).toInt();
  uint16_t mois = debut.substring(3, 5).toInt();
  uint16_t an = debut.substring(6, 8).toInt();
  float heure = (GetValeur(reponse_serveur, "heure:" ).toFloat());
  uint16_t seconde = (int)((heure - (int)heure)*3600.0);
  uint16_t minute  = seconde/60;
  
  periode_reserv.SetHeure(heure, minute, seconde);
  periode_reserv.SetDate(jour, mois, an);

  periode_reserv.SetDuree(GetValeur(reponse_serveur, "duree:" ).toFloat());
  periode_reserv.SetCycle(GetValeur(reponse_serveur, "cycle:" ).toInt());

  String fin = GetValeur(reponse_serveur, "fin:" );
  uint16_t jour_fin = fin.substring(0,2).toInt();
  uint16_t mois_fin = fin.substring(3,5).toInt();
  uint16_t an_fin = fin.substring(6,8).toInt(); 
//Serial.print("deb : ");
//Serial.println(periode_reserv.GetMessage());
	periode_reserv.SetFin(jour_fin, mois_fin, an_fin);
  
  return periode_reserv;

}

// Fonction pour mettre à jour la date et l'heure de l'instant
void CAcces::SetHeureSystem(String& reponse_serveur) 
{
	//"date: Thu, 31 Aug 2023 10:47:23 GMT"
    // Extraire la date et l'heure de la réponse du serveur
    // version always data int debut_date = reponse_serveur.indexOf("date: ") + 6;
    int debut_date = reponse_serveur.indexOf("Date: ") + 6;
    int fin_date = reponse_serveur.indexOf(" GMT");
    String date_heure = reponse_serveur.substring(debut_date, fin_date);
    // Extraire les parties de la date et de l'heure
    String st_jour = date_heure.substring(5, 7);
    unsigned int jour = st_jour.toInt();
    String st_mois = date_heure.substring(8, 11);
	unsigned int mois = m_horloge.Month2Nombre(st_mois);    

    unsigned int an = date_heure.substring(12, 16).toInt();
    unsigned int heure = date_heure.substring(17, 19).toInt();
	heure ++;//GMT
    unsigned int minute = date_heure.substring(20, 22).toInt();
    unsigned int seconde = date_heure.substring(23, 25).toInt();
   
	m_horloge.SetDate(jour, mois, an);
	m_horloge.SetHeure(heure, minute, seconde);
	m_horloge.DecaleGMT();
	m_horloge.SetDate(jour, mois, an);


	m_millis_start = millis();  
}

CInstant CAcces::GetHeureSystem()
{
	unsigned long millisec = millis() - m_millis_start;
	unsigned long secondes = millisec/1000;
	
	CInstant heure_syst;
	heure_syst.SetInstant(m_horloge);
	heure_syst.Add(secondes);
	return heure_syst;
}

/*CTRLtemps restant
elle recoit la periode de reservation c_periode
apres elle calcul le temps restant avec la focntion minute restant par rapport à l'heure systeme
si il reste des minutes elle appelle la fonction ouvre pour se nombre de minutes restantes
a la fin elle return les minutes restantes*/
int CAcces::CtrlTempsRestant(CPeriode reservation)
{
	int min_rest = reservation.MinutesRestantes(GetHeureSystem());
	/*Serial.print("mins restantes :");
	Serial.println(min_rest);
	Serial.print("heure sys :");
	Serial.println(GetHeureSystem().GetMessage());
	*/
	if (min_rest)		Ouvre(min_rest);

	return min_rest;
	
}

/*ouvre elle renvois rien, elle recoit des minutes d'ouverture 
si l'acces est hors service ou so les minutes sont = a 0 
l'instant de fermeture (l'instant ferm = 0)
sinon
l'instant de fermeture prends l'heure systeme
controle durée gache 
si il existent de seconde gache 
l'instant ferme + seconde gache
autrtement c'est une ouverture public 
l'instant ferme + les minutes d'ouverture ens econdes
on fais une sauvegarde en EPROM et ensuite on controle la commande avce la fonction commande*/
void CAcces::Ouvre(int minutes)
{
	//minutes = m_sec_gache;
	if (m_hs == false || minutes == 0)
		m_instant_ferme.SetInstant(0);
	//Préparation d'ouverture (instant ferme reçoit l'heure système)
	if (m_hs == false && minutes)
		m_instant_ferme.SetInstant(GetHeureSystem());
	//Finalisation de l'ouverture (ajout de secondes et de minutes)
	if (m_sec_gache != 0)
		m_instant_ferme.Add(m_sec_gache);
	else
		m_instant_ferme.Add(minutes*60);
	//on fais une sauvegarde en EPROM
	//et ensuite on controle la commande avce la fonction commande
}

void CAcces::Controle()
{
	if (m_instant_ferme.SuperieurA(GetHeureSystem()))
		Serial.print("+");
	else
		Serial.print("-");
	
	digitalWrite(m_portA, (m_instant_ferme.SuperieurA(GetHeureSystem())));
	digitalWrite(m_portB, (m_instant_ferme.SuperieurA(GetHeureSystem())));
}

String CAcces::GetReponseAcces(String reponse_serveur)
{
	String sms;
	if (reponse_serveur == "")
		Serial.print("PAS DE REPONSE SERVEUR");
	else
	{
		SetHeureSystem(reponse_serveur);
	    CPeriode reservation = GetPeriodeServeur(reponse_serveur);

		int temps_restant = CtrlTempsRestant(reservation);

	
		sms += "Bonjour ";
		sms += GetValeur(reponse_serveur, "prenom:");
		sms += " ";
		sms += GetValeur(reponse_serveur, ">nom:");
		sms += "\nNOUS SOMMES LE :";
		sms += m_horloge.GetMessage();
		sms += "\nvotre acces : ";
		sms += GetValeur(reponse_serveur, "designation:");
		sms += reservation.GetMessage();

		if(temps_restant)
		{
			sms +=  "\nMinutes restantes : ";
			sms +=  String (temps_restant);
		}
		else sms +=  " \nPas de minute restantes,\nhors periode\nouverture impossible";
	}
	return sms ;
}



//yon 
//Initialisation de l'accès
void CAcces::Init()
{
	// lit l'EEPROM à l'adresse donnée et MAJ les attributs de CAcces
	EEPROM.get(EEPROM_ADR_ACCES, *this);
	// définition des ports en sortie 
	pinMode(m_portA, OUTPUT);
	pinMode(m_portB, OUTPUT);
	//mise à 0 des ports
	digitalWrite(m_portA, HIGH);
	delay(1000);
	digitalWrite(m_portB, LOW);
	// afficher tous les paramètres des accès
	Serial.println(GetParam());
}

void CAcces::ConfigParSms(String& sms)
{
	 //Mise en majuscule systématique pour éviter les confusions majuscules minuscules
    sms.toUpperCase();
    //Désignation accès
    String param = "ACCES:";
    if (sms.indexOf(param) != -1)
        SetNom(GetValeur(sms, param));
	
	param = "NOM PORTA:";
	if (sms.indexOf(param) != -1)
		SetNomPortA(GetValeur(sms, param));
	
	param = "PORT A:";
	if (sms.indexOf(param) != -1)	
		SetPortA(GetValeur(sms, param).toInt());
	
	param = "NOM PORTB:";
	if (sms.indexOf(param) != -1)
		SetNomPortB(GetValeur(sms, param));
	
	param = "PORT B:";
	if (sms.indexOf(param) != -1)
		SetPortB(GetValeur(sms, param).toInt());
	
	param = "GACHE:";
	if (sms.indexOf(param) != -1)
		SetSecGache(GetValeur(sms, param).toInt());
	
	param = "EN SERVICE";
	if (sms.indexOf(param) != -1)
		SetHs(false);
	
	param = "HORS SERVICE";
	if (sms.indexOf(param) != -1)
		SetHs(true);
	
	//Ouvre en minutes
	param = "OUVRE:";
	if (sms.indexOf(param) != -1)
		Ouvre(GetValeur(sms, param).toInt());
	
	Serial.print(GetParam());

}

String CAcces::GetParam()
{
	Serial.println("Init acces");
	String param = "\nACCES:";
	param += m_nom_acces;
	param += "\nportA : ";
	param += m_nom_portA;
	param += " : ";
	param += m_portA;
	param += "\nportB : ";
	param += m_nom_portB;
	param += " : ";
	param += m_portB;
	param += "\nSecondes ouverture gâche : ";
	param += m_sec_gache;
	// if est hs ou pas
	if (EstHs())
		param += "\nHors service";
	else 
		param+= "\nEn service";
	param += "\nHeure système: \n";
	param += GetHeureSystem().GetMessage();
	param += "\nfermeture: \n";
	param += m_instant_ferme.GetMessage();
	return param;
} 


void CAcces::SetNom(String nom)
{
	nom.toCharArray(m_nom_acces, 50);
	EEPROM_SAVE;
	Serial.println(GetParam());
}

void CAcces::SetNomPortA(String nomPortA)
{
	nomPortA.toCharArray(m_nom_portA, 50);
	EEPROM_SAVE;
	Init();
}

void CAcces::SetPortA(int portA)
{
	m_portA = portA;
	EEPROM_SAVE;
	Init();
}

void CAcces::SetNomPortB(String nomPortB)
{
	nomPortB.toCharArray(m_nom_portB, 50);
	EEPROM_SAVE;
	Init();
}

void CAcces::SetPortB(int portB)
{
	m_portB = portB;
	EEPROM_SAVE;
	Init();
}

void CAcces::SetSecGache(int secGache )
{
	m_sec_gache = secGache;
	EEPROM_SAVE;
	Init();
}

void CAcces::SetHs(bool hs)
{
	m_hs = hs;
	EEPROM_SAVE; 
	Init();
}

bool CAcces::EstHs()
{
	return m_hs;
}

