/*
 Andrea Dellera 158365
 Gianluca Bortoli 159993
 
 Progetto 1
 Anno accademico 2013/2014
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


int
main (int argc, char **argv)
{
    char *name = NULL;
    int minKey = -1;
    int maxKey = -1;
    int maxMsg = -1;
    int index;
    int k;
    int long_index =0;

    
    static struct option long_options[] = {
        {"name",    required_argument,       0,  'n' },
        {"msg",     required_argument,       0,  'a' },
        {"min",     required_argument, 0,  'm' },
        {"max",     required_argument, 0,  'M' },
        {0,           0,                 0,  0   }
    };
    opterr = 0;
    
    while ((getopt_long(argc, argv,"n:a:m:M:", long_options, &long_index )) != -1)
        switch (k)
    {
        case 'n':
            name = optarg;
            break;
            
        case 'a':
            maxMsg = atoi(optarg);
            break;
            
        case 'm':
            minKey = atoi(optarg);
            break;
            
        case 'M':
            maxKey = atoi(optarg);
            break;
        
        case '?':
            return 1;
            
            
        default:
            break;
            //abort ();
    }
    
    printf ("nvalue = %s, minvalue = %d, maxvalue = %d\n", name, minKey, maxKey);
    
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    return 0;
}