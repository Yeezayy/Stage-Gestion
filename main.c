#include "main.h"


/**
 * @brief Charge les données des étudiants depuis un fichier dans des tableaux.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des références de stage attribuées aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param tmax Taille maximale des tableaux.
 * @return Nombre d'étudiants chargés, -1 si le fichier est introuvable, -2 si la capacité maximale est atteinte.
 */
int fChargementEtu(int tEtu[], int tStage[], float tNoteF[], int tmax) {
    int i = 0;
    int noEtu, refS, noteF;

    // Ouverture du fichier
    FILE *etudiants = fopen("fiche_etu.txt", "r");
    if (etudiants == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'fiche_etu.txt'.\n");
        return -1;
    }

    // Lecture ligne par ligne avec contrôle du retour de fscanf
    while (fscanf(etudiants, "%d\t%d\t%d", &noEtu, &refS, &noteF) == 3) {
        if (i >= tmax) {  // Vérifie si le tableau est plein
            printf("Erreur : Capacité maximale du tableau atteinte.\n");
            fclose(etudiants);
            return -2;
        }

        // Stocke les valeurs dans les tableaux
        tEtu[i] = noEtu;
        tStage[i] = refS;
        tNoteF[i] = noteF;

        i++;
    }

    // Fermeture du fichier
    fclose(etudiants);

    // Retourne le nombre d'étudiants chargés
    return i;
}


/**
 * @brief Charge les données des stages depuis un fichier dans des tableaux.
 * 
 * @param tRef Tableau des références de stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si le stage est pourvu.
 * @param tCand Tableau du nombre de candidatures par stage.
 * @param tCandEtu Tableau 2D des candidats pour chaque stage.
 * @param tmax Taille maximale des tableaux.
 * @return Nombre de stages chargés, -1 si le fichier est introuvable, -2 si la capacité maximale est atteinte.
 */
int fChargementStage(int tRef[], int tDept[], int tPourvu[],int tCand[], int tCandEtu[][3], int tmax) {
    int i = 0;
    int ref, dept, pourvu,nbCand;
    FILE *stages = fopen("offre_stage.txt", "r");
    if (stages == NULL) return -1;
    fscanf(stages, "%d %d %d %d", &ref, &dept, &pourvu,&nbCand);
    while (!feof(stages)) {
        if (i == tmax) {
            fclose(stages);
            return -2;
        }
        tRef[i] = ref;
        tDept[i] = dept;
        tPourvu[i]= pourvu;
        tCand[i] = nbCand;
        i++;
        fscanf(stages, "%d %d %d %d", &ref, &dept, &pourvu,&nbCand);
    }
    fclose(stages);
    return i;
}


/**
 * @brief Supprime un étudiant donné des tableaux et met à jour le fichier des étudiants.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des références de stage attribuées aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nbEtu Pointeur vers le nombre d'étudiants dans le tableau.
 * @param num Numéro de l'étudiant à supprimer.
 * @return 0 si succès, -1 si l'étudiant est introuvable, -2 si le fichier ne peut pas être ouvert.
 */
int supprimerEtu(int tEtu[], int tStage[], float tNoteF[], int *nb_etudiants, int num) {
    int trouve = 0;

    // Recherche de l'étudiant
    for (int i = 0; i < *nb_etudiants; i++) {
        if (tEtu[i] == num) {
            trouve = 1;

            // Décalage des éléments restants
            for (int j = i; j < *nb_etudiants - 1; j++) {
                tEtu[j] = tEtu[j + 1];
                tStage[j] = tStage[j + 1];
                tNoteF[j] = tNoteF[j + 1];
            }
            (*nb_etudiants)--;
            break;
        }
    }

    if (!trouve) {
        printf("Erreur : Étudiant %d introuvable.\n", num);
        return -1;
    }

    // Réécriture du fichier
    FILE *etudiants = fopen("fiche_etu.txt", "w");
    if (etudiants == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'fiche_etu.txt' pour la réécriture.\n");
        return -2;
    }
    for (int i = 0; i < *nb_etudiants; i++) {
        fprintf(etudiants, "%d\t%d\t%f\n", tEtu[i], tStage[i], tNoteF[i]);
    }
    fclose(etudiants);

    printf("L'étudiant %d a été supprimé avec succès et le fichier a été mis à jour.\n", num);
    return 0;
}


/**
 * @brief Recherche un numéro dans un tableau.
 * 
 * @param numero Numéro à rechercher.
 * @param tableau Tableau où effectuer la recherche.
 * @param taille Taille du tableau.
 * @param trouve Pointeur vers une variable indiquant si le numéro a été trouvé (1) ou non (0).
 * @return Index de l'élément trouvé, -1 si introuvable.
 */
int fRechercher(int numero, int tableau[], int taille, int *trouve) {
    for (int i = 0; i < taille; i++) {
        if (tableau[i] == numero) {
            *trouve = 1; 
            return i;    
        }
    }
    *trouve = 0;
    return -1;  
}


/**
 * @brief Ajoute un étudiant dans les tableaux et met à jour le fichier.
 * 
 * @param tEtu Tableau des numéros d'étudiants.
 * @param tStage Tableau des références de stage attribuées aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nb_etudiants Pointeur vers le nombre d'étudiants dans le tableau.
 * @param tmax Taille maximale des tableaux.
 * @return 0 si succès, -1 si la capacité maximale est atteinte, -2 si le fichier ne peut pas être ouvert.
 */
int ajouter_etudiant(int tEtu[], int tStage[], float tNoteF[], int *nb_etudiants, int tmax) {
    int numero;
    if (*nb_etudiants >= tmax) {
        printf("Impossible d'ajouter un étudiant : tableau plein.\n");
        return -1;
    }
    
    printf("Entrez le numéro de l'étudiant : ");
    scanf("%d", &numero);
    getchar();

    // Mise à jour des tableaux
    tEtu[*nb_etudiants] = numero;
    tStage[*nb_etudiants] = -1;  // Stage non attribué par défaut
    tNoteF[*nb_etudiants] = -1; // Pas de note par défaut
    (*nb_etudiants)++;

    // Ajout au fichier
    FILE *etudiants = fopen("fiche_etu.txt", "a");
    if (etudiants == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'fiche_etu.txt' pour l'écriture.\n");
        return -2;
    }
    fprintf(etudiants, "\n%d\t%d\t%d", numero, -1, -1);
    fclose(etudiants);

    printf("L'étudiant %d a été ajouté avec succès et enregistré dans le fichier.\n", numero);
    return 0;
}


/**
 * @brief Ajoute une offre de stage dans les tableaux et met à jour le fichier.
 * 
 * @param tRef Tableau des références de stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si le stage est pourvu.
 * @param tCand Tableau du nombre de candidatures par stage.
 * @param nbStages Pointeur vers le nombre de stages dans le tableau.
 * @param tmax Taille maximale des tableaux.
 * @return 0 si succès, -1 si la capacité maximale est atteinte, -2 si le fichier ne peut pas être ouvert.
 */
