#define CRYPTO_TEST
#include "crypto.c"
#include "minunit.h"

int tests_run = 0;

int foo = 7;

static char* test_encryption() 
{
    mu_assert("error, foo != 7", encrypt("peppers.bmp", "encodedpeppers.bmp", "secret_key.txt") == 1);
    return 0;
}

static char* test_decryption() 
{
    mu_assert("error, foo != 7", decrypt("encodedpeppers.bmp", "decodedpeppers.bmp", "secret_key.txt") == 1);
    return 0;
}

static char* all_tests() 
{
    mu_run_test(test_encryption);
    mu_run_test(test_decryption);
    return 0;
}

int main(void) 
{
    char *result = all_tests();

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