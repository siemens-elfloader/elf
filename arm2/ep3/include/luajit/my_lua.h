
#ifndef __MY_LUA_H__
#define __MY_LUA_H__

#include <swilib.h>
#include "lua.h"

#define lua_boxpointer(L,u) \
        (*(void **)(lua_newuserdata(L, sizeof(void *))) = (u))

#define lua_unboxpointer(L,i)   (*(void **)(lua_touserdata(L, i)))

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    void (*exit_func)(lua_State *L, void *user_data);
    void *user_data;
    void *next;
    void *prev;
}atexit_list;


typedef struct
{
    void (*abort)(int status);
    char keep_alive;
    char *s_folder;
    char *s_name;
    char *script;
    char *plugin_dir;
    char is_aborting;
    int is_lock;
    atexit_list *atexitl;
    void (*RunInLuaProc)(void *func, void *ud);
}m_lua_State;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}LUA_MAIN_CSM;


typedef struct
{
  GUI gui;
  lua_State *L;
  int ref[6];
  int id;
  char closing;
}LUA_MAIN_GUI;


typedef struct
{
    char curentPen[5];
    char curentBrus[5];
    int curentFont;
    int curentTextAttribyte;
    WSHDR *lua_ws;
    size_t lua_ws_AllocatedSize;
}_lua_draw_engine;

static __inline__ m_lua_State * mluaState(lua_State *L)
{
   lua_getglobal(L, "__MLS__");
   void* point = lua_unboxpointer(L, -1);
   lua_pop(L, 1);
   return (m_lua_State*)point;
}


static inline void lua_lock_exit(lua_State *L)
{
    mluaState(L)->is_lock ++;
}

static inline void lua_unlock_exit(lua_State *L)
{
    mluaState(L)->is_lock --;
}


int docall(lua_State *L, int narg, int clear);
int traceback(lua_State *L);
int report(lua_State *L, int status);
void l_message(const char *pname, const char *msg);



#ifdef __cplusplus
}
#endif

#endif
