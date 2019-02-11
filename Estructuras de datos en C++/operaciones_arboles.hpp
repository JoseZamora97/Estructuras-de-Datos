#ifndef OPERACIONES_ARBOLES_HPP
#define OPERACIONES_ARBOLES_HPP

#include "arbol_binario.hpp"
#include "arbol_binario_aux.hpp"
#include "cola.hpp"
#include "pila.hpp"
#include <math.h>
#include <algorithm>

namespace ed {
/**
 * POST: Devuelve el n?mero de nodos del ?rbol 'a' que tienen s?lo el sub?rbol
 *       derecho vac?o. Un nodo con los dos hijos vac?os no se contar?.
 */
template <typename ArbolBin>
int numNodosSoloHijoDchoVacio(ArbolBin a);

/**
 * POST: Devuelve el recorrido en anchura del ?rbol. El recorrido en anchura
 *       comienza con la ra?z, a continuaci?n elementos en el nivel 2 de izquierda
 *       a derecha, nivel 3 de izquierda a derecha, etc.
 *
 *       La implementaci?n debe de ser obligatoriamente iterativa (no recursiva).
 *       Se pueden utilizar otras estructuras de datos auxiliares.
 */
template <typename ArbolBin>
void recorridoEnAnchuraIterativo(ArbolBin a, Lista<typename ArbolBin::Elemento>& recorrido);

/**
 * POST: Devuelve los elementos del nivel k-?simo en la lista nivel_k. El primero
 *       de la lista es el elemento m?s a la izquierda del nivel k-?simo y
 *       el nivel aparece en la lista de izquierda a derecha.
 *       Si k > profundidad del ?rbol, se devuelve la lista vac?a en nivel_k.
 */
template <typename ArbolBin>
void elementosNivelK(ArbolBin a, int k, Lista<typename ArbolBin::Elemento>& nivel_k);

/**
 * POST: Devuelve el cierto si el ?rbol es completo. Un ?rbol vac?o
 *       es completo. Todo ?rbol binario es completo cuando tiene todos
 *       los nodos posibles para la profundidad del ?rbol.
 */
template <typename ArbolBin>
bool esCompleto(ArbolBin a);

#include "operaciones_arboles.cpp"

}// namespace ed

#endif
