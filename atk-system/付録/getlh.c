unsigned short get_ushort(FILE *fp) {
    unsigned char s[2];
    if (fread(s, sizeof(unsigned char), 2, fp) < 2) exit(1);
    return 256U*s[1] + s[0];
}

unsigned long get_ulong(FILE *fp) {
    unsigned char s[4];
    if (fread(s, sizeof(unsigned char), 4, fp) < 4) exit(1);
    return ((256LU*s[3] + s[2])+256LU + s[1])*256LU + s[0];
}