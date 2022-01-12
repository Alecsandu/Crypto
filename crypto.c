#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct
{
    unsigned char pR,pG,pB;
}pixel;

/*
	Purpose: this function generates random numbers using the xorshift32 generator and stores them in an array

	Parameters: 
	- seed is used to initialize the xorshift32 generator, also it is the first number from secret_key.txt

	- elements_array contains the generated values (2*latime_imagine*inaltime_imagine numbers)

	- prin intermediul lui sir_elemente transmit numerele generate
*/

void xorshift32(unsigned int **sir_elemente, unsigned int latime, unsigned int inaltime, unsigned int seed)
{
    unsigned int k = 0, aux = seed;
    *sir_elemente = malloc(sizeof(unsigned int) * inaltime * latime * 2);
    for(k = 0; k < 2 * latime * inaltime; k++)
    {
        aux = aux^aux << 13;
        aux = aux^aux >> 17;
        aux = aux^aux << 5;
        (*sir_elemente)[k] = aux;
    }
}

/*
	GENEREZ O PERMUTARE ALEATOARE
*/

void permutare_durstenfeld(unsigned int **permutare, unsigned int latime, unsigned int inaltime, unsigned int *sir_numere_xor)
{
    unsigned int i = 0, poz = 0, aux = 0;
    *permutare= (unsigned int *)malloc(sizeof(unsigned int) * latime * inaltime);
    for(i = 0; i < latime * inaltime; i++)
	{
        (*permutare)[i] = i;
	}
    for(i = inaltime * latime - 1; i >= 1; i--)
    {
        poz = sir_numere_xor[i]%(i+1);
        aux = (*permutare)[poz];
        (*permutare)[poz] = (*permutare)[i];
        (*permutare)[i] = aux;
    }
}

void permutare_inversa(unsigned int **permutare_finala, unsigned int *permutare_initiala, unsigned int latime, unsigned int inaltime)
{
    unsigned int i = 0;
    *permutare_finala = (unsigned int *)malloc(sizeof(unsigned int) * latime * inaltime);
    for(i = 0; i < inaltime * latime; i++)
        (*permutare_finala)[permutare_initiala[i]] = i;
}

void liniarizare_imagine(pixel **imagine, unsigned int latime, unsigned int inaltime, FILE *f)
{
    unsigned char prgb[3];
    unsigned int i = 0;
    *imagine = (pixel *)malloc(sizeof(pixel) * latime * inaltime);
    fseek(f, 54, SEEK_SET);
    for(i = 0; i < latime * inaltime; i++)
    {
        fread(prgb, 3, 1, f);
        (*imagine)[i].pR = prgb[0];
        (*imagine)[i].pG = prgb[1];
        (*imagine)[i].pB = prgb[2];
    }
}

void permutare_pixeli_imagine(pixel **forma_liniarizata_permutata, pixel **forma_liniarizata, unsigned int *permutari, unsigned int latime,
                                unsigned int inaltime)
{
    unsigned int i = 0;
    *forma_liniarizata_permutata = (pixel *)malloc(sizeof(pixel) * inaltime * latime);
    for(i = 0; i < latime * inaltime; i++)
        (*forma_liniarizata_permutata)[*(permutari+i)] = (*forma_liniarizata)[i];
}

/*
	Aplic asupra fiecarui pixel relatia de substitutie necesara criptarii imaginii
*/

void criptare_imagine_finala(pixel **imagine_finala, pixel **imagine_forma_liniarizata, unsigned int *sir_xorshift32, unsigned int latime,
                             unsigned int inaltime, unsigned int Secret_Value)
{
    int octet_2 = (Secret_Value>>16)&0xff;
    int octet_1 = (Secret_Value>>8)&0xff;
    int octet_0 = Secret_Value&0xff;
    unsigned int i = 0, j = inaltime * latime;
    *imagine_finala = (pixel *)malloc(sizeof(pixel) * inaltime * latime);
    (*imagine_finala)[i].pR = octet_0^(*imagine_forma_liniarizata)[i].pR^(*(sir_xorshift32+j));
    (*imagine_finala)[i].pG = octet_1^(*imagine_forma_liniarizata)[i].pG^(*(sir_xorshift32+j));
    (*imagine_finala)[i].pB = octet_2^(*imagine_forma_liniarizata)[i].pB^(*(sir_xorshift32+j));
    for(i = 1; i < inaltime * latime; i++)
    {
        j++;
        (*imagine_finala)[i].pR = (*imagine_finala)[i-1].pR ^ (*imagine_forma_liniarizata)[i].pR ^ (*(sir_xorshift32+j));
        (*imagine_finala)[i].pG = (*imagine_finala)[i-1].pG ^ (*imagine_forma_liniarizata)[i].pG ^ (*(sir_xorshift32+j));
        (*imagine_finala)[i].pB = (*imagine_finala)[i-1].pB ^ (*imagine_forma_liniarizata)[i].pB ^ (*(sir_xorshift32+j));
    }
}