int ajouter_stage(int tRef[], int tDept[], int tPourvu[], int tCand[], int *nbStages, int tmax) {
    if (*nbStages >= tmax) {
        printf("Impossible d'ajouter une offre : tableau plein.\n");
        return -1;
    }

    int ref, dept;
    printf("Entrez la référence du stage : ");
    scanf("%d", &ref);
    printf("Entrez le département : ");
    scanf("%d", &dept);

    // Mise à jour des tableaux
    tRef[*nbStages] = ref;
    tDept[*nbStages] = dept;
    tPourvu[*nbStages] = 0; // Stage non pourvu par défaut
    tCand[*nbStages] = 0;  // Pas de candidatures au début
    (*nbStages)++;

    // Mise à jour du fichier
    FILE *stages = fopen("offre_stage.txt", "a");
    if (stages == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'offre_stage.txt' pour l'écriture.\n");
        return -2;
    }

    // Écrire dans le fichier selon le format demandé avec un tab entre la référence et le département
    fprintf(stages, "%d %d\n", ref, dept);  // Référence et département séparés par un tab
    fprintf(stages, "%d\n", 0);  // Pourvu = 0
    fprintf(stages, "%d\n", 0);  // Candidatures = 0
    fclose(stages);

    printf("Stage ajouté avec succès et enregistré dans le fichier.\n");
    return 0;
}


/**
 * @brief Supprime une offre de stage des tableaux et met à jour le fichier.
 * 
 * @param tRef Tableau des références de stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si le stage est pourvu.
 * @param tCand Tableau du nombre de candidatures par stage.
 * @param nbStages Pointeur vers le nombre de stages dans le tableau.
 * @param refStage Référence du stage à supprimer.
 * @return 0 si succès, -1 si le stage est introuvable, -2 si le fichier ne peut pas être ouvert.
 */
int supprimer_stage(int tRef[], int tDept[], int tPourvu[], int tCand[], int *nbStages, int refStage) {
    int found = -1;

    // Recherche du stage à supprimer
    for (int i = 0; i < *nbStages; i++) {
        if (tRef[i] == refStage) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Stage non trouvé.\n");
        return -1;
    }

    // Décalage des éléments restants
    for (int i = found; i < *nbStages - 1; i++) {
        tRef[i] = tRef[i + 1];
        tDept[i] = tDept[i + 1];
        tPourvu[i] = tPourvu[i + 1];
        tCand[i] = tCand[i + 1];
    }
    (*nbStages)--;

    // Réécriture du fichier
    FILE *stages = fopen("offre_stage.txt", "w");
    if (stages == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'offre_stage.txt' pour la réécriture.\n");
        return -2;
    }

    for (int i = 0; i < *nbStages; i++) {
        // Écriture des données sous le format demandé
        fprintf(stages, "%d %d\n", tRef[i], tDept[i]); // Référence du stage et département
        fprintf(stages, "%d\n", tPourvu[i]);            // Stage pourvu (0 ou 1)
        fprintf(stages, "%d\n", tCand[i]);              // Nombre de candidatures
    }
    fclose(stages);

    printf("Stage supprimé avec succès et le fichier a été mis à jour.\n");
    return 0;
}


/**
 * @brief Affiche tous les stages disponibles (non pourvus).
 * 
 * @details Lit les données des stages depuis le fichier "offre_stage.txt" et affiche les stages qui ne sont pas encore pourvus.
 */
void afficherStagesDisponibles() {
    FILE *fichier = fopen("offre_stage.txt", "r");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    int tRef, tDept, tPourvu, tCand;
    printf("Liste des stages disponibles :\n");

    while (fscanf(fichier, "%d\t%d\n%d\n%d\n", &tRef, &tDept, &tPourvu, &tCand) == 4) {
        if (tPourvu == 0) { // Affiche uniquement les stages non pourvus
            printf("Stage référence %d, Département %d, Nombre de candidatures : %d\n", tRef, tDept, tCand);
        }

        // Ignore les candidats listés dans le fichier (si présents)
        for (int i = 0; i < tCand; i++) {
            int tempEtu;
            fscanf(fichier, "%d\n", &tempEtu); // Lire mais ne rien faire avec les IDs étudiants
        }
    }

    fclose(fichier);
}


/**
 * @brief Permet à un étudiant de candidater à un stage.
 * 
 * Cette fonction vérifie plusieurs conditions avant d'ajouter un étudiant à la liste des candidats pour un stage :
 * - Le stage est-il déjà pourvu ?
 * - L'étudiant a-t-il déjà atteint la limite de candidatures ?
 * - Le stage a-t-il atteint le nombre maximal de candidatures ?
 * - L'étudiant a-t-il déjà candidaté pour ce stage ?
 * 
 * Si toutes les conditions sont remplies, l'étudiant est ajouté à la liste des candidatures pour ce stage.
 * Le fichier des stages est ensuite réécrit pour refléter la nouvelle candidature.
 * 
 * @param etuNum Le numéro de l'étudiant.
 * @param refStage La référence du stage auquel l'étudiant veut candidater.
 * @param tRef Tableau des références des stages.
 * @param tCand Tableau du nombre de candidatures par stage.
 * @param tPourvu Tableau indiquant si le stage est pourvu (1 pour pourvu, 0 pour non).
 * @param tCandEtu Tableau des étudiants ayant candidaté à chaque stage.
 * @param tDept Tableau des départements des stages.
 * @param nbStages Nombre total de stages disponibles.
 * 
 * @return Retourne -1 en cas de succès ou un code d'erreur si une condition échoue :
 *         -7 si le stage est déjà pourvu,
 *         -6 si l'étudiant a déjà atteint la limite de candidatures,
 *         -2 si le stage est déjà complet,
 *         -3 si l'étudiant a déjà candidaté pour ce stage,
 *         -1 si le stage est introuvable,
 *         -4 en cas d'erreur d'ouverture du fichier des stages.
 */
