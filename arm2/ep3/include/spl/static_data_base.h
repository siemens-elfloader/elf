

#ifndef __STATIC_DATA_BASE_H__
#define __STATIC_DATA_BASE_H__



#define declare_static_db(db_struct_name, func_prefix, max_members_var)   \
    static db_struct_name _db[max_members_var];     \
    static CoreMutex db_struct_name##_lock;           \
                                                    \
    void func_prefix##Init()                        \
    {                                               \
        createMutex(&db_struct_name##_lock);        \
        for(int i=0; i<max_members_var; ++i)        \
            _db[i].id = -1;                         \
    }                                               \
                                                    \
    void func_prefix##Fini()                        \
    {                                               \
        destroyMutex(&db_struct_name##_lock);       \
    }                                               \
                                                    \
    static int get_empty_id()                       \
    {                                               \
        for(int i=0; i<max_members_var; ++i)        \
            if(_db[i].id == -1)                     \
                return i;                           \
                                                    \
        return -1;                                  \
    }                                               \
                                                    \
    static db_struct_name *get##db_struct_name##Data(int id)  \
    {                                               \
        if(id < 0 || id >= max_members_var)                  \
            return 0;                              \
                                                    \
        return &_db[id];                            \
    }                                               \
                                                    \
    static db_struct_name *new##db_struct_name##Data()            \
    {                                               \
        int id = get_empty_id();                    \
        db_struct_name *db_v = get##db_struct_name##Data(id); \
        if(!db_v)                                   \
            return 0;                              \
                                                    \
        db_v->id = id;                              \
        return db_v;                                  \
    }                                               \
                                                    \
    static int free##db_struct_name##Data(int id)         \
    {                                               \
        db_struct_name *db_v = get##db_struct_name##Data(id); \
        if(!db_v || db_v->id != id)                 \
            return -1;                              \
                                                    \
        db_v->id = -1;                              \
        return 0;                                   \
    }                                               \
                                                    \
    static db_struct_name *check##db_struct_name##Data(int id) \
    {                                               \
        db_struct_name *db_v = get##db_struct_name##Data(id);  \
        if(!db_v || db_v->id != id)                 \
            return 0;                               \
                                                    \
        return db_v;                                \
    }


#endif
