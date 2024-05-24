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
		
		String m_nom_acces;
		char         m_nom_acces[50] = ""; // = GetStringLongueurFixe("Piscine 25", 25);
		int m_portA = 10;
		String m_nom_portA; 
		char         m_nom_portA[50] = ""; // GetStringLongueurFixe("porte 4", 25) ;
		int m_portB = 20;
		String m_nom_portB;
		char         m_nom_portB[50] = ""; // GetStringLongueurFixe("porte 10", 25);
		int m_sec_gache = 0;
		bool m_hs = false;
		CInstant m_instant_ferme;
		CInstant m_horloge = 0;
		uint32_t m_millis_start;
		
	public:
	    CAcces();
		void Init();//Mise à jour des attributs (valeur par defaut) puis depuis l'EEPROM
		String GetParam();
		void ConfigParSms(String& sms);
		void SetNom(String nom);
		void SetNomPortA(String nomPortA);
		void SetPortA(int portA);
		void SetNomPortB(String nomPortB);
		void SetPortB(int portB);
		void SetSecGache(int secGache );
		void SetHs(bool hs);
		bool EstHs();
		void Ouvre(int minutes);
		int CtrlTempsRestant(CPeriode reservation);
		void Controle();
		String GetReponseAcces(String reponse_serveur);
		void SetHeureSystem(String& reponse_serveur);
		CInstant GetHeureSystem();
		CPeriode GetPeriodeServeur(String& reponse_serveur);

	
};
//Fin des directives de préprocesseur 
#endif