int candidater(int etuNum, int refStage, int tRef[], int tCand[], int tPourvu[], int tCandEtu[][3], int tDept[], int nbStages) {
    int index = -1;

    // Recherche de l'index correspondant à la référence du stage
    for (int i = 0; i < nbStages; i++) {
        if (tRef[i] == refStage) {
            index = i;
            break;
        }
    }

    // Si le stage est introuvable
    if (index == -1) {
        printf("Erreur : Stage avec la référence %d introuvable.\n", refStage);
        return -1; // Code d'erreur : stage introuvable
    }

    // Vérifie si le stage est pourvu
    if (tPourvu[index] == 1) {
        printf("Erreur : Le stage %d est déjà pourvu. Vous ne pouvez pas candidater.\n", refStage);
        return -7; // Code d'erreur : stage déjà pourvu
    }

    // Vérification du nombre de candidatures existantes pour l'étudiant
    int candidaturesExistantes = 0;
    for (int i = 0; i < nbStages; i++) {
        for (int j = 0; j < 3; j++) {
            if (tCandEtu[i][j] == etuNum) {
                candidaturesExistantes++;
            }
        }
    }

    // Limitation à 3 candidatures
    if (candidaturesExistantes >= 3) {
        return -6; // Limite de candidatures atteinte
    }

    // Vérifie si le stage est déjà complet
    if (tCand[index] >= 3) {
        printf("Erreur : Le stage %d a atteint le nombre maximal de candidatures.\n", refStage);
        return -2; // Code d'erreur : stage complet
    }

    // Vérifie si l'étudiant a déjà candidaté pour ce stage
    for (int j = 0; j < 3; j++) {
        if (tCandEtu[index][j] == etuNum) {
            printf("Erreur : L'étudiant %d a déjà candidaté pour le stage %d.\n", etuNum, refStage);
            return -3; // Code d'erreur : candidature déjà existante
        }
    }

    // Recherche d'une place libre pour l'étudiant
    for (int j = 0; j < 3; j++) {
        if (tCandEtu[index][j] == -1) { // Trouver une place libre
            tCandEtu[index][j] = etuNum; // Ajouter l'étudiant
            tCand[index]++;              // Incrémenter le compteur de candidatures

            // Si le stage a atteint le nombre maximal de candidatures (3), le marquer comme pourvu
            if (tCand[index] == 3) {
                tPourvu[index] = 1; // Marque le stage comme "pourvu"
            }

            // Réécriture complète du fichier des stages
            FILE *stage = fopen("offre_stage.txt", "w");
            if (stage == NULL) {
                printf("Erreur : Impossible d'ouvrir le fichier des stages.\n");
                return -4; // Code d'erreur : problème d'ouverture de fichier
            }

            // Écriture des données dans le fichier
            for (int i = 0; i < nbStages; i++) {
                fprintf(stage, "%d\t%d\n", tRef[i], tDept[i]); // Référence et département
                fprintf(stage, "%d\n", tPourvu[i] ? 1 : 0); // Statut pourvu ou non
                fprintf(stage, "%d\n", tCand[i]); // Nombre de candidatures

                // Liste des étudiants candidats
                if (tCand[i] != 0) {
                    for (int k = 0; k < 3; k++) {
                        if (tCandEtu[i][k] != -1) {
                            fprintf(stage, "%d\n", tCandEtu[i][k]);
                        }
                    }
                }
            }

            fclose(stage);

            printf("Succès : L'étudiant %d a candidaté pour le stage %d.\n", etuNum, refStage);
            return -1;
        }
    }

    // Si aucune place libre n'est trouvée
    printf("Erreur : Le stage %d est complet. Aucune place disponible.\n", refStage);
    return -5; // Code d'erreur : pas de place disponible
}



/**
 * @brief Attribue des notes à un étudiant pour son stage.
 * 
 * Cette fonction permet d'attribuer des notes à un étudiant pour son stage, en prenant en compte les notes de l'entreprise, 
 * du rapport et de la soutenance. Elle calcule ensuite la note finale en appliquant les coefficients définis.
 * Le fichier des étudiants est mis à jour avec les nouvelles notes et les mentions (si applicable).
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des références des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants dans le tableau.
 * @param mentions Tableau des mentions des étudiants (indiquant "Stage en cours" si le stage n'est pas terminé).
 * @param tmax Taille maximale des tableaux.
 */
void attribuerNotes(int tEtu[], int tStage[], int *nb_etudiants, char mentions[][20], int tmax) {
    float notesEntreprise[100], notesRapport[100], notesSoutenance[100], notesFinales[100];

    // Fichier ouvert en mode lecture pour charger les données
    FILE *etudiants = fopen("fiche_etu.txt", "r");
    if (etudiants == NULL) {
        printf("Erreur lors de l'ouverture du fichier en lecture.\n");
        return;
    }

    // Chargement des données existantes
    int tempEtu[100], tempStage[100];
    float tempNote[100];
    int lignes = 0;

    while (fscanf(etudiants, "%d %d %f", &tempEtu[lignes], &tempStage[lignes], &tempNote[lignes]) != EOF) {
        if (tempNote[lignes] == -1) {
            for (int j = 0; j < 20; j++) {
                mentions[lignes][j] = 0;  // Effacer l'ancien contenu
            }
            // "Stage en cours" ajouté caractère par caractère
            char texte[] = "Stage en cours";
            for (int j = 0; texte[j] != '\0'; j++) {
                mentions[lignes][j] = texte[j];
            }
        }
        lignes++;
    }
    fclose(etudiants);

    // Demander le numéro de l'étudiant à modifier
    int numero, trouve = 0;
    printf("Entrez le numéro de l'étudiant à attribuer des notes : ");
    scanf("%d", &numero);

    // Recherche de l'étudiant dans le tableau
    int index = fRechercher(numero, tEtu, *nb_etudiants, &trouve);
    if (!trouve) {
        printf("L'étudiant avec le numéro %d n'a pas été trouvé.\n", numero);
        return;
    }

    printf("Étudiant numéro %d, Stage référence %d\n", tEtu[index], tStage[index]);

    // Vérification si le stage est valide
    if (tStage[index] == -1) {
        printf("L'étudiant %d est toujours en stage, aucune note ne peut être attribuée.\n", tEtu[index]);
        return;
    }

    // Attribution des nouvelles notes
    printf("Attribuer une note pour cet étudiant :\n");
    printf("Note d'entreprise (coefficient 2) : ");
    scanf("%f", &notesEntreprise[index]);

    printf("Note du rapport (coefficient 1) : ");
    scanf("%f", &notesRapport[index]);

    printf("Note de soutenance (coefficient 1) : ");
    scanf("%f", &notesSoutenance[index]);

    // Calcul de la note finale
    notesFinales[index] = ((notesEntreprise[index] * 2) + notesRapport[index] + notesSoutenance[index]) / 4.0;
    tempNote[index] = notesFinales[index];

    // Suppression de l'ancienne mention
    for (int j = 0; j < 20; j++) {
        mentions[index][j] = 0;  // Réinitialisation à vide
    }

    // Réécriture complète du fichier
    etudiants = fopen("fiche_etu.txt", "w");
    if (etudiants == NULL) {
        printf("Erreur lors de l'ouverture du fichier en écriture.\n");
        return;
    }

    // Mise à jour des données en mémoire et écriture dans le fichier
    for (int i = 0; i < lignes; i++) {
        if (tempNote[i] == -1) {
            fprintf(etudiants, "%d %d -1\n", tempEtu[i], tempStage[i]);
        } else {
            fprintf(etudiants, "%d %d %.2f\n", tempEtu[i], tempStage[i], tempNote[i]);
        }
    }

    fclose(etudiants);

    printf("Note finale pour l'étudiant %d : %.2f\n", tEtu[index], notesFinales[index]);
    printf("Les nouvelles informations ont été mises à jour dans 'fiche_etu.txt'.\n");
}

