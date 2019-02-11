/**
* Modulo: ListaIO
* Tipo: Programa() Interfaz TAD () Implementacion TAD () Otros(X)
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de las operaciones de entrada/salida
*              de listas.
*/

/**
 *  El formato establecido para la lectura/escritura de una lista
 *  es simplemente un entero con el número de elementos de la lista y
 *  a continuación la sucesión de los elementos que componen la lista
 *  separados por espacios. Por ejemplo, la lista [1, 2, 3] se escribirá
 *  en fichero como (sin las comillas):
 *
 *  "3 1 2 3"
 *
 *  POST: Se escribe 'l' en el stream con el formato especificado
 *        más arriba.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Lista<T>& l)
{
  T e;

  os << l.longitud();
  if (!l.esVacia())
  {
    os << " ";
  }

  typename Lista<T>::Iterador it = l.primerIterador();
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
 * PRE : La entrada por defecto almacena una lista con el formato adecuado
 *        Queda espacio en memoria para crear 'lista'
 * POST: 'lista' contendrá la lista de elementos leída
 * EXCEPCIONES: Se activa 'EErrorEntrada' si lo almacenado no tiene la
 *       forma especificada en operator<< o si no queda espacio en memoria
 *       y 'EMemoriaAgotada' si no queda espacio de memoria.
 */
template<typename T>
std::istream& operator>>(std::istream& is, Lista<T>& l)
{
  T e;
  int longitud;
  is >> longitud;

  for (int i=0; i< longitud; i++)
  {
    is >> e;
    l.insertarFinal(e);
  }

  return is;
}
