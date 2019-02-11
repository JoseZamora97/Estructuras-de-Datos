/**
* Modulo: ArbolBinario
* Tipo: Programa() Interfaz TAD (X) Implementacion TAD () Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular Árboles Binarios de elementos (implementación
*              en memoria enlazada).
*/

#ifndef ARBOL_BINARIO_HPP
#define ARBOL_BINARIO_HPP

#include <stdexcept> // Excepciones estándar en C++

namespace ed {

/*
 * Implementación de ArbolBinario para la asignatura de Estructuras
 * de datos de la URJC con tipo de elemento E.
 */
template <typename E>
class ArbolBinario
{
public:

  // Excepciones asociadas a ArbolBinario
  class EMemoriaAgotada: public std::runtime_error
  {
  public:
    EMemoriaAgotada(const std::string& w = "EMemoriaAgotada"): std::runtime_error(w) {}
  };

  class EArbolVacio: public std::domain_error
  {
  public:
    EArbolVacio(const std::string& w = "EArbolVacio"): std::domain_error(w) {}
  };

  /** POST: Constructor sin parámetros. Deja el árbol vacío. */
  ArbolBinario();

  /** Destructor: libera toda la memoria dinámica del a Árbol Binario */
  ~ArbolBinario();

  /**
   *  POST: Deja el Árbol Binario vacío.
   */
  void vaciar();

  /**
   *  PRE: Queda suficiente espacio para insertar un nuevo elemento en el árbol
   *  actual.
   *  POST: Construye el árbol con raíz 'e' e hijos 'izq', 'dcho' y se lo
   *        asigna al árbol actual. Si árbol actual no es ninguno de los
   *        hijos, el actual se deja vacío antes.
   *        NOTA IMPORTANTE:
   *        Las variables 'izqdo' y 'dcho' ya no son dueñas de la memoria,
   *        ahora lo será ha pasado a ser propiedad de 'arbin'
   *  EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void construir(ArbolBinario& izqdo, E e, ArbolBinario& dcho);

  /**
   * PRE: El árbol actual no está vacío.
   * POST: Devuelve el elemento que está en la raíz del árbol actual.
   * EXCEPCIONES: 'EArbolVacio' si el árbol actual es el vacío.
   */
  void raiz(E& e);

  /**
   * PRE: El árbol actual no está vacío.
   * POST: Copia 'e' sobre el elemento raíz del árbol actual.
   * EXCEPCIONES: 'EArbolVacio' si el árbol actual es el vacío.
   */
  void cambiarRaiz(E e);

  /**
   * PRE: El árbol actual no está vacío.
   * POST: Devuelve el hijo izquierdo del árbol.
   * EXCEPCIONES: 'EArbolVacio' si el árbol actual es el vacío.
   */
  void hijoIzquierdo(ArbolBinario& izqdo);

  /**
   * PRE: El árbol actual no está vacío.
   * POST: Devuelve el hijo derecho del árbol.
   * EXCEPCIONES: 'EArbolVacio' si el árbol actual es el vacío.
   */
  void hijoDerecho(ArbolBinario& dcho);

  /**
   * POST: devuelve cierto si 'ArbolBinario' es la vacío.
   */
  bool esVacio();

  /** Operador de asignación */
  ArbolBinario& operator=(ArbolBinario& l);

  /** Constructor de copia */
  ArbolBinario(ArbolBinario& l);

  /** Operador de comparación */
  bool operator==(ArbolBinario& l);
  bool operator!=(ArbolBinario& l);

  // Elemento necesario para poder hacer operaciones genéricas
  // sobre árboles binario de cualquier tipo.
  typedef E Elemento;

//  //-----------------------------------------------
//  // Elementos necesarios para definir iteradores

//  // Hacer friend a IteradorArbolBinario (para que tenga acceso a la
//  // parte privada de ArbolBinario).
//  friend class IteradorArbolBinario<E>;

//  /** Definir el tipo de iterador para la Árbol Binario */
//  typedef IteradorArbolBinario<E> Iterador;

//  /** Función que devuelve un iterador apuntando al primer elemento */
//  Iterador primerIterador() { return Iterador(*this, this->nodo_raiz_); }

protected:
  /**
   *  El tipo Nodo es privado dado que sólo es necesario internamente
   *  en la implementación de ArbolBinario.
   */
  struct Nodo
  {
    E raiz;
    Nodo* hijoizqdo;
    Nodo* hijodcho;
  };

  /**
   * POST: Devuelve un único nodo con raíz 'e', e hijos 'izqdo' y 'dcho'.
   */
  Nodo* crearNodo(Nodo* izqdo, E e, Nodo* dcho);

  /**
   * POST: Elimina todos los nodos del árbol que representa pNodo (puntero a la raíz).
   */
  void destruir(Nodo*& pNodo);

  /**
   * POST: Copia todos los nodos del árbol representado por el puntero al
   *       nodo raíz pNodoOrigen' en el árbol representado por el puntero al nodo
   *       raíz 'pNodoDestino'.
   */
  void copiar(Nodo*& pNodoDestino, Nodo*& pNodoOrigen);

  /**
   * POST: Devuelve cierto si los árboles son iguales (misma forma y valor de nodos).
   *       pNodo1 es el puntero al nodo raíz del árbol 1 y pNodo2 es el puntero al
   *       nodo raíz del árbol 2.
   */
  bool iguales(Nodo* pNodo1, Nodo* pNodo2);

  /**
   * Implementación de ArbolBinario en memoria dinámica con:
   *   - Puntero al nodo raíz
   */
  Nodo* nodo_raiz_;
  bool es_propietario_;
};

#include "arbol_binario.cpp"
//#include "iterador_arbol_binario.cpp"
#include "arbol_binario_io.cpp"

} // namespace ed

#endif // ARBOL_BINARIO_HPP
