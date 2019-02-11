/**
* Modulo: Pila
* Tipo: Programa() Interfaz TAD (X) Implementacion TAD () Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular Pilas de elementos implementada
*              utilizando una lista internamente (parametrizado en
*              función de los elementos que se guardan)
*/

#ifndef PILA_HPP
#define PILA_HPP

#include <stdexcept> // Excepciones estándar en C++
#include "lista.hpp"

namespace ed {

// Declaración adelantada del iterador sobre Pilas.
// ¡¡Es necesaria porque Pila depende de IteradorPila pero Pila
//   todavía no está definida!!
template <typename E> class IteradorPila;

/*
 * Implementación de Pilas para la asignatura de Estructuras
 * de datos de la URJC con tipo de elemento E.
 */
template <typename E>
class Pila
{
public:
  // Excepciones asociadas a Pilas
  class EMemoriaAgotada: public std::runtime_error
  {
  public:
    EMemoriaAgotada(const std::string& w = "EMemoriaAgotada"): std::runtime_error(w) {}
  };

  class EPilaVacia: public std::domain_error
  {
  public:
    EPilaVacia(const std::string& w = "EPilaVacia"): std::domain_error(w) {}
  };

  /** Constructor sin parámetros */
  Pila();

  /** Destructor: libera toda la memoria dinámica de la pila */
  ~Pila();

  /**
   *  POST: Deja la pila vacía.
   */
  void vaciar();

  /**
   *  PRE: Queda suficiente espacio para insertar
   *       un nuevo elemento.
   *  POST: inserta un nodo conteniendo 'e' en la cima de
   *        la pila.
   *  EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void apilar(E e);

  /**
   * PRE: La pila no está vacía
   * POST: devuelve el elemento en la cima de la pila en 'e'
   * EXCEPCIONES: 'EPilaVacia' si 'Pila' está vacía
   */
  void cima(E& e);

  /**
   * POST: devuelve cierto si la pila es la vacía.
   */
  bool esVacia();

  /**
   * POST: devuelve el número de elementos en la pila.
   */
  int longitud();

  /**
   * PRE: La pila no está vacía
   * POST: elimina el elemento en la cima de la pila.
   * EXCEPCIONES: 'EPilaVacia' si la pila está vacía
   */
  void desapilar();

  /** Operador de asignación */
  Pila& operator=(Pila& l);

  /** Constructor de copia */
  Pila(Pila& l);

  /** Operador de comparación */
  bool operator==(Pila& l);
  bool operator!=(Pila& l);

  //-----------------------------------------------
  // Elementos necesarios para definir iteradores

  // Hacer friend a IteradorPila (para que tenga acceso a la
  // parte privada de Pila).
  friend class IteradorPila<E>;

  /** Definir el tipo de iterador para la pila */
  typedef IteradorPila<E> Iterador;

  /** Función que devuelve un iterador apuntando al primer elemento */
  Iterador primerIterador() { return Iterador(*this, almacen_.primerIterador()); }

  /** Función que devuelve un iterador apuntando al último elemento */
  Iterador ultimoIterador() { return Iterador(*this, almacen_.ultimoIterador()); }

private:
  // Los elementos de la pila están almacenados internamente
  // en una lista.
  Lista<E> almacen_;
};

template <typename E>
class IteradorPila
{
public:
  // Tipos asociados al IteradorPila.
  typedef typename Lista<E>::Iterador Cursor;

  // Excepciones asociadas a IteradorPila
  class EIteradorNoValido: public std::runtime_error
  {
  public:
    EIteradorNoValido(const std::string& w = "EIteradorNoValido"): std::runtime_error(w) {}
  };

  // Constructor
  IteradorPila(Pila<E>& l, Cursor c): pila_(l), cursor_(c) {}

  /**
   * POST: devuelve cierto si el iterador permite ir del primer al
   *       último elemento
   */
  bool permiteIterarAscendente();

  /**
   * POST: devuelve cierto si el iterador permite ir del último al
   *       primer elemento.
   */
  bool permiteIterarDescendente();

  /**
   * POST: devuelve cierto si el iterador permite utilizar insertar().
   */
  bool permiteInsertar();

  /**
   * POST: devuelve cierto si el iterador permite utilizar eliminar().
   */
  bool permiteEliminar();

  /**
   * PRE:  El iterador es válido (se puede usar para iterar).
   * POST: devuelve el elemento asociado a 'c' en 'e'
   * EXCEPCIONES: 'EIteradorNoValido' si el iterador no es válido.
   */
  void obtenerElemento(E& e);

  /**
   * PRE: Queda suficiente espacio en memoria para insertar
   *       un nuevo elemento en la pila
   * POST: inserta un nodo con elemento 'e' inmediatamente detrás
   *       (si el parámetro 'detras' es cierto) o inmediatamente
   *       delante (si el parámetro 'detras' es falso)
   *       del nodo apuntado por el iterador.  Si el iterador
   *       no es válido, se inserta el nuevo nodo al final de la pila.
   * EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void insertar(E e, bool detras);

  /**
   * PRE: El iterador es válido (se puede usar para iterar)
   * POST: asigna 'e' al elemento apuntado por el iterador
   * EXCEPCIONES: 'EIteradorNoValido' si es un iterador no válido.
   */
  void reemplazar(E e);

  /**
   * PRE:  El iterador es válido (se puede usar para iterar)
   * POST: elimina el elemento apuntado por el iterador de la pila. El
   *       iteador toma el valor del siguiente()
   * EXCEPCIONES: 'EIteradorNoValido' si el iterador no es válido.
   */
  void eliminar();

  /**
   * PRE:  El iterador es válido (se puede usar para iterar).
   * POST: Avanza el iterador al elemento siguiente
   *       al que apuntaba. Si no hay ningún elemento detrás del
   *       iterador, el iterador se transforma en el no válido.
   * EXCEPCIONES: 'EIteradorNoValido' si el iterador no es válido.
   */
  void siguiente();

  /**
   * PRE:  El iterador es válido (se puede usar para iterar).
   * POST: Retrocede el iterador al elemento anterior
   *       al que apuntaba. Si no hay ningún elemento delante del
   *       iterador, el iterador se transforma en el no válido.
   * EXCEPCIONES: 'EIteradorNoValido' si el iterador no es válido.
   */
  void anterior();

  /**
   * POST: Devuelve cierto si el iterador apunta a algún elemento
   *       de la pila.
   */
  bool esIteradorValido();

  /**
   * POST: Devuelve cierto si el iterador apunta al primer elemento de la
   *       pila
   */
  bool esPrimero();

  /**
   * POST: Devuelve cierto si el iterador apunta al último nodo de la
   *       pila
   */
  bool esUltimo();

private:

  // Tenemos una referencia a la pila sobre la que iteramos
  Pila<E>& pila_;

  // Datos que necesitamos para iterar sobre la pila (sólo un iterador
  // de pila sobre el elemento en el que nos encontramos).
  Cursor cursor_;
};

#include "pila.cpp"
#include "iterador_pila.cpp"
#include "pila_io.cpp"

} // namespace ed

#endif // PILA_HPP
