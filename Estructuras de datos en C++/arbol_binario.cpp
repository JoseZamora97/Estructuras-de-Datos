/**
* Modulo: ArbolBinario
* Tipo: Programa() Interfaz TAD () Implementacion TAD (X) Otros()
* Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
* Fecha: 2016
* Descripción: Implementación de un TAD para representar
*              y manipular ArbolBinarios de elementos implementada utilizando
*              una lista internamente.
*/

#ifndef nullptr
#define nullptr NULL
#endif

template <typename E>
typename ArbolBinario<E>::Nodo*
ArbolBinario<E>::crearNodo(ArbolBinario<E>::Nodo* izqdo, E e, ArbolBinario<E>::Nodo* dcho)
{
  ArbolBinario<E>::Nodo* pNodo;

  // new(std::nothrow) permite que pNodo sea nullptr si no hay memoria
  // en lugar de lanzar la excepción std::bad_allow si nos quedamos
  // sin memoria. Lo hacemos así para hacer la traducción de excepciones de
  // std::bad_allow a la que hemos elegido lanzar ArbolBinario<E>::EMemoriaAgotada.
  pNodo = new(std::nothrow) Nodo;
  if (!pNodo)
  {
    throw EMemoriaAgotada();
  }
  pNodo->raiz = e;
  pNodo->hijoizqdo = izqdo;
  pNodo->hijodcho = dcho;

  return pNodo;
}

// Implementación recursiva de la operación destruir árbol binario.
template <typename E>
void ArbolBinario<E>::destruir(ArbolBinario<E>::Nodo*& pNodo)
{
  if (pNodo != nullptr) // Árbol no vacío.
  {
    destruir(pNodo->hijoizqdo);
    destruir(pNodo->hijodcho);
    delete pNodo;
    pNodo = nullptr;
  }
}

template <typename E>
void ArbolBinario<E>::vaciar()
{
  if (es_propietario_)
  {
    destruir(nodo_raiz_);
  }
  nodo_raiz_ = nullptr;
  es_propietario_ = true;
}

template <typename E>
ArbolBinario<E>::ArbolBinario()
{
  nodo_raiz_ = nullptr;
  es_propietario_ = true;
}

template <typename E>
ArbolBinario<E>::~ArbolBinario()
{
  vaciar();
}

template <typename E>
void ArbolBinario<E>::construir(ArbolBinario& izqdo, E e, ArbolBinario& dcho)
{
  if ((nodo_raiz_ != izqdo.nodo_raiz_) && (nodo_raiz_ != dcho.nodo_raiz_))
  {
    destruir(this->nodo_raiz_);
  }

  nodo_raiz_ = crearNodo(izqdo.nodo_raiz_, e, dcho.nodo_raiz_);

  // Ahora los nodos del izqdo y los de dcho pertenecen al árbol actual.
  es_propietario_ = true;

  // Por tanto, hacemos que izqdo y dcho terminen cediendo la propiedad
  // al árbol actual.
  izqdo.es_propietario_ = false;
  dcho.es_propietario_ = false;
}

template <typename E>
void ArbolBinario<E>::raiz(E& raiz)
{
  if (esVacio())
  {
    throw EArbolVacio();
  }

  raiz = nodo_raiz_->raiz;
}

template <typename E>
void ArbolBinario<E>::cambiarRaiz(E e)
{
  if (esVacio())
  {
    throw EArbolVacio();
  }

  nodo_raiz_->raiz = e;
}

template <typename E>
void ArbolBinario<E>::hijoIzquierdo(ArbolBinario<E>& izqdo)
{
  if (esVacio())
  {
    throw EArbolVacio();
  }

  izqdo.nodo_raiz_ = nodo_raiz_->hijoizqdo;
  izqdo.es_propietario_ = false;
}

template <typename E>
void ArbolBinario<E>::hijoDerecho(ArbolBinario<E>& dcho)
{
  if (esVacio())
  {
    throw EArbolVacio();
  }

  dcho.nodo_raiz_ = nodo_raiz_->hijodcho;
  dcho.es_propietario_ = false;
}

template <typename E>
bool ArbolBinario<E>::esVacio()
{
  return (nodo_raiz_ == nullptr);
}

// Implementación recursiva de la operación de copia de
// árboles binarios.
template<typename E>
void ArbolBinario<E>::copiar(Nodo*& pNodoDestino, Nodo*& pNodoOrigen)
// Pasamos un puntero por referencia. ¡El puntero puede verse
// modificado!
{
  if (pNodoOrigen == nullptr) // El origen 'a' es vacío
  {
    destruir(pNodoDestino);
  }
  else if (pNodoDestino == nullptr) // el destino (*this) es vacío.
  {
    Nodo* pIzqdo = nullptr;
    Nodo* pDcho = nullptr;
    copiar(pIzqdo, pNodoOrigen->hijoizqdo);
    copiar(pDcho, pNodoOrigen->hijodcho);
    E e = pNodoOrigen->raiz;

    // Dejamos en arbol_destino la copia de origen.
    pNodoDestino = crearNodo(pIzqdo, e, pDcho);
  }
  else // reutilizar la memoria de *this.
  {
    pNodoDestino->raiz = pNodoOrigen->raiz;

    if (pNodoOrigen->hijoizqdo == nullptr)
    {
      destruir(pNodoDestino->hijoizqdo);
    }
    copiar(pNodoDestino->hijoizqdo, pNodoOrigen->hijoizqdo);

    if (pNodoOrigen->hijodcho == nullptr)
    {
      destruir(pNodoDestino->hijodcho);
    }
    copiar(pNodoDestino->hijodcho, pNodoOrigen->hijodcho);
  }
}

template<typename E>
ArbolBinario<E>& ArbolBinario<E>::operator=(ArbolBinario& a)
// Operador de asignación
{
  copiar(nodo_raiz_, a.nodo_raiz_);
  es_propietario_ = true;

  return (*this);
}

template<typename E>
ArbolBinario<E>::ArbolBinario(ArbolBinario<E>& a)
// Constructor de copia
{
  nodo_raiz_ = nullptr;
  es_propietario_ = true;

  (*this) = a;
}

// Implementación recursiva de la operación de comparación de
// árboles binarios.
template<typename E>
bool ArbolBinario<E>::iguales(ArbolBinario<E>::Nodo* pNodo1,
                              ArbolBinario<E>::Nodo* pNodo2)
{
  if ((pNodo1 == nullptr) && (pNodo2 == nullptr))
  {
    return true;
  }
  else if ((pNodo1 == nullptr) || (pNodo2 == nullptr))
  {
    return false;
  }
  else
  {
    return (pNodo1->raiz == pNodo2->raiz) &&
            iguales(pNodo1->hijoizqdo, pNodo2->hijoizqdo) &&
            iguales(pNodo1->hijodcho, pNodo2->hijodcho);
  }
}

template<typename E>
bool ArbolBinario<E>::operator==(ArbolBinario& a)
// Operador de comparación: "¿son iguales elemento a elemento?"
{
  return iguales(nodo_raiz_, a.nodo_raiz_);
}

template<typename E>
bool ArbolBinario<E>::operator!=(ArbolBinario& c)
{
  return !((*this) == c); // Utilizamos operator==
}