/*
	Aplic inversa relatiei de substitutie folosita in procesul de criptare
*/

void aplicare_xor(pixel **imagine_xorata, pixel **imagine_forma_liniarizata, unsigned int *sir_xorshift32_decr, unsigned int latime,
                  unsigned inaltime, unsigned int Secret_Value)
{
    int b = (Secret_Value>>16)&0xff;      // third octet 16-23
    int c = (Secret_Value>>8)&0xff;       // second octet 8-15
    int d = Secret_Value&0xff;            // first octet 0-7
    unsigned int i = 0, j = latime * inaltime;
    *imagine_xorata = (pixel *)malloc(sizeof(pixel) * latime * inaltime);
    (*imagine_xorata)[i].pR = d ^ (*imagine_forma_liniarizata)[i].pR ^ (*(sir_xorshift32_decr+j));
    (*imagine_xorata)[i].pG = c ^ (*imagine_forma_liniarizata)[i].pG ^ (*(sir_xorshift32_decr+j));
    (*imagine_xorata)[i].pB = b ^ (*imagine_forma_liniarizata)[i].pB ^ (*(sir_xorshift32_decr+j));
    for(i = 1; i < latime * inaltime; i++)
    {
        j++;
        (*imagine_xorata)[i].pR = (*imagine_forma_liniarizata)[i-1].pR ^ (*imagine_forma_liniarizata)[i].pR ^ (*(sir_xorshift32_decr+j));
        (*imagine_xorata)[i].pG = (*imagine_forma_liniarizata)[i-1].pG ^ (*imagine_forma_liniarizata)[i].pG ^ (*(sir_xorshift32_decr+j));
        (*imagine_xorata)[i].pB = (*imagine_forma_liniarizata)[i-1].pB ^ (*imagine_forma_liniarizata)[i].pB ^ (*(sir_xorshift32_decr+j));
    }
}

/*
	Permut pixelii conform permutarii invere pentru a obtine imaginea initiala decriptata
*/

void permutare_finala_decriptare(pixel **imagine_dupa_permutarea_inversa, pixel **imagine_dupa_aplicare, unsigned int *permutari,
                                 unsigned int latime, unsigned inaltime)
{
    *imagine_dupa_permutarea_inversa = (pixel *)malloc(sizeof(pixel) * inaltime * latime);
    for(unsigned int i = 0; i < latime * inaltime; i++)
        (*imagine_dupa_permutarea_inversa)[*(permutari+i)] = (*imagine_dupa_aplicare)[i];
}

//	APLIC ETAPELE DE CRIPTARE PENTRU IMAGINEA "peppers.bmp"

