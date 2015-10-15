#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 40
#define IN "staedte.txt"
#define STEP 2

typedef struct
{
	int g;
	int m;

	char r [2];
	double dezi;
}KORDI;


typedef struct
{
	char name [MAX];
	KORDI laenge;
	KORDI breite;
	int einwohner;

}STADT;

int holeSpeicher ( STADT ** zeiger , int *res , int anzahl );
STADT interpretiere ( char zeile [] ) ;
KORDI string2kordi(char string []);
void sorteinwohner(STADT* pz, int anz);
void sortname(STADT* pz, int anz);
void sortgeo(STADT* pz, int anz);


int main ( void ) 
{
	// Speicherverwaltungsdaten
	STADT * pz = NULL ; // adresse des dyn. arrays
	int reserviert = 0 , belegt = 0 ; // Verwaltungsdaten
	
	// Dateiverarbeiten:
	FILE * fp = NULL ;

	int i = 0;
	char zeile [ 1000 ] = "" ;
	STADT dorf;
	
	
	if ( NULL == ( fp = fopen ( IN , "r" ) ) )
		{
			 return 1 ;
		}
		
	if (pz==NULL)
	{
		printf("Wollen Sie Daten einlesen? Druecken Sie E und Return\n");
	}
		if (getchar()=='E')
	{
		reserviert = holeSpeicher ( &pz , &reserviert , STEP ) ;
		while ( NULL != fgets ( zeile , 1000 , fp ) )
		{
			//printf("%s", zeile);
			dorf = interpretiere ( zeile ) ;
			if ( i >= reserviert )
		 		 holeSpeicher ( &pz , &reserviert , STEP ) ;
			pz [ i ++ ] = dorf ; 
	
		
		}
	belegt = i ;	fclose ( fp ) ;
	

	}
	if (pz!=NULL)
	{
		printf(" Wollen Sie die Daten ausgeben? Druecken Sie A und Return \n Wollen Sie die Daten loeschen und den Vorgang beenden?\n\t Druecken Sie L und Return \n "
				"Wollen Sie die Daten nach Namen sortieren und ausgeben? Druecken Sie N Return\n Wollen Sie die Daten nach Einwohnerzahl sortieren? Druecken Sie Z und Return \n"
				" Wollen Sie die Daten nach geo. Breite sortieren? Druecken Sie B und Return \n ");
	
    while (1)
    {
	char Eingabe =getchar();
	if (Eingabe=='A')
	{
		int k=0;
		for (k=0; k<belegt; k++)
	{
		printf("%-8s:%3d Grad %2d Minuten %10s %10f Grad dezimal \n\t %3d Grad %2d Minuten %10s %10f Grad dezimal \n\t\t%10d Einwohner \n\n", pz[k].name, pz[k].breite.g, pz[k].breite.m, 
		pz[k].breite.r, pz[k].breite.dezi,
		pz[k].laenge.g, pz[k].laenge.m, pz[k].laenge.r, pz[k].laenge.dezi, pz[k].einwohner);
	}
	printf("\n");
	}
	else if (Eingabe=='N')
	{
		sortname(pz, belegt);
		int k=0;
		for (k=0; k<belegt; k++)
		{
		printf("%-8s:%3d Grad %2d Minuten %10s %10f Grad dezimal \n\t %3d Grad %2d Minuten %10s %10f Grad dezimal \n\t\t%10d Einwohner \n\n", pz[k].name, pz[k].breite.g, pz[k].breite.m, 
		pz[k].breite.r, pz[k].breite.dezi,
		pz[k].laenge.g, pz[k].laenge.m, pz[k].laenge.r, pz[k].laenge.dezi, pz[k].einwohner);
		}
		printf("\n");
	}
	
	
	else if(Eingabe=='Z')
	{
		sorteinwohner(pz, belegt);
		int k=0;
		for (k=0; k<belegt; k++)
		{
		printf("%-8s:%3d Grad %2d Minuten %10s %10f Grad dezimal \n\t %3d Grad %2d Minuten %10s %10f Grad dezimal \n\t\t%10d Einwohner \n\n", pz[k].name, pz[k].breite.g, pz[k].breite.m, 
		pz[k].breite.r, pz[k].breite.dezi,
		pz[k].laenge.g, pz[k].laenge.m, pz[k].laenge.r, pz[k].laenge.dezi, pz[k].einwohner);
		}
		printf("\n");
	}
	else if (Eingabe=='B')
	{
		sortgeo(pz, belegt);
		int k=0;
		for (k=0; k<belegt; k++)
		{
		printf("%-8s:%3d Grad %2d Minuten %10s %10f Grad dezimal \n\t %3d Grad %2d Minuten %10s %10f Grad dezimal \n\t\t%10d Einwohner \n\n", pz[k].name, pz[k].breite.g, pz[k].breite.m, 
		pz[k].breite.r, pz[k].breite.dezi,
		pz[k].laenge.g, pz[k].laenge.m, pz[k].laenge.r, pz[k].laenge.dezi, pz[k].einwohner);
		}
		printf("\n");
	}

	else if (Eingabe=='L')
	{
		free(pz);
		belegt=reserviert=0;
		return 0;
	}

	}
	}
	


	free ( pz ) ;
	belegt=reserviert=0;

	return 0;
}





