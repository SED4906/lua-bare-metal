#include <lauxlib.h>
#include <lua.h>
#include "api/unicode.h"

static const luaL_Reg funcs[] = {
    {NULL, NULL}
};

int luaopen_unicode(lua_State *L) {
    luaL_newlib(L, funcs);
    return 1;
}