
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurante.h"

// Archivos Planos
void cargarDatos(Ingrediente *ings, int *t_ing, Plato *platos, int *t_pla, Receta *recs, int *t_rec) {
    char linea[MAX_LINEA];
    
    FILE *f1 = fopen("ingredientes.csv", "r");
    if (f1) {
        fgets(linea, sizeof(linea), f1); 
        while (fgets(linea, sizeof(linea), f1) && *t_ing < MAX_ITEMS) {
            sscanf(linea, "%d,%49[^,],%f,%19[^\n]", 
                   &ings[*t_ing].codigo, ings[*t_ing].nombre, &ings[*t_ing].costo_unitario, ings[*t_ing].unidad_medida);
            (*t_ing)++;
        }
        fclose(f1);
    }

    FILE *f2 = fopen("platos.csv", "r");
    if (f2) {
        fgets(linea, sizeof(linea), f2);
        while (fgets(linea, sizeof(linea), f2) && *t_pla < MAX_ITEMS) {
            sscanf(linea, "%d,%49[^,],%49[^,],%f,%f,%f", 
                   &platos[*t_pla].codigo, platos[*t_pla].nombre, platos[*t_pla].categoria,
                   &platos[*t_pla].imp_pct, &platos[*t_pla].serv_pct, &platos[*t_pla].gan_pct);
            (*t_pla)++;
        }
        fclose(f2);
    }

    FILE *f3 = fopen("plato_ingredientes.csv", "r");
    if (f3) {
        fgets(linea, sizeof(linea), f3);
        while (fgets(linea, sizeof(linea), f3) && *t_rec < MAX_ITEMS) {
            sscanf(linea, "%d,%d,%f", &recs[*t_rec].cod_plato, &recs[*t_rec].cod_ing, &recs[*t_rec].cantidad);
            (*t_rec)++;
        }
        fclose(f3);
    }
}

void guardarDatos(const Ingrediente *ings, int t_ing, const Plato *platos, int t_pla, const Receta *recs, int t_rec) {
    FILE *f1 = fopen("ingredientes.csv", "w");
    if (f1) {
        fprintf(f1, "codigo_ing,nombre_ing,costo_unitario,unidad_medida\n");
        for (int i = 0; i < t_ing; i++) {
            fprintf(f1, "%d,%s,%.2f,%s\n", ings[i].codigo, ings[i].nombre, ings[i].costo_unitario, ings[i].unidad_medida);
        }
        fclose(f1);
    }

    FILE *f2 = fopen("platos.csv", "w");
    if (f2) {
        fprintf(f2, "codigo_plato,nombre_plato,categoria,impuesto_porcentaje,servicio_porcentaje,ganancia_porcentaje\n");
        for (int i = 0; i < t_pla; i++) {
            fprintf(f2, "%d,%s,%s,%.2f,%.2f,%.2f\n", platos[i].codigo, platos[i].nombre, platos[i].categoria, platos[i].imp_pct, platos[i].serv_pct, platos[i].gan_pct);
        }
        fclose(f2);
    }

    FILE *f3 = fopen("plato_ingredientes.csv", "w");
    if (f3) {
        fprintf(f3, "codigo_plato,codigo_ing,cantidad_usada\n");
        for (int i = 0; i < t_rec; i++) {
            fprintf(f3, "%d,%d,%.2f\n", recs[i].cod_plato, recs[i].cod_ing, recs[i].cantidad);
        }
        fclose(f3);
    }
}// Autor: Omar Nuñez
// --- LOGICA DE INGREDIENTES ---
void registrarIngrediente(Ingrediente *ings, int *t_ing) {
    if (*t_ing >= MAX_ITEMS) return;
    Ingrediente nuevo;
    printf("Codigo Ingrediente: "); scanf("%d", &nuevo.codigo);
    
    for(int i=0; i < *t_ing; i++) {
        if(ings[i].codigo == nuevo.codigo) {
            printf("Error: Codigo ya existe.\n"); return;
        }
    }
    
    getchar(); 
    printf("Nombre: "); fgets(nuevo.nombre, MAX_STR, stdin); nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;
    printf("Costo Unitario: "); scanf("%f", &nuevo.costo_unitario);
    getchar();
    printf("Unidad (ej. kg, litros): "); fgets(nuevo.unidad_medida, 20, stdin); nuevo.unidad_medida[strcspn(nuevo.unidad_medida, "\n")] = 0;
    
    if (nuevo.costo_unitario > 0) {
        ings[*t_ing] = nuevo; (*t_ing)++;
        printf("Ingrediente registrado.\n");
    } else {
        printf("Costo invalido.\n");
    }
}

void listarIngredientes(const Ingrediente *ings, int t_ing) {
    printf("\n--- INGREDIENTES ---\n");
    for (int i = 0; i < t_ing; i++) {
        printf("ID: %d | %s | $%.2f x %s\n", ings[i].codigo, ings[i].nombre, ings[i].costo_unitario, ings[i].unidad_medida);
    }
}