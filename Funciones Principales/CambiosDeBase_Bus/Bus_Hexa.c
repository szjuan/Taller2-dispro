void bus4_to_hex(int a3[], int a2[], int a1[], int a0[],
int index, char out[2])
{
    unsigned char value =
        ((a3[index] & 1) << 3) |
        ((a2[index] & 1) << 2) |
        ((a1[index] & 1) << 1) |
        (a0[index] & 1);

    const char hex[] = "0123456789ABCDEF";

    out[0] = hex[value & 0x0F];
    out[1] = '\0';
}

void bus8_to_hex(int a7[], int a6[], int a5[], int a4[],int a3[], int a2[], int a1[], int a0[],
int index,char out[3]){
    unsigned char value =
            ((a7[index] & 1) << 7) |
            ((a6[index] & 1) << 6) |
            ((a5[index] & 1) << 5) |
            ((a4[index] & 1) << 4) |
            ((a3[index] & 1) << 3) |
            ((a2[index] & 1) << 2) |
            ((a1[index] & 1) << 1) |
            (a0[index] & 1);

    const char hex[] = "0123456789ABCDEF";

    out[0] = hex[(value >> 4) & 0x0F];
    out[1] = hex[value & 0x0F];
    out[2] = '\0';
}

void counter_to_hex2(const int cnt[], int index, char out[3]){
    const char hex[] = "0123456789ABCDEF";
    int value = cnt[index] & 0x0F;

    out[0] = '0';            // MSB fijo
    out[1] = hex[value];     // dígito real
    out[2] = '\0';
}