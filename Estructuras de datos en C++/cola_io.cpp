/**
* Modulo: ColaIO
* Tipo: Programa() Interfaz TAD () Implementacion TAD () Otros(X)
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de las operaciones de entrada/salida
*              de colas.
*/

/**
 *  El formato establecido para la lectura/escritura de una cola
 *  es simplemente un entero con el número de elementos de la cola y
 *  a continuación la sucesión de los elementos que componen la cola
 *  separados por espacios (de fondo a la cima). Por ejemplo,
 *  la cola con cima 1, y fondo 3, con elementos 1, 2, 3 se escribirá
 *  en fichero como (sin las comillas):
 *
 *  "3 1 2 3"
 *
 *  POST: Se escribe "c" en el stream con el formato especificado
 *        más arriba.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Cola<T>& c)
{
  T e;

  os << c.longitud();
  if (!c.esVacia())
  {
    os << " ";
  }

  typename Cola<T>::Iterador it = c.primerIterador();
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
 * PRE : La entrada por defecto almacena una cola "c" con el formato adecuado
 *       Queda espacio en memoria para crear "c"
 * POST: 'p' contendrá la lista de elementos leída
 * EXCEPCIONES: Se activa 'EErrorEntrada' si lo almacenado no tiene la
 *       forma especificada en operator<< o si no queda espacio en memoria
 *       y 'EMemoriaAgotada' si no queda espacio de memoria.
 */
template<typename T>
std::istream& operator>>(std::istream& is, Cola<T>& c)
{
  T e;
  int longitud;
  is >> longitud;

  for (int i=0; i<longitud; i++)
  {
    is >> e;
    c.insertar(e);
  }

  return is;
}
