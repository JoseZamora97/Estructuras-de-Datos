/**
* Modulo: Cola
* Tipo: Programa() Interfaz TAD (X) Implementacion TAD () Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular Colas de elementos implementada
*              utilizando una lista internamente (parametrizado en
*              función de los elementos que se guardan)
*/

#ifndef COLA_HPP
#define COLA_HPP

#include <stdexcept> // Excepciones estándar en C++
#include "lista.hpp"

namespace ed {

// Declaración adelantada del iterador sobre Colas.
// ¡¡Es necesaria porque Cola depende de IteradorCola pero Cola
//   todavía no está definida!!
template <typename E> class IteradorCola;

/*
 * Implementación de Colas para la asignatura de Estructuras
 * de datos de la URJC con tipo de elemento E.
 */
template <typename E>
class Cola
{
public:
  // Excepciones asociadas a Colas
  class EMemoriaAgotada: public std::runtime_error
  {
  public:
    EMemoriaAgotada(const std::string& w = "EMemoriaAgotada"): std::runtime_error(w) {}
  };

  class EColaVacia: public std::domain_error
  {
  public:
    EColaVacia(const std::string& w = "EColaVacia"): std::domain_error(w) {}
  };

  /** Constructor sin parámetros */
  Cola();

  /** Destructor: libera toda la memoria dinámica de la cola */
  ~Cola();

  /**
   *  POST: Deja la cola vacía.
   */
  void vaciar();

  /**
   *  PRE: Hay memoria suficiente para insertar un elemento.
   *  POST: inserta el elemento 'e' al final de la cola actual.
   *  EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void insertar(E e);

  /**
   * PRE: La cola actual no está vacía.
   * POST: devuelve el elemento en al comienzo de la cola en 'e'.
   * EXCEPCIONES: 'EColaVacia' si la cola actual es la vacía.
   */
  void primero(E& e);

  /**
   * POST: devuelve cierto si la cola es la vacía.
   */
  bool esVacia();

  /**
   * POST: devuelve el número de elementos insertados en la cola.
   */
  int longitud();

  /**
   * PRE: La cola actual no está vacía.
   * POST: elimina el elemento al comienzo de la cola actual.
   * EXCEPCIONES: 'EColaVacia' si la cola es la vacía.
   */
  void eliminar();

  /** Operador de asignación */
  Cola& operator=(Cola& l);

  /** Constructor de copia */
  Cola(Cola& l);

  /** Operador de comparación */
  bool operator==(Cola& l);
  bool operator!=(Cola& l);

  //-----------------------------------------------
  // Elementos necesarios para definir iteradores

  // Hacer friend a IteradorCola (para que tenga acceso a la
  // parte privada de Cola).
  friend class IteradorCola<E>;

  /** Definir el tipo de iterador para la cola */
  typedef IteradorCola<E> Iterador;

  /** Función que devuelve un iterador apuntando al primer elemento */
  Iterador primerIterador() { return Iterador(*this, almacen_.primerIterador()); }

  /** Función que devuelve un iterador apuntando al último elemento */
  Iterador ultimoIterador() { return Iterador(*this, almacen_.ultimoIterador()); }

private:
  // Los elementos de la cola están almacenados internamente
  // en una lista.
  Lista<E> almacen_;
};

template <typename E>
class IteradorCola
{
public:
  // Tipos asociados al IteradorCola.
  typedef typename Lista<E>::Iterador Cursor;

  // Excepciones asociadas a IteradorCola
  class EIteradorNoValido: public std::runtime_error
  {
  public:
    EIteradorNoValido(const std::string& w = "EIteradorNoValido"): std::runtime_error(w) {}
  };

  // Constructor
  IteradorCola(Cola<E>& l, Cursor c): cola_(l), cursor_(c) {}

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
   *       un nuevo elemento en la cola
   * POST: inserta un nodo con elemento 'e' inmediatamente detrás
   *       (si el parámetro 'detras' es cierto) o inmediatamente
   *       delante (si el parámetro 'detras' es falso)
   *       del nodo apuntado por el iterador.  Si el iterador
   *       no es válido, se inserta el nuevo nodo al final de la cola.
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
   * POST: elimina el elemento apuntado por el iterador de la cola. El
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
   *       de la cola.
   */
  bool esIteradorValido();

  /**
   * POST: Devuelve cierto si el iterador apunta al primer elemento de la
   *       cola
   */
  bool esPrimero();

  /**
   * POST: Devuelve cierto si el iterador apunta al último nodo de la
   *       cola
   */
  bool esUltimo();

private:

  // Tenemos una referencia a la cola sobre la que iteramos
  Cola<E>& cola_;

  // Datos que necesitamos para iterar sobre la cola (sólo un iterador
  // de cola sobre el elemento en el que nos encontramos).
  Cursor cursor_;
};

#include "cola.cpp"
#include "iterador_cola.cpp"
#include "cola_io.cpp"

} // namespace ed

#endif // COLA_HPP