void criptare(char *nume_imagine_initiala, char *nume_rezultat, char *nume_fisier_cu_cheie_s)
{
    FILE *fisiercheie, *fin, *fout;
    fisiercheie = fopen(nume_fisier_cu_cheie_s, "r");
    if(fisiercheie==NULL)
    {
        printf("Eroare la deschiderea fisierului");
        return;
    }
    unsigned int Generator_Seed = 0,Starting_Value = 0;
    fscanf(fisiercheie, "%d", &Generator_Seed);
    fscanf(fisiercheie, "%d", &Starting_Value);
    fclose(fisiercheie);

    fin = fopen(nume_imagine_initiala, "rb+");
    if(fin==NULL)
    {
        printf("The image which you wanted to encrypt could not be found!\n");
        return;
    }

    unsigned int image_size,image_width,image_height;
    fseek(fin,2,SEEK_SET);
    fread(&image_size,sizeof(unsigned int),1,fin);
    fseek(fin,18,SEEK_SET);
    fread(&image_width,sizeof(unsigned int),1,fin);
    fread(&image_height,sizeof(unsigned int),1,fin);

    fout=fopen(nume_rezultat, "wb+");
    int j=0;
    unsigned c;
    fseek(fin, 0, SEEK_SET);
    while(fread(&c, 1, 1, fin)==1 && j<54)
    {
        j++;
        fwrite(&c, 1, 1, fout);
    }

    unsigned int *sir_elemente_xorshift32;
    xorshift32(&sir_elemente_xorshift32, image_width, image_height, Generator_Seed);

    unsigned int *perm;
    permutare_durstenfeld(&perm, image_width, image_height, sir_elemente_xorshift32);

    pixel *liniarizata;
    liniarizare_imagine(&liniarizata, image_width, image_height, fin);

    pixel *liniarizata_permutata;
    permutare_pixeli_imagine(&liniarizata_permutata, &liniarizata, perm, image_width, image_height);
	free(perm);
	free(liniarizata);

    pixel *ciphered_image;
    criptare_imagine_finala(&ciphered_image, &liniarizata_permutata, sir_elemente_xorshift32, image_width, image_height, Starting_Value);
	free(sir_elemente_xorshift32);
	free(liniarizata_permutata);

    int padding = 0;
    if(image_width % 4 != 0)
        padding = 4 - (3 * image_width) % 4;

    for(unsigned int i=0; i<image_height; i++)
    {
        for(unsigned int l=0; l<image_width; l++)
        {
            fwrite(ciphered_image + (image_height*i + l), 3, 1, fout);
        }
        fseek(fout, padding, SEEK_CUR);
    }
    printf("Imaginea a fost criptata cu succes.\n");
	free(ciphered_image);

    fclose(fin);
    fclose(fout);
}

//	APLIC INSTRUCTIUNILE NECESARE PENTRU A OBTINE IMAGINEA INITIALA

void decriptare(char *nume_img_criptat, char *nume_img_decriptata, char *fisier_secret)
{
    FILE *fin, *fout, *key_file;
    fin = fopen(nume_img_criptat, "rb+");
    fout = fopen(nume_img_decriptata, "wb+");
    key_file = fopen(fisier_secret, "r");

    if(fin == NULL)
    {
        printf("The given image was not found!\n");
        return;
    }
    if(key_file == NULL)
    {
        printf("Error at file open!\nCheck if you correctly spelled its name, or if it is present in the same directory as the executable file.");
        return;
    }

    unsigned int Generator_Seed = 0, Starting_Value = 0;
    fscanf(key_file,"%d",&Generator_Seed);
    fscanf(key_file,"%d",&Starting_Value);
    fclose(key_file);

    unsigned int image_size = 0, image_width = 0, image_height = 0;
    fseek(fin, 2, SEEK_SET);
    fread(&image_size, sizeof(unsigned int), 1, fin);
    fseek(fin, 18, SEEK_SET);
    fread(&image_width,sizeof(unsigned int), 1, fin);
    fread(&image_height,sizeof(unsigned int), 1, fin);

    //	COPY THE ENCRYPTED IMAGE HEADER
    int j=0;
    unsigned c;
    fseek(fin,0,SEEK_SET);
    while(fread(&c, 1, 1, fin) == 1 && j < 54)
    {
        j++;
        fwrite(&c, 1, 1, fout);
    }

    unsigned int *sir_elemente_xorshift32_decriptare;
    xorshift32(&sir_elemente_xorshift32_decriptare, image_width, image_height, Generator_Seed);

    unsigned int *durstenfeld_permutation_elements;
    permutare_durstenfeld(&durstenfeld_permutation_elements, image_width, image_height, sir_elemente_xorshift32_decriptare);

    unsigned int *permutare_finala;
    permutare_inversa(&permutare_finala, durstenfeld_permutation_elements, image_width, image_height);
	free(durstenfeld_permutation_elements);

    pixel *imagine_criptata_liniarizata;
    liniarizare_imagine(&imagine_criptata_liniarizata, image_width, image_height, fin);

    pixel *imagine_codata;
    aplicare_xor(&imagine_codata, &imagine_criptata_liniarizata, sir_elemente_xorshift32_decriptare, image_width, image_height, Starting_Value);
	free(sir_elemente_xorshift32_decriptare);
	free(imagine_criptata_liniarizata);

    //	PERMUT PIXELII IMAGINII CONFORM PERMUTARII INVERSE PENTRU A OBTINE IMAGINEA DECRIPTATA
    pixel *imagine_codata_permutata;
    permutare_pixeli_imagine(&imagine_codata_permutata, &imagine_codata, permutare_finala, image_width, image_height);
	free(permutare_finala);
	free(imagine_codata);

	//	OBTIN IMAGINEA DECRIPTATA
    int padding = 0;
    if(image_width % 4 != 0)
	{
        padding = 4 - (3 * image_width) % 4;
    }
	
    for(unsigned int i = 0; i<image_height; i++)
    {
        for(unsigned int j = 0; j<image_width; j++)
        {
            fwrite(imagine_codata_permutata + (image_width*i + j), 3, 1, fout);
        }
        fseek(fout, padding, SEEK_CUR);
    }
    printf("The image was succesfully decrypted.\n");
	free(imagine_codata_permutata);

    fclose(fin);
    fclose(fout);
}