/**
 * @brief Affiche les notes des étudiants par ordre décroissant.
 * 
 * Cette fonction trie les étudiants par leur note finale (de la plus élevée à la plus basse) et affiche la liste triée.
 * Les étudiants avec la mention "Stage en cours" sont affichés à la fin de la liste.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des références des stages des étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nb_etudiants Nombre d'étudiants dans le tableau.
 * @param mentions Tableau des mentions des étudiants (notamment "Stage en cours").
 */
void afficherNotesParOrdreDecroissant(int tEtu[], int tStage[], float tNoteF[], int *nb_etudiants, char mentions[][20]) {
    // Tri des étudiants par leur note finale (ordre décroissant), en plaçant les mentions "Stage en cours" à la fin
    for (int i = 0; i < *nb_etudiants - 1; i++) {
        for (int j = i + 1; j < *nb_etudiants; j++) {
            int mentionIEnCours = (mentions[i][0] == 'S'); // Vérifie si mention[i] commence par "Stage"
            int mentionJEnCours = (mentions[j][0] == 'S'); // Vérifie si mention[j] commence par "Stage"

            // Condition de tri : note décroissante ou "Stage en cours" à la fin
            if ((!mentionIEnCours && (tNoteF[i] < tNoteF[j])) || (mentionJEnCours && !mentionIEnCours)) {
                // Échange des données
                int tempEtu = tEtu[i];
                int tempStage = tStage[i];
                float tempNote = tNoteF[i];
                char tempMention[20];

                // Copier caractère par caractère dans tempMention
                for (int k = 0; k < 20; k++) {
                    tempMention[k] = mentions[i][k];
                }

                // Échange des valeurs
                tEtu[i] = tEtu[j];
                tStage[i] = tStage[j];
                tNoteF[i] = tNoteF[j];

                // Copier caractère par caractère dans mentions[i]
                for (int k = 0; k < 20; k++) {
                    mentions[i][k] = mentions[j][k];
                }

                // Copier de tempMention dans mentions[j]
                for (int k = 0; k < 20; k++) {
                    mentions[j][k] = tempMention[k];
                }
            }
        }
    }

    // Affichage des résultats
    printf("=== Liste des étudiants par ordre décroissant des notes ===\n");
    printf("Numéro\tNote Finale\n");

    // Afficher les étudiants ayant une note finale valide (non "Stage en cours")
    for (int i = 0; i < *nb_etudiants; i++) {
        if (mentions[i][0] != 'S') { // Vérifie si mention[i] n'est pas "Stage en cours"
            printf("%d\t%.2f\n", tEtu[i], tNoteF[i]);
        }
    }

    // Afficher les étudiants avec "Stage en cours" à la fin
    printf("\n=== Étudiants en stage (Stage en cours) ===\n");
    for (int i = 0; i < *nb_etudiants; i++) {
        if (mentions[i][0] == 'S') { // Vérifie si mention[i] est "Stage en cours"
            printf("%d\t%d\tStage en cours\n", tEtu[i], tStage[i]);
        }
    }
}


/**
 * @brief Affecte un stage à un étudiant.
 * 
 * Cette fonction permet d'affecter un stage à un étudiant en vérifiant que l'étudiant n'a pas déjà un stage. 
 * Si l'étudiant est éligible, la fonction met à jour le fichier des étudiants et des stages pour refléter cette affectation.
 * Elle supprime également toutes les candidatures précédentes de l'étudiant pour ce stage et marque ce dernier comme pourvu.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des références des stages.
 * @param nb_etudiants Nombre d'étudiants dans le tableau.
 * @param tmax Taille maximale des tableaux.
 * @param refStage Référence du stage à affecter.
 * @param numero Numéro de l'étudiant à affecter au stage.
 */
void affecter_stage(int tEtu[], int tStage[], int nb_etudiants, int tmax, int refStage, int numero) {
    // Ouverture du fichier des étudiants
    FILE *etudiants = fopen("fiche_etu.txt", "r+");
    if (etudiants == NULL) {
        printf("Erreur lors de l'ouverture du fichier 'fiche_etu.txt'.\n");
        return;
    }

    // Lecture et mise en mémoire des données des étudiants
    int tempEtu[100], tempStage[100];
    float tempNote[100];
    int lignes = 0, trouve = 0;

    while (fscanf(etudiants, "%d %d %f", &tempEtu[lignes], &tempStage[lignes], &tempNote[lignes]) != EOF) {
        lignes++;
    }

    // Recherche de l'étudiant et modification de son stage
    for (int i = 0; i < lignes; i++) {
        if (tempEtu[i] == numero) {
            if (tempStage[i] == -1) {
                tempStage[i] = refStage; // Mise à jour de la référence du stage
                trouve = 1;
                break;
            } else {
                printf("L'étudiant %d a déjà un stage attribué.\n", numero);
                fclose(etudiants);
                return; // Étudiant déjà affecté
            }
        }
    }

    if (!trouve) {
        printf("Étudiant %d non trouvé dans 'fiche_etu.txt'.\n", numero);
        fclose(etudiants);
        return;
    }

    // Mise à jour du fichier des étudiants
    fclose(etudiants); 
    etudiants = fopen("fiche_etu.txt", "w");
    if (etudiants == NULL) {
        printf("Erreur lors de l'ouverture du fichier 'fiche_etu.txt' en écriture.\n");
        return;
    }

    for (int i = 0; i < lignes; i++) {
        fprintf(etudiants, "%d %d %.2f\n", tempEtu[i], tempStage[i], tempNote[i]);
    }
    fclose(etudiants);

    // Mise à jour du fichier des stages
    FILE *stages = fopen("offre_stage.txt", "r+");
    if (stages == NULL) {
        printf("Erreur lors de l'ouverture du fichier 'offre_stage.txt'.\n");
        return;
    }

    // Lecture et mise en mémoire des données des stages
    int tempRef[100], tempDept[100], tempPourvu[100], tempCand[100];
    int tempCandEtu[100][3];

    // Initialisation explicite de tempCandEtu
    for (int i = 0; i < tmax; i++) {
        for (int j = 0; j < 3; j++) {
            tempCandEtu[i][j] = -1;
        }
    }

    int lignesStages = 0;

    while (fscanf(stages, "%d\t%d\n%d\n%d\n", &tempRef[lignesStages], &tempDept[lignesStages], 
                  &tempPourvu[lignesStages], &tempCand[lignesStages]) != EOF) {
        for (int j = 0; j < tempCand[lignesStages]; j++) {
            fscanf(stages, "%d\n", &tempCandEtu[lignesStages][j]);
        }
        lignesStages++;
    }

    // Suppression de toutes les candidatures de l'étudiant
    for (int i = 0; i < lignesStages; i++) {
        for (int j = 0; j < tempCand[i]; j++) {
            if (tempCandEtu[i][j] == numero) {
                // Supprime la candidature de l'étudiant dans le stage
                tempCandEtu[i][j] = -1;
                // Réduire le nombre de candidatures pour ce stage
                tempCand[i]--;
            }
        }
    }

    // Suppression de toutes les candidatures pour le stage affecté
    for (int i = 0; i < lignesStages; i++) {
        if (tempRef[i] == refStage) {
            // Vide toutes les candidatures pour ce stage
            for (int j = 0; j < 3; j++) {
                tempCandEtu[i][j] = -1;
            }
            tempCand[i] = 0; // Réinitialise le nombre de candidats pour ce stage
            tempPourvu[i] = 1; // Marque le stage comme "pourvu"
            break;
        }
    }

    // Mise à jour du fichier des stages
    fclose(stages);
    stages = fopen("offre_stage.txt", "w");
    if (stages == NULL) {
        printf("Erreur lors de l'ouverture du fichier 'offre_stage.txt' en écriture.\n");
        return;
    }

    for (int i = 0; i < lignesStages; i++) {
        fprintf(stages, "%d\t%d\n%d\n%d\n", tempRef[i], tempDept[i], tempPourvu[i], tempCand[i]);

        // Réécriture des candidatures
        for (int j = 0; j < 3; j++) {
            if (tempCandEtu[i][j] != -1) {
                fprintf(stages, "%d\n", tempCandEtu[i][j]);
            }
        }
    }
    fclose(stages);

    printf("Stage %d affecté à l'étudiant %d avec succès. Toutes les candidatures précédentes ont été supprimées.\n", refStage, numero);
}



