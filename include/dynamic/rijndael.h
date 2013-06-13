/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 09/20/2010
 * @brief AES cipher function declaration
 *
 *
 */

#ifndef H__RIJNDAEL
#define H__RIJNDAEL

int rijndaelSetupEncrypt(unsigned long *rk, const unsigned char *key,
  int keybits);
int rijndaelSetupDecrypt(unsigned long *rk, const unsigned char *key,
  int keybits);
void rijndaelEncrypt(const unsigned long *rk, int nrounds,
  const unsigned char plaintext[16], unsigned char ciphertext[16]);
void rijndaelDecrypt(const unsigned long *rk, int nrounds,
  const unsigned char ciphertext[16], unsigned char plaintext[16]);

#define _AES_KEYLENGTH(keybits) ((keybits)/8)
#define _AES_RKLENGTH(keybits)  ((keybits)/8+28)
#define _AES_NROUNDS(keybits)   ((keybits)/32+6)

#endif

