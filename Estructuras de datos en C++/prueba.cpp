/**
 * Modulo: prueba.cpp
 * Tipo: Programa(x) Interfaz-Implementacion TAD ()       Otros()
 * Autor: Jose Miguel Zamora Batista (jm.zamora.2016@alumnos.urjc.es)
 * Fecha: 2016
 * Descripción: programa de prueba de las operaciones sobre Árboles Binarios.
 * Lee la operación a probar de la entrada estándar y escribe el resultado
 * en la salida estándar.
 */

// Descomentar para mandar al Mooshak y Comentar para probar desde fichero
#undef ENTRADA_DESDE_FICHERO

// Descomentar para que el programa de prueba tome la entrada del fichero
// prueba_listas.txt y ¡Comentar para mandar al Mooshak!
//#define ENTRADA_DESDE_FICHERO

#include <iostream>
#ifdef ENTRADA_DESDE_FICHERO
  #include <fstream>
  #include <sstream>
#endif
#include "operaciones_arboles.hpp"
#include "lista.hpp"

#define Elemento int
#define ArbolPrueba ed::ArbolBinario<Elemento>
#define ListaPrueba ed::Lista<Elemento>
//a ( 34 ( 45 ( 94 ( 12 () () ) () ) ( 56 ( 13 ( 26 ( 45 () () ) () ) () ) () ) ) ( 789 () () ) )

void probarNumHijosSoloHijoDchoVacio(std::istream& is)
{
  ArbolPrueba a;
  is >> a;

  std::cout << numNodosSoloHijoDchoVacio(a);
}

void probarRecorridoEnAnchuraIterativo(std::istream& is)
{
  ArbolPrueba a;
  ListaPrueba recorrido;
  is >> a;

  recorridoEnAnchuraIterativo(a, recorrido);

  std::cout << recorrido;
}

void probarElementosNivelK(std::istream& is)
{
  ArbolPrueba a;
  ListaPrueba nivel_k;
  int k;
  is >> k;
  is >> a;

  elementosNivelK(a, k, nivel_k);

  std::cout << nivel_k;
}

void probarEsCompleto(std::istream& is)
{
  ArbolPrueba a;
  is >> a;

  if (esCompleto(a))
  {
    std::cout << "COMPLETO";
  }
  else
  {
    std::cout << "NO COMPLETO";
  }
}

int main()
{
  char opcion;

#ifdef ENTRADA_DESDE_FICHERO
  std::ifstream is("prueba_arboles.txt");
  
  if (!is.is_open())
  {
    std::cerr << "No se puede abrir el fichero prueba_arboles.txt" << std::endl;
    return 1;
  }
#else
#define is std::cin
#endif

  try
  {
      // Lectura de la operación a probar
      is >> opcion;

      switch(opcion)
      {
        case 'd': probarNumHijosSoloHijoDchoVacio(is); break;
        case 'a': probarRecorridoEnAnchuraIterativo(is); break;
        case 'k': probarElementosNivelK(is); break;
        case 'c': probarEsCompleto(is); break;
      }
    }
    catch (std::exception const& excepcion)
    {
      std::cout << "EXCEPCION GENERADA: "  <<  excepcion.what();
    }

#ifdef ENTRADA_DESDE_FICHERO
    // Cerrar el fichero abierto.
    is.close();
#endif

  return 0;
}

