//Reference: https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
#include<stdio.h> 
#include<string.h> 
  
//no of characters in input alphabet
#define d 256 
  
/* parameters:
   pat -> pattern we are looking for
    txt -> text that is given
    q -> A prime number to use for our hash function
*/
void search(char pattern[], char txt[], int q) 
{ 
    int psize = strlen(pattern); 
    int tsize = strlen(txt); 
    int i, j; 
    int hashp = 0; // hash value for pattern
    int hasht = 0; // hash value for text 
    int h = 1; 
    int f = 0;
  
    // Hash function defined as:
    // h = pow(d, psize-1)%q
    for (i = 0; i < psize-1; i++) 
        {h = (h*d)%q; }
  
    // Calculate the hash value of pattern and first 
    for (i = 0; i < psize; i++) 
    { 
        hashp = (d*hashp + pattern[i])%q; 
        hasht = (d*hasht + txt[i])%q; 
    } 
  
    // Slide the pattern over text one by one 
    for (i = 0; i <= tsize - psize; i++) 
    { 
  
        // Check the hash values of current selected text 
        // and pattern. 
        // If the total hash values match, check if the characters match

        if ( hashp == hasht ) 
        { 
            /* Check for characters one by one */
            for (j = 0; j < psize; j++) 
            { 
                //if any character doesn't match, come out of loop
                if (txt[i+j] != pattern[j]) 
                    break; 
            } 
  
            // pattern size and content matches with selected text 
            if (j == psize) 
                {printf("Pattern found in text at position %d \n", i+1); 
                f = f + 1;}
            
            
        } 
        
  
        // Calculate hash value for next window of text: 
        // Remove leading digit, add trailing digit 
        if ( i < tsize-psize ) 
        { 
            hasht = (d*(hasht - txt[i]*h) + txt[i+psize])%q; 
  
            //if hasht is negative, we convert to positive
            if (hasht < 0) 
            hasht = (hasht + q); 
        } 
    } 

    if (f == 0)
    {printf("Pattern not found in text.\n");}

} 
  
/* test Function */
int main() 
{ 
    char txt[] = "Bricks killed Cersei Lannister"; 
    char pattern[] = "led"; 
    char pat2[] = "jaimie";
    int q = 101; // A prime number 
    printf ("searching '%s' in '%s'.. \n",pattern, txt);
    search(pattern, txt, q); 
    printf("searching '%s' in '%s'.. \n", pat2, txt);
    search(pat2,txt,q);
    return 0; 
} 