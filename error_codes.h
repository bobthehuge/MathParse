#pragma once

#define ERR_OK 0
#define ERR_NOARG 1
#define ERR_NOVARG 2
#define ERR_NOEARG 3
#define ERR_INVCHAR 4
#define ERR_INVNUMREP 5
#define ERR_UNEXPTOK 6
#define ERR_MATHNOEARG 7

#define ERR_NOARG_MSG "ERROR: no argument provided\n"
#define ERR_NOVARG_MSG "ERROR: no valid argument\n"
#define ERR_NOEARG_MSG "ERROR: not enough argument provided\n"
#define ERR_INVCHAR_MSG "ERROR: unknown char\n"
#define ERR_INVNUMREP_MSG "ERROR: numbers shouldn't start with 0 and 0 should be unique\n" 
#define ERR_UNEXPTOK_MSG "ERROR: unexpected token found\n"
#define ERR_MATHNOEARG_MSG "ERROR: mismatch argument count for math operator\n"