/**
 * @brief Affiche la liste des stages disponibles.
 * 
 * Cette fonction affiche les détails des stages disponibles, y compris leur référence, département,
 * état de pourvoi et nombre de candidatures.
 * 
 * @param tRef Tableau des références de stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si le stage est pourvu (1) ou non (0).
 * @param tCand Tableau des candidatures pour chaque stage.
 * @param nbStages Nombre total de stages.
 */
void afficherStages(int tRef[], int tDept[], int tPourvu[],int tCand[], int nbStages) {
    printf("Liste des stages disponibles :\n");
    for (int i = 0; i < nbStages; i++) {
        printf("Référence : %d, Département : %d, Pourvu à: %d ,Candidatures : %d\n", tRef[i], tDept[i], tPourvu[i],tCand[i]);
    }
}


/**
 * @brief Affiche les informations des étudiants et leurs candidatures.
 * 
 * Cette fonction affiche soit la liste complète des étudiants, soit les informations d'un étudiant particulier
 * en fonction du numéro fourni. Si le numéro de l'étudiant est trouvé, ses informations sont affichées.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param nbEtu Nombre d'étudiants.
 * @param num Numéro de l'étudiant à rechercher. Si égal à -1, affiche tous les étudiants.
 */
void afficherEleves(int tEtu[], int tStage[], float tNoteF[], int *nb_etudiants, int num) {
    int trouve = 0;

    printf("=== Affichage des étudiants ===\n");

    if (num == -1) {
        printf("Liste de tous les étudiants :\n");
        printf("Numéro\tStage\tNote Finale\n");
        for (int i = 0; i < *nb_etudiants; i++) {
            printf("%d\t%d\t%f\n", tEtu[i], tStage[i], tNoteF[i]);
        }
    } else {
        for (int i = 0; i < *nb_etudiants; i++) {
            if (tEtu[i] == num) {
                printf("Étudiant trouvé :\n");
                printf("Numéro : %d\n", tEtu[i]);
                printf("Stage : %d\n", tStage[i]);
                printf("Note Finale : %f\n", tNoteF[i]);
                trouve = 1;
                break;
            }
        }

        if (!trouve) {
            printf("Aucun étudiant avec le numéro %d trouvé.\n", num);
        }
    }
}


/**
 * @brief Affiche les stages non pourvus.
 * 
 * Cette fonction affiche les stages qui n'ont pas encore été pourvus, en indiquant leur référence et leur département.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu (1) ou non (0).
 * @param nb_stages Nombre total de stages.
 */
void afficherStagesNonPourvus(int tRef[], int tDept[], int tPourvu[], int nb_stages) {
    printf("\nStages non pourvus :\n");
    int compteur = 0;

    for (int i = 0; i < nb_stages; i++) {
        if (tPourvu[i] == 0) {
            printf("Référence du stage : %d, Département : %d\n", tRef[i], tDept[i]);
            compteur++;
        }
    }

    if (compteur == 0) {
        printf("Aucun stage disponible.\n");
    }
}


/**
 * @brief Affiche les candidatures d'un étudiant spécifique.
 * 
 * Cette fonction affiche les stages auxquels un étudiant a candidaté ainsi que leur état (pourvu ou non).
 * Elle affiche également le stage affecté si un stage a été pourvu à l'étudiant.
 * 
 * @param etuNum Numéro de l'étudiant.
 * @param tCandEtu Tableau des candidatures des étudiants aux stages.
 * @param tRef Tableau des références des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param nb_stages Nombre total de stages.
 */
void afficherCandidaturesEtudiant(int etuNum, int tCandEtu[][3], int tRef[], int tPourvu[], int nb_stages) {
    printf("\nCandidatures de l'étudiant %d :\n", etuNum);
    int trouve = 0;

    for (int i = 0; i < nb_stages; i++) {
        // Affiche les stages auxquels l'étudiant a candidaté
        for (int j = 0; j < 3; j++) {
            if (tCandEtu[i][j] == etuNum) {
                printf("- Stage référence : %d (Pourvu : %s)\n", tRef[i], tPourvu[i] ? "Oui" : "Non");
                trouve = 1;
                break;
            }
        }
    }

    if (!trouve) {
        printf("Aucune candidature trouvée pour cet étudiant.\n");
    }

    // Affiche le stage affecté si pourvu
    for (int i = 0; i < nb_stages; i++) {
        if (tPourvu[i] == 1 && tCandEtu[i][0] == etuNum) {
            printf("\nStage affecté : Référence %d\n", tRef[i]);
            return;
        }
    }
}


/**
 * @brief Affiche les stages par département.
 * 
 * Cette fonction affiche les stages d'un département spécifique, en indiquant si ces stages sont pourvus ou non.
 * 
 * @param numDept Numéro du département.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param nb_stages Nombre total de stages.
 */
void afficherStagesParDepartement(int numDept, int tRef[], int tDept[], int tPourvu[], int nb_stages) {
    printf("\nStages pour le département %d :\n", numDept);
    int compteur = 0;

    for (int i = 0; i < nb_stages; i++) {
        if (tDept[i] == numDept) {
            printf("- Référence : %d (Pourvu : %s)\n", tRef[i], tPourvu[i] ? "Oui" : "Non");
            compteur++;
        }
    }

    if (compteur == 0) {
        printf("Aucun stage trouvé pour ce département.\n");
    }
}


