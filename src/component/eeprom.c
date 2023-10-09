#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include "eeprom.h"
#include "api/component.h"

static int eeprom_get(lua_State *L, struct eeprom_data *data, int arguments_start) {
    if (data->contents == NULL)
        lua_pushnil(L);
    else
        lua_pushstring(L, data->contents);
    return 1;
}

static int eeprom_set(lua_State *L, void *data, int arguments_start) {
    return luaL_error(L, "eeprom contents are read-only");
}

static int eeprom_get_data(lua_State *L, struct eeprom_data *data, int arguments_start) {
    if (data->data == NULL)
        lua_pushnil(L);
    else
        lua_pushstring(L, data->data);
    return 1;
}

static int eeprom_set_data(lua_State *L, struct eeprom_data *data, int arguments_start) {
    const char *new_data = luaL_checkstring(L, arguments_start);

    if (data->data != NULL)
        free(data->data);

    data->data = malloc(strlen(new_data) + 1);

    if (data->data == NULL)
        return luaL_error(L, "out of memory");

    strcpy(data->data, new_data);

    return 0;
}

static int eeprom_get_label(lua_State *L, struct eeprom_data *data, int arguments_start) {
    if (data->label == NULL)
        lua_pushnil(L);
    else
        lua_pushstring(L, data->label);
    return 1;
}

static int eeprom_set_label(lua_State *L, struct eeprom_data *data, int arguments_start) {
    const char *new_label = luaL_checkstring(L, arguments_start);

    if (data->label != NULL)
        free(data->label);

    data->label = malloc(strlen(new_label) + 1);

    if (data->label == NULL)
        return luaL_error(L, "out of memory");

    strcpy(data->label, new_label);

    return 0;
}

static int eeprom_get_size(lua_State *L, struct eeprom_data *data, int arguments_start) {
    lua_pushinteger(L, strlen(data->contents));
    return 1;
}

static int eeprom_get_data_size(lua_State *L, void *data, int arguments_start) {
    lua_pushinteger(L, 4096); /* arbitrary */
    return 1;
}

struct eeprom_data *eeprom_init(void) {
    struct eeprom_data *data = malloc(sizeof(struct eeprom_data));
    assert(data != NULL);

    data->contents = NULL;
    data->data = NULL;
    data->label = NULL;
    
    struct component *eeprom = new_component("eeprom", new_uuid(), data);
    add_method(eeprom, "get", eeprom_get);
    add_method(eeprom, "set", eeprom_set);
    add_method(eeprom, "getLabel", eeprom_get_label);
    add_method(eeprom, "setLabel", eeprom_set_label);
    add_method(eeprom, "getSize", eeprom_get_size);
    add_method(eeprom, "getDataSize", eeprom_get_data_size);
    add_method(eeprom, "getData", eeprom_get_data);
    add_method(eeprom, "setData", eeprom_set_data);
    // getChecksum
    // makeReadonly
    add_component(eeprom);

    return data;
}
