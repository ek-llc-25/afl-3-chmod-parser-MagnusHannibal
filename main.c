// main.c - Fixed version with more tests
#include <assert.h>
#include <stdio.h>
#include "perms.h"

int main(int argc, char *argv[]) {
    // Test 1
    {
        struct perms_t file_a = { 0644 };
        printf("Test 1 before: %o\n", file_a.bits);
        struct perms_t expect = { 0640 };
        printf("Test 1 expect: %o\n", expect.bits);
        bool success = chmod("o-r", &file_a);
        printf("Test 1 after:  %o\n", file_a.bits);
        assert(success && file_a.bits == expect.bits);
        printf(" -> Test 1 gik godt!\n\n");
    }

    // Test 2
    {
        struct perms_t file_b = { 0777 };
        printf("Test 2 before: %o\n", file_b.bits);
        struct perms_t expect = { 0666 };
        printf("Test 2 expect: %o\n", expect.bits);
        bool success = chmod("a-x", &file_b);
        printf("Test 2 after:  %o\n", file_b.bits);
        assert(success && file_b.bits == expect.bits);
        printf(" -> Test 2 gik godt!\n\n");
    }

    // Test 3
    {
        struct perms_t file_c = { 0400 };
        printf("Test 3 before: %o\n", file_c.bits);
        struct perms_t expect = { 0700 };
        printf("Test 3 expect: %o\n", expect.bits);
        bool success = chmod("u+wx", &file_c);
        printf("Test 3 after:  %o\n", file_c.bits);
        assert(success && file_c.bits == 0700);
        printf(" -> Test 3 gik godt!\n\n");
    }

    // Test 4
    {
        struct perms_t file_d = { 0644 };
        printf("Test 4 before: %o\n", file_d.bits);
        struct perms_t expect = { 0664 };
        printf("Test 4 expect: %o\n", expect.bits);
        bool success = chmod("g+w", &file_d);
        printf("Test 4 after:  %o\n", file_d.bits);
        assert(success && file_d.bits == expect.bits);
        printf(" -> Test 4 gik godt!\n\n");
    }

    // Test 5
    {
        struct perms_t file_e = { 0644 };
        printf("Test 5 before: %o\n", file_e.bits);
        struct perms_t expect = { 0755 };
        printf("Test 5 expect: %o\n", expect.bits);
        bool success = chmod("a+x", &file_e);
        printf("Test 5 after:  %o\n", file_e.bits);
        assert(success && file_e.bits == expect.bits);
        printf(" -> Test 5 gik godt!\n\n");
    }

    // Test 6
    {
        struct perms_t file_f = { 0640 };
        printf("Test 6 before: %o\n", file_f.bits);
        struct perms_t expect = { 0647 };
        printf("Test 6 expect: %o\n", expect.bits);
        bool success = chmod("o+rwx", &file_f);
        printf("Test 6 after:  %o\n", file_f.bits);
        assert(success && file_f.bits == expect.bits);
        printf(" -> Test 6 gik godt!\n\n");
    }

    // Test 7
    {
        struct perms_t file_g = { 0755 };
        printf("Test 7 before: %o\n", file_g.bits);
        struct perms_t expect = { 0055 };
        printf("Test 7 expect: %o\n", expect.bits);
        bool success = chmod("u-rwx", &file_g);
        printf("Test 7 after:  %o\n", file_g.bits);
        assert(success && file_g.bits == expect.bits);
        printf(" -> Test 7 gik godt!\n\n");
    }

    // Test 8
    {
        struct perms_t file_h = { 0644 };
        uint32_t original = file_h.bits;
        printf("Test 8: Testing invalid input\n");
        bool success = chmod("invalid", &file_h);
        assert(!success && file_h.bits == original);
        printf(" -> Test 8 gik godt!\n\n");
    }

    // Test 9
    {
        struct perms_t file_i = { 0644 };
        printf("Test 9: Tester NULL input\n");
        bool success = chmod(NULL, &file_i);
        assert(!success);
        printf(" -> Test 9 gik godt!\n\n");
    }
    return 0;
}