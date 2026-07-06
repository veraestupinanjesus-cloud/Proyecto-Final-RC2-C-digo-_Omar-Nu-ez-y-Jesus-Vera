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
}
// LOGICA DE INGREDIENTES 
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

// LOGICA DE PLATOS Y COSTOS 
void registrarPlato(Plato *platos, int *t_pla) {
    if (*t_pla >= MAX_ITEMS) return;
    Plato p;
    printf("Codigo Plato: "); scanf("%d", &p.codigo);
    for(int i=0; i < *t_pla; i++) {
        if(platos[i].codigo == p.codigo) { printf("Error: Codigo existe.\n"); return; }
    }
    getchar();
    printf("Nombre Plato: "); fgets(p.nombre, MAX_STR, stdin); p.nombre[strcspn(p.nombre, "\n")] = 0;
    printf("Categoria: "); fgets(p.categoria, MAX_STR, stdin); p.categoria[strcspn(p.categoria, "\n")] = 0;
    printf("%% Impuesto (ej. 15): "); scanf("%f", &p.imp_pct);
    printf("%% Servicio (ej. 10): "); scanf("%f", &p.serv_pct);
    printf("%% Ganancia (ej. 30): "); scanf("%f", &p.gan_pct);
    
    platos[*t_pla] = p; (*t_pla)++;
    printf("Plato registrado.\n");
}

float calcularCostoBase(int cod_plato, const Receta *recs, int t_rec, const Ingrediente *ings, int t_ing) {
    float costoTotal = 0;
    for (int i = 0; i < t_rec; i++) {
        if (recs[i].cod_plato == cod_plato) {
            for (int j = 0; j < t_ing; j++) {
                if (ings[j].codigo == recs[i].cod_ing) {
                    costoTotal += (ings[j].costo_unitario * recs[i].cantidad);
                    break;
                }
            }
        }
    }
    return costoTotal;
}

void listarPlatos(const Plato *platos, int t_pla, const Ingrediente *ings, int t_ing, const Receta *recs, int t_rec) {
    printf("\n--- MENU DE PLATOS ---\n");
    for (int i = 0; i < t_pla; i++) {
        float c_base = calcularCostoBase(platos[i].codigo, recs, t_rec, ings, t_ing);
        float imp = c_base * (platos[i].imp_pct / 100.0);
        float serv = c_base * (platos[i].serv_pct / 100.0);
        float gan = c_base * (platos[i].gan_pct / 100.0);
        float c_final = c_base + imp + serv + gan;

        printf("ID: %d | %s (%s)\n", platos[i].codigo, platos[i].nombre, platos[i].categoria);
        printf("   Costo Base: $%.2f | PRECIO FINAL VENTA: $%.2f\n", c_base, c_final);
    }
}

// RECETAS la ASOCIACION
void asociarIngredientePlato(Receta *recs, int *t_rec, const Plato *platos, int t_pla, const Ingrediente *ings, int t_ing) {
    Receta r;
    printf("ID Plato a modificar: "); scanf("%d", &r.cod_plato);
    printf("ID Ingrediente a agregar: "); scanf("%d", &r.cod_ing);
    printf("Cantidad usada de ese ingrediente: "); scanf("%f", &r.cantidad);

    if(r.cantidad <= 0) { printf("Cantidad invalida.\n"); return; }

    for(int i=0; i<*t_rec; i++) {
        if(recs[i].cod_plato == r.cod_plato && recs[i].cod_ing == r.cod_ing) {
            printf("Error: Ya existe.\n"); return;
        }
    }
    recs[*t_rec] = r; (*t_rec)++;
    printf("Ingrediente asociado al plato exitosamente.\n");
}