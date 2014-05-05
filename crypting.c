//
//  Andrea Dellera 158365
//  Gianluca Bortoli 159993
//  Progetto n°1
//

/*
Alfabeto di 26 lettere.
ASCII 'A': 65
ASCII 'Z': 90
ASCII 'a': 97
ASCII 'z': 122

nuova lettera: lettera +[lettera+offset] mod 26
*/

#include <stdio.h>



int main(){//main di test delle funzioni
    char key[] = "a";
    char text[] = "andrea";

    cript(text, key);
    
    printf("messaggio criptato: ");
    int i = 0;
    while(text[i] != '\0'){
        printf("%c",text[i]);
        i++;
    }
    printf("\n\n");
    
    
    i = 0;
    decript(text, key);
    printf("messaggio DEcriptato: ");
    while(text[i] != '\0'){
        printf("%c",text[i]);
        i++;
    }
    printf("\n");
    
    return 0;
}

