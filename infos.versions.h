#ifndef INFOS_VERSIONS_H
#define INFOS_VERSIONS_H

/*Création du projet : 
#define	VERSION	"GSM_ACCES_2024.02.XX.V00"
	Création
#define	VERSION	"GSM_ACCES_2024.02.XX.V01"

#define	VERSION	"GSM_ACCES_2024.02.XX.V02"

#define	VERSION	"GSM_ACCES_2024.02.12.V03"

#define	VERSION	"GSM_ACCES_2024.02.12.V04"
	Objectifs :
	Envoi requête API avec num tel appelant 
	Récup réponse
	Réseau GSM OK
	WEB OK
	Récup num appelant OK
	Envoi requête OK
	Réception requête OK
#define	VERSION	"GSM_ACCES_2024.03.04.V05"
	Objectifs :
	Création de la fonction RecoitSMS	OK
	Test d'un envoi et de réception de SMS	OK
#define	VERSION	"GSM_ACCES_2024.03.05.V06"
	Objectifs :
	Intégration de CAcces et de CPeriode
	Mise à jour de CInstant
	Compile mais CAcces incomplète :
	- GetHeureSystem();
	- GetReponseAcces(String reponse_serveur);
	- Controle()
#define	VERSION	"GSM_ACCES_2024.03.18.V07"
	Mise à jour de CAcces (corenthin me la envoyé) mais il manque : 
	- GetReponseAcces(String reponse_serveur);
	- Controle()
	Mais le programme compile et fonctionne en l'état actuel
#define	VERSION	"GSM_ACCES_2024.03.18.V08"
	Mise à jour de CAcces et le programme fonctionne complètement (Corenthin est en train de réaliser le décalage GMT+1 car
	dans ce programme, le serveur nous renvoie l'heure GMT+0 qui ne correspond pas à l'heure française)
#define	VERSION	"GSM_ACCES_2024.03.27.V09"
	Changement de l'API en modèle PHP MVC (Dany et Quentin sont en train de travailler dessus)
	Décalage GMT est fonctionnel (Réalisé par Corenthin)
#define	VERSION	"GSM_ACCES_2024.05.30.V11"
	URL du lycée : 185.182.169.30 port : 1024
	// version always data : int debut_date = reponse_serveur.indexOf("date: ") + 6; d miniscule.
#define	VERSION	"GSM_ACCES_2024.05.30.V12"
	Insertion commande d'ouverture "Ouvre:" en mode service régisseur par SMS
	Commande OUVRE:0 affecte l'instant d'ouverture à 0
	void CAcces::ConfigParSms(String& sms)
	Modification de la fonction : void CAcces::Ouvre(int minutes)
	Modification de : CInstant CAcces::GetHeureSystem() et ajout des millis depuis la mise sous tension
	//modification de l'heuresyst
#define	VERSION	"GSM_ACCES_2024.06.04.V13"
	Modif nom fonction : String CHttpGsm::GetReponseClient(int delai) => String CHttpGsm::GetReponseServeur(int delai)
	Modif fonction : String CHttpGsm::GetReponseServeur(int delai):	reponse.replace("<br>", "\n");
		Suppression des <br>
		
#define	VERSION	"GSM_ACCES_2024.06.04.V14"
	Debug décalage 1h CPeriode en cours
		14:46:07.592 -> Tel:0646811496
		14:46:07.592 -> prenom:Bixente
		14:46:07.592 -> nom:MATHEU
		14:46:07.592 -> debut:03/06/24
		14:46:07.592 -> fin:14/06/24
		14:46:07.592 -> heure:9 // bug
		14:46:07.592 -> duree:9
		14:46:07.592 -> cycle:1
		14:46:07.592 -> Acces:1
		14:46:07.592 -> designation:Salle Omnisport
		14:46:07.592 -> 
		14:46:07.592 -> 
		14:46:07.592 -> 
		14:46:09.709 -> Message Envoyé :
		14:46:09.709 -> Bonjour Bixente 
		14:46:09.709 -> NOUS SOMMES LE :MAR 4/JUIN/2024 A 14H46:04
		14:46:09.709 -> 
		14:46:09.709 -> votre acces : Salle Omnisport
		14:46:09.709 -> Période du LUN 3/JUIN/2024 A 10H00:00
		14:46:09.709 -> AU 14/06/2024. Durée : 9.00 heure(s).
		14:46:09.745 -> Minutes restantes : 253

	Modif de : void CAcces::SetHeureSystem(String& reponse_serveur) 
		Ligne 38 : heure ++;//GMT
*/

#define	VERSION	"GSM_ACCES_2024.06.04.V14"
 
#endif