int holeSpeicher ( STADT ** zeiger , int *res , int anzahl ) 
{
	int menge = *res + anzahl ;
	int bytes = menge * sizeof ( **zeiger ) ;
	STADT * hz = NULL ;
	
	if ( *zeiger == NULL || *res == 0 )
	{
		// erstanforderung
		if ( NULL == ( *zeiger = 
				(STADT*) malloc ( bytes ) ) )
			return -1 ;
		*res = menge ;
		return *res ;
	}
	// speichererweiterungsanforderung
	hz = (STADT*) realloc ( (void*) *zeiger , bytes ) ;
	if ( NULL == hz ) 
		return -1 ;
	if ( hz != *zeiger ) 
		free ( (void*) *zeiger ) ;
	*zeiger = hz ;
	hz = NULL ;
	*res = menge ;
	return menge ;
}





STADT interpretiere ( char zeile [] )
{
	
	STADT dorf = { "" , {0,0,"",0},{0,0,"",0},0 } ;
	int o=0;
	char bufferBreite [15]="";
	char bufferLaenge [15]="";
	char bufferEinwohner [15]="";
	char bufferName [15]="";
	char* Abschnitt ="";


		Abschnitt= strtok(zeile,";");                      //Zerteilung das eingelesenen Strings in Einzelteile und Buffer-Speicherung
			if (o<4)
			{

				strcpy(bufferName, Abschnitt);
				
				o++;
				if ( o==1&&(Abschnitt  = strtok(NULL, ";")) )
				{
					strcpy(bufferBreite, Abschnitt);
				}
				o++;
				if ( o==2&&(Abschnitt  = strtok(NULL, ";")) )
				{
					strcpy(bufferLaenge, Abschnitt);
				}
				o++;
				if ( o==3&&(Abschnitt  = strtok(NULL, ";")) )
				{
					strcpy(bufferEinwohner, Abschnitt);
				}
				o++;
			}
	
	dorf.einwohner=atoi(bufferEinwohner);                  //Umwandlung der Stringelemente in verarbeitbare Daten
	strcpy(dorf.name,bufferName);
	
	
	dorf.laenge=string2kordi(bufferLaenge);
	dorf.breite=string2kordi(bufferBreite);



	return dorf ;
}


KORDI string2kordi(char string [])
{
	int o=0;
	char* Abschnitt = "";
	char bufferGrad [15]="";
	char bufferMinute [15]="";
	char bufferRichtung [15]="";
	KORDI kordi={-1,-1,"F", -1};          //Defaultinitialisierung
	Abschnitt= strtok(string,"°");            // Zerteilung an Einheiten
			if (o<2)
			{
				
				strcpy(bufferGrad, Abschnitt);
				
				o++;
				if ( o==1&&(Abschnitt  = strtok(NULL, "'")) )
				{
					strcpy(bufferMinute, Abschnitt);
					o++;
				}
				if (o==2&& (Abschnitt = strtok(NULL, "")))
				{
					strcpy(bufferRichtung, Abschnitt);
				}
			}
	if ((atoi(bufferGrad)<90)||((bufferRichtung[0]==("W"||"w"||"O"||"o"||"E"||"e"))&&atoi(bufferGrad)<180))    //Prüfung auf Sinnhaftigkeit der Werte
	{
		kordi.g=atoi(bufferGrad);
	}
	if(atoi(bufferMinute)<60)
	{
		kordi.m=atoi(bufferMinute);
	}
	strcpy(kordi.r, bufferRichtung);

	kordi.dezi=(((double)kordi.m/(double)60)+kordi.g);                     //Umrechnung ins Dezimalgrad
	if(kordi.r[0]==("S"||"s"||"W"||"w"))
	{
		kordi.dezi=-kordi.dezi;
	}
			
	return kordi;

}


void sorteinwohner(STADT* pz, int anz)
{
	int k, m;
	for(k=0;k<anz; k++)                           //Sortierung über Ersetzungsschleife
	{
		for(m=0; m<anz; m++)
		{
			if (pz[k].einwohner>pz[m].einwohner)
			{
				STADT puffer=pz[k];
				pz[k]=pz[m];
			    pz[m]=puffer;
			}
		}
	}

}

void sortname(STADT* pz, int anz)
{
	int k, m;
	for(k=0;k<anz; k++)
	{
		for(m=0; m<anz; m++)
		{
			if (strcmp(pz[k].name, pz[m].name)<=0)
			{
				STADT puffer=pz[k];
				pz[k]=pz[m];
			    pz[m]=puffer;
			}
		}
	}

}
void sortgeo(STADT* pz, int anz)
{
	int k, m;
	for(k=0;k<anz; k++)
	{
		for(m=0; m<anz; m++)
		{
			if (pz[k].breite.dezi>pz[m].breite.dezi)
			{
				STADT puffer=pz[k];
				pz[k]=pz[m];
			    pz[m]=puffer;
			}
		}
	}

}