/**
 * @brief Affiche les stages pourvus avec les étudiants affectés.
 * 
 * Cette fonction affiche les stages qui ont été pourvus, en indiquant la référence du stage,
 * le département et l'étudiant affecté.
 * 
 * @param tRef Tableau des références des stages.
 * @param tEtu Tableau des numéros des étudiants affectés.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param nb_stages Nombre total de stages.
 * @param nb_etudiants Nombre total d'étudiants.
 */
void afficherStagesPourvus(int tRef[], int tEtu[], int tDept[], int tPourvu[], int nb_stages, int nb_etudiants) {
    printf("\n===== Stages pourvus =====\n");
    for (int i = 0; i < nb_stages; i++) {
        if (tPourvu[i] == 1) {  // Stage pourvu
            printf("Stage référence %d, Département %d : Étudiant %d\n", tRef[i], tDept[i], tEtu[i]);
        }
    }
}


/**
 * @brief Affiche les stages non pourvus pour un responsable.
 * 
 * Cette fonction affiche les stages non pourvus, avec leur référence et département.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param nb_stages Nombre total de stages.
 */
void afficherStagesNonPourvusResp(int tRef[], int tDept[], int tPourvu[], int nb_stages) {
    printf("\n===== Stages non pourvus =====\n");
    for (int i = 0; i < nb_stages; i++) {
        if (tPourvu[i] == 0) {  // Stage non pourvu
            printf("Stage référence %d, Département %d\n", tRef[i], tDept[i]);
        }
    }
}


/**
 * @brief Affiche la liste des étudiants sans stage.
 * 
 * Cette fonction affiche les étudiants qui n'ont pas encore de stage attribué.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 */
void afficherEtudiantsSansStage(int tEtu[], int tStage[], int nb_etudiants) {
    printf("\n===== Étudiants sans stage =====\n");
    for (int i = 0; i < nb_etudiants; i++) {
        if (tStage[i] == -1) {  // Étudiant sans stage affecté
            printf("Étudiant %d\n", tEtu[i]);
        }
    }
}


/**
 * @brief Affiche les informations d'un stage particulier.
 * 
 * Cette fonction permet de rechercher et d'afficher les informations d'un stage basé sur sa référence.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param nb_stages Nombre total de stages.
 */
void afficherInfoStage(int tRef[], int tDept[], int tPourvu[], int nb_stages) {
    int refStage;
    printf("\nEntrez la référence du stage pour afficher les informations : ");
    scanf("%d", &refStage);

    int trouve = 0;
    for (int i = 0; i < nb_stages; i++) {
        if (tRef[i] == refStage) {
            printf("Stage référence %d, Département %d, Pourvu : %d\n", tRef[i], tDept[i], tPourvu[i]);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Stage avec la référence %d non trouvé.\n", refStage);
    }
}


/**
 * @brief Recherche des stages selon un critère (numéro de stage ou département).
 * 
 * Cette fonction permet de rechercher un stage par son numéro ou son département et affiche les résultats.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param nb_stages Nombre total de stages.
 */
void rechercherStages(int tRef[], int tDept[], int tPourvu[],int nb_stages) {
    int critere, valeur;
    printf("\nRecherche de stage par critère\n");
    printf("1. Recherche par numéro de stage\n");
    printf("2. Recherche par département\n");
    printf("Choisissez un critère (1 ou 2) : ");
    scanf("%d", &critere);

    if (critere == 1) {
        printf("Entrez le numéro de stage à rechercher : ");
        scanf("%d", &valeur);
        printf("\nRésultats de la recherche pour le stage %d :\n", valeur);
        for (int i = 0; i < nb_stages; i++) {
            if (tRef[i] == valeur) {
                printf("Stage référence %d, Département %d, Pourvu : %d\n", tRef[i], tDept[i], tPourvu[i]);
            }
        }
    } else if (critere == 2) {
        printf("Entrez le numéro du département à rechercher : ");
        scanf("%d", &valeur);
        printf("\nRésultats de la recherche pour le département %d :\n", valeur);
        for (int i = 0; i < nb_stages; i++) {
            if (tDept[i] == valeur) {
                printf("Stage référence %d, Département %d, Pourvu : %d\n", tRef[i], tDept[i], tPourvu[i]);
            }
        }
    } else {
        printf("Choix invalide.\n");
    }
}


/**
 * @brief Sauvegarde les données des étudiants dans un fichier.
 * 
 * Cette fonction sauvegarde les informations des étudiants (numéro, stage attribué, note finale) dans un fichier texte.
 * 
 * @param etudiants Tableau des structures représentant les étudiants.
 * @param nb_etudiants Nombre total d'étudiants.
 */
void sauvegarder_etudiants(int tEtu[], int tStage[], float tNoteF[], int *nb_etudiants) {
    FILE *fichier = fopen("fiche_etu.txt", "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'fiche_etu.txt'.\n");
        return;
    }

    for (int i = 0; i < *nb_etudiants; i++) {
        fprintf(fichier, "\n%d" , tEtu[i]);
        fprintf(fichier, "%d", tStage[i]);
        fprintf(fichier, "%.2f", tNoteF[i]);
    }

    fclose(fichier);
    printf("Données des étudiants sauvegardées avec succès.\n");
}



/**
 * @brief Sauvegarde les données des stages dans un fichier.
 * 
 * Cette fonction sauvegarde les informations des stages (référence, département, état de pourvoi, nombre de candidatures) dans un fichier texte.
 * 
 * @param stages Tableau des structures représentant les stages.
 * @param nb_stages Nombre total de stages.
 */
void sauvegarder_stages(int tRef[], int tDept[], int tPourvu[], int tCand[], int tCandEtu[][3], int nbStages) {
    FILE *fichier = fopen("offre_stage.txt", "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'offre_stage.txt'.\n");
        return;
    }

    for (int i = 0; i < nbStages; i++) {
        // Écriture des données principales du stage
        fprintf(fichier, "%d\t%d\n", tRef[i], tDept[i]);
        fprintf(fichier, "%d\n", tPourvu[i]);
        fprintf(fichier, "%d\n", tCand[i]);

        // Écriture des étudiants candidats
        for (int j = 0; j < 3; j++) {
            if (tCandEtu[i][j] != -1) { // Évite les cases vides
                fprintf(fichier, "%d\n", tCandEtu[i][j]);
            }
        }
    }

    fclose(fichier);
    printf("Données des stages sauvegardées avec succès.\n");
}


/**
 * @brief Menu principal pour la gestion des étudiants par le jury.
 * 
 * Cette fonction permet au jury de gérer les étudiants, ajouter/supprimer un étudiant, attribuer des notes, afficher les notes, etc.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param tRef Tableau des références des stages.
 * @param nb_etudiants Nombre total d'étudiants.
 * @param nb_stages Nombre total de stages.
 * @param mentions Tableau des mentions des étudiants.
 * @param tmax Taille maximale des tableaux.
 */
