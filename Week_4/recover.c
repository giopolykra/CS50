#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Ensure correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // open file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    // Variable to store the chanks or 512 bytes
    //unsigned char buffer[512];

    //will store the name of each output file
    char filename[8];

    // target file
    FILE *output_image = NULL;

    // while there are bytes to be read (read in chunks of 512 bytes)
    //save 512 byte chanks on buffer
    uint8_t buffer[512];
    size_t n_bytes = 0;
    // keep track of jpegs opened
    int pic = 0;
    //read from input_file save to buffer, succesfully reading only one element in chanks of 512 bytes
    while (fread(buffer, 512, 1, input_file) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] >= 0xe0) && (buffer[3] <= 0xef)))
        {
            //close the previous output_image
            if (pic != 0)
            {
                fclose(output_image);
            }
            // stores the jpeg file name with the # jpeg
            sprintf(filename, "%03i.jpg", pic);
            output_image = fopen(filename, "w");
            pic++;
        }
        // If JPEG was found write it on output image
        if (output_image != NULL)
        {
            fwrite(buffer, 512, 1, output_image);
        }

    }

    fclose(output_image);
    fclose(input_file);

    return 0;
}
