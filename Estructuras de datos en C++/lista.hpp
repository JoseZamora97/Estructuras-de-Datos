/**
* Modulo: Lista
* Tipo: Programa() Interfaz TAD (X) Implementacion TAD () Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular Listas de elementos implementada con
*              nodos de doble enlace (parametrizado en
*              función de los elementos que se guardan)
*/

#ifndef LISTA_HPP
#define LISTA_HPP

#include <stdexcept> // Excepciones estándar en C++

namespace ed {

// Declaración adelantada del iterador sobre Listas.
// ¡¡Es necesaria porque Lista depende de IteradorLista pero Lista
//   todavía no está definida!!
template <typename E> class IteradorLista;

/*
 * Implementación de Listas para la asignatura de Estructuras
 * de datos de la URJC con tipo de elemento E.
 */
template <typename E>
class Lista
{
public:
  // Excepciones asociadas a Listas
  class EMemoriaAgotada: public std::runtime_error
  {
  public:
    EMemoriaAgotada(const std::string& w = "EMemoriaAgotada"): std::runtime_error(w) {}
  };

  class EListaVacia: public std::domain_error
  {
  public:
    EListaVacia(const std::string& w = "EListaVacia"): std::domain_error(w) {}
  };

  /** Constructor sin parámetros */
  Lista();

  /** Destructor: libera toda la memoria dinámica de la lista */
  ~Lista();

  /**
   *  POST: Deja la lista vacía.
   */
  void vaciar();

  /**
   *  PRE: Queda suficiente espacio para insertar
   *       un nuevo elemento en la 'Lista'.
   *  POST: inserta un nodo conteniendo 'e' al principio de
   *        la Lista.
   *  EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void construir(E e);

  /**
   * PRE: 'Lista' no está vacía
   * POST: devuelve el primer elemento de la Lista
   * EXCEPCIONES: 'EListaVacia' si 'Lista' está vacía
   */
  void primero(E& e);

  /**
   * POST: devuelve cierto si 'Lista' es la vacía.
   */
  bool esVacia();

  /**
   * POST: devuelve el número de elementos en 'Lista'.
   */
  int longitud();

  /**
   * PRE: 'Lista' no está vacía
   * POST: devuelve el último elemento de la Lista
   * EXCEPCIONES: 'EListaVacia' si 'Lista' está vacía
   */
  void ultimo(E& e);

  /**
   * POST: devuelve cierto si 'e' está en 'Lista'
   */
  bool pertenece(E e);

  /**
   * PRE: 'Lista' no está vacía;
   *       queda suficiente memoria para crear el resto
   * POST: devuelve en 'resto' una copia del resto de 'Lista'
   *       (todo menos el primer nodo)
   * EXCEPCIONES: 'EListaVacia' si 'Lista' está vacía
   *              'EMemoriaAgotada' si no queda memoria
   */
  void resto(Lista& r);

  /**
   * PRE: Queda suficiente espacio en memoria para insertar
   *      un nuevo elemento en la Lista
   * POST: 'Lista' es una nueva Lista cuyo último elementos
   *       es 'e'
   * EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void insertarFinal(E e);

  /**
   * PRE: Queda suficiente espacio en memoria para crear la concatenación
   * POST: 'salida' es una nueva Lista cuyo contenido es una copia de la
   *       concatenación de la 'Lista' con la Lista 'l'.
   * EXCEPCIONES: 'EMemoriaAgotada' si la memoria está llena
   */
  void concatenar(Lista l, Lista& salida);

  /**
   * POST: Elimina de la 'Lista' la primera aparición de 'e' (si la hay).
   */
  void borrarElemento(E e);

  /** Operador de asignación */
  Lista& operator=(Lista& l);

  /** Constructor de copia */
  Lista(Lista& l);

  /** Operador de comparación */
  bool operator==(Lista& l);
  bool operator!=(Lista& l);

  //-----------------------------------------------
  // Elementos necesarios para definir iteradores

  // Hacer friend a IteradorLista (para que tenga acceso a la
  // parte privada de Lista).
  friend class IteradorLista<E>;

  /** Definir el tipo de iterador para la lista */
  typedef IteradorLista<E> Iterador;

  /** Función que devuelve un iterador apuntando al primer elemento */
  Iterador primerIterador() { return Iterador(*this, this->primero_); }

  /** Función que devuelve un iterador apuntando al último elemento */
  Iterador ultimoIterador() { return Iterador(*this, this->ultimo_); }

private:
  /**
   *  El tipo Nodo es privado dado que sólo es necesario internamente
   *  en la implementación de Lista.
   */
  struct Nodo
  {
    E elemento;
    Nodo* siguiente;
    Nodo* anterior;
  };

  /**
   * POST: Devuelve un único nodo
   *        con elemento 'e', siguiente 'sig' y anterior 'ant'
   */
  Nodo* crearNodo(E e, Nodo* ant, Nodo* sig);

  /**
   * Implementación de Lista en memoria dinámica con:
   *   - Puntero al primer nodo
   *   - Puntero al úlWtimo nodo.
   */
  Nodo* primero_;
  Nodo* ultimo_;
};

template <typename E>
class IteradorLista
{
public:
  // Tipos asociados al IteradorLista.
  typedef typename Lista<E>::Nodo* Cursor;

  // Excepciones asociadas a IteradorLista
  class EIteradorNoValido: public std::runtime_error
  {
  public:
    EIteradorNoValido(const std::string& w = "EIteradorNoValido"): std::runtime_error(w) {}
  };

  // Constructor
  IteradorLista(Lista<E>& l, Cursor c): lista_(l), cursor_(c) {}

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
   *       un nuevo elemento en la lista
   * POST: inserta un nodo con elemento 'e' inmediatamente detrás
   *       (si el parámetro 'detras' es cierto) o inmediatamente
   *       delante (si el parámetro 'detras' es falso)
   *       del nodo apuntado por el iterador.  Si el iterador
   *       no es válido, se inserta el nuevo nodo al final de la lista.
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
   * POST: elimina el elemento apuntado por el iterador de la lista. El
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
   * POST: Devuelve cierto si el iterador apunta a algún nodo
   *       de la lista.s
   */
  bool esIteradorValido();

  /**
   * POST: Devuelve cierto si el iterador apunta al primer nodo de la
   *       lista
   */
  bool esPrimero();

  /**
   * POST: Devuelve cierto si el iterador apunta al último nodo de la
   *       lista
   */
  bool esUltimo();

private:
  // Operaciones auxiliares de IteradorLista::insertar.
  void insertarDelante(Cursor c);
  void insertarDetras(Cursor c);

  // Tenemos una referencia a la lista sobre la que iteramos
  Lista<E>& lista_;

  // Datos que necesitamos para iterar sobre la lista (sólo un puntero
  // al nodo por el que vamos.
  Cursor cursor_;
};

#include "lista.cpp"
#include "iterador_lista.cpp"
#include "lista_io.cpp"

} // namespace ed

#endif // LISTA_HPP
