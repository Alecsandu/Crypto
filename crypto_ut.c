#define CRYPTO_TEST
#include "crypto.c"
#include "minunit.h"

int tests_run = 0;

static char* test_encryption() 
{
    int encryption_return_flag = encrypt("peppers.bmp", "encodedpeppers.bmp", "secret_key.txt");
    mu_assert("ERROR, encryption failed\n", encryption_return_flag == 1);
    return 0;
}

static char* test_decryption() 
{
    int decryption_return_flag = decrypt("encodedpeppers.bmp", "decodedpeppers.bmp", "secret_key.txt");
    mu_assert("ERROR, decryption failed\n", decryption_return_flag == 1);
    return 0;
}

static char* run_all_tests() 
{
    mu_run_test(test_encryption);
    mu_run_test(test_decryption);
    return 0;
}

int main(void) 
{
    char *result = run_all_tests();

    if (result != 0) 
    {
        printf("%s\n", result);
    }
    else 
    {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}