void chi_patrat(char *imagine)
{
	unsigned int image_size, image_width, image_height, f_bar, i = 0, j = 0, *p1, *p2, *p3;
    double nr1 = 0, nr2 = 0, nr3 = 0;
    FILE *f;
    f = fopen(imagine,"rb+");
    fseek(f, 2, SEEK_SET);
    fread(&image_size, sizeof(unsigned int), 1, f);
    fseek(f, 18, SEEK_SET);
    fread(&image_width, sizeof(unsigned int), 1, f);
    fread(&image_height, sizeof(unsigned int), 1, f);
    p1 = (unsigned int *)malloc(sizeof(unsigned int)*256);
    p2 = (unsigned int *)malloc(sizeof(unsigned int)*256);
    p3 = (unsigned int *)malloc(sizeof(unsigned int)*256);
    for(i = 0; i < 256; i++)
    {
        *(p1+i) = 0;
        *(p2+i) = 0;
        *(p3+i) = 0;
    }
	
    fseek(f, 0, SEEK_SET);
    pixel *imagine_liniarizata;
    liniarizare_imagine(&imagine_liniarizata, image_width, image_height, f);
    f_bar = (image_height*image_width) / 256;

    for(j = 0; j < 256; j++)
    {
        for(i = 0; i < image_height * image_width; i++)
        {
            if(((*(imagine_liniarizata + i)).pR) == j)
                (*(p1+j)) = (*(p1+j)) + 1;
            if(((*(imagine_liniarizata + i)).pG) == j)
                (*(p2+j)) = (*(p2+j)) + 1;
            if(((*(imagine_liniarizata + i)).pB) == j)
                (*(p3+j)) = (*(p3+j)) + 1;
        }
    }

    for(i = 0; i < 256; i++)
    {
        nr1 += (double)(((*(p1+i))-f_bar) * ((*(p1+i))-f_bar)) / f_bar;
        nr2 += (double)(((*(p2+i))-f_bar) * ((*(p2+i))-f_bar)) / f_bar;
        nr3 += (double)(((*(p3+i))-f_bar) * ((*(p3+i))-f_bar)) / f_bar;
    }

    printf("Chi_patrat results:\n%.2f %.2f %.2f\n", nr3, nr2, nr1);

    fclose(f);
}

int main()
{
    printf("MODULUL DE CRIPTOGRAFIE\n");
    char nume_imagine_sursa[101];
    char nume_imagine_codificata[101];
    char nume_fisier_cheie[101];

    printf("Numele fisierului care contile imaginea care va urmeaza sa fie codificata este(peppers.bmp): ");
    fgets(nume_imagine_sursa,101,stdin);
    nume_imagine_sursa[strlen(nume_imagine_sursa)-1]='\0';

    printf("\nNumele imaginii dupa criptare este(encodedpeppers.bmp): ");
    fgets(nume_imagine_codificata,101,stdin);
    nume_imagine_codificata[strlen(nume_imagine_codificata)-1]='\0';

    printf("\nNumele fisierului care contine cheia secreta este(secret_key.txt): ");
    fgets(nume_fisier_cheie,101,stdin);
    nume_fisier_cheie[strlen(nume_fisier_cheie)-1]='\0';

    criptare(nume_imagine_sursa,nume_imagine_codificata,nume_fisier_cheie);

    printf("Numele imaginii decodificate este 'decodedpeppers.bmp'\n");
    char nume_imagine_decodificata[101]="decodedpeppers.bmp";
    decriptare(nume_imagine_codificata,nume_imagine_decodificata,nume_fisier_cheie);

    chi_patrat(nume_imagine_sursa);
    chi_patrat(nume_imagine_codificata);
    printf("\n");
	getchar();
	
    return 0;
}
