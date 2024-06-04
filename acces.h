//Tous les fichiers ".h" reprennent les mêmes
//directives de préprocesseur de manière à ne compiler qu'une seule fois 
//les ".h" et ".cpp" correspondants
//Par convention la directive porte le nom des fichiers en majuscule suivi de "_H"
#ifndef ACCES_H
#define ACCES_H
#include <EEPROM.h>

//Plan EEPROM
#define EEPROM_ADR_ACCES	1
//#define EEPROM_SAVE			;
#define EEPROM_SAVE			EEPROM.put(EEPROM_ADR_ACCES,*this);delay(2000);



//Déclaration de la classe
class CAcces 
{
	private:
		
		char 		m_nom_acces[50] = "trinquet"; 	// 50 octets
		char		m_nom_portA[50] = "porte"; 	// 50 octets
		int 		m_portA = 13;			// 2  octets
		char    	m_nom_portB[50] = "lumiere";	// 50 octets 
		int 		m_portB = 13; 				// 2 octets
		int 		m_sec_gache = 10;		// 2 octets	
		bool 		m_hs = false;			// 1 octet
		CInstant 	m_instant_ferme = 0;		// 8 octets
		CInstant 	m_horloge = 0;			// 8 octets
		uint32_t 	m_millis_start;			// 4 octets
		
	public:
	    CAcces();
		void 		Init();//Mise à jour des attributs (valeur par defaut) puis depuis l'EEPROM
		void 		Ouvre(int minutes);
		int 		CtrlTempsRestant(CPeriode reservation);
		void 		Controle();
		String 		GetReponseAcces(String reponse_serveur);
		void 		SetHeureSystem(String& reponse_serveur);
		CInstant 	GetHeureSystem();
		CPeriode 	GetPeriodeServeur(String& reponse_serveur);

		String 		GetParam();
		void 		ConfigParSms(String& sms);
		void 		SetNom(String nom);
		void 		SetNomPortA(String nomPortA);
		void 		SetPortA(int portA);
		void 		SetNomPortB(String nomPortB);
		void 		SetPortB(int portB);
		void 		SetSecGache(int secGache );
		void 		SetHs(bool hs);
		bool 		EstHs();
	
};
//Fin des directives de préprocesseur 
#endif

