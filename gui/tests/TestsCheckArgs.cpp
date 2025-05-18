/*
** EPITECH PROJECT, 2023
** Tests.cpp
** File description:
** unit_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

static const int ERROR = 84;
static const int SUCCESS = 0;

int checkArgs(const int ac, char *av[]);

Test(checkArgs, test_help_argument, .exit_code = SUCCESS)
{
    int ac = 2;
    const char* av[3] = {"program", "-help", NULL};
    checkArgs(ac, const_cast<char**>(av));
}

Test(checkArgs, test_flags)
{
    int ac = 5;
    const char* av[6] = {"program", "-p", "12345", "-h", "localhost", NULL};
    cr_assert_eq(checkArgs(ac, const_cast<char**>(av)), SUCCESS);
}

Test(checkArgs, test_invalid_flags)
{
    int ac = 5;
    const char* av[6] = {"program", "-q", "12345", "-i", "localhost", NULL};
    cr_assert_eq(checkArgs(ac, const_cast<char**>(av)), ERROR);
}

Test(checkArgs, test_port_validity)
{
    int ac = 5;
    const char* av[6] = {"program", "-p", "12345", "-h", "localhost", NULL};
    cr_assert_eq(checkArgs(ac, const_cast<char**>(av)), SUCCESS);
}

Test(checkArgs, test_invalid_port_number)
{
    int ac = 5;
    const char* av[6] = {"program", "-p", "-12345", "-h", "localhost", NULL};
    cr_assert_eq(checkArgs(ac, const_cast<char**>(av)), ERROR);
}

Test(checkArgs, test_invalid_port_argument)
{
    int ac = 5;
    const char* av[6] = {"program", "-p", "invalid", "-h", "localhost", NULL};
    cr_assert_eq(checkArgs(ac, const_cast<char**>(av)), ERROR);
}
