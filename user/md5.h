#pragma once

typedef unsigned long int UINT4;
typedef struct {
  UINT4 i[2];
  UINT4 buf[4];
  unsigned char in[64];
  unsigned char digest[16];
} MD5_CTX;

void MD5Init ();
void MD5Update ();
void MD5Final ();
void MD5Get(char*, unsigned int, char*);
