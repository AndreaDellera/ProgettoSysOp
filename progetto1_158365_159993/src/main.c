/*
 Andrea Dellera 158365
 Gianluca Bortoli 159993
 
 Progetto 1
 Anno accademico 2013/2014
 */

#include <stdio.h>
#include "function.h"
#include <getopt.h>

int main(int argc, char **argv){
    static struct option long_options[] = {
        {"name",    required_argument,       0,  'n' },
        {"msg",     required_argument,       0,  'a' },
        {"min",     required_argument, 0,  'm' },
        {"max",     required_argument, 0,  'M' },
        {0,           0,                 0,  0   }
    };
    
    if(strcmp(argv[0],"codeserver")){
        server s = new server();
        
        
        int k;
        
        char *options ="n:a:m:M:"; // i : indicano che il parametro ha un argomento
        
        opterr = 0;
        
        while ((k = getopt_long(argc, argv,"n:a:m:M:",
                                long_options, &long_index )) != -1)
            switch (k)
        {
            case 'n':
                s.name = optarg;
                break;
                
            case 'a':
                s.maxMsg = atoi(optarg);
                
            case 'm':
                s.minKey = atoi(optarg);
                break;
                
            case 'M':
                s.maxKey = atoi(optarg);
                break;
                
            case '?':
                if (optopt == 'n')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort ();
        }
        
        printf ("nvalue = %s, minvalue = %d, maxvalue = %d\n", nvalue, minvalue, maxvalue);
        
        for (index = optind; index < argc; index++)
            printf ("Non-option argument %s\n", argv[index]);
    }
    
    if(strcmp(argv[0],"codeclient")){
        
    }
    
    return 0;
}
