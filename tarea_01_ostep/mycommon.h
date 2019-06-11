#ifndef __MYCOMMON__
#define __MYCOMMON__

#include "pthread.h"
#include "common.h"
#define puerta pthread_mutex_t // nuevo tipo de dato
#define crear_puerta(m) pthread_mutex_init(&m,NULL) // función para crear la puerta
#define cerrar_puerta(m) pthread_mutex_lock(&m) // función para cerrar la puerta
#define abrir_puerta(m) pthread_mutex_unlock(&m) // función parar abrir la puerta
#define destruir_puerta(m) pthread_mutex_destroy(&m) // función para destruir la puerta

#endif