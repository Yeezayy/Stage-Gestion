#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Charge les informations des étudiants depuis un fichier.
 * 
 * Cette fonction charge les données des étudiants, y compris les numéros d'étudiant, les stages attribués,
 * et les notes finales, dans les tableaux fournis.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param tmax Taille maximale des tableaux.
 * 
 * @return Le nombre d'étudiants chargés.
 */
int fChargementEtu(int tEtu[], int tStage[], float tNoteF[], int tmax);

/**
 * @brief Charge les informations des stages depuis un fichier.
 * 
 * Cette fonction charge les données des stages, y compris les références de stage, les départements, les états de pourvu,
 * les candidatures des étudiants, dans les tableaux fournis.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCand Tableau des candidatures des étudiants.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param tmax Taille maximale des tableaux.
 * 
 * @return Le nombre de stages chargés.
 */
int fChargementStage(int tRef[], int tDept[], int tPourvu[], int tCand[], int tCandEtu[][3], int tmax);



/**
 * @brief Attribue des mentions aux étudiants en fonction de leurs notes.
 * 
 * Cette fonction attribue une mention aux étudiants en fonction de leurs notes dans les tableaux fournis.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param mentions Tableau des mentions des étudiants.
 * @param tmax Taille maximale des tableaux.
 */
void attribuerNotes(int tEtu[], int tStage[], int nb_etudiants, char mentions[][20], int tmax);

/**
 * @brief Affiche les notes des étudiants par ordre décroissant.
 * 
 * Cette fonction affiche les notes des étudiants triées par ordre décroissant, en utilisant les tableaux
 * d'étudiants, de stages et de notes finales fournis.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param mentions Tableau des mentions des étudiants.
 */
void afficherNotesParOrdreDecroissant(int tEtu[], int tStage[], float tNoteF[], int nb_etudiants, char mentions[][20]);



/**
 * @brief Ajoute un étudiant dans les tableaux correspondants.
 * 
 * Cette fonction permet d'ajouter un étudiant avec ses informations dans les tableaux d'étudiants, de stages,
 * et de notes finales.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nb_etudiants Pointeur vers le nombre d'étudiants.
 * @param tmax Taille maximale des tableaux.
 * 
 * @return 1 si l'étudiant a été ajouté avec succès, 0 sinon.
 */
int ajouter_etudiant(int tEtu[], int tStage[], float tNoteF[], int *nb_etudiants, int tmax);

/**
 * @brief Supprime un étudiant des tableaux correspondants.
 * 
 * Cette fonction permet de supprimer un étudiant en fonction de son numéro et de mettre à jour les tableaux
 * d'étudiants, de stages et de notes finales.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nbEtu Pointeur vers le nombre d'étudiants.
 * @param num Numéro de l'étudiant à supprimer.
 * 
 * @return 1 si l'étudiant a été supprimé avec succès, 0 sinon.
 */
int supprimerEtu(int tEtu[], int tStage[], float tNoteF[], int *nbEtu, int num);

/**
 * @brief Ajoute un stage dans les tableaux correspondants.
 * 
 * Cette fonction permet d'ajouter une offre de stage dans les tableaux des références, départements, et candidatures.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCand Tableau des candidatures des étudiants.
 * @param nbStages Pointeur vers le nombre de stages.
 * @param tmax Taille maximale des tableaux.
 * 
 * @return 1 si le stage a été ajouté avec succès, 0 sinon.
 */
int ajouter_stage(int tRef[], int tDept[], int tPourvu[], int tCand[], int *nbStages, int tmax);

/**
 * @brief Supprime un stage des tableaux correspondants.
 * 
 * Cette fonction permet de supprimer une offre de stage en fonction de sa référence et de mettre à jour les tableaux
 * des références, départements, et candidatures.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCand Tableau des candidatures des étudiants.
 * @param nbStages Pointeur vers le nombre de stages.
 * @param refStage Référence du stage à supprimer.
 * 
 * @return 1 si le stage a été supprimé avec succès, 0 sinon.
 */
int supprimer_stage(int tRef[], int tDept[], int tPourvu[], int tCand[], int *nbStages, int refStage);



