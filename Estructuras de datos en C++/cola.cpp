/**
* Modulo: Cola
* Tipo: Programa() Interfaz TAD () Implementacion TAD (X) Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular Colas de elementos implementada utilizando
*              una cola internamente.
*/

#ifndef nullptr
#define nullptr NULL
#endif

template <typename E>
void Cola<E>::vaciar()
//  COMPLEJIDAD: O(N), siendo N la longitud de la cola.
{
  almacen_.vaciar();
}

template <typename E>
Cola<E>::Cola(): almacen_()
{
}

template <typename E>
Cola<E>::~Cola()
//  COMPLEJIDAD: O(N), siendo N la longitud de la cola.
{
  almacen_.vaciar();
}

template <typename E>
void Cola<E>::insertar(E e)
//  COMPLEJIDAD: O(1)
{
  almacen_.insertarFinal(e);
}

template <typename E>
void Cola<E>::primero(E& e)
//  COMPLEJIDAD: O(1)
{
  try
  {
    almacen_.primero(e);
  }
  catch (typename Lista<E>::EListaVacia)
  {
    // Traducción de excepciones de Lista<E>::EListaVacia
    // a Cola<E>::EColaVacia
    throw EColaVacia();
  }
}

template <typename E>
bool Cola<E>::esVacia()
//  COMPLEJIDAD: O(1)
{
  return almacen_.esVacia();
}

template <typename E>
int Cola<E>::longitud()
{
  return almacen_.longitud();
}

template <typename E>
void Cola<E>::eliminar()
{
  E e;
  primero(e); // llamada a operación de cola.
  almacen_.borrarElemento(e);
  // No es necesario generar la excepción ColaVacia.
  // En el caso de que la cola esté vacía, la genera
  // la llamada a cima.
}

template<typename E>
Cola<E>& Cola<E>::operator=(Cola& p)
// Operador de asignación
{
  // Usamos el operador de asignación de las listas.
  almacen_ = p.almacen_;

  return (*this);
}

template<typename E>
Cola<E>::Cola(Cola<E>& p)
// Constructor de copia
{
  // Utilizamos el operador de asignación de listas.
  almacen_ = p.almacen_;
}

template<typename E>
bool Cola<E>::operator==(Cola& p)
// Operador de comparación: "¿son iguales elemento a elemento?"
{
  return (almacen_ == p.almacen_);
}

template<typename E>
bool Cola<E>::operator!=(Cola& p)
{
  return !((*this) == p); // Utilizamos operator==
}
