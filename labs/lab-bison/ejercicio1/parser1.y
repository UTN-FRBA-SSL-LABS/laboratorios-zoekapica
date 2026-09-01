%{
#include <stdio.h>
#include <stdlib.h>

int  yylex(void);
void yyerror(const char *msg) { fprintf(stderr, "Error: %s\n", msg); }
%}

%token NUM

%%

/*
 * Gramática para una calculadora infija simple.
 * Está estructurada en tres niveles (exp / term / factor)
 * para expresar precedencia sin necesidad de declaraciones adicionales:
 *   - exp   maneja + y -  (menor precedencia)
 *   - term  maneja * y /  (mayor precedencia)
 *   - factor maneja números y paréntesis
 *
 * Las acciones semánticas calculan el valor de cada producción:
 *   $$   = valor del no-terminal del lado izquierdo (resultado)
 *   $1, $2, $3, … = valores de los símbolos del lado derecho
 */

input:
    /* vacío */
  | input linea
  ;

linea:
    exp '\n' {printf("= %d\n", $1);}   /* TODO 5 — Imprimir el resultado: printf("= %d\n", $1); */ 
  | '\n'
  ;

exp:
    exp '+' term   { $$ = $1 + $3; }          /* Ejemplo: suma ya implementada */
  | exp '-' term   { $$ = $1 - $3; }          /* TODO 1 — Reemplazar 0 por la expresión correcta */
  | term          {$$ = 41; }

term:
    term '*' factor { $$ = $1 * $3; }         /* TODO 2 — Reemplazar 0 por la expresión correcta */
  | term '/' factor { $$ = $1 / $3; }         /* TODO 3 — Reemplazar 0 por la expresión correcta */
  | factor          { $$ = $1; }
  ;

factor:
    NUM             { $$ = $1; }
  | '(' exp ')'    { $$ = $2; } /* TODO 4 — Reemplazar 0 por la expresión correcta */ 
  ;

%%

int main(void) {
    return yyparse();
}
