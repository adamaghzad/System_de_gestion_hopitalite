#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct patient {
    int id;
    char patientName[50];
    char patientAddress[50];
    char disease[50];
    char date[12];
};

FILE *fp;

void ajouterPatient();
void listePatients();
void dechargerPatient();
void editerPatient();
void rechercherPatient();

int menu() {
    int ch;

    while (1) {
        system("cls");
        printf("\n\t\t<== Système de gestion hospitalière ==>\n");
        printf("\n\t\t\n1. Ajouter Patient\n");
        printf("\n\t\t\n1. Ajouter dossier de Patient\n");
        printf("\n\t\t\n2. Liste des Patients\n");
        printf("\n\t\t\n3. Decharger Patient\n");
        printf("\n\t\t\n4. Éditer Patient\n");
        printf("\n\t\t\n5. Rechercher Patient\n");
        printf("\n\t\t\n0. Quitter\n\n");
        printf("\n\t\tChoisissez une option : ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                exit(0);

            case 1:
                ajouterPatient();
                break;

            case 2:
                listePatients();
                break;

            case 3:
                dechargerPatient();
                break;

            case 4:
                editerPatient();
                break;

            case 5:
                rechercherPatient();
                break;

            default:
                printf("Choix invalide...\n\n");
        }

        printf("\n\nAppuyez sur une touche pour continuer...");
        getch();
    }

    return 0;
}
void main (){
system ("color F4");
menu();
}
void ajouterPatient() {
    struct patient p;
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("patient.txt", "ab");

    printf("Entrez l'ID du patient : ");
    scanf("%d", &p.id);

    printf("Entrez le nom du patient : ");
    fflush(stdin);
    gets(p.patientName);

    printf("Entrez l'adresse du patient : ");
    fflush(stdin);
    gets(p.patientAddress);

    printf("Entrez la maladie du patient : ");
    fflush(stdin);
    gets(p.disease);

    printf("\nPatient ajouté avec succès");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void listePatients() {
    struct patient p;

    system("cls");
    printf("<== Liste des Patients ==>\n\n");
    printf("\t\t\n%-10s %-30s %-30s %-20s %s\n", "Id", "Nom du Patient", "Adresse", "Maladie", "Date");
    printf("----------------------------------------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb");
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-10d %-30s %-30s %-20s %s\n", p.id, p.patientName, p.patientAddress, p.disease, p.date);
    }

    fclose(fp);
}

void dechargerPatient() {
    int id, f = 0;
    struct patient p;

    system("cls");
    printf("<== Patient déchargé ==>\n\n");
    printf("Entrez l'ID du patient à décharger : ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            f = 1;
        } else {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nPatient avec ID déchargé");
    } else {
        printf("\n\nEnregistrement introuvable !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");
}

void editerPatient() {
    int id, found = 0;
    struct patient p;

    system("cls");
    printf("<== Éditer Patient ==>\n\n");
    printf("\t\t\nEntrez l'ID du patient à éditer : ");
    scanf("%d", &id);

    fp = fopen("patient.txt", "rb+");

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Détails du patient :\n");
        printf("Identifiant du patient : %d\n", p.id);
        printf("Nom du patient : %s\n", p.patientName);
        printf("Adresse du patient : %s\n", p.patientAddress);
        printf("Maladie du patient : %s\n\n", p.disease);

        printf("Entrez les nouveaux détails :\n");

        printf("Entrez le nouveau nom du patient : ");
        fflush(stdin);
        gets(p.patientName);

        printf("Entrez la nouvelle adresse du patient : ");
        fflush(stdin);
        gets(p.patientAddress);

        printf("Entrez la nouvelle maladie du patient : ");
        fflush(stdin);
        gets(p.disease);

        fseek(fp, ftell(fp) - sizeof(p), 0);
        fwrite(&p, sizeof(p), 1, fp);
        printf("\n\nDétails du patient mis à jour avec succès.");
    } else {
        printf("\n\nPatient introuvable !");
    }

    fclose(fp);
}

void rechercherPatient() {
    int id, found = 0;
    struct patient p;

    system("cls");
    printf("<== Rechercher Patient ==>\n\n");
    printf("\t\t\nEntrez l'ID du patient à rechercher : ");
    scanf("%d", &id);

    fp = fopen("patient.txt", "rb");

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Détails du patient :\n");
        printf("Identifiant du patient : %d\n", p.id);
        printf("Nom du patient : %s\n", p.patientName);
        printf("Adresse du patient : %s\n", p.patientAddress);
        printf("Maladie du patient : %s\n", p.disease);
        printf("Date : %s\n\n", p.date);
    } else {
        printf("\n\nPatient introuvable !");
    }

    fclose(fp);
}