void menu_jury(int tEtu[], int tStage[], float tNoteF[], int tRef[], int *nb_etudiants, int nb_stages, char mentions[][20], int tmax) {
    int choix;

    do {
        printf("\n===== MENU JURY =====\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Supprimer un étudiant\n");
        printf("3. Rechercher un eleve\n");
        printf("4. Attribuer les notes\n");
        printf("5. Affiche les notes\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_etudiant(tEtu, tStage, tNoteF, nb_etudiants, tmax);
                break;

            case 2: {
                if (nb_etudiants > 0) {
                    int numero;
                    printf("Entrez le numéro de l'étudiant à supprimer : ");
                    scanf("%d", &numero);
                    supprimerEtu(tEtu, tStage, tNoteF, nb_etudiants, numero);
                } else {
                    printf("Aucun étudiant à supprimer.\n");
                }
                break;
            }

            case 3: {
                int num;
                printf("Entrez le numéro de l'étudiant à afficher : ");
                scanf("%d", &num);
                afficherEleves(tEtu, tStage, tNoteF, nb_etudiants, num);
                break;
            }

            case 4:
                attribuerNotes(tEtu, tStage, nb_etudiants, mentions,tmax);
                break;

            case 5:
                afficherNotesParOrdreDecroissant(tEtu, tStage, tNoteF, nb_etudiants, mentions);
                break;

            case 6:
                printf("Retour au menu principal.\n");
                break;

            default:
                printf("Choix invalide. Essayez de nouveau.\n");
                break;
        }
    } while (choix != 6);
}


/**
 * @brief Suite du menu pour un étudiant particulier.
 * 
 * Cette fonction affiche le menu pour un étudiant spécifique, permettant de consulter ses candidatures et de gérer ses choix de stage.
 * 
 * @param numero Numéro de l'étudiant.
 * @param tEtu Tableau des numéros des étudiants.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 */
void suite_etudiant(int numero, int tEtu[], int tRef[], int tDept[], int tPourvu[], int tCandEtu[][3], int nb_etudiants, int nb_stages) {
    int choix;
    int index = -1;

    // Recherche de l'étudiant dans le tableau tEtu[]
    for (int i = 0; i < nb_etudiants; i++) {
        if (tEtu[i] == numero) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Erreur : Étudiant avec le numéro %d non trouvé.\n", numero);
        return;
    }

    do {
        printf("\n===== SUITE MENU POUR L'ÉTUDIANT %d =====\n", numero);
        printf("1. Afficher tous les stages non pourvus\n");
        printf("2. Afficher toutes mes candidatures\n");
        printf("3. Afficher mes candidatures (stage affecté)\n");
        printf("4. Afficher les stages selon un département choisi\n");
        printf("5. Retour au menu précédent\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Affichage des stages non pourvus
                printf("\nStages non pourvus :\n");
                for (int i = 0; i < nb_stages; i++) {
                    if (tPourvu[i] == 0) {  // 0 signifie stage non pourvu
                        printf("Stage référence : %d, Département : %d\n", tRef[i], tDept[i]);
                    }
                }
                break;

            case 2:
                // Affichage des candidatures de l'étudiant
                printf("\nMes candidatures :\n");
                int trouveCandidature = 0;
                for (int i = 0; i < nb_stages; i++) {
                    if (tCandEtu[i][0] == numero) {
                        printf("Candidature pour le stage référence : %d, Département : %d\n", tRef[i], tDept[i]);
                        trouveCandidature = 1;
                    }
                }
                if (!trouveCandidature) {
                    printf("Vous n'avez pas encore de candidatures.\n");
                }
                break;

            case 3:
                // Affichage du stage affecté (si l'étudiant a un stage affecté)
                if (tCandEtu[index][1] != -1) {  // Si un stage est affecté
                    printf("\nVous avez été affecté au stage référence : %d, Département : %d\n", tCandEtu[index][1], tDept[tCandEtu[index][1]]);
                } else {
                    printf("Vous n'avez pas encore de stage affecté.\n");
                }
                break;

            case 4:
                // Demander à l'étudiant de renseigner le département
                printf("\nEntrez le numéro du département pour lequel vous souhaitez voir les stages : ");
                int departementChoisi;
                scanf("%d", &departementChoisi);

                // Affichage des stages selon le département choisi
                printf("\nStages du département %d :\n", departementChoisi);
                int trouveStage = 0;
                for (int i = 0; i < nb_stages; i++) {
                    if (tDept[i] == departementChoisi) {
                        printf("Stage référence : %d\n", tRef[i]);
                        trouveStage = 1;
                    }
                }
                if (!trouveStage) {
                    printf("Aucun stage trouvé pour le département %d.\n", departementChoisi);
                }
                break;

            case 5:
                // Retour au menu précédent
                printf("Retour au menu précédent...\n");
                break;

            default:
                printf("Choix invalide. Essayez de nouveau.\n");
                break;
        }
    } while (choix != 5);
}


/**
 * @brief Menu principal pour un étudiant.
 * 
 * Cette fonction affiche le menu principal pour un étudiant, lui permettant de consulter les stages disponibles, de candidater pour un stage, etc.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tNoteF Tableau des notes finales des étudiants.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCand Tableau des candidatures des étudiants.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 */
void menu_etudiant(int tEtu[], int tStage[], float tNoteF[], int tRef[], int tDept[], int tPourvu[], int tCand[], int tCandEtu[][3], int nb_etudiants, int nb_stages) {
    int choix;
    int numero = -1; // Numéro de l'étudiant
    int trouve, index;

    do {
        // Si le numéro de l'étudiant n'a pas encore été renseigné, le demander
        if (numero == -1) {
            printf("Entrez votre numéro étudiant : ");
            scanf("%d", &numero);
        }

        printf("\n===== MENU ETUDIANT =====\n");
        printf("1. Afficher les stages disponibles\n");
        printf("2. Candidater pour un stage\n");
        printf("3. Voir mes Affichages\n");
        printf("4. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherStagesDisponibles();
                break;

            case 2:
                // Vérification de l'étudiant et candidature
                index = fRechercher(numero, tEtu, nb_etudiants, &trouve);
                if (!trouve) {
                    printf("Erreur : Étudiant avec le numéro %d non trouvé.\n", numero);
                    break;
                }

                // Demander la référence du stage et candidater
                int refStage;
                printf("Entrez la référence du stage : ");
                scanf("%d", &refStage);

                // Vérifier si le stage existe
                int stageIndex = -1;
                for (int i = 0; i < nb_stages; i++) {
                    if (tRef[i] == refStage) {
                        stageIndex = i;
                        break;
                    }
                }

                if (stageIndex == -1) {
                    printf("Erreur : Stage avec la référence %d non trouvé.\n", refStage);
                    break;
                }

                if (stageIndex == -2) {
                    printf("Erreur : L'étudiant %d a déjà postulé à 3 stages.\n", numero);
                    break;
                }

                // Appel de la fonction de candidature
                int resultat = candidater(numero, refStage, tRef, tCand, tPourvu, tCandEtu, tDept, nb_stages);
            case 3:
                suite_etudiant(numero, tEtu, tRef, tDept, tPourvu, tCandEtu, nb_etudiants, nb_stages);
                break;

            case 4:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide. Essayez de nouveau.\n");
                break;
        }
    } while (choix != 4);
}


