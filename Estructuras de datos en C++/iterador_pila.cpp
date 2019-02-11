/**
* Modulo: IteradorPila
* Tipo: Programa() Interfaz-Implementacion TAD (X)       Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de los iteradores para el TAD Pila
*/

#ifndef nullptr
#define nullptr NULL
#endif

template <typename E>
bool IteradorPila<E>::permiteIterarAscendente()
{
  return true;
}

template <typename E>
bool IteradorPila<E>::permiteIterarDescendente()
{
  return false;
}

template <typename E>
bool IteradorPila<E>::permiteInsertar()
{
  return false;
}

template <typename E>
bool IteradorPila<E>::permiteEliminar()
{
  return false;
}

template <typename E>
void IteradorPila<E>::obtenerElemento(E& e)
{
  try
  {
    cursor_.obtenerElemento(e);
  }
  catch (typename IteradorLista<E>::EIteradorNoValido)
  {
    // Traducción de excepciones de IteradorLista<E>::EIteradorNoValido
    // a IteradorPila<E, F>::EIteradorNoValido.
    throw EIteradorNoValido();
  }
}

template <typename E>
void IteradorPila<E>::insertar(E e, bool detras)
{
  cursor_.insertar(e, detras);
}

template <typename E>
void IteradorPila<E>::reemplazar(E e)
{
  try
  {
    cursor_.reemplazar(e);
  }
  catch (typename IteradorLista<E>::EIteradorNoValido)
  {
    // Traducción de excepciones de IteradorLista<E>::EIteradorNoValido
    // a IteradorPila<E, F>::EIteradorNoValido.
    throw EIteradorNoValido();
  }
}

template <typename E>
void IteradorPila<E>::siguiente()
{
  try
  {
    cursor_.siguiente();
  }
  catch (typename IteradorLista<E>::EIteradorNoValido)
  {
    // Traducción de excepciones de IteradorLista<E>::EIteradorNoValido
    // a IteradorPila<E, F>::EIteradorNoValido.
    throw EIteradorNoValido();
  }
}

template <typename E>
void IteradorPila<E>::anterior()
{
  try
  {
    cursor_.anterior();
  }
  catch (typename IteradorLista<E>::EIteradorNoValido)
  {
    // Traducción de excepciones de IteradorLista<E>::EIteradorNoValido
    // a IteradorPila<E, F>::EIteradorNoValido.
    throw EIteradorNoValido();
  }
}

template <typename E>
bool IteradorPila<E>::esIteradorValido()
{
  return cursor_.esIteradorValido();
}

template <typename E>
bool IteradorPila<E>::esPrimero()
{
  return cursor_.esPrimero();
}

template <typename E>
bool IteradorPila<E>::esUltimo()
{
  return cursor_.esUltimo();
}
