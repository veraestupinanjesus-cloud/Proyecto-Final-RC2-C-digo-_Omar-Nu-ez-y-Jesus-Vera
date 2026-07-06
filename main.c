#include <stdio.h>
#include <stdlib.h>
#include "restaurante.h"

int main() {
    Ingrediente ingredientes[MAX_ITEMS]; int total_ing = 0;
    Plato platos[MAX_ITEMS]; int total_pla = 0;
    Receta recetas[MAX_ITEMS]; int total_rec = 0;

    // Carga inicial de datos de archivos CSV
    cargarDatos(ingredientes, &total_ing, platos, &total_pla, recetas, &total_rec);

    int opcion;
    do {
        printf("\n===================================\n");
        printf("    SISTEMA DE GESTION DE COSTOS   \n");
        printf("===================================\n");
        printf("1. Registrar Ingrediente\n");
        printf("2. Listar Ingredientes\n");
        printf("3. Registrar Plato\n");
        printf("4. Listar Platos y Costos Finales\n");
        printf("5. Asociar Ingrediente a un Plato\n");
        printf("6. Guardar Cambios y Salir\n");
        printf("===================================\n");
        printf("Seleccione opcion: ");
        
        if(scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Saliendo...\n");
            break;
        }

        switch(opcion) {
            case 1: registrarIngrediente(ingredientes, &total_ing); break;
            case 2: listarIngredientes(ingredientes, total_ing); break;
            case 3: registrarPlato(platos, &total_pla); break;
            case 4: listarPlatos(platos, total_pla, ingredientes, total_ing, recetas, total_rec); break;
            case 5: asociarIngredientePlato(recetas, &total_rec, platos, total_pla, ingredientes, total_ing); break;
            case 6: 
                guardarDatos(ingredientes, total_ing, platos, total_pla, recetas, total_rec);
                printf("Archivos CSV guardados correctamente. Saliendo...\n");
                break;
            default: printf("Opcion no valida.\n");
        }
    } while(opcion != 6);

    return 0;
}