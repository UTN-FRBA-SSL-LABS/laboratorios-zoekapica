#include <stdio.h>
#include "../src/carrito.h"
#include "minunit/minunit.h"

/*
 * Tests de integracion: verifican que las funciones trabajan bien
 * en combinacion, no de forma aislada.
 */

/* ═══════════════════════════════════════════════════════════════════════════
 *  PARTE D — Escribir el test guiado (ver README.md, Parte 8)
 * ═══════════════════════════════════════════════════════════════════════════ */

void test_compra_con_descuento(void) {
    printf("\n[integracion: compra con descuento]\n");
    Carrito c;
    carrito_init(&c);

    Producto pan = {"Pan", 200, 3};       // Subtotal: 600
    Producto leche = {"Leche", 350, 2};   // Subtotal: 700

    carrito_agregar(&c, pan);
    carrito_agregar(&c, leche);

    int total = carrito_total(&c);
    ASSERT_IGUAL(1300, total);

    int total_con_desc = carrito_descuento(total, 10);
    ASSERT_IGUAL(1170, total_con_desc);
}

/* ═══════════════════════════════════════════════════════════════════════════
 *  PARTE E — Disenar un test propio (ver README.md, Parte 9)
 * ═══════════════════════════════════════════════════════════════════════════ */

void test_agregar_hasta_llenar(void) {
    printf("\n[integracion: agregar hasta llenar y verificar conteo]\n");
    Carrito c;
    carrito_init(&c);
    Producto p = {"Item", 50, 1};

    for (int i = 0; i < 4; i++) {
        carrito_agregar(&c, p);
    }

    ASSERT_IGUAL(4, carrito_contar(&c));
    ASSERT_IGUAL(0, carrito_agregar(&c, p)); // 5to intento falla
    ASSERT_IGUAL(4, carrito_contar(&c));     // El conteo no cambia
}

int main(void) {
    printf("=== Tests de integracion ===");
    /* Descomentar a medida que agregues las funciones: */
    test_compra_con_descuento();  
     test_agregar_hasta_llenar();  
    RESUMEN();
    return EXIT_CODE();
}
