/**
 * File : popcipher.cc
 * Author : Valentin Clement (clementval)
 * Description : Encryption program for the virtual configuration file (Use AES algorithm)
 * Creation date : 02/2011
 * 
 * Modifications :
 * Authors		Date			Comment
 */
#include <stdio.h>
#include "aes.h"
#include "rijndael.h"

#define KEYBITS 256


int main(int argc, char **argv)
{
  unsigned long rk[_AES_RKLENGTH(KEYBITS)];
  unsigned char key[_AES_KEYLENGTH(KEYBITS)];
  int i;
  int nrounds;
  char *password;
  FILE *output;
  if (argc < 2)
  {
    fputs("Missing argument\n", stderr);
    return 1;
  }
  password = (char*)_AES_KEY;
  for (i = 0; i < sizeof(key); i++)
    key[i] = *password != 0 ? *password++ : 0;
  output = fopen(argv[1], "wb");
  if (output == NULL)
  {
    fputs("File write error", stderr);
    return 1;
  }
  nrounds = rijndaelSetupEncrypt(rk, key, 256);
  while (!feof(stdin))
  {
    unsigned char plaintext[16];
    unsigned char ciphertext[16];
    int j;
    for (j = 0; j < sizeof(plaintext); j++)
    {
      int c = getchar();
      if (c == EOF)
        break;
      plaintext[j] = c;
    }
    if (j == 0)
      break;
    for (; j < sizeof(plaintext); j++)
      plaintext[j] = ' ';
    rijndaelEncrypt(rk, nrounds, plaintext, ciphertext);
    if (fwrite(ciphertext, sizeof(ciphertext), 1, output) != 1)
    {
      fclose(output);
      fputs("File write error", stderr);
      return 1;
    }
  }
  fclose(output);
}

