#include "main.hpp"
#include <fstream>

int abs_i(int n) {
	return n < 0 ? -n : n;
}

VALUE load_int(VALUE obj, char* name){
    int re = rgss_obj_ivar_get(obj, rgss_ascii_new_cstr(name));
    return re >> 1;
}

VALUE load_obj(VALUE obj, char* name){
    return rgss_obj_ivar_get(obj, rgss_ascii_new_cstr(name));
}

VALUE set_obj(VALUE obj, char* name, VALUE val){
    return rgss_obj_ivar_set(obj, rgss_ascii_new_cstr(name), val);
}

DWORD DLL_EXPORT InitOK() {
	return init_ok;
}

VALUE DLL_EXPORT HelloWorld() {
	if (!init_ok) { return -1; }
	return rgss_ascii_new_cstr("Hello World from RGSS-Extension!");
}

VALUE DLL_EXPORT GetInstance(VALUE obj, VALUE iv) {
	if (!init_ok) { return -1; }
	return rgss_obj_ivar_get(obj, iv);
}

VALUE DLL_EXPORT SetInstance(VALUE obj, VALUE iv, VALUE val) {
	if (!init_ok) { return -1; }
	return rgss_obj_ivar_set(obj, iv, val);
}

VALUE DLL_EXPORT GetAryIndex(VALUE ary, VALUE pos){
    if(!init_ok){return -1;}
	return rgss_ary_at(ary, pos);
}

VALUE DLL_EXPORT CheckCollision(DWORD proj_len, VALUE projs, DWORD ppl_len, VALUE ppl){
    if(!init_ok){return -1;}
    int* ppl_x  = new int[ppl_len];
    int* ppl_y  = new int[ppl_len];
    int* ppl_wx = new int[ppl_len];
    int* ppl_hy = new int[ppl_len];

    for(int i=0;i<proj_len;++i){
        VALUE obj = rgss_ary_at(projs, i);
        int px = load_int(obj, "@x");
        int py = load_int(obj, "@y");
        VALUE crect = load_obj(obj, "@crect");
        px += load_int(crect, "@x");
        py += load_int(crect, "@y");
        int pwx = px + load_int(crect, "@width");
        int phy = py + load_int(crect, "@height");

        for(int j=0;j<ppl_len;++j){
            VALUE p = rgss_ary_at(ppl, j);
            if(i == 0){
                VALUE crect2 = load_obj(p, "@crect");
                ppl_x[j] = load_int(p, "@x") + load_int(crect2, "@x");
                ppl_y[j] = load_int(p, "@y") + load_int(crect2, "@y");
                ppl_wx[j] = ppl_x[j] + load_int(crect2, "@width");
                ppl_hy[j] = ppl_y[j] + load_int(crect2, "@height");
            }
            int px2 = ppl_x[j];
            int py2 = ppl_y[j];
            int pwx2 = ppl_wx[j];
            int phy2 = ppl_hy[j];
            if(pwx > px2 && px < pwx2 && phy > py2 && py < phy2){
                set_obj(obj, "@collided", p);
            }
        }
    }

    delete[] ppl_x;
    delete[] ppl_y;
    delete[] ppl_wx;
    delete[] ppl_hy;
    return 0;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
