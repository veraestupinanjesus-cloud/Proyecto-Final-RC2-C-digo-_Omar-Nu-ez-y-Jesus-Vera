// Autor: Omar Nuñez
#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#define MAX_STR 50
#define MAX_ITEMS 100
#define MAX_LINEA 256

// Las estructuras

typedef struct {
    int codigo;
    char nombre[MAX_STR];
    float costo_unitario;
    char unidad_medida[20];
} Ingrediente;

typedef struct {
    int codigo;
    char nombre[MAX_STR];
    char categoria[MAX_STR];
    float imp_pct;
    float serv_pct;
    float gan_pct;
} Plato;

typedef struct {
    int cod_plato;
    int cod_ing;
    float cantidad;
} Receta;

// FUNCIONES 


#endif