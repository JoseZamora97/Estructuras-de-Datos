/**
* Modulo: Pila
* Tipo: Programa() Interfaz TAD () Implementacion TAD (X) Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular Pilas de elementos implementada utilizando
*              una pila internamente.
*/

#ifndef nullptr
#define nullptr NULL
#endif

template <typename E>
void Pila<E>::vaciar()
//  COMPLEJIDAD: O(N), siendo N la longitud de la pila.
{
  almacen_.vaciar();
}

template <typename E>
Pila<E>::Pila(): almacen_()
{
}

template <typename E>
Pila<E>::~Pila()
//  COMPLEJIDAD: O(N), siendo N la longitud de la pila.
{
  almacen_.vaciar();
}

template <typename E>
void Pila<E>::apilar(E e)
//  COMPLEJIDAD: O(1)
{
  almacen_.construir(e);
}

template <typename E>
void Pila<E>::cima(E& e)
//  COMPLEJIDAD: O(1)
{
  try
  {
    almacen_.primero(e);
  }
  catch (typename Lista<E>::EListaVacia)
  {
    // Traducción de excepciones de Lista<E>::EListaVacia
    // a Pila<E>::EPilaVacia
    throw EPilaVacia();
  }
}

template <typename E>
bool Pila<E>::esVacia()
//  COMPLEJIDAD: O(1)
{
  return almacen_.esVacia();
}

template <typename E>
int Pila<E>::longitud()
{
  return almacen_.longitud();
}

template <typename E>
void Pila<E>::desapilar()
{
  E e;
  cima(e);
  almacen_.borrarElemento(e);
  // No es necesario generar la excepción PilaVacia.
  // En el caso ode que la pila esté vacía, la genera
  // la llamada a cima.
}

template<typename E>
Pila<E>& Pila<E>::operator=(Pila& p)
// Operador de asignación
{
  // Usamos el operador de asignación de las listas.
  almacen_ = p.almacen_;

  return (*this);
}

template<typename E>
Pila<E>::Pila(Pila<E>& p)
// Constructor de copia
{
  // Utilizamos el operador de asignación de listas.
  almacen_ = p.almacen_;
}

template<typename E>
bool Pila<E>::operator==(Pila& p)
// Operador de comparación: "¿son iguales elemento a elemento?"
{
  return (almacen_ == p.almacen_);
}

template<typename E>
bool Pila<E>::operator!=(Pila& p)
{
  return !((*this) == p); // Utilizamos operator==
}
