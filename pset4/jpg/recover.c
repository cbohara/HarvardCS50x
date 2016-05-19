/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdint.h>
 
 // each jpeg image is stored as a block of 512 bytes
 const int BLOCK_SIZE = 512;
 
 int main(int argc, char *agrv[])
 {
    FILE *f;
    
    if ((f = fopen("card.raw", "r")) == NULL)
    {
        printf("Error opening the file \"ecard.raw\"...");
        return 1;
    }
    
    uint8_t buf[512];
    
    int counter = 0;
    FILE *fw = NULL;
    
    // iterate through the file contents
    while (fread(buf, BLOCK_SIZE, 1, f))
    {
        // check if the first four bytes are a JPEG signature
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] == 0xe0 || buf[3] == 0xe1))
        {
            // close the current file
            if (fw != NULL)
                fclose(fw);
            
            char filename[8];
            sprintf(filename, "%03d.jpg", counter);
                
            // open a new JPEG file to output the recovered JPEG
            fw = fopen(filename, "w");
            
            counter++;
        }
        
        if (fw != NULL)
            fwrite(buf, BLOCK_SIZE, 1, fw);
    }
    
    if (fw != NULL)
        fclose(fw);
    
    fclose(f);
 
    return 0;
 } 