/**
 * @brief Permet à un étudiant de candidater à un stage.
 * 
 * Cette fonction permet à un étudiant de candidater à un stage donné en fonction de son numéro et de la référence
 * du stage. Elle met à jour les candidatures et les informations liées aux stages.
 * 
 * @param etuNum Numéro de l'étudiant.
 * @param refStage Référence du stage auquel candidater.
 * @param tRef Tableau des références des stages.
 * @param tCand Tableau des candidatures des étudiants.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param tDept Tableau des départements des stages.
 * @param nbStages Nombre de stages.
 * 
 * @return 1 si la candidature a été enregistrée avec succès, 0 sinon.
 */
int candidater(int etuNum, int refStage, int tRef[], int tCand[], int tPourvu[], int tCandEtu[][3], int tDept[], int nbStages);

/**
 * @brief Affecte un stage à un étudiant.
 * 
 * Cette fonction affecte un stage à un étudiant en fonction de son numéro et de la référence du stage. Elle met
 * à jour les tableaux des étudiants et des stages.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param tmax Taille maximale des tableaux.
 * @param refStage Référence du stage à affecter.
 * @param numero Numéro de l'étudiant à affecter au stage.
 */
void affecter_stage(int tEtu[], int tStage[], int nb_etudiants, int tmax, int refStage, int numero);



/**
 * @brief Recherche un élément dans un tableau.
 * 
 * Cette fonction recherche un élément donné dans un tableau. Elle met à jour une variable de résultat indiquant
 * si l'élément a été trouvé.
 * 
 * @param numero L'élément à rechercher.
 * @param tableau Le tableau dans lequel rechercher.
 * @param taille Taille du tableau.
 * @param trouve Pointeur vers une variable indiquant si l'élément a été trouvé.
 * 
 * @return 1 si l'élément est trouvé, 0 sinon.
 */
int fRechercher(int numero, int tableau[], int taille, int *trouve);

/**
 * @brief Permet de rechercher des stages selon un critère.
 * 
 * Cette fonction permet de rechercher des stages en fonction de différents critères, tels que la référence,
 * le département, et l'état de pourvu.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 */
void rechercherStages(int tRef[], int tDept[], int tPourvu[], int nb_stages);



/**
 * @brief Affiche les informations d'un étudiant.
 * 
 * Cette fonction affiche les informations d'un étudiant donné en utilisant ses numéros d'étudiant, son stage, 
 * et sa note finale.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nbEtu Nombre d'étudiants.
 * @param num Numéro de l'étudiant à afficher.
 */
void afficherEleves(int tEtu[], int tStage[], float tNoteF[], int nbEtu, int num);

/**
 * @brief Affiche les candidatures d'un étudiant.
 * 
 * Cette fonction affiche les candidatures d'un étudiant donné en fonction de son numéro.
 * 
 * @param etuNum Numéro de l'étudiant.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param tRef Tableau des références des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 */
void afficherCandidaturesEtudiant(int etuNum, int tCandEtu[][3], int tRef[], int tPourvu[], int nb_stages);

/**
 * @brief Affiche les étudiants sans stage.
 * 
 * Cette fonction affiche la liste des étudiants qui n'ont pas de stage attribué.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 */
void afficherEtudiantsSansStage(int tEtu[], int tStage[], int nb_etudiants);

/**
 * @brief Affiche les stages.
 * 
 * Cette fonction affiche les informations sur les stages, y compris les références, les départements,
 * et l'état de pourvu.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param tCand Tableau des candidatures des étudiants.
 * @param nbStages Nombre de stages.
 */
void afficherStages(int tRef[], int tDept[], int tPourvu[], int tCand[], int nbStages);

/**
 * @brief Affiche les stages disponibles.
 * 
 * Cette fonction affiche la liste des stages disponibles (non pourvus).
 */
void afficherStagesDisponibles(void);

/**
 * @brief Affiche les stages d'un département spécifique.
 * 
 * Cette fonction affiche les stages disponibles dans un département donné.
 * 
 * @param numDept Numéro du département.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 */
void afficherStagesParDepartement(int numDept, int tRef[], int tDept[], int tPourvu[], int nb_stages);

/**
 * @brief Affiche les stages pourvus.
 * 
 * Cette fonction affiche les stages pourvus et les étudiants qui y sont affectés.
 * 
 * @param tRef Tableau des références des stages.
 * @param tEtu Tableau des numéros des étudiants.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 * @param nb_etudiants Nombre d'étudiants.
 */
void afficherStagesPourvus(int tRef[], int tEtu[], int tDept[], int tPourvu[], int nb_stages, int nb_etudiants);

