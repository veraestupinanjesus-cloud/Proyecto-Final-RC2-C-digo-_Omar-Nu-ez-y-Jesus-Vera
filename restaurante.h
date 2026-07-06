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
void cargarDatos(Ingrediente *ings, int *t_ing, Plato *platos, int *t_pla, Receta *recs, int *t_rec);
void guardarDatos(const Ingrediente *ings, int t_ing, const Plato *platos, int t_pla, const Receta *recs, int t_rec);
void registrarIngrediente(Ingrediente *ings, int *t_ing);
void listarIngredientes(const Ingrediente *ings, int t_ing);
void registrarPlato(Plato *platos, int *t_pla);
void listarPlatos(const Plato *platos, int t_pla, const Ingrediente *ings, int t_ing, const Receta *recs, int t_rec);
void asociarIngredientePlato(Receta *recs, int *t_rec, const Plato *platos, int t_pla, const Ingrediente *ings, int t_ing);
float calcularCostoBase(int cod_plato, const Receta *recs, int t_rec, const Ingrediente *ings, int t_ing);

#endif