/**
 * @brief Affiche le menu des responsabilités pour le responsable des stages.
 * 
 * Ce menu permet au responsable des stages d'effectuer diverses actions telles que l'affichage des stages pourvus,
 * non pourvus, des étudiants sans stage, des informations sur un stage spécifique, et une recherche de stage.
 * 
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 */
void suite_responsable(int tEtu[], int tStage[], int tRef[], int tDept[], int tPourvu[], int tCandEtu[][3], int nb_etudiants, int nb_stages) {
    int choix;

    do {
        printf("\n===== MENU RESPONSABLE DES STAGES =====\n");
        printf("1. Afficher tous les stages pourvus avec les étudiants affectés\n");
        printf("2. Afficher tous les stages non pourvus\n");
        printf("3. Afficher la liste des étudiants sans stage\n");
        printf("4. Afficher les informations concernant un stage\n");
        printf("5. Recherche de stage selon un critère\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherStagesPourvus(tRef, tEtu, tDept, tPourvu, nb_stages, nb_etudiants);
                break;
            case 2:
                afficherStagesNonPourvusResp(tRef, tDept, tPourvu, nb_stages);
                break;
            case 3:
                afficherEtudiantsSansStage(tEtu, tStage, nb_etudiants);
                break;
            case 4:
                afficherInfoStage(tRef, tDept, tPourvu, nb_stages);
                break;
            case 5:
                rechercherStages(tRef, tDept, tPourvu,nb_stages);
                break;
            case 6:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Essayez de nouveau.\n");
                break;
        }
    } while (choix != 6);
}


/**
 * @brief Affiche le menu principal pour le responsable des stages.
 * 
 * Ce menu permet au responsable des stages d'ajouter ou de supprimer une offre de stage, d'affecter un stage à un étudiant,
 * d'afficher les stages disponibles, et de consulter ses affichages.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCand Tableau des candidatures des étudiants.
 * @param nbStages Pointeur vers le nombre de stages.
 * @param tEtu Tableau des numéros des étudiants.
 * @param tStage Tableau des stages attribués aux étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param tmax Taille maximale des tableaux.
 * @param tCandEtu Tableau des candidatures des étudiants.
 */
void menu_responsable(int tRef[], int tDept[], int tPourvu[], int tCand[], int *nbStages, int tEtu[], int tStage[], int nb_etudiants, int tmax, int tCandEtu[][3]) {
    int choix;

    do {
        printf("\n===== MENU RESPONSABLE DES STAGES =====\n");
        printf("1. Ajouter une offre de stage\n");
        printf("2. Supprimer une offre de stage\n");
        printf("3. Affecter un stage à un étudiant\n");
        printf("4. Afficher les stages disponibles\n");
        printf("5. Voir mes affichages\n");
        printf("6. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_stage(tRef, tDept, tPourvu, tCand, nbStages, tmax);
                break;

            case 2:
                if (*nbStages > 0) {
                    int ref;
                    printf("Entrez la référence du stage à supprimer : ");
                    scanf("%d", &ref);
                    supprimer_stage(tRef, tDept, tPourvu, tCand, nbStages, ref);
                } else {
                    printf("Aucun stage à supprimer.\n");
                }
                break;

            case 3:
                if (nb_etudiants > 0) {
                    int etuNum, refStage,numero;
                    printf("Entrez le numéro de l'étudiant : ");
                    scanf("%d", &etuNum);
                    printf("Entrez la référence du stage à affecter : ");
                    scanf("%d", &refStage);
                    affecter_stage(tEtu,tStage,nb_etudiants,tmax,refStage,etuNum);
                } else {
                    printf("Aucun étudiant à affecter.\n");
                }
                break;

            case 4:
                afficherStages(tRef, tDept, tPourvu, tCand, *nbStages);
                break;

            case 5:
                suite_responsable(tEtu,tStage,tRef,tDept,tPourvu,tCandEtu,nb_etudiants, *nbStages);
                break;
            case 6:
                printf("Retour au menu principal.\n");
                break;

            default:
                printf("Choix invalide. Essayez de nouveau.\n");
                break;
        }
    } while (choix != 6);
}


/**
 * @brief Affiche le menu principal de l'application.
 * 
 * Ce menu permet à l'utilisateur de choisir entre différents sous-menus : Jury, Étudiant, Responsable des Stages,
 * ou de quitter l'application. Il charge également les données depuis les fichiers et initialise les variables nécessaires.
 * 
 * @param tRef Tableau des références des stages.
 * @param tDept Tableau des départements des stages.
 * @param tPourvu Tableau indiquant si un stage est pourvu.
 * @param tCand Tableau des candidatures des étudiants.
 * @param tCandEtu Tableau des candidatures des étudiants.
 * @param mentions Tableau des mentions des étudiants.
 * @param nb_etudiants Nombre d'étudiants.
 * @param nb_stages Nombre de stages.
 * @param tmax Taille maximale des tableaux.
 */
void menu_principal() {
    int choix;
    int tmax = 100;
    int nb_etudiants, nb_stages;
    int tEtu[100], tStage[100];
    float tNoteF[100];
    int tRef[100], tDept[100], tPourvu[100], tCand[100];
    int tCandEtu[100][3];
    char mentions[100][20];


    // Charger les données depuis les fichiers
    nb_etudiants = fChargementEtu(tEtu, tStage, tNoteF, tmax);
    nb_stages = fChargementStage(tRef, tDept, tPourvu, tCand, tCandEtu, tmax);


    // Initialiser les informations des stages
    for (int i = 0; i < nb_stages; i++) {
        tCand[i] = 0;
        tPourvu[i] = 0;
        for (int j = 0; j < 3; j++) {
            tCandEtu[i][j] = -1;
        }
    }
    printf("nb d'élève chargé %d", nb_etudiants);

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Accéder au menu Jury\n");
        printf("2. Accéder au menu Étudiant\n");
        printf("3. Accéder au menu Responsable des Stages\n");
        printf("4. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                menu_jury(tEtu, tStage, tNoteF, tRef, &nb_etudiants, nb_stages, mentions, tmax);
                break;

            case 2:
                menu_etudiant(tEtu, tStage, tNoteF, tRef, tDept, tPourvu, tCand, tCandEtu, nb_etudiants, nb_stages);
                break;

            case 3:
                printf("nb d'élève chargé %d", nb_etudiants);
                break;

            case 4: 
                sauvegarder_etudiants(tEtu,tStage,tNoteF,&nb_etudiants);
                sauvegarder_stages(tRef,tDept,tPourvu,tCand,tCandEtu,nb_stages);
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide. Essayez de nouveau.\n");
                break;
        }
    } while (choix != 4);
}

int main(void) {
    menu_principal();
    return 0;
}