/**
 * @brief Affiche les stages non pourvus.
 * 
 * Cette fonction affiche les stages qui ne sont pas encore pourvus.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 */
void afficherStagesNonPourvus(int tRef[], int tDept[], int tPourvu[], int nb_stages);

/**
 * @brief Affiche les stages non pourvus pour un responsable.
 * 
 * Cette fonction affiche les stages non pourvus spécifiquement pour un responsable.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 */
void afficherStagesNonPourvusResp(int tRef[], int tDept[], int tPourvu[], int nb_stages);

/**
 * @brief Affiche les informations d'un stage.
 * 
 * Cette fonction affiche les informations détaillées d'un stage, y compris la référence,
 * le département et l'état de pourvu.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param nb_stages Nombre de stages.
 */
void afficherInfoStage(int tRef[], int tDept[], int tPourvu[], int nb_stages);



/**
 * @brief Sauvegarde les informations des étudiants dans un fichier.
 * 
 * Cette fonction sauvegarde les informations des étudiants dans un fichier, y compris leur numéro,
 * leur stage, et leur note finale.
 * 
 * @param etudiants Tableau des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 */
void sauvegarder_etudiants(int tEtu[], int tStage[], float tNoteF[], int nbEtu);

/**
 * @brief Sauvegarde les informations des stages dans un fichier.
 * 
 * Cette fonction sauvegarde les informations des stages dans un fichier, y compris la référence, 
 * le département, et l'état de pourvu.
 * 
 * @param stages Tableau des stages.
 * @param nb_stages Nombre de stages.
 */
void sauvegarder_stages(int tRef[], int tDept[], int tPourvu[], int tCand[], int tCandEtu[][3], int nbStages);



/**
 * @brief Affiche le menu du jury.
 * 
 * Ce menu permet au jury de consulter les étudiants, leurs stages et leurs notes finales.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param tRef Tableau des références des stages.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 * @param mentions Tableau des mentions des étudiants.
 * @param tmax Taille maximale des tableaux.
 */
void menu_jury(int tEtu[], int tStage[], float tNoteF[], int tRef[], int nb_etudiants, int nb_stages, char mentions[][20], int tmax);

/**
 * @brief Affiche le menu étudiant.
 * 
 * Ce menu permet à l'étudiant de candidater à des stages, de consulter ses candidatures, et d'afficher
 * ses notes et informations personnelles.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param tCand Tableau des candidatures des étudiants.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 */
void menu_etudiant(int tEtu[], int tStage[], float tNoteF[], int tRef[], int tDept[], int tPourvu[], int tCand[], int tCandEtu[][3], int nb_etudiants, int nb_stages);

/**
 * @brief Permet à l'étudiant de gérer ses candidatures.
 * 
 * Cette fonction permet à l'étudiant de consulter ses candidatures et d'effectuer des actions en conséquence.
 * 
 * @param numero Numéro de l'étudiant.
 * @param tEtu Tableau des numéros des étudiants.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 */
void suite_etudiant(int numero, int tEtu[], int tRef[], int tDept[], int tPourvu[], int tCandEtu[][3], int nb_etudiants, int nb_stages);

/**
 * @brief Affiche le menu du responsable.
 * 
 * Ce menu permet au responsable de gérer les stages, de consulter les candidatures et de gérer les étudiants.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param tCand Tableau des candidatures des étudiants.
 * @param nbStages Pointeur vers le nombre de stages.
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param tmax Taille maximale des tableaux.
 * @param tCandEtu Tableau des candidatures des étudiants.
 */
void menu_responsable(int tRef[], int tDept[], int tPourvu[], int tCand[], int *nbStages, int tEtu[], int tStage[], int nb_etudiants, int tmax, int tCandEtu[][3]);

/**
 * @brief Affiche la suite du menu responsable.
 * 
 * Cette fonction permet au responsable de consulter les informations sur les stages, les étudiants et les candidatures.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau des états de pourvu des stages.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 */
void suite_responsable(int tEtu[], int tStage[], int tRef[], int tDept[], int tPourvu[], int tCandEtu[][3], int nb_etudiants, int nb_stages);

/**
 * @brief Affiche le menu principal.
 * 
 * Ce menu permet à l'utilisateur de choisir entre le menu jury, étudiant, ou responsable.
 */
void menu_principal(void);
