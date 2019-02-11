/**
* Modulo: PilaIO
* Tipo: Programa() Interfaz TAD () Implementacion TAD () Otros(X)
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de las operaciones de entrada/salida
*              de pilas.
*/

/**
 *  El formato establecido para la lectura/escritura de una lista
 *  es simplemente un entero con el número de elementos de la pila y
 *  a continuación la sucesión de los elementos que componen la pila
 *  separados por espacios (de fondo a la cima). Por ejemplo,
 *  la pila con cima 1, y fondo 3, con elementos 1, 2, 3 se escribirá
 *  en fichero como (sin las comillas):
 *
 *  "3 1 2 3"
 *
 *  POST: Se escribe 'p' en el stream con el formato especificado
 *        más arriba.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Pila<T>& p)
{
  T e;

  os << p.longitud();
  if (!p.esVacia())
  {
    os << " ";
  }

  typename Pila<T>::Iterador it = p.primerIterador();
  while (it.esIteradorValido())
  {
    it.obtenerElemento(e);
    os << e;
    if (!it.esUltimo())
    {
      os << " ";
    }
    it.siguiente();
  }

  return os;
}

/**
 * PRE : La entrada por defecto almacena una pila "p" con el formato adecuado
 *       Queda espacio en memoria para crear 'p'
 * POST: 'p' contendrá la lista de elementos leída
 * EXCEPCIONES: Se activa 'EErrorEntrada' si lo almacenado no tiene la
 *       forma especificada en operator<< o si no queda espacio en memoria
 *       y 'EMemoriaAgotada' si no queda espacio de memoria.
 */
template<typename T>
std::istream& operator>>(std::istream& is, Pila<T>& p)
{
  T e;
  int longitud;
  is >> longitud;

  Pila<T> p_aux;
  for (int i=0; i<longitud; i++)
  {
    is >> e;
    p_aux.apilar(e);
  }

  // En este punto los elementos están en la pila al revés de como
  // deberían. Les damos la vuelta sobre p.
  while (!p_aux.esVacia())
  {
    p_aux.cima(e);
    p_aux.desapilar();
    p.apilar(e);
  }

  return is;